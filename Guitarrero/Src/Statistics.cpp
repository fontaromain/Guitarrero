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

#include "Statistics.h"

Statistics::Statistics()
{
	this->correctlyPN 		= 0 ;
	this->longestLStreak 	= 0 ;
	this->currentLStreak 	= 0 ;
	this->score 			= 0 ;
	this->notesC 			= 0 ;
	this->multiplicator 	= MIN_MULTIPLICATOR ;
	this->maxMultiplicator 	= MIN_MULTIPLICATOR ;
}

void Statistics::linePlayed(LINE_PLAY_STATE action, int lineNoteCount)
{
	switch(action)
	{
		case LINE_PLAYED :
		{
			// Manage the multiplicator
			if(((this->currentLStreak % MULTIPLICATOR_UP_COUNT) == 0)
			&& 	(this->currentLStreak != 0)
			&& 	(this->multiplicator < MAX_MULTIPLICATOR))
			{
				// Increment and Update if necessary maxMultiplicator
				if (++this->multiplicator > this->maxMultiplicator)
				{
					this->maxMultiplicator = this->multiplicator ;
				}
			}
			
			// Increment and Update if necessary longestNotesStreak
			if (++this->currentLStreak > this->longestLStreak)
			{
				this->longestLStreak = this->currentLStreak ;
			}
				
			this->correctlyPN 	+= lineNoteCount ;										// We played a line
			this->score 		+= this->multiplicator * (BASE_SCORE * lineNoteCount) ; // Score each note
			break ;
		}
		case LINE_STILL_PLAYED :
		{
			this->score += this->multiplicator * lineNoteCount ; // Increment score
			break ;
		}
		case LINE_ERROR :
		case LINE_MISSED :
		{
			this->multiplicator  = 1 ; 	// Set multiplicator back to 1
			this->currentLStreak = 0 ; 	// Reinit linesstreak			
			break ;
		}
	}
	
	// Count notes
	switch(action)
	{
		case LINE_PLAYED :
		case LINE_MISSED :
		{
			this->notesC += lineNoteCount ;
		}
	}
}
