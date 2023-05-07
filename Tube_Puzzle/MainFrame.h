#pragma once
#include <wx/wx.h>
#include "Stack.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void onColHover(wxMouseEvent& event);
	void onColClick(wxMouseEvent& event);
	int getTubColID(int tmp);
private:
	wxStaticText* m_idLabel;
	Stack** colTubStack;
	wxDECLARE_EVENT_TABLE();
};

enum {
	ID_QUIT = wxID_EXIT,
	ID_ABOUT = wxID_ABOUT
};



