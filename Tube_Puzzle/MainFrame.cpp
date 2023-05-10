
#include "GameControl.h"
#include "stack.h"
#include "MainFrame.h"
#include <iostream>
#include <wx/wx.h>
#include <wx/artprov.h>
using namespace std;

enum colIDs {
	playPanelID = 101,
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
	wxLogDebug("Entered mainFrame %p", this);
	//game round initialization
	int values[] = {1,2,3,3,1,2,3,1,2,3,1,2,0,0,0,0,0,0,0,0 };
	const int col = 5;
	const int tub = 3;
	round1 = new Game(col,tub,values);

	//window layout from here
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
	wxPanel* toolbarPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 90));
	toolbarPanel->SetBackgroundColour(wxColour(235, 235, 235));

	// Create a box sizer to layout the toolbar panel
	wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create an undo button
	wxButton* undoButton = new wxButton(toolbarPanel, wxID_ANY, "Undo");
	undoButton->SetBitmap(wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR));
	undoButton->SetToolTip("Undo last action");
	undoButton->Bind(wxEVT_BUTTON, &MainFrame::OnUndo, this);
	// Create an redo button
	wxButton* redoButton = new wxButton(toolbarPanel, wxID_ANY, "Redo");
	redoButton->SetBitmap(wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR));
	redoButton->SetToolTip("Redo previous action");

	///////////////////////tmp Panel
	int tmpID = wxID_ANY;
	m_idLabel = new wxStaticText(toolbarPanel, tmpID, wxString::Format("ID: %d", tmpID), wxDefaultPosition, wxDefaultSize);
	

	// Add a spacer to push the undo button to the right
	toolbarSizer->AddStretchSpacer();

	// Add the undo button to the toolbar
	toolbarSizer->Add(undoButton, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_CENTER_VERTICAL));
	// Add the redo button to the toolbar
	toolbarSizer->Add(redoButton, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_CENTER_VERTICAL));

	// Add the toolbar sizer to the toolbar panel
	toolbarPanel->SetSizer(toolbarSizer);

	// Add the toolbar panel to the main sizer
	mainSizer->Add(toolbarPanel, wxSizerFlags().Expand().Border(wxALL, 0));
	
	// Set the main sizer for the main panel
	mainPanel->SetSizer(mainSizer);

	// Create a play panel
	wxPanel* playPanel = new wxPanel(mainPanel, playPanelID,wxDefaultPosition,wxSize(398,368));
	playPanel->SetBackgroundColour(wxColour(210, 210, 210));
	// Create a sizer for the play panel
	wxBoxSizer* playSizer = new wxBoxSizer(wxHORIZONTAL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*TubeSet tubes(col, tub);
	tubes.fillArray(values);*/
	

	playSizer->AddStretchSpacer(); // this strecher will help centre the columns horizontally
	wxPanel* columnPanel[col];
	wxBoxSizer* columnSizer[col];
	
	/*colTubStack = new Stack * [col];*/
	//initialization of Stack for each column
	int tmpColor_n = 0;
	for (int Index = 0; Index < col ; Index++)
	{
		/*colTubStack[Index] = new Stack(col);*/

		columnPanel[Index] = new wxPanel(playPanel, col1+Index, wxDefaultPosition, wxSize(30, 200), wxTAB_TRAVERSAL);
		columnPanel[Index]->SetBackgroundColour(wxColour(255, 255, 255));
		columnSizer[Index] = new wxBoxSizer(wxVERTICAL);
		columnSizer[Index]->AddStretchSpacer();
		for (int i = 0; i < tub; i++) {
			int tmpBarID = tube1 + i + Index * 100;

			wxPanel* bar = new wxPanel(columnPanel[Index], tmpBarID, wxDefaultPosition, wxSize(25, 35));
			
			tmpColor_n = round1->getColor(Index, i);
			bar->SetBackgroundColour(round1->getWXColor(tmpColor_n));
			columnSizer[Index]->Add(bar, wxSizerFlags().Border(wxALL, 2).Center());

			bar->Bind(wxEVT_MOTION, &MainFrame::onColHover, this);
			bar->Bind(wxEVT_LEFT_DOWN, &MainFrame::onColClick, this);

			//pushing tube IDs into column's Stack
			if(tmpColor_n>0)	round1->pushIDinStack(Index, tmpBarID);
		}
		//reversing the Column's Stack 
		round1->reverseStack(Index);

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
	// Bind PlayPanel to outClick
	playPanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::onOutClick, this);

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

MainFrame::~MainFrame()
{
	wxLogDebug("-----------inside mainframe destruc%p game%p",this,round1);
	delete round1;
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
	int tubId = event.GetId();
	int tub_n = getTubID(tubId);
	int col_n = getTubColID(tubId);
	int tubColor = round1->getColor(col_n, tub_n);
	wxLogStatus(wxString::Format("col no: %d %d", col_n,tubColor));
}

void MainFrame::onColClick(wxMouseEvent& event)
{
	int tubId = event.GetId();

	int tub_n = getTubID(tubId);
	int col_n = getTubColID(tubId);
	int tmpColno = round1->getTmpCol();

	highlightSelectedCol(col_n);
	round1->setTmpColNo(col_n);
	round1->swapByClick(tmpColno,col_n);
	updateTubeColors();

	displayInfoOnPanel(tubId);
}

void MainFrame::onOutClick(wxMouseEvent& event)
{
	highlightSelectedCol(-1);
	round1->resetTmpDetails();
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

int MainFrame::getTubID(int tmp)
{
	if (tmp >= 10000) {
		tmp =(round1->getColStackTop(getTubColID(tmp)))%100 - 1;
		
	}
	else {
		tmp = tmp % 100 - 1;
	}
	return tmp;
}
void MainFrame::updateTubeColors() {
	wxLogDebug("Inside updateTubeColors%p round%p \ntube%s\nStack%s ",this,round1,round1->traverseTubeSet(),round1->traverseColStackAll());
	for (int colIndex = 0; colIndex < round1->getNumCols(); colIndex++) {
		// make stack empty to refilling
		round1->makeColStackEmpty(colIndex);
		for (int tubeIndex = 0; tubeIndex < round1->getNumTubes(); tubeIndex++) {
			int tmpBarID = tube1 + tubeIndex + colIndex * 100;
			wxPanel* bar = wxDynamicCast(FindWindow(tmpBarID), wxPanel);
			if (bar) {
				wxLogDebug("\t\tupdaterd1%p  %d %d",round1,colIndex,tubeIndex);
				int color = round1->getColor(colIndex, tubeIndex);
				bar->SetBackgroundColour(round1->getWXColor(color));
				wxLogStatus("%d",color);
				//pushing tube IDs into column's Stack
				if (color > 0)	round1->pushIDinStack(colIndex, tmpBarID);
				bar->Refresh();
			}
		}
		round1->reverseStack(colIndex);
	}
	wxLogDebug("Inside later updateTubeColors%p round%p \ntube%s\nStack%s ", this, round1, round1->traverseTubeSet(), round1->traverseColStackAll());
}

void MainFrame::highlightSelectedCol(int col_n)
{
	for (int Index = 0; Index < round1->getNumCols() ; Index++)
	{
		
		wxPanel* selectedPanel = wxDynamicCast(FindWindow(col1 + Index), wxPanel);
		selectedPanel->SetBackgroundColour(wxColour(255,255,255));
		if (Index == col_n) selectedPanel->SetBackgroundColour(wxColour(200, 200, 200));;
		selectedPanel->Refresh();
	}
}

void MainFrame::displayInfoOnPanel(int tubeID)
{
	int tubId = tubeID;
	int tub_n = getTubID(tubId);
	int col_n = getTubColID(tubId);
	int tubColor = round1->getColor(col_n, tub_n);
	int ColTop_n = getTubID(round1->getColStackTop(col_n));
	int TopTubColor = round1->getColor(col_n, ColTop_n);
	wxString str1 = wxString::Format("Clicked:%d(%d)(%d)-Col%d TOP%d(%d) ", tubId, tub_n, tubColor, col_n, ColTop_n, TopTubColor);
	wxString str2 = wxString::Format(" Count:%d", round1->getColStackCount(col_n)).Append(" ").Append(round1->traverseColStack(col_n));

	int tmpColno = round1->getTmpCol();
	wxString str3 = wxString::Format(" tmp%d", tmpColno);



	str3.Append(wxString::Format(" %d", round1->getTmpCol()));
	str3.Append(wxString::Format(" \n")).Append(round1->traverseTubeSet());
	wxString str = str1.Append("\n").Append(str2).Append(" ").Append(str3);;
	m_idLabel->SetLabelText(str);
}

void MainFrame::OnUndo(wxCommandEvent& event)
{
	wxLogDebug("inside OnUndoComman%p round1%p \nTubes:%s\nStack:%s",this,round1,round1->traverseTubeSet(),round1->traverseColStackAll());
	round1->revertAction();
	updateTubeColors();
	wxLogDebug("inside later OnUndoComman%p round1%p \nTubes:%s\nStack:%s", this, round1, round1->traverseTubeSet(), round1->traverseColStackAll());
}



