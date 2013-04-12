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

#include "Game.h"
#include "InputReceiver.h"

bool InputReceiver::checkInputsFor(int state, NotesLine* line, int player)
{
	bool success = false ; // By default
	
	if (player == 0)
	{
		if (state == STATE_PLAY) // We should play a line
		{
			// (KeyValidator was pushed) or (tapping and the last line was a success)
			if (this->player1Keys[1][5] || (line->isTapping() && this->player1State[1])) /* true */
			{
				if (this->player1Keys[1][5]) // Not a tapping line
				{
					if (this->compareLineToKeys(line, this->player1Keys[0])) // So check actual keys
					{
						success = true ;
					}
				}
				else
				{
					if (this->compareLineToKeys(line, this->player1Keys[1])) // Validated keys
					{
						success = true ;
					}
				}
				
				if (success)
				{
					// If we can get here it's a success
					this->player1State[0] 	= true ; 	// Line note is correctly played
					this->player1State[1] 	= true ;	// For the next tapping line
					this->player1Keys[1][5] = false ; 	// Reinit
					
					if (line->isTapping()) // But the line is tappable
					{
						this->player1State[2] = true ;
					}
					else
					{
						this->player1State[2] = false ;
					}
				}
			}
		}
		else if (state == STATE_MAINTAIN) // We should maintain a notesLine
		{
			if (!this->player1Keys[1][5]) // Check for not playing again with keyValidator
			{
				success = this->compareLineToKeys(line, this->player1Keys[0]) ; // Check for no move
			}
			else // We pushed keyValidator
			{
				if (line->isTapping() && this->player1State[2]) // But the line is tappable
				{
					this->player1State[2] = false ;
					success = this->compareLineToKeys(line, this->player1Keys[0]) ; // Check for no move
					this->player1Keys[1][5] = false ; // Reinit it because we played
				}
				else
				{
					this->player1Keys[1][5] = false ; // Reinit it because we played
				}
			}
			
			for (int i = 0 ; i < 5 ; i++){this->player1Keys[1][i] = false ;}
		}
		else if (state == STATE_NOTHING) // We should play nothing so
		{
			if (!this->player1Keys[1][5]) // Check if keyValidator wasn't pushed
			{	
				success = true ; // We wasn't playing !
			}
			else // We pushed keyValidator
			{
				this->player1Keys[1][5] = false ; // Reinit it because we played
			}
			
			for (int i = 0 ; i < 5 ; i++){this->player1Keys[1][i] = false ;}	
		}
	}
	else
	{
		if (state == STATE_PLAY) // We should play a line
		{
			// (KeyValidator was pushed) or (tapping and the last line was a success)
			if (this->player2Keys[1][5] || (line->isTapping() && this->player2State[1]))
			{
				if (this->player2Keys[1][5]) // Not a tapping line
				{
					if (this->compareLineToKeys(line, this->player2Keys[0])) // So check actual keys
					{
						success = true ;
					}
				}
				else
				{
					if (this->compareLineToKeys(line, this->player2Keys[1])) // Validated keys
					{
						success = true ;
					}
				}
				
				if (success)
				{
					// If we can get here it's a success
					this->player2State[0] 	= true ; 	// Line note is correctly played
					this->player2State[1] 	= true ;	// For the next tapping line
					this->player2Keys[1][5] = false ; 	// Reinit
					
					if (line->isTapping()) // But the line is tappable
					{
						this->player2State[2] = true ;
					}
					else
					{
						this->player2State[2] = false ;
					}
				}
			}
		}
		else if (state == STATE_MAINTAIN) // We should maintain a notesLine
		{
			if (!this->player2Keys[1][5]) // Check for not playing again with keyValidator
			{
				success = this->compareLineToKeys(line, this->player2Keys[0]) ; // Check for no move
			}
			else // We pushed keyValidator
			{
				if (line->isTapping() && this->player2State[2]) // But the line is tappable
				{
					this->player2State[2] = false ;
					success = this->compareLineToKeys(line, this->player2Keys[0]) ; // Check for no move
					this->player2Keys[1][5] = false ; // Reinit it because we played
				}
				else
				{
					this->player2Keys[1][5] = false ; // Reinit it because we played
				}
			}
			
			for (int i = 0 ; i < 5 ; i++){this->player2Keys[1][i] = false ;}
		}
		else if (state == STATE_NOTHING) // We should play nothing so
		{
			if (!this->player2Keys[1][5]) // Check if keyValidator wasn't pushed
			{	
				success = true ; // We wasn't playing !
			}
			else // We pushed keyValidator
			{
				this->player2Keys[1][5] = false ; // Reinit it because we played
			}
			
			for (int i = 0 ; i < 5 ; i++){this->player2Keys[1][i] = false ;}	
		}	
	}
	
	return success ;
}

