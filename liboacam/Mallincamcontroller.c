/*****************************************************************************
 *
 * Mallincamcontroller.c -- Main camera controller thread
 *
 * Copyright 2016 James Fidell (james@openastroproject.org)
 *
 * License:
 *
 * This file is part of the Open Astro Project.
 *
 * The Open Astro Project is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Open Astro Project is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Open Astro Project.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include <oa_common.h>

#include <pthread.h>
#include <sys/time.h>

#include <openastro/camera.h>

#include "oacamprivate.h"
#include "unimplemented.h"
#include "Mallincamoacam.h"
#include "Mallincamstate.h"


static int	_processSetControl ( MALLINCAM_STATE*, OA_COMMAND* );
static int	_processGetControl ( MALLINCAM_STATE*, OA_COMMAND* );
static int	_processSetResolution ( MALLINCAM_STATE*, OA_COMMAND* );
//static int	_processSetROI ( oaCamera*, OA_COMMAND* );
static int	_processStreamingStart ( MALLINCAM_STATE*, OA_COMMAND* );
static int	_processStreamingStop ( MALLINCAM_STATE*, OA_COMMAND* );
static int	_doStart ( MALLINCAM_STATE* );
static int	_doStop ( MALLINCAM_STATE* );
static int	_setBinning ( MALLINCAM_STATE*, int );
static int	_setColourMode ( MALLINCAM_STATE*, int );
static int	_setBitDepth ( MALLINCAM_STATE*, int );


void*
oacamMallincamcontroller ( void* param )
{
  oaCamera*		camera = param;
  MALLINCAM_STATE*	cameraInfo = camera->_private;
  OA_COMMAND*		command;
  int			exitThread = 0;
  int			resultCode;
  int			streaming = 0;

  do {
    pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
    exitThread = cameraInfo->stopControllerThread;
    pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
    if ( exitThread ) {
      break;
    } else {
      pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
      // stop us busy-waiting
      streaming = cameraInfo->isStreaming;
      if ( !streaming && oaDLListIsEmpty ( cameraInfo->commandQueue )) {
        pthread_cond_wait ( &cameraInfo->commandQueued,
            &cameraInfo->commandQueueMutex );
      }
      pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
    }
    do {
      command = oaDLListRemoveFromHead ( cameraInfo->commandQueue );
      if ( command ) {
        switch ( command->commandType ) {
          case OA_CMD_CONTROL_SET:
            resultCode = _processSetControl ( cameraInfo, command );
            break;
          case OA_CMD_CONTROL_GET:
            resultCode = _processGetControl ( cameraInfo, command );
            break;
          case OA_CMD_RESOLUTION_SET:
            resultCode = _processSetResolution ( cameraInfo, command );
            break;
          /*
          case OA_CMD_ROI_SET:
            resultCode = _processSetROI ( camera, command );
            break;
           */
          case OA_CMD_START:
            resultCode = _processStreamingStart ( cameraInfo, command );
            break;
          case OA_CMD_STOP:
            resultCode = _processStreamingStop ( cameraInfo, command );
            break;
          default:
            fprintf ( stderr, "Invalid command type %d in controller\n",
                command->commandType );
            resultCode = -OA_ERR_INVALID_CONTROL;
            break;
        }
        if ( command->callback ) {
        } else {
          pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
          command->completed = 1;
          command->resultCode = resultCode;
          pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
          pthread_cond_broadcast ( &cameraInfo->commandComplete );
        }
      }
    } while ( command );
  } while ( !exitThread );

  return 0;
}


