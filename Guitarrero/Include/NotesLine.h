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

#ifndef _NOTESLINE_H_
#define _NOTESLINE_H_

#include "irrlicht.h"
#include "include.h"

#define NB_NOTES 	5	// Should be impair or set note may won't work correctly


class NotesLine
{
	public :
		NotesLine(int startTime, int endTime, int lengthTime, int level, bool tapping = false) ;
		~NotesLine() ;
		
		irr::scene::ISceneNode* getNodeStart(int i)			{return this->notesNodes[0][i] ;}
		irr::scene::ISceneNode* getNodeEnd(int i)			{return this->notesNodes[1][i] ;}
		int						getNextLineTime()			{return this->nextLineTime ;}
		int 					getNote(int index)			{return (index < NB_NOTES && index >= 0) ? this->notes[index] : 0 ;}
		int 					getNotesCount()				{return this->nbNotes ;}
		int 					getStartTime()				{return this->startTime ;}
		int 					getEndTime()				{return this->endTime ;}
		int 					getLength()					{return this->lengthTime ;}
		bool					isTapping()					{return this->tapping ;}
		bool					isChord()					{return this->nbNotes > 1 ;}
		
		void 					setNode(int i, irr::scene::ISceneNode* nodeStart, irr::scene::ISceneNode* nodeEnd) ;
		void					setNextLineTime(int time) ;
		void 					setNote(int note) ;

	private :
		irr::scene::ISceneNode* notesNodes[2][NB_NOTES] ;	// Store corresponding notes nodes
		int 					notes[NB_NOTES] ;			// Array which contains notes values, 0 = no notes
		int						nextLineTime ;				// When can start the next line ?
		int 					lengthTime ;				// The note length time (in ms)
		int 					startTime ; 				// The note start time (in ms)
		int 					endTime ;					// The note end time (in ms)
		int 					nbNotes ;					// Store the number of notes in the line
		bool 					tapping ;					// Tell if the line could be tapped
		int 					level ;						// Level of the line, used by setNote			
};

#endif
