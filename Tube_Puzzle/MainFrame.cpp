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
	playSizer->AddStretchSpacer(); // this strecher will help centre the columns horizontally
	// Create a column panel 1
	wxPanel* columnPanel1 = new wxPanel(playPanel, wxID_ANY, wxDefaultPosition, wxSize(30, 200), wxTAB_TRAVERSAL);
	columnPanel1->SetBackgroundColour(wxColour(255, 255, 255));

	// Create a column sizer 1
	wxBoxSizer* columnSizer1 = new wxBoxSizer(wxVERTICAL);
	columnSizer1->AddStretchSpacer();
	for (int i = 0; i < 5; i++) {
		wxPanel* bar = new wxPanel(columnPanel1, wxID_ANY, wxDefaultPosition, wxSize(25, 35));
		bar->SetBackgroundColour(wxColour(0, 255, 0));
		columnSizer1->Add(bar, wxSizerFlags().Border(wxALL, 2).Center());
	}
	columnSizer1->AddStretchSpacer();

	// Add the column sizer 1 to the column panel 1
	columnPanel1->SetSizer(columnSizer1);

	// Add the column panel 1 to the play sizer
	playSizer->Add(columnPanel1, wxSizerFlags().Center().Border(wxALL, 5));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create a column panel 2 and column sizer 2 (similar to column panel 1 and column sizer 1)
	wxPanel* columnPanel2 = new wxPanel(playPanel, wxID_ANY, wxDefaultPosition, wxSize(30,200), wxTAB_TRAVERSAL);
	columnPanel2->SetBackgroundColour(wxColour(255, 255, 255));
	
	wxBoxSizer* columnSizer2 = new wxBoxSizer(wxVERTICAL);
	columnSizer2->AddStretchSpacer();
	for (int i = 0; i < 5; i++) {
		wxPanel* bar = new wxPanel(columnPanel2, wxID_ANY, wxDefaultPosition, wxSize(25, 35));
		bar->SetBackgroundColour(wxColour(0, 255, 0));
		columnSizer2->Add(bar, wxSizerFlags().Border(wxALL, 2).Center());
	}
	columnSizer2->AddStretchSpacer();

	// Add the column sizer 1 to the column panel 1
	columnPanel2->SetSizer(columnSizer2);
	// Add the column panel 1 to the play sizer
	playSizer->Add(columnPanel2, wxSizerFlags().Center().Border(wxALL, 5));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create a column panel 3 and column sizer 3 (similar to column panel 1 and column sizer 1)
	wxPanel* columnPanel3 = new wxPanel(playPanel, wxID_ANY, wxDefaultPosition, wxSize(30, 200), wxTAB_TRAVERSAL);
	columnPanel3->SetBackgroundColour(wxColour(255, 255, 255));

	wxBoxSizer* columnSizer3 = new wxBoxSizer(wxVERTICAL);
	columnSizer3->AddStretchSpacer();
	for (int i = 0; i < 5; i++) {
		wxPanel* bar = new wxPanel(columnPanel3, wxID_ANY, wxDefaultPosition, wxSize(25, 35));
		bar->SetBackgroundColour(wxColour(0, 255, 0));
		columnSizer3->Add(bar, wxSizerFlags().Border(wxALL, 2).Center());
	}
	columnSizer3->AddStretchSpacer();

	// Add the column sizer 1 to the column panel 1
	columnPanel3->SetSizer(columnSizer3);
	// Add the column panel 1 to the play sizer
	playSizer->Add(columnPanel3, wxSizerFlags().Center().Border(wxALL, 5));
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
