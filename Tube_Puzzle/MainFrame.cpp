#include "gameControl.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/artprov.h>

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_QUIT, MainFrame::OnQuit)
    EVT_MENU(ID_ABOUT, MainFrame::OnAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_ABOUT, "&About\tF1", "Show about dialog");
    menuFile->AppendSeparator();
    menuFile->Append(ID_QUIT, "E&xit\tAlt-X", "Quit this program");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to Tube Puzzle Game!");

	// Create a panel to hold the main content
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	mainPanel->SetMinSize(wxSize(400, 400));

	// Create a box sizer to layout the main panel
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Create a toolbar panel
	wxPanel* toolbarPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 30));
	toolbarPanel->SetBackgroundColour(wxColour(235, 235, 235));

	// Create a box sizer to layout the toolbar panel
	wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create an undo button
	wxButton* undoButton = new wxButton(toolbarPanel, wxID_ANY, "Undo");
	undoButton->SetBitmap(wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR));
	undoButton->SetToolTip("Undo last action");


	// Add a spacer to push the undo button to the right
	toolbarSizer->AddStretchSpacer();

	// Add the undo button to the toolbar
	toolbarSizer->Add(undoButton, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_CENTER_VERTICAL));

	// Add the toolbar sizer to the toolbar panel
	toolbarPanel->SetSizer(toolbarSizer);

	// Add the toolbar panel to the main sizer
	mainSizer->Add(toolbarPanel, wxSizerFlags().Expand().Border(wxALL, 0));
	
	// Set the main sizer for the main panel
	mainPanel->SetSizer(mainSizer);

	// Create a play panel
	wxPanel* playPanel = new wxPanel(mainPanel, wxID_ANY,wxDefaultPosition,wxSize(398,368));
	playPanel->SetBackgroundColour(wxColour(210, 210, 210));
	// Create a sizer for the play panel
	wxBoxSizer* playSizer = new wxBoxSizer(wxHORIZONTAL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int values[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
	const int col = 2;
	const int tub = 5;
	TubeSet tubes(col, tub);
	tubes.fillArray(values);
	

	playSizer->AddStretchSpacer(); // this strecher will help centre the columns horizontally
	wxPanel* columnPanel[col];
	wxBoxSizer* columnSizer[col];

	for (int Index = 0; Index < col ; Index++)
	{
		columnPanel[Index] = new wxPanel(playPanel, wxID_ANY, wxDefaultPosition, wxSize(30, 200), wxTAB_TRAVERSAL);
		columnPanel[Index]->SetBackgroundColour(wxColour(255, 255, 255));
		columnSizer[Index] = new wxBoxSizer(wxVERTICAL);
		columnSizer[Index]->AddStretchSpacer();
		for (int i = 0; i < tub; i++) {
			wxPanel* bar = new wxPanel(columnPanel[Index], wxID_ANY, wxDefaultPosition, wxSize(25, 35));
			bar->SetBackgroundColour(tubes.GetColor(tubes.get(Index,i)));
			columnSizer[Index]->Add(bar, wxSizerFlags().Border(wxALL, 2).Center());
		}
		columnSizer[Index]->AddStretchSpacer();
		columnPanel[Index]->SetSizer(columnSizer[Index]);
		playSizer->Add(columnPanel[Index], wxSizerFlags().Center().Border(wxALL, 5));
	}
	playSizer->AddStretchSpacer(); // this strecher will help centre the columns horizontally
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// Set the play sizer for the play panel
	playPanel->SetSizer(playSizer);
	// Add the play panel to the main sizer, centering it within the main panel
	mainSizer->AddStretchSpacer();
	mainSizer->Add(playPanel, wxSizerFlags().Center().Border(wxALL, 5).Proportion(1));
	mainSizer->AddStretchSpacer();

	// Add the main panel to the frame
	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->AddStretchSpacer();
	frameSizer->Add(mainPanel, wxSizerFlags(1).Align(wxALIGN_CENTER));
	frameSizer->AddStretchSpacer();
	SetSizer(frameSizer);


}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("Tube Puzzle Game is a game in which players solve puzzles by manipulating tubes on a board.", "About Tube Puzzle Game", wxOK | wxICON_INFORMATION, this);
}
