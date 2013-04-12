///////////////////////////////////////////////////////////////////////////////
// This file is part of Guitarrero. Copyright (C) 2009-2012 FONTA Romain
//
// Guitarrero is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Guitarrero is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Guitarrero.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <iostream>

/* GLOBAL TEXTS */
#define GAME_NAME				L"Guitarrero"
#define GAME_VERSION			L"V1.0 BETA 5 - 2010"
#define GAME_AUTHOR				L"FONTA Romain"
#define GAME_WEBSITE			L"http://playguitarrero.online.fr"

/* DIRECTORY */
#define SKINS_DIR   			"./Skins/"
#define LANGS_DIR 	  			"./Langs/"
#define SCENES_DIR 	  			"./Scenes/"

/* CONFIG FILE */
#define XML_ENGINE_FILE 		"./GuitarreroConfig.xml"

/* DEFAULT LANG AND SKIN */
#define DEFAULT_SKIN_PATH		SKINS_DIR"Default"
#define DEFAULT_LANG_PATH		LANGS_DIR"English.xml"
#define DEFAULT_SONGS_PATH		"./Songs/"

/* PAUSE BEFORE STARTING SONG */
#define PAUSE_BEFORE 			1500

/* DELAY BEFORE AND AFTER TO PLAY A LINE */
#define MS_DELAY 				100	

/* TTF SUPPORT FOR THE ENGINE */
#include "CGUIFreeTypeFont.h"


/* GAME_STATES */
enum GAME_STATE
{
	GS_UNDEFINED		= -1,
	GS_MAIN 			= 0,
	GS_GAME,
	GS_PAUSE,
	GS_CREDITS,
	GS_SONG_SELECTION,
	GS_SONG_STATISTIC,
	GS_MODE_SELECTION,
	GS_SPECIAL_MODE_S,
	GS_EXIT,
	GS_RESUME_GAME,
	GS_RESTART_GAME,
	GS_NO_LEVELS_AFTER_MODE_S
};

/* RENDER STATE */
enum RENDER_STATE
{
	RS_NOT_DRAWED		= 0,
	RS_NOT_STARTED,
	RS_READY
};

/* LEVELS */
enum LEVEL
{
	LEVEL_EASY 		= 62,
	LEVEL_MEDIUM 	= 74,
	LEVEL_NORMAL	= 86,
	LEVEL_HARD		= 98,
};

/* GAME MODES */
enum GMODE
{
	GM_NORMAL	= 0,
	GM_REFLEX,
	GM_DUEL,
	GM_DUEL_P,
	GM_DUEL_REFLEX,
	GM_DUEL_P_REFLEX
};

/* USED BY GUI PAGE */
enum ACTION_TYPE
{
	ACTION_NONE = 0,
	ACTION_P1_KEY_PRESSED,
	ACTION_P2_KEY_PRESSED,
	ACTION_P1_INPUT,
	ACTION_P2_INPUT	
};

/* FOR GUI PAGE */
#define FRET_1 1
#define FRET_2 2
#define FRET_3 3
#define FRET_4 4
#define FRET_5 5

#endif
