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

#include "TimeCounter.h"

TimeCounter::TimeCounter(irr::scene::ISceneManager* smgr, Ressources* myRessources)
{
	// Init members
	this->smgr 			= smgr->createNewSceneManager() ;
	this->driver 		= this->smgr->getVideoDriver() ;
	this->myRessources	= myRessources ;
	this->textFont		= this->smgr->getGUIEnvironment()->getFont(irr::core::stringc(this->myRessources->getFile(FONT_SCORE_COUNTER)).c_str()) ;

	// Create the counter
	this->create() ;
}

TimeCounter::~TimeCounter()
{
	this->smgr->drop() ;	
}

void TimeCounter::render()
{
	this->smgr->drawAll() ;
	this->driver->clearZBuffer() ;
}

void TimeCounter::create()
{
	// Create counter
	this->counter = this->smgr->addBillboardSceneNode(
					0, 
					irr::core::dimension2d<irr::f32>(250.0f, 80.0f), 
					irr::core::vector3df(500, 980, 0)) ;
	this->counter->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(TIME_COUNTER))) ; // Apply texture
	this->counter->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL)  ;

	// Score text
    this->timeDigitE = this->smgr->addBillboardTextSceneNode(
                    this->textFont,
                    irr::core::stringw(0).c_str(), 
                    this->counter, 
                    irr::core::dimension2d<irr::f32>(40.0f, 60.0f), 
                    irr::core::vector3df(-10, 0, -80)) ;
    this->timeDigitD = this->smgr->addBillboardTextSceneNode(
                    this->textFont,
                    irr::core::stringw(0).c_str(), 
                    this->counter, 
                    irr::core::dimension2d<irr::f32>(40.0f, 60.0f), 
                    irr::core::vector3df(-10, 0, -35)) ;
    this->timeSeparator = this->smgr->addBillboardTextSceneNode(
                    this->textFont,
                    L":", 
                    this->counter, 
                    irr::core::dimension2d<irr::f32>(40.0f, 60.0f), 
                    irr::core::vector3df(-10, 0, 0)) ;
    this->timeDigitB = this->smgr->addBillboardTextSceneNode(
                    this->textFont,
                    irr::core::stringw(0).c_str(), 
                    this->counter, 
                    irr::core::dimension2d<irr::f32>(40.0f, 60.0f), 
                    irr::core::vector3df(-10, 0, 35)) ;
    this->timeDigitA = this->smgr->addBillboardTextSceneNode(
                    this->textFont,
                    irr::core::stringw(0).c_str(), 
                    this->counter, 
                    irr::core::dimension2d<irr::f32>(40.0f, 60.0f), 
                    irr::core::vector3df(-10, 0, 80)) ;

	// Don't use lightning	
	this->counter->setMaterialFlag(			irr::video::EMF_LIGHTING, false) ;
	this->timeDigitA->setMaterialFlag(		irr::video::EMF_LIGHTING, false) ; 
	this->timeDigitB->setMaterialFlag(		irr::video::EMF_LIGHTING, false) ; 
	this->timeSeparator->setMaterialFlag(	irr::video::EMF_LIGHTING, false) ; 
	this->timeDigitD->setMaterialFlag(		irr::video::EMF_LIGHTING, false) ; 
	this->timeDigitE->setMaterialFlag(		irr::video::EMF_LIGHTING, false) ;
	
 	// Add an animator
 	this->counter->addAnimator(this->smgr->createFlyStraightAnimator(irr::core::vector3df(500, 2000, 0), irr::core::vector3df(500, 980, 0), PAUSE_BEFORE / 2, false)) ;
 	
 	// Add camera to see it
 	this->smgr->addCameraSceneNode(0, irr::core::vector3df(-500, 1000, 0), irr::core::vector3df(1000, 0, 0)) ;
}

void TimeCounter::setTime(int msLeft)
{
	int m = msLeft / 1000 / 60 ;
	int s = msLeft / 1000 - m * 60 ;
	
	int digitA = m / 10 ;
	int digitB = m - (digitA * 10) ;
	int digitD = s / 10 ;
	int digitE = s - (digitD * 10) ;

	this->timeDigitA->setText(irr::core::stringw(digitA).c_str()) ;
	this->timeDigitB->setText(irr::core::stringw(digitB).c_str()) ;
	this->timeDigitD->setText(irr::core::stringw(digitD).c_str()) ;
	this->timeDigitE->setText(irr::core::stringw(digitE).c_str()) ;
}
