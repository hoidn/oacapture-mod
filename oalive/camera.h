/*****************************************************************************
 *
 * camera.h -- class declaration
 *
 * Copyright 2013,2014 James Fidell (james@openastroproject.org)
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

#pragma once

#include "QtGui"

extern "C" {
#include <openastro/camera.h>
}

class Camera : public QObject
{
  public:
    			Camera();
    			~Camera();
    int			listConnected ( oaCameraDevice*** );
    int			initialise ( oaCameraDevice* );
    void		disconnect ( void );

    int			start ( void );
    void		stop ( void );
    void		releaseImageData ( void );

    int			has16Bit ( void );
    int			hasRawMode ( void );
    int			hasDemosaicMode ( void );
    int			hasBinning ( int64_t );
    int			hasROI ( void );
    int			hasControl ( int );
    int			hasAuto ( int );
    int			isAuto ( int );
    int			hasFixedFrameRates ( int, int );
    int			hasFrameRateSupport ( void );
    int			isColour ( void );
    int			isInitialised ( void );

    void		controlRange ( int, int64_t*, int64_t*, int64_t*,
                            int64_t* );
    const char*		name ( void );
    const FRAMESIZES*	frameSizes ( void );
    const FRAMERATES*	frameRates ( int, int );
    void		delayFrameRateChanges ( void );
    int			videoFramePixelFormat ( void );
    int			videoFramePixelFormat ( int );

    void		populateControlValue ( oaControlValue*, uint32_t,
				int64_t );
    int64_t		unpackControlValue ( oaControlValue* );
    int			setControl ( int, int64_t );
    int64_t		readControl ( int );
    int			getAWBManualSetting ( void );
    int			setResolution ( int, int );
    int			setROI ( int, int );
    int			setFrameInterval ( int, int );
    float		getTemperature ( void );
    int			setBitDepth ( int );
    int			setRawMode ( int );
    int			testROISize ( unsigned int, unsigned int,
				unsigned int*, unsigned int* );

    const char*		getMenuString ( int, int );

  private:

    oaCamera*		cameraContext;
    int			initialised;
    int			framePixelFormat;
};
