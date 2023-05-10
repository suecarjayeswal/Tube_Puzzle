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
	void highlightSelectedCol(int col_n,int col=0);
	void displayInfoOnPanel(int tubeID);

	void OnRedo(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);

private:
	Game* round1;
	wxStaticText* m_idLabel;
	wxStaticText* stepsCount;
	//Stack** colTubStack;
	wxDECLARE_EVENT_TABLE();
};

enum {
	ID_QUIT = wxID_EXIT,
	ID_ABOUT = wxID_ABOUT
};



