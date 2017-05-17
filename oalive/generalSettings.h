/*****************************************************************************
 *
 * generalSettings.h -- class declaration
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

#pragma once

#include "qtgui_all_includes.h"

#include "version.h"


class GeneralSettings : public QWidget
{
  Q_OBJECT

  public:
    			GeneralSettings ( QWidget* );
    			~GeneralSettings();
    void		storeSettings ( void );

  private:
    QCheckBox*		saveBox;
    QCheckBox*		saveCaptureSettings;
    QCheckBox*		connectSole;
    QVBoxLayout*	box;
    QVBoxLayout*	leftBox;
    QVBoxLayout*	rightBox;
    QHBoxLayout*	topBox;

    QHBoxLayout*	reticlebox;
    QButtonGroup*	reticleButtons;
    QRadioButton*	circleButton;
    QRadioButton*	crossButton;
    QRadioButton*	tramlineButton;
    QButtonGroup*	tempButtons;
    QRadioButton*	degCButton;
    QRadioButton*	degFButton;
    QPushButton*	recentreButton;
    QPushButton*	derotateButton;

  public slots:
    // void		updateFPSLabel ( int );
};
