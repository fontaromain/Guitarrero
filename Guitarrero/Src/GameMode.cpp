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

#include "GameMode.h"

GameMode::GameMode()
{
	this->seq 			= 0 ; 
	this->lineToDraw 	= DEFAULT_LINE_TO_DRAW ;
	this->nbPlayer 		= DEFAULT_NUMBER_PLAYER ;
	this->mode 			= DEFAULT_MODE ;
	this->level 		= DEFAULT_LEVEL ;
	this->speed 		= DEFAULT_SPEED ;
}

void GameMode::setSequence(Sequence* seq)
{
	this->seq = seq ;
}	

void GameMode::setlineToDraw(int nltd)
{
	if (nltd > 0)
	{
		this->lineToDraw = nltd ;
	}
}

void GameMode::setNbPlayer(int nbPl)
{
	if (nbPl >  0)
	{
		this->nbPlayer = nbPl ;
	}
}

void GameMode::setSpeed(float speed)
{
	if (speed > 0)
	{
		this->speed = speed ;
	}
}

void GameMode::setLevel(LEVEL lvl)
{
	this->level = lvl ;
}

void GameMode::setMode(GMODE mode)
{
	this->mode = mode ;
}

Sequence* GameMode::getSequence()
{
	return this->seq ;
}

int GameMode::getLineToDraw()
{
	return this->lineToDraw ;
}

int GameMode::getNbPlayer()
{
	return this->nbPlayer ;
}

GMODE GameMode::getMode()
{
	return this->mode ;
}

LEVEL GameMode::getLevel()
{
	return this->level ;
}

float GameMode::getSpeed()
{
	return this->speed ;
}
	
void GameMode::addStats(Statistics* stat)
{
	this->stats.push_back(stat) ;
}

void GameMode::clearStats()
{
	for(int i = 0 ; i < this->stats.size() ; i++)
	{
		delete this->stats[i] ;
	} 
	
	this->stats.clear() ; 
}

std::deque<Statistics*> GameMode::getStats()
{
	return this->stats ;
}

irr::core::stringw GameMode::getLevelStr(Ressources* res)
{
	switch(this->level)
	{
		case LEVEL_EASY :
			return res->getText(ID_TEXT_LEVEL_EASY_FROM_MODE_SELECTION).c_str() ;
		case LEVEL_MEDIUM :
			return res->getText(ID_TEXT_LEVEL_MEDIUM_FROM_MODE_SELECTION).c_str() ;
		case LEVEL_NORMAL :
			return res->getText(ID_TEXT_LEVEL_NORMAL_FROM_MODE_SELECTION).c_str() ;
		case LEVEL_HARD :
			return res->getText(ID_TEXT_LEVEL_HARD_FROM_MODE_SELECTION).c_str() ;
		default :
			return "Unknow" ;
	}
}
