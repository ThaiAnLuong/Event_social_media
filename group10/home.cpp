/**
 * @file home.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Home page containing buttons to go to different pages that provide different functionality 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "home.h"

using json = nlohmann::json;
/**
 * @brief Construct a new home::home object
 * 
 * @param title Title of the page
 * @param pos Position of the window
 * @param size Size of the window
 * @param user Username of the logged in user
 */
home::home(const wxString &title, const wxPoint &pos, const wxSize &size, std::string user) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	this->Bind(wxEVT_CLOSE_WINDOW, &home::closeFrame, this);

	this->user = user;
	wxColour backg_accent_colour = wxColour(22, 41, 110);

	handler = new UserDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");

	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1204, 720));
	//image here
	mainPanel->SetBackgroundColour(wxColor(13, 28, 83));

	searchPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(1204, 720));
	searchPanel->Hide();
	mainPanel->Layout();

	butPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(1204, 720));
	butPanel->Raise();

	//buttons
	butBack = new wxButton(searchPanel, wxID_ANY, "\n<\n", wxPoint(12, 7), wxSize(50, 50));
	butBack->Bind(wxEVT_BUTTON, &home::butBackClicked, this);
	butBack->SetBackgroundColour(backg_accent_colour);
	butBack->SetForegroundColour(wxColour(255, 255, 255));

	// buttons
	butBoard = new wxButton(butPanel, wxID_ANY, "\nBOARD\n", wxPoint(189, 136), wxSize(140, 140));
	butBoard->SetBackgroundColour(backg_accent_colour);
	butBoard->SetForegroundColour(wxColour(255, 255, 255));
	butBoard->Bind(wxEVT_BUTTON, &home::butDisplayClicked, this);

	butSearch = new wxButton(butPanel, wxID_ANY, "\nSEARCH\n", wxPoint(526, 404), wxSize(140, 140));
	butSearch->Bind(wxEVT_BUTTON, &home::butSearchClicked, this);
	butSearch->SetBackgroundColour(backg_accent_colour);
	butSearch->SetForegroundColour(wxColour(255, 255, 255));

	butAccInfo = new wxButton(butPanel, wxID_ANY, "\nACCOUNT\n", wxPoint(849, 136), wxSize(140, 140));
	butAccInfo->Bind(wxEVT_BUTTON, &home::butAccountlicked, this);
	butAccInfo->SetBackgroundColour(backg_accent_colour);
	butAccInfo->SetForegroundColour(wxColour(255, 255, 255));

	butCreateEve = new wxButton(butPanel, wxID_ANY, "CREATE\nEVENT", wxPoint(189, 404), wxSize(140, 140));
	butCreateEve->Bind(wxEVT_BUTTON, &home::butCreateClicked, this);
	butCreateEve->SetBackgroundColour(backg_accent_colour);
	butCreateEve->SetForegroundColour(wxColour(255, 255, 255)); // White color

	butEdit = new wxButton(butPanel, wxID_ANY, "\nEDIT\nPROFILE\n", wxPoint(849, 404), wxSize(140, 140));
	butEdit->SetBackgroundColour(backg_accent_colour);
	butEdit->SetForegroundColour(wxColour(255, 255, 255));
	butEdit->Bind(wxEVT_BUTTON, &home::butEditClicked, this);

	// text boxes
	uNameBox = new wxTextCtrl(searchPanel, wxID_ANY, "", wxPoint(441, 326), wxSize(313, 26));
	wxStaticText *searchLabel2 = new wxStaticText(searchPanel, wxID_ANY, "Search User", wxPoint(441, 296), wxSize(313, 20), wxALIGN_CENTER);
	searchLabel2->SetForegroundColour(wxColour(255, 255, 255));

	butFind = new wxButton(searchPanel, wxID_ANY, "Search", wxPoint(441, 360), wxSize(313, 40));
	butFind->Bind(wxEVT_BUTTON, &home::butFindClicked, this);
	butBoard->SetBackgroundColour(backg_accent_colour);
	butBoard->SetForegroundColour(wxColour(255, 255, 255));
	
	wxImage::AddHandler(new wxPNGHandler());
	wxImage image;
	if (!image.LoadFile("./images/logo_text_white.png", wxBITMAP_TYPE_PNG))
	{
		// Handle the error (e.g. show an error message)
		return;
	}
	image.Rescale(200, 208);

	wxBitmap bitmap(image);
	if (!bitmap.IsOk())
	{
		// Handle the error (e.g. show an error message)
		return;
	}

	wxStaticBitmap *staticBitmap = new wxStaticBitmap(mainPanel, wxID_ANY, bitmap);
	staticBitmap->SetPosition(wxPoint(500, 100));

	// Calculate the size of the image
	wxSize imageSize = bitmap.GetSize();

	// Set the size of the static bitmap to be the same as the size of the image
	staticBitmap->SetSize(wxSize(200,208));
}

