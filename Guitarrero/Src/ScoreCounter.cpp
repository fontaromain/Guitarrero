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

#include "ScoreCounter.h"
#include "GridManager.h"

ScoreCounter::ScoreCounter(GridManager* grid, Statistics* stats, int xStats, int yStats)
{
	// Init members
	this->myGrid	= grid ;
	this->myStats 	= stats ;
	this->precision	= 0 ;
	this->textFont	= this->myGrid->guiSmgr->getGUIEnvironment()->getFont(irr::core::stringc(this->myGrid->myRessources->getFile(FONT_SCORE_COUNTER)).c_str()) ;

	// Create the counter
	this->create(xStats, yStats) ;
}

void ScoreCounter::create(int xStats, int yStats)
{
	// Create counter
	this->counter = this->myGrid->guiSmgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(350.0f, 350.0f)) ;
	this->counter->setMaterialTexture(0, this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(SCORE_COUNTER))) ; // Apply texture
	this->counter->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL) ;
	this->counter->setMaterialFlag(irr::video::EMF_ZBUFFER, false)  ;

	irr::core::vector3df animSt = irr::core::vector3df(1200, xStats, -1000) ; 
	irr::core::vector3df animEd = irr::core::vector3df(1200, xStats, yStats) ; 
	int animTime = PAUSE_BEFORE ;
	
	this->counter->addAnimator(this->myGrid->guiSmgr->createFlyStraightAnimator(animSt, animEd, animTime, false)) ;
	
	// Score text
	irr::scene::ISceneNode* node = this->myGrid->guiTextSmgr->addEmptySceneNode() ;
	node->addAnimator(this->myGrid->guiTextSmgr->createFlyStraightAnimator(animSt, animEd, animTime, false)) ;
	
	int ScoreHPos = 138 ;
	irr::core::dimension2d<irr::f32> dimSc = irr::core::dimension2d<irr::f32>(40.0f, 50.0f) ;

    this->scoreDigitG = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node, dimSc, irr::core::vector3df(0, ScoreHPos, -120)) ;
    this->scoreDigitF = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node, dimSc, irr::core::vector3df(0, ScoreHPos, -80)) ;
    this->scoreDigitE = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node, dimSc, irr::core::vector3df(0, ScoreHPos, -40)) ;
    this->scoreDigitD = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node, dimSc, irr::core::vector3df(0, ScoreHPos, 0)) ;
    this->scoreDigitC = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node, dimSc, irr::core::vector3df(0, ScoreHPos, 40)) ;
	this->scoreDigitB = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node, dimSc, irr::core::vector3df(0, ScoreHPos, 80)) ;
	this->scoreDigitA = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node, dimSc, irr::core::vector3df(0, ScoreHPos, 120)) ;

	// Lines streak text
	irr::scene::ISceneNode* node2 = this->myGrid->guiTextSmgr->addEmptySceneNode() ;
	node2->addAnimator(this->myGrid->guiTextSmgr->createFlyStraightAnimator(animSt, animEd, animTime, false)) ;
	
	int lineStreakHPos = -132 ;
	irr::core::dimension2d<irr::f32> dim = irr::core::dimension2d<irr::f32>(40.0f, 50.0f) ;
	
	this->lineStreakDigitC = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node2, dim, irr::core::vector3df(0, lineStreakHPos, -110)) ;
	this->lineStreakDigitB = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node2, dim, irr::core::vector3df(0, lineStreakHPos, -70)) ;
	this->lineStreakDigitA = this->myGrid->guiTextSmgr->addBillboardTextSceneNode(
					this->textFont, L"0", node2, dim, irr::core::vector3df(0, lineStreakHPos, -30)) ;
	
	// Multiplicator text
	this->counterMultiplicator = this->myGrid->guiSmgr->addBillboardSceneNode(
					this->counter, 
					irr::core::dimension2d<irr::f32>(80.0f, 80.0f),
					irr::core::vector3df(-30, 10, 0)) ;
	this->counterMultiplicator->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL)  ;
	this->counterMultiplicator->setMaterialTexture(0, this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(SCORE_COUNTER_MULT1))) ;
	
	// Don't use lightning	
	this->counter->setMaterialFlag(				irr::video::EMF_LIGHTING, false);
	this->scoreDigitA->setMaterialFlag(			irr::video::EMF_LIGHTING, false);
	this->scoreDigitB->setMaterialFlag(			irr::video::EMF_LIGHTING, false);
	this->scoreDigitC->setMaterialFlag(			irr::video::EMF_LIGHTING, false);
	this->scoreDigitD->setMaterialFlag(			irr::video::EMF_LIGHTING, false);
	this->scoreDigitE->setMaterialFlag(			irr::video::EMF_LIGHTING, false);
	this->scoreDigitF->setMaterialFlag(			irr::video::EMF_LIGHTING, false);
	this->scoreDigitG->setMaterialFlag(			irr::video::EMF_LIGHTING, false);
	this->lineStreakDigitA->setMaterialFlag(	irr::video::EMF_LIGHTING, false);
	this->lineStreakDigitB->setMaterialFlag(	irr::video::EMF_LIGHTING, false);
	this->lineStreakDigitC->setMaterialFlag(	irr::video::EMF_LIGHTING, false);
	this->counterMultiplicator->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	// Add a camera to see it
	this->myGrid->guiSmgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;
	this->myGrid->guiTextSmgr->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;
}