bool InputReceiver::compareLineToKeys(NotesLine* line, bool playerKeys[6])
{
	if (line->isChord()) // Should ONLY play correct notes
	{
		for (int i = 0 ; i < 5 ; i++)
		{
			if (line->getNote(i) != 0) // If is a note to play
			{
				if (!playerKeys[i]) // If note is not played
				{
					return false ; // Try again !
				}
			}
			else if (playerKeys[i]) // If a note that should not be played is played
			{
				return false ; // Try again !
			}
		}
	}
	else // Could play 11000 to really play 01000
	{
		bool noteReached = false ;

		for (int i = 0 ; i < 5 ; i++)
		{
			if (noteReached && playerKeys[i]) // Under the note to be played
			{
				return false ; // Try again !
			}

			if (line->getNote(i) != 0) // If it's the note to play
			{
				if (!playerKeys[i]) // If the note is not played
				{
					return false ; // Try again !
				}
				
				noteReached = true ;
			}
		}
	}
	
	return true ;
}

void InputReceiver::reInit(int player)
{
	if (player == 0)
	{
		// Player 1
		if (!this->player1State[0]) // If the last line wasn't a success
		{
			this->player1State[1] = false ;	// Store it
		}
	
		this->player1State[0] = false ; 	// We cannot already have played next line
		this->player1Keys[1][5]= false ; 
	}
	else
	{
		// Player 2
		if (!this->player2State[0]) // If the last line wasn't a success
		{
			this->player2State[1] = false ;	// Store it
		}
	
		this->player2State[0] = false ; 	// We cannot already have played next line
		this->player2Keys[1][5]= false ;
	}	
}

bool InputReceiver::hasPlayedNotesLine(int player)
{
	return player == 1 ? this->player2State[0] : this->player1State[0] ;
}

