/*****************************************************************************
 *
 * EUVCconnect.c -- Initialise EUVC cameras
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
#include <openastro/camera.h>
#include <openastro/util.h>

#include <libusb-1.0/libusb.h>

#include "unimplemented.h"
#include "oacamprivate.h"
#include "EUVC.h"
#include "EUVCstate.h"
#include "EUVCoacam.h"
#include "EUVCusb.h"


static void	_EUVCInitFunctionPointers ( oaCamera* );
static void	_getEUVCControlValues ( oaCamera*, int );
void*		_euvcEventHandler ( void* );
static int	_scanEUVCStream ( oaCamera*, struct
		    libusb_config_descriptor*, int );

static FRAMERATE	rates1[] = {
    { .numerator = 1, .denominator = 60 },
    { .numerator = 1, .denominator = 30 },
    { .numerator = 1, .denominator = 15 },
    { .numerator = 2, .denominator = 15 },
    { .numerator = 4, .denominator = 15 }
};
static FRAMERATES	pixelClockFrameRates = {
  .numRates = 5,
  .rates = rates1
};

/*
static FRAMERATE	intervals2[] = {
    { .numerator = 1, .denominator = 87 },
    { .numerator = 1, .denominator = 60 },
    { .numerator = 1, .denominator = 30 },
    { .numerator = 1, .denominator = 25 },
    { .numerator = 1, .denominator = 15 },
    { .numerator = 2, .denominator = 15 },
    { .numerator = 1, .denominator = 5 }};
static unsigned int	intervalIds2[] = { 6, 5, 0, 1, 2, 3, 4 };

static FRAMERATE	intervals3[] = {
    { .numerator = 1, .denominator = 60 },
    { .numerator = 1, .denominator = 30 },
    { .numerator = 1, .denominator = 15 },
    { .numerator = 2, .denominator = 15 }
};
static unsigned int	intervalIds3[] = { 0, 1, 2, 3 };

static FRAMERATE	intervals4[] = {
    { .numerator = 1, .denominator = 27 },
    { .numerator = 1, .denominator = 20 },
    { .numerator = 1, .denominator = 15 },
    { .numerator = 2, .denominator = 15 }
};
static unsigned int	intervalIds4[] = { 0, 1, 2, 3 };
*/

struct puCtrl EUVCControlData[] = {
  {
    .euvcControl        = EUVC_PU_BRIGHTNESS_CONTROL,
    .oaControl          = OA_CAM_CTRL_BRIGHTNESS,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_CONTRAST_CONTROL,
    .oaControl          = OA_CAM_CTRL_CONTRAST,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_HUE_CONTROL,
    .oaControl          = OA_CAM_CTRL_HUE,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_SATURATION_CONTROL,
    .oaControl          = OA_CAM_CTRL_SATURATION,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_SHARPNESS_CONTROL,
    .oaControl          = OA_CAM_CTRL_SHARPNESS,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_GAMMA_CONTROL,
    .oaControl          = OA_CAM_CTRL_GAMMA,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL,
    .oaControl          = OA_CAM_CTRL_WHITE_BALANCE_TEMP,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL,
    .oaControl          = 0, // odd one.  R&B combined?
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 4
  }, {
    .euvcControl        = EUVC_PU_BACKLIGHT_COMPENSATION_CONTROL,
    .oaControl          = 0,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_GAIN_CONTROL,
    .oaControl          = OA_CAM_CTRL_GAIN,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_POWER_LINE_FREQUENCY_CONTROL,
    .oaControl          = 0,
    .oaControlType      = OA_CTRL_TYPE_MENU,
    .size               = 1
  }, {
    .euvcControl        = EUVC_PU_HUE_AUTO_CONTROL,
    .oaControl          = OA_CAM_CTRL_HUE_AUTO,
    .oaControlType      = OA_CTRL_TYPE_BOOLEAN,
    .size               = 1
  }, {
    .euvcControl        = EUVC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL,
    .oaControl          = OA_CAM_CTRL_AUTO_WHITE_BALANCE_TEMP,
    .oaControlType      = OA_CTRL_TYPE_BOOLEAN,
    .size               = 1
  }, {
    .euvcControl        = EUVC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL,
    .oaControl          = OA_CAM_CTRL_AUTO_WHITE_BALANCE,
    .oaControlType      = OA_CTRL_TYPE_BOOLEAN,
    .size               = 1
  }, {
    .euvcControl        = EUVC_PU_DIGITAL_MULTIPLIER_CONTROL,
    .oaControl          = 0,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL,
    .oaControl          = 0,
    .oaControlType      = OA_CTRL_TYPE_INT32,
    .size               = 2
  }, {
    .euvcControl        = EUVC_PU_ANALOG_VIDEO_STANDARD_CONTROL,
    .oaControl          = 0,
    .oaControlType      = OA_CTRL_TYPE_READONLY,
    .size               = 1
  }, {
    .euvcControl        = EUVC_PU_ANALOG_LOCK_STATUS_CONTROL,
    .oaControl          = 0,
    .oaControlType      = OA_CTRL_TYPE_READONLY,
    .size               = 1
  }, {
    .euvcControl        = EUVC_PU_CONTRAST_AUTO_CONTROL,
    .oaControl          = OA_CAM_CTRL_AUTO_CONTRAST,
    .oaControlType      = OA_CTRL_TYPE_BOOLEAN,
    .size               = 1
  }
};

unsigned int numPUEUVCControls = sizeof ( EUVCControlData ) /
    sizeof ( struct puCtrl );


/**
 * Initialise a given camera device
 */

