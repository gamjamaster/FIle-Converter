#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/textfile.h>


// App class
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Main frame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    void OnExit(wxCommandEvent& event);
    void OnOpenFile(wxCommandEvent& event);
};

wxIMPLEMENT_APP(MyApp);

// App init
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("My wxWidgets Notepad");
    frame->Show(true);
    return true;
}

// Main frame constructor
MyFrame::MyFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400))
{
    // Menu bar
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT, "&Exit\tCtrl+Q", "Quit the application");
    fileMenu->Append(wxFD_OPEN, "&Open File\tCtrl+O", "Open a file");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");

    SetMenuBar(menuBar);

    //Create button
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxButton* openfile = new wxButton(panel, wxID_ANY, "Select File", wxPoint(120, 60), wxSize(150, 40));

    // Event binding
    openfile->Bind(wxEVT_BUTTON, &MyFrame::OnOpenFile, this);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnOpenFile, this, wxFD_OPEN);
}

// Open file
void MyFrame::OnOpenFile(wxCommandEvent& event) {
    wxFileDialog openFileDialog(
        this, _("Select a file"), "", "",
        "PPT|*.pptx",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString filePath = openFileDialog.GetPath();
    wxMessageBox("Selected file:\n" + filePath, "File Path");
}

// Exit
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
