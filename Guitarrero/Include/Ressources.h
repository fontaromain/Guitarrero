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

#ifndef _RESSOURCES_H_
#define _RESSOURCES_H_

#include "include.h"
#include "irrlicht.h"
#include <map> 

///////////////
/* Main page */
///////////////
/* Texts */
#define ID_TEXT_BTN_GO_SELECT_SONG_FROM_MENU		"mainBtnPlay"
#define ID_TEXT_BTN_GO_CREDITS_FROM_MENU			"mainBtnCredits"
#define ID_TEXT_BTN_EXIT_GAME_FROM_MENU				"mainBtnExit"
/* Main page buttons */
#define BUTTON1_MAIN								"button1Main"
#define BUTTON2_MAIN								"button2Main"
#define BUTTON3_MAIN								"button3Main"
/* Textures */
#define BACK_TOP_MAIN								"topMain"
#define BACK_MAIN									"backgroundMain"


//////////////////
/* Credits page */
//////////////////
/* Texts */
#define ID_TEXT_BTN_GO_MENU_FROM_CREDITS			"creditsBtnGoMenu"
/* Credits page buttons */
#define BUTTON1_CREDITS								"button1Credits"
/* Textures */
#define BACK_CREDITS								"backgroundCredits"


//////////////////////
/* Select song page */
//////////////////////
/* Texts */
#define ID_TEXT_BTN_GO_MENU_FROM_SONG_SELECTION		"selectsongBtnGoMenu"
#define ID_TEXT_BTN_GO_MODE_FROM_SONG_SELECTION		"selectsongBtnGoMode"
#define ID_TEXT_CHANGE_SONGDOWN_FROM_SONG_SELECTION	"selectsongChangeSondDown"
#define ID_TEXT_CHANGE_SONGUP_FROM_SONG_SELECTION	"selectsongChangeSongUp"
#define ID_TEXT_NO_SCORES_FROM_SONG_SELECTION		"selectsongNoScore"
/* Select song page buttons */
#define BUTTON1_SONG								"button1Song"
#define BUTTON2_SONG								"button2Song"
#define BUTTON3_SONG								"button3Song"
#define BUTTON4_SONG								"button4Song"
/* Textures */
#define BACK_SONG									"backgroundSong"
/* Misc */
#define SONGLIST_COLOR								"songListColor"
#define SELECTED_SONGTITLE_COLOR					"selectedSongColor"
#define SCORES_TITLE_COLOR							"scoreTitleColor"
#define SCORES_LIST_COLOR							"scoreListColor"

//////////////////////
/* Select mode page */
//////////////////////
/* Texts */
#define ID_TEXT_BTN_CHANGE_LVL_FROM_MODE_SELECTION	"selectmodeChangeLevel"
#define ID_TEXT_BTN_CHANGE_P_FROM_MODE_SELECTION	"selectmodeBtnChangePlayer"
#define ID_TEXT_BTN_GO_GAME_FROM_MODE_SELECTION		"selectmodeBtnPlay"
#define ID_TEXT_BTN_GO_SONG_FROM_MODE_SELECTION		"selectmodeBtnBack"
#define ID_TEXT_LEVEL_MEDIUM_FROM_MODE_SELECTION	"selectmodeLevelMedium"
#define ID_TEXT_LEVEL_NORMAL_FROM_MODE_SELECTION	"selectmodeLevelNormal"
#define ID_TEXT_LEVEL_EASY_FROM_MODE_SELECTION		"selectmodeLevelEasy"
#define ID_TEXT_LEVEL_HARD_FROM_MODE_SELECTION		"selectmodeLevelHard"
#define ID_TEXT_P1_FROM_MODE_SELECTION				"selectmodeTextPlayer1"
#define ID_TEXT_P2_FROM_MODE_SELECTION				"selectmodeTextPlayer2"
/* Select mode page buttons */
#define BUTTON1_MODE								"button1Mode"
#define BUTTON2_MODE								"button2Mode"
#define BUTTON3_MODE								"button3Mode"
#define BUTTON4_MODE								"button4Mode"
/* Textures */
#define BACK_MODE									"backgroundMode"
/* Misc */
#define LEVELLIST_COLOR 							"levelListColor"
#define SELECTED_LEVEL_COLOR 						"selectedLevelColor"
#define PLAYERLIST_COLOR							"nbPlListColor"
#define SELECTED_PLAYER_COLOR						"selectedNbPlColor"
#define PLAYERLIST_POSITION							"playerListPosition"
#define LEVELLIST_POSITION							"levelListPosition"


//////////////////////////////
/* No levels page */
//////////////////////////////
/* Texts */
#define ID_TEXT_BTN_GO_BACK_FROM_NO_LEVELS			"nolevelsBtnBack"
/* Select mode page buttons */
#define BUTTON1_NO_LEVELS							"button1NoLevels"
/* Textures */
#define BACK_NO_LEVELS								"backgroundNoLevels"


//////////////////////////////
/* Select special mode page */
//////////////////////////////
/* Texts */
#define ID_TEXT_BTN_GO_GAME_FROM_SMODE_SELECTION	"selectsmodeBtnPlay"
#define ID_TEXT_BTN_GO_SONG_FROM_SMODE_SELECTION	"selectsmodeBtnBack"
#define ID_TEXT_BTN_CHANGE_MODE_FROM_SMODE_SELECTION "selectsmodeBtnChangeMode"
/* Select mode page buttons */
#define BUTTON1_SMODE								"button1Smode"
#define BUTTON2_SMODE								"button2Smode"
#define BUTTON3_SMODE								"button3Smode"
/* Textures */
#define BACK_SMODE									"backgroundSmode"
/* Misc */
#define SMODELIST_POSITION							"smodeListPosition"
#define SMODELIST_COLOR								"smodeListColor"
#define SELECTED_SMODE_COLOR						"selectedSModeColor"


