#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);
	wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 35));

	wxCheckBox* checkBox = new wxCheckBox(panel, wxID_ANY, "checkbox", wxPoint(550, 55));

	wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Static Text", wxPoint(120, 180), wxSize(200, -1));

	wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "Text CHnaage", wxPoint(500, 145), wxSize(200, -1));

	wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0, 100, wxPoint(100, 250), wxSize(200, -1));


	wxGauge* gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(500, 250), wxSize(200, -1));
	gauge->SetValue(50);

	wxArrayString choices;
	choices.Add("Item 1");			  
	choices.Add("Item 2");
	choices.Add("Item 3");

	wxChoice* choiceb = new wxChoice(panel, wxID_ANY, wxPoint(150, 375), wxSize(100, -1), choices);
	choiceb->Select(0);

	wxSpinCtrl* spinCtrl = new wxSpinCtrl(panel, wxID_ANY, "hh", wxPoint(510, 575), wxSize(100, -1));/**/
	
}