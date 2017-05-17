/*****************************************************************************
 *
 * camera.cc -- camera interface class
 *
 * Copyright 2013,2014,2015 James Fidell (james@openastroproject.org)
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

#include "camera.h"
#include "configuration.h"
#include "state.h"
#include "version.h"

#define	DEFAULT_FRAME_TIME	100

#define cameraFuncs	cameraContext->funcs
#define cameraControls	cameraContext->controls
#define cameraFeatures	cameraContext->features

Camera::Camera()
{
  initialised = 0;
  framePixelFormat = OA_PIX_FMT_RGB24; // the default
}


Camera::~Camera()
{
  if ( initialised ) {
    stop();
    disconnect();
  }
}


void
Camera::populateControlValue ( oaControlValue* cp, uint32_t c, int64_t v )
{
  cp->valueType = cameraControls[ c ];
  switch ( cameraControls[ c ] ) {
    case OA_CTRL_TYPE_INT32:
      cp->int32 = v & 0xffffffff;
      break;
    case OA_CTRL_TYPE_BOOLEAN:
      cp->boolean = v ? 1 : 0;
      break;
    case OA_CTRL_TYPE_MENU:
      cp->menu = v & 0xffffffff;
      break;
    case OA_CTRL_TYPE_BUTTON:
      break;
    case OA_CTRL_TYPE_INT64:
      cp->int64 = v;
      break;
    case OA_CTRL_TYPE_DISCRETE:
      cp->discrete = v & 0xffffffff;
      break;
    default:
      qWarning() << __FUNCTION__ << " called with invalid control type " <<
        cameraControls[ c ] << " for control " << c;
  }
}


int64_t
Camera::unpackControlValue ( oaControlValue *cp )
{
  int64_t res;

  switch ( cp->valueType ) {
    case OA_CTRL_TYPE_INT32:
      res = cp->int32;
      break;
    case OA_CTRL_TYPE_BOOLEAN:
      res = cp->boolean;
      break;
    case OA_CTRL_TYPE_MENU:
      res = cp->menu;
      break;
    case OA_CTRL_TYPE_READONLY:
      res = cp->readonly;
      break;
    case OA_CTRL_TYPE_INT64:
      res = cp->int64;
      // FIX ME -- because at the moment Qt controls can only handle 32-bit
      // values
      res &= 0xffffffff;
      break;
    case OA_CTRL_TYPE_DISCRETE:
      res = cp->discrete;
      break;
    default:
      qWarning() << __FUNCTION__ << " called with invalid control type " <<
        cameraControls[ cp->valueType ];
      res = -1;
  }

  return res;
}


int
Camera::has16Bit ( void )
{
  oaControlValue v;

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  // FIX ME -- this assumes that we don't have a 16-bit mode if the bit
  // depth can't be changed which may not be true at all.

  if ( !cameraControls[ OA_CAM_CTRL_BIT_DEPTH ] ) {
    return 0;
  }
  populateControlValue ( &v, OA_CAM_CTRL_BIT_DEPTH, 16 );
  return ( OA_ERR_NONE == cameraFuncs.testControl ( cameraContext,
    OA_CAM_CTRL_BIT_DEPTH, &v )) ? 1 : 0;
}


int
Camera::hasBinning ( int64_t factor )
{
  oaControlValue v;

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  if ( !cameraControls[ OA_CAM_CTRL_BINNING ] ) {
    return 0;
  }
  populateControlValue ( &v, OA_CAM_CTRL_BINNING, factor );
  return ( OA_ERR_NONE == cameraFuncs.testControl ( cameraContext,
      OA_CAM_CTRL_BINNING, &v )) ? 1 : 0;
}


int
Camera::testROISize ( unsigned int xRes, unsigned int yRes,
    unsigned int* suggX, unsigned int* suggY )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }

  return cameraFuncs.testROISize ( cameraContext, xRes, yRes, suggX, suggY );
}


int
Camera::hasROI ( void )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  return cameraFeatures.ROI;
}


int
Camera::hasFrameRateSupport ( void )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  return cameraFeatures.frameRates;
}


int
Camera::hasFixedFrameRates ( int xRes, int yRes )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }

  return cameraFeatures.frameRates;
}


int
Camera::hasControl ( int control )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }

  if ( control >= 0 && control < OA_CAM_CTRL_LAST_P1 ) {
    return cameraControls[ control ];
  }
  qWarning() << __FUNCTION__ << " unrecognised control" << control;
  return 0;
}


int
Camera::hasAuto ( int control )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }

  if ( control >= 0 && control < OA_CAM_CTRL_LAST_P1 ) {
    return cameraFuncs.hasAuto ( cameraContext, control );
  }
  qWarning() << __FUNCTION__ << " unrecognised control";
  return 0;
}


int
Camera::isAuto ( int control )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  } 

  if ( control >= 0 && control < OA_CAM_CTRL_LAST_P1 ) {
    return cameraFuncs.isAuto ( cameraContext, control );
  }
  qWarning() << __FUNCTION__ << " unrecognised control";
  return 0;
}


int
Camera::isColour ( void )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  return ( cameraFeatures.rawMode | cameraFeatures.demosaicMode );
}


float
Camera::getTemperature ( void )
{
  oaControlValue v;

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  if ( !cameraControls[ OA_CAM_CTRL_TEMPERATURE ]) {
    return -273.15;
  }
  cameraFuncs.readControl ( cameraContext, OA_CAM_CTRL_TEMPERATURE, &v );
  float tempReading = v.int32;
  tempReading /= 10;
  return tempReading;
}


const char*
Camera::name()
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return "";
  }
  return cameraContext->deviceName;
}


void
Camera::controlRange ( int control, int64_t* min, int64_t* max,
    int64_t* step, int64_t* def )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
  } else {
    cameraFuncs.getControlRange ( cameraContext, control, min, max, step, def );
  }
  // FIX ME -- this is because the sliders can't handle more than 32-bit
  // values
  *min &= 0xffffffff;
  *max &= 0xffffffff;
  *step &= 0xffffffff;
  *def &= 0xffffffff;
  return;
}


const FRAMESIZES*
Camera::frameSizes ( void )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  return cameraFuncs.enumerateFrameSizes ( cameraContext );
}


// FIX ME -- might be nice to make this a tidier type at some point.  vector?
const FRAMERATES*
Camera::frameRates ( int xRes, int yRes)
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  return cameraFuncs.enumerateFrameRates ( cameraContext, xRes, yRes );
}


// FIX ME -- might be nice to make this a tidier type at some point.  vector?
int
Camera::listConnected ( oaCameraDevice*** devs )
{
  return ( oaGetCameras ( devs ));
}


// FIX ME -- handling of the return code here is really scabby.  Do it
// properly at some point

int
Camera::initialise ( oaCameraDevice* device )
{
  int ret;

  disconnect();

  if ( !device ) {
    qWarning() << "device is null!";
    return -1;
  }

  // At the moment this is really just for OSX
  if ( device->hasLoadableFirmware && !device->firmwareLoaded ) {

    QMessageBox* loading = new QMessageBox ( QMessageBox::NoIcon,
        APPLICATION_NAME, tr ( "Attempting to load camera firmware" ),
        QMessageBox::NoButton, state.mainWindow );
    QAbstractButton* b = loading->button ( QMessageBox::Ok );
    if ( b ) {
      loading->removeButton ( b );
    }
    QApplication::setOverrideCursor ( Qt::WaitCursor );
    loading->show();
    ret = device->loadFirmware ( device );
    QApplication::restoreOverrideCursor();
    loading->hide();
    delete loading;

    if ( ret != OA_ERR_NONE ) {
      switch ( -ret ) {

        case OA_ERR_RESCAN_BUS:
          return 1;
          break;

        case OA_ERR_MANUAL_FIRMWARE:
          QMessageBox::warning ( state.mainWindow, APPLICATION_NAME,
              tr ( "The firmware could not be loaded.  It must be loaded "
              "manually." ));
          break;

        case OA_ERR_FXLOAD_NOT_FOUND:
          QMessageBox::warning ( state.mainWindow, APPLICATION_NAME,
              tr ( "The firmware could not be loaded.  The fxload utility "
              "was not found." ));
          break;

        case OA_ERR_FXLOAD_ERROR:
          QMessageBox::warning ( state.mainWindow, APPLICATION_NAME,
              tr ( "The firmware could not be loaded.  The fxload utility "
              "returned an error." ));
          break;

        case OA_ERR_FIRMWARE_UNKNOWN:
          QMessageBox::warning ( state.mainWindow, APPLICATION_NAME,
              tr ( "The firmware could not be found." ));
          break;

        default:
          QMessageBox::warning ( state.mainWindow, APPLICATION_NAME,
              tr ( "Unexpected error loading firmware." ));
          break;
      }

      return -1;
    }
  }

  if (( cameraContext = device->initCamera ( device ))) {
    initialised = 1;
    framePixelFormat = cameraFuncs.getFramePixelFormat ( cameraContext, 0 );
    return 0;
  }
  return -1;
}


void
Camera::disconnect ( void )
{
  if ( initialised ) {
    cameraFuncs.closeCamera ( cameraContext );
    initialised = 0;
  }
}


int
Camera::setControl ( int control, int64_t value )
{
  oaControlValue v;

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }

  populateControlValue ( &v, control, value );
  return cameraFuncs.setControl ( cameraContext, control, &v );
}


int64_t
Camera::readControl ( int control )
{
  oaControlValue v;

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }

  cameraFuncs.readControl ( cameraContext, control, &v );
  return unpackControlValue ( &v );
}


int
Camera::setResolution ( int x, int y )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }

  return cameraFuncs.setResolution ( cameraContext, x, y );
}


int
Camera::setROI ( int x, int y )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }

  return cameraFuncs.setROI ( cameraContext, x, y );
}


int
Camera::setFrameInterval ( int numerator, int denominator )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }

  return cameraFuncs.setFrameInterval ( cameraContext, numerator,
      denominator );
}


int
Camera::start ( void )
{
  void* (*callback )(void*, void*, int);

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }

  callback = ( void* (*)(void*, void*, int)) &ViewWidget::addImage;
  return cameraFuncs.startStreaming ( cameraContext, callback, &state );
}


void
Camera::stop ( void )
{
  if ( !initialised ) {
    return;
  }

  if ( cameraFuncs.isStreaming ( cameraContext )) {
    cameraFuncs.stopStreaming ( cameraContext );
  }
}


int
Camera::videoFramePixelFormat ( void )
{
  return framePixelFormat;
}


int
Camera::setBitDepth ( int depth )
{
  int ret;
  oaControlValue v;

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }

  populateControlValue ( &v, OA_CAM_CTRL_BIT_DEPTH, depth );
  ret = cameraFuncs.setControl ( cameraContext, OA_CAM_CTRL_BIT_DEPTH, &v );
  framePixelFormat = cameraFuncs.getFramePixelFormat ( cameraContext, 0 );
  return ret;
}


int
Camera::setRawMode ( int enabled )
{
  int ret;
  oaControlValue v;

  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }

  populateControlValue ( &v, OA_CAM_CTRL_COLOUR_MODE,
      enabled ? OA_COLOUR_MODE_RAW : OA_COLOUR_MODE_NONRAW );
  ret = cameraFuncs.setControl ( cameraContext, OA_CAM_CTRL_COLOUR_MODE, &v );
  framePixelFormat = cameraFuncs.getFramePixelFormat ( cameraContext, 0 );
  return ret;
}


int
Camera::videoFramePixelFormat ( int depth )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return -1;
  }
  return cameraFuncs.getFramePixelFormat ( cameraContext, depth );
}


int
Camera::isInitialised ( void )
{
  return initialised;
}


int
Camera::hasRawMode ( void )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
  }
  return initialised ? cameraFeatures.rawMode : 0;
}


int
Camera::hasDemosaicMode ( void )
{
  if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
  }
  return initialised ? cameraFeatures.demosaicMode : 0;
}


const char*
Camera::getMenuString ( int control, int index )
{
 if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return "";
  }
  return cameraFuncs.getMenuString ( cameraContext, control, index );
}


int
Camera::getAWBManualSetting ( void )
{
 if ( !initialised ) {
    qWarning() << __FUNCTION__ << " called with camera uninitialised";
    return 0;
  }
  return cameraFuncs.getAutoWBManualSetting ( cameraContext );
}
