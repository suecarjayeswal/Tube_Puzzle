
// MainFrame implementation file
#include "GameControl.h"
#include "stack.h"
#include "MainFrame.h"
#include <iostream>
#include <wx/wx.h>
#include <wx/artprov.h>
using namespace std;

enum colIDs {
	stepsCID = 2,
	levelCID = 3,
	completionPanelID = 9,
	playPanelID = 101,
	col1 = 10001,
	col2,
	tube1 = 1001,
	tube2,
};


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_QUIT, MainFrame::OnQuit)
    EVT_MENU(ID_ABOUT, MainFrame::OnAbout)
END_EVENT_TABLE()



/**
 * This function creates the main frame of a Tube Puzzle Game, including the toolbar, play panel, and reset panel.
 *
 * @param title The title of the main window frame.
 */
MainFrame::MainFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 600))
{
	// wxLogDebug("Entered mainFrame %p", this);
	//game round initialization
	const int col = 7;
	const int tub = 4;
	current_Game_Lvl = 1;
	int arr[28];
	TubeGenerator((arr));
	current_Round = new Game(col,tub,arr);

	//window layout from here
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_ABOUT, "&About\tF1", "Show about dialog");
    menuFile->AppendSeparator();
    menuFile->Append(ID_QUIT, "E&xit\tAlt-X", "Quit this program");
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to Tube Puzzle Game! Transfer a tube over same colored tube by clicking on columns");

	// Create a panel to hold the main content
	mainPanel = new wxPanel(this, wxID_ANY);
	mainPanel->SetSize(wxSize(600, 600));
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); // a box sizer to layout the main panel

	// Create a toolbar panel
	wxPanel* toolbarPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 90));
	toolbarPanel->SetBackgroundColour(wxColour(235, 235, 235));
	wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);


	wxPanel* stepsPanel = new wxPanel(toolbarPanel, wxID_ANY);
	stepsPanel->SetBackgroundColour(wxColour(230, 230, 230));
	wxBoxSizer* stepsSizer = new wxBoxSizer(wxHORIZONTAL);
	stepsPanel->SetSizer(stepsSizer);
	stepsSizer->AddStretchSpacer();
	wxStaticText* stepsLabel = new wxStaticText(stepsPanel, wxID_ANY, "Steps: \nLevel:");
	stepsSizer->Add(stepsLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 20);
	stepsCount = new wxStaticText(stepsPanel, stepsCID, wxString::Format("%d\n%d",current_Round->getStepsCount(),current_Game_Lvl));
	stepsCount->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	stepsSizer->Add(stepsCount, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);

	toolbarSizer->Add(stepsPanel, 0, wxEXPAND | wxALL, 5);

	// Create an undo button
	wxButton* undoButton = new wxButton(toolbarPanel, wxID_ANY, "Undo");
	undoButton->SetBitmap(wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR));
	undoButton->SetToolTip("Undo last action");
	undoButton->Bind(wxEVT_BUTTON, &MainFrame::OnUndo, this);
	// Create an redo button
	wxButton* redoButton = new wxButton(toolbarPanel, wxID_ANY, "Redo");
	redoButton->SetBitmap(wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR));
	redoButton->SetToolTip("Redo previous action");
	redoButton->Bind(wxEVT_BUTTON, &MainFrame::OnRedo, this);


	// Add a spacer to push the undo button to the right
	toolbarSizer->AddStretchSpacer();

	// Add the undo button to the toolbar
	toolbarSizer->Add(undoButton, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_CENTER_VERTICAL));
	toolbarSizer->Add(redoButton, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_CENTER_VERTICAL));
	toolbarPanel->SetSizer(toolbarSizer);

	// Add the toolbar panel to the main sizer
	mainSizer->Add(toolbarPanel, wxSizerFlags().Expand().Border(wxALL, 0));
	mainPanel->SetSizer(mainSizer);

	// Create a play panel
	playPanel = new wxPanel(mainPanel, playPanelID,wxDefaultPosition,wxSize(598,568));
	playPanel->SetBackgroundColour(wxColour(210, 210, 210));
	playSizer = new wxBoxSizer(wxHORIZONTAL);

	playSizer->AddStretchSpacer(); // this strecher will help centre the columns horizontally

	// create an array of columnPanels and columnSizers for each Panel
	wxPanel* columnPanel[col];
	wxBoxSizer* columnSizer[col];

	int tmpColor_n = 0; // temporary variable to store color of tube during iterations below
	for (int Index = 0; Index < col ; Index++)
	{
		int colWidth = 0.9*playPanel->GetSize().GetWidth() /col;
		int colHeight = 0.8 * playPanel->GetSize().GetHeight();
		columnPanel[Index] = new wxPanel(playPanel, col1+Index, wxDefaultPosition, wxSize(35, 300), wxTAB_TRAVERSAL); //definition of columnPanel
		columnPanel[Index]->SetBackgroundColour(wxColour(255, 255, 255));

		columnSizer[Index] = new wxBoxSizer(wxVERTICAL); //definition of columnSizer
		columnSizer[Index]->AddStretchSpacer();


		for (int i = 0; i < tub; i++) {
			int tmpBarID = tube1 + i + Index * 100;
			int barWidth = columnPanel[Index]->GetSize().GetWidth()*0.9;
			int barHeight = 0.95*columnPanel[Index]->GetSize().GetHeight() /tub ;
			wxPanel* bar = new wxPanel(columnPanel[Index], tmpBarID, wxDefaultPosition, wxSize(barWidth, barHeight));


			tmpColor_n = current_Round->getColor(Index, i);
			bar->SetBackgroundColour(current_Round->getWXColor(tmpColor_n));
			columnSizer[Index]->Add(bar, wxSizerFlags().Border(wxALL, 2).Center());

			bar->Bind(wxEVT_MOTION, &MainFrame::OnColHover, this); // for debugging purposes
			bar->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnColClick, this);

			//pushing tube IDs into column's stack indexed at Index inside GameControl current_Round
			if(tmpColor_n>0)	current_Round->pushIDinStack(Index, tmpBarID);
		}
		//reversing the Column's Stack
		current_Round->reverseStack(Index);

		columnSizer[Index]->AddStretchSpacer();
		columnPanel[Index]->SetSizer(columnSizer[Index]);
		playSizer->Add(columnPanel[Index], wxSizerFlags().Center().Border(wxALL, 5));
		columnPanel[Index]->Bind(wxEVT_MOTION, &MainFrame::OnColHover, this);
		columnPanel[Index]->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnColClick, this);
	}
	// saving the current state into undoStack
	current_Round->saveStateOnSwapByClick();



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	wxPanel* completionPanel = new wxPanel(playPanel, completionPanelID, wxDefaultPosition, wxSize(598 / 2, 598 / 2.1), wxBORDER_NONE);
	completionPanel->SetBackgroundColour(wxColour(255, 255, 255));
	wxBoxSizer* completionPanelSizer = new wxBoxSizer(wxVERTICAL);
	completionPanel->SetSizer(completionPanelSizer);


	wxFont font(wxFontInfo(10).Bold());
	wxStaticText* wellDoneText = new wxStaticText(completionPanel, wxID_ANY, "Well done, level completed", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wellDoneText->SetFont(font);

	completionPanelSizer->AddStretchSpacer();
	completionPanelSizer->Add(wellDoneText, 0, wxALIGN_CENTER | wxALL, 10);


	// Create a button for the next level
	wxButton* nextLevelButton = new wxButton(completionPanel, wxID_ANY, "Next Level", wxDefaultPosition, wxDefaultSize);
	nextLevelButton->Bind(wxEVT_BUTTON, &MainFrame::OnNextLevel, this);
	completionPanelSizer->Add(nextLevelButton, 0, wxALIGN_CENTER | wxALL, 10);
	completionPanelSizer->AddStretchSpacer();


	playSizer->Add(completionPanel, wxSizerFlags().Center().Border(wxALL, 5));
	playSizer->AddStretchSpacer();
	playPanel->SetSizer(playSizer);
	completionPanel->Hide(); // while gameplay is on, hide the completion panel


	playPanel->SetSizer(playSizer);
	playPanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnOutClick, this); // this bind will help unselect a column

	// Add the play panel to the main sizer, centering it within the main panel
	mainSizer->AddStretchSpacer();
	mainSizer->Add(playPanel, wxSizerFlags(1).Center().Border(wxALL, 5).Proportion(1));
	mainSizer->AddStretchSpacer();

	// Create a reset panel
	wxPanel* resetPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 40));
	resetPanel->SetBackgroundColour(wxColour(235, 235, 235));
	wxBoxSizer* resetPanelSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create a reset button
	wxButton* resetButton = new wxButton(resetPanel, wxID_ANY, "Reset");
	resetButton->SetBitmap(wxArtProvider::GetBitmap(wxART_ERROR, wxART_TOOLBAR,wxSize(20,20)));
	resetButton->SetToolTip("Reset the game");
	resetButton->Bind(wxEVT_BUTTON, &MainFrame::OnReset, this);

	// Add the reset button to the reset panel sizer
	resetPanelSizer->AddStretchSpacer();
	resetPanelSizer->Add(resetButton, wxSizerFlags().Border(wxALL, 5).Align(wxALIGN_CENTER_VERTICAL));
	resetPanel->SetSizer(resetPanelSizer);

	// Add the reset panel to the main panel sizer
	mainSizer->Add(resetPanel, wxSizerFlags().Expand().Border(wxALL, 0));

	// Add the main panel to the frame
	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	frameSizer->AddStretchSpacer();
	frameSizer->Add(mainPanel, wxSizerFlags(1).Align(wxALIGN_CENTER));
	frameSizer->AddStretchSpacer();
	SetSizer(frameSizer);
}

