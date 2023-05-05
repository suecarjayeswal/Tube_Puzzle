
#include "MainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(500, 300))
{
    // Create a sizer to hold the columns and tubes
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    // Create the three columns of tubes
    for (int i = 0; i < 3; i++)
    {
        wxBoxSizer* column = new wxBoxSizer(wxVERTICAL);

        // Add the tubes to the column
        for (int j = 0; j < 5; j++)
        {
            wxPanel* tube = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(30, 30));
            tube->SetBackgroundColour(wxColor(255, 0, 0));
            column->Add(tube, 1,wxEXPAND | wxALL, 5);
			
        }
        // Add the column to the sizer
        sizer->Add(column,1, wxEXPAND|wxALL, 5);
    }

    // Create the undo button and add it to the sizer
    wxButton* undoBtn = new wxButton(this, ID_UNDO, "Undo");
    sizer->Add(undoBtn, 1,wxALIGN_CENTER_VERTICAL);

	// Define a class member variable to store the picked tube
	wxStaticBitmap* picked_tube = nullptr;

	// Define a flag to indicate whether a tube has been picked up
	bool tube_picked_up = false;

    // Set the window sizer
    this->SetSizerAndFit(sizer);
}

void MainFrame::OnUndo(wxCommandEvent& event)
{
    // TODO: Implement undo functionality
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(ID_UNDO, MainFrame::OnUndo)
wxEND_EVENT_TABLE()




//#include "MainFrame.h"
//#include <wx/wx.h>
//#include <wx/spinctrl.h>
//
//    
//MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
//	wxPanel* panel = new wxPanel(this);
//	wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 35));
//
//	wxCheckBox* checkBox = new wxCheckBox(panel, wxID_ANY, "checkbox", wxPoint(550, 55));
//
//	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Static Text", wxPoint(120, 180), wxSize(200, -1));
//
//	wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "Text CHnaage", wxPoint(500, 145), wxSize(200, -1));
//
//	wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0, 100, wxPoint(100, 250), wxSize(200, -1));
//
//
//	wxGauge* gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(500, 250), wxSize(200, -1));
//	gauge->SetValue(50);
//
//	wxArrayString choices;
//	choices.Add("Item 1");			  
//	choices.Add("Item 2");
//	choices.Add("Item 3");
//
//	wxChoice* choiceb = new wxChoice(panel, wxID_ANY, wxPoint(150, 375), wxSize(100, -1), choices);
//	choiceb->Select(0);
//
//	wxSpinCtrl* spinCtrl = new wxSpinCtrl(panel, wxID_ANY, "hh", wxPoint(510, 575), wxSize(100, -1));/**/
//	
//}
