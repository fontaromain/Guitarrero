#include "Configure.h"

////Header Include Start
////Header Include End

////Event Table Start
BEGIN_EVENT_TABLE(Configure,wxDialog)
	////Manual Code Start
	////Manual Code End
	EVT_BUTTON(ID_WXBUTTON3,Configure::WxButton3Click)
	EVT_CHOICE(ID_WXCHOICE2,Configure::WxChoice2Selected)
	
	EVT_COMMAND_SCROLL(ID_WXSLIDER1,Configure::WxSlider1Scroll)
	EVT_BUTTON(ID_WXBUTTON2,Configure::PlayClick)
	EVT_BUTTON(ID_WXBUTTON1,Configure::ExitClick)
END_EVENT_TABLE()
////Event Table End

Configure::Configure(irr::IrrlichtDevice *engine, GameParams* params, wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style), params(params), engine(engine)
{
	CreateGUIControls();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	Dialog Init
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Configure::CreateGUIControls()
{
	////GUI Items Creation Start

	WxCheckBox5 = new wxCheckBox(this, ID_WXCHECKBOX5, wxT("Sustain Mode"), wxPoint(180, 182), wxSize(100, 17), 0, wxDefaultValidator, wxT("WxCheckBox5"));
	WxCheckBox5->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxDirDialog1 =  new wxDirDialog(this, wxT("Choose a directory"), wxT(""));

	WxButton3 = new wxButton(this, ID_WXBUTTON3, wxT("Change songs path"), wxPoint(20, 204), wxSize(260, 25), 0, wxDefaultValidator, wxT("WxButton3"));
	WxButton3->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText14 = new wxStaticText(this, ID_WXSTATICTEXT14, wxT("Current Songs path"), wxPoint(20, 236), wxDefaultSize, 0, wxT("WxStaticText14"));
	WxStaticText14->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxCheckBox4 = new wxCheckBox(this, ID_WXCHECKBOX4, wxT("3D Scenery"), wxPoint(180, 161), wxSize(100, 17), 0, wxDefaultValidator, wxT("WxCheckBox4"));
	WxCheckBox4->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText13 = new wxStaticText(this, ID_WXSTATICTEXT13, wxT("Pick"), wxPoint(535, 203), wxDefaultSize, 0, wxT("WxStaticText13"));
	WxStaticText13->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText12 = new wxStaticText(this, ID_WXSTATICTEXT12, wxT("Fret 5"), wxPoint(535, 174), wxDefaultSize, 0, wxT("WxStaticText12"));
	WxStaticText12->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText11 = new wxStaticText(this, ID_WXSTATICTEXT11, wxT("Fret 4"), wxPoint(535, 143), wxDefaultSize, 0, wxT("WxStaticText11"));
	WxStaticText11->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText10 = new wxStaticText(this, ID_WXSTATICTEXT10, wxT("Fret 3"), wxPoint(535, 113), wxDefaultSize, 0, wxT("WxStaticText10"));
	WxStaticText10->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText9 = new wxStaticText(this, ID_WXSTATICTEXT9, wxT("Fret 2"), wxPoint(535, 83), wxDefaultSize, 0, wxT("WxStaticText9"));
	WxStaticText9->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText8 = new wxStaticText(this, ID_WXSTATICTEXT8, wxT("Fret 1"), wxPoint(535, 53), wxDefaultSize, 0, wxT("WxStaticText8"));
	WxStaticText8->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText7 = new wxStaticText(this, ID_WXSTATICTEXT7, wxT("Player 2"), wxPoint(430, 30), wxDefaultSize, 0, wxT("WxStaticText7"));
	WxStaticText7->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText6 = new wxStaticText(this, ID_WXSTATICTEXT6, wxT("Player 1"), wxPoint(315, 30), wxDefaultSize, 0, wxT("WxStaticText6"));
	WxStaticText6->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	wxArrayString arrayStringFor_ChoiceP2key4;
	ChoiceP2key4 = new wxChoice(this, ID_WXCHOICE14, wxPoint(420, 200), wxSize(110, 21), arrayStringFor_ChoiceP2key4, 0, wxDefaultValidator, wxT("ChoiceP2key4"));
	ChoiceP2key4->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP2key4->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP2key3;
	ChoiceP2key3 = new wxChoice(this, ID_WXCHOICE13, wxPoint(420, 170), wxSize(110, 21), arrayStringFor_ChoiceP2key3, 0, wxDefaultValidator, wxT("ChoiceP2key3"));
	ChoiceP2key3->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP2key3->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP2key2;
	ChoiceP2key2 = new wxChoice(this, ID_WXCHOICE12, wxPoint(420, 140), wxSize(110, 21), arrayStringFor_ChoiceP2key2, 0, wxDefaultValidator, wxT("ChoiceP2key2"));
	ChoiceP2key2->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP2key2->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP2key1;
	ChoiceP2key1 = new wxChoice(this, ID_WXCHOICE11, wxPoint(420, 110), wxSize(110, 21), arrayStringFor_ChoiceP2key1, 0, wxDefaultValidator, wxT("ChoiceP2key1"));
	ChoiceP2key1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP2key1->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP2key0;
	ChoiceP2key0 = new wxChoice(this, ID_WXCHOICE10, wxPoint(420, 80), wxSize(110, 21), arrayStringFor_ChoiceP2key0, 0, wxDefaultValidator, wxT("ChoiceP2key0"));
	ChoiceP2key0->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP2key0->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP2keyV;
	ChoiceP2keyV = new wxChoice(this, ID_WXCHOICE9, wxPoint(420, 50), wxSize(110, 21), arrayStringFor_ChoiceP2keyV, 0, wxDefaultValidator, wxT("ChoiceP2keyV"));
	ChoiceP2keyV->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP2keyV->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP1key4;
	ChoiceP1key4 = new wxChoice(this, ID_WXCHOICE8, wxPoint(305, 200), wxSize(110, 21), arrayStringFor_ChoiceP1key4, 0, wxDefaultValidator, wxT("ChoiceP1key4"));
	ChoiceP1key4->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP1key4->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP1key3;
	ChoiceP1key3 = new wxChoice(this, ID_WXCHOICE7, wxPoint(305, 170), wxSize(110, 21), arrayStringFor_ChoiceP1key3, 0, wxDefaultValidator, wxT("ChoiceP1key3"));
	ChoiceP1key3->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP1key3->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP1key2;
	ChoiceP1key2 = new wxChoice(this, ID_WXCHOICE6, wxPoint(305, 140), wxSize(110, 21), arrayStringFor_ChoiceP1key2, 0, wxDefaultValidator, wxT("ChoiceP1key2"));
	ChoiceP1key2->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP1key2->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP1key1;
	ChoiceP1key1 = new wxChoice(this, ID_WXCHOICE5, wxPoint(305, 110), wxSize(110, 21), arrayStringFor_ChoiceP1key1, 0, wxDefaultValidator, wxT("ChoiceP1key1"));
	ChoiceP1key1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP1key1->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP1key0;
	ChoiceP1key0 = new wxChoice(this, ID_WXCHOICE4, wxPoint(305, 80), wxSize(110, 21), arrayStringFor_ChoiceP1key0, 0, wxDefaultValidator, wxT("ChoiceP1key0"));
	ChoiceP1key0->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP1key0->SetSelection(-1);

	wxArrayString arrayStringFor_ChoiceP1keyV;
	ChoiceP1keyV = new wxChoice(this, -1, wxPoint(305, 50), wxSize(110, 21), arrayStringFor_ChoiceP1keyV, 0, wxDefaultValidator, wxT("ChoiceP1keyV"));
	ChoiceP1keyV->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	ChoiceP1keyV->SetSelection(-1);

	wxArrayString arrayStringFor_WxChoice3;
	WxChoice3 = new wxChoice(this, ID_WXCHOICE3, wxPoint(20, 170), wxSize(145, 21), arrayStringFor_WxChoice3, 0, wxDefaultValidator, wxT("WxChoice3"));
	WxChoice3->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	WxChoice3->SetSelection(-1);

	wxArrayString arrayStringFor_WxChoice2;
	WxChoice2 = new wxChoice(this, ID_WXCHOICE2, wxPoint(20, 130), wxSize(145, 21), arrayStringFor_WxChoice2, 0, wxDefaultValidator, wxT("WxChoice2"));
	WxChoice2->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	WxChoice2->SetSelection(-1);

	wxArrayString arrayStringFor_WxChoice1;
	WxChoice1 = new wxChoice(this, ID_WXCHOICE1, wxPoint(20, 49), wxSize(145, 21), arrayStringFor_WxChoice1, 0, wxDefaultValidator, wxT("WxChoice1"));
	WxChoice1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));
	WxChoice1->SetSelection(-1);

	WxStaticText5 = new wxStaticText(this, ID_WXSTATICTEXT5, wxT("(ms)"), wxPoint(256, 113), wxDefaultSize, 0, wxT("WxStaticText5"));
	WxStaticText5->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText4 = new wxStaticText(this, ID_WXSTATICTEXT4, wxT("A/V Delay"), wxPoint(190, 113), wxDefaultSize, 0, wxT("WxStaticText4"));
	WxStaticText4->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, wxT("Skins"), wxPoint(30, 153), wxDefaultSize, 0, wxT("WxStaticText3"));
	WxStaticText3->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, wxT("Languages"), wxPoint(30, 113), wxDefaultSize, 0, wxT("WxStaticText2"));
	WxStaticText2->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, wxT("Resolutions"), wxPoint(30, 30), wxDefaultSize, 0, wxT("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxSlider1 = new wxSlider(this, ID_WXSLIDER1, 0, -200, 200, wxPoint(170, 128), wxSize(115, 30), wxSL_HORIZONTAL | wxSL_SELRANGE , wxDefaultValidator, wxT("WxSlider1"));
	WxSlider1->SetRange(-200,200);
	WxSlider1->SetValue(0);
	WxSlider1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxCheckBox3 = new wxCheckBox(this, ID_WXCHECKBOX3, wxT("VSynch"), wxPoint(180, 73), wxSize(97, 17), 0, wxDefaultValidator, wxT("WxCheckBox3"));
	WxCheckBox3->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxCheckBox2 = new wxCheckBox(this, ID_WXCHECKBOX2, wxT("Stencil Buffer"), wxPoint(180, 51), wxSize(97, 17), 0, wxDefaultValidator, wxT("WxCheckBox2"));
	WxCheckBox2->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxCheckBox1 = new wxCheckBox(this, ID_WXCHECKBOX1, wxT("Fullscreen"), wxPoint(180, 29), wxSize(97, 17), 0, wxDefaultValidator, wxT("WxCheckBox1"));
	WxCheckBox1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	Play = new wxButton(this, ID_WXBUTTON2, wxT("Play"), wxPoint(445, 235), wxSize(140, 25), 0, wxDefaultValidator, wxT("Play"));
	Play->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	Exit = new wxButton(this, ID_WXBUTTON1, wxT("Exit"), wxPoint(295, 235), wxSize(140, 25), 0, wxDefaultValidator, wxT("Exit"));
	Exit->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticBox3 = new wxStaticBox(this, ID_WXSTATICBOX3, wxT("Controls Options"), wxPoint(295, 10), wxSize(291, 220));
	WxStaticBox3->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticBox2 = new wxStaticBox(this, ID_WXSTATICBOX2, wxT("Game Options"), wxPoint(10, 95), wxSize(280, 165));
	WxStaticBox2->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, wxT("Graphics Options"), wxPoint(10, 10), wxSize(280, 85));
	WxStaticBox1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, false));

	SetTitle(wxT("Configure"));
	SetIcon(wxNullIcon);
	SetSize(8,8,601,292);
	Center();
	
	////GUI Items Creation End
	
	//////////
	// Init //
	//////////
	// Get resolution list
	irr::video::IVideoModeList *videoList 	= this->engine->getVideoModeList() ;
	
	// Get the file list of lang dir
	this->engine->getFileSystem()->changeWorkingDirectoryTo(LANGS_DIR) ;
	irr::io::IFileList* langList 			= this->engine->getFileSystem()->createFileList() ;
	this->engine->getFileSystem()->changeWorkingDirectoryTo("..") ;

	// Get the file list of skins dir
	this->engine->getFileSystem()->changeWorkingDirectoryTo(SKINS_DIR) ;
	irr::io::IFileList* skinList 			= this->engine->getFileSystem()->createFileList() ;
	this->engine->getFileSystem()->changeWorkingDirectoryTo("..") ;

	// Prepare accelerator
	wxAcceleratorEntry entries[1] ;
	entries[0].Set(wxACCEL_NORMAL, WXK_RETURN, ID_WXBUTTON2) ;
	this->SetAcceleratorTable(wxAcceleratorTable(1, entries)) ;

	//////////////////////////////
	// Init resolutions listbox	//
	//////////////////////////////		
	for (int i = 0 ; i < videoList->getVideoModeCount() ; i++)
	{
		int y = videoList->getVideoModeResolution(i).Height ;
		int x = videoList->getVideoModeResolution(i).Width ;
		int d = videoList->getVideoModeDepth(i) ;
				
		// Check if it's > 800*600 and >= 16bit)
		if (x >= 800 && y >= 600 && d >=32)
		{
			WxChoice1->Insert(wxString(irr::core::stringc(
				irr::core::stringc(x) + irr::core::stringc("*") + irr::core::stringc(y) + irr::core::stringc("*") + irr::core::stringc(d)).c_str()), 0) ;
		}
	}	
	
	///////////////////////
	// Init lang listbox //	
	///////////////////////		
	for (int i = 0 ; i < langList->getFileCount() ; i++)
	{
		if (strcmp(langList->getFileName(i), "..") && strcmp(langList->getFileName(i), ".") && !langList->isDirectory(i))
		{
			irr::core::stringc lang(langList->getFileName(i)) ;
			WxChoice2->Insert(wxString(lang.subString(0, lang.find(".")).c_str()), 0) ;
		}
	}

	///////////////////////
	// Init skin listbox //	
	///////////////////////	
	for (int i = 0 ; i < skinList->getFileCount() ; i++)
	{
		if (strcmp(skinList->getFileName(i), "..") && strcmp(skinList->getFileName(i), ".") && skinList->isDirectory(i))
		{
			WxChoice3->Insert(wxString(skinList->getFileName(i)), 0) ;
		}
	}
	
	//////////////////////////////
	// Init players keys values //
	//////////////////////////////
	wxArrayString sel ;
	this->getKeys(sel) ; // Get possible keys selections once		
	this->ChoiceP1keyV->Append(sel) ;
	this->ChoiceP1key0->Append(sel) ;
	this->ChoiceP1key1->Append(sel) ;
	this->ChoiceP1key2->Append(sel) ;
	this->ChoiceP1key3->Append(sel) ;
	this->ChoiceP1key4->Append(sel) ;
	this->ChoiceP2keyV->Append(sel) ;
	this->ChoiceP2key0->Append(sel) ;
	this->ChoiceP2key1->Append(sel) ;
	this->ChoiceP2key2->Append(sel) ;
	this->ChoiceP2key3->Append(sel) ;
	this->ChoiceP2key4->Append(sel) ;
	
	///////////////////////////////
	// Load previous config file //
	///////////////////////////////
	this->loadConfig() ;

	///////////////////////
	// Check environment //
	///////////////////////
	if (!this->checkEnvironment())		
	{
		(new wxMessageDialog(NULL,
			wxString("\nSomething is wrong with your config file or you don't have any songs.\n\nYou can try to :\n - Delete './guitarreroConfig.xml'\n - Put some songs in './Songs'\n - Reinstall Guitarrero"),
			wxString("An error occured"),
			wxOK|wxCENTRE|wxICON_ERROR))->ShowModal() ;
		this->Destroy() ;
	}

	/////////////
	// Cleanup //
	/////////////
	skinList->drop() ;
	langList->drop() ;
	videoList->drop() ;
}

