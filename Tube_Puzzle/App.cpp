
#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include<cstdlib>
class MyApp : public wxApp
{
private:
	int m_status;
	int** values;
	int endLevel;
public:
	MyApp() {
		m_status = 0;
		endLevel = 5;
		values = new int*[endLevel];
		int a[]={ 1,2,1,3,4,1,5,2,2,5,2,1,4,4,4,5,5,3,3,3,0,0,0,0,0,0,0,0,0};
		int b[]= { 1,2,3,3,1,2,1,4,3,2,5,4,1,3,5,5,5,4,2,4,0,0,0,0,0,0,0,0,0 };
		int c[] = { 1,2,1,3,4,1,5,2,2,5,2,1,4,4,4,5,5,3,3,3,0,0,0,0,0,0,0,0,0 };
		values[0] = a;
		values[1] = b;
		values[2] = c;
		wxLogDebug("%p %p",a,values[0]);
	}

	virtual bool OnInit()
	{
		int arr2[] = {1,2,1,3,4,1,5,2,2,5,2,1,4,4,4,5,5,3,3,3,0,0,0,0,0,0,0,0,0 };
		int arr[28];
		tubeGenerator((arr));
		wxLogDebug("seeValues");
		for (int Index = 0; Index < 28; Index++)
		{
			wxLogDebug("%d", arr[Index]);
		}
		
		MainFrame* frame = new MainFrame(wxT("Tube Puzzle Game "),&m_status,arr);
		frame->Bind(wxEVT_CLOSE_WINDOW, &MyApp::OnMainFrameClose, this); // Bind the close event to a handler function
		frame->Show(true);

		wxLogDebug("OnInit");
	
		return true;
	}

	void OnMainFrameClose(wxCloseEvent& event)
	{
		// Check the status value

		if (m_status > 0 && m_status<endLevel)
		{
			int arr[28];
			tubeGenerator((arr));
			//int values[] = { 1,2,3,3,1,2,1,4,3,2,5,4,1,3,5,5,5,4,2,4,0,0,0,0,0,0,0,0,0};
			MainFrame* frame = new MainFrame(wxT("Part 2"), &m_status, arr);
			//frame->Bind(wxEVT_CLOSE_WINDOW, &MyApp::OnMainFrameClose, this); // Bind the close event to a handler function
			frame->Show(true);
		}
		wxLogDebug("close click");
		event.Skip(); // Allow the default frame closing behavior
	}
	void tubeGenerator(int arr[]) {
		int a, b, c, d, e, f,i=0;
		a = b = c = d = e = 4;
		f = 8;
		srand(time(NULL));
		while ((a+b+c+d+e+f)>0)
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
		for (int Index = 0; Index < 28; Index++)
		{
			wxLogDebug("%d", arr[Index]);
		}
		wxLogDebug("sorted");
		for (int i = 0; i < 7 ; i++)
		{
			for (int j = 1;j < 4;j++) {

				if (arr[i * 4 + j] == 0) {
					int k;
					for (k = 0;k < 4;k++) if (arr[i * 4 + k] != 0) break;
					if (k-1 == 3 && arr[i * 4 + k-1] == 0) break;
					arr[i * 4 + j] = arr[i * 4 + k];
					arr[i * 4 + k] = 0;
				}
			}
		}


		for (int Index = 0; Index < 28 ; Index++)
		{
			wxLogDebug("%d", arr[Index]);
		}

	}
	
};

wxIMPLEMENT_APP(MyApp);

