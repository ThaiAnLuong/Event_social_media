/**
 * @file MainFrame.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Frame containing the login
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "MainFrame.h"

using json = nlohmann::json;

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size): wxFrame(NULL, wxID_ANY, title, pos, size) 
{
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::closeFrame, this);

	handler = new UserDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");


	wxColour backg_accent_colour = wxColour(22, 41, 110);
	
	wxSize textSize;
	//panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColor(13, 28, 83));

		//IMAGE - LOGO
	wxImage::AddHandler(new wxPNGHandler());
	wxImage image;
	if (!image.LoadFile("./images/logo_ball_color_2.png", wxBITMAP_TYPE_PNG))
	{
		// Handle the error (e.g. show an error message)
		return;
	}
	image.Rescale(213, 230);

	wxBitmap bitmap(image);
	if (!bitmap.IsOk())
	{
		// Handle the error (e.g. show an error message)
		return;
	}

	wxStaticBitmap *staticBitmap = new wxStaticBitmap(panel, wxID_ANY, bitmap);
	staticBitmap->SetPosition(wxPoint(500, -10));

	// Calculate the size of the image
	wxSize imageSize = bitmap.GetSize();

	// Set the size of the static bitmap to be the same as the size of the image
	staticBitmap->SetSize(wxSize(213, 230));



	panel1 = new wxPanel(panel, wxID_ANY, wxPoint(335, 234), wxSize(533, 368));


	//button
	//para this: this frame		ID: any		"text on button" 		"wxPoint(x,y) (x y inside panel)"	wxSize(x,y)
	button = new wxButton(panel1, wxID_ANY, "Login", wxPoint(34, 181), wxSize(411, 53));

	button->Bind(wxEVT_BUTTON, &MainFrame::loginClicked, this);

	//text
	failLog = new wxStaticText(panel1, wxID_ANY, "Invalid User Name or Password", wxPoint(175, 37));

	failLog->SetForegroundColour(wxColor("#ff0000"));

	wxFont fontFail = failLog->GetFont();
	//set font size
	fontFail.SetPointSize(10);

	//set bold
	fontFail.SetWeight(wxFONTWEIGHT_BOLD);
	//set font to it
	failLog->SetFont(fontFail);

	//hide text
	failLog->Hide();
	panel1->Layout();


	//text box
	userLog = new wxTextCtrl(panel1, wxID_ANY, "", wxPoint(111, 62), wxSize(334, 33));

	//text box
	passLog = new wxTextCtrl(panel1, wxID_ANY, "", wxPoint(111, 118), wxSize(334, 33), wxTE_PASSWORD);

	//text
	wxStaticText* userName = new wxStaticText(panel1, wxID_ANY, "USERNAME", wxPoint(18, 67));
	userName->SetForegroundColour(wxColor("#ffffff"));
	wxFont fontUser = userName->GetFont();
	//set font size
	fontUser.SetPointSize(11);

	//set font to it
	userName->SetFont(fontUser);

	//text
	wxStaticText* password = new wxStaticText(panel1, wxID_ANY, "PASSWORD", wxPoint(18, 122));
	password->SetForegroundColour(wxColor("#ffffff"));
	wxFont fontPass = password->GetFont();
	password->Wrap(password->GetSize().GetWidth());
	//set font size
	fontPass.SetPointSize(11);

	//set font to it
	password->SetFont(fontPass);


	createAcc = new wxButton(panel1, wxID_ANY, "Create Account", wxPoint(125, 248), wxDefaultSize);
	createAcc->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	createAcc->SetBackgroundColour(wxColor(13, 28, 83));
	createAcc->SetForegroundColour(wxColor(255, 255, 255));
	createAcc->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnCreateAccountClick, this);

	resetPass = new wxButton(panel1, wxID_ANY, "Reset Password", wxPoint(275, 248), wxDefaultSize);
	resetPass->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	resetPass->SetBackgroundColour(wxColor(155, 0, 0));
	resetPass->SetForegroundColour(wxColor(255, 255, 255));
	resetPass->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnResetClick ,this);

	panel1->Layout();

}

/**
 * @brief Function to check the login information passed in and verify the user
 * 
 * @param evt Event trigger for when the event button is clicked
 */
void MainFrame::loginClicked(wxCommandEvent& evt) {
	// Get the user name and password from the text boxes
	wxString username = userLog->GetValue();
	wxString password = passLog->GetValue();

	if(username.ToStdString().compare("") != 0 && password.ToStdString().compare("")){
		json info = handler->getUser(username.ToStdString());
		std::string setPassword = info["Password"];
		if(info != NULL && password.ToStdString().compare(setPassword)== 0){
			// Show the home frame
			Home = new home("Home", wxPoint(50, 50), wxSize(1204, 720), username.ToStdString());
			Home->Center();
			Home->Show();
			this->Hide();
		}else{
			failLog->Show();
			resetPass->Show();
			panel1->Layout();
		}
	}
	else {
		// Show the failLog text
		failLog->Show();
		resetPass->Show();
		panel1->Layout();
	}

}

/**
 * @brief Function to show a closing message on window closing
 * 
 * @param evt Event trigger for closing the window
 */
void MainFrame::closeFrame(wxCloseEvent& evt){
	// Delete the log file before out
	std::ofstream logFile("log.json", std::ios::app);

	// Delete the log file if it already exists
	if (logFile.good()) {
		logFile.close();
		std::remove("log.json");
	}

	wxLogMessage("Exit Application");
	evt.Skip();
}

/**
 * @brief Function display the account creation page
 * 
 * @param event Event trigger for clicking the account creation button
 */
void MainFrame::OnCreateAccountClick(wxCommandEvent& event){
    // Create an instance of the SignUp frame and show it
    SignUp* signUpFrame = new SignUp("Create Account", wxPoint(50, 50), wxSize(1204, 720));
    signUpFrame->Center();
    signUpFrame->Show();
}

/**
 * @brief Function used to bring up the reset page
 * 
 * @param event Event trigger for cliicking the reset button
 */
void MainFrame::OnResetClick(wxCommandEvent& event){
	wxArrayString qList;
	qList.Add("Select Question...");
	qList.Add("What is your hometown?");qList.Add("What is your middle name?");qList.Add("What was your first car?");qList.Add("Name of elementary school?");qList.Add("What is your favourite color?");

	Reset* resetFrame = new Reset("Reset Password", wxPoint(50, 50), wxSize(858, 509), qList);
	resetFrame->Center();
	resetFrame->Show();


}
