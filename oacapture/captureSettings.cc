/*****************************************************************************
 *
 * captureSettings.cc -- class for the capture tab in the settings dialog
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

#include <oa_common.h>

extern "C" {
#ifdef HAVE_FITSIO_H 
#include "fitsio.h"
#else
#ifdef HAVE_CFITSIO_FITSIO_H
#include "cfitsio/fitsio.h"
#endif
#endif
}

#include "captureSettings.h"
#include "state.h"

#define FLEN_VALUE     71

CaptureSettings::CaptureSettings ( QWidget* parent ) : QWidget ( parent )
{
  indexResetButton = new QPushButton ( tr ( "Reset capture counter" ), this );
  winAVIBox = new QCheckBox (
      tr ( "Use Windows-compatible format for AVI files "
      "(8-bit mono/raw colour)" ), this );
  winAVIBox->setChecked ( config.windowsCompatibleAVI );

  utVideoBox = new QCheckBox (
      tr ( "Use UtVideo lossless compression for AVI files where possible" ),
      this );
  utVideoBox->setChecked ( config.useUtVideo );

  fitsLabel = new QLabel ( tr ( "FITS data" ), this );
  observerLabel = new QLabel ( tr ( "Observer" ), this );
  telescopeLabel = new QLabel ( tr ( "Telescope" ), this );
  instrumentLabel = new QLabel ( tr ( "Instrument" ), this );
  objectLabel = new QLabel ( tr ( "Object" ), this );
  commentLabel = new QLabel ( tr ( "Comments" ), this );

  observerInput = new QLineEdit ( this );
  observerInput->setMaxLength ( FLEN_VALUE );
  observerInput->setText ( config.fitsObserver );
  connect ( observerInput, SIGNAL( editingFinished()), parent,
      SLOT( dataChanged()));

  telescopeInput = new QLineEdit ( this );
  telescopeInput->setMaxLength ( FLEN_VALUE );
  telescopeInput->setText ( config.fitsTelescope );
  connect ( telescopeInput, SIGNAL( editingFinished()), parent,
      SLOT( dataChanged()));

  instrumentInput = new QLineEdit ( this );
  instrumentInput->setMaxLength ( FLEN_VALUE );
  instrumentInput->setText ( config.fitsInstrument );
  connect ( instrumentInput, SIGNAL( editingFinished()), parent,
      SLOT( dataChanged()));

  objectInput = new QLineEdit ( this );
  objectInput->setMaxLength ( FLEN_VALUE );
  objectInput->setText ( config.fitsObject );
  connect ( objectInput, SIGNAL( editingFinished()), parent,
      SLOT( dataChanged()));

  commentInput = new QLineEdit ( this );
  commentInput->setMaxLength ( FLEN_VALUE );
  connect ( commentInput, SIGNAL( editingFinished()), parent,
      SLOT( dataChanged()));
  commentInput->setText ( config.fitsComment );

#ifdef HAVE_LIBCFITSIO
  grid = new QGridLayout;
  grid->addWidget ( observerLabel, 0, 0 );
  grid->addWidget ( observerInput, 0, 1 );
  grid->addWidget ( telescopeLabel, 1, 0 );
  grid->addWidget ( telescopeInput, 1, 1 );
  grid->addWidget ( instrumentLabel, 2, 0 );
  grid->addWidget ( instrumentInput, 2, 1 );
  grid->addWidget ( objectLabel, 3, 0 );
  grid->addWidget ( objectInput, 3, 1 );
  grid->addWidget ( commentLabel, 4, 0 );
  grid->addWidget ( commentInput, 4, 1 );
#endif

  hLayout = new QHBoxLayout ( this );
  vLayout = new QVBoxLayout();
  vLayout->addWidget ( indexResetButton );
  vLayout->addWidget ( winAVIBox );
  vLayout->addWidget ( utVideoBox );
#ifdef HAVE_LIBCFITSIO
  vLayout->addStretch ( 1 );
  vLayout->addWidget ( fitsLabel );
  vLayout->addLayout ( grid );
#endif
  vLayout->addStretch ( 1 );
  hLayout->addLayout ( vLayout );
  hLayout->addStretch ( 1 );

  setLayout ( hLayout );
  connect ( indexResetButton, SIGNAL ( clicked()), this,
      SLOT ( resetIndex()));
  connect ( winAVIBox, SIGNAL ( stateChanged ( int )), parent,
      SLOT ( dataChanged()));
  connect ( utVideoBox, SIGNAL ( stateChanged ( int )), parent,
      SLOT ( dataChanged()));
}


CaptureSettings::~CaptureSettings()
{
  state.mainWindow->destroyLayout (( QLayout* ) vLayout );
}


void
CaptureSettings::storeSettings ( void )
{
  config.windowsCompatibleAVI = winAVIBox->isChecked() ? 1 : 0;
  config.useUtVideo = utVideoBox->isChecked() ? 1 : 0;
  config.fitsObserver = observerInput->text();
  config.fitsTelescope = telescopeInput->text();
  config.fitsInstrument = instrumentInput->text();
  config.fitsObject = objectInput->text();
  config.fitsComment = commentInput->text();
}


void
CaptureSettings::resetIndex ( void )
{
  // FIX ME -- this might not be good in the middle of a capture run
  state.captureIndex = 0;
}
