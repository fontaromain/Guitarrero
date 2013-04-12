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

#ifndef _INPUTRECEIVER_H_
#define _INPUTRECEIVER_H_

#include "include.h"
#include "NotesLine.h"
#include "Irrlicht.h"

class Game ;

// Receiver state's
#define STATE_PLAY 		0
#define STATE_MAINTAIN 	1
#define STATE_NOTHING 	2

class InputReceiver : public irr::IEventReceiver
{
	public:
		InputReceiver(int player1KeysMap[6], int player2KeysMap[6], Game* myGame) ;
		
		bool 	hasPlayedNotesLine(int player) ;
		bool 	checkInputsFor(int state, NotesLine* line, int player) ;
		bool 	OnEvent(const irr::SEvent& event) ;	
		void 	reInit(int player) ;
		
		int*	getKeyMap(int player) {return player == 0 ? this->player1KeysMap : this->player2KeysMap ;} 
		
	private:
		bool	compareLineToKeys(NotesLine* line, bool playerKeys[6]) ; 	// Compare a notesLine to user keysState's
		
		/* Player 1 */
		int		player1KeysMap[6] ; 										// Store the keyMap for player1
		bool 	player1Keys[2][6] ;											// Actual states for player1 keys in [0], validated states in [1]
		bool	player1State[3] ;											// Play state for player1 (0 hasPlayedLine, 1 lastLineOk, 2 tappableAgain)
	
		/* Player 2 */
		int		player2KeysMap[6] ; 										// Store the keyMap for player2
		bool 	player2Keys[2][6] ;											// Actual states for player2 keys in [0], validated states in [1]
		bool	player2State[3] ;											// Play state for player2 (0 hasPlayedLine, 1 lastLineOk, 2 tappableAgain)
		
		Game* 	myGame ; 													// The game to interact with
};
#endif
