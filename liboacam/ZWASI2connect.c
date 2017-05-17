/*****************************************************************************
 *
 * ZWASI2connect.c -- Initialise ZW ASI cameras APIv2
 *
 * Copyright 2015 James Fidell (james@openastroproject.org)
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
#include <openastro/util.h>
#include <ASICamera2.h>

#include "oacamprivate.h"
#include "unimplemented.h"
#include "ZWASI.h"
#include "ZWASIoacam.h"
#include "ZWASI2oacam.h"
#include "ZWASIstate.h"


static void _ZWASIInitFunctionPointers ( oaCamera* );

/**
 * Initialise a given camera device
 */

oaCamera*
oaZWASI2InitCamera ( oaCameraDevice* device )
{
  oaCamera*		camera;
  DEVICE_INFO*		devInfo;
  ZWASI_STATE*		cameraInfo;
  COMMON_INFO*		commonInfo;
  ASI_CAMERA_INFO	camInfo;
  ASI_CONTROL_CAPS	controlCaps;
  int          		c, f, i, j, bin, multiplier, numControls;
  long			currentValue;
  ASI_BOOL		autoSetting;

  oacamDebugMsg ( DEBUG_CAM_INIT, "ZWASI: init: %s ()\n", __FUNCTION__ );

  if (!( camera = ( oaCamera* ) malloc ( sizeof ( oaCamera )))) {
    perror ( "malloc oaCamera failed" );
    return 0;
  }
  if (!( cameraInfo = ( ZWASI_STATE* ) malloc ( sizeof ( ZWASI_STATE )))) {
    free (( void* ) camera );
    perror ( "malloc ZWASI_STATE failed" );
    return 0;
  }
  if (!( commonInfo = ( COMMON_INFO* ) malloc ( sizeof ( COMMON_INFO )))) {
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    perror ( "malloc COMMON_INFO failed" );
    return 0;
  }
  OA_CLEAR ( *commonInfo );
  OA_CLEAR ( *cameraInfo );
  camera->_private = cameraInfo;
  camera->_common = commonInfo;

  ( void ) strcpy ( camera->deviceName, device->deviceName );
  cameraInfo->initialised = 0;
  cameraInfo->index = -1;
  devInfo = device->_private;

  camera->interface = device->interface;
  cameraInfo->index = devInfo->devIndex;
  cameraInfo->cameraType = devInfo->devType;

  ASIGetCameraProperty ( &camInfo, cameraInfo->index );
  cameraInfo->cameraId = camInfo.CameraID;

  OA_CLEAR ( camera->controls );
  OA_CLEAR ( camera->features );
  
  if ( ASIOpenCamera ( cameraInfo->cameraId )) {
    fprintf ( stderr, "open of camera %ld failed\n", cameraInfo->cameraId );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  _oaInitCameraFunctionPointers ( camera );
  _ZWASIInitFunctionPointers ( camera );

  pthread_mutex_init ( &cameraInfo->commandQueueMutex, 0 );
  pthread_mutex_init ( &cameraInfo->callbackQueueMutex, 0 );
  pthread_cond_init ( &cameraInfo->callbackQueued, 0 );
  pthread_cond_init ( &cameraInfo->commandQueued, 0 );
  pthread_cond_init ( &cameraInfo->commandComplete, 0 );
  cameraInfo->isStreaming = 0;

  if ( ASIGetNumOfControls ( cameraInfo->cameraId, &numControls )) {
    fprintf ( stderr, "%s: ASIGetNumOfControls returns error\n",
      __FUNCTION__ );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  for ( c = 0; c < numControls; c++ ) {
    if ( !ASIGetControlCaps ( cameraInfo->cameraId, c, &controlCaps )) {

      switch ( controlCaps.ControlType ) {

        case ASI_GAIN:
          camera->controls[ OA_CAM_CTRL_GAIN ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_GAIN ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_GAIN ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_GAIN ] = 1;
          commonInfo->def[ OA_CAM_CTRL_GAIN ] = controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentGain = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_GAIN ] = OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_GAIN ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_GAIN ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_GAIN ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_GAIN ] = cameraInfo->autoGain =
                autoSetting;
          }
          break;

        case ASI_EXPOSURE:
          camera->controls[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] = 1;
          commonInfo->def[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentAbsoluteExposure = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_EXPOSURE ] =
                OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_EXPOSURE ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_EXPOSURE ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_EXPOSURE ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_EXPOSURE ] =
                cameraInfo->autoExposure = autoSetting;
          }
          break;

        case ASI_GAMMA:
          camera->controls[ OA_CAM_CTRL_GAMMA ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_GAMMA ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_GAMMA ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_GAMMA ] = 1;
          commonInfo->def[ OA_CAM_CTRL_GAMMA ] = controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentGamma = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_GAMMA ] = OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_GAMMA ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_GAMMA ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_GAMMA ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_GAMMA ] = cameraInfo->autoGamma =
                autoSetting;
          }
          break;

        case ASI_WB_R:
          camera->controls[ OA_CAM_CTRL_RED_BALANCE ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_RED_BALANCE ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_RED_BALANCE ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_RED_BALANCE ] = 1;
          commonInfo->def[ OA_CAM_CTRL_RED_BALANCE ] =
              controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentRedBalance = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_RED_BALANCE ] =
                OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_RED_BALANCE ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_RED_BALANCE ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_RED_BALANCE ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_RED_BALANCE ] =
                cameraInfo->autoRedBalance = autoSetting;
          }
          break;

        case ASI_WB_B:
          camera->controls[ OA_CAM_CTRL_BLUE_BALANCE ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_BLUE_BALANCE ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_BLUE_BALANCE ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_BLUE_BALANCE ] = 1;
          commonInfo->def[ OA_CAM_CTRL_BLUE_BALANCE ] =
              controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentBlueBalance = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_BLUE_BALANCE ] =
                OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_BLUE_BALANCE ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_BLUE_BALANCE ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_BLUE_BALANCE ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_BLUE_BALANCE ] =
                cameraInfo->autoBlueBalance = autoSetting;
          }
          break;

        case ASI_BRIGHTNESS:
          camera->controls[ OA_CAM_CTRL_BRIGHTNESS ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_BRIGHTNESS ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_BRIGHTNESS ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_BRIGHTNESS ] = 1;
          commonInfo->def[ OA_CAM_CTRL_BRIGHTNESS ] = controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentBrightness = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_BRIGHTNESS ] =
                OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_BRIGHTNESS ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_BRIGHTNESS ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_BRIGHTNESS ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_BRIGHTNESS ] =
                cameraInfo->autoBrightness = autoSetting;
          }
          break;

        case ASI_BANDWIDTHOVERLOAD:
          camera->controls[ OA_CAM_CTRL_USBTRAFFIC ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_USBTRAFFIC ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_USBTRAFFIC ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_USBTRAFFIC ] = 1;
          commonInfo->def[ OA_CAM_CTRL_USBTRAFFIC ] = controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentUSBTraffic = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_USBTRAFFIC ] =
                OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_USBTRAFFIC ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_USBTRAFFIC ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_USBTRAFFIC ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_USBTRAFFIC ] =
                cameraInfo->autoUSBTraffic = autoSetting;
          }
          break;

        case ASI_OVERCLOCK:
          camera->controls[ OA_CAM_CTRL_OVERCLOCK ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_OVERCLOCK ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_OVERCLOCK ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_OVERCLOCK ] = 1;
          commonInfo->def[ OA_CAM_CTRL_OVERCLOCK ] = controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentOverclock = currentValue;
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_OVERCLOCK ] =
                OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_OVERCLOCK ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_OVERCLOCK ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_OVERCLOCK ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_OVERCLOCK ] =
                cameraInfo->autoOverclock = autoSetting;
          }
          break;

        case ASI_HIGH_SPEED_MODE:
          camera->controls[ OA_CAM_CTRL_HIGHSPEED ] = OA_CTRL_TYPE_BOOLEAN;
          commonInfo->min[ OA_CAM_CTRL_HIGHSPEED ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_HIGHSPEED ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_HIGHSPEED ] = 1;
          commonInfo->def[ OA_CAM_CTRL_HIGHSPEED ] = controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentHighSpeed = currentValue;
          /*
          if ( controlCaps.IsAutoSupported ) {
            camera->controls[ OA_CAM_CTRL_AUTO_HIGHSPEED ] =
                OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_AUTO_HIGHSPEED ] = 0;
            commonInfo->max[ OA_CAM_CTRL_AUTO_HIGHSPEED ] = 1;
            commonInfo->step[ OA_CAM_CTRL_AUTO_HIGHSPEED ] = 1;
            commonInfo->def[ OA_CAM_CTRL_AUTO_HIGHSPEED ] =
                cameraInfo->autoHighSpeed = autoSetting;
          }
          */
          cameraInfo->autoHighSpeed = 0;
          break;

        case ASI_FLIP:
          if ( controlCaps.MaxValue >= ASI_FLIP_HORIZ ) {
            camera->controls[ OA_CAM_CTRL_HFLIP ] = OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_HFLIP ] = 0;
            commonInfo->max[ OA_CAM_CTRL_HFLIP ] = 1;
            commonInfo->step[ OA_CAM_CTRL_HFLIP ] = 1;
            commonInfo->def[ OA_CAM_CTRL_HFLIP ] = cameraInfo->currentHFlip = 0;
          }
          if ( controlCaps.MaxValue >= ASI_FLIP_VERT ) {
            camera->controls[ OA_CAM_CTRL_VFLIP ] = OA_CTRL_TYPE_BOOLEAN;
            commonInfo->min[ OA_CAM_CTRL_VFLIP ] = 0;
            commonInfo->max[ OA_CAM_CTRL_VFLIP ] = 1;
            commonInfo->step[ OA_CAM_CTRL_VFLIP ] = 1;
            commonInfo->def[ OA_CAM_CTRL_VFLIP ] = cameraInfo->currentVFlip = 0;
          }
          break;

        case ASI_COOLER_ON:
          camera->controls[ OA_CAM_CTRL_COOLER ] = OA_CTRL_TYPE_BOOLEAN;
          commonInfo->min[ OA_CAM_CTRL_COOLER ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_COOLER ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_COOLER ] = 1;
          commonInfo->def[ OA_CAM_CTRL_COOLER ] = controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->coolerEnabled = currentValue;
          break;


        case ASI_TARGET_TEMP:
          camera->controls[ OA_CAM_CTRL_TEMP_SETPOINT ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_TEMP_SETPOINT ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_TEMP_SETPOINT ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_TEMP_SETPOINT ] = 1;
          commonInfo->def[ OA_CAM_CTRL_TEMP_SETPOINT ] =
              controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentSetPoint = currentValue;
          break;

        case ASI_COOLER_POWER_PERC:
          // Ignore this one -- it's read-only anyhow
