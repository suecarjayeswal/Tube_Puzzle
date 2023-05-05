
#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void OnUndo(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_UNDO = wxID_HIGHEST + 1
};

//#pragma once
//#include <wx/wx.h>
//
//class mainframe: public wxframe
//{
//public:
//	mainframe(const wxstring& title);
//
//};