/**
 * The destructor of the MainFrame class deletes the current_Round object.
 */
MainFrame::~MainFrame()
{
	// wxLogDebug("-----------inside mainframe destruc%p game%p",this,current_Round);
	delete current_Round;
}

/**
 * The function closes the main frame of the application when the quit command is triggered.
 *
 * @param WXUNUSED WXUNUSED is a macro defined in the wxWidgets library that is used to indicate that a function parameter
 * is intentionally unused and should not generate a compiler warning. It is typically used to avoid warnings about unused
 * parameters in function definitions.
 */
void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("The Tube Puzzle Game is a C++ project that presents an engaging and challenging puzzle-solving experience. It involves arranging a grid of tubes in a specific order by swapping them within columns.\n\n It was created by Himanshu Gurung and Swikar Jaiswal for partial fulfillment of their course COMP 202 under supervision of Dr. Prakash Poudyal. \n\n We are grateful towards our supervisor and Department of Mathematics, School of Science as well as our Classmates at BSc. in Computational Mathematics 2021 Batch", "About Tube Puzzle Game", wxOK | wxICON_INFORMATION, this);
}

/**
 * The function retrieves information about a clicked object and logs the column number, color index, and whether the
 * current round is complete.
 *
 * @param event wxMouseEvent object that contains information about the mouse event that triggered the function call.
 */
