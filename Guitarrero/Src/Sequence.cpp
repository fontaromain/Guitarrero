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

#include "Sequence.h"

Sequence::Sequence(irr::core::stringc seqDirectory, int delay)
{
	// Init member
	this->seqDirectory	= seqDirectory ;
	this->fDelay 		= delay ;
	this->myCSeq		= 0 ;
	this->mySeqInfos	= 0 ;
	
	// Retrieve the song informations (artist, delay etc.)
	this->readSongIni() ;

	// Set availableLevel[] to false
	for (int i = 0 ; i < 4 ; i++)
	{
		this->availableLevel[i] = 0 ;
	}
}

Sequence::~Sequence()
{
	delete this->myCSeq ;
	delete this->mySeqInfos ;
}

void Sequence::readSongIni()
{
	if (this->mySeqInfos)
	{
		delete this->mySeqInfos ;
		this->mySeqInfos = 0 ;	
	}
	
	this->mySeqInfos 	= new SequenceInformations(this->seqDirectory) ;
	this->delay			= this->fDelay + this->mySeqInfos->getSeqDelay() ;	
}

std::deque<irr::core::stringw> Sequence::getAvLevels(Ressources* ressources)
{
	// Create a deque for levels
	std::deque<irr::core::stringw> avLevels ;
	
	if(this->availableLevel[0] >= NB_NOTES_MIN_IN_LEVEL)
	{
		avLevels.push_back(ressources->getText(ID_TEXT_LEVEL_EASY_FROM_MODE_SELECTION)) ;
	}
	if(this->availableLevel[1] >= NB_NOTES_MIN_IN_LEVEL)
	{
		avLevels.push_back(ressources->getText(ID_TEXT_LEVEL_MEDIUM_FROM_MODE_SELECTION)) ;
	}
	if(this->availableLevel[2] >= NB_NOTES_MIN_IN_LEVEL)
	{
		avLevels.push_back(ressources->getText(ID_TEXT_LEVEL_NORMAL_FROM_MODE_SELECTION)) ;
	}
	if(this->availableLevel[3] >= NB_NOTES_MIN_IN_LEVEL)
	{
		avLevels.push_back(ressources->getText(ID_TEXT_LEVEL_HARD_FROM_MODE_SELECTION)) ;	
	}
	
	return avLevels ;
}

bool Sequence::hasLevels()
{
	return !(this->availableLevel[0] < NB_NOTES_MIN_IN_LEVEL && this->availableLevel[1] < NB_NOTES_MIN_IN_LEVEL && 
			this->availableLevel[2] < NB_NOTES_MIN_IN_LEVEL && this->availableLevel[3] < NB_NOTES_MIN_IN_LEVEL) ;
}

CObjectEvent* Sequence::getFirstEvent()
{
	CObjectEvent* firstEvent = 0 ;
	
	if (this->myCSeq)
	{
		// Find good track
		TPattern* tracks = this->myCSeq->getPattern() ;
		
		while(strcmp(tracks->szTitle, "PART GUITAR") != 0 && tracks->pRight)
		{
			tracks = tracks->pRight ;
		}
		
		firstEvent = tracks->pFirstEvent ; // Get the first event
	}
	
	return firstEvent ;
}

void Sequence::loadMidFile()
{
	if (this->myCSeq == 0)
	{
		// Init the array levels which contains all levels
		LEVEL levels[4] = {LEVEL_EASY, LEVEL_MEDIUM, LEVEL_NORMAL, LEVEL_HARD} ;
	
		// Parse the file to found levels
		this->myCSeq = new CSequencer() ;
	
		// Init
		this->myCSeq->ImportMidiFile((this->seqDirectory + MIDI_FILE).c_str()) ;
	
		// Create playable track
		CObjectEvent* event = this->getFirstEvent() ;
		while(event)
		{
			if (event->GetType() == MIDI_NOTEON) // A note
			{
				int note = ((CObjectEventNote*)event)->note ;
				for (int i = 0 ; i < 4 ; i++)
				{
					if ((note <= levels[i]+2 && note >= levels[i]-2) 	// If this note is for the targeted level
					&& this->availableLevel[i] < NB_NOTES_MIN_IN_LEVEL) // and we've not reached the min notes per level
					{
						this->availableLevel[i]++ ;
					}
				}
			}
			event = event->pRight ; // Go next note
		}
	}
}

std::deque<NotesLine*>* Sequence::getLines(LEVEL level)
{
	// Update song informations (to allow to change without exiting and launching again the game)
	this->readSongIni() ;
	
	// The notes lines
	std::deque<NotesLine*>* notesLines = new std::deque<NotesLine*>() ;
	
	// Create playable track
	CObjectEvent* event = this->getFirstEvent() ;
	
	NotesLine* actualNotesLine 	= new NotesLine(-1, -1, -1, -1) ; // Line to be stored
	
	int 	nbNotes 		= 0 ; 	// Note count	
	int 	note 			= -1 ;  // Current note readed from midi file
	int 	lastNote		= -1 ;	// Store last note for tapping detection
	int 	noteEndTime 	= -1 ; 	// Current note end time
	int 	noteStartTime 	= -1 ;	// Current note start time
	double 	currentTempo 	= -1 ; 	// Current tempo at this time
	
	while(event) // While there is smthg in the midi file
	{
		if (event->GetType() == MIDI_NOTEON) // We readed a note from midi
		{
			note = ((CObjectEventNote*)event)->note ; // Get the current note

			if (note <= level+2 && note >= level-2) // If this note is for the targeted level
			{
				noteStartTime = myCSeq->TimeCodeToTimeClock(event->left) + PAUSE_BEFORE + this->delay ; // Get the time to beat this note (in Ms)					

				if (noteStartTime > /*!=*/ actualNotesLine->getStartTime()) // First line or new line
				{					
					noteEndTime = myCSeq->TimeCodeToTimeClock(((CObjectEventNote*)event)->right) + PAUSE_BEFORE + this->delay ; // Update end time

					// Update the current tempo	/ 4
					currentTempo = (60000.0 / (myCSeq->GetTempo(event->left) * 4)) ; 	
					bool tapping = false ;	// Is the next line tappable ?
					
					if (nbNotes != 0) // Store the line if not at initialising
					{
						// Checks for tapping detections
						if ((actualNotesLine->getEndTime() + currentTempo > noteStartTime)
						&& (!actualNotesLine->isChord())
						&& (note != lastNote))
						{
							tapping = true ;
						}
						
						// Define next line time
						actualNotesLine->setNextLineTime(noteStartTime) ;
						
						// Store the last line in container
						notesLines->push_back(actualNotesLine) ;
					}

					lastNote = note ; // Store the last note for tapping detection
					
					// Create a new line
					actualNotesLine = new NotesLine(noteStartTime,
													noteEndTime,
													noteEndTime - noteStartTime <= currentTempo ? 1 : noteEndTime - noteStartTime,
													level,
													tapping) ;
				}
				else if (noteStartTime < actualNotesLine->getStartTime()) // We have reached the end of the track (even if there is other bugged notes after ...)
				{
					break ;
				}

				actualNotesLine->setNote(note) ; // Store the note			
				nbNotes++ ; // Note count++
			}
		}
		
		event = event->pRight ; // Go to next note
	}

	notesLines->push_back(actualNotesLine) ;	// Store the last line
	
	return notesLines ;	// Return the lines
}
