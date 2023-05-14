// This is the main frame. We're going to make it a class so it's easy to define how the methods are
// mainframe header file
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
	void OnColHover(wxMouseEvent& event);
	void OnColClick(wxMouseEvent& event);
	void OnOutClick(wxMouseEvent& event);

	int GetTubColID(int tmp);
	int GetTubID(int tmp);
	void UpdateTubeColors(); // updates tube panel colors based on tubeset in round
	void HighlightSelectedCol(int col_n,int col=0); // if col=-1 the column is selected dark red
	void DisplayInfoOnPanel(int tubeID); // for debugging purpose


	void OnRedo(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void OnNextLevel(wxCommandEvent& event); // handler for next level button

	void CompletionPage(); //hide columns and display completionPage

	void TubeGenerator(int arr[]); // return an array of col*tube elements whose values correspond to color of tubes
private:
	Game* current_Round; 
	int current_Game_Lvl;
	int* values;

	wxPanel* mainPanel;
	wxPanel* playPanel;
	wxBoxSizer* playSizer;
	
	wxStaticText* stepsCount;
	wxDECLARE_EVENT_TABLE();
};

enum {
	ID_QUIT = wxID_EXIT,
	ID_ABOUT = wxID_ABOUT
};



