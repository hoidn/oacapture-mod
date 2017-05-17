/*****************************************************************************
 *
 * PGEcontrol.c -- control functions for Point Grey Gig-E cameras
 *
 * Copyright 2015,2016 James Fidell (james@openastroproject.org)
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
#include <openastro/camera.h>

#include "oacamprivate.h"
#include "PGEoacam.h"
#include "PGEstate.h"

int
oaPGECameraSetControl ( oaCamera* camera, int control, oaControlValue* val )
{
  OA_COMMAND	command;
  PGE_STATE*	cameraInfo = camera->_private;
  int		retval;

  // Could do more validation here, but it's a bit messy to do here
  // and in the controller too.

  OA_CLEAR ( command );
  command.commandType = OA_CMD_CONTROL_SET;
  command.controlId = control;
  command.commandData = val;

  cameraInfo = camera->_private;
  oaDLListAddToTail ( cameraInfo->commandQueue, &command );
  pthread_cond_broadcast ( &cameraInfo->commandQueued );
  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &cameraInfo->commandComplete,
        &cameraInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


int
oaPGECameraReadControl ( oaCamera* camera, int control, oaControlValue* val )
{
  OA_COMMAND    command;
  PGE_STATE*   cameraInfo = camera->_private;
  int           retval;

  // Could do more validation here, but it's a bit messy to do here
  // and in the controller too.

  OA_CLEAR ( command );
  command.commandType = OA_CMD_CONTROL_GET;
  command.controlId = control;
  command.resultData = val;

  cameraInfo = camera->_private;
  oaDLListAddToTail ( cameraInfo->commandQueue, &command );
  pthread_cond_broadcast ( &cameraInfo->commandQueued );
  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &cameraInfo->commandComplete,
        &cameraInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


int
oaPGECameraTestControl ( oaCamera* camera, int control, oaControlValue* val )
{
  uint32_t	val_u32;
  int64_t	val_s64;
  COMMON_INFO*	commonInfo = camera->_common;

  if ( !camera->controls [ control ] ) {
    return -OA_ERR_INVALID_CONTROL;
  }

  if ( camera->controls [ control ] != val->valueType ) {
    return -OA_ERR_INVALID_CONTROL_TYPE;
  }

  switch ( control ) {

    case OA_CAM_CTRL_BRIGHTNESS:
    case OA_CAM_CTRL_CONTRAST:
    case OA_CAM_CTRL_SATURATION:
    case OA_CAM_CTRL_HUE:
    case OA_CAM_CTRL_SHARPNESS:
    case OA_CAM_CTRL_GAMMA:
    case OA_CAM_CTRL_WHITE_BALANCE_TEMP:
    case OA_CAM_CTRL_GAIN:
      // This should be unsigned 32-bit
      val_s64 = val->int64;
      if ( val_s64 < 0 ) {
        return -OA_ERR_OUT_OF_RANGE;
      }
      val_u32 = val_s64 & 0xffffffff;
      if ( val_u32 >= commonInfo->min[ control ] &&
          val_u32 <= commonInfo->max[ control ] &&
          ( 0 == ( val_u32 - commonInfo->min[ control ] ) %
          commonInfo->step[ control ] )) {
        return OA_ERR_NONE;
      }
      break;

    case OA_CAM_CTRL_EXPOSURE_ABSOLUTE:
      val_s64 = val->int64;
      if ( val_s64 <= 0 ) {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;

    case OA_CAM_CTRL_AUTO_WHITE_BALANCE:
    case OA_CAM_CTRL_AUTO_WHITE_BALANCE_TEMP:
    case OA_CAM_CTRL_HUE_AUTO:
      // These just need to be boolean and we've already checked that
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_AUTO_EXPOSURE:
      if ( val->int32 != OA_EXPOSURE_AUTO && val->int32 !=
          OA_EXPOSURE_MANUAL ) {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;     

    case OA_CAM_CTRL_BIT_DEPTH:
      if ( val->valueType != OA_CTRL_TYPE_DISCRETE ) {
        fprintf ( stderr, "%s: invalid control type %d where discrete "
            "expected\n", __FUNCTION__, val->valueType );
        return -OA_ERR_INVALID_CONTROL_TYPE;
      }
      // FIX ME -- this test should be better
      if ( 16 != val->discrete && 12 != val->discrete && 8 != val->discrete ) {
        return -OA_ERR_OUT_OF_RANGE;
      }
      return OA_ERR_NONE;
      break;

    case OA_CAM_CTRL_BINNING:
      return -OA_ERR_INVALID_CONTROL;
      break;

    default:
      // If we reach here it's because we don't recognise the control
      fprintf ( stderr, "Unrecognised control %d in %s\n", control,
          __FUNCTION__ );
      return -OA_ERR_INVALID_CONTROL;
      break;
  }

  // And if we reach here it's because the value wasn't valid
  return -OA_ERR_OUT_OF_RANGE;
}


int
oaPGECameraSetFrameInterval ( oaCamera* camera, int numerator,
    int denominator )
{
  FRAMERATE	r;
  OA_COMMAND	command;
  PGE_STATE*	cameraInfo = camera->_private;
  int		retval;

fprintf ( stderr, "implement %s\n", __FUNCTION__ );
  OA_CLEAR ( command );
  command.commandType = OA_CMD_FRAME_INTERVAL_SET;
  r.numerator = numerator;
  r.denominator = denominator;
  command.commandData = &r;
  cameraInfo = camera->_private;
  oaDLListAddToTail ( cameraInfo->commandQueue, &command );
  pthread_cond_broadcast ( &cameraInfo->commandQueued );
  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &cameraInfo->commandComplete,
        &cameraInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


int
oaPGECameraSetResolution ( oaCamera* camera, int x, int y )
{
  FRAMESIZE	s;
  OA_COMMAND	command;
  PGE_STATE*	cameraInfo = camera->_private;
  int		retval;

  OA_CLEAR ( command );
  command.commandType = OA_CMD_RESOLUTION_SET;
  s.x = x;
  s.y = y;
  command.commandData = &s;
  cameraInfo = camera->_private;
  oaDLListAddToTail ( cameraInfo->commandQueue, &command );
  pthread_cond_broadcast ( &cameraInfo->commandQueued );
  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &cameraInfo->commandComplete,
        &cameraInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


int
oaPGECameraSetROI ( oaCamera* camera, int x, int y )
{
  FRAMESIZE	s;
  OA_COMMAND	command;
  PGE_STATE*	cameraInfo = camera->_private;
  int		retval;

  OA_CLEAR ( command );
  command.commandType = OA_CMD_ROI_SET;
  s.x = x;
  s.y = y;
  command.commandData = &s;
  cameraInfo = camera->_private;
  oaDLListAddToTail ( cameraInfo->commandQueue, &command );
  pthread_cond_broadcast ( &cameraInfo->commandQueued );
  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &cameraInfo->commandComplete,
        &cameraInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


int
oaPGECameraStartStreaming ( oaCamera* camera,
    void* (*callback)(void*, void*, int), void* callbackArg )
{
  OA_COMMAND    command;
  CALLBACK      callbackData;
  int           retval;
  PGE_STATE*  cameraInfo = camera->_private;

  oacamDebugMsg ( DEBUG_CAM_CTRL, "PGE: control: %s ( %p )\n",
      __FUNCTION__, callback );

  OA_CLEAR ( command );
  callbackData.callback = callback;
  callbackData.callbackArg = callbackArg;
  command.commandType = OA_CMD_START;
  command.commandData = ( void* ) &callbackData;

  oaDLListAddToTail ( cameraInfo->commandQueue, &command );
  pthread_cond_broadcast ( &cameraInfo->commandQueued );
  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &cameraInfo->commandComplete,
        &cameraInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


int
oaPGECameraIsStreaming ( oaCamera* camera )
{
  PGE_STATE*  cameraInfo = camera->_private;

  return ( cameraInfo->isStreaming );
}


int
oaPGECameraStopStreaming ( oaCamera* camera )
{
  OA_COMMAND    command;
  int           retval;
  PGE_STATE*   cameraInfo = camera->_private;

  oacamDebugMsg ( DEBUG_CAM_CTRL, "PGE: control: %s()\n", __FUNCTION__ );

  OA_CLEAR ( command );
  command.commandType = OA_CMD_STOP;

  oaDLListAddToTail ( cameraInfo->commandQueue, &command );
  pthread_cond_broadcast ( &cameraInfo->commandQueued );
  pthread_mutex_lock ( &cameraInfo->commandQueueMutex );
  while ( !command.completed ) {
    pthread_cond_wait ( &cameraInfo->commandComplete,
        &cameraInfo->commandQueueMutex );
  }
  pthread_mutex_unlock ( &cameraInfo->commandQueueMutex );
  retval = command.resultCode;

  return retval;
}


const char*
oaPGECameraGetMenuString ( oaCamera* camera, int control, int index )
{
  if ( OA_CAM_CTRL_TRIGGER_POLARITY == control ||
      OA_CAM_CTRL_STROBE_POLARITY == control ) {

    switch ( index ) {
      case 0:
        return "Active on trailing edge";
        break;
      case 1:
        return "Active on leading edge";
        break;
    }
    return "Invalid index";

  }

  if ( OA_CAM_CTRL_TRIGGER_MODE == control ) {
    switch ( index ) {
      case 0:
        return "External Trigger";
        break;
      case 1:
        return "Bulb Shutter Trigger";
        break;
      case 2:
        return "Pulse Count Trigger";
        break;
      case 3:
        return "Skip Frames Trigger";
        break;
      case 4:
        return "Multiple Preset Trigger";
        break;
      case 5:
        return "Multiple Pulse Width Trigger";
        break;
      case 13:
        return "Low Smear Trigger";
        break;
      case 14:
        return "Overlapped Exposure Readout Trigger";
        break;
      case 15:
        return "Multi-Shot Trigger";
        break;
    }
    return "Invalid index";
  }

  fprintf ( stderr, "%s: control not implemented\n", __FUNCTION__ );
  return "";
}

