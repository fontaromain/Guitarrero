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

#include "GuiSongSelectPage.h"

GuiSongSelectPage::GuiSongSelectPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, Jukebox* jukebox, GameMode* myGameMode)
: GuiPage(baseSmgr, driver, ressources, SONG_FONT)
{
	// Init class members
	this->myJukebox = jukebox ;
	this->songsSeq 	= this->myJukebox->getSequences(this->filter) ;
	this->preview 	= false ;
	
	// Restore last state
	Sequence* lastSeq = myGameMode->getSequence() ;
	
	if (lastSeq != 0)
	{
		this->it = this->songsSeq->find(lastSeq->getSeqInfos()->getSeqArtist()+ " - " + lastSeq->getSeqInfos()->getSeqName()) ;

		if (this->it == this->songsSeq->end())
		{
			this->it = this->songsSeq->begin() ;			
		}
	}
	else
	{
		this->it = this->songsSeq->begin() ;
	}

	// Create the gui
	this->createGui() ;
}

void GuiSongSelectPage::performAction(ACTION_TYPE at, int val)
{
	switch(at)
	{
		case ACTION_P1_KEY_PRESSED :
		{
			switch(val)
			{
				case FRET_3 : // Song Up
				{
					this->updateSelection(true) ;
					break ;
				}
				case FRET_4 : // Song Down
				{
					this->updateSelection(false) ;
					break ;
				}
			}
			
			break ;		
		}
		case ACTION_P1_INPUT :
		{
			this->inputFilter((char)val) ;
			break ;	
		}
	}
}