bool InputReceiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) // Keyboard event
	{
		int 		key 		= event.KeyInput.Key ;			// The key
		bool 		state 		= event.KeyInput.PressedDown ;	// The state of the key
		GAME_STATE 	gameState 	= this->myGame->state ;			// The state of the game
		
		if (gameState == GS_GAME) // If we are ingame
		{
			for (int i = 0 ; i < 6 ; i++)
			{
				// Player 1
				if (key == this->player1KeysMap[i] && this->player1Keys[0][i] != state)
				{
					this->player1Keys[0][i] = state ;

					if (state && !this->player1Keys[1][i]) // We pushed once
					{		
						this->player1Keys[1][i] = state ;
					}

					if (i != 5) // No 3D keyValidator
					{
						this->myGame->setGraphicAction(this->player1KeysMap[i], state) ;
					}
				}
				// Player 2
				else if (key == this->player2KeysMap[i] && this->player2Keys[0][i] != state)
				{
					this->player2Keys[0][i] = state ;

					if (state && !this->player2Keys[1][i]) // We pushed once
					{		
						this->player2Keys[1][i] = state ;
					}

					if (i != 5) // No 3D keyValidator
					{
						this->myGame->setGraphicAction(this->player2KeysMap[i], state) ;
					}
				}
			}

			///////////////////////////
			// For the gui
			///////////////////////////
			if (key == irr::KEY_ESCAPE && state)
			{
				this->myGame->setState(GS_PAUSE) ;		
			}
		}
		else // We are not ingame, so let's navigate !
		{
			if (state) // Key pushed down
			{
				switch(gameState)
				{
					case GS_MAIN : 							// Main page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_SONG_SELECTION) ;
						else if (key == this->player1KeysMap[1])
							this->myGame->setState(GS_CREDITS) ;
						else if (key == this->player1KeysMap[2])
							this->myGame->setState(GS_EXIT) ;
						break ;
					}
						
					case GS_PAUSE : 						// Pause page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_RESUME_GAME) ;
						else if (key == this->player1KeysMap[1])
							this->myGame->setState(GS_RESTART_GAME) ;
						else if (key == this->player1KeysMap[2])
							this->myGame->setState(GS_MAIN) ;
						break ;
					}
						
					case GS_CREDITS : 						// Credits page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_MAIN) ;
						break ;
					}
					
					case GS_NO_LEVELS_AFTER_MODE_S : 		// No levels page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_SONG_SELECTION) ;
						break ;
					}
					
					case GS_SONG_SELECTION : 				// Song selection page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_MODE_SELECTION) ;
						else if (key == this->player1KeysMap[1])
							this->myGame->setState(GS_MAIN) ;
						else if (key == this->player1KeysMap[2] || key == irr::KEY_UP)
							this->myGame->setGuiAction(ACTION_P1_KEY_PRESSED, FRET_4) ;		
						else if (key == this->player1KeysMap[3] || key == irr::KEY_DOWN)
							this->myGame->setGuiAction(ACTION_P1_KEY_PRESSED, FRET_3) ;
						else if (key == this->player1KeysMap[4])
							this->myGame->setGuiAction(ACTION_P1_KEY_PRESSED, FRET_5) ;
						else if ((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || key == 8)
							this->myGame->setGuiAction(ACTION_P1_INPUT, key) ;
						break ;
					}

					case GS_MODE_SELECTION : 				// Mode selection page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_SPECIAL_MODE_S) ;
						else if (key == this->player1KeysMap[1])
							this->myGame->setState(GS_SONG_SELECTION) ;
						else if (key == this->player1KeysMap[2])
							this->myGame->setGuiAction(ACTION_P1_KEY_PRESSED, FRET_3) ;		
						else if (key == this->player1KeysMap[3])
							this->myGame->setGuiAction(ACTION_P1_KEY_PRESSED, FRET_4) ;
						break ;
					}
							
					case GS_SPECIAL_MODE_S : 				// Special Mode selection page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_GAME) ;
						else if (key == this->player1KeysMap[1])
							this->myGame->setState(GS_MODE_SELECTION) ;
						else if (key == this->player1KeysMap[2])
							this->myGame->setGuiAction(ACTION_P1_KEY_PRESSED, FRET_3) ;		
						break ;
					}

					case GS_SONG_STATISTIC : 				// Song statistic page
					{
						if (key == this->player1KeysMap[0])
							this->myGame->setState(GS_SONG_SELECTION) ;
						else if (key == this->player1KeysMap[1])
							this->myGame->setState(GS_MAIN) ;
						else
							this->myGame->setGuiAction(ACTION_P1_INPUT, key) ;		
						break ;
					}
				}
			}
		}
	}
	
	return false;
}

InputReceiver::InputReceiver(int player1KeysMap[6], int player2KeysMap[6], Game* myGame)
{
	for (int i = 0 ; i < 6 ; i++) // At start, no keys pushed
	{
		// Player 1
		this->player1KeysMap[i] = player1KeysMap[i] ;
		this->player1Keys[1][i] = false ;
		this->player1Keys[0][i] = false ;
		
		// Player 2
		this->player2KeysMap[i] = player2KeysMap[i] ;
		this->player2Keys[1][i] = false ;
		this->player2Keys[0][i] = false ;
		
		if (i < 3 )
		{
			// Player 1
			player1State[i] = 0 ;	// No line state
			
			// Player 2
			player2State[i] = 0 ;	// No line state
		}
	}
	
	this->myGame = myGame ; // No game at start
}
