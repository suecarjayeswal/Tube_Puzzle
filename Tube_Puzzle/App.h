// app.h file
#pragma once
#include <wx/wx.h>
class App:public wxApp
{
public:
	bool OnInit();
private:
	int m_status;
};