void GuiSongSelectPage::createGui()
{
	this->clear() ;	
	this->addCamera(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;
	this->addBackground(BACK_SONG) ;
	this->addButton(BUTTON1_SONG, ID_TEXT_BTN_GO_MODE_FROM_SONG_SELECTION) ;
	this->addButton(BUTTON2_SONG, ID_TEXT_BTN_GO_MENU_FROM_SONG_SELECTION) ;
	this->addButton(BUTTON3_SONG, ID_TEXT_CHANGE_SONGUP_FROM_SONG_SELECTION) ;
	this->addButton(BUTTON4_SONG, ID_TEXT_CHANGE_SONGDOWN_FROM_SONG_SELECTION) ;
	this->draw() ;
}

void GuiSongSelectPage::draw()
{
	// First draw the selected sequence
	this->drawSequence(this->it->first, this->it->second) ;
	
	// Draw the other songs
	this->drawSongList() ;
	
	// Draw filter if needed
	if (this->filter.size() != 0)
	{
		this->addSimpleText(irr::core::dimension2d<irr::s32>(80, 18), this->filter.c_str(), irr::video::SColor(255, 255, 255, 255), 220, 220, true) ;
	}
}

void GuiSongSelectPage::drawSongList()
{
	std::map<irr::core::stringc, Sequence*>::iterator iter(this->it) ;
	std::map<irr::core::stringc, Sequence*>::iterator rIter(this->it) ;

	for (int i = 0 ; i < 15 ; i++)
	{
		irr::video::SColor color = this->myRessources->getColor(SONGLIST_COLOR) ;
	
		int alpha = color.getAlpha() - 50 * i ;
		color.setAlpha(alpha >= 0 ? alpha : 0) ;

		if (this->updateIterator(rIter, false))
		{
			this->drawTitle(rIter->first, rIter->second, color, 130 + 20 * i, 0) ;
		}
	}
	
	for (int i = 0 ; i < 15 ; i++)
	{
		irr::video::SColor color = this->myRessources->getColor(SONGLIST_COLOR) ;
	
		int alpha = color.getAlpha() - 50 * i ;
		color.setAlpha(alpha >= 0 ? alpha : 0) ;
	
		if (this->updateIterator(iter, true)) 
		{
			this->drawTitle(iter->first, iter->second, color,  -60 - 20 * i, 0) ;
		}
	}
}

void GuiSongSelectPage::drawTitle(irr::core::stringc name, Sequence* seq, irr::video::SColor color, int x, int y)
{
	// Get needed attributes
	irr::core::stringw 	text = name ;

	// Add the title of the current selected song
	this->addSimpleText(irr::core::dimension2d<irr::s32>(500, 18), text.c_str(), color, x, y) ;	
}

void GuiSongSelectPage::drawSequence(irr::core::stringc name, Sequence* seq)
{
	// Draw the selected title	
	this->drawTitle(name, seq, this->myRessources->getColor(SELECTED_SONGTITLE_COLOR), STITLE_X, STITLE_Y) ;

	// Add scores
	irr::core::array<Player*> scoresEasy	= seq->getSeqInfos()->getSeqScores(LEVEL_EASY) ;
	irr::core::array<Player*> scoresMedium	= seq->getSeqInfos()->getSeqScores(LEVEL_MEDIUM) ;
	irr::core::array<Player*> scoresNormal	= seq->getSeqInfos()->getSeqScores(LEVEL_NORMAL) ;
	irr::core::array<Player*> scoresHard	= seq->getSeqInfos()->getSeqScores(LEVEL_HARD) ;

	// Draw scores
	irr::video::SColor color = this->myRessources->getColor(SCORES_TITLE_COLOR) ;
	this->drawScores(this->myRessources->getText(ID_TEXT_LEVEL_EASY_FROM_MODE_SELECTION), scoresEasy, SSCORES_X, 220, color) ;
	this->drawScores(this->myRessources->getText(ID_TEXT_LEVEL_MEDIUM_FROM_MODE_SELECTION), scoresMedium, SSCORES_X, 75, color) ;
	this->drawScores(this->myRessources->getText(ID_TEXT_LEVEL_NORMAL_FROM_MODE_SELECTION), scoresNormal, SSCORES_X, -75, color) ;
	this->drawScores(this->myRessources->getText(ID_TEXT_LEVEL_HARD_FROM_MODE_SELECTION), scoresHard, SSCORES_X, -220, color) ;
}

void GuiSongSelectPage::drawScores(irr::core::stringw title, irr::core::array<Player*> scores, int x, int y, irr::video::SColor color)
{
	// Draw title
	this->addSimpleText(irr::core::dimension2d<irr::s32>(120, 18), title.c_str(), color, x, y) ;

	// Draw scores
	irr::core::stringw scoresStr ;

	int i = 0 ;
	for ( ; i < scores.size() && i < MAX_LIST_SCORES_COUNT ; i++)
	{
		scoresStr += irr::core::stringw(scores[i]->getName()).subString(0, MAX_CHAR_PER_NAME) + " " ;
		scoresStr += scores[i]->getScore() + "\n" ;
	}

	if (scores.size() == 0)
	{
		scoresStr = this->myRessources->getText(ID_TEXT_NO_SCORES_FROM_SONG_SELECTION) ;	
		i = 2 ;
	}

	this->addSimpleText(irr::core::dimension2d<irr::s32>(120, 80), scoresStr.c_str(), this->myRessources->getColor(SCORES_LIST_COLOR), x - 60, y) ;	
}

void GuiSongSelectPage::destroyGui()
{
}

void GuiSongSelectPage::updateSelection(bool direction)
{
	if (this->updateIterator(this->it, direction))
	{
		this->preview = true ; // Need to preview
		this->createGui() ;
	}
	else
	{
		this->preview = false ; // No need to change actual preview
	}
}

bool GuiSongSelectPage::updateIterator(std::map<irr::core::stringc, Sequence*>::iterator &iter, bool direction)
{
	if (direction)
	{
		if (++iter != this->songsSeq->end())
		{
			return true ;
		}
		else
		{
			iter-- ;
		}
	}
	else
	{
		if (iter != this->songsSeq->begin())
		{
			iter-- ;
			return true ;
		}
	}
	
	return false ;	
}

Sequence* GuiSongSelectPage::getSequence()
{
	return this->it->second ;
}


void GuiSongSelectPage::inputFilter(char val)
{
	if (((val >= 'A' && val <= 'Z') || (val >= '0' && val <= '9')) && this->filter.size() < 8)
	{
		this->filter.append(val) ;
	}
	else if (val == 8)
	{
		this->filter = this->filter.subString(0, this->filter.size() - 1) ;
	}
	
	// Update the songs sequence and cleanup
	delete this->songsSeq ;
	this->songsSeq 	= this->myJukebox->getSequences(this->filter) ;
	this->it 		= this->songsSeq->begin() ;

	// Update the page
	this->preview = true ;
	this->createGui() ;
}

bool GuiSongSelectPage::shouldPreview()
{
	return this->preview ;
}