void MainFrame::OnColHover(wxMouseEvent& event)
{
	int tubId = event.GetId(); // gets ID of current object clicked
	int tub_n = GetTubID(tubId); //returns index of corresponding tube or top tube of that column
	int col_n = GetTubColID(tubId); // return index of column clicked
	int tubColor = current_Round->getColor(col_n, tub_n); // return color index at given column and tube indices
	wxLogStatus(wxString::Format("col no: %d %d %d", col_n,tubColor, current_Round->roundCompleteCheck()));
}

void MainFrame::OnColClick(wxMouseEvent& event)
{
	int tubId = event.GetId();
	int tub_n = GetTubID(tubId);
	int col_n = GetTubColID(tubId);
	int tmpColno = current_Round->getTmpCol();

	HighlightSelectedCol(col_n);
	current_Round->setTmpColNo(col_n); // sets current selected column in Temporary
	bool changed = current_Round->swapByClick(tmpColno,col_n); // return if swap was successful
	wxLogStatus(wxString::Format("%d", changed));
	if (changed)
	{
		UpdateTubeColors();

	}
	else {
		if(current_Round->getTmpCol()!=-1) {
			HighlightSelectedCol(col_n,-1);
			current_Round->resetTmpDetails();
		}
	}
	// In the below, if round is completed, completionPage is shown
	if (current_Round->roundCompleteCheck()) {
		CompletionPage();
	}
}

// in below, clicking outside the columns is handled
void MainFrame::OnOutClick(wxMouseEvent& event)
{
	HighlightSelectedCol(-1);
	current_Round->resetTmpDetails();
}

