/*****************************************************************************
 *
 * ZWASI2oacam.c -- main entrypoint for ZW ASI Cameras, API v2
 *
 * Copyright 2013,2014,2015,2016 James Fidell (james@openastroproject.org)
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

#include <ASICamera2.h>

#include "unimplemented.h"
#include "oacamprivate.h"
#include "ZWASI.h"
#include "ZWASI2oacam.h"

static const char *cameraNames[] = {
  "ZWO ASI130MM", "ZWO ASI120MM", "ZWO ASI120MC", "ZWO ASI035MM",
  "ZWO ASI035MC", "ZWO ASI030MC", "ZWO ASI034MC", "ZWO ASI120MM-S",
  "ZWO ASI120MC-S", "ZWO ASI174MM", "ZWO ASI174MC", "ZWO ASI178MM",
  "ZWO ASI178MC", "ZWO ASI185MC", "ZWO ASI224MC", "ZWO ASI1600MM",
  "ZWO ASI1600MC", "ZWO ASI290MM", "ZWO ASI290MC"
};

/**
 * Cycle through the cameras reported by the ASI library
 */

int
oaZWASI2GetCameras ( CAMERA_LIST* deviceList, int flags )
{
  unsigned int		numFound = 0, i;
  int			ret;
  const char*		currName;
  oaCameraDevice*	dev;
  DEVICE_INFO*		_private;
  ASI_CAMERA_INFO	camInfo;
  unsigned int		typesFound[ ZWO_NUM_CAMERAS + 1 ];
  int			j, cameraType, found;

  if (( numFound = ASIGetNumOfConnectedCameras()) < 1 ) {
    return 0;
  }

  for ( i = 0; i <= ZWO_NUM_CAMERAS; i++ ) {
    typesFound[i] = 0;
  }

  for ( i = 0; i < numFound; i++ ) {
    ASIGetCameraProperty ( &camInfo, i );
    currName = camInfo.Name;
    found = 0;
    for ( j = 0; !found && j < ZWO_NUM_CAMERAS; j++ ) {
      // only check the length of the string so we don't need to handle
      // names with eg. " COOL" appended
      int l = strlen ( cameraNames[j] );
      if ( !strncmp ( currName, cameraNames[j], l ) &&
          ( currName[l] == 0 || currName[l] == ' ' ||
            !strcasecmp ( currName + l, "-Cool" ))) {
        found = 1;
        cameraType = j;
      }
    }
    if ( !found ) {
      fprintf ( stderr, "Unrecognised camera '%s'\n", currName );
      cameraType = ZWOCAM_UNKNOWN;
    }

    // +1 is so ZWOCAM_UNKNOWN becomes entry 0
    typesFound[ cameraType+1 ]++;

    if (!( dev = malloc ( sizeof ( oaCameraDevice )))) {
      _oaFreeCameraDeviceList ( deviceList );
      return -OA_ERR_MEM_ALLOC;
    }
    if (!( _private = malloc ( sizeof ( DEVICE_INFO )))) {
      free (( void* ) dev );
      _oaFreeCameraDeviceList ( deviceList );
      return -OA_ERR_MEM_ALLOC;
    }
    _oaInitCameraDeviceFunctionPointers ( dev );
    dev->interface = OA_CAM_IF_ZWASI2;
    if ( typesFound[ cameraType+1 ] == 1 ) {
      ( void ) strncpy ( dev->deviceName, currName, OA_MAX_NAME_LEN );
    } else {
      snprintf ( dev->deviceName, OA_MAX_NAME_LEN, "%s #%d", currName,
          typesFound[ cameraType+1 ] );
    }
    _private->devType = cameraType;
    _private->devIndex = i;
    dev->_private = _private;
    dev->initCamera = oaZWASI2InitCamera;
    dev->hasLoadableFirmware = 0;
    if (( ret = _oaCheckCameraArraySize ( deviceList )) < 0 ) {
      free (( void* ) dev );
      free (( void* ) _private );
      _oaFreeCameraDeviceList ( deviceList );
      return ret;
    }
    deviceList->cameraList[ deviceList->numCameras++ ] = dev;
  }

  return numFound;
}
