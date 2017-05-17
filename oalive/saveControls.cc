/*****************************************************************************
 *
 * saveControls.cc -- class for the save data tab in the settings dialog
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

extern "C" {
#ifdef HAVE_FITSIO_H 
#include "fitsio.h"
#else
#ifdef HAVE_CFITSIO_FITSIO_H
#include "cfitsio/fitsio.h" 
#endif
#endif
}


#include "saveControls.h"
#include "state.h"
#ifdef HAVE_LIBCFITSIO
#include "outputFITS.h"
#endif
#include "outputTIFF.h"

#ifdef HAVE_LIBCFITSIO
#define MAX_FILE_FORMATS        3
static QString  fileFormats[MAX_FILE_FORMATS] = {
    "", "TIFF", "FITS"
};
#else
#define MAX_FILE_FORMATS        2
static QString  fileFormats[MAX_FILE_FORMATS] = {
    "", "TIFF"
};
#endif

#define FLEN_VALUE     71

SaveControls::SaveControls ( QWidget* parent ) : QWidget ( parent )
{
  typeLabel = new QLabel ( tr ( "Saved file type:" ), this );
  typeMenu = new QComboBox ( this );
  for ( int i = 1; i < MAX_FILE_FORMATS; i++ ) {
    QVariant v(i);
    typeMenu->addItem ( fileFormats[i], v );
  }
  typeMenu->setCurrentIndex ( config.fileTypeOption - 1 );
  connect ( typeMenu, SIGNAL( currentIndexChanged ( int )), this,
      SLOT( fileTypeChanged ( int )));

  saveEachFrame = new QCheckBox ( tr ( "Save each frame" ), this );
  saveEachFrame->setChecked ( config.saveEachFrame );
  connect ( saveEachFrame, SIGNAL( stateChanged ( int )), this,
      SLOT( updateSaveEachFrame ( int )));

  saveProcessedImage = new QCheckBox ( tr ( "Save each processed Image" ), this );
  saveProcessedImage->setChecked ( config.saveProcessedImage );
  connect ( saveProcessedImage, SIGNAL( stateChanged ( int )), this,
      SLOT( updateSaveProcessedImage ( int )));

  frameLabel = new QLabel ( tr ( "Frame filename template" ), this );
  frameFilename = new QLineEdit ( this );
  frameFilename->setText ( config.frameFileNameTemplate );
  connect ( frameFilename, SIGNAL( editingFinished()), this,
      SLOT( updateFrameFilename()));

  processedLabel = new QLabel ( tr ( "Processed image filename template" ),
      this );
  processedFilename = new QLineEdit ( this );
  processedFilename->setText ( config.processedFileNameTemplate );
  connect ( processedFilename, SIGNAL( editingFinished()), this,
      SLOT( updateProcessedFilename()));

  newFolderButton = new QPushButton (
      QIcon ( ":/icons/folder-new-7.png" ), "", this );
  newFolderButton->setToolTip ( tr ( "Select a new capture directory" ));
  connect ( newFolderButton, SIGNAL( clicked()), this,
      SLOT( setNewCaptureDirectory()));

  openFolderButton = new QPushButton (
      QIcon ( ":/icons/folder-open-4.png" ), "", this );
  openFolderButton->setToolTip ( tr ( "View capture directory" ));
  connect ( openFolderButton, SIGNAL( clicked()), this,
      SLOT( openCaptureDirectory()));

  titleLabel = new QLabel ( tr ( "FITS data" ), this );
  observerLabel = new QLabel ( tr ( "Observer" ), this );
  telescopeLabel = new QLabel ( tr ( "Telescope" ), this );
  instrumentLabel = new QLabel ( tr ( "Instrument" ), this );
  objectLabel = new QLabel ( tr ( "Object" ), this );
  commentLabel = new QLabel ( tr ( "Comments" ), this );

  observerInput = new QLineEdit ( this );
  observerInput->setMaxLength ( FLEN_VALUE );
  observerInput->setText ( config.fitsObserver );
  connect ( observerInput, SIGNAL( editingFinished()), this,
      SLOT( updateObserver()));

  telescopeInput = new QLineEdit ( this );
  telescopeInput->setMaxLength ( FLEN_VALUE );
  telescopeInput->setText ( config.fitsTelescope );
  connect ( telescopeInput, SIGNAL( editingFinished()), this,
      SLOT( updateTelescope()));

  instrumentInput = new QLineEdit ( this );
  instrumentInput->setMaxLength ( FLEN_VALUE );
  instrumentInput->setText ( config.fitsInstrument );
  connect ( instrumentInput, SIGNAL( editingFinished()), this,
      SLOT( updateInstrument()));

  objectInput = new QLineEdit ( this );
  objectInput->setMaxLength ( FLEN_VALUE );
  objectInput->setText ( config.fitsObject );
  connect ( objectInput, SIGNAL( editingFinished()), this,
      SLOT( updateObject()));

  commentInput = new QLineEdit ( this );
  commentInput->setMaxLength ( FLEN_VALUE );
  connect ( commentInput, SIGNAL( editingFinished()), this,
      SLOT( updateComment()));
  commentInput->setText ( config.fitsComment );

  typeBox = new QHBoxLayout;
  typeBox->addWidget ( typeLabel );
  typeBox->addWidget ( typeMenu );

  dirButtonBox = new QHBoxLayout;
  dirButtonBox->addWidget ( newFolderButton );
  dirButtonBox->addWidget ( openFolderButton );

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
  grid->setRowStretch ( 5, 1 );

  layout = new QVBoxLayout;
  layout->addLayout ( typeBox );
  layout->addWidget ( saveEachFrame );
  layout->addWidget ( frameLabel );
  layout->addWidget ( frameFilename );
  layout->addWidget ( saveProcessedImage );
  layout->addWidget ( processedLabel );
  layout->addWidget ( processedFilename );
  layout->addLayout ( dirButtonBox );
  layout->addWidget ( titleLabel );
  layout->addLayout ( grid );

  setLayout ( layout );
}


SaveControls::~SaveControls()
{
  if ( layout ) {
    state.mainWindow->destroyLayout (( QLayout* ) layout );
  }
}


void
SaveControls::updateObserver ( void )
{
  config.fitsObserver = observerInput->text();
}


void
SaveControls::updateTelescope ( void )
{
  config.fitsTelescope = telescopeInput->text();
}


void
SaveControls::updateInstrument ( void )
{
  config.fitsInstrument = instrumentInput->text();
}


void
SaveControls::updateObject ( void )
{
  config.fitsObject = objectInput->text();
}


void
SaveControls::updateComment ( void )
{
  config.fitsComment = commentInput->text();
}


void
SaveControls::updateFrameFilename ( void )
{
  config.frameFileNameTemplate = frameFilename->text();
}


void
SaveControls::updateProcessedFilename ( void )
{
  config.processedFileNameTemplate = processedFilename->text();
}


void
SaveControls::updateSaveEachFrame ( int state )
{
  config.saveEachFrame = state;
}


void
SaveControls::updateSaveProcessedImage ( int state )
{
  config.saveProcessedImage = state;
}


void
SaveControls::setNewCaptureDirectory ( void )
{
  QFileDialog dialog( this );

  dialog.setFileMode ( QFileDialog::Directory );
  dialog.setOption ( QFileDialog::ShowDirsOnly );
  if ( config.captureDirectory != "" ) {
    dialog.setDirectory ( config.captureDirectory );
  } else {
    dialog.setDirectory ( "." );
  }
  dialog.setWindowTitle ( tr ( "Select capture directory" ));
  int done = 0;
  while ( !done ) {
    if ( dialog.exec()) {
      QStringList names = dialog.selectedFiles();
      if ( !access ( names[0].toStdString().c_str(), W_OK | R_OK )) {
        config.captureDirectory = names[0];
        done = 1;
      } else {
        QMessageBox err;
        err.setText ( tr (
            "The selected directory is not writable/accessible" ));
        err.setInformativeText ( tr ( "Select another?" ));
        err.setStandardButtons ( QMessageBox::No | QMessageBox::Yes );
        err.setDefaultButton ( QMessageBox::Yes );
        int ret = err.exec();
        done = ( ret == QMessageBox::Yes ) ? 0 : 1;
      }
    } else {
      done = 1;
    }
  }
}


void
SaveControls::openCaptureDirectory ( void )
{
  QFileDialog dialog( this );

  dialog.setFileMode ( QFileDialog::AnyFile );
  if ( config.captureDirectory != "" ) {
    dialog.setDirectory ( config.captureDirectory );
  } else {
    dialog.setDirectory ( "." );
  }
  dialog.setWindowTitle ( tr ( "Capture directory" ));
  dialog.exec();
}


void
SaveControls::fileTypeChanged ( int index )
{
  QVariant v = typeMenu->itemData ( index );
  config.fileTypeOption = v.toInt();
  if ( CAPTURE_TIFF == config.fileTypeOption ||
      CAPTURE_FITS == config.fileTypeOption ) {
    if ( !config.frameFileNameTemplate.contains ( "%INDEX" ) &&
        !config.frameFileNameTemplate.contains ( "%I" ) &&
        !config.processedFileNameTemplate.contains ( "%INDEX" ) &&
        !config.processedFileNameTemplate.contains ( "%I" )) {
      QMessageBox::warning ( this, APPLICATION_NAME,
          tr ( "The " ) + fileFormats[ config.fileTypeOption ] +
          tr ( " file format is selected, but the filename templates do "
          "not both contain either the \"%INDEX\" or \"%I\" pattern.  Output "
          "files may therefore overwrite each other" ));
    }
  }
}
