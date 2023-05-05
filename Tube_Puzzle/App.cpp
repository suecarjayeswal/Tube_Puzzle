
#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MainFrame* frame = new MainFrame(wxT("Tube Puzzle Game"));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);


//#include "App.h"
//#include "MainFrame.h"
//#include <wx/wx.h>
//
//wxIMPLEMENT_APP(App);
//bool App::OnInit() {
//	MainFrame* mainFrame = new MainFrame(" C++ GUI");
//	mainFrame->SetClientSize(800, 600);
//	mainFrame->Center();
//	mainFrame->Show();
//	return true;
//}