#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	wxDECLARE_EVENT_TABLE();
};

enum {
	ID_QUIT = wxID_EXIT,
	ID_ABOUT = wxID_ABOUT
};



