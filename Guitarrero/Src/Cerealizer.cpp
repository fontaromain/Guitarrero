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

#include "Cerealizer.h"

irr::core::array<Player*> Cerealizer::parse(irr::core::stringc line)
{
	irr::core::array<Player*> players ; // To return
	
	int val[32768] = {0} ;
 	for (int i = 0, count = 0 ; line[i] != 0 ; i+=2, count++)
   	{
		val[count] = getIntVal(line[i])*16 + getIntVal(line[i+1]) ;
	}
	
	irr::core::stringc toParse = val ;

   	int nextReturn = 0 ;	
	while(nextReturn != -1)
	{
		nextReturn = toParse.find("tuple") ; // Split to the next end of line
		
		if (nextReturn != -1)
		{
			int lineToRead = getIntVal(toParse[nextReturn + 5 + 1]) ;
		
			// Remove what we readed
			toParse = toParse.subString(nextReturn + 5 + 3, toParse.size()) ;
		
			irr::core::stringc score ;
			for(int i = 1 ; i <= lineToRead ; i++) // Faire +1 si on veux le hash (osef ?)
			{
				nextReturn = toParse.find("\n") ; // Split to the next end of line
	
				// Read line
				score.append(toParse.subString(0, nextReturn) + "\n") ;
		
				// Remove already readed
				toParse = toParse.subString(nextReturn + 1, toParse.size() - nextReturn) ;
			}

			// Now parse the tuple
			players.push_back(parseTuple(score)) ;
		}
		else
		{
			// Now we associate each player to the good level
			for (int i = 0 ; i < players.size() ; i++)
			{
				int delim = toParse.find("i") ; 										// Find value in string
				switch(atoi(toParse.subString(delim + 1, 1).c_str()))
				{
					case 0 : players[i]->setLevel(LEVEL_HARD) ;		break ;		
					case 1 : players[i]->setLevel(LEVEL_NORMAL) ;	break ;		
					case 2 : players[i]->setLevel(LEVEL_MEDIUM) ; 	break ;		
					case 3 : players[i]->setLevel(LEVEL_EASY) ; 	break ;		
				}

				toParse = toParse.subString(delim + 1, toParse.size() - delim - 1) ;	// Remove readed
			}
		}
	}
	
	return players ;
}

irr::core::stringc Cerealizer::serialize(irr::core::array<Player*> players)
{
	irr::core::stringc toReturn ; // Return param
	
	// Now create the string (tuples)
	//////////////////////////////////////////////////////////////////////
	// Struture of a tuple -> int (score), int (stars), string (name)	//
	//////////////////////////////////////////////////////////////////////
	for (int i = 0 ; i < players.size() ; i++)
	{
		toReturn.append(irr::core::stringc("tuple\n4\ni") + players[i]->getScore() +
						irr::core::stringc("\ni") 			+ players[i]->getStars() +
						irr::core::stringc("\ns")			+ irr::core::stringc(players[i]->getName().size()) +
						irr::core::stringc("\n")			+ players[i]->getName() +
						irr::core::stringc("s40thefuckinghash...\n")) ;
	}
	
	// Now add levels
	for (int i = 0 ; i < players.size() ; i++)
	{
		switch(players[i]->getLevel())
		{
			case LEVEL_HARD : 	toReturn.append(irr::core::stringc("\nr") + irr::core::stringc(i) + irr::core::stringc("\ni") + irr::core::stringc(0)) ;	break ;
			case LEVEL_NORMAL : toReturn.append(irr::core::stringc("\nr") + irr::core::stringc(i) + irr::core::stringc("\ni") + irr::core::stringc(1)) ;	break ;
			case LEVEL_MEDIUM : toReturn.append(irr::core::stringc("\nr") + irr::core::stringc(i) + irr::core::stringc("\ni") + irr::core::stringc(2)) ;	break ;
			case LEVEL_EASY : 	toReturn.append(irr::core::stringc("\nr") + irr::core::stringc(i) + irr::core::stringc("\ni") + irr::core::stringc(3)) ;	break ;
		}
	}

	// Now we have to convert our ascii string into hex ascii string (yeah... why doing that ?!)
	irr::core::stringc ret ;	
	for (int i = 0 ; i < toReturn.size() ; i++)
	{
		ret.append(getHexVal(toReturn[i] / 16)) ; 
		ret.append(getHexVal(toReturn[i] - ((toReturn[i] / 16)*16))) ;
	}

	return ret ;
}


Player* Cerealizer::parseTuple(irr::core::stringc tuple)
{
	//////////////////////////////////////////////////////////////////////
	// Struture of a tuple -> int (score), int (stars), string (name)	//
	//////////////////////////////////////////////////////////////////////

	////////////////	
	// Get the score
	tuple = tuple.subString(1, tuple.size() - 1) ; // First remove the first integer identifier
	int endDelim = tuple.find("\n") ; // Go through the next elem
	irr::core::stringc score = tuple.subString(0, endDelim) ;

	////////////////
	// Get the stars
	tuple = tuple.subString(endDelim + 2, tuple.size() - endDelim - 2) ; // Remove the second integer identifier + "\n"
	endDelim = tuple.find("\n") ; // Go through the next elem
	irr::core::stringc stars = tuple.subString(0, endDelim) ;

	////////////////
	// Get the name
	tuple = tuple.subString(endDelim + 2, tuple.size() - endDelim - 2) ; // Rremove the string identifier + "\n"
	endDelim = tuple.find("\n") ; // Go through the next elem
	int strLength = atoi(tuple.subString(0, endDelim).c_str()) ;
	tuple = tuple.subString(endDelim + 1, tuple.size() - endDelim - 1) ; // Rremove the "\n"
	irr::core::stringc name = tuple.subString(0, strLength) ; ;

	/////////////////////
	// Return the player
	return new Player(name, stars, score) ;	
}

int Cerealizer::getIntVal(int val)
{
	switch(val)
	{
		case '0' : return 0 ;
		case '1' : return 1 ;
		case '2' : return 2 ;
		case '3' : return 3 ;
		case '4' : return 4 ;
		case '5' : return 5 ;
		case '6' : return 6 ;
		case '7' : return 7 ;
		case '8' : return 8 ;
		case '9' : return 9 ;
		case 'A' :
		case 'a' : return 10 ;
		case 'B' :
		case 'b' : return 11 ;
		case 'C' :
		case 'c' : return 12 ;
		case 'D' :
		case 'd' : return 13 ;
		case 'E' :
		case 'e' : return 14 ;
		case 'F' :
		case 'f' : return 15 ;
		default  : return 0 ; // Unknow value but shouldn't happen
	}	
}

char Cerealizer::getHexVal(int val)
{
	switch(val)
	{
		case 0 	: return '0' ;
		case 1 	: return '1' ;
		case 2 	: return '2' ;
		case 3 	: return '3' ;
		case 4 	: return '4' ;
		case 5 	: return '5' ;
		case 6 	: return '6' ;
		case 7 	: return '7' ;
		case 8 	: return '8' ;
		case 9 	: return '9' ;
		case 10 : return 'a' ;
		case 11 : return 'b' ;
		case 12 : return 'c' ;
		case 13 : return 'd' ;
		case 14 : return 'e' ;
		case 15 : return 'f' ;
		default : return '0' ; // Unknow value but shouldn't happen
	}	
}
