#ifndef __CONFIGURE_h__
#define __CONFIGURE_h__

#include "Game.h"

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif


////Header Include Start
#include <wx/dirdlg.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/statbox.h>
////Header Include End

////Dialog Style Start
#undef Configure_STYLE
#define Configure_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX
////Dialog Style End

class Configure : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		Configure(irr::IrrlichtDevice *engine, GameParams* params, wxWindow *parent = NULL, wxWindowID id = 1, const wxString &title = wxT("Configure"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Configure_STYLE);
		~Configure() ;
		void ExitClick(wxCommandEvent& event);
		void PlayClick(wxCommandEvent& event);
		void ConfigureActivate(wxActivateEvent& event);
		void WxSlider1Scroll(wxScrollEvent& event);
		void WxChoice2Selected(wxCommandEvent& event );
		void ChoiceP1key1Selected(wxCommandEvent& event );
		void WxButton3Click(wxCommandEvent& event);

	private:
		////GUI Control Declaration Start
		wxCheckBox *WxCheckBox5;
		wxDirDialog *WxDirDialog1;
		wxButton *WxButton3;
		wxStaticText *WxStaticText14;
		wxCheckBox *WxCheckBox4;
		wxStaticText *WxStaticText13;
		wxStaticText *WxStaticText12;
		wxStaticText *WxStaticText11;
		wxStaticText *WxStaticText10;
		wxStaticText *WxStaticText9;
		wxStaticText *WxStaticText8;
		wxStaticText *WxStaticText7;
		wxStaticText *WxStaticText6;
		wxChoice *ChoiceP2key4;
		wxChoice *ChoiceP2key3;
		wxChoice *ChoiceP2key2;
		wxChoice *ChoiceP2key1;
		wxChoice *ChoiceP2key0;
		wxChoice *ChoiceP2keyV;
		wxChoice *ChoiceP1key4;
		wxChoice *ChoiceP1key3;
		wxChoice *ChoiceP1key2;
		wxChoice *ChoiceP1key1;
		wxChoice *ChoiceP1key0;
		wxChoice *ChoiceP1keyV;
		wxChoice *WxChoice3;
		wxChoice *WxChoice2;
		wxChoice *WxChoice1;
		wxStaticText *WxStaticText5;
		wxStaticText *WxStaticText4;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxSlider *WxSlider1;
		wxCheckBox *WxCheckBox3;
		wxCheckBox *WxCheckBox2;
		wxCheckBox *WxCheckBox1;
		wxButton *Play;
		wxButton *Exit;
		wxStaticBox *WxStaticBox3;
		wxStaticBox *WxStaticBox2;
		wxStaticBox *WxStaticBox1;
		////GUI Control Declaration End

		enum
		{
			////GUI Enum Control ID Start
			ID_WXCHECKBOX5 = 1048,
			ID_WXBUTTON3 = 1047,
			ID_WXSTATICTEXT14 = 1046,
			ID_WXCHECKBOX4 = 1044,
			ID_WXSTATICTEXT13 = 1043,
			ID_WXSTATICTEXT12 = 1042,
			ID_WXSTATICTEXT11 = 1041,
			ID_WXSTATICTEXT10 = 1040,
			ID_WXSTATICTEXT9 = 1039,
			ID_WXSTATICTEXT8 = 1038,
			ID_WXSTATICTEXT7 = 1037,
			ID_WXSTATICTEXT6 = 1036,
			ID_WXCHOICE14 = 1035,
			ID_WXCHOICE13 = 1034,
			ID_WXCHOICE12 = 1033,
			ID_WXCHOICE11 = 1032,
			ID_WXCHOICE10 = 1031,
			ID_WXCHOICE9 = 1030,
			ID_WXCHOICE8 = 1028,
			ID_WXCHOICE7 = 1027,
			ID_WXCHOICE6 = 1026,
			ID_WXCHOICE5 = 1025,
			ID_WXCHOICE4 = 1024,
			ID_WXCHOICE3 = 1021,
			ID_WXCHOICE2 = 1020,
			ID_WXCHOICE1 = 1019,
			ID_WXSTATICTEXT5 = 1018,
			ID_WXSTATICTEXT4 = 1017,
			ID_WXSTATICTEXT3 = 1016,
			ID_WXSTATICTEXT2 = 1015,
			ID_WXSTATICTEXT1 = 1014,
			ID_WXSLIDER1 = 1010,
			ID_WXCHECKBOX3 = 1005,
			ID_WXCHECKBOX2 = 1004,
			ID_WXCHECKBOX1 = 1003,
			ID_WXBUTTON2 = 1002,
			ID_WXBUTTON1 = 1001,
			ID_WXSTATICBOX3 = 1023,
			ID_WXSTATICBOX2 = 1013,
			ID_WXSTATICBOX1 = 1012,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_
		};
		
		void loadConfig() ;
		void saveConfig() ;
		void update() ;
		void CreateGUIControls();
		void setLang(const char* langFile) ;	
		bool checkEnvironment() ;
		void selectValueInWxChoice(wxChoice* choice, int keyCode) ;
		void getKeys(wxArrayString& array) ;
		int getKeyCode(wxString key) ;
		
		irr::IrrlichtDevice *engine ;
		GameParams *params ;
		irr::core::stringw	getText(const char* index) ;
		std::map<irr::core::stringc, irr::core::stringw> texts ;
};

#endif
