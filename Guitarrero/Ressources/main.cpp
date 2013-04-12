#ifdef _GRAPHIC_UI_
#include "main.h"

IMPLEMENT_APP(ConfigureApp)

bool ConfigureApp::OnInit()
{
	// Create the dialog and the game parameters 
	this->engine 	= irr::createDevice(irr::video::EDT_NULL) ;
	this->params	= new GameParams() ;
	this->dialog	= new Configure(this->engine, this->params) ;
	
	// Show the dialog 
	this->dialog->Show(true) ;

	// Everything is fine
	return true ;
}

int ConfigureApp::OnExit()
{
	// Cleanup
// BUG this->engine->drop() ;

	// Launch the game if needed
	if (this->params->play)
	{
		Game game((*this->params)) ;
	}
 
 	return 0 ;
}

#endif


#ifdef _CONSOLE_DEBUG_
#include "Game.h"

int main(void)
{
	GameParams params ;
	params.use3DScenery 				= true ;
	params.irrParams.WindowSize.Width	= 800 ;
	params.irrParams.WindowSize.Height 	= 600 ;
//	params.irrParams.Fullscreen = true ;
	params.languageFile = LANGS_DIR"French.xml" ;
	Game game(params) ;

    return 0 ;
}

#endif

