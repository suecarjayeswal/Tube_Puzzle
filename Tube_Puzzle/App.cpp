
#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include<cstdlib>
class MyApp : public wxApp
{
public:
	virtual bool OnInit()
	{
		MainFrame* frame = new MainFrame(wxT("Tube Puzzle Game "));
		frame->Show(true);
		wxLogDebug("OnInit");
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);