/*
          camera->controls[ OA_CAM_CTRL_COOLER_POWER ] = OA_CTRL_TYPE_INT32;
          commonInfo->min[ OA_CAM_CTRL_COOLER_POWER ] = controlCaps.MinValue;
          commonInfo->max[ OA_CAM_CTRL_COOLER_POWER ] = controlCaps.MaxValue;
          commonInfo->step[ OA_CAM_CTRL_COOLER_POWER ] = 1;
          commonInfo->def[ OA_CAM_CTRL_COOLER_POWER ] =
              controlCaps.DefaultValue;
          ASIGetControlValue ( cameraInfo->cameraId, c, &currentValue,
            &autoSetting );
          cameraInfo->currentCoolerPower = currentValue;
*/
          break;

        case ASI_AUTO_MAX_GAIN:
        case ASI_AUTO_MAX_EXP:
        case ASI_AUTO_MAX_BRIGHTNESS:
        case ASI_HARDWARE_BIN:
          fprintf ( stderr, "%s: control %s is not supported\n", __FUNCTION__,
              controlCaps.Name );
          break;

        case ASI_TEMPERATURE:
          break; // handled elsewhere

        default:
          fprintf ( stderr, "%s: Unrecognised control '%s'\n", __FUNCTION__,
              controlCaps.Name );
          break;
      }
    }
  }

  cameraInfo->maxResolutionX = camInfo.MaxWidth;
  cameraInfo->maxResolutionY = camInfo.MaxHeight;

  i = 0;
  while (( bin = camInfo.SupportedBins[i] )) {
    if ( 2 == bin || 3 ==bin || 4 == bin ) {
      camera->controls[ OA_CAM_CTRL_BINNING ] = OA_CTRL_TYPE_DISCRETE;
    }
    i++;
  }
  camera->controls[ OA_CAM_CTRL_DROPPED ] = OA_CTRL_TYPE_READONLY;

  camera->controls[ OA_CAM_CTRL_TEMPERATURE ] = OA_CTRL_TYPE_READONLY;

  // All cameras support ROI according to Sam@ZWO
  camera->features.ROI = 1;
  camera->features.hasReset = 1;

  // Ok, now we need to find out what frame formats are supported and
  // which one we want to use

  cameraInfo->videoRGB24 = cameraInfo->videoGrey16 = 0;
  cameraInfo->videoGrey = 0;
  cameraInfo->videoCurrent = -1;
  // The mono ASI120MM will do RGB24 as a greyscale RGB image if we ask it
  // to, but that's rather wasteful, so we only support this for colour
  // cameras
  if ( camInfo.IsColorCam ) {
    int have16Bit = 0;
    camera->controls[ OA_CAM_CTRL_COLOUR_MODE ] = OA_CTRL_TYPE_DISCRETE;
    cameraInfo->colour = 1;
    i = 0;
    while (( f = camInfo.SupportedVideoFormat[ i ]) != ASI_IMG_END ) {
      if ( ASI_IMG_RGB24 == f ) {
        cameraInfo->videoCurrent = ASI_IMG_RGB24;
        cameraInfo->videoRGB24 = 1;
        camera->features.demosaicMode = 1;
      }
      if ( ASI_IMG_RAW8 == f ) {
        camera->features.rawMode = 1;
      }
      if ( ASI_IMG_RAW16 == f ) {
        have16Bit = 1;
      }
      i++;
    }
    if (( cameraInfo->videoRGB24 || camera->features.rawMode ) && have16Bit ) {
      camera->controls[ OA_CAM_CTRL_BIT_DEPTH ] = OA_CTRL_TYPE_DISCRETE;
    }
  } else {
    cameraInfo->colour = 0;
    i = 0;
    while (( f = camInfo.SupportedVideoFormat[ i ]) != ASI_IMG_END ) {
      if ( ASI_IMG_RAW8 == f ) {
        cameraInfo->videoCurrent = ASI_IMG_RAW8;
        cameraInfo->videoGrey = 1;
      }
      if ( ASI_IMG_RAW16 == f ) {
        if ( cameraInfo->videoCurrent < 0 ) {
          cameraInfo->videoCurrent = ASI_IMG_RAW16;
        }
        cameraInfo->videoGrey16 = 1;
      }
      if ( ASI_IMG_Y8 == f ) {
        if ( cameraInfo->videoCurrent < 0 ) {
          cameraInfo->videoCurrent = ASI_IMG_Y8;
        }
        cameraInfo->videoGrey = 1;
      }
      i++;
    }
    if ( cameraInfo->videoGrey16 && cameraInfo->videoGrey ) {
      camera->controls[ OA_CAM_CTRL_BIT_DEPTH ] = OA_CTRL_TYPE_DISCRETE;
    }
  }

  if ( -1 == cameraInfo->videoCurrent ) {
    fprintf ( stderr, "No suitable video format found on camera %d\n",
        cameraInfo->index );
    free (( void* ) camera->_common );
    free (( void* ) camera->_private );
    free (( void* ) camera );
    return 0;
  }

  // This sets up a finite state machine to handle switching between 8-bit
  // RGB, 8-bit raw and 16-bit raw nicely.  See the controller code for
  // more details
  if ( cameraInfo->colour ) {
    switch ( cameraInfo->videoCurrent ) {
      case ASI_IMG_RAW16:
        cameraInfo->FSMState = 1;
        cameraInfo->currentBitDepth = 16;
        break;
      case ASI_IMG_RAW8:
        cameraInfo->FSMState = 3;
        cameraInfo->currentBitDepth = 8;
        break;
      case ASI_IMG_RGB24:
      default:
        cameraInfo->currentBitDepth = 8;
        cameraInfo->FSMState = 0;
    }
  }
  cameraInfo->binMode = OA_BIN_MODE_NONE;

  for ( i = 1; i <= 4; i++ ) {
    cameraInfo->frameSizes[i].numSizes = 0;
    cameraInfo->frameSizes[i].sizes = 0;
  }

  switch ( cameraInfo->cameraType ) {

    case ZWOCAM_ASI130MM:
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          10, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[4].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) cameraInfo->frameSizes[2].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 1280;
      cameraInfo->frameSizes[1].sizes[0].y = 1024;
      cameraInfo->frameSizes[1].sizes[1].x = 1280;
      cameraInfo->frameSizes[1].sizes[1].y = 600;
      cameraInfo->frameSizes[1].sizes[2].x = 1280;
      cameraInfo->frameSizes[1].sizes[2].y = 400;
      cameraInfo->frameSizes[1].sizes[3].x = 800;
      cameraInfo->frameSizes[1].sizes[3].y = 600;
      cameraInfo->frameSizes[1].sizes[4].x = 800;
      cameraInfo->frameSizes[1].sizes[4].y = 400;
      cameraInfo->frameSizes[1].sizes[5].x = 640;
      cameraInfo->frameSizes[1].sizes[5].y = 480;
      cameraInfo->frameSizes[1].sizes[6].x = 600;
      cameraInfo->frameSizes[1].sizes[6].y = 400;
      cameraInfo->frameSizes[1].sizes[7].x = 400;
      cameraInfo->frameSizes[1].sizes[7].y = 400;
      cameraInfo->frameSizes[1].sizes[8].x = 480;
      cameraInfo->frameSizes[1].sizes[8].y = 320;
      cameraInfo->frameSizes[1].sizes[9].x = 320;
      cameraInfo->frameSizes[1].sizes[9].y = 240;
      cameraInfo->frameSizes[1].numSizes = 10;

      cameraInfo->frameSizes[2].sizes[0].x = 640;
      cameraInfo->frameSizes[2].sizes[0].y = 512;
      cameraInfo->frameSizes[2].numSizes = 1;

      cameraInfo->frameSizes[4].sizes[0].x = 320;
      cameraInfo->frameSizes[4].sizes[0].y = 256;
      cameraInfo->frameSizes[4].numSizes = 1;

      camera->features.pixelSizeX = 5200;
      camera->features.pixelSizeY = 5200;

      break;

    case ZWOCAM_ASI120MM_S:
    case ZWOCAM_ASI120MC_S:
      cameraInfo->usb3Cam = 1;
      /* fallthrough */

    case ZWOCAM_ASI120MM:
    case ZWOCAM_ASI120MC:
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          18, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 1280;
      cameraInfo->frameSizes[1].sizes[0].y = 960;
      cameraInfo->frameSizes[1].sizes[1].x = 1280;
      cameraInfo->frameSizes[1].sizes[1].y = 720;
      cameraInfo->frameSizes[1].sizes[2].x = 1280;
      cameraInfo->frameSizes[1].sizes[2].y = 600;
      cameraInfo->frameSizes[1].sizes[3].x = 1280;
      cameraInfo->frameSizes[1].sizes[3].y = 400;
      cameraInfo->frameSizes[1].sizes[4].x = 960;
      cameraInfo->frameSizes[1].sizes[4].y = 960;
      cameraInfo->frameSizes[1].sizes[5].x = 1024;
      cameraInfo->frameSizes[1].sizes[5].y = 768;
      cameraInfo->frameSizes[1].sizes[6].x = 1024;
      cameraInfo->frameSizes[1].sizes[6].y = 600;
      cameraInfo->frameSizes[1].sizes[7].x = 1024;
      cameraInfo->frameSizes[1].sizes[7].y = 400;
      cameraInfo->frameSizes[1].sizes[8].x = 800;
      cameraInfo->frameSizes[1].sizes[8].y = 800;
      cameraInfo->frameSizes[1].sizes[9].x = 800;
      cameraInfo->frameSizes[1].sizes[9].y = 640;
      cameraInfo->frameSizes[1].sizes[10].x = 800;
      cameraInfo->frameSizes[1].sizes[10].y = 512;
      cameraInfo->frameSizes[1].sizes[11].x = 800;
      cameraInfo->frameSizes[1].sizes[11].y = 320;
      cameraInfo->frameSizes[1].sizes[12].x = 640;
      cameraInfo->frameSizes[1].sizes[12].y = 560;
      cameraInfo->frameSizes[1].sizes[13].x = 640;
      cameraInfo->frameSizes[1].sizes[13].y = 480;
      cameraInfo->frameSizes[1].sizes[14].x = 512;
      cameraInfo->frameSizes[1].sizes[14].y = 440;
      cameraInfo->frameSizes[1].sizes[15].x = 512;
      cameraInfo->frameSizes[1].sizes[15].y = 400;
      cameraInfo->frameSizes[1].sizes[16].x = 480;
      cameraInfo->frameSizes[1].sizes[16].y = 320;
      cameraInfo->frameSizes[1].sizes[17].x = 320;
      cameraInfo->frameSizes[1].sizes[17].y = 240;
      cameraInfo->frameSizes[1].numSizes = 18;

      cameraInfo->frameSizes[2].sizes[0].x = 640;
      cameraInfo->frameSizes[2].sizes[0].y = 480;
      cameraInfo->frameSizes[2].numSizes = 1;

      camera->features.pixelSizeX = 3750;
      camera->features.pixelSizeY = 3750;

      break;

    case ZWOCAM_ASI035MM:
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[2].sizes[0].x = 376;
      cameraInfo->frameSizes[2].sizes[0].y = 240;
      cameraInfo->frameSizes[2].numSizes = 1;

      // fallthrough

    case ZWOCAM_ASI035MC:
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          5, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[2].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }

      cameraInfo->frameSizes[1].sizes[0].x = 752;
      cameraInfo->frameSizes[1].sizes[0].y = 480;
      cameraInfo->frameSizes[1].sizes[1].x = 640;
      cameraInfo->frameSizes[1].sizes[1].y = 480;
      cameraInfo->frameSizes[1].sizes[2].x = 600;
      cameraInfo->frameSizes[1].sizes[2].y = 400;
      cameraInfo->frameSizes[1].sizes[3].x = 400;
      cameraInfo->frameSizes[1].sizes[3].y = 400;
      cameraInfo->frameSizes[1].sizes[4].x = 320;
      cameraInfo->frameSizes[1].sizes[4].y = 240;
      cameraInfo->frameSizes[1].numSizes = 5;

      camera->features.pixelSizeX = 6000;
      camera->features.pixelSizeY = 6000;

      break;

    case ZWOCAM_ASI030MC:
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          3, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 640;
      cameraInfo->frameSizes[1].sizes[0].y = 480;
      cameraInfo->frameSizes[1].sizes[1].x = 480;
      cameraInfo->frameSizes[1].sizes[1].y = 320;
      cameraInfo->frameSizes[1].sizes[2].x = 320;
      cameraInfo->frameSizes[1].sizes[2].y = 240;
      cameraInfo->frameSizes[1].numSizes = 3;

      camera->features.pixelSizeX = 6000;
      camera->features.pixelSizeY = 6000;

      break;

    case ZWOCAM_ASI034MC:
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          4, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 728;
      cameraInfo->frameSizes[1].sizes[0].y = 512;
      cameraInfo->frameSizes[1].sizes[1].x = 640;
      cameraInfo->frameSizes[1].sizes[1].y = 480;
      cameraInfo->frameSizes[1].sizes[2].x = 480;
      cameraInfo->frameSizes[1].sizes[2].y = 320;
      cameraInfo->frameSizes[1].sizes[3].x = 320;
      cameraInfo->frameSizes[1].sizes[3].y = 240;
      cameraInfo->frameSizes[1].numSizes = 4;

      camera->features.pixelSizeX = 5600;
      camera->features.pixelSizeY = 5600;

      break;

    case ZWOCAM_ASI174MM:
    case ZWOCAM_ASI174MC:
      cameraInfo->usb3Cam = 1;
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          3, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 1936;
      cameraInfo->frameSizes[1].sizes[0].y = 1216;
      cameraInfo->frameSizes[1].sizes[1].x = 640;
      cameraInfo->frameSizes[1].sizes[1].y = 480;
      cameraInfo->frameSizes[1].sizes[2].x = 320;
      cameraInfo->frameSizes[1].sizes[2].y = 240;
      cameraInfo->frameSizes[1].numSizes = 3;

      cameraInfo->frameSizes[2].sizes[0].x = 968;
      cameraInfo->frameSizes[2].sizes[0].y = 608;
      cameraInfo->frameSizes[2].numSizes = 1;

      camera->features.pixelSizeX = 5860;
      camera->features.pixelSizeY = 5860;

      break;

    case ZWOCAM_ASI178MM:
    case ZWOCAM_ASI178MC:
      cameraInfo->usb3Cam = 1;
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          7, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 3096;
      cameraInfo->frameSizes[1].sizes[0].y = 2080;
      cameraInfo->frameSizes[1].sizes[1].x = 2560;
      cameraInfo->frameSizes[1].sizes[1].y = 2048;
      cameraInfo->frameSizes[1].sizes[2].x = 2048;
      cameraInfo->frameSizes[1].sizes[2].y = 1080;
      cameraInfo->frameSizes[1].sizes[3].x = 1280;
      cameraInfo->frameSizes[1].sizes[3].y = 960;
      cameraInfo->frameSizes[1].sizes[4].x = 800;
      cameraInfo->frameSizes[1].sizes[4].y = 600;
      cameraInfo->frameSizes[1].sizes[5].x = 640;
      cameraInfo->frameSizes[1].sizes[5].y = 480;
      cameraInfo->frameSizes[1].sizes[6].x = 320;
      cameraInfo->frameSizes[1].sizes[6].y = 240;
      cameraInfo->frameSizes[1].numSizes = 7;

      cameraInfo->frameSizes[2].sizes[0].x = 1548;
      cameraInfo->frameSizes[2].sizes[0].y = 1040;
      cameraInfo->frameSizes[2].numSizes = 1;

      camera->features.pixelSizeX = 2400;
      camera->features.pixelSizeY = 2400;

      break;

    case ZWOCAM_ASI185MC:
      cameraInfo->usb3Cam = 1;
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          6, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 1944;
      cameraInfo->frameSizes[1].sizes[0].y = 1224;
      cameraInfo->frameSizes[1].sizes[1].x = 1920;
      cameraInfo->frameSizes[1].sizes[1].y = 1080;
      cameraInfo->frameSizes[1].sizes[2].x = 1024;
      cameraInfo->frameSizes[1].sizes[2].y = 768;
      cameraInfo->frameSizes[1].sizes[3].x = 800;
      cameraInfo->frameSizes[1].sizes[3].y = 800;
      cameraInfo->frameSizes[1].sizes[4].x = 640;
      cameraInfo->frameSizes[1].sizes[4].y = 480;
      cameraInfo->frameSizes[1].sizes[5].x = 320;
      cameraInfo->frameSizes[1].sizes[5].y = 240;
      cameraInfo->frameSizes[1].numSizes = 6;

      cameraInfo->frameSizes[2].sizes[0].x = 972;
      cameraInfo->frameSizes[2].sizes[0].y = 612;
      cameraInfo->frameSizes[2].numSizes = 1;

      camera->features.pixelSizeX = 3750;
      camera->features.pixelSizeY = 3750;

      break;

    case ZWOCAM_ASI224MC:
      cameraInfo->usb3Cam = 1;
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          5, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 1304;
      cameraInfo->frameSizes[1].sizes[0].y = 976;
      cameraInfo->frameSizes[1].sizes[1].x = 1280;
      cameraInfo->frameSizes[1].sizes[1].y = 960;
      cameraInfo->frameSizes[1].sizes[2].x = 800;
      cameraInfo->frameSizes[1].sizes[2].y = 600;
      cameraInfo->frameSizes[1].sizes[3].x = 640;
      cameraInfo->frameSizes[1].sizes[3].y = 480;
      cameraInfo->frameSizes[1].sizes[4].x = 320;
      cameraInfo->frameSizes[1].sizes[4].y = 250;
      cameraInfo->frameSizes[1].numSizes = 5;

      cameraInfo->frameSizes[2].sizes[0].x = 652;
      cameraInfo->frameSizes[2].sizes[0].y = 488;
      cameraInfo->frameSizes[2].numSizes = 1;

      camera->features.pixelSizeX = 3750;
      camera->features.pixelSizeY = 3750;

      break;

    case ZWOCAM_ASI290MM:
    case ZWOCAM_ASI290MC:
      cameraInfo->usb3Cam = 1;
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          5, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      if (!( cameraInfo->frameSizes[2].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = 1936;
      cameraInfo->frameSizes[1].sizes[0].y = 1096;
      cameraInfo->frameSizes[1].sizes[1].x = 1280;
      cameraInfo->frameSizes[1].sizes[1].y = 960;
      cameraInfo->frameSizes[1].sizes[2].x = 640;
      cameraInfo->frameSizes[1].sizes[2].y = 480;
      cameraInfo->frameSizes[1].sizes[3].x = 320;
      cameraInfo->frameSizes[1].sizes[3].y = 240;
      cameraInfo->frameSizes[1].numSizes = 4;

      cameraInfo->frameSizes[2].sizes[0].x = 968;
      cameraInfo->frameSizes[2].sizes[0].y = 548;
      cameraInfo->frameSizes[2].numSizes = 1;

      camera->features.pixelSizeX = 2900;
      camera->features.pixelSizeY = 2900;

      break;

    case ZWOCAM_ASI1600MM:
    case ZWOCAM_ASI1600MC:
      cameraInfo->usb3Cam = 1;
      if (!( cameraInfo->frameSizes[1].sizes = ( FRAMESIZE* ) calloc (
          5, sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: calloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }

      cameraInfo->frameSizes[1].sizes[0].x = 4656;
      cameraInfo->frameSizes[1].sizes[0].y = 3520;
      cameraInfo->frameSizes[1].sizes[1].x = 3840;
      cameraInfo->frameSizes[1].sizes[1].y = 2160;
      cameraInfo->frameSizes[1].sizes[2].x = 1920;
      cameraInfo->frameSizes[1].sizes[2].y = 1680;
      cameraInfo->frameSizes[1].sizes[3].x = 1280;
      cameraInfo->frameSizes[1].sizes[3].y = 960;
      cameraInfo->frameSizes[1].sizes[4].x = 640;
      cameraInfo->frameSizes[1].sizes[4].y = 480;
      cameraInfo->frameSizes[1].sizes[5].x = 320;
      cameraInfo->frameSizes[1].sizes[5].y = 240;
      cameraInfo->frameSizes[1].numSizes = 6;

      camera->features.pixelSizeX = 3800;
      camera->features.pixelSizeY = 3800;

      break;

    default:
      fprintf ( stderr, "unknown camera type %d. Using limited resolutions\n",
          cameraInfo->cameraType );
      cameraInfo->usb3Cam = camInfo.IsUSB3Camera ? 1 : 0;
      if (!( cameraInfo->frameSizes[1].sizes =
          ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
        fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
        free (( void* ) cameraInfo->frameSizes[1].sizes );
        free (( void* ) camera->_common );
        free (( void* ) camera->_private );
        free (( void* ) camera );
        return 0;
      }
      cameraInfo->frameSizes[1].sizes[0].x = cameraInfo->maxResolutionX;
      cameraInfo->frameSizes[1].sizes[0].y = cameraInfo->maxResolutionY;
      cameraInfo->frameSizes[1].numSizes = 1;
      // Fake up some resolutions for 2x binning
      if ( camera->controls[ OA_CAM_CTRL_BINNING ]) {
        if (!( cameraInfo->frameSizes[2].sizes =
            ( FRAMESIZE* ) malloc ( sizeof ( FRAMESIZE )))) {
          fprintf ( stderr, "%s: malloc ( FRAMESIZE ) failed\n", __FUNCTION__ );
          free (( void* ) cameraInfo->frameSizes[1].sizes );
          free (( void* ) camera->_common );
          free (( void* ) camera->_private );
          free (( void* ) camera );
          return 0;
        }
        cameraInfo->frameSizes[2].sizes[0].x = cameraInfo->maxResolutionX / 2;
        cameraInfo->frameSizes[2].sizes[0].y = cameraInfo->maxResolutionY / 2;
        cameraInfo->frameSizes[2].numSizes = 1;
      }

      break;
  }

  cameraInfo->xSize = cameraInfo->maxResolutionX;
  cameraInfo->ySize = cameraInfo->maxResolutionY;
  cameraInfo->buffers = 0;
  cameraInfo->configuredBuffers = 0;

  ASISetROIFormat ( cameraInfo->cameraId, cameraInfo->xSize,
      cameraInfo->ySize, cameraInfo->binMode, cameraInfo->videoCurrent );

  // The largest buffer size we should need
  // RGB colour is 3 bytes per pixel, mono one for 8-bit, two for 16-bit,
  // RAW is one for 8-bit, 2 for 16-bit.  We assume that if the BIT_DEPTH
  // control is supported them 16-bit is supported.
  multiplier = ( ASI_IMG_RGB24 == cameraInfo->videoCurrent ) ? 3 :
      ( camera->controls[ OA_CAM_CTRL_BIT_DEPTH ] ? 2 : 1 );
  cameraInfo->imageBufferLength = cameraInfo->maxResolutionX *
      cameraInfo->maxResolutionY * multiplier;
  cameraInfo->buffers = calloc ( OA_CAM_BUFFERS, sizeof ( struct ZWASIbuffer ));
  for ( i = 0; i < OA_CAM_BUFFERS; i++ ) {
    void* m = malloc ( cameraInfo->imageBufferLength );
    if ( m ) {
      cameraInfo->buffers[i].start = m;
      cameraInfo->configuredBuffers++;
    } else {
      fprintf ( stderr, "%s malloc failed\n", __FUNCTION__ );
      if ( i ) {
        for ( j = 0; j < i; j++ ) {
          free (( void* ) cameraInfo->buffers[j].start );
        }
      }
      for ( j = 1; j < 5; j++ ) {
        if ( cameraInfo->frameSizes[j].sizes ) {
          free (( void* ) cameraInfo->frameSizes[j].sizes );
        }
      }
      free (( void* ) camera->_common );
      free (( void* ) camera->_private );
      free (( void* ) camera );
      return 0;
    }
  }
  cameraInfo->nextBuffer = 0;
  cameraInfo->buffersFree = OA_CAM_BUFFERS;

  cameraInfo->stopControllerThread = cameraInfo->stopCallbackThread = 0;
  cameraInfo->commandQueue = oaDLListCreate();
  cameraInfo->callbackQueue = oaDLListCreate();

  if ( pthread_create ( &( cameraInfo->controllerThread ), 0,
      oacamZWASI2controller, ( void* ) camera )) {
    for ( i = 0; i < OA_CAM_BUFFERS; i++ ) {
      free (( void* ) cameraInfo->buffers[i].start );
    }
    for ( i = 1; i < 5; i++ ) {
      if ( cameraInfo->frameSizes[i].sizes )
        free (( void* ) cameraInfo->frameSizes[i].sizes );
    }
    free (( void* ) camera->_common );
    free (( void* ) camera->_private );
    free (( void* ) camera );
    oaDLListDelete ( cameraInfo->commandQueue, 0 );
    oaDLListDelete ( cameraInfo->callbackQueue, 0 );
    return 0;
  }

  if ( pthread_create ( &( cameraInfo->callbackThread ), 0,
      oacamZWASIcallbackHandler, ( void* ) camera )) {

    void* dummy;
    cameraInfo->stopControllerThread = 1;
    pthread_cond_broadcast ( &cameraInfo->commandQueued );
    pthread_join ( cameraInfo->controllerThread, &dummy );

    for ( i = 0; i < OA_CAM_BUFFERS; i++ ) {
      free (( void* ) cameraInfo->buffers[i].start );
    }
    for ( i = 1; i < 5; i++ ) {
      if ( cameraInfo->frameSizes[i].sizes )
        free (( void* ) cameraInfo->frameSizes[i].sizes );
    }
    free (( void* ) camera->_common );
    free (( void* ) camera->_private );
    free (( void* ) camera );
    oaDLListDelete ( cameraInfo->commandQueue, 0 );
    oaDLListDelete ( cameraInfo->callbackQueue, 0 );
    return 0;
  }

  return camera;
}


static void
_ZWASIInitFunctionPointers ( oaCamera* camera )
{
  camera->funcs.initCamera = oaZWASI2InitCamera;
  camera->funcs.closeCamera = oaZWASI2CloseCamera;

  camera->funcs.testControl = oaZWASICameraTestControl;
  camera->funcs.readControl = oaZWASI2CameraReadControl;
  camera->funcs.setControl = oaZWASICameraSetControl;
  camera->funcs.getControlRange = oaZWASICameraGetControlRange;

  camera->funcs.startStreaming = oaZWASICameraStartStreaming;
  camera->funcs.stopStreaming = oaZWASICameraStopStreaming;
  camera->funcs.isStreaming = oaZWASICameraIsStreaming;

  camera->funcs.setResolution = oaZWASICameraSetResolution;
  camera->funcs.setROI = oaZWASICameraSetResolution;

  camera->funcs.hasAuto = oacamHasAuto;
  //  camera->funcs.isAuto = oaIsAuto;

  camera->funcs.enumerateFrameSizes = oaZWASICameraGetFrameSizes;
  camera->funcs.getFramePixelFormat = oaZWASI2CameraGetFramePixelFormat;
  camera->funcs.testROISize = oaZWASICameraTestROISize;
}


int
oaZWASI2CloseCamera ( oaCamera* camera )
{
  int		j;
  void*		dummy;
  ZWASI_STATE*	cameraInfo;

  if ( camera ) {

    cameraInfo = camera->_private;

    cameraInfo->stopControllerThread = 1;
    pthread_cond_broadcast ( &cameraInfo->commandQueued );
    pthread_join ( cameraInfo->controllerThread, &dummy );

    cameraInfo->stopCallbackThread = 1;
    pthread_cond_broadcast ( &cameraInfo->callbackQueued );
    pthread_join ( cameraInfo->callbackThread, &dummy );

    ASICloseCamera ( cameraInfo->cameraId );

    if ( cameraInfo->buffers ) {
      for ( j = 0; j < OA_CAM_BUFFERS; j++ ) {
        if ( cameraInfo->buffers[j].start ) {
          free (( void* ) cameraInfo->buffers[j].start );
        }
      }
    }
    for ( j = 1; j < 5; j++ ) {
      if ( cameraInfo->frameSizes[j].sizes )
        free (( void* ) cameraInfo->frameSizes[j].sizes );
    }

    oaDLListDelete ( cameraInfo->commandQueue, 1 );
    oaDLListDelete ( cameraInfo->callbackQueue, 1 );

    free (( void* ) cameraInfo->buffers );
    free (( void* ) cameraInfo );
    free (( void* ) camera->_common );
    free (( void* ) camera );

  } else {
   return -OA_ERR_INVALID_CAMERA;
  }
  return OA_ERR_NONE;
}