/*****************************************************************************
 *
 * oacam-controls.h -- camera API (sub)header for camera controls
 *
 * Copyright 2014,2015,2016 James Fidell (james@openastroproject.org)
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

#ifndef OPENASTRO_CAMERA_CONTROLS_H
#define OPENASTRO_CAMERA_CONTROLS_H

#define	OA_CAM_CTRL_BRIGHTNESS			1
#define	OA_CAM_CTRL_CONTRAST			2
#define	OA_CAM_CTRL_SATURATION			3
#define	OA_CAM_CTRL_HUE				4
#define	OA_CAM_CTRL_AUTO_WHITE_BALANCE		5
#define	OA_CAM_CTRL_WHITE_BALANCE		6
#define	OA_CAM_CTRL_BLUE_BALANCE		7
#define	OA_CAM_CTRL_RED_BALANCE			8
#define	OA_CAM_CTRL_GAMMA			9
#define	OA_CAM_CTRL_EXPOSURE			10
#define	OA_CAM_CTRL_AUTO_GAIN			11
#define	OA_CAM_CTRL_GAIN			12
#define	OA_CAM_CTRL_HFLIP			13
#define	OA_CAM_CTRL_VFLIP			14
#define	OA_CAM_CTRL_POWER_LINE_FREQ		15
#define	OA_CAM_CTRL_HUE_AUTO			16
#define	OA_CAM_CTRL_WHITE_BALANCE_TEMP		17
#define	OA_CAM_CTRL_SHARPNESS			18
#define	OA_CAM_CTRL_BACKLIGHT_COMPENSATION	19
#define	OA_CAM_CTRL_CHROMA_AGC			20
#define	OA_CAM_CTRL_COLOUR_KILLER		21
#define	OA_CAM_CTRL_COLOR_KILLER		OA_CAM_CTRL_COLOUR_KILLER
#define	OA_CAM_CTRL_COLOURFX			22
#define	OA_CAM_CTRL_COLORFX			OA_CAM_CTRL_COLOURFX
#define	OA_CAM_CTRL_AUTO_BRIGHTNESS		23
#define	OA_CAM_CTRL_BAND_STOP_FILTER		24
#define	OA_CAM_CTRL_ROTATE			25
#define	OA_CAM_CTRL_BG_COLOUR			26
#define	OA_CAM_CTRL_BG_COLOR			OA_CAM_CTRL_BG_COLOUR
#define	OA_CAM_CTRL_CHROMA_GAIN			27
#define	OA_CAM_CTRL_MIN_BUFFERS_FOR_CAPTURE	28
#define	OA_CAM_CTRL_ALPHA_COMPONENT		29
#define	OA_CAM_CTRL_COLOURFX_CBCR		30
#define	OA_CAM_CTRL_COLORFX_CBCR		OA_CAM_CTRL_COLOURFX_CBCR
#define OA_CAM_CTRL_AUTO_EXPOSURE		31
#define OA_CAM_CTRL_EXPOSURE_ABSOLUTE		32
#define	OA_CAM_CTRL_PAN_RELATIVE		33
#define	OA_CAM_CTRL_TILT_RELATIVE		34
#define OA_CAM_CTRL_PAN_RESET			35
#define OA_CAM_CTRL_TILT_RESET			36
#define OA_CAM_CTRL_PAN_ABSOLUTE		37
#define OA_CAM_CTRL_TILT_ABSOLUTE		38
#define OA_CAM_CTRL_ZOOM_ABSOLUTE		39
#define	OA_CAM_CTRL_BACKLIGHT			40
#define	OA_CAM_CTRL_BLACKLEVEL			41
#define	OA_CAM_CTRL_GAIN2X			42
#define	OA_CAM_CTRL_GAINBOOST			43
#define	OA_CAM_CTRL_HDR				44
#define	OA_CAM_CTRL_HPC				45
#define	OA_CAM_CTRL_HIGHSPEED			46
#define	OA_CAM_CTRL_LOWNOISE			47
#define	OA_CAM_CTRL_PIXELCLOCK			48
#define	OA_CAM_CTRL_COLOUR_MODE			49
#define	OA_CAM_CTRL_COLOR_MODE			OA_CAM_CTRL_COLOUR_MODE
#define	OA_CAM_CTRL_ROLLING_SHUTTER		50
#define	OA_CAM_CTRL_SHUTTER			51
#define	OA_CAM_CTRL_SIGNAL_BOOST		52
#define	OA_CAM_CTRL_SUBS_VOLTAGE		53
#define	OA_CAM_CTRL_TEMP_SETPOINT		54
#define	OA_CAM_CTRL_USBTRAFFIC			55
#define	OA_CAM_CTRL_BIT_DEPTH			56
#define	OA_CAM_CTRL_AUTO_GAMMA			57
#define	OA_CAM_CTRL_AUTO_RED_BALANCE		58
#define	OA_CAM_CTRL_AUTO_BLUE_BALANCE		59
#define	OA_CAM_CTRL_BINNING			60
#define	OA_CAM_CTRL_AUTO_USBTRAFFIC		61
#define	OA_CAM_CTRL_TEMPERATURE			62
#define	OA_CAM_CTRL_GREEN_BALANCE		63
#define	OA_CAM_CTRL_AUTO_GREEN_BALANCE		64
#define OA_CAM_CTRL_CONTOUR			65
#define OA_CAM_CTRL_AUTO_CONTOUR		66
#define OA_CAM_CTRL_NOISE_REDUCTION		67
#define OA_CAM_CTRL_SAVE_USER			68
#define OA_CAM_CTRL_RESTORE_USER		69
#define OA_CAM_CTRL_RESTORE_FACTORY		70
#define OA_CAM_CTRL_AUTO_WB_SPEED		71
#define OA_CAM_CTRL_AUTO_WB_DELAY		72
#define OA_CAM_CTRL_DROPPED			73
#define OA_CAM_CTRL_DROPPED_RESET		74
#define	OA_CAM_CTRL_AUTO_WHITE_BALANCE_TEMP	75
#define	OA_CAM_CTRL_AUTO_CONTRAST		76
#define	OA_CAM_CTRL_OVERCLOCK			77
#define	OA_CAM_CTRL_AUTO_OVERCLOCK		78
#define	OA_CAM_CTRL_COOLER			79
#define	OA_CAM_CTRL_COOLER_POWER		80
#define	OA_CAM_CTRL_TRIGGER_ENABLE		81
#define	OA_CAM_CTRL_TRIGGER_MODE		82
#define	OA_CAM_CTRL_TRIGGER_SOURCE		83
#define	OA_CAM_CTRL_TRIGGER_POLARITY		84
#define	OA_CAM_CTRL_TRIGGER_DELAY_ENABLE	85
#define	OA_CAM_CTRL_TRIGGER_DELAY		86
#define OA_CAM_CTRL_STROBE_ENABLE		87
#define	OA_CAM_CTRL_STROBE_POLARITY		88
#define OA_CAM_CTRL_STROBE_SOURCE		89
#define	OA_CAM_CTRL_STROBE_DELAY		90
#define	OA_CAM_CTRL_STROBE_DURATION		91
#define	OA_CAM_CTRL_SPEED			92
#define	OA_CAM_CTRL_FAN				93
// Adding more items here may require updating liboacam/control.c
#define	OA_CAM_CTRL_LAST_P1		OA_CAM_CTRL_FAN+1

#define OA_COLOUR_MODE_RAW		1
#define OA_COLOUR_MODE_NONRAW		2
#define OA_COLOR_MODE_RAW		OA_COLOUR_MODE_RAW
#define OA_COLOR_MODE_NONRAW		OA_COLOUR_MODE_NONRAW

// white balance ranges

#define OA_WHITE_BALANCE_MANUAL		0
#define OA_WHITE_BALANCE_AUTO		1
#define OA_WHITE_BALANCE_INCANDESCENT	2
#define OA_WHITE_BALANCE_FLUORESCENT	3
#define OA_WHITE_BALANCE_FLUORESCENT_H	4
#define OA_WHITE_BALANCE_HORIZON	5
#define OA_WHITE_BALANCE_DAYLIGHT	6
#define OA_WHITE_BALANCE_FLASH		7
#define OA_WHITE_BALANCE_CLOUDY		8
#define OA_WHITE_BALANCE_SHADE		9
#define OA_AWB_PRESET_LAST_P1		OA_WHITE_BALANCE_SHADE+1

// auto exposure types

#define OA_EXPOSURE_AUTO		0
#define OA_EXPOSURE_MANUAL		1
#define OA_EXPOSURE_SHUTTER_PRIORITY	2
#define OA_EXPOSURE_APERTURE_PRIORITY	3
#define OA_EXPOSURE_TYPE_LAST_P1	OA_EXPOSURE_APERTURE_PRIORITY+1

#define OA_TRIGGER_EXTERNAL		0
#define OA_TRIGGER_BULB_SHUTTER		1
#define OA_TRIGGER_PULSE_COUNT		2
#define OA_TRIGGER_SKIP_FRAMES		3
#define OA_TRIGGER_MULTI_PRESET		4
#define OA_TRIGGER_MULTI_PULSE_WIDTH    5
#define OA_TRIGGER_LOW_SMEAR		13
#define OA_TRIGGER_VENDOR_1		14
#define OA_TRIGGER_VENDOR_2		15

#define OA_TRIGGER_SOURCE_0		0
#define OA_TRIGGER_SOURCE_1		1
#define OA_TRIGGER_SOURCE_2		2
#define OA_TRIGGER_SOURCE_3		3

#define OA_TRIGGER_POLARITY_ACTIVE_LOW	0
#define OA_TRIGGER_POLARITY_ACTIVE_HIGH	1

extern const char* oaCameraControlLabel[ OA_CAM_CTRL_LAST_P1 ];
extern const char* oaCameraPresetAWBLabel[ OA_AWB_PRESET_LAST_P1 ];
extern const char* oaCameraAutoExposureLabel[ OA_EXPOSURE_TYPE_LAST_P1 ];

#endif	/* OPENASTRO_CAMERA_CONTROLS_H */