void
_MallincamFrameCallback ( const void *frame, const BITMAPINFOHEADER*
    bitmapHeader, BOOL bSnap, void *ptr )
{
  MALLINCAM_STATE*	cameraInfo = ptr;
  int			buffersFree, nextBuffer, shiftBits, bitsPerPixel;
  unsigned int		dataLength;

  pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
  buffersFree = cameraInfo->buffersFree;
  bitsPerPixel = cameraInfo->currentBitsPerPixel;
  pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );

  if ( frame && buffersFree && bitmapHeader->biSizeImage ) {
    if (( dataLength = bitmapHeader->biSizeImage ) >
        cameraInfo->imageBufferLength ) {
      dataLength = cameraInfo->imageBufferLength;
    }
    nextBuffer = cameraInfo->nextBuffer;

    // Now here's the fun...  In 12-bit (and presumably 10- and 14-bit)
    // mode Mallincam cameras appear to return little-endian data, but
    // right-aligned rather than left-aligned as many other cameras do.
    // So if we have such an image we try to fix it here.
    // FIX ME -- I'm not sure this is the right place to be doing this.
    // Perhaps there should be a flag to tell the user whether the data is
    // left-or right-aligned and they can sort it out.

    shiftBits = 0;
    if ( bitsPerPixel > 8 && bitsPerPixel < 16 ) {
      shiftBits = 16 - bitsPerPixel;
    }

    if ( shiftBits ) {
      const uint16_t	*s = frame;
      uint16_t		*t = cameraInfo->buffers[ nextBuffer ].start;
      uint16_t		v;
      unsigned int	i;

      for ( i = 0; i < dataLength; i += 2 ) {
        v = *s++;
        v <<= shiftBits;
        *t++ = v;
      }
    } else {
      ( void ) memcpy ( cameraInfo->buffers[ nextBuffer ].start, frame,
          dataLength );
    }

    cameraInfo->frameCallbacks[ nextBuffer ].callbackType =
        OA_CALLBACK_NEW_FRAME;
    cameraInfo->frameCallbacks[ nextBuffer ].callback =
        cameraInfo->streamingCallback.callback;
    cameraInfo->frameCallbacks[ nextBuffer ].callbackArg =
        cameraInfo->streamingCallback.callbackArg;
    cameraInfo->frameCallbacks[ nextBuffer ].buffer =
        cameraInfo->buffers[ nextBuffer ].start;
    cameraInfo->frameCallbacks[ nextBuffer ].bufferLen = dataLength;
    pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
    oaDLListAddToTail ( cameraInfo->callbackQueue,
        &cameraInfo->frameCallbacks[ nextBuffer ]);
    cameraInfo->buffersFree--;
    cameraInfo->nextBuffer = ( nextBuffer + 1 ) % cameraInfo->configuredBuffers;
    pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );
    pthread_cond_broadcast ( &cameraInfo->callbackQueued );
  }
}