void ScoreCounter::update()
{
	//////////////////////
	// SCORE
	//////////////////////
	int score 	= this->myStats->getScore() ;
	int digitA 	= score / 1000000 ;
	int digitB 	= score / 100000 	- ((digitA * 10)) ;
	int digitC 	= score / 10000		- ((digitA * 100)		+ (digitB * 10)) ;
	int digitD 	= score / 1000     	- ((digitA * 1000) 		+ (digitB * 100) 	+ (digitC * 10)) ;
	int digitE 	= score / 100		- ((digitA * 10000)     + (digitB * 1000)   + (digitC * 100) + (digitD * 10)) ;
	int digitF 	= score / 10      	- ((digitA * 100000) 	+ (digitB * 10000)  + (digitC * 1000)+ (digitD * 100) + (digitE * 10)) ;
	int digitG 	= score            	- (score / 10) * 10 ;

	this->scoreDigitA->setText(irr::core::stringw(digitA).c_str()) ;
	this->scoreDigitB->setText(irr::core::stringw(digitB).c_str()) ;
	this->scoreDigitC->setText(irr::core::stringw(digitC).c_str()) ;
	this->scoreDigitD->setText(irr::core::stringw(digitD).c_str()) ;
	this->scoreDigitE->setText(irr::core::stringw(digitE).c_str()) ;
	this->scoreDigitF->setText(irr::core::stringw(digitF).c_str()) ;
	this->scoreDigitG->setText(irr::core::stringw(digitG).c_str()) ;

	//////////////////////
	// Line streak
	//////////////////////
	int streak 	= this->myStats->getCurrentLinesStreak() ;
	int dA 		= streak / 100 ;
	int dB 		= streak / 10    - (dA * 10) ;
	int dC 		= streak         - (streak / 10) * 10 ;

	this->lineStreakDigitA->setText(irr::core::stringw(dA).c_str()) ;
	this->lineStreakDigitB->setText(irr::core::stringw(dB).c_str()) ;
	this->lineStreakDigitC->setText(irr::core::stringw(dC).c_str()) ;

	//////////////////////
	// MULTIPILICATOR
	//////////////////////
	irr::video::ITexture* multTexture ; 
	switch(this->myStats->getMultiplicator())
	{
		case 1 : multTexture = this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(SCORE_COUNTER_MULT1)) ; break ;
		case 2 : multTexture = this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(SCORE_COUNTER_MULT2)) ; break ;
		case 3 : multTexture = this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(SCORE_COUNTER_MULT3)) ; break ;
		case 4 : multTexture = this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(SCORE_COUNTER_MULT4)) ; break ;
	}
	
	this->counterMultiplicator->setMaterialTexture(0, multTexture) ;
}

void ScoreCounter::addMessage(int type, int timePrecision)
{
/*	if (!this->precision)
	{
		this->precision = this->myGrid->smgr->addCubeSceneNode(1, 0, -1, irr::core::vector3df(0, 0, (this->myGrid->distEcart * 3) + this->myGrid->yOffset - (this->myGrid->animOffset * 0)), irr::core::vector3df(0, this->myGrid->rotation, 0), irr::core::vector3df(this->myGrid->distEcart / 2, 0, this->myGrid->distEcart / 2)) ;
		this->precision->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}

	switch(type)
	{
		case PRECISION :
		{
			timePrecision = irr::core::abs_(timePrecision) ;
			
			if (timePrecision < 33)
			{
				this->precision->setMaterialTexture(0, this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(PRECISION_HIGH))) ;
			}
			else if (timePrecision < 66)
			{
				this->precision->setMaterialTexture(0, this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(PRECISION_MED))) ;
			}
			else
			{
				this->precision->setMaterialTexture(0, this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(PRECISION_LOW))) ;
			}

			break ;
		}
		case ERROR_LINE :
		case ERROR_IDLE :
		{
			this->precision->setMaterialTexture(0, this->myGrid->driver->getTexture(this->myGrid->myRessources->getFile(PLAY_ERROR))) ;
			break ;
		}
	}*/
}
