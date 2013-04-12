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

#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "include.h"
#include "SequenceInformations.h"
#include "NotesLine.h"
#include "ObjectMidi.h"
#include "Sequencer.h"
#include "Ressources.h"
#include "irrlicht.h"
#include <deque>

/* SEQUENCE */
#define MIDI_FILE 						"/notes.mid"
#define NB_NOTES_MIN_IN_LEVEL			10


class Sequence
{
	public :
		Sequence(irr::core::stringc seqDirectory, int delay) ;
		~Sequence() ;

		std::deque<irr::core::stringw> 	getAvLevels(Ressources* ressources) ;
		std::deque<NotesLine*>*			getLines(LEVEL lvl) ;
		void							loadMidFile() ;
		bool							hasLevels() ;
	
		SequenceInformations*			getSeqInfos()		{ return this->mySeqInfos ;}
		irr::core::stringc 				getDirectory() 		{ return this->seqDirectory ;}

	private :
		CObjectEvent*					getFirstEvent() ;		// Get the first midi event of the song (for parsing)
		void							readSongIni();			// Read ini file of the song
		
		SequenceInformations*			mySeqInfos ;			// Sequence informations
		irr::core::stringc				seqDirectory ;			// The seq directory
		CSequencer*						myCSeq ;				// Midi reader
		int								fDelay ;				// Fixed delay in launcher
		int								delay ;					// A/V Delay from the ini file
		int								availableLevel[4] ; 	// Available levels for this sequence
};

#endif
