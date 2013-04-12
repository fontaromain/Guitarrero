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

#include "SequenceInformations.h"

SequenceInformations::SequenceInformations(irr::core::stringc directory)
{
	// Init class members
	this->seqName		= irr::core::stringc("Undefined name") ;
	this->seqArtist		= irr::core::stringc("Undefined artist") ;
	this->seqDirectory	= directory ;
	this->seqDelay		= 0 ; // By default no delay

	// Open the song information file
	std::ifstream informationsFile((directory + INFORMATION_SONG_FILE).c_str()); // Open the file

	// If file don't exists
	if(informationsFile.is_open())
	{
		char readedLine[MAX_LINE_LENGHT]; // Container to store lines
		
		while(informationsFile.getline (readedLine, MAX_LINE_LENGHT, '\n')) // Read and parse all lines
		{
			irr::core::stringc line(readedLine) ; // Store the line

			int delimiter = line.findFirst(DELIMITER) ; // Find the delimiter between tag / value 
		
			if (delimiter != -1) // Delimiter founded
			{
				irr::core::stringc tag = line.subString(0, delimiter).trim(" \n\r\t") ;
				
				if (tag == TAG_SONG_NAME)
				{
					this->seqName = line.subString(delimiter+1, line.size()).trim(" \n\r\t") ;
				}
				else if (tag == TAG_ARTIST_NAME)
				{
					this->seqArtist = line.subString(delimiter+1, line.size()).trim(" \n\r\t") ;
				}
				else if (tag == TAG_DELAY)
				{
					this->seqDelay = atoi((line.subString(delimiter+1, line.size()).trim(" \n\r\t")).c_str()) ;
				}
				else if (tag == TAG_SCORES)
				{
					Cerealizer cer ;
					this->seqPlayers = cer.parse(line.subString(delimiter+1, line.size()).trim(" \n\r\t")) ;
				}
			}
		}
   	}
   
   	informationsFile.close() ; 		// Close ini file		
   	this->saveInformationsFile() ;	// Save it to hard disk
}

void SequenceInformations::addPlayer(irr::core::stringc name, int score, int stars, LEVEL level)
{
	Player* player = new Player(name, irr::core::stringc(stars), irr::core::stringc(score)) ;
	player->setLevel(level) ;
	this->seqPlayers.push_back(player) ;
}

irr::core::array<Player*> SequenceInformations::getSeqScores(LEVEL level)
{
	irr::core::array<Player*> players ;

	// Now grab all players
	for (int i = 0 ; i < this->seqPlayers.size() ; i++)
	{
		if (this->seqPlayers[i]->getLevel() == level)
		{
			players.push_back(this->seqPlayers[i]) ;
		}
	}
	
	// Sort them by scores
	bool 	sorted 	= false ;
	int 	size 	= players.size() ;
	while(!sorted && size != 0)
	{
		sorted = true ;
		for(int i = 0 ; i < size - 1 ; i++)
		{
			if (atoi(players[i]->getScore().c_str()) < atoi(players[i + 1]->getScore().c_str()))
			{
				Player* pl 		= players[i] ;
				players[i] 		= players[i + 1] ;
				players[i + 1] 	= pl ;
				sorted = false ;
			}
		}
	}
	
	// Return the array of players
	return players ;
}

Player* SequenceInformations::getSeqBestScore(LEVEL level)
{
	Player *player = 0 ;

	for (int i = 0 ; i < this->seqPlayers.size() ; i++)
	{
		if (this->seqPlayers[i]->getLevel() == level)
		{
			if (player == 0) // Init
			{
				player = this->seqPlayers[i] ;				
			}
			else if (atoi(player->getScore().c_str()) < atoi(this->seqPlayers[i]->getScore().c_str()))
			{
				player = this->seqPlayers[i] ;
			}
		}
	}
	
	return player ;
}

void SequenceInformations::saveInformationsFile()
{	
	// First serialize scores
	Cerealizer cer ;
	
	// Open the song information file or create (if open erase everything inside)
	std::ofstream informationsFile((this->seqDirectory + INFORMATION_SONG_FILE).c_str()) ; 

	// Now rewrite the file with new values
	informationsFile << INI_FILE_HEAD 	<< "\n" ; 															// Header
	informationsFile << TAG_SONG_NAME 	<< " " << DELIMITER << " " << this->seqName.c_str() 	<< "\n" ; 	// Song name
	informationsFile << TAG_ARTIST_NAME << " " << DELIMITER << " " << this->seqArtist.c_str() 	<< "\n" ; 	// Song artist
	informationsFile << TAG_SCORES 		<< " " << DELIMITER << " " << cer.serialize(this->seqPlayers).c_str() << "\n" ; 	// Song score
	informationsFile << TAG_DELAY 		<< " " << DELIMITER << " " << this->seqDelay << "\n" ; 				// Song Delay

   	// Close the file
	informationsFile.close() ;
}
