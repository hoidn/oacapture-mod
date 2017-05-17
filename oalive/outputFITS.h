/*****************************************************************************
 *
 * outputFITS.h -- class declaration
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

#pragma once

#include "outputHandler.h"

class OutputFITS : public OutputHandler
{
  public:
    			OutputFITS ( int, int, int, int, int, QString );
    			~OutputFITS();
    int			openOutput ( void );
    int			addFrame ( void*, const char* );
    void		closeOutput ( void );
    int			outputExists ( void );
    int			outputWritable ( void );

  private:
    int			xSize;
    int			ySize;
    int			validFileType;
    int			reverseByteOrder;
    int			swapRedBlue;
    int			frameSize;
    unsigned char*	writeBuffer;
    int			nAxes;
    int			bitpix;
    int			tableType;
    int			bytesPerPixel;
    int			splitPlanes;
    int                 rowLength;
    int                 totalRows;
    int                 planeDepth;
    int			elements;
    long		fitsAxes[3];
};