// takes columnID to return index of column
int MainFrame::GetTubColID(int tmp)
{
	if (tmp >= 10000) { // if tmp is ID of column
		tmp = tmp % 10000 - 1;
	}
	else {
		tmp = (tmp - 1000) / 100; // if tmp is ID of tube
	}
	return tmp;
}

int MainFrame::GetTubID(int tmp)
{
	if (tmp >= 10000) {
		tmp =(current_Round->getColStackTop(GetTubColID(tmp)))%100 - 1;
	}
	else {
		tmp = tmp % 100 - 1;
	}
	return tmp;
}

/**
 * This function updates the colors of the tubes in a game and also updates the step counter label.
 */
void MainFrame::UpdateTubeColors() {
	for (int colIndex = 0; colIndex < current_Round->getNumCols(); colIndex++) {
		// make stack empty to refilling
		current_Round->makeColStackEmpty(colIndex);


		for (int tubeIndex = 0; tubeIndex < current_Round->getNumTubes(); tubeIndex++) {
			int tmpBarID = tube1 + tubeIndex + colIndex * 100;
			wxPanel* bar = wxDynamicCast(FindWindow(tmpBarID), wxPanel);

			if (bar) {
				int color = current_Round->getColor(colIndex, tubeIndex);
				bar->SetBackgroundColour(current_Round->getWXColor(color));
				if (color > 0)	current_Round->pushIDinStack(colIndex, tmpBarID);
				bar->Refresh();
			}
		}
		current_Round->reverseStack(colIndex);
	}
	// update StepCounter label
	wxStaticText* stepC = wxDynamicCast(FindWindow(stepsCID), wxStaticText);
	stepC->SetLabel(wxString::Format("%d\n%d", current_Round->getStepsCount(), current_Game_Lvl));
}

/**
 * This function highlights a selected column in a wxPanel by changing its background color.
 *
 * @param col_n The index of the column to be highlighted.
 * @param ifHardColor An integer parameter that determines whether to highlight the selected column with a hard color or
 * not. If the value is -1, the selected column will be highlighted with a hard color. Otherwise, it will be highlighted
 * with a normal color.
 */
void MainFrame::HighlightSelectedCol(int col_n,int ifHardColor)
{
	// unHighlight all other columns except at index col_n
	// if ifHardColor == -1, highlight it hard
	for (int Index = 0; Index < current_Round->getNumCols() ; Index++)
	{
		wxPanel* selectedPanel = wxDynamicCast(FindWindow(col1 + Index), wxPanel);
		selectedPanel->SetBackgroundColour(wxColour(255,255,255));

		if (Index == col_n) {
			selectedPanel->SetBackgroundColour(wxColour(200, 200, 200));
			if (ifHardColor ==-1) selectedPanel->SetBackgroundColour(wxColour(100, 100, 100));

		}
		selectedPanel->Refresh();
	}
}

/**
 * The function displays information about a clicked tube and the current state of the game on a panel.
 *
 * @param tubeID The ID of the tube that was clicked on.
 */
void MainFrame::DisplayInfoOnPanel(int tubeID)
{
	int tubId = tubeID;
	int tub_n = GetTubID(tubId);
	int col_n = GetTubColID(tubId);
	int tubColor = current_Round->getColor(col_n, tub_n);
	int ColTop_n = GetTubID(current_Round->getColStackTop(col_n));
	int TopTubColor = current_Round->getColor(col_n, ColTop_n);
	wxString str1 = wxString::Format("Clicked:%d(%d)(%d)-Col%d TOP%d(%d) ", tubId, tub_n, tubColor, col_n, ColTop_n, TopTubColor);
	wxString str2 = wxString::Format(" Count:%d", current_Round->getColStackCount(col_n)).Append(" ").Append(current_Round->traverseColStack(col_n));

	int tmpColno = current_Round->getTmpCol();
	wxString str3 = wxString::Format(" tmp%d", tmpColno);

	str3.Append(wxString::Format(" %d", col_n));
	str3.Append(wxString::Format(" \n")).Append(current_Round->traverseTubeSet());
	wxString str = str1.Append("\n").Append(str2).Append(" ").Append(str3);;
}


void MainFrame::OnUndo(wxCommandEvent& event)
{
	current_Round->revertAction();
	UpdateTubeColors();
}

