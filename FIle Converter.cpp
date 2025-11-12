#include <wx/wx.h>

// Application class
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Main frame class
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
};

// App init
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("Hello wxWidgets!");
    frame->Show(true);
    return true;
}

// Frame constructor
MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxButton* btn = new wxButton(panel, wxID_ANY, "Click Me", wxPoint(150, 100), wxSize(100, 30));

    // event when the button has been clicked
    btn->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        wxMessageBox("Hello, wxWidgets!", "Message", wxOK | wxICON_INFORMATION);
        });
}

wxIMPLEMENT_APP(MyApp);
