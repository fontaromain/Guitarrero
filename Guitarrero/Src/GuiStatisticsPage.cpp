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

#include "GuiStatisticsPage.h"

GuiStatisticsPage::GuiStatisticsPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, GameMode* myGameMode)
: GuiPage(baseSmgr, driver, ressources, STATS_FONT)
{
	this->myGameMode = myGameMode ; // Init
	this->createGui() ; 			// Create the gui
}

void GuiStatisticsPage::performAction(ACTION_TYPE at, int val)
{
	switch(at)
	{
		case ACTION_P1_INPUT :
		{
			this->inputName((char)val) ;
			break ;
		}
	}
}

void GuiStatisticsPage::createGui()
{
	this->clear() ;
	this->addCamera(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;

	this->addBackground(BACK_STATS) ;
	this->addButton(BUTTON1_STATS, ID_TEXT_BTN_GO_SELECT_SONG_FROM_STATISTIC) ; 
	this->addButton(BUTTON2_STATS, ID_TEXT_BTN_GO_MENU_FROM_STATISTIC) ; 

	std::deque<Statistics*> stats = this->myGameMode->getStats() ;
	for (int i = 0 ; i < stats.size() ; i++)
	{
		irr::core::stringw score 			= this->myRessources->getText(ID_TEXT_SCORE_FROM_STATISTIC) + irr::core::stringw(stats[i]->getScore()) ;
		irr::core::stringw level			= this->myRessources->getText(ID_TEXT_LEVEL_FROM_STATISTIC) + this->myGameMode->getLevelStr(this->myRessources) ;
		irr::core::stringw percentage 		= this->myRessources->getText(ID_TEXT_PERCENTAGE_ACHIEVED_FROM_STATISTIC) + irr::core::stringw(stats[i]->getPercentageAchieved()) ;
		irr::core::stringw lineStreak 		= this->myRessources->getText(ID_TEXT_LONGEST_STREAK_FROM_STATISTIC) + irr::core::stringw(stats[i]->getLongestLinesStreak()) ;
		irr::core::stringw correctlyPlayed 	= this->myRessources->getText(ID_TEXT_CORRECTLY_PLAYED_FROM_STATISTIC) + irr::core::stringw(stats[i]->getCorrectlyPlayedNotes()) ;
		irr::core::stringw noteCount 		= this->myRessources->getText(ID_TEXT_NOTE_COUNT_FROM_STATISTIC) + irr::core::stringw(stats[i]->getNotesCount()) ;
		irr::core::stringw maxMulti 		= this->myRessources->getText(ID_TEXT_MAX_MULTIPLICATOR_FROM_STATISTIC) + irr::core::stringw(stats[i]->getMaxMultiplicator()) ;
	
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), score.c_str(), irr::video::SColor(255, 255, 255, 255), 90, 150 - i * 300, true) ;
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), level.c_str(), irr::video::SColor(255, 255, 255, 255), 60, 150 - i * 300, true) ;
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), percentage.c_str(), irr::video::SColor(255, 255, 255, 255), 30, 150 - i * 300, true) ;
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), lineStreak.c_str(), irr::video::SColor(255, 255, 255, 255), 0, 150 - i * 300, true) ;
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), correctlyPlayed.c_str(), irr::video::SColor(255, 255, 255, 255), -30, 150 - i * 300, true) ;
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), noteCount.c_str(), irr::video::SColor(255, 255, 255, 255), -60, 150 - i * 300, true) ;
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), maxMulti.c_str(), irr::video::SColor(255, 255, 255, 255), -90, 150 - i * 300, true) ;
	}

	// We could save score only if in game normal
	if (this->myGameMode->getMode() == GM_NORMAL)
	{		
		this->addSimpleText(irr::core::dimension2d<irr::s32>(300, 100), this->name.size() == 0 ? L"Enter your name" : this->name.c_str(), irr::video::SColor(255, 255, 255, 255), -130, 0, true) ;
	}
}

void GuiStatisticsPage::destroyGui()
{

}

irr::core::stringw GuiStatisticsPage::getName()
{
	return this->name ;	
}

void GuiStatisticsPage::inputName(char val)
{
	if (this->myGameMode->getMode() == GM_NORMAL)
	{
		if (((val >= 'A' && val <= 'Z') || (val >= '0' && val <= '9')) && this->name.size() < 8)
		{
			this->name.append(val) ;
		}
		else if (val == 8)
		{
			this->name = this->name.subString(0, this->name.size() - 1) ;
		}
		
		this->createGui() ; // Update the page
	}
}
