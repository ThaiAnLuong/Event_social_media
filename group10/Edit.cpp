/**
 * @file Edit.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Class to allow for the password, name, and birthday of a user to be changed
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "Edit.h"

/**
* @brief Constructs an Edit object with a user interface for users to edit their account information and passwords.
* 
* @param title The title of the window.
* 
* @param pos The initial position of the window.
*
* @param size The initial size of the window.
*
* @param User The username of the current user.
*/
Edit::Edit(const wxString &title, const wxPoint &pos, const wxSize &size, std::string User) : wxFrame(NULL, wxID_ANY, title, pos, size)
{

	// Store the current user
	curUser = User;

	// Initialize the user database handler
	handler = new UserDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");

	// Create the main panel
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1204, 720));
	mainPanel->SetBackgroundColour(wxColor(68, 70, 84));

	// Create the info panel to display account information
	infoPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(361, 93), wxSize(574, 445));
	infoPanel->SetBackgroundColour(wxColor(199, 233, 208));

	// Create the password panel to allow the user to change their password
	passwordPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(361, 93), wxSize(574, 445));
	;
	passwordPanel->SetBackgroundColour(wxColor(199, 233, 208));
	passwordPanel->Hide();

	// Create a list box to select between account information and password change
	options.Add("Account Infomations");
	options.Add("Password");

	changeOption = new wxListBox(mainPanel, wxID_ANY, wxPoint(219, 93), wxSize(135, -1), options);
	changeOption->SetSelection(0);
	changeOption->SetLayoutDirection(wxLayout_RightToLeft);
	changeOption->Bind(wxEVT_LISTBOX, &Edit::pick, this);
	wxFont font1(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	changeOption->SetFont(font1);

	// Create a save button for the password panel
	savePass = new wxButton(passwordPanel, wxID_ANY, "Update", wxPoint(215, 370), wxSize(118, 47));
	savePass->Bind(wxEVT_BUTTON, &Edit::savePassClicked, this);

	// Create a save button for the account information panel
	saveInfo = new wxButton(infoPanel, wxID_ANY, "Update", wxPoint(215, 370), wxSize(118, 47));
	saveInfo->Bind(wxEVT_BUTTON, &Edit::saveInfoClicked, this);

	// Create controls for the password panel

	// Create text controls for the current password, new password, and confirm password fields
	wxFont font2(9.75, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxFont font3(9.75, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	curPass = new wxTextCtrl(passwordPanel, wxID_ANY, "", wxPoint(149, 78), wxSize(313, 26), wxTE_PASSWORD);
	newPass = new wxTextCtrl(passwordPanel, wxID_ANY, "", wxPoint(149, 135), wxSize(313, 26), wxTE_PASSWORD);
	conPass = new wxTextCtrl(passwordPanel, wxID_ANY, "", wxPoint(149, 167), wxSize(313, 26), wxTE_PASSWORD);

	curPassText = new wxStaticText(passwordPanel, wxID_ANY, "Current Password", wxPoint(16, 85));
	curPassText->SetFont(font2);
	newPassText = new wxStaticText(passwordPanel, wxID_ANY, "New Password", wxPoint(38, 142));
	newPassText->SetFont(font2);
	conPassText = new wxStaticText(passwordPanel, wxID_ANY, "Confirm Password", wxPoint(16, 174));
	conPassText->SetFont(font2);

	//warning
	warn1 = new wxStaticText(passwordPanel, wxID_ANY, "Incorrect", wxPoint(464, 84));
	warn1->SetForegroundColour(wxColor("#ff0000"));
	warn1->SetFont(font3);
	warn1->Hide();

	warn2 = new wxStaticText(passwordPanel, wxID_ANY, "Unmatch", wxPoint(464, 173));
	warn2->SetForegroundColour(wxColor("#ff0000"));
	warn2->SetFont(font3);
	warn2->Hide();

	//info panel control

	//get curUser date month year
	//get curUser nName, lName
	std::cout << "crash" << std::endl;
	nlohmann::json data = handler->getUser(curUser);

	int date = data["BDay"], month = data["BMonth"], year = data["BYear"]; //get from database
	std::string nNameData = data["FirstName"];
	std::string lNameData = data["LastName"];

	dob = new wxStaticText(infoPanel, wxID_ANY, "Date Of Birth", wxPoint(41, 175));
	dob->SetFont(font2);

	yearUpDown = new wxSpinCtrl(infoPanel, wxID_ANY, "", wxPoint(388, 169), wxSize(120, 29), wxSP_WRAP, 1900, 2023, year);

	wxArrayString monthList;
	monthList.Add("January");
	monthList.Add("February");
	monthList.Add("March");
	monthList.Add("April");
	monthList.Add("May");
	monthList.Add("June");
	monthList.Add("July");
	monthList.Add("August");
	monthList.Add("September");
	monthList.Add("October");
	monthList.Add("November");
	monthList.Add("December");

	monthBox = new wxChoice(infoPanel, wxID_ANY, wxPoint(261, 169), wxSize(121, 29), monthList);
	monthBox->SetSelection(month - 1);

	dateUpDown = new wxSpinCtrl(infoPanel, wxID_ANY, "", wxPoint(135, 169), wxSize(120, 29), wxSP_WRAP, 1, 31, date);

	nNameText = new wxStaticText(infoPanel, wxID_ANY, "Name", wxPoint(85, 95));
	nNameText->SetFont(font2);

	lNameText = new wxStaticText(infoPanel, wxID_ANY, "Last Name", wxPoint(286, 95));
	lNameText->SetFont(font2);

	nName = new wxTextCtrl(infoPanel, wxID_ANY, nNameData, wxPoint(135, 88), wxSize(120, 26));
	lName = new wxTextCtrl(infoPanel, wxID_ANY, lNameData, wxPoint(369, 88), wxSize(120, 26));

	passwordPanel->Hide();
	mainPanel->Layout();
}

// This function is triggered when a new option is selected from the "change option" dropdown menu
/**
* @brief Hides all panels and shows the selected panel.
* 
* @param evt The event triggered by selecting a new option from the dropdown menu.
*/
void Edit::pick(wxCommandEvent &evt)
{
	// Hide all panels
	this->infoPanel->Hide();
	this->passwordPanel->Hide();
	//add more panels here if needed

	// Always layout to update the changes
	mainPanel->Layout();

	// Get the selected item from the listbox
	int selection = changeOption->GetSelection();

	// Show the corresponding panel based on the selection
	if (selection == 0)
	{
		this->infoPanel->Show();
		this->infoPanel->Raise();
	}
	else if (selection == 1)
	{
		this->passwordPanel->Show();
		this->passwordPanel->Raise();
	}
	// Layout again to update the changes
	mainPanel->Layout();
}

// This function is triggered when the "save password" button is clicked
/**
* @brief Saves the user's updated password to the system.
*
* @param evt The event triggered by the "save password" button.
*/
void Edit::savePassClicked(wxCommandEvent &evt)
{
	// Call the handler's function to update the user's password
	handler->changePassword(curUser, (newPass->GetValue()).ToStdString());
	// Create a progress bar dialog to show the update progress
	wxProgressDialog dialog("Updating Password...", "Progress...", 100, this, wxPD_APP_MODAL | wxPD_ELAPSED_TIME);
	dialog.CenterOnParent();
	// Run the progress bar for 2 seconds
	for (int i = 0; i < 100; i++)
	{
		wxMilliSleep(20);
		dialog.Update(i, wxString::Format("%d%%", i));
	}
	// Destroy the progress bar dialog
	dialog.Destroy();
}

// This function is triggered when the "save info" button is clicked
/**
* @brief Saves the user's updated information to the system.
* 
* @param evt The event triggered by the "save info" button.
*/
void Edit::saveInfoClicked(wxCommandEvent &evt)
{
	// Call the handler's functions to update the user's information
	handler->changeBirthday(curUser, dateUpDown->GetValue(), monthBox->GetSelection() + 1, yearUpDown->GetValue());
	handler->changeFirstName(curUser, nName->GetValue().ToStdString());
	handler->changeLastName(curUser, lName->GetValue().ToStdString());
	// Create a progress bar dialog to show the update progress
	wxProgressDialog dialog("Updating Info...", "Progress...", 100, this, wxPD_APP_MODAL | wxPD_ELAPSED_TIME);
	dialog.CenterOnParent();
	// Run progress bar for 2 seconds
	for (int i = 0; i < 100; i++)
	{
		wxMilliSleep(20);
		dialog.Update(i, wxString::Format("%d%%", i));
	}
	// Destroy the progress bar dialog
	dialog.Destroy();
}