///////////////
/* Game page */
///////////////
/* Positions */
#define PLAYER_1_1P_COUNTERPOS						"playerSCounter1P"
#define PLAYER_1_2P_COUNTERPOS						"player1SCounter2P"
#define PLAYER_2_2P_COUNTERPOS						"player2SCounter2P"
/* Textures */
#define KEY_DESEL									"keydesel"
#define BACK_GAME									"backgroundGame"
#define MISSED_LINE									"missedLine"
#define MISSED_NOTE									"missedNote"
#define NECK										"neck"
#define LINES										"lines"
#define SCORE_COUNTER								"scoreCounter"
#define TIME_COUNTER								"timeCounter"
#define	SCORE_COUNTER_MULT1	 						"mult1x"
#define	SCORE_COUNTER_MULT2							"mult2x"
#define	SCORE_COUNTER_MULT3 						"mult3x"
#define	SCORE_COUNTER_MULT4 						"mult4x"
#define FONT_SCORE_COUNTER							"fontScoreCounter"
#define FONT_TIME_COUNTER							"fontTimeCounter"
#define PRECISION_HIGH								"precisionHigh"
#define PRECISION_MED								"precisionMed"
#define PRECISION_LOW								"precisionLow"
#define PLAY_ERROR									"playError"



////////////////
/* Pause page */
////////////////
/* Texts */
#define ID_TEXT_BTN_GO_RESTART_FROM_PAUSE			"pauseBtnRestart"
#define ID_TEXT_BTN_GO_MENU_FROM_PAUSE				"pauseBtnGoMenu"
#define ID_TEXT_BTN_RESUME_FROM_PAUSE				"pauseBtnResume"
/* Pause page buttons */
#define BACK_PAUSE									"backgroundPause"
#define BUTTON1_PAUSE								"button1Pause"
#define BUTTON2_PAUSE								"button2Pause"
#define BUTTON3_PAUSE								"button3Pause"


/////////////////////
/* Statistics page */
/////////////////////
/* Texts */
#define ID_TEXT_PERCENTAGE_ACHIEVED_FROM_STATISTIC 	"statsAchieved"
#define ID_TEXT_BTN_GO_SELECT_SONG_FROM_STATISTIC 	"statsBtnSelectsong"
#define ID_TEXT_MAX_MULTIPLICATOR_FROM_STATISTIC	"statsMaxMulti"
#define ID_TEXT_CORRECTLY_PLAYED_FROM_STATISTIC		"statsCorrectlyPlayed"
#define ID_TEXT_LONGEST_STREAK_FROM_STATISTIC		"statsLongestStreak"
#define ID_TEXT_TRACK_LENGTH_FROM_STATISTIC			"statsTrackLength"
#define ID_TEXT_BTN_GO_MENU_FROM_STATISTIC			"statsBtnGoMenu"
#define ID_TEXT_NOTE_COUNT_FROM_STATISTIC 			"statsNoteCount"
#define ID_TEXT_LEVEL_FROM_STATISTIC				"statsLevel"
#define ID_TEXT_SCORE_FROM_STATISTIC 				"statsScore"
/* Statistic page buttons */
#define BUTTON1_STATS								"button1Stats"
#define BUTTON2_STATS								"button2Stats"
/* Textures */
#define BACK_STATS									"backgroundStats"


//////////////////////
/* Fonts			*/
//////////////////////
#define MAIN_FONT									"fontMain"
#define CREDITS_FONT								"fontCredits"
#define SONG_FONT									"fontSong"
#define MODE_FONT									"fontMode"
#define PAUSE_FONT									"fontPause"
#define STATS_FONT									"fontStats"
#define SMODE_FONT									"fontSmode"
#define NOLEVELS_FONT								"fontNoLevels"


//////////////////////
/* Sounds			*/
//////////////////////
#define MENU_BUTTONS_SOUND							"menuButtonsSound"
#define MENU_SELECT_SOUND							"menuSelectSound"
#define PLAYING_ERROR_SOUND							"playingError"
#define ENTRY_3D_SOUND								"sceneEntrySound"

// FILE TO LOAD
#define SKIN_FILE									"/skin.xml"


class Ressources
{
	public :
		Ressources(irr::core::stringc skinDir, irr::core::stringc languageFile) ;

		void 							preloadAllTextures(irr::video::IVideoDriver* videoDriver) ;		
		void 							parseLangFile(const char* langFile) ;			// Parse an xml language file and store it
		void 							parseSkinPath(const char* skinPath) ;			// Parse an xml skin file and store it
		irr::core::position2d<irr::s32> getPosition(const char* index) ;				// Get position
		irr::video::SColor				getColor(const char* index) ;					// Get color
		irr::core::stringw 				getFile(const char* index) ;					// Get file
		irr::core::stringw				getText(const char* index) ;					// Get text
	
	private :
		void							addText(irr::core::stringc name, irr::core::stringw text) ;		
		
		std::map<irr::core::stringc, irr::core::position2d<irr::s32> > 	positions ;		// Map of positions
		std::map<irr::core::stringc, irr::video::SColor> 				colors ;		// Map of colors	
		std::map<irr::core::stringc, irr::core::stringw> 				files ;			// Map of files	
		std::map<irr::core::stringc, irr::core::stringw>				texts ; 		// Map of texts
};

#endif