void MainFrame::OnRedo(wxCommandEvent& event)
{
	current_Round->undoRevert();
	UpdateTubeColors();
}

void MainFrame::OnReset(wxCommandEvent& event)
{
	//CompletionPage();
	current_Round->hardReset();
	HighlightSelectedCol(-1);
	UpdateTubeColors();

	stepsCount->Refresh();// Clear the steps count
}

/**
 * The function handles the event of moving to the next level in a game and generates a new game round with updated
 * parameters.
 *
 * @param event wxCommandEvent object that triggered the event handler function
 */
void MainFrame::OnNextLevel(wxCommandEvent& event)
{
	current_Game_Lvl++;
	delete current_Round;

	int arr[28];
	TubeGenerator((arr));
	current_Round = new Game(7, 4, arr);
	// unHide the panels and hide the completionPanel
	for (int Index = 0; Index < 7; Index++) {
		wxPanel* column = wxDynamicCast(FindWindow(col1 + Index), wxPanel);
		column->Show();
	}
	wxPanel* completionPanel = wxDynamicCast(FindWindow(completionPanelID), wxPanel);
	completionPanel->Hide();

	playPanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnOutClick, this);
	UpdateTubeColors();

	// the following forces the window to put everything in their rightful position and state // works like a charm to refresh
	playPanel->SetSize(wxSize(playPanel->GetSize().GetWidth() - current_Game_Lvl % 2, playPanel->GetSize().GetHeight()));
	this->Refresh();
}
/**
 * The function hides all columns and shows the completion page in a wxWidgets GUI application.
 */
void MainFrame::CompletionPage()
{
	// just hide all the columns and show completion Page
	for (int Index = 0; Index < 7; Index++) {
		wxPanel* column = wxDynamicCast(FindWindow(col1 + Index), wxPanel);
		column->Hide();
	}
	playPanel->Unbind(wxEVT_LEFT_DOWN, &MainFrame::OnOutClick, this); //unbinding to avoid errors
	wxPanel* completionPanel = wxDynamicCast(FindWindow(completionPanelID), wxPanel);
	completionPanel->Show();

	playPanel->SetSize(wxSize(playPanel->GetSize().GetWidth() + current_Game_Lvl % 2, playPanel->GetSize().GetHeight()));
	this->Refresh();
}

/**
 * The function generates a random array of tube colors and replaces any non-colored tubes with the first colored tube in
 * the same column.
 *
 * @param arr an integer array that represents the tubes in the game. Each element in the array represents a tube and its
 * color. The array has a length of 28, representing 7 columns and 4 tubes in each column. The colors are represented by
 * integers from 0 to 5, where 0
 */
void MainFrame::TubeGenerator(int arr[]) {

	//creating variables to store count of each of 5 colors, one var(f) to Count noColor,
	int a, b, c, d, e, f, i = 0;
	a = b = c = d = e = 4;
	f = 8;

	// just create a random number and modulo it to get tube color, use the color if colorCount Left and decrement colorCount
	srand(time(NULL));
	while ((a + b + c + d + e + f) > 0)
	{
		int value = rand() % 6;
		switch (value) {
		case 1:
			if (a == 0) continue;
			arr[i++] = 1;
			a--;
			break;
		case 2:
			if (b == 0) continue;
			arr[i++] = 2;
			b--;
			break;
		case 3:
			if (c == 0) continue;
			arr[i++] = 3;
			c--;
			break;
		case 4:
			if (d == 0) continue;
			arr[i++] = 4;
			d--;
			break;
		case 5:
			if (e == 0) continue;
			arr[i++] = 5;
			e--;
			break;
		default:
			if (f == 0) continue;
			arr[i++] = 0;
			f--;
			break;
		}
	}
	for (int i = 0; i < 7; i++)
	{
		// for each column
		for (int j = 1;j < 4;j++) {
			// for each tube
			if (arr[i * 4 + j] == 0) {
				// if it's nonColored tube then replace it the first colored tube in the column
				int k;
				for (k = 0;k < 4;k++) if (arr[i * 4 + k] != 0) break; // find index of first colored tube
				if (k - 1 == 3 && arr[i * 4 + k - 1] == 0) break; // if found no colored tube then move to next column,
				arr[i * 4 + j] = arr[i * 4 + k];
				arr[i * 4 + k] = 0;
			}
		}
	}
}
