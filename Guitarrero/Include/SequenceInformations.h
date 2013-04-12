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

#ifndef _SEQUENCEINFORMATIONS_H_
#define _SEQUENCEINFORMATIONS_H_

#include <fstream>
#include "irrlicht.h"
#include "Cerealizer.h"

/* INI TAGS */
#define MAX_LINE_LENGHT					32768
#define INFORMATION_SONG_FILE 			"/song.ini"
#define INI_FILE_HEAD					"[song]"
#define DELIMITER						'='
#define TAG_SONG_NAME					"name"
#define TAG_ARTIST_NAME					"artist"
#define TAG_SCORES						"scores"
#define TAG_DELAY						"delay"


class SequenceInformations
{
	public :
		SequenceInformations(irr::core::stringc directory) ;

		irr::core::array<Player*>	getSeqScores()	{return this->seqPlayers ;}
		irr::core::stringc 			getSeqArtist()	{return this->seqArtist ;}
		irr::core::stringc 			getSeqName()	{return this->seqName ;}
		int							getSeqDelay()	{return this->seqDelay ;}

		void						addPlayer(irr::core::stringc name, int score, int stars, LEVEL level) ;
		irr::core::array<Player*>	getSeqScores(LEVEL level) ;
		Player* 					getSeqBestScore(LEVEL level) ;
		void 						saveInformationsFile() ;

	private :
		irr::core::array<Player*>	seqPlayers ;	// All players scores with levels and stars
		irr::core::stringc 			seqArtist ;		// The song artist (from ini file)
		irr::core::stringc 			seqName ;		// The song name (from ini file)
		irr::core::stringc			seqDirectory ;	// The song directory
		int							seqDelay ;		// The song delay as specified in ini file
};
#endif
