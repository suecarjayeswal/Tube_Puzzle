
#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
class MyApp : public wxApp
{
private:
	int m_status;
public:
	MyApp() {
		m_status = 0;
	}
	virtual bool OnInit()
	{
		int values[] = { 1,2,3,3,1,2,3,1,2,3,1,2,0,0,0,0,0,0,0,0 };
		MainFrame* frame = new MainFrame(wxT("Tube Puzzle Game"),&m_status);
		frame->Bind(wxEVT_CLOSE_WINDOW, &MyApp::OnMainFrameClose, this); // Bind the close event to a handler function
		frame->Show(true);
		return true;
	}

	void OnMainFrameClose(wxCloseEvent& event)
	{
		// Check the status value

		if (m_status == 1)
		{
			int values[] = { 1,2,3,3,1,2,3,1,2,3,1,2,0,0,0,0,0,0,0,0 };
			MainFrame* frame2 = new MainFrame(wxT("Part 2"), &m_status);
			frame2->Show(true);
		}

		event.Skip(); // Allow the default frame closing behavior
	}
};

wxIMPLEMENT_APP(MyApp);