void home::butBoardClicked(wxCommandEvent &evt)
{
}


/**
 * @brief Function to bring up the search panel to search for users
 * 
 * @param evt Event trigger to handler button click
 */
void home::butSearchClicked(wxCommandEvent &evt)
{
	butPanel->Hide();
	searchPanel->Show();
	searchPanel->Raise();
}

/**
 * @brief Function to load the information about the user
 * 
 * @param evt Event trigger to handle the button click
 */
void home::butAccountlicked(wxCommandEvent &evt)
{
	//create AccountInfo
	AccountInfo *accountInfo = new AccountInfo("Personal Account", wxPoint(50, 50), wxSize(1204, 720), "", user, 1);
	accountInfo->Center();
	accountInfo->Show();
	//this->Hide();
}

/**
 * @brief Function to load the the event creation page
 * 
 * @param evt Event trigger to handle the button click
 */
void home::butCreateClicked(wxCommandEvent &evt)
{
	CreateEvent *createEvent = new CreateEvent("Create Event", wxPoint(50, 50), wxSize(1204, 720), user);
	createEvent->Center();
	createEvent->Show();
}

/**
 * @brief Function to load the events from the followed users
 * 
 * @param evt Event trigger to handle the button click
 */
void home::butDisplayClicked(wxCommandEvent& evt)
{
	DisplayEvent* displayEvent = new DisplayEvent("Display Event", wxPoint(50, 50), wxSize(1204, 720), user);
	displayEvent->Center();
	displayEvent->Show();
}

/**
 * @brief Button to take you back to the home page
 * 
 * @param evt Event trigger to handle the button click
 */
void home::butBackClicked(wxCommandEvent &evt)
{
	searchPanel->Hide();
	butPanel->Show();
	butPanel->Raise();
}

/**
 * @brief Find the user searched and allow for following if the user is different from the logged in user
 * 
 * @param evt Event trigger to handle the button click
 */
void home::butFindClicked(wxCommandEvent &evt)
{
	json data = handler->getUser((uNameBox->GetValue()).ToStdString());
	if (data != NULL)
	{
		AccountInfo* accountInfo;
		if((uNameBox->GetValue()).ToStdString().compare(user) == 0){
			accountInfo = new AccountInfo("Personal Account", wxPoint(50, 50), wxSize(1204, 720), "", user, 1);
		}else{
			accountInfo = new AccountInfo("Personal Account", wxPoint(50, 50), wxSize(1204, 720), (uNameBox->GetValue()).ToStdString(), user,0);
		}
		accountInfo->Center();
		accountInfo->Show();
	}
}

/**
 * @brief Function to load the edit account window
 * 
 * @param evt Event trigger to handle the button click
 */
void home::butEditClicked(wxCommandEvent& evt){
	std::cout<<"crash10\n";
	Edit* EditAccount = new Edit("Setting", wxPoint(50, 50), wxSize(1204, 720),user);
	std::cout<<"crash20\n";
	EditAccount->Center();
	EditAccount->Show();

}


/**
 * @brief Function to display a closing message
 * 
 * @param evt Event trigger to handle window close
 */
void home::closeFrame(wxCloseEvent& evt){
	std::ofstream logFile("log.json", std::ios::app);

	// Delete the log file if it already exists
	if (logFile.good()) {
		logFile.close();
		std::remove("log.json");
	}

	wxLogMessage("Exit Application");
	evt.Skip();
}