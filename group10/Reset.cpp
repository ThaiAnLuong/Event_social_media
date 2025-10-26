#include "Reset.h"

using json = nlohmann::json;

/**
 * @file Reset.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief Construct a new Reset Password window:: Reset object
 * 
 * @param title This is the title for the window that is generated to reset the password
 * @param pos  This is the position of the frame where the reset password window appears
 * @param size This is the size of the window for the reset password pop-up
 * @param qList This is the list of security questions for the user to andwe theirs
 */

Reset::Reset(const wxString& title, const wxPoint& pos, const wxSize& size, wxArrayString qList) : wxFrame(NULL, wxID_ANY, title, pos, size) {
	handler = new UserDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");

	mainPanel = new wxPanel(this, wxID_ANY,wxPoint(0,0), wxSize(1204, 720));
	//image here
	mainPanel->SetBackgroundColour(wxColor(13, 28, 83));

	uNameBox = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(256, 97), wxSize(313, 26));

	//button green + bold + 12
	butCheck = new wxButton(mainPanel, wxID_ANY, "Check", wxPoint(590, 97), wxSize(72, 26));
	butCheck->Bind(wxEVT_BUTTON, &Reset::butCheckClicked, this);

	infoPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(84, 149), wxSize(636, 314));
	infoPanel->Hide();

	questionChoice = new wxChoice(infoPanel, wxID_ANY, wxPoint(172, 8), wxSize(313, 29), qList);
	questionChoice->Enable(FALSE);

	// 14.24
	secABox = new wxTextCtrl(infoPanel, wxID_ANY, "", wxPoint(172, 43), wxSize(313, 26));

	newPassBox = new wxTextCtrl(infoPanel, wxID_ANY, "", wxPoint(172, 102), wxSize(313, 26), wxTE_PASSWORD);

	confirmPassBox = new wxTextCtrl(infoPanel, wxID_ANY, "", wxPoint(172, 134), wxSize(313, 26), wxTE_PASSWORD);

	//but blue + violet letter + bold + 14.25
	butReset = new wxButton(infoPanel, wxID_ANY, "Reset Password", wxPoint(116, 247), wxSize(411,53));
	butReset->Bind(wxEVT_BUTTON, &Reset::butResetClicked, this);

	uName = new wxStaticText(mainPanel , wxID_ANY, "Username", wxPoint(157, 96));
	uName->SetForegroundColour(wxColor("#ffffff"));

	secQ = new wxStaticText(infoPanel, wxID_ANY, "Security Question", wxPoint(12, 10));
	secQ->SetForegroundColour(wxColor("#ffffff"));

	secA = new wxStaticText(infoPanel, wxID_ANY, "Answer", wxPoint(96, 42));
	secA->SetForegroundColour(wxColor("#ffffff"));

	newPass = new wxStaticText(infoPanel, wxID_ANY, "New Password", wxPoint(34, 101));
	newPass->SetForegroundColour(wxColor("#ffffff"));

	conPass = new  wxStaticText(infoPanel, wxID_ANY, "Confirm Password", wxPoint(8, 133));
	conPass->SetForegroundColour(wxColor("#ffffff"));


	//red waringing + bold + 8.25
	warn1= new  wxStaticText(mainPanel, wxID_ANY, "Invalid Username!", wxPoint(253, 126));
	warn1->SetForegroundColour(wxColor("#ffffff"));
	warn1->Hide();

	warn2= new  wxStaticText(infoPanel, wxID_ANY, "Incorrect answer!", wxPoint(169, 72));
	warn2->SetForegroundColour(wxColor("#ffffff"));
	warn2->Hide();

	warn3=new wxStaticText(infoPanel, wxID_ANY, "Password not match!", wxPoint(169, 72));
	warn3->SetForegroundColour(wxColor("#ffffff"));
	warn3->Hide();

	infoPanel->Layout();
	mainPanel->Layout();
}

/**
 * @brief This is the function that runs if the Reset password button is clicked, it checks that the security answer the user 
 * has is the same and then it takes the users input in the new password box and stores it
 * 
 * @param evt This is the signal send to from the gui to click the button.
 */
void Reset::butResetClicked(wxCommandEvent& evt) {
	//check if security answer is the same
	if (((secABox->GetValue()).ToStdString()).compare(securityAns) != 0) {
		warn2->Show();
		return;
	}

	if ((newPassBox->GetValue()).Cmp(confirmPassBox->GetValue()) != 0) {
		warn3->Show();
		return;
	}

	handler->changePassword((uNameBox->GetValue()).ToStdString(), (newPassBox->GetValue()).ToStdString());
	wxLogMessage("Successfully change password");
	this->Close();

}
/**
 * @brief This is the function that runs if the Reset password button is clicked, it checks that the security answer the user 
 * has is the same and then it takes the users input in the new password box and stores it
 * 
 * @param evt This is the signal send to from the gui to click the button.
 */
void Reset::butCheckClicked(wxCommandEvent& evt){

	wxString uNameCheck= uNameBox->GetValue();
	json res = handler->getUser(uNameCheck.ToStdString());

	if(res == NULL){
		warn1->Show();
		return;
	}

	int questionSelection = res["SecurityQuestion"];
	questionChoice->SetSelection(questionSelection);

	securityAns = res["SQAnswer"];

	//show the panel
	infoPanel->Show();
	infoPanel->Raise();
	mainPanel->Layout();
	warn1->Hide();
}
