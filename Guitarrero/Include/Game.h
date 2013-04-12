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

#ifndef _GAME_H_
#define _GAME_H_

#include "include.h"
#include "Irrlicht.h"
#include "irrklang.h"
#include "GameParams.h"
#include "GameMode.h"
#include "GraphicsManager.h"
#include "GuiManager.h"
#include "InputReceiver.h"
#include "Jukebox.h"
#include "Ressources.h"
#include "Sequence.h"
#include "SongManager.h"
#include "Statistics.h"

#define DELTA			10	// How many times we do game loop before drawing a frame
#define TEXT_CAPTION	GAME_NAME" "GAME_VERSION" - By "GAME_AUTHOR" - "GAME_WEBSITE

class Game
{
	friend class InputReceiver ;
	friend class GuiManager ;
	friend class GraphicsManager ;

	public :
		Game(GameParams &params) ;
		~Game() ;

	private :
		void						setSpeed(float speed) ;				// Set the game speed (for both sounds and graphics)
		void 						drawSplashScreen() ;				// Draw splash screen, for game only
		void 						gameLoop() ;						// The main loop, for game only

		irr::video::IVideoDriver* 	myDriver ;
		irrklang::ISoundEngine*		mySoundEngine ;
		irr::IrrlichtDevice* 		myGraphicEngine ;
		GraphicsManager*			myGraphicsManager ;
		InputReceiver*	 			myReceiver ;
		irr::ITimer*				myTimer ;
		SongManager*				mySongManager ;
		GuiManager*					myGuiManager ;
		Ressources* 				myRessources ;
		GameMode*					myGameMode ;
		Jukebox* 					myJukebox ;

		// FOR STATE CHANGES
		void 						setState(GAME_STATE newState) ;		// Set new game state
		void 						updateState() ; 					// Update game state, for game only

		GAME_STATE 					state ;
		GAME_STATE 					newState ;
		bool 						changeState ;

		// FOR GUI ACTIONS
		void 						setGuiAction(ACTION_TYPE a, int v) ; // Propagate an action to gui manager
		void 						propagateGuiAction() ;

		int 						guiActionValue ;
		bool 						doGuiAction ;
		ACTION_TYPE 				guiAction ;

		// FOR GRAPHIC ACTIONS
		void 						setGraphicAction(int a, int v) ; 	// Propagate an action to graphics manager
		void 						propagateGraphicAction() ;
		
		int 						graphicActionValue ;
		bool 						doGraphicAction ;
		int 						graphicAction ;
};

#endif