Configure::~Configure()
{
	/////////////
	// Cleanup //
	/////////////
	this->WxStaticText13->Destroy() ;
	this->WxStaticText12->Destroy() ;
	this->WxStaticText11->Destroy() ;
	this->WxStaticText10->Destroy() ;
	this->WxStaticText9->Destroy() ;
	this->WxStaticText8->Destroy() ;
	this->WxStaticText7->Destroy() ;
	this->WxStaticText6->Destroy() ;
	this->ChoiceP2key4->Destroy() ;
	this->ChoiceP2key3->Destroy() ;
	this->ChoiceP2key2->Destroy() ;
	this->ChoiceP2key1->Destroy() ;
	this->ChoiceP2key0->Destroy() ;
	this->ChoiceP2keyV->Destroy() ;
	this->ChoiceP1key4->Destroy() ;
	this->ChoiceP1key3->Destroy() ;
	this->ChoiceP1key2->Destroy() ;
	this->ChoiceP1key1->Destroy() ;
	this->ChoiceP1key0->Destroy() ;
	this->ChoiceP1keyV->Destroy() ;
	this->WxChoice3->Destroy() ;
	this->WxChoice2->Destroy() ;
	this->WxChoice1->Destroy() ;
	this->WxStaticText5->Destroy() ;
	this->WxStaticText4->Destroy() ;
	this->WxStaticText3->Destroy() ;
	this->WxStaticText2->Destroy() ;
	this->WxStaticText1->Destroy() ;
	this->WxSlider1->Destroy() ;
	this->WxCheckBox3->Destroy() ;
	this->WxCheckBox2->Destroy() ;
	this->WxCheckBox1->Destroy() ;
	this->Play->Destroy() ;
	this->Exit->Destroy() ;
	this->WxStaticBox3->Destroy() ;
	this->WxStaticBox2->Destroy() ;
	this->WxStaticBox1->Destroy() ;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	Languages managements
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Configure::setLang(const char* langFile)
{
	this->texts.clear() ; // Clear actual map	
  	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(langFile) ;

	while(xml && xml->read()) // While there is data
	{
    	switch(xml->getNodeType())
    	{
			case irr::io::EXN_ELEMENT :
				// For accents and specials chars, store into temp string
				irr::core::stringw line = xml->getAttributeValue("value") ;
				line.replace('é', 233) ;
				line.replace('è', 232) ;
				line.replace('ç', 231) ;
				line.replace('à', 224) ;
				line.replace('à', 226) ;
				line.replace('ô', 244) ;

				// Store value it the ressource map
				this->texts[xml->getNodeName()] = line ;
				break ;
		}
	}
	
	///////////////
	// Update UI //
	///////////////
	this->WxButton3->SetLabel(		wxString(this->getText("btnSongsPath").c_str())) ;
	this->Play->SetLabel(			wxString(this->getText("btnPlay").c_str())) ;
	this->Exit->SetLabel(			wxString(this->getText("btnExit").c_str())) ;
	this->WxStaticText7->SetLabel(	wxString(this->getText("lblPlayer2").c_str())) ;
	this->WxStaticText6->SetLabel(	wxString(this->getText("lblPlayer1").c_str())) ;
	this->WxStaticText4->SetLabel(	wxString(this->getText("lblDelay").c_str())) ;
	this->WxStaticText3->SetLabel(	wxString(this->getText("lblSkins").c_str())) ;
	this->WxStaticText2->SetLabel(	wxString(this->getText("lblLang").c_str())) ;
	this->WxStaticText1->SetLabel(	wxString(this->getText("lblRes").c_str())) ;
	this->WxCheckBox4->SetLabel(	wxString(this->getText("lblScenery").c_str())) ;
	this->WxCheckBox3->SetLabel(	wxString(this->getText("lblVSynch").c_str())) ;
	this->WxCheckBox2->SetLabel(	wxString(this->getText("lblStencilBuffer").c_str())) ;
	this->WxCheckBox1->SetLabel(	wxString(this->getText("lblFullScreen").c_str())) ;
	this->WxStaticBox3->SetLabel(	wxString(this->getText("lblControlOptions").c_str())) ;
	this->WxStaticBox2->SetLabel(	wxString(this->getText("lblGameOptions").c_str())) ;
	this->WxStaticBox1->SetLabel(	wxString(this->getText("lblGraphicOptions").c_str())) ;
	this->SetLabel(					wxString(GAME_NAME" - "GAME_VERSION" - "GAME_WEBSITE" - By "GAME_AUTHOR)) ;

	/////////////
	// Cleanup //
	/////////////
	delete xml ;
}

irr::core::stringw Configure::getText(const char* index)
{
	std::map<irr::core::stringc, irr::core::stringw>::iterator iter = this->texts.find(index) ;
	
    if (iter != this->texts.end()) // Value founded
    {
		return (*iter).second ;   
    }
    
    return "Text Not Found" ;	
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	Events callbacks
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Configure::PlayClick(wxCommandEvent& event)
{
	////////////////////////////////
	// Get the configuration back //
	////////////////////////////////
	irr::core::stringc resStr		 	= irr::core::stringc(WxChoice1->GetStringSelection().fn_str()) ;
	int firstStar 						= resStr.findFirst('*') ; 	// For parsing the str resolution
	int lastStar 						= resStr.findLast('*') ;	// Same thing 
	params->irrParams.WindowSize.Width 	= irr::convertToInt(resStr.subString(0, firstStar)) ;
	params->irrParams.WindowSize.Height = irr::convertToInt(resStr.subString(firstStar + 1, lastStar - 1 - firstStar)) ;
	params->irrParams.Bits  			= irr::convertToInt(resStr.subString(lastStar + 1, resStr.size() - lastStar - 1)) ;		
	params->languageFile  				= irr::core::stringc(irr::core::stringc(LANGS_DIR) 	+ irr::core::stringc(WxChoice2->GetStringSelection().fn_str()) + ".xml") ;
	params->skinDir 					= irr::core::stringc(irr::core::stringc(SKINS_DIR) 	+ irr::core::stringc(WxChoice3->GetStringSelection().fn_str())) ;
	params->irrParams.Fullscreen 		= WxCheckBox1->IsChecked() ;
	params->irrParams.Stencilbuffer	 	= WxCheckBox2->IsChecked() ;
	params->irrParams.Vsync 			= WxCheckBox3->IsChecked() ;
	params->use3DScenery				= WxCheckBox4->IsChecked() ;
	params->sustainMode					= WxCheckBox5->IsChecked() ;
	params->delay 						= WxSlider1->GetValue() ;
	params->play						= true ; // Set to play the game !
	params->player1KeysMap[0]	 		= this->getKeyCode(this->ChoiceP1keyV->GetStringSelection()) ;
	params->player1KeysMap[1] 			= this->getKeyCode(this->ChoiceP1key0->GetStringSelection()) ;
	params->player1KeysMap[2] 			= this->getKeyCode(this->ChoiceP1key1->GetStringSelection()) ;
	params->player1KeysMap[3] 			= this->getKeyCode(this->ChoiceP1key2->GetStringSelection()) ;
	params->player1KeysMap[4] 			= this->getKeyCode(this->ChoiceP1key3->GetStringSelection()) ;
	params->player1KeysMap[5] 			= this->getKeyCode(this->ChoiceP1key4->GetStringSelection()) ;
	params->player2KeysMap[0] 			= this->getKeyCode(this->ChoiceP2keyV->GetStringSelection()) ;
	params->player2KeysMap[1] 			= this->getKeyCode(this->ChoiceP2key0->GetStringSelection()) ;
	params->player2KeysMap[2] 			= this->getKeyCode(this->ChoiceP2key1->GetStringSelection()) ;
	params->player2KeysMap[3] 			= this->getKeyCode(this->ChoiceP2key2->GetStringSelection()) ;
	params->player2KeysMap[4] 			= this->getKeyCode(this->ChoiceP2key3->GetStringSelection()) ;
	params->player2KeysMap[5] 			= this->getKeyCode(this->ChoiceP2key4->GetStringSelection()) ;

	/////////////////
	// Save params //
	/////////////////
	this->saveConfig() ;

	/////////////////
	// Launch game //
	/////////////////
	this->Destroy() ;
}

void Configure::WxButton3Click(wxCommandEvent& event)
{
	// If user canceled
	if (wxID_CANCEL == this->WxDirDialog1->ShowModal())
	{
		return ;	
	}
	
	// Now format the path
	wxString path = this->WxDirDialog1->GetPath() ;
	path.Replace("\\", "/") ;
	path += "/" ; // Important because we access subdirectories after
	
	// Before validating this new directory, check if he's empty
	irr::core::stringc oldSongsDirectory = this->params->songsDir ;	
	this->params->songsDir = irr::core::stringc(path.fn_str()) ;
			
	if (!this->checkEnvironment()) // Check new directory	
	{
		(new wxMessageDialog(NULL,
			wxString(this->getText("lblNoSongs").c_str()),
			wxString("Error !"),
			wxOK|wxCENTRE|wxICON_ERROR))->ShowModal() ;
		
		// Restore the old directory
		this->params->songsDir = oldSongsDirectory ;
	}
	
	// Truncate for showing the path
	wxString truncatedPath = wxString(this->params->songsDir.c_str()) ;
	if (truncatedPath.Length() >= 45)
	{
		truncatedPath = wxString("[...]") + truncatedPath.Mid(truncatedPath.Length() - 45, 45) ;
	}
	
	// Update the current songs dir label
	this->WxStaticText14->SetLabel(truncatedPath) ;
}

void Configure::ExitClick(wxCommandEvent& event)
{
	this->Destroy() ;
}

void Configure::WxChoice2Selected(wxCommandEvent& event)
{
	this->update() ;
}

void Configure::WxSlider1Scroll(wxScrollEvent& event)
{
	this->update() ;
}

void Configure::update()
{	
	this->setLang(irr::core::stringc(irr::core::stringc(LANGS_DIR) + irr::core::stringc(WxChoice2->GetStringSelection().fn_str()) + ".xml").c_str()) ;
	WxStaticText5->SetLabel(wxString(irr::core::stringc(WxSlider1->GetValue()).c_str())) ;	
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	Loading and saving config file + checking environment
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Configure::checkEnvironment()
{
	/////////////////////////////////////
	// Check game environment (dir...) //
	/////////////////////////////////////
	bool check = true ;				 														// Check state	

	if (irr::io::createIrrXMLReader(this->params->languageFile.c_str())) 					// File language exists
	{
		if (irr::io::createIrrXMLReader(irr::core::stringc(this->params->skinDir + SKIN_FILE).c_str()))// File Skin exists
		{
			// Get the original working directory
			irr::core::stringc originalDir 	= this->engine->getFileSystem()->getWorkingDirectory() ;
		
			if (this->engine->getFileSystem()->changeWorkingDirectoryTo(this->params->songsDir.c_str()))// Songs dir exists
			{
				if (this->engine->getFileSystem()->createFileList()->getFileCount() <= 2) 	// Two directory (. && ..)			
				{
					check = false ;
				}
				
				// Rectore original directory
				this->engine->getFileSystem()->changeWorkingDirectoryTo(originalDir.c_str()) ;
			}
			else
			{
				check = false ;
			}
		}
		else
		{
			check = false ;
		}
	}
	else
	{
		check = false ;
	}

	return check ;		
}

void Configure::loadConfig()
{
	//////////////////////
	// Read config file //
	//////////////////////
	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(XML_ENGINE_FILE) ;
		
	while(xml && xml->read())
	{
		switch(xml->getNodeType())
		{
		case irr::io::EXN_ELEMENT :
			if (!strcmp("settings", xml->getNodeName()))
			{
				this->params->irrParams.WindowSize.Width	= xml->getAttributeValueAsInt("width") ;
				this->params->irrParams.WindowSize.Height	= xml->getAttributeValueAsInt("height") ;
				this->params->irrParams.Bits 				= xml->getAttributeValueAsInt("bits") ;
				this->params->irrParams.Fullscreen  		= xml->getAttributeValueAsInt("fullscreen") ;
			}
			else if (!strcmp("options", xml->getNodeName()))
			{
				this->params->irrParams.Vsync		 		= xml->getAttributeValueAsInt("vsync") ;
				this->params->irrParams.Stencilbuffer		= xml->getAttributeValueAsInt("stencilbuffer") ;
				this->params->use3DScenery					= xml->getAttributeValueAsInt("3DScenery") ;
				this->params->sustainMode					= xml->getAttributeValueAsInt("sustainMode") ;
			}
			else if (!strcmp("skin", xml->getNodeName()))
			{
				this->params->skinDir 						= xml->getAttributeValue("value") ;
			}
			else if (!strcmp("songs", xml->getNodeName()))
			{
				this->params->songsDir 						= xml->getAttributeValue("value") ;
			}
			else if (!strcmp("lang", xml->getNodeName()))
			{
				this->params->languageFile			 		= xml->getAttributeValue("value") ;
			}
			else if (!strcmp("player1", xml->getNodeName()))
			{
				this->params->player1KeysMap[0] 			= xml->getAttributeValueAsInt("key0") ;
				this->params->player1KeysMap[1] 			= xml->getAttributeValueAsInt("key1") ;
				this->params->player1KeysMap[2] 			= xml->getAttributeValueAsInt("key2") ;
				this->params->player1KeysMap[3] 			= xml->getAttributeValueAsInt("key3") ;
				this->params->player1KeysMap[4] 			= xml->getAttributeValueAsInt("key4") ;
			}
			else if (!strcmp("player1V", xml->getNodeName()))
			{
				this->params->player1KeysMap[5] 			= xml->getAttributeValueAsInt("keyV") ;
			}
			else if (!strcmp("player2", xml->getNodeName()))
			{
				this->params->player2KeysMap[0] 			= xml->getAttributeValueAsInt("key0") ;
				this->params->player2KeysMap[1] 			= xml->getAttributeValueAsInt("key1") ;
				this->params->player2KeysMap[2] 			= xml->getAttributeValueAsInt("key2") ;
				this->params->player2KeysMap[3] 			= xml->getAttributeValueAsInt("key3") ;
				this->params->player2KeysMap[4] 			= xml->getAttributeValueAsInt("key4") ;
			}
			else if (!strcmp("player2V", xml->getNodeName()))
			{
				this->params->player2KeysMap[5] 			= xml->getAttributeValueAsInt("keyV") ;
			}
			else if (!strcmp("delay", xml->getNodeName()))
			{
				this->params->delay			 				= xml->getAttributeValueAsInt("value") ;
			}
		}
	}
	
	///////////////
	// Update UI //
	///////////////
	irr::core::stringc lang = this->params->languageFile.subString(this->params->languageFile.findLast('/') + 1, this->params->languageFile.size() - this->params->languageFile.findLast('/')) ;
	lang 					= lang.subString(0, lang.find(".")) ;	
	irr::core::stringc skin = this->params->skinDir.subString(this->params->skinDir.findLast('/') + 1, this->params->skinDir.size() - this->params->skinDir.findLast('/')) ;
	irr::core::stringc res 	= irr::core::stringc(irr::core::stringc(this->params->irrParams.WindowSize.Width) +
											irr::core::stringc("*") + 
											irr::core::stringc(this->params->irrParams.WindowSize.Height) + 
											irr::core::stringc("*") + 
											irr::core::stringc(this->params->irrParams.Bits)
											) ;
	
	// Update
	this->WxStaticText14->SetLabel(wxString(this->params->songsDir.c_str())) ;
	this->WxCheckBox1->SetValue(this->params->irrParams.Fullscreen) ;
	this->WxCheckBox2->SetValue(this->params->irrParams.Stencilbuffer) ;
	this->WxCheckBox3->SetValue(this->params->irrParams.Vsync) ;
	this->WxCheckBox4->SetValue(this->params->use3DScenery) ;
	this->WxCheckBox5->SetValue(this->params->sustainMode) ;
	this->WxChoice3->Select(this->WxChoice3->FindString(wxString(skin.c_str()))) ;
	this->WxChoice2->Select(this->WxChoice2->FindString(wxString(lang.c_str()))) ;	
	this->WxChoice1->Select(this->WxChoice1->FindString(wxString(res.c_str()))) ;
	this->WxSlider1->SetValue(this->params->delay) ;
	this->selectValueInWxChoice(this->ChoiceP1keyV, this->params->player1KeysMap[0]) ;
	this->selectValueInWxChoice(this->ChoiceP1key0, this->params->player1KeysMap[1]) ;
	this->selectValueInWxChoice(this->ChoiceP1key1, this->params->player1KeysMap[2]) ;
	this->selectValueInWxChoice(this->ChoiceP1key2, this->params->player1KeysMap[3]) ;
	this->selectValueInWxChoice(this->ChoiceP1key3, this->params->player1KeysMap[4]) ;
	this->selectValueInWxChoice(this->ChoiceP1key4, this->params->player1KeysMap[5]) ;
	this->selectValueInWxChoice(this->ChoiceP2keyV, this->params->player2KeysMap[0]) ;
	this->selectValueInWxChoice(this->ChoiceP2key0, this->params->player2KeysMap[1]) ;
	this->selectValueInWxChoice(this->ChoiceP2key1, this->params->player2KeysMap[2]) ;
	this->selectValueInWxChoice(this->ChoiceP2key2, this->params->player2KeysMap[3]) ;
	this->selectValueInWxChoice(this->ChoiceP2key3, this->params->player2KeysMap[4]) ;
	this->selectValueInWxChoice(this->ChoiceP2key4, this->params->player2KeysMap[5]) ;
	this->update() ;

	/////////////
	// Cleanup //
	/////////////
	delete xml ;
}

void Configure::saveConfig()
{
	///////////////////////
	// Create xml writer //
	///////////////////////
	irr::io::IXMLWriter* xmlw = this->engine->getFileSystem()->createXMLWriter(XML_ENGINE_FILE) ;
	
	if (xmlw)
	{	
		xmlw->writeXMLHeader();
		xmlw->writeElement(L"config");
		xmlw->writeLineBreak();   
		xmlw->writeElement(	L"settings", 		false,
							L"width", 			irr::core::stringw(this->params->irrParams.WindowSize.Width).c_str(),
							L"height", 			irr::core::stringw(this->params->irrParams.WindowSize.Height).c_str(),
							L"bits", 			irr::core::stringw(this->params->irrParams.Bits).c_str(),
							L"fullscreen",		irr::core::stringw(this->params->irrParams.Fullscreen).c_str());									
		xmlw->writeClosingTag(L"settings");
		xmlw->writeLineBreak();
		xmlw->writeElement(	L"options", 		false,
							L"vsync", 			irr::core::stringw(this->params->irrParams.Vsync).c_str(),
							L"stencilbuffer", 	irr::core::stringw(this->params->irrParams.Stencilbuffer).c_str(),
							L"3DScenery",		irr::core::stringw(this->params->use3DScenery).c_str(),
							L"sustainMode",		irr::core::stringw(this->params->sustainMode).c_str());
		xmlw->writeClosingTag(L"options");
		xmlw->writeLineBreak();
		xmlw->writeElement(	L"skin", 			false, 
							L"value", 			irr::core::stringw(this->params->skinDir).c_str()) ;
		xmlw->writeClosingTag(L"skin") ;
		xmlw->writeLineBreak();
		xmlw->writeElement(	L"songs", 			false, 
							L"value", 			irr::core::stringw(this->params->songsDir).c_str()) ;
		xmlw->writeClosingTag(L"songs") ;
		xmlw->writeLineBreak() ;
		xmlw->writeElement(	L"lang", 			false,
							L"value", 			irr::core::stringw(this->params->languageFile).c_str()) ;
		xmlw->writeClosingTag(L"lang") ;
		xmlw->writeLineBreak() ;
		xmlw->writeElement(	L"player1", 		false,
							L"key0", 			irr::core::stringw(this->params->player1KeysMap[0]).c_str(),
							L"key1", 			irr::core::stringw(this->params->player1KeysMap[1]).c_str(),
							L"key2", 			irr::core::stringw(this->params->player1KeysMap[2]).c_str(),
							L"key3",			irr::core::stringw(this->params->player1KeysMap[3]).c_str(),
							L"key4", 			irr::core::stringw(this->params->player1KeysMap[4]).c_str());	
		xmlw->writeClosingTag(L"player1") ;
		xmlw->writeLineBreak() ;	
		xmlw->writeElement(	L"player1V", 		false,
							L"keyV", 			irr::core::stringw(this->params->player1KeysMap[5]).c_str());					
		xmlw->writeClosingTag(L"player1V") ;
		xmlw->writeLineBreak() ;								
		xmlw->writeElement(	L"player2", 		false,
							L"key0", 			irr::core::stringw(this->params->player2KeysMap[0]).c_str(),
							L"key1", 			irr::core::stringw(this->params->player2KeysMap[1]).c_str(),
							L"key2", 			irr::core::stringw(this->params->player2KeysMap[2]).c_str(),
							L"key3",			irr::core::stringw(this->params->player2KeysMap[3]).c_str(),
							L"key4", 			irr::core::stringw(this->params->player2KeysMap[4]).c_str());			
		xmlw->writeClosingTag(L"player2") ;
		xmlw->writeLineBreak() ;
		xmlw->writeElement(	L"player2V", 		false,
							L"keyV", 			irr::core::stringw(this->params->player2KeysMap[5]).c_str());					
		xmlw->writeClosingTag(L"player2V") ;
		xmlw->writeLineBreak() ;	
		xmlw->writeElement(	L"delay", 			false,
							L"value", 			irr::core::stringw(this->params->delay).c_str());					
		xmlw->writeClosingTag(L"delay") ;
		xmlw->writeLineBreak() ;		
		xmlw->writeClosingTag(L"config");
		
		/////////////
		// Cleanup //
		/////////////
		xmlw->drop();	// Drop the writer	
	}
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	Managements of players keys
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Configure::getKeys(wxArrayString &selections)
{	
	selections.Insert(wxString("BACK"), 0) ;
	selections.Insert(wxString("TAB"), 0) ;
	selections.Insert(wxString("CLEAR"), 0) ;
	selections.Insert(wxString("SHIFT"), 0) ;
	selections.Insert(wxString("CONTROL"), 0) ;
	selections.Insert(wxString("MENU"), 0) ;
	selections.Insert(wxString("PAUSE"), 0) ;
	selections.Insert(wxString("SPACE"), 0) ;
	selections.Insert(wxString("PRIOR"), 0) ;
	selections.Insert(wxString("NEXT"), 0) ;
	selections.Insert(wxString("END"), 0) ;
	selections.Insert(wxString("HOME"), 0) ;
	selections.Insert(wxString("LEFT"), 0) ;
	selections.Insert(wxString("UP"), 0) ;
	selections.Insert(wxString("RIGHT"), 0) ;
	selections.Insert(wxString("DOWN"), 0) ;
	selections.Insert(wxString("MULTIPLY"), 0) ;
	selections.Insert(wxString("ADD"), 0) ;
	selections.Insert(wxString("SEPARATOR"), 0) ;
	selections.Insert(wxString("SUBTRACT"), 0) ;
	selections.Insert(wxString("DECIMAL"), 0) ;
	selections.Insert(wxString("DIVIDE"), 0) ;
	selections.Insert(wxString("SCROLL"), 0) ;
	selections.Insert(wxString("LSHIFT"), 0) ;
	selections.Insert(wxString("RSHIFT"), 0) ;
	selections.Insert(wxString("LCONTROL"), 0) ;
	selections.Insert(wxString("RCONTROL"), 0) ;
	selections.Insert(wxString("RETURN"), 0) ;
	selections.Insert(wxString("0"), 0) ;
	selections.Insert(wxString("1"), 0) ;
	selections.Insert(wxString("2"), 0) ;
	selections.Insert(wxString("3"), 0) ;
	selections.Insert(wxString("4"), 0) ;
	selections.Insert(wxString("5"), 0) ;
	selections.Insert(wxString("6"), 0) ;
	selections.Insert(wxString("7"), 0) ;
	selections.Insert(wxString("8"), 0) ;
	selections.Insert(wxString("9"), 0) ;
	selections.Insert(wxString("A"), 0) ;
	selections.Insert(wxString("B"), 0) ;
	selections.Insert(wxString("C"), 0) ;
	selections.Insert(wxString("D"), 0) ;
	selections.Insert(wxString("E"), 0) ;
	selections.Insert(wxString("F"), 0) ;
	selections.Insert(wxString("G"), 0) ;
	selections.Insert(wxString("H"), 0) ;
	selections.Insert(wxString("I"), 0) ;
	selections.Insert(wxString("J"), 0) ;
	selections.Insert(wxString("K"), 0) ;
	selections.Insert(wxString("L"), 0) ;
	selections.Insert(wxString("M"), 0) ;
	selections.Insert(wxString("N"), 0) ;
	selections.Insert(wxString("O"), 0) ;
	selections.Insert(wxString("P"), 0) ;
	selections.Insert(wxString("Q"), 0) ;
	selections.Insert(wxString("R"), 0) ;
	selections.Insert(wxString("S"), 0) ;
	selections.Insert(wxString("T"), 0) ;
	selections.Insert(wxString("U"), 0) ;
	selections.Insert(wxString("V"), 0) ;
	selections.Insert(wxString("W"), 0) ;
	selections.Insert(wxString("X"), 0) ;
	selections.Insert(wxString("Y"), 0) ;
	selections.Insert(wxString("Z"), 0) ;	
	selections.Insert(wxString("NUMPAD0"), 0) ;
	selections.Insert(wxString("NUMPAD1"), 0) ;
	selections.Insert(wxString("NUMPAD2"), 0) ;
	selections.Insert(wxString("NUMPAD3"), 0) ;
	selections.Insert(wxString("NUMPAD4"), 0) ;
	selections.Insert(wxString("NUMPAD5"), 0) ;
	selections.Insert(wxString("NUMPAD6"), 0) ;
	selections.Insert(wxString("NUMPAD7"), 0) ;
	selections.Insert(wxString("NUMPAD8"), 0) ;
	selections.Insert(wxString("NUMPAD9"), 0) ;
	selections.Insert(wxString("F1"), 0) ;
	selections.Insert(wxString("F2"), 0) ;
	selections.Insert(wxString("F3"), 0) ;
	selections.Insert(wxString("F4"), 0) ;
	selections.Insert(wxString("F5"), 0) ;
	selections.Insert(wxString("F6"), 0) ;
	selections.Insert(wxString("F7"), 0) ;
	selections.Insert(wxString("F8"), 0) ;
	selections.Insert(wxString("F9"), 0) ;
	selections.Insert(wxString("F10"), 0) ;
	selections.Insert(wxString("F11"), 0) ;
	selections.Insert(wxString("F12"), 0) ;
	selections.Insert(wxString("F13"), 0) ;
	selections.Insert(wxString("F14"), 0) ;
	selections.Insert(wxString("F15"), 0) ;
	selections.Insert(wxString("F16"), 0) ;
	selections.Insert(wxString("F17"), 0) ;
	selections.Insert(wxString("F18"), 0) ;
	selections.Insert(wxString("F19"), 0) ;
	selections.Insert(wxString("F20"), 0) ;
	selections.Insert(wxString("F21"), 0) ;
	selections.Insert(wxString("F22"), 0) ;
	selections.Insert(wxString("F23"), 0) ;
	selections.Insert(wxString("F24"), 0) ;	
}

void Configure::selectValueInWxChoice(wxChoice* choice, int keyCode)
{
	wxString toSelect = "" ;
	
	switch(keyCode)
	{
		case irr::KEY_BACK : toSelect = "BACK" ; break ;	
		case irr::KEY_TAB : toSelect = "TAB" ; break ;
		case irr::KEY_CLEAR  : toSelect = "CLEAR" ; break ;
		case irr::KEY_RETURN : toSelect = "RETURN" ; break ;
		case irr::KEY_SHIFT : toSelect = "SHIFT" ; break ;
		case irr::KEY_CONTROL : toSelect = "CONTROL" ; break ;
		case irr::KEY_MENU : toSelect = "MENU" ; break ;
		case irr::KEY_PAUSE : toSelect = "PAUSE" ; break ;
		case irr::KEY_SPACE : toSelect = "SPACE" ; break ;
		case irr::KEY_PRIOR : toSelect = "PRIOR" ; break ;
		case irr::KEY_NEXT : toSelect = "NEXT" ; break ;
		case irr::KEY_END : toSelect = "END" ; break ;
		case irr::KEY_HOME : toSelect = "HOME" ; break ;
		case irr::KEY_LEFT : toSelect = "LEFT" ; break ;
		case irr::KEY_UP : toSelect = "UP" ; break ;
		case irr::KEY_RIGHT : toSelect = "RIGHT" ; break ;
		case irr::KEY_DOWN : toSelect = "DOWN" ; break ;
		case irr::KEY_KEY_0 : toSelect = "0" ; break ;
		case irr::KEY_KEY_1 : toSelect = "1" ; break ;
		case irr::KEY_KEY_2 : toSelect = "2" ; break ;
		case irr::KEY_KEY_3 : toSelect = "3" ; break ;
		case irr::KEY_KEY_4 : toSelect = "4" ; break ;
		case irr::KEY_KEY_5 : toSelect = "5" ; break ;
		case irr::KEY_KEY_6 : toSelect = "6" ; break ;
		case irr::KEY_KEY_7 : toSelect = "7" ; break ;
		case irr::KEY_KEY_8 : toSelect = "8" ; break ;
		case irr::KEY_KEY_9 : toSelect = "9" ; break ;
		case irr::KEY_KEY_A : toSelect = "A" ; break ;
		case irr::KEY_KEY_B : toSelect = "B" ; break ;
		case irr::KEY_KEY_C : toSelect = "C" ; break ;
		case irr::KEY_KEY_D : toSelect = "D" ; break ;
		case irr::KEY_KEY_E : toSelect = "E" ; break ;
		case irr::KEY_KEY_F : toSelect = "F" ; break ;
		case irr::KEY_KEY_G : toSelect = "G" ; break ;
		case irr::KEY_KEY_H : toSelect = "H" ; break ;
		case irr::KEY_KEY_I : toSelect = "I" ; break ;
		case irr::KEY_KEY_J : toSelect = "J" ; break ;
		case irr::KEY_KEY_K : toSelect = "K" ; break ;
		case irr::KEY_KEY_L : toSelect = "L" ; break ;
		case irr::KEY_KEY_M : toSelect = "M" ; break ;
		case irr::KEY_KEY_N : toSelect = "N" ; break ;
		case irr::KEY_KEY_O : toSelect = "O" ; break ;
		case irr::KEY_KEY_P : toSelect = "P" ; break ;
		case irr::KEY_KEY_Q : toSelect = "Q" ; break ;
		case irr::KEY_KEY_R : toSelect = "R" ; break ;
		case irr::KEY_KEY_S : toSelect = "S" ; break ;
		case irr::KEY_KEY_T : toSelect = "T" ; break ;
		case irr::KEY_KEY_U : toSelect = "U" ; break ;
		case irr::KEY_KEY_V : toSelect = "V" ; break ;
		case irr::KEY_KEY_W : toSelect = "W" ; break ;
		case irr::KEY_KEY_X : toSelect = "X" ; break ;
		case irr::KEY_KEY_Y : toSelect = "Y" ; break ;
		case irr::KEY_KEY_Z : toSelect = "Z" ; break ;
		case irr::KEY_NUMPAD0 : toSelect = "NUMPAD0" ; break ;
		case irr::KEY_NUMPAD1 : toSelect = "NUMPAD1" ; break ;
		case irr::KEY_NUMPAD2 : toSelect = "NUMPAD2" ; break ;
		case irr::KEY_NUMPAD3 : toSelect = "NUMPAD3" ; break ;
		case irr::KEY_NUMPAD4 : toSelect = "NUMPAD4" ; break ;
		case irr::KEY_NUMPAD5 : toSelect = "NUMPAD5" ; break ;
		case irr::KEY_NUMPAD6 : toSelect = "NUMPAD6" ; break ;
		case irr::KEY_NUMPAD7 : toSelect = "NUMPAD7" ; break ;
		case irr::KEY_NUMPAD8 : toSelect = "NUMPAD8" ; break ;
		case irr::KEY_NUMPAD9 : toSelect = "NUMPAD9" ; break ;
		case irr::KEY_MULTIPLY : toSelect = "MULTIPLY" ; break ;
		case irr::KEY_ADD : toSelect = "ADD" ; break ;
		case irr::KEY_SEPARATOR : toSelect = "SEPARATOR" ; break ;
		case irr::KEY_SUBTRACT : toSelect = "SUBTRACT" ; break ;
		case irr::KEY_DECIMAL : toSelect = "DECIMAL" ; break ;
		case irr::KEY_DIVIDE : toSelect = "DIVIDE" ; break ;
		case irr::KEY_F1 : toSelect = "F1" ; break ;
		case irr::KEY_F2 : toSelect = "F2" ; break ;
		case irr::KEY_F3 : toSelect = "F3" ; break ;
		case irr::KEY_F4 : toSelect = "F4" ; break ;
		case irr::KEY_F5 : toSelect = "F5" ; break ;
		case irr::KEY_F6 : toSelect = "F6" ; break ;
		case irr::KEY_F7 : toSelect = "F7" ; break ;
		case irr::KEY_F8 : toSelect = "F8" ; break ;
		case irr::KEY_F9 : toSelect = "F9" ; break ;
		case irr::KEY_F10 : toSelect = "F10" ; break ;
		case irr::KEY_F11 : toSelect = "F11" ; break ;
		case irr::KEY_F12 : toSelect = "F12" ; break ;
		case irr::KEY_F13 : toSelect = "F13" ; break ;
		case irr::KEY_F14 : toSelect = "F14" ; break ;
		case irr::KEY_F15 : toSelect = "F15" ; break ;
		case irr::KEY_F16 : toSelect = "F16" ; break ;
		case irr::KEY_F17 : toSelect = "F17" ; break ;
		case irr::KEY_F18 : toSelect = "F18" ; break ;
		case irr::KEY_F19 : toSelect = "F19" ; break ;
		case irr::KEY_F20 : toSelect = "F20" ; break ;
		case irr::KEY_F21 : toSelect = "F21" ; break ;
		case irr::KEY_F22 : toSelect = "F22" ; break ;
		case irr::KEY_F23 : toSelect = "F23" ; break ;
		case irr::KEY_F24 : toSelect = "F24" ; break ;
		case irr::KEY_SCROLL : toSelect = "SCROLL" ; break ;
		case irr::KEY_LSHIFT : toSelect = "LSHIFT" ; break ;
		case irr::KEY_RSHIFT : toSelect = "RSHIFT" ; break ;
		case irr::KEY_LCONTROL : toSelect = "LCONTROL" ; break ;
		case irr::KEY_RCONTROL : toSelect = "RCONTROL" ; break ;
	}
	
	// Update the wxChoice
	choice->Select(choice->FindString(toSelect)) ;
}

int Configure::getKeyCode(wxString key)
{	
	if (key.IsSameAs(wxString("BACK"))){return irr::KEY_BACK ;}
	if (key.IsSameAs(wxString("TAB"))){return irr::KEY_TAB ;}
	if (key.IsSameAs(wxString("CLEAR"))){return irr::KEY_CLEAR ;}
	if (key.IsSameAs(wxString("RETURN"))){return irr::KEY_RETURN ;}
	if (key.IsSameAs(wxString("SHIFT"))){return irr::KEY_SHIFT ;}
	if (key.IsSameAs(wxString("CONTROL"))){return irr::KEY_CONTROL ;}
	if (key.IsSameAs(wxString("MENU"))){return irr::KEY_MENU ;}
	if (key.IsSameAs(wxString("PAUSE"))){return irr::KEY_PAUSE ;}
	if (key.IsSameAs(wxString("SPACE"))){return irr::KEY_SPACE ;}
	if (key.IsSameAs(wxString("PRIOR"))){return irr::KEY_PRIOR ;}
	if (key.IsSameAs(wxString("NEXT"))){return irr::KEY_NEXT ;}
	if (key.IsSameAs(wxString("END"))){return irr::KEY_END ;}
	if (key.IsSameAs(wxString("HOME"))){return irr::KEY_HOME ;}
	if (key.IsSameAs(wxString("LEFT"))){return irr::KEY_LEFT ;}
	if (key.IsSameAs(wxString("UP"))){return irr::KEY_UP ;}
	if (key.IsSameAs(wxString("RIGHT"))){return irr::KEY_RIGHT ;}
	if (key.IsSameAs(wxString("DOWN"))){return irr::KEY_DOWN ;}
	if (key.IsSameAs(wxString("0"))){return irr::KEY_KEY_0 ;}
	if (key.IsSameAs(wxString("1"))){return irr::KEY_KEY_1 ;}
	if (key.IsSameAs(wxString("2"))){return irr::KEY_KEY_2 ;}
	if (key.IsSameAs(wxString("3"))){return irr::KEY_KEY_3 ;}
	if (key.IsSameAs(wxString("4"))){return irr::KEY_KEY_4 ;}
	if (key.IsSameAs(wxString("5"))){return irr::KEY_KEY_5 ;}
	if (key.IsSameAs(wxString("6"))){return irr::KEY_KEY_6 ;}
	if (key.IsSameAs(wxString("7"))){return irr::KEY_KEY_7 ;}
	if (key.IsSameAs(wxString("8"))){return irr::KEY_KEY_8 ;}
	if (key.IsSameAs(wxString("9"))){return irr::KEY_KEY_9 ;}
	if (key.IsSameAs(wxString("A"))){return irr::KEY_KEY_A ;}
	if (key.IsSameAs(wxString("B"))){return irr::KEY_KEY_B ;}
	if (key.IsSameAs(wxString("C"))){return irr::KEY_KEY_C ;} 
	if (key.IsSameAs(wxString("D"))){return irr::KEY_KEY_D ;}
	if (key.IsSameAs(wxString("E"))){return irr::KEY_KEY_E ;}
	if (key.IsSameAs(wxString("F"))){return irr::KEY_KEY_F ;}
	if (key.IsSameAs(wxString("G"))){return irr::KEY_KEY_G ;}
	if (key.IsSameAs(wxString("H"))){return irr::KEY_KEY_H ;}
	if (key.IsSameAs(wxString("I"))){return irr::KEY_KEY_I ;}
	if (key.IsSameAs(wxString("J"))){return irr::KEY_KEY_J ;} 
	if (key.IsSameAs(wxString("K"))){return irr::KEY_KEY_K ;}
	if (key.IsSameAs(wxString("L"))){return irr::KEY_KEY_L ;}
	if (key.IsSameAs(wxString("M"))){return irr::KEY_KEY_M ;}
	if (key.IsSameAs(wxString("N"))){return irr::KEY_KEY_N ;}
	if (key.IsSameAs(wxString("O"))){return irr::KEY_KEY_O ;}
	if (key.IsSameAs(wxString("P"))){return irr::KEY_KEY_P ;}
	if (key.IsSameAs(wxString("Q"))){return irr::KEY_KEY_Q ;}
	if (key.IsSameAs(wxString("R"))){return irr::KEY_KEY_R ;}
	if (key.IsSameAs(wxString("S"))){return irr::KEY_KEY_S ;}
	if (key.IsSameAs(wxString("T"))){return irr::KEY_KEY_T ;}
	if (key.IsSameAs(wxString("U"))){return irr::KEY_KEY_U ;}
	if (key.IsSameAs(wxString("V"))){return irr::KEY_KEY_V ;}
	if (key.IsSameAs(wxString("W"))){return irr::KEY_KEY_W ;}
	if (key.IsSameAs(wxString("X"))){return irr::KEY_KEY_X ;}
	if (key.IsSameAs(wxString("Y"))){return irr::KEY_KEY_Y ;}
	if (key.IsSameAs(wxString("Z"))){return irr::KEY_KEY_Z ;}
	if (key.IsSameAs(wxString("NUMPAD0"))){return irr::KEY_NUMPAD0 ;}
	if (key.IsSameAs(wxString("NUMPAD1"))){return irr::KEY_NUMPAD1 ;}
	if (key.IsSameAs(wxString("NUMPAD2"))){return irr::KEY_NUMPAD2 ;}
	if (key.IsSameAs(wxString("NUMPAD3"))){return irr::KEY_NUMPAD3 ;}
	if (key.IsSameAs(wxString("NUMPAD4"))){return irr::KEY_NUMPAD4 ;}
	if (key.IsSameAs(wxString("NUMPAD5"))){return irr::KEY_NUMPAD5 ;}
	if (key.IsSameAs(wxString("NUMPAD6"))){return irr::KEY_NUMPAD6 ;}
	if (key.IsSameAs(wxString("NUMPAD7"))){return irr::KEY_NUMPAD7 ;}
	if (key.IsSameAs(wxString("NUMPAD8"))){return irr::KEY_NUMPAD8 ;}
	if (key.IsSameAs(wxString("NUMPAD9"))){return irr::KEY_NUMPAD9 ;}
	if (key.IsSameAs(wxString("MULTIPLY"))){return irr::KEY_MULTIPLY ;}
	if (key.IsSameAs(wxString("ADD"))){return irr::KEY_ADD ;}
	if (key.IsSameAs(wxString("SEPARATOR"))){return irr::KEY_SEPARATOR ;}
	if (key.IsSameAs(wxString("SUBTRACT"))){return irr::KEY_SUBTRACT ;}
	if (key.IsSameAs(wxString("DECIMAL"))){return irr::KEY_DECIMAL ;}
	if (key.IsSameAs(wxString("DIVIDE"))){return irr::KEY_DIVIDE ;}
	if (key.IsSameAs(wxString("F1"))){return irr::KEY_F1 ;}
	if (key.IsSameAs(wxString("F2"))){return irr::KEY_F2 ;}
	if (key.IsSameAs(wxString("F3"))){return irr::KEY_F3 ;}
	if (key.IsSameAs(wxString("F4"))){return irr::KEY_F4 ;} 
	if (key.IsSameAs(wxString("F5"))){return irr::KEY_F5 ;}
	if (key.IsSameAs(wxString("F6"))){return irr::KEY_F6 ;}
	if (key.IsSameAs(wxString("F7"))){return irr::KEY_F7 ;}
	if (key.IsSameAs(wxString("F8"))){return irr::KEY_F8 ;}
	if (key.IsSameAs(wxString("F9"))){return irr::KEY_F9 ;}
	if (key.IsSameAs(wxString("F10"))){return irr::KEY_F10 ;}
	if (key.IsSameAs(wxString("F11"))){return irr::KEY_F11 ;}
	if (key.IsSameAs(wxString("F12"))){return irr::KEY_F12 ;}
	if (key.IsSameAs(wxString("F13"))){return irr::KEY_F13 ;}
	if (key.IsSameAs(wxString("F14"))){return irr::KEY_F14 ;}
	if (key.IsSameAs(wxString("F15"))){return irr::KEY_F15 ;} 
	if (key.IsSameAs(wxString("F16"))){return irr::KEY_F16 ;}
	if (key.IsSameAs(wxString("F17"))){return irr::KEY_F17 ;}
	if (key.IsSameAs(wxString("F18"))){return irr::KEY_F18 ;}
	if (key.IsSameAs(wxString("F19"))){return irr::KEY_F19 ;}
	if (key.IsSameAs(wxString("F20"))){return irr::KEY_F20 ;}
	if (key.IsSameAs(wxString("F21"))){return irr::KEY_F21 ;}
	if (key.IsSameAs(wxString("F22"))){return irr::KEY_F22 ;}
	if (key.IsSameAs(wxString("F23"))){return irr::KEY_F23 ;}
	if (key.IsSameAs(wxString("F24"))){return irr::KEY_F24 ;}
	if (key.IsSameAs(wxString("SCROLL"))){return irr::KEY_SCROLL ;}
	if (key.IsSameAs(wxString("LSHIFT"))){return irr::KEY_LSHIFT ;}
	if (key.IsSameAs(wxString("RSHIFT"))){return irr::KEY_RSHIFT ;}
	if (key.IsSameAs(wxString("LCONTROL"))){return irr::KEY_LCONTROL ;}
	if (key.IsSameAs(wxString("RCONTROL"))){return irr::KEY_RCONTROL ;}
	return irr::KEY_F1 ;
}