oaCamera*
oaEUVCInitCamera ( oaCameraDevice* device )
{
  oaCamera*				camera;
  int                   		i, j, matched;
  int					deviceAddr, deviceBus, numUSBDevices;
  int					interfaceNo;
  libusb_device**			devlist;
  libusb_device*			usbDevice;
  libusb_device_handle*			usbHandle = 0;
  const struct libusb_interface_descriptor* interfaceDesc;
  struct libusb_device_descriptor	desc;
  struct libusb_config_descriptor*	deviceConfig;
  DEVICE_INFO*				devInfo;
  EUVC_STATE*				cameraInfo;
  COMMON_INFO*				commonInfo;
  unsigned int				k, oaControl, control;
  uint8_t				cameraTypeFlags, euvcControl;
  const uint8_t*			data;
  uint8_t				dataLeft, blockSize, subtype;
  uint64_t				flags;
  int32_t				puCaps, colourFormats;
  uint16_t				termCaps;
  uint8_t				buff[4];

  devInfo = device->_private;

  if (!( camera = ( oaCamera* ) malloc ( sizeof ( oaCamera )))) {
    perror ( "malloc oaCamera failed" );
    return 0;
  }
  if (!( cameraInfo = ( EUVC_STATE* ) malloc ( sizeof ( EUVC_STATE )))) {
    free (( void* ) camera );
    perror ( "malloc EUVC_STATE failed" );
    return 0;
  }
  if (!( commonInfo = ( COMMON_INFO* ) malloc ( sizeof ( COMMON_INFO )))) {
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    perror ( "malloc COMMON_INFO failed" );
    return 0;
  }

  OA_CLEAR ( *cameraInfo );
  OA_CLEAR ( *commonInfo );
  OA_CLEAR ( camera->controls );
  OA_CLEAR ( camera->features );
  camera->_private = cameraInfo;
  camera->_common = commonInfo;

  _oaInitCameraFunctionPointers ( camera );
  _EUVCInitFunctionPointers ( camera );

  ( void ) strcpy ( camera->deviceName, device->deviceName );
  cameraInfo->initialised = 0;
  cameraInfo->index = -1;

  // FIX ME -- This is a bit ugly.  Much of it is repeated from the
  // getCameras function.  I should join the two together somehow.

  libusb_init ( &cameraInfo->usbContext );
  numUSBDevices = libusb_get_device_list ( cameraInfo->usbContext, &devlist );
  if ( numUSBDevices < 1 ) {
    libusb_free_device_list ( devlist, 1 );
    libusb_exit ( cameraInfo->usbContext );
    if ( numUSBDevices ) {
      fprintf ( stderr, "Can't see any USB devices now (list returns -1)\n" );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free (( void* ) camera );
      return 0;
    }
    fprintf ( stderr, "Can't see any USB devices now\n" );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  matched = 0;
  deviceAddr = devInfo->devIndex & 0xff;
  deviceBus = devInfo->devIndex >> 8;
  for ( i = 0; i < numUSBDevices && !matched; i++ ) {
    usbDevice = devlist[i];
    if ( LIBUSB_SUCCESS != libusb_get_device_descriptor ( usbDevice, &desc )) {
      libusb_free_device_list ( devlist, 1 );
      libusb_exit ( cameraInfo->usbContext );
      fprintf ( stderr, "get device descriptor failed\n" );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free (( void* ) camera );
      return 0;
    }
    if ( TIS_VENDOR_ID == desc.idVendor &&
        desc.idProduct == EUVCCameraList[ devInfo->misc ].productId &&
        libusb_get_bus_number ( usbDevice ) == deviceBus &&
        libusb_get_device_address ( usbDevice ) == deviceAddr ) {
      // this looks like the one!
      matched = 1;
      libusb_open ( usbDevice, &usbHandle );
    }
  }
  libusb_free_device_list ( devlist, 1 );
  if ( !matched ) {
    fprintf ( stderr, "No matching USB device found!\n" );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }
  if ( !usbHandle ) {
    fprintf ( stderr, "Unable to open USB device!\n" );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  cameraInfo->usbHandle = usbHandle;

  if ( libusb_get_config_descriptor ( usbDevice, 0, &deviceConfig )) {
    fprintf ( stderr, "Unable to get device config descriptor!\n" );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  for ( interfaceNo = 0; interfaceNo < deviceConfig->bNumInterfaces;
      interfaceNo++ ) {
    interfaceDesc = &deviceConfig->interface[ interfaceNo ].altsetting[0];
    if ( 255 == interfaceDesc->bInterfaceClass &&
        1 == interfaceDesc->bInterfaceSubClass ) {
      break;
    }
    interfaceDesc = 0;
  }

  if ( !interfaceDesc ) {
    fprintf ( stderr, "Unable to find correct interface class\n" );
    libusb_free_config_descriptor ( deviceConfig );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  cameraInfo->controlInterfaceNo = interfaceNo;
  cameraInfo->controlEndpoint = 0;
  if ( interfaceDesc->bNumEndpoints ) {
    cameraInfo->controlEndpoint = interfaceDesc->endpoint[0].bEndpointAddress;
  }

  if ( libusb_kernel_driver_active ( usbHandle, interfaceNo )) {
    libusb_detach_kernel_driver( usbHandle, interfaceNo );
  }

  if ( libusb_claim_interface ( usbHandle, cameraInfo->controlInterfaceNo )) {
    fprintf ( stderr, "Unable to claim interface for USB device!\n" );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  // Have to do this now because we need to know if the camera is colour
  // or mono
  if ( euvcUsbReadRegister ( cameraInfo, EUVC_REG_CAMERA_TYPE,
      &cameraTypeFlags ) != 1 ) {
    fprintf ( stderr, "euvcReadRegister for reg %d returns error\n",
        EUVC_REG_CAMERA_TYPE );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  cameraInfo->cameraTypeFlags = cameraTypeFlags;
  cameraInfo->isColour = ( 2 == ( cameraTypeFlags & 0x3 )) ? 1 : 0;

  // Grab all the stuff associated with a processing unit

  data = interfaceDesc->extra;
  dataLeft = interfaceDesc->extra_length;

  while ( dataLeft >= 3 ) {
    blockSize = data[0];
    subtype = data[2];

    switch ( subtype ) {
      case EUVC_VC_HEADER:
        if ( blockSize > 13 ) {
          fprintf ( stderr, "Not expecting more than one video stream\n" );
          libusb_free_config_descriptor ( deviceConfig );
          libusb_exit ( cameraInfo->usbContext );
          free (( void* ) commonInfo );
          free (( void* ) cameraInfo );
          free (( void* ) camera );
          return 0;
        }
        for ( i = 12; i < blockSize; i++ ) {
          if ( _scanEUVCStream ( camera, deviceConfig, data[i] )) {
            fprintf ( stderr, "Scan of stream %d failed\n", i );
            libusb_free_config_descriptor ( deviceConfig );
            libusb_exit ( cameraInfo->usbContext );
            free (( void* ) commonInfo );
            free (( void* ) cameraInfo );
            free (( void* ) camera );
            return 0;
          }
        }
        break;

      case EUVC_VC_INPUT_TERMINAL:
        cameraInfo->terminalId = data[3];
        for ( i = 14 + data[14]; i >= 15; i-- ) {
          cameraInfo->termControlsBitmap = data[i] +
              ( cameraInfo->termControlsBitmap << 8 );
        }
        break;

      case EUVC_VC_PROCESSING_UNIT:
        cameraInfo->processingUnitId = data[3];
        cameraInfo->processingSourceId = data[3];
        for ( i = 7 + data[7]; i >= 8; i-- ) {
          cameraInfo->puControlsBitmap = data[i] +
              ( cameraInfo->puControlsBitmap << 8 );
        }
        break;

      case EUVC_VC_EXTENSION_UNIT:
        // don't whine about this for the time being
        // fprintf ( stderr, "Unhandled VC extension unit\n" );
        break;

      case EUVC_VC_OUTPUT_TERMINAL:
      case EUVC_VC_SELECTOR_UNIT:
        break;

      default:
        fprintf ( stderr, "Unhandled VC subtype %d\n", subtype );
        break;
    }

    dataLeft -= blockSize;
    data += blockSize;
  }

  if ( !cameraInfo->processingUnitId ) {
    fprintf ( stderr, "processing unit not found\n" );
    libusb_free_config_descriptor ( deviceConfig );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }

  if ( cameraInfo->streamInterfaceNo != cameraInfo->controlInterfaceNo ) {
    if ( libusb_kernel_driver_active ( usbHandle,
        cameraInfo->streamInterfaceNo )) {
      libusb_detach_kernel_driver( usbHandle, cameraInfo->streamInterfaceNo );
    }

    if ( libusb_claim_interface ( usbHandle, cameraInfo->streamInterfaceNo )) {
      fprintf ( stderr, "Unable to claim interface for USB device!\n" );
      libusb_exit ( cameraInfo->usbContext );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free (( void* ) camera );
      return 0;
    }
  }

  // Handle the controls from the input terminal

  control = 1;
  flags = cameraInfo->termControlsBitmap;
  for ( k = 0; k < numPUEUVCControls; k++ ) {
    if ( flags & 1 ) {

      // FIX ME -- need to know what the units are for all of these

      switch ( control ) {

        case EUVC_CT_SCANNING_MODE_CONTROL:
          fprintf ( stderr, "Unsupported control CT_SCANNING_MODE_CONTROL\n" );
          break;

        case EUVC_CT_AE_MODE_CONTROL:
        {
          uint8_t euvcdef, def = 1;

          // FIX ME
          // EUVC auto exposure mode is messy -- a bitfield of:
          // 1 = manual, 2 = auto, 4 = shutter priority, 8 = aperture priority
          // fortunately the exponents of the bit values correspond to the
          // menu values we're using
          camera->controls[ OA_CAM_CTRL_AUTO_EXPOSURE ] =
              OA_CTRL_TYPE_MENU;
          commonInfo->min[ OA_CAM_CTRL_AUTO_EXPOSURE ] = OA_EXPOSURE_AUTO;
          commonInfo->max[ OA_CAM_CTRL_AUTO_EXPOSURE ] =
              OA_EXPOSURE_APERTURE_PRIORITY;
          commonInfo->step[ OA_CAM_CTRL_AUTO_EXPOSURE ] = 1;

          if ( getEUVCTermControl ( cameraInfo, EUVC_CT_AE_MODE_CONTROL,
              &euvcdef, 1, EUVC_GET_DEF )) {
            fprintf ( stderr, "failed to get min value for AE setting\n" );
          }
          switch ( euvcdef ) {
             case 1:
               def = OA_EXPOSURE_MANUAL;
               break;
             case 2:
               def = OA_EXPOSURE_AUTO;
               break;
             case 4:
               def = OA_EXPOSURE_SHUTTER_PRIORITY;
               break;
             case 8:
               def = OA_EXPOSURE_APERTURE_PRIORITY;
               break;
             default:
               def = OA_EXPOSURE_MANUAL; // FIX ME -- why?
               break;
          }
          commonInfo->def[ OA_CAM_CTRL_AUTO_EXPOSURE ] = def;
          break;
        }
        case EUVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL:
        {
          camera->controls[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              OA_CTRL_TYPE_INT64;
          if ( getEUVCTermControl ( cameraInfo,
              EUVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, buff, 4,
              EUVC_GET_MIN )) {
            fprintf ( stderr, "failed to get min value for AE setting\n" );
          }
          commonInfo->min[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              buff[0] + ( buff[1] << 8 ) + ( buff[2] << 16 ) +
              ( buff[3] << 24 );
          if ( getEUVCTermControl ( cameraInfo,
              EUVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, buff, 4,
              EUVC_GET_MAX )) {
            fprintf ( stderr, "failed to get max value for AE setting\n" );
          }
          commonInfo->max[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              buff[0] + ( buff[1] << 8 ) + ( buff[2] << 16 ) +
              ( buff[3] << 24 );
          if ( getEUVCTermControl ( cameraInfo,
              EUVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, buff, 4,
              EUVC_GET_RES )) {
            fprintf ( stderr, "failed to get resolution for AE setting\n" );
          }
          commonInfo->step[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              buff[0] + ( buff[1] << 8 ) + ( buff[2] << 16 ) +
              ( buff[3] << 24 );
          if ( getEUVCTermControl ( cameraInfo,
              EUVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL, buff, 4,
              EUVC_GET_DEF )) {
            fprintf ( stderr, "failed to get default for AE setting\n" );
          }
          commonInfo->def[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] =
              buff[0] + ( buff[1] << 8 ) + ( buff[2] << 16 ) +
              ( buff[3] << 24 );

          // now convert the values from 100usec to usec.
          commonInfo->min[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] *= 100;
          commonInfo->max[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] *= 100;
          commonInfo->step[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] *= 100;
          commonInfo->def[ OA_CAM_CTRL_EXPOSURE_ABSOLUTE ] *= 100;
          break;
        }

        case EUVC_CT_ZOOM_ABSOLUTE_CONTROL:
        case EUVC_CT_EXPOSURE_TIME_RELATIVE_CONTROL:
        case EUVC_CT_AE_PRIORITY_CONTROL:
        case EUVC_CT_FOCUS_ABSOLUTE_CONTROL:
        case EUVC_CT_FOCUS_RELATIVE_CONTROL:
        case EUVC_CT_FOCUS_AUTO_CONTROL:
        case EUVC_CT_IRIS_ABSOLUTE_CONTROL:
        case EUVC_CT_IRIS_RELATIVE_CONTROL:
        case EUVC_CT_ZOOM_RELATIVE_CONTROL:
        case EUVC_CT_PANTILT_ABSOLUTE_CONTROL:
        case EUVC_CT_PANTILT_RELATIVE_CONTROL:
        case EUVC_CT_ROLL_ABSOLUTE_CONTROL:
        case EUVC_CT_ROLL_RELATIVE_CONTROL:
        case EUVC_CT_PRIVACY_CONTROL:
        case EUVC_CT_FOCUS_SIMPLE_CONTROL:
        case EUVC_CT_DIGITAL_WINDOW_CONTROL:
        case EUVC_CT_REGION_OF_INTEREST_CONTROL:
        // I don't know if any of these below will actually ever turn up
        // but there's no need to give an error if they do
        case EUVC_CT_CAPABILITY:
        case EUVC_CT_PIXEL_CLOCK:
        case EUVC_CT_PARTIAL_SCAN_WIDTH:
        case EUVC_CT_PARTIAL_SCAN_HEIGHT:
        case EUVC_CT_BLANKING_INFO:
        case EUVC_CT_PARTIAL_SCAN_X:
        case EUVC_CT_PARTIAL_SCAN_Y:
        case EUVC_CT_BINNING:
        case EUVC_CT_SOFTWARE_TRIGGER:
        case EUVC_CT_SENSOR_RESET:
        case EUVC_CT_FIRMWARE_REVISION:
        case EUVC_CT_GPOUT:
        case EUVC_CT_HDR_ENABLE:
        case EUVC_CT_HDR_SHUTTER_1:
        case EUVC_CT_HDR_SHUTTER_2:
        case EUVC_CT_HDR_VSTEP_1:
        case EUVC_CT_HDR_VSTEP_2:
        case EUVC_CT_HDR_VSTEP_3:
        case EUVC_CT_HDR_VSTEP_4:
        case EUVC_CT_UART:
          // fprintf ( stderr, "Unsupported EUVC control %d\n", control );
          break;

        default:
          fprintf ( stderr, "Unknown EUVC control %d\n", control );
          break;
      }
    }
    flags >>= 1;
    control++;
  }

  if ( flags ) {
    fprintf ( stderr, "unknown EUVC processing unit controls are present\n" );
  }

  if ( getEUVCTermControl ( cameraInfo, EUVC_CT_CAPABILITY,
      &buff, 2, EUVC_GET_CUR )) {
    fprintf ( stderr, "unable to get term capabilities\n" );
    libusb_free_config_descriptor ( deviceConfig );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }
  termCaps = buff[0] + ( buff[1] << 8 );

  if (( termCaps & EUVC_CT_CAPABILITY_PARTIAL_SCAN_WIDTH ) &&
      ( termCaps & EUVC_CT_CAPABILITY_PARTIAL_SCAN_HEIGHT )) {
    camera->features.ROI = 1;
  }

  // I'm not aware of any camera modes that don't fit this
  cameraInfo->bytesPerPixel = 1;
  cameraInfo->binMode = OA_BIN_MODE_NONE;
  if ( termCaps & EUVC_CT_CAPABILITY_BINNING ) {
    camera->controls[ OA_CAM_CTRL_BINNING ] = OA_CTRL_TYPE_DISCRETE;
  }

  // Deal with the controls from the processing unit

  flags = cameraInfo->puControlsBitmap;
  cameraInfo->haveComponentWhiteBalance = 0;
  for ( k = 0; k < numPUEUVCControls; k++ ) {
    if ( flags & 1 ) {
      // FIX ME -- remove these two temp variables
      euvcControl = EUVCControlData[ k ].euvcControl;
      oaControl = EUVCControlData[ k ].oaControl;
      // if oaControl == 0 we don't support this yet, but white balance
      // component is a special case because it is red and blue balance
      // combined
      if ( EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL == euvcControl ) {
        cameraInfo->haveComponentWhiteBalance = 1;
      }
      if ( oaControl || ( EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL ==
          euvcControl )) {
        // FIX ME -- need to know what the default units are for all of these
        _getEUVCControlValues ( camera, k );
      } else {
        fprintf ( stderr, "Unsupported EUVC processing unit control %d = %d\n",
            k, euvcControl );
      }
    }
    flags >>= 1;
  }

  if ( flags ) {
    fprintf ( stderr, "unknown EUVC processing unit controls are present\n" );
  }

  if (( puCaps = getEUVCControl ( cameraInfo, EUVC_PU_CAPABILITY, 2,
      EUVC_GET_CUR )) < 0 ) {
    fprintf ( stderr, "unable to get PU capabilities\n" );
    libusb_free_config_descriptor ( deviceConfig );
    libusb_exit ( cameraInfo->usbContext );
    free (( void* ) commonInfo );
    free (( void* ) cameraInfo );
    free (( void* ) camera );
    return 0;
  }
  if ( puCaps & EUVC_PU_CAPABILITY_COLOUR_FORMAT ) {
    if (( colourFormats = getEUVCControl ( cameraInfo,
        EUVC_PU_COLOR_FORMAT, 2, EUVC_GET_CUR )) < 0 ) {
      fprintf ( stderr, "unable to get colour formats\n" );
      libusb_free_config_descriptor ( deviceConfig );
      libusb_exit ( cameraInfo->usbContext );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free (( void* ) camera );
      return 0;
    }
    cameraInfo->colourFormats = colourFormats;
  }

  // Finally, if we have a pixel clock we're going to use that to set the
  // frame rates.  Read the pixel clock rate etc.

  camera->features.frameRates = 1;
  if (( termCaps & EUVC_CT_CAPABILITY_PIXEL_CLOCK ) &&
      ( termCaps & EUVC_CT_CAPABILITY_BLANKING_INFO )) {
    if ( getEUVCTermControl ( cameraInfo, EUVC_CT_PIXEL_CLOCK,
        buff, 4, EUVC_GET_MIN )) {
      fprintf ( stderr, "unable to get term capabilities\n" );
      libusb_free_config_descriptor ( deviceConfig );
      libusb_exit ( cameraInfo->usbContext );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free (( void* ) camera );
      return 0;
    }
    cameraInfo->minPixelClock = buff[0] + ( buff[1] << 8 ) +
        ( buff[2] << 16 ) + ( buff[3] << 24 );
    if ( getEUVCTermControl ( cameraInfo, EUVC_CT_PIXEL_CLOCK,
        buff, 4, EUVC_GET_MAX )) {
      fprintf ( stderr, "unable to get term capabilities\n" );
      libusb_free_config_descriptor ( deviceConfig );
      libusb_exit ( cameraInfo->usbContext );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free (( void* ) camera );
      return 0;
    }
    cameraInfo->maxPixelClock = buff[0] + ( buff[1] << 8 ) +
        ( buff[2] << 16 ) + ( buff[3] << 24 );

    if ( getEUVCTermControl ( cameraInfo, EUVC_CT_PIXEL_CLOCK,
        &buff, 4, EUVC_GET_CUR )) {
      fprintf ( stderr, "unable to get term capabilities\n" );
      libusb_free_config_descriptor ( deviceConfig );
      libusb_exit ( cameraInfo->usbContext );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free (( void* ) camera );
      return 0;
    }
    cameraInfo->currentPixelClock = buff[0] + ( buff[1] << 8 ) +
        ( buff[2] << 16 ) + ( buff[3] << 24 );
    cameraInfo->frameRates = &pixelClockFrameRates;
    cameraInfo->currentFrameRate = 1;
  } else {
    fprintf ( stderr, "need to set up frame rates\n" );
  }


  // need to initialise these first two here so they're available for the
  // euvcUsbReadRegister call

  pthread_mutex_init ( &cameraInfo->usbMutex, 0 );
  pthread_mutex_init ( &cameraInfo->commandQueueMutex, 0 );
  pthread_mutex_init ( &cameraInfo->callbackQueueMutex, 0 );
  pthread_mutex_init ( &cameraInfo->videoCallbackMutex, 0 );
  pthread_cond_init ( &cameraInfo->callbackQueued, 0 );
  pthread_cond_init ( &cameraInfo->commandQueued, 0 );
  pthread_cond_init ( &cameraInfo->commandComplete, 0 );
  cameraInfo->isStreaming = 0;

  // Set up the status transfer and callback

  if (!( cameraInfo->statusTransfer = libusb_alloc_transfer(0))) {
    fprintf ( stderr, "Can't allocate status transfer\n" );
    free (( void* ) camera->_common );
    free (( void* ) camera->_private );
    free (( void* ) camera );
    return 0;
  }
  libusb_fill_interrupt_transfer ( cameraInfo->statusTransfer, usbHandle,
      USB_INTR_EP_IN, cameraInfo->statusBuffer,
      sizeof ( cameraInfo->statusBuffer ), euvcStatusCallback, cameraInfo, 0 );
  if ( libusb_submit_transfer ( cameraInfo->statusTransfer )) {
    fprintf ( stderr, "submit of status transfer callback failed\n" );
    // FIX ME -- free interrupt transfer buffer?
    free (( void* ) camera->_common );
    free (( void* ) camera->_private );
    free (( void* ) camera );
    return 0;
  }

  pthread_create ( &cameraInfo->eventHandler, 0, _euvcEventHandler,
      ( void* ) cameraInfo );

  camera->interface = device->interface;
  cameraInfo->index = devInfo->devIndex;
  cameraInfo->cameraType = devInfo->devType;

  cameraInfo->buffers = 0;
  cameraInfo->configuredBuffers = 0;
  cameraInfo->imageBufferLength = cameraInfo->maxResolutionX *
      cameraInfo->maxResolutionY * cameraInfo->bytesPerPixel;

  if (!( cameraInfo->buffers = calloc ( OA_CAM_BUFFERS,
      sizeof ( struct EUVCbuffer )))) {
    fprintf ( stderr, "malloc of buffer array failed in %s\n",
        __FUNCTION__ );
    // FIX ME -- free interrupt transfer buffer?
    // FIX ME -- kill event handler thread
    free (( void* ) cameraInfo->frameSizes[1].sizes );
    // free (( void* ) cameraInfo->frameSizes[2].sizes );
    free (( void* ) camera->_common );
    free (( void* ) camera->_private );
    free (( void* ) camera );
    return 0;
  }

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
      // FIX ME -- free interrupt transfer buffer?
      // FIX ME -- kill event handler thread
      free (( void* ) cameraInfo->frameSizes[1].sizes );
      // free (( void* ) cameraInfo->frameSizes[2].sizes );
      free (( void* ) cameraInfo->buffers );
      free (( void* ) commonInfo );
      free (( void* ) cameraInfo );
      free ( camera );
      return 0;
    }
  }

  cameraInfo->buffersFree = cameraInfo->configuredBuffers;
  cameraInfo->currentExposure = EUVC_DEFAULT_EXPOSURE * 1000;

  cameraInfo->stopControllerThread = cameraInfo->stopCallbackThread = 0;
  cameraInfo->commandQueue = oaDLListCreate();
  cameraInfo->callbackQueue = oaDLListCreate();
  if ( pthread_create ( &( cameraInfo->controllerThread ), 0,
      oacamEUVCcontroller, ( void* ) camera )) {
    for ( j = 0; j < OA_CAM_BUFFERS; j++ ) {
      free (( void* ) cameraInfo->buffers[j].start );
    }
    // FIX ME -- free interrupt transfer buffer?
    // FIX ME -- kill event handler thread
    free (( void* ) cameraInfo->frameSizes[1].sizes );
    // free (( void* ) cameraInfo->frameSizes[2].sizes );
    free (( void* ) cameraInfo->buffers );
    free (( void* ) camera->_common );
    free (( void* ) camera->_private );
    free (( void* ) camera );
    oaDLListDelete ( cameraInfo->commandQueue, 0 );
    oaDLListDelete ( cameraInfo->callbackQueue, 0 );
    return 0;
  }

  if ( pthread_create ( &( cameraInfo->callbackThread ), 0,
      oacamEUVCcallbackHandler, ( void* ) camera )) {

    void* dummy;
    cameraInfo->stopControllerThread = 1;
    pthread_cond_broadcast ( &cameraInfo->commandQueued );
    pthread_join ( cameraInfo->controllerThread, &dummy );
    for ( j = 0; j < OA_CAM_BUFFERS; j++ ) {
      free (( void* ) cameraInfo->buffers[j].start );
    }
    // FIX ME -- free interrupt transfer buffer?
    // FIX ME -- kill event handler thread
    free (( void* ) cameraInfo->frameSizes[1].sizes );
    // free (( void* ) cameraInfo->frameSizes[2].sizes );
    free (( void* ) cameraInfo->buffers );
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
_EUVCInitFunctionPointers ( oaCamera* camera )
{
  camera->funcs.initCamera = oaEUVCInitCamera;
  camera->funcs.closeCamera = oaEUVCCloseCamera;

  camera->funcs.setControl = oaEUVCCameraSetControl;
  camera->funcs.readControl = oaEUVCCameraReadControl;
  camera->funcs.testControl = oaEUVCCameraTestControl;
  camera->funcs.getControlRange = oaEUVCCameraGetControlRange;

  camera->funcs.startStreaming = oaEUVCCameraStartStreaming;
  camera->funcs.stopStreaming = oaEUVCCameraStopStreaming;
  camera->funcs.isStreaming = oaEUVCCameraIsStreaming;

  camera->funcs.setResolution = oaEUVCCameraSetResolution;
  camera->funcs.setROI = oaEUVCCameraSetROI;
  camera->funcs.testROISize = oaEUVCCameraTestROISize;

  camera->funcs.hasAuto = oacamHasAuto;
  // camera->funcs.isAuto = _isAuto;

  camera->funcs.enumerateFrameSizes = oaEUVCCameraGetFrameSizes;
  camera->funcs.getFramePixelFormat = oaEUVCCameraGetFramePixelFormat;

  camera->funcs.enumerateFrameRates = oaEUVCCameraGetFrameRates;
  camera->funcs.setFrameInterval = oaEUVCCameraSetFrameInterval;
}


int
oaEUVCCloseCamera ( oaCamera* camera )
{
  int		j, res;
  void*		dummy;
  EUVC_STATE*	cameraInfo;

  if ( camera ) {

    cameraInfo = camera->_private;

    cameraInfo->stopControllerThread = 1;

    pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
    if ( cameraInfo->statusTransfer ) {
      res = libusb_cancel_transfer ( cameraInfo->statusTransfer );
      if ( res < 0 && res != LIBUSB_ERROR_NOT_FOUND ) {
        free ( cameraInfo->statusBuffer );
        libusb_free_transfer ( cameraInfo->statusTransfer );
        cameraInfo->statusTransfer = 0;
      }
    }
    pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );

    pthread_cond_broadcast ( &cameraInfo->commandQueued );
    pthread_join ( cameraInfo->controllerThread, &dummy );

    cameraInfo->stopCallbackThread = 1;
    pthread_cond_broadcast ( &cameraInfo->callbackQueued );
    pthread_join ( cameraInfo->callbackThread, &dummy );

    pthread_join ( cameraInfo->eventHandler, &dummy );

    libusb_release_interface ( cameraInfo->usbHandle, 0 );
    libusb_close ( cameraInfo->usbHandle );
    libusb_exit ( cameraInfo->usbContext );

    if ( cameraInfo->buffers ) {
      for ( j = 0; j < OA_CAM_BUFFERS; j++ ) {
        if ( cameraInfo->buffers[j].start ) {
          free (( void* ) cameraInfo->buffers[j].start );
        }
      }
    }
    free (( void* ) cameraInfo->frameSizes[1].sizes );
    // free (( void* ) cameraInfo->frameSizes[2].sizes );
    free (( void* ) cameraInfo->buffers );
    free (( void* ) cameraInfo );
    free (( void* ) camera->_common );
    free (( void* ) camera );
  } else {
    return -OA_ERR_INVALID_CAMERA;
  }
  return OA_ERR_NONE;
}


void*
_euvcEventHandler ( void* param )
{
  struct timeval	tv;
  EUVC_STATE*		cameraInfo = param;
  int			exitThread;

  tv.tv_sec = 1;
  tv.tv_usec = 0;
  do {
    libusb_handle_events_timeout_completed ( cameraInfo->usbContext, &tv, 0 );
    pthread_mutex_lock ( &cameraInfo->callbackQueueMutex );
    exitThread = cameraInfo->stopCallbackThread;
    pthread_mutex_unlock ( &cameraInfo->callbackQueueMutex );
  } while ( !exitThread );
  return 0;
}


static void
_getEUVCControlValues ( oaCamera* camera, int index )
{
  int				len;
  unsigned int			oaControl, euvcControl;
  COMMON_INFO*			commonInfo = camera->_common;
  EUVC_STATE*			cameraInfo = camera->_private;

  euvcControl = EUVCControlData[ index ].euvcControl;
  oaControl = EUVCControlData[ index ].oaControl;
  len = EUVCControlData[ index ].size;

  // special case for white component control
  if ( EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL == euvcControl ) {
    int val;

    if (( val = getEUVCControl ( cameraInfo,
        EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL, len, EUVC_GET_MIN )) < 0 ) {
      return;
    }
    commonInfo->min[ OA_CAM_CTRL_BLUE_BALANCE ] = val & 0xffff;
    commonInfo->min[ OA_CAM_CTRL_RED_BALANCE ] = val >> 16;

    if (( val = getEUVCControl ( cameraInfo,
        EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL, len, EUVC_GET_MAX )) < 0 ) {
      return;
    }
    commonInfo->max[ OA_CAM_CTRL_BLUE_BALANCE ] = val & 0xffff;
    commonInfo->max[ OA_CAM_CTRL_RED_BALANCE ] = val >> 16;

    if (( val = getEUVCControl ( cameraInfo,
        EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL, len, EUVC_GET_RES )) < 0 ) {
      return;
    }
    commonInfo->step[ OA_CAM_CTRL_BLUE_BALANCE ] = val & 0xffff;
    commonInfo->step[ OA_CAM_CTRL_RED_BALANCE ] = val >> 16;

    if (( val = getEUVCControl ( cameraInfo,
        EUVC_PU_WHITE_BALANCE_COMPONENT_CONTROL, len, EUVC_GET_DEF )) < 0 ) {
      return;
    }
    commonInfo->def[ OA_CAM_CTRL_BLUE_BALANCE ] = val & 0xffff;
    commonInfo->def[ OA_CAM_CTRL_RED_BALANCE ] = val >> 16;

    camera->controls[ OA_CAM_CTRL_BLUE_BALANCE ] = OA_CTRL_TYPE_INT32;
    camera->controls[ OA_CAM_CTRL_RED_BALANCE ] = OA_CTRL_TYPE_INT32;

  } else {

    int val;

    camera->controls[ oaControl ] = EUVCControlData[ index ].oaControlType;

    switch ( camera->controls[ oaControl ] ) {
      case OA_CTRL_TYPE_INT32:
      case OA_CTRL_TYPE_MENU:
        if (( val = getEUVCControl ( cameraInfo, euvcControl, len,
            EUVC_GET_MIN )) < 0 ) {
          return;
        }
        commonInfo->min[ oaControl ] = val;
        if (( val = getEUVCControl ( cameraInfo, euvcControl, len,
            EUVC_GET_MAX )) < 0 ) {
          return;
        }
        commonInfo->max[ oaControl ] = val;
        if (( val = getEUVCControl ( cameraInfo, euvcControl, len,
            EUVC_GET_RES )) < 0 ) {
          return;
        }
        commonInfo->step[ oaControl ] = val;
        if (( commonInfo->def[ oaControl ] = getEUVCControl (
            cameraInfo, euvcControl, len, EUVC_GET_DEF )) < 0 ) {
          return;
        }
        break;

      case OA_CTRL_TYPE_BOOLEAN:
        commonInfo->min[ oaControl ] = 0;
        commonInfo->max[ oaControl ] = 1;
        commonInfo->step[ oaControl ] = 1;
        if (( val = getEUVCControl ( cameraInfo, euvcControl, len,
            EUVC_GET_DEF )) < 0 ) {
          return;
        }
        commonInfo->def[ oaControl ] = val;
        break;

      case OA_CTRL_TYPE_READONLY:
        break;

      default:
        fprintf ( stderr, "unhandled control type %d in %s\n",
            camera->controls[ oaControl ], __FUNCTION__ );
        break;
    }
  }
}


static int
_scanEUVCStream ( oaCamera* camera,
    struct libusb_config_descriptor* deviceConfig, int interfaceNo )
{
  EUVC_STATE*					cameraInfo;
  const struct libusb_interface_descriptor*	interfaceDesc;
  const uint8_t*				data;
  uint8_t					dataLeft, blockSize, subtype;
  uint8_t					frameIndex;
  unsigned int					xSize, ySize, lastFormatIndex;
  unsigned int					maxX, maxY, maxBufferSize, i;
  int						haveInterestingFormat;
  int						skipFrame, sizeIndex, binIndex;

  cameraInfo = camera->_private;
  interfaceDesc = &( deviceConfig->interface[ interfaceNo ].altsetting[0]);
  cameraInfo->streamInterfaceNo = interfaceDesc->bInterfaceNumber;

  data = interfaceDesc->extra;
  dataLeft = interfaceDesc->extra_length;
  lastFormatIndex = 0;
  haveInterestingFormat = 0;
  maxX = maxY = 0;

  while ( dataLeft >= 3 ) {
    blockSize = data[0];
    subtype = data[2];

    switch ( subtype ) {
      case EUVC_VS_INPUT_HEADER:
        cameraInfo->streamEndpoint = data[6] & 0x8f;
        break;

      case EUVC_VS_FORMAT_UNCOMPRESSED:
        haveInterestingFormat = 0;
        if ( 16 == data[21] ) { // bpp must be 16
          if ( cameraInfo->isColour ) {
            if ( !strncmp ( "YUY2", &data[5], 4 ) ||
                !strncmp ( "UYVY", &data[5], 4 )) {
              haveInterestingFormat = 1;
              lastFormatIndex = data[3];
            }
          } else {
            if ( !strncmp ( "Y800", &data[5], 4 )) {
              haveInterestingFormat = 1;
              lastFormatIndex = data[3];
            }
          }
        }
        break;

      case EUVC_VS_FRAME_UNCOMPRESSED:
        if ( haveInterestingFormat ) {
          frameIndex = data[3];
          skipFrame = 0;
          // xSize value is always half what it should be
          xSize = ( data[5] + ( data[6] << 8 )) * 2;
          ySize = data[7] + ( data[8] << 8 );
          maxBufferSize = data[17] + ( data[18] << 8 ) + ( data[19] << 16 ) +
              ( data[20] << 24 );
          if ( !cameraInfo->frameSizes[1].numSizes ) {
            binIndex = 1;
            sizeIndex = 0;
          } else {
            for ( i = 0; i < cameraInfo->frameSizes[1].numSizes &&
                !skipFrame; i++ ) {
              if ( xSize == cameraInfo->frameSizes[1].sizes[i].x &&
                  ySize == cameraInfo->frameSizes[1].sizes[i].y ) {
                skipFrame = 1;
              }
              if ( xSize > cameraInfo->frameSizes[1].sizes[i].x ||
                  ySize > cameraInfo->frameSizes[1].sizes[i].y ) {
                fprintf ( stderr, "size is greater than previous entry\n" );
                skipFrame = 1;
              }
            }
            if ( !skipFrame ) {
              // At this point the new size must be smaller than previous
              // ones.  If it is and binning is enabled, throw an error if
              // this size is not half the previous one (we're assuming
              // that 2x binning is enabled if 4x binning is).
              if ( camera->controls[ OA_CAM_CTRL_BINNING ] ) {
                if ( !cameraInfo->frameSizes[2].numSizes ) {
                  if ( xSize * 2 != cameraInfo->frameSizes[1].sizes[0].x ||
                      ySize * 2 != cameraInfo->frameSizes[1].sizes[0].y ) {
                    fprintf ( stderr, "bin mode size is not 2x smaller\n" );
                    skipFrame = 1;
                  } else {
                    binIndex = 2;
                    sizeIndex = 0;
                  }
                } else {
                  if ( !cameraInfo->frameSizes[4].numSizes ) {
                    if ( xSize * 4 != cameraInfo->frameSizes[1].sizes[0].x ||
                        ySize * 4 != cameraInfo->frameSizes[1].sizes[0].y ) {
                      fprintf ( stderr, "bin mode size is not 4x smaller\n" );
                      skipFrame = 1;
                    } else {
                      binIndex = 4;
                      sizeIndex = 0;
                    }
                  } else {
                    fprintf ( stderr, "too many binmode sizes\n" );
                    skipFrame = 1;
                  }
                }
              } else {
                binIndex = 1;
                sizeIndex = cameraInfo->frameSizes[1].numSizes;
              }
            }
          }

          if ( !skipFrame ) {
            if (!( cameraInfo->frameSizes[binIndex].sizes = ( FRAMESIZE* )
                realloc ( cameraInfo->frameSizes[binIndex].sizes,
                sizeof ( FRAMESIZE ) * ( sizeIndex + 1 )))) {
              fprintf ( stderr, "malloc for frame size failed\n" );
              return -OA_ERR_MEM_ALLOC;
            }
            if (!( cameraInfo->frameInfo[binIndex] = ( struct frameExtras* )
                realloc ( cameraInfo->frameInfo[binIndex],
                sizeof ( struct frameExtras ) * ( sizeIndex + 1 )))) {
              fprintf ( stderr, "malloc for frame extras failed\n" );
              return -OA_ERR_MEM_ALLOC;
            }

            cameraInfo->frameSizes[binIndex].sizes[sizeIndex].x = xSize;
            cameraInfo->frameSizes[binIndex].sizes[sizeIndex].y = ySize;
            cameraInfo->frameSizes[binIndex].numSizes++;

            cameraInfo->frameInfo[binIndex][sizeIndex].formatId = 
                lastFormatIndex;
            cameraInfo->frameInfo[binIndex][sizeIndex].frameId = frameIndex;
            cameraInfo->frameInfo[binIndex][sizeIndex].maxBufferSize =
                maxBufferSize + 2; // 2 allows for header

            if ( xSize > maxX ) {
              maxX = xSize;
            }
            if ( ySize > maxY ) {
              maxY = ySize;
            }
          }
        }
        break;
      // We don't expect to see or use any of these with EUVC cameras
      case EUVC_VS_OUTPUT_HEADER:
        // fprintf ( stderr, "unsupported subtype VS_OUTPUT_HEADER\n" );
        break;
      case EUVC_VS_STILL_IMAGE_FRAME:
        // fprintf ( stderr, "unsupported subtype VS_STILL_IMAGE_FRAME\n" );
        break;
      case EUVC_VS_FORMAT_MJPEG:
        // fprintf ( stderr, "unsupported subtype VS_FORMAT_MJPEG\n" );
        break;
      case EUVC_VS_FRAME_MJPEG:
        // fprintf ( stderr, "unsupported subtype VS_FRAME_MJPEG\n" );
        break;
      case EUVC_VS_FORMAT_MPEG2TS:
        // fprintf ( stderr, "unsupported subtype VS_FORMAT_MPEG2TS\n" );
        break;
      case EUVC_VS_FORMAT_DV:
        // fprintf ( stderr, "unsupported subtype VS_FORMAT_DV\n" );
        break;
      case EUVC_VS_COLORFORMAT:
        // fprintf ( stderr, "unsupported subtype VS_COLORFORMAT\n" );
        break;
      case EUVC_VS_FORMAT_FRAME_BASED:
        // fprintf ( stderr, "unsupported subtype VS_FORMAT_FRAME_BASED\n" );
        break;
      case EUVC_VS_FRAME_FRAME_BASED:
        // fprintf ( stderr, "unsupported subtype VS_FRAME_FRAME_BASED\n" );
        break;
      case EUVC_VS_FORMAT_STREAM_BASED:
        // fprintf ( stderr, "unsupported subtype VS_FORMAT_STREAM_BASED\n" );
        break;
      default:
        fprintf ( stderr, "unsupported descriptor subtype: %d\n", subtype );
        break;
    }

    dataLeft -= blockSize;
    data += blockSize;
  }

  cameraInfo->maxResolutionX = cameraInfo->xSize = maxX;
  cameraInfo->maxResolutionY = cameraInfo->ySize = maxY;

  return 0;
}
