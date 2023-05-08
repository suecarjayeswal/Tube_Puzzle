#include "TubeSet.h"
#include "stack.h"
#include "MainFrame.h"
#include <iostream>
#include <wx/wx.h>
#include <wx/artprov.h>
using namespace std;

enum colIDs {
	col1 = 10001,
	col2,
	tube1 = 1001,
	tube2
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_QUIT, MainFrame::OnQuit)
    EVT_MENU(ID_ABOUT, MainFrame::OnAbout)
	
END_EVENT_TABLE()
//
//BEGIN_EVENT_TABLE(MainFrame, wxFrame)
//EVT_MENU(ID_QUIT, MainFrame::OnQuit)
//EVT_MENU(ID_ABOUT, MainFrame::OnAbout)
//END_EVENT_TABLE()


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
	///////////////////////tmp Panel
	int tmpID = wxID_ANY;
	m_idLabel = new wxStaticText(toolbarPanel, tmpID, wxString::Format("ID: %d", tmpID), wxDefaultPosition, wxDefaultSize);
	

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
	int values[] = { 1, 2, 3, 4, 5, 1, 2, 3, 3, 2 };
	const int col = 2;
	const int tub = 5;
	TubeSet tubes(col, tub);
	tubes.fillArray(values);
	

	playSizer->AddStretchSpacer(); // this strecher will help centre the columns horizontally
	wxPanel* columnPanel[col];
	wxBoxSizer* columnSizer[col];
	cout << "Hello There" << endl;
	colTubStack = new Stack * [col];
	//initialization of Stack for each column
	
	for (int Index = 0; Index < col ; Index++)
	{
		colTubStack[Index] = new Stack();

		columnPanel[Index] = new wxPanel(playPanel, col1+Index, wxDefaultPosition, wxSize(30, 200), wxTAB_TRAVERSAL);
		columnPanel[Index]->SetBackgroundColour(wxColour(255, 255, 255));
		columnSizer[Index] = new wxBoxSizer(wxVERTICAL);
		columnSizer[Index]->AddStretchSpacer();
		for (int i = 0; i < tub; i++) {
			wxPanel* bar = new wxPanel(columnPanel[Index], tube1+i+Index*100, wxDefaultPosition, wxSize(25, 35));
			bar->SetBackgroundColour(tubes.getWXColor(tubes.getColor(Index,i)));
			columnSizer[Index]->Add(bar, wxSizerFlags().Border(wxALL, 2).Center());

			bar->Bind(wxEVT_MOTION, &MainFrame::onColHover, this);
			bar->Bind(wxEVT_LEFT_DOWN, &MainFrame::onColClick, this);

			//pushing tube IDs into column's Stack
			colTubStack[Index]->push(tube1 + i + Index * 100);
		}
		//reversing the Column's Stack 
		colTubStack[Index]->reverseStack();

		columnSizer[Index]->AddStretchSpacer();
		columnPanel[Index]->SetSizer(columnSizer[Index]);
		playSizer->Add(columnPanel[Index], wxSizerFlags().Center().Border(wxALL, 5));
		columnPanel[Index]->Bind(wxEVT_MOTION, &MainFrame::onColHover, this);
		columnPanel[Index]->Bind(wxEVT_LEFT_DOWN, &MainFrame::onColClick, this);
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

void MainFrame::onColHover(wxMouseEvent& event)
{
	
	wxLogStatus(wxString::Format("col no: %d", getTubColID(event.GetId())));
}

void MainFrame::onColClick(wxMouseEvent& event)
{
	cout << "\n Hi There Id:" << event.GetId();
	int  tmp = getTubColID(event.GetId());
	int tmpColId = colTubStack[tmp]->top();
	wxString str = wxString::Format("col no is:%d %d %d",event.GetId(), tmp,tmpColId);
	m_idLabel->SetLabelText(str);


	/*m_idLabel->SetLabelText(wxString::Format("%s", colTubStack[tmp]->traverse()));*/
	tmpColId = colTubStack[tmp]->top();
	wxPanel* clickedPanel = wxDynamicCast(FindWindow(tmpColId), wxPanel); // get a pointer to the clicked panel
	if (clickedPanel) {
		clickedPanel->SetBackgroundColour(wxColour(255,255,255)); // set the background color of the clicked panel to red
		clickedPanel->Refresh(); // refresh the panel to show the new background color
	}
}

int MainFrame::getTubColID(int tmp)
{
	if (tmp >= 10000) {
		tmp = tmp % 10000 - 1;
	}
	else {
		tmp = (tmp - 1000) / 100;
	}
	return tmp;
}


