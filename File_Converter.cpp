#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/textfile.h>
#include <wx/filename.h>
#include "Tools.h"

enum {
    ID_MENU_OPEN_FILE = wxID_HIGHEST + 1,
    ID_MENU_OPEN_DIR
};

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
    void SaveDirectory(wxCommandEvent& event);
    wxString  filePath;
    wxString  directory;
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
    fileMenu->Append(ID_MENU_OPEN_FILE, "&Open File\tCtrl+O", "Open a file");
    fileMenu->Append(ID_MENU_OPEN_DIR, "&Choose directory\tCtrl+D", "Choose a directory");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");

    SetMenuBar(menuBar); 
 
    //Button for file path
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxButton* openfile = new wxButton(panel, wxID_ANY, "Select File", wxPoint(120, 60), wxSize(150, 40));

    //Button for conversion
    wxButton* conversion = new wxButton(panel, wxID_ANY, "Convert", wxPoint(0, 60), wxSize(150, 40));

    // Event binding
    openfile->Bind(wxEVT_BUTTON, &MyFrame::OnOpenFile, this);
    conversion -> Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { 
        if (this->filePath.IsEmpty()) {
            wxMessageBox("Please select a file first!", "Error", wxOK | wxICON_ERROR);
            return;
        }
        if (this->directory.IsEmpty()) {
            wxMessageBox("Please select a save directory first!", "Error", wxOK | wxICON_ERROR);
            return;
        }
        
        wxFileName inputFile(this->filePath);
        wxString outputPath = this->directory + "\\" + inputFile.GetName() + ".pdf";
        
        EmbedPythonConvert((this->filePath).ToStdString(), outputPath.ToStdString());
        wxMessageBox("Conversion completed!\nSaved to: " + outputPath, "Success", wxOK | wxICON_INFORMATION);
    });

    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnOpenFile, this, ID_MENU_OPEN_FILE);
    Bind(wxEVT_MENU, &MyFrame::SaveDirectory, this, ID_MENU_OPEN_DIR);
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

    filePath = openFileDialog.GetPath();
}

// Directory to save file
void MyFrame::SaveDirectory(wxCommandEvent& event) {
    wxDirDialog dlg(this, "Choose a folder");

    if (dlg.ShowModal() == wxID_OK)
    {
        directory = dlg.GetPath();
    }
}

// Exit
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
