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

#ifndef _STATISTICS_H_
#define _STATISTICS_H_

/* STATISTICS SCORE VALUES */
#define	MULTIPLICATOR_UP_COUNT 		10	// NotesStreak to up multiplicator
#define MIN_MULTIPLICATOR 			1	// Min multiplicator
#define MAX_MULTIPLICATOR			4	// Max multiplicator
#define BASE_SCORE					50	// Base score (multiplicator == MIN_MULTIPLICATOR) for a note

/* LINE PLAY STATES */
enum LINE_PLAY_STATE
{
	LINE_PLAYED	= 0,	// We played a line
	LINE_STILL_PLAYED,	// We are maintaining a line
	LINE_MISSED,		// We made an error
	LINE_ERROR			// We played when we shouldn't
};


class Statistics
{
	public :
				Statistics() ;
		int		getCorrectlyPlayedNotes()	{return this->correctlyPN ;}
		int		getPercentageAchieved()		{return this->correctlyPN * 100 / (this->notesC == 0 ? 1 : this->notesC) ;}
		int 	getLongestLinesStreak()		{return this->longestLStreak ;}
		int 	getCurrentLinesStreak()		{return this->currentLStreak ;}
		int 	getMaxMultiplicator()		{return this->maxMultiplicator ;}
		int 	getMultiplicator()			{return this->multiplicator ;}
		int 	getNotesCount()				{return this->notesC ;}
		int 	getScore()					{return this->score ;}
	
		void	linePlayed(LINE_PLAY_STATE action, int lineNoteCount = 0) ;

	private :
		int		maxMultiplicator ;	// Max multiplicator
		int 	longestLStreak ;	// Longest lines streak
		int 	currentLStreak ;	// Current lines streak
		int 	multiplicator ;		// Current multiplicator
		int 	correctlyPN ;		// Correctly played notes
		int 	notesC ;			// Notes count
		int 	score ;				// Current score
};

#endif
