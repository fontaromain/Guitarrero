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

#include "NotesLine.h"

NotesLine::NotesLine(int startTime, int endTime, int lengthTime, int level, bool tapping)
{
	// Init
	this->startTime 	= startTime ;
	this->endTime 		= endTime ;
	this->lengthTime 	= lengthTime ;
	this->level 		= level ;
	this->tapping 		= tapping ;
	this->nextLineTime	= 0 ;
	this->nbNotes 		= 0 ;

	// Init arrays
	for (int i = 0 ; i < NB_NOTES ; i++)
	{
		this->notes[i] 			= 0 ; // By default no notes
		this->notesNodes[0][i] 	= 0 ; // By default no 3D SceneNode	(noteStart)
		this->notesNodes[1][i]	= 0 ; // By default no 3D SceneNode	(noteLength)
	}
}

NotesLine::~NotesLine()
{	
	delete[] this->notesNodes ;
	delete[] this->notes ;
}

void NotesLine::setNote(int note)
{
	int index = note - this->level + 2 ;
	
	// Not out of array and not already added
	if ((index >= 0 && index < NB_NOTES) && (this->notes[index] == 0))
	{
		this->notes[note - this->level + 2] = note ; // Store it
		this->nbNotes++ ;							 // Increment note count
	}
}

void NotesLine::setNode(int i, irr::scene::ISceneNode* nodeStart, irr::scene::ISceneNode* nodeLength)
{
	if (i >= 0 && i < NB_NOTES) // Not out of array
	{
		this->notesNodes[0][i] = nodeStart ;
		this->notesNodes[1][i] = nodeLength ;
	}
}

void NotesLine::setNextLineTime(int time) 	
{
	if (time > 0 && this->endTime > (time - MS_DELAY))
	{
		this->nextLineTime 	= time ;
		int toRemove 		= this->endTime - (this->nextLineTime - MS_DELAY) ;		
		this->endTime 		= this->endTime - toRemove ;
		
		if ((this->lengthTime - toRemove) > 0)
		{
			this->lengthTime -= toRemove ;
		}
		else
		{
			this->lengthTime = 1 ;
		}
	}
}
