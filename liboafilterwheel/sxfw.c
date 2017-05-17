/*****************************************************************************
 *
 * sxfw.c -- Control Starlight Xpress filter wheels
 *
 * Copyright 2014,2015 James Fidell (james@openastroproject.org)
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

#include <errno.h>
#include <hidapi.h>
#include <libusb-1.0/libusb.h>

#include <openastro/util.h>
#include <openastro/filterwheel.h>

#include "oafwprivate.h"
#include "unimplemented.h"
#include "sxfw.h"

int
oaSXGetFilterWheels ( FILTERWHEEL_LIST* deviceList )
{
  int                                   numFound = 0, numUSBDevices, i;
  int					ret;
  libusb_context*                       ctx = 0;
  libusb_device**                       devlist;
  libusb_device*                        device;
  struct libusb_device_descriptor       desc;
  oaFilterWheelDevice*			wheel;
  unsigned short			busNum, addr;
  unsigned int				index;
  DEVICE_INFO*				_private;

  libusb_init ( &ctx );
  // libusb_set_debug ( ctx, LIBUSB_LOG_LEVEL_DEBUG );
  numUSBDevices = libusb_get_device_list ( ctx, &devlist );
  if ( numUSBDevices < 1 ) {
    libusb_free_device_list ( devlist, 1 );
    libusb_exit ( ctx );
    if ( numUSBDevices ) {
      fprintf ( stderr, "libusb_get_device_list() failed in %s\n",
          __FUNCTION__ );
      return -OA_ERR_SYSTEM_ERROR;
    }
    return OA_ERR_NONE;
  }

  for ( i = 0; i < numUSBDevices; i++ ) {
    device = devlist[i];
    if ( LIBUSB_SUCCESS != libusb_get_device_descriptor ( device, &desc )) {
      libusb_free_device_list ( devlist, 1 );
      libusb_exit ( ctx );
      fprintf ( stderr, "libusb_get_device_descriptor() failed in %s\n",
          __FUNCTION__ );
      return -OA_ERR_SYSTEM_ERROR;
    }
    busNum = libusb_get_bus_number ( device );
    addr = libusb_get_device_address ( device );
    index = ( busNum << 8 ) | addr;

    if ( desc.idVendor == STARLIGHT_XPRESS_VID &&
        desc.idProduct == STARLIGHT_XPRESS_FILTERWHEEL_PID ) {

      if (!( wheel = malloc ( sizeof ( oaFilterWheelDevice )))) {
        _oaFreeFilterWheelDeviceList ( deviceList );
        libusb_free_device_list ( devlist, 1 );
        libusb_exit ( ctx );
        return -OA_ERR_MEM_ALLOC;
      }
      if (!( _private = malloc ( sizeof ( DEVICE_INFO )))) {
        free (( void* ) wheel );
        _oaFreeFilterWheelDeviceList ( deviceList );
        libusb_free_device_list ( devlist, 1 );
        libusb_exit ( ctx );
        return -OA_ERR_MEM_ALLOC;
      }
      _oaInitFilterWheelDeviceFunctionPointers ( wheel );
      wheel->interface = OA_FW_IF_SX;
      _private->devIndex = index;
      // Don't know of any other types at the moment
      ( void ) strcpy ( wheel->deviceName,
          "Starlight Xpress Universal Wheel" );
      _private->devType = SX_UNIVERSAL;
      _private->vendorId = STARLIGHT_XPRESS_VID;
      _private->productId = STARLIGHT_XPRESS_FILTERWHEEL_PID;
      wheel->_private = _private;
      wheel->initFilterWheel = oaSXInitFilterWheel;
      if (( ret = _oaCheckFilterWheelArraySize ( deviceList )) < 0 ) {
        free (( void* ) wheel );
        free (( void* ) _private );
        libusb_free_device_list ( devlist, 1 );
        libusb_exit ( ctx );
        _oaFreeFilterWheelDeviceList ( deviceList );
        return ret;
      }
      deviceList->wheelList[ deviceList->numFilterWheels++ ] = wheel;
      numFound++;
    }
  }

  libusb_free_device_list ( devlist, 1 );
  libusb_exit ( ctx );

  return numFound;
}


const char*
oaSXWheelGetName ( oaFilterWheel* wheel )
{
  return wheel->deviceName;
}
