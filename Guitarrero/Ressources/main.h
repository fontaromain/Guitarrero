#ifndef __CONFIGUREApp_h__
#define __CONFIGUREApp_h__

// Needed includes
#include "Game.h"
#include "Configure.h" 

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class ConfigureApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
		
	private :
		irr::IrrlichtDevice* 	engine ;
		GameParams* 			params ;
		Configure*				dialog ;
};

#endif