static int
_processSetControl ( MALLINCAM_STATE* cameraInfo, OA_COMMAND* command )
{
  oaControlValue	*valp = command->commandData;
  int			control = command->controlId, val;

  switch ( control ) {

    case OA_CAM_CTRL_BRIGHTNESS:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= TOUPCAM_BRIGHTNESS_MIN && val <= TOUPCAM_BRIGHTNESS_MAX ) {
        if (( *p_Mallincam_put_Brightness )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_Brightness ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_CONTRAST:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= TOUPCAM_CONTRAST_MIN && val <= TOUPCAM_CONTRAST_MAX ) {
        if (( *p_Mallincam_put_Contrast )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_Contrast ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_GAMMA:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= TOUPCAM_GAMMA_MIN && val <= TOUPCAM_GAMMA_MAX ) {
        if (( *p_Mallincam_put_Gamma )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_Gamma ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_HFLIP:
      if ( OA_CTRL_TYPE_BOOLEAN != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where boolean expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->boolean ? 1 : 0;
      if (( *p_Mallincam_put_HFlip )( cameraInfo->handle, val )) {
        fprintf ( stderr, "Mallincam_put_HFlip ( %d ) failed\n", val );
        return -OA_ERR_CAMERA_IO;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_VFLIP:
      if ( OA_CTRL_TYPE_BOOLEAN != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where boolean expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->boolean ? 1 : 0;
      if (( *p_Mallincam_put_VFlip )( cameraInfo->handle, val )) {
        fprintf ( stderr, "Mallincam_put_VFlip ( %d ) failed\n", val );
        return -OA_ERR_CAMERA_IO;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_AUTO_EXPOSURE:
      if ( OA_CTRL_TYPE_BOOLEAN != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where boolean expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = ( valp->boolean == OA_EXPOSURE_MANUAL ) ? 0 : 1;
      if (( *p_Mallincam_put_AutoExpoEnable )( cameraInfo->handle, val )) {
        fprintf ( stderr, "Mallincam_put_AutoExpoEnable ( %d ) failed\n", val );
        return -OA_ERR_CAMERA_IO;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_EXPOSURE_ABSOLUTE:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= cameraInfo->exposureMin && val <= cameraInfo->exposureMax ) {
        if (( *p_Mallincam_put_ExpoTime )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_ExpoTime ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_GAIN:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= cameraInfo->gainMin && val <= cameraInfo->gainMax ) {
        if (( *p_Mallincam_put_ExpoAGain )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_ExpoAGain ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_SPEED:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= 0 && val <= cameraInfo->speedMax ) {
        if (( *p_Mallincam_put_Speed )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_Speed ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_HUE:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= TOUPCAM_HUE_MIN && val <= TOUPCAM_HUE_MAX ) {
        if (( *p_Mallincam_put_Hue )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_Hue ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_SATURATION:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= TOUPCAM_SATURATION_MIN && val <= TOUPCAM_SATURATION_MAX ) {
        if (( *p_Mallincam_put_Saturation )( cameraInfo->handle, val )) {
          fprintf ( stderr, "Mallincam_put_Saturation ( %d ) failed\n", val );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_RED_BALANCE:
    case OA_CAM_CTRL_BLUE_BALANCE:
    case OA_CAM_CTRL_GREEN_BALANCE:
      if ( OA_CTRL_TYPE_INT32 != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->int32;
      if ( val >= TOUPCAM_WBGAIN_MIN && val <= TOUPCAM_WBGAIN_MAX ) {
        int gain[3];
        if (( *p_Mallincam_get_WhiteBalanceGain )( cameraInfo->handle, gain )) {
          fprintf ( stderr, "Mallincam_get_WhiteBalanceGain (gain[3]) failed\n" );
          return -OA_ERR_CAMERA_IO;
        }
        switch ( control ) {
          case OA_CAM_CTRL_RED_BALANCE:
            gain[0] = val;
            break;
          case OA_CAM_CTRL_BLUE_BALANCE:
            gain[2] = val;
            break;
          case OA_CAM_CTRL_GREEN_BALANCE:
            gain[1] = val;
            break;
        }
        if (( *p_Mallincam_put_WhiteBalanceGain )( cameraInfo->handle, gain )) {
          fprintf ( stderr, "Mallincam_put_WhiteBalanceGain (gain[3]) failed\n" );
          return -OA_ERR_CAMERA_IO;
        }
      } else {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_BINNING:
      if ( OA_CTRL_TYPE_DISCRETE != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where int32 expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->discrete;
      return _setBinning ( cameraInfo, val );
      break;

    case OA_CAM_CTRL_COOLER:
      if ( OA_CTRL_TYPE_BOOLEAN != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where boolean expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->boolean ? 0 : 1;
      if (( *p_Mallincam_put_Option )( cameraInfo->handle,
          TOUPCAM_OPTION_COOLER, 1 )) {
        fprintf ( stderr, "Mallincam_put_Option ( cooler, %d ) failed\n", val );
        return -OA_ERR_CAMERA_IO;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_FAN:
      if ( OA_CTRL_TYPE_BOOLEAN != valp->valueType ) {
        fprintf ( stderr, "%s: invalid control type %d where boolean expected "
            "for control %d\n", __FUNCTION__, valp->valueType, control );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->boolean ? 0 : 1;
      if (( *p_Mallincam_put_Option )( cameraInfo->handle,
          TOUPCAM_OPTION_FAN, 1 )) {
        fprintf ( stderr, "Mallincam_put_Option ( fan, %d ) failed\n", val );
        return -OA_ERR_CAMERA_IO;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_COLOUR_MODE:
      if ( valp->valueType != OA_CTRL_TYPE_DISCRETE ) {
        fprintf ( stderr, "%s: invalid control type %d where discrete "
            "expected\n", __FUNCTION__, valp->valueType );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->discrete;
      if ( OA_COLOUR_MODE_RAW != val && OA_COLOUR_MODE_NONRAW != val ) {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return _setColourMode ( cameraInfo, val );
      break;

    case OA_CAM_CTRL_BIT_DEPTH:
      if ( valp->valueType != OA_CTRL_TYPE_DISCRETE ) {
        fprintf ( stderr, "%s: invalid control type %d where discrete "
            "expected\n", __FUNCTION__, valp->valueType );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      val = valp->discrete;
      return _setBitDepth ( cameraInfo, val );
      break;
  }

  fprintf ( stderr, "Unrecognised control %d in %s\n", control, __FUNCTION__ );
  return -OA_ERR_INVALID_CONTROL;
}


static int
_processGetControl ( MALLINCAM_STATE* cameraInfo, OA_COMMAND* command )
{
  oaControlValue	*valp = command->commandData;
  int			control = command->controlId;
  int32_t		val_s32;
  unsigned short	val_u16;
  short			val_s16;

  switch ( control ) {

    case OA_CAM_CTRL_BRIGHTNESS:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_Brightness )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_Brightness failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_CONTRAST:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_Contrast )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_Contrast failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_GAMMA:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_Gamma )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_Gamma failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_HFLIP:
      valp->valueType = OA_CTRL_TYPE_BOOLEAN;
      if (( *p_Mallincam_get_HFlip )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_HFlip failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->boolean = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_VFLIP:
      valp->valueType = OA_CTRL_TYPE_BOOLEAN;
      if (( *p_Mallincam_get_VFlip )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_VFlip failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->boolean = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_AUTO_EXPOSURE:
      valp->valueType = OA_CTRL_TYPE_BOOLEAN;
      if (( *p_Mallincam_get_AutoExpoEnable )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_AutoExpoEnable failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->boolean = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_EXPOSURE_ABSOLUTE:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_ExpoTime )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_ExpoTime failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_GAIN:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_ExpoAGain )( cameraInfo->handle, &val_u16 )) {
        fprintf ( stderr, "Mallincam_get_ExpoAGain failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_u16;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_SPEED:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_Speed )( cameraInfo->handle, &val_u16 )) {
        fprintf ( stderr, "Mallincam_get_Speed failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_u16;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_HUE:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_Hue )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_Hue failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_SATURATION:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_Saturation )( cameraInfo->handle, &val_s32 )) {
        fprintf ( stderr, "Mallincam_get_Saturation failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_s32;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_RED_BALANCE:
    case OA_CAM_CTRL_BLUE_BALANCE:
    case OA_CAM_CTRL_GREEN_BALANCE:
    {
      int gain[3];
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_WhiteBalanceGain )( cameraInfo->handle, gain )) {
        fprintf ( stderr, "Mallincam_get_WhiteBalanceGain (gain[3]) failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      switch ( control ) {
        case OA_CAM_CTRL_RED_BALANCE:
          val_s32 = gain[0];
          break;
        case OA_CAM_CTRL_BLUE_BALANCE:
          val_s32 = gain[2];
          break;
        case OA_CAM_CTRL_GREEN_BALANCE:
          val_s32 = gain[1];
          break;
      }
      valp->int32 = val_s32;
      return OA_ERR_NONE;
      break;
    }

    case OA_CAM_CTRL_TEMPERATURE:
      valp->valueType = OA_CTRL_TYPE_INT32;
      if (( *p_Mallincam_get_Temperature )( cameraInfo->handle, &val_s16 )) {
        fprintf ( stderr, "Mallincam_get_Temperature failed\n" );
        return -OA_ERR_CAMERA_IO;
      }
      valp->int32 = val_s16;
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_BINNING:
      fprintf ( stderr, "%s: Need to code binning control for Mallincam\n",
          __FUNCTION__ );
      return -OA_ERR_INVALID_CONTROL;
      break;

    case OA_CAM_CTRL_COLOUR_MODE:
      fprintf ( stderr, "%s: Need to code colour mode control for Mallincam\n",
          __FUNCTION__ );
      return -OA_ERR_INVALID_CONTROL;
      break;

    case OA_CAM_CTRL_BIT_DEPTH:
      fprintf ( stderr, "%s: Need to code bit depth control for Mallincam\n",
          __FUNCTION__ );
      return -OA_ERR_INVALID_CONTROL;
      break;

    case OA_CAM_CTRL_COOLER:
    case OA_CAM_CTRL_FAN:
      fprintf ( stderr, "%s: unimplemented control\n", __FUNCTION__ );
      return -OA_ERR_INVALID_CONTROL;
      break;
  }

  fprintf ( stderr, "Unrecognised control %d in %s\n", control, __FUNCTION__ );
  return -OA_ERR_INVALID_CONTROL;
}


static int
_processSetResolution ( MALLINCAM_STATE* cameraInfo, OA_COMMAND* command )
{
  FRAMESIZE*			size = command->commandData;
  unsigned int			s, found, restart = 0;

  found = -1;
  for ( s = 0; s < cameraInfo->frameSizes[ cameraInfo->binMode ].numSizes;
      s++ ) {
    if ( cameraInfo->frameSizes[ cameraInfo->binMode ].sizes[ s ].x == size->x
        && cameraInfo->frameSizes[ cameraInfo->binMode ].sizes[ s ].y ==
        size->y ) {
      found = s;
      break;
    }
  }

  if ( found < 0 ) {
    return -OA_ERR_OUT_OF_RANGE;
  }

  if ( cameraInfo->isStreaming ) {
    restart = 1;
    _doStop ( cameraInfo );
  }

  /*
  // Reset the ROI

  if (( *p_Mallincam_put_Roi )( cameraInfo->handle, 0, 0, 0, 0 )) {
    fprintf ( stderr, "Can't clear Mallincam ROI\n" );
    return -OA_ERR_CAMERA_IO;
  }
   */

  if (( *p_Mallincam_put_Size )( cameraInfo->handle, size->x, size->y )) {
    fprintf ( stderr, "Can't set Mallincam frame size %dx%d\n", size->x,
      size->y );
    return -OA_ERR_CAMERA_IO;
  }

  cameraInfo->currentXSize = cameraInfo->currentXResolution = size->x;
  cameraInfo->currentYSize = cameraInfo->currentYResolution = size->y;
  cameraInfo->imageBufferLength = cameraInfo->currentXSize *
      cameraInfo->currentYSize * cameraInfo->currentBytesPerPixel;

  if ( restart ) {
    _doStart ( cameraInfo );
  }

  return OA_ERR_NONE;
}

/*
static int
_processSetROI ( oaCamera* camera, OA_COMMAND* command )
{
  MALLINCAM_STATE*		cameraInfo = camera->_private;
  FRAMESIZE*			size = command->commandData;
  unsigned int			offsetX, offsetY, x, y;

  if ( !camera->features.ROI ) {
    return -OA_ERR_INVALID_CONTROL;
  }

  x = size->x;
  y = size->y;

  if ( x < 16 || x > cameraInfo->currentXResolution || ( x % 2 ) || y < 16 ||
     y > cameraInfo->currentYResolution || ( y % 2 )) {
    return -OA_ERR_OUT_OF_RANGE;
  }

  // ROI position must be even co-ordinate values

  offsetX = (( cameraInfo->currentXResolution - x ) / 2 ) & ~1;
  offsetY = (( cameraInfo->currentYResolution - y ) / 2 ) & ~1;

  if (( *p_Mallincam_put_Roi )( cameraInfo->handle, offsetX, offsetY, x, y )) {
    fprintf ( stderr, "Can't set Mallincam ROI ( %d, %d, %d, %d )\n",
        offsetX, offsetY, x, y );
    return -OA_ERR_CAMERA_IO;
  }

  cameraInfo->currentXSize = x;
  cameraInfo->currentYSize = y;
  cameraInfo->imageBufferLength = cameraInfo->currentXSize *
      cameraInfo->currentYSize * cameraInfo->currentBytesPerPixel;

  return OA_ERR_NONE;
}
*/

static int
_processStreamingStart ( MALLINCAM_STATE* cameraInfo, OA_COMMAND* command )
{
  CALLBACK*		cb = command->commandData;

  if ( cameraInfo->isStreaming ) {
    return -OA_ERR_INVALID_COMMAND;
  }

  cameraInfo->streamingCallback.callback = cb->callback;
  cameraInfo->streamingCallback.callbackArg = cb->callbackArg;

  cameraInfo->imageBufferLength = cameraInfo->currentXSize *
      cameraInfo->currentYSize * cameraInfo->currentBytesPerPixel;

  return _doStart ( cameraInfo );
}


static int
_doStart ( MALLINCAM_STATE* cameraInfo )
{
  int			ret;

  if (( ret = ( *p_Mallincam_StartPushMode )( cameraInfo->handle,
      _MallincamFrameCallback, cameraInfo ))) {
    fprintf ( stderr, "%s: Mallincam_StartPushMode failed: 0x%x\n",
        __FUNCTION__, ret );
    return -OA_ERR_CAMERA_IO;
  }

  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  cameraInfo->isStreaming = 1;
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  return OA_ERR_NONE;
}


static int
_processStreamingStop ( MALLINCAM_STATE* cameraInfo, OA_COMMAND* command )
{
  if ( !cameraInfo->isStreaming ) {
    return -OA_ERR_INVALID_COMMAND;
  }

  return _doStop ( cameraInfo );
}


static int
_doStop ( MALLINCAM_STATE* cameraInfo )
{
  int		ret;

  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  cameraInfo->isStreaming = 0;
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );

  if (( ret = ( *p_Mallincam_Stop )( cameraInfo->handle ))) {
    fprintf ( stderr, "%s: Mallincam_Stop failed: %d\n", __FUNCTION__, ret );
    return -OA_ERR_CAMERA_IO;
  }
  return OA_ERR_NONE;
}


static int
_setBinning ( MALLINCAM_STATE* cameraInfo, int binMode )
{
  int		restart = 0, x, y;

  if ( binMode < 0 || binMode > OA_MAX_BINNING ||
      cameraInfo->frameSizes[ binMode ].numSizes < 1 ) {
    return -OA_ERR_OUT_OF_RANGE;
  }

  /*
  // Reset the ROI

  if (( *p_Mallincam_put_Roi )( cameraInfo->handle, 0, 0, 0, 0 )) {
    fprintf ( stderr, "Can't clear Mallincam ROI\n" );
    return -OA_ERR_CAMERA_IO;
  }
   */

  if ( cameraInfo->isStreaming ) {
    restart = 1;
    _doStop ( cameraInfo );
  }

  x = cameraInfo->frameSizes[ binMode ].sizes[0].x;
  y = cameraInfo->frameSizes[ binMode ].sizes[0].y;
  if (( *p_Mallincam_put_Size )( cameraInfo->handle, x, y )) {
    fprintf ( stderr, "Can't set Mallincam frame size\n" );
    return -OA_ERR_CAMERA_IO;
  }

  cameraInfo->binMode = binMode;
  cameraInfo->currentXSize = cameraInfo->currentXResolution = x;
  cameraInfo->currentYSize = cameraInfo->currentYResolution = y;

  if ( restart ) {
    _doStart ( cameraInfo );
  }

  return OA_ERR_NONE;
}


static int
_setColourMode ( MALLINCAM_STATE* cameraInfo, int mode )
{
  int		restart = 0;

  if ( cameraInfo->isStreaming ) {
    restart = 1;
    _doStop ( cameraInfo );
  }

  if (( *p_Mallincam_put_Option )( cameraInfo->handle,
      TOUPCAM_OPTION_RAW, OA_COLOUR_MODE_RAW == mode ? 1 : 0  )) {
    fprintf ( stderr, "Mallincam_put_Option ( raw, %d ) failed\n", mode );
    return -OA_ERR_CAMERA_IO;
  }

  if ( OA_COLOUR_MODE_RAW == mode ) {
    if ( cameraInfo->currentVideoFormat == OA_PIX_FMT_RGB24 ) {
      cameraInfo->currentVideoFormat = cameraInfo->cfaPattern;
      cameraInfo->currentBitsPerPixel = 8;
    } else {
fprintf ( stderr, "don't know how to handle raw for current video mode\n" );
    }
  } else {
    if ( cameraInfo->currentVideoFormat == cameraInfo->cfaPattern ) {
      cameraInfo->currentVideoFormat = OA_PIX_FMT_RGB24;
      cameraInfo->currentBitsPerPixel = 24;
    } else {
fprintf ( stderr, "don't know how to handle nonraw for current video mode\n" );
    }
  }

  if ( restart ) {
    _doStart ( cameraInfo );
  }

  return OA_ERR_NONE;
}


static int
_setBitDepth ( MALLINCAM_STATE* cameraInfo, int depth )
{
  if  ( depth != 8 && depth != 16 ) {
    return -OA_ERR_OUT_OF_RANGE;
  }

  if ( 8 == depth && ( OA_PIX_FMT_RGB24 == cameraInfo->currentVideoFormat ||
      OA_ISBAYER8 ( cameraInfo->currentVideoFormat ) ||
      OA_PIX_FMT_GREY8 == cameraInfo->currentVideoFormat )) {
    return OA_ERR_NONE;
  }

  // I'm assuming on the basis of no information whatsoever that the format
  // will be little-endian here

  if ( 16 == depth && ( OA_PIX_FMT_RGB48LE == cameraInfo->currentVideoFormat ||
      OA_ISBAYER16 ( cameraInfo->currentVideoFormat ) ||
      OA_PIX_FMT_GREY16LE == cameraInfo->currentVideoFormat )) {
    return OA_ERR_NONE;
  }

  if (( *p_Mallincam_put_Option )( cameraInfo->handle, TOUPCAM_OPTION_BITDEPTH,
      16 == depth ? 1 : 0  )) {
    fprintf ( stderr, "Mallincam_put_Option ( depth, %d ) failed\n",
        16 == depth ? 1 : 0 );
    return -OA_ERR_CAMERA_IO;
  }

  if ( 8 == depth ) {
    switch ( cameraInfo->currentVideoFormat ) {
      case OA_PIX_FMT_BGGR16LE:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_BGGR8;
        cameraInfo->currentBytesPerPixel = 1;
        cameraInfo->currentBitsPerPixel = 8;
        break;
      case OA_PIX_FMT_RGGB16LE:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_RGGB8;
        cameraInfo->currentBytesPerPixel = 1;
        cameraInfo->currentBitsPerPixel = 8;
        break;
      case OA_PIX_FMT_GBRG16LE:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_GBRG8;
        cameraInfo->currentBytesPerPixel = 1;
        cameraInfo->currentBitsPerPixel = 8;
        break;
      case OA_PIX_FMT_GRBG16LE:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_GRBG8;
        cameraInfo->currentBytesPerPixel = 1;
        cameraInfo->currentBitsPerPixel = 8;
        break;
      case OA_PIX_FMT_GREY16LE:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_GREY8;
        cameraInfo->currentBytesPerPixel = 1;
        cameraInfo->currentBitsPerPixel = 8;
        break;
      case OA_PIX_FMT_RGB48LE:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_RGB24;
        cameraInfo->currentBytesPerPixel = 3;
        cameraInfo->currentBitsPerPixel = 24;
        break;
    }
  } else {
    switch ( cameraInfo->currentVideoFormat ) {
      case OA_PIX_FMT_BGGR8:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_BGGR16LE;
        cameraInfo->currentBytesPerPixel = 2;
        cameraInfo->currentBitsPerPixel = cameraInfo->maxBitDepth;
        break;
      case OA_PIX_FMT_RGGB8:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_RGGB16LE;
        cameraInfo->currentBytesPerPixel = 2;
        cameraInfo->currentBitsPerPixel = cameraInfo->maxBitDepth;
        break;
      case OA_PIX_FMT_GBRG8:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_GBRG16LE;
        cameraInfo->currentBytesPerPixel = 2;
        cameraInfo->currentBitsPerPixel = cameraInfo->maxBitDepth;
        break;
      case OA_PIX_FMT_GRBG8:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_GRBG16LE;
        cameraInfo->currentBytesPerPixel = 2;
        cameraInfo->currentBitsPerPixel = cameraInfo->maxBitDepth;
        break;
      case OA_PIX_FMT_GREY8:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_GREY16LE;
        cameraInfo->currentBytesPerPixel = 2;
        cameraInfo->currentBitsPerPixel = cameraInfo->maxBitDepth;
        break;
      case OA_PIX_FMT_RGB24:
        cameraInfo->currentVideoFormat = OA_PIX_FMT_RGB48LE;
        cameraInfo->currentBytesPerPixel = 6;
        cameraInfo->currentBitsPerPixel = 48;
        break;
    }
  }

  cameraInfo->imageBufferLength = cameraInfo->currentXSize *
      cameraInfo->currentYSize * cameraInfo->currentBytesPerPixel;

  return OA_ERR_NONE;
}
