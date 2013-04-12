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

#ifndef _GAMEPARAMS_H_
#define _GAMEPARAMS_H_

#include "include.h"
#include "irrlicht.h"

class GameParams
{
	public :
		GameParams()
		{
			this->player1KeysMap[0] = irr::KEY_F1 ;
			this->player1KeysMap[1] = irr::KEY_F2 ;
			this->player1KeysMap[2] = irr::KEY_F3 ;
			this->player1KeysMap[3] = irr::KEY_F4 ;
			this->player1KeysMap[4] = irr::KEY_F5 ;
			this->player1KeysMap[5] = irr::KEY_RETURN ;
			
			this->player2KeysMap[0] = irr::KEY_KEY_1 ;
			this->player2KeysMap[1] = irr::KEY_KEY_2 ;
			this->player2KeysMap[2] = irr::KEY_KEY_3 ;
			this->player2KeysMap[3] = irr::KEY_KEY_4 ;
			this->player2KeysMap[4] = irr::KEY_KEY_5 ;
			this->player2KeysMap[5] = irr::KEY_NUMPAD0 ;
			
			this->songsDir 			= DEFAULT_SONGS_PATH ;
			this->skinDir			= DEFAULT_SKIN_PATH ;
			this->languageFile		= DEFAULT_LANG_PATH ;
			this->play 				= false ;
			this->use3DScenery 		= false ;
			this->delay 			= 0 ;
			this->sustainMode		= false ;
		}
		
		irr::SIrrlichtCreationParameters 	irrParams ;				// Graphical parameters
		irr::core::stringc 					skinDir ; 				// Skin to use
		irr::core::stringc 					languageFile ;			// Language file to use 
		irr::core::stringc					songsDir ;				// The songs directory
		bool 								play ;					// Set to true by dialog if we should launch the game
		bool								use3DScenery ;			// For the scene manager, should we use 3D scenery ?
		int 								player1KeysMap[6] ;		// Player 1 keys Map
		int 								player2KeysMap[6] ;		// Player 2 keys Map
		int 								delay ;					// A/V Delay in ms
		bool								sustainMode ;			// False (default) = if releasing too early audio muted else don't care !
};

#endif
