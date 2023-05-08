#pragma once
#include <wx/wx.h>
#include "Stack.h"
#include "GameControl.h"

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
	~MainFrame();
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void onColHover(wxMouseEvent& event);
	void onColClick(wxMouseEvent& event);
	void onOutClick(wxMouseEvent& event);
	int getTubColID(int tmp);
	int getTubID(int tmp);
	void updateTubeColors();
	void highlightSelectedCol(int col_n);
	void displayInfoOnPanel(int tubeID);
private:
	Game* round1;
	wxStaticText* m_idLabel;
	//Stack** colTubStack;
	wxDECLARE_EVENT_TABLE();
};

enum {
	ID_QUIT = wxID_EXIT,
	ID_ABOUT = wxID_ABOUT
};



