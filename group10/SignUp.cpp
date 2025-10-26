/**
 * @file SignUp.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "SignUp.h"

using json = nlohmann::json;

/**
* @brief Constructor for the SignUp class.
* @param title A string representing the title of the frame.
* @param pos A wxPoint object representing the position of the frame.
* @param size A wxSize object representing the size of the frame.
*/
SignUp::SignUp(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	handler = new UserDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");

	//large panel for picture
	wxPanel *mainPanel = new wxPanel(this, wxID_ANY);

	//image here
	mainPanel->SetBackgroundColour(wxColor(13, 28, 83));

	//for design
	wxPanel *panel1 = new wxPanel(mainPanel, wxID_ANY, wxPoint(253, 126), wxSize(606, 494));
	panel1->SetBackgroundColour(wxColor(160, 160, 160));

	wxPanel *panel2 = new wxPanel(mainPanel, wxID_ANY, wxPoint(270, 112), wxSize(606, 494));
	panel2->SetBackgroundColour(wxColor(233, 150, 122));

	wxPanel *panel3 = new wxPanel(mainPanel, wxID_ANY, wxPoint(288, 96), wxSize(606, 494));
	panel3->SetBackgroundColour(wxColor(185, 209, 234));

	wxPanel *panel4 = new wxPanel(mainPanel, wxID_ANY, wxPoint(306, 78), wxSize(606, 494));
	panel4->SetBackgroundColour(wxColor(240, 255, 240));

	//panel for fill in
	panelSign = new wxPanel(mainPanel, wxID_ANY, wxPoint(306, 78), wxSize(606, 494));
	panelSign->SetBackgroundColour(wxColor(240, 255, 240));
	panelSign->Raise();

	wxStaticText *nName = new wxStaticText(panelSign, wxID_ANY, "Name or Nickname", wxPoint(119, 19));
	wxFont font = nName->GetFont();
	//set font size
	font.SetPointSize(9.75);
	//set font to it
	nName->SetFont(font);

	wxStaticText *lName = new wxStaticText(panelSign, wxID_ANY, "Last Name", wxPoint(322, 19));
	lName->SetFont(font);

	wxStaticText *uName = new wxStaticText(panelSign, wxID_ANY, "Username", wxPoint(45, 88));
	uName->SetFont(font);

	wxStaticText *pass = new wxStaticText(panelSign, wxID_ANY, "Password", wxPoint(54, 120));
	pass->SetFont(font);

	wxStaticText *cPass = new wxStaticText(panelSign, wxID_ANY, "Confirm Password", wxPoint(6, 152));
	cPass->SetFont(font);

	wxStaticText *dob = new wxStaticText(panelSign, wxID_ANY, "Date of Birth", wxPoint(42, 187));
	dob->SetFont(font);

	wxStaticText *secQ = new wxStaticText(panelSign, wxID_ANY, "Security Question", wxPoint(10, 242));
	secQ->SetFont(font);

	wxStaticText *secA = new wxStaticText(panelSign, wxID_ANY, "Answer", wxPoint(70, 275));
	secA->SetFont(font);

	nNameBox = new wxTextCtrl(panelSign, wxID_ANY, "", wxPoint(121, 38), wxSize(110, 26));

	lNameBox = new wxTextCtrl(panelSign, wxID_ANY, "", wxPoint(324, 38), wxSize(110, 26));

	uNameBox = new wxTextCtrl(panelSign, wxID_ANY, "", wxPoint(121, 83), wxSize(313, 26));

	passBox = new wxTextCtrl(panelSign, wxID_ANY, "", wxPoint(121, 115), wxSize(313, 26), wxTE_PASSWORD);

	cPassBox = new wxTextCtrl(panelSign, wxID_ANY, "", wxPoint(121, 147), wxSize(313, 26), wxTE_PASSWORD);

	yearUpDown = new wxSpinCtrl(panelSign, wxID_ANY, "", wxPoint(324, 183), wxSize(110, 29), wxSP_WRAP, 1990, 2023, 1900);

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

	monthBox = new wxChoice(panelSign, wxID_ANY, wxPoint(198, 183), wxSize(121, 29), monthList);
	monthBox->SetSelection(0);

	dateUpDown = new wxSpinCtrl(panelSign, wxID_ANY, "", wxPoint(121, 183), wxSize(70, 29), wxSP_WRAP, 1, 31, 1);

	wxArrayString qList;
	qList.Add("Select Question...");
	qList.Add("What is your hometown?");
	qList.Add("What is your middle name?");
	qList.Add("What was your first car?");
	qList.Add("Name of elementary school?");
	qList.Add("What is your favourite color?");

	qBox = new wxChoice(panelSign, wxID_ANY, wxPoint(121, 235), wxSize(313, 29), qList);
	qBox->SetSelection(0);

	secABox = new wxTextCtrl(panelSign, wxID_ANY, "", wxPoint(121, 270), wxSize(313, 26));

	// Create the sign up button
	m_btnSignUp = new wxButton(panelSign, wxID_ANY, "Sign Up", wxPoint(204, 417), wxSize(176, 62));

	// Bind the sign up button to the OnSignUpClicked function
	m_btnSignUp->Bind(wxEVT_BUTTON, &SignUp::signUpClicked, this);

	//red + 9.75
	warn1 = new wxStaticText(panelSign, wxID_ANY, "unmatch", wxPoint(458, 151));
	warn1->Hide();

	panelSign->Layout();
}

/**
 * @brief Event handler function for the m_btnSignUp button. Checks if user already exists, then adds user to database.
 * @param evt A reference to the wxCommandEvent object that called this function.
 */
void SignUp::signUpClicked(wxCommandEvent &evt)
{

	wxString nName = nNameBox->GetValue();
	wxString lName = lNameBox->GetValue();
	wxString uName = uNameBox->GetValue();
	wxString pass = passBox->GetValue();
	wxString cPass = cPassBox->GetValue();
	int secQ = qBox->GetSelection(); //start from 0
	wxString secA = secABox->GetValue();
	int date = dateUpDown->GetValue();
	int month = monthBox->GetSelection();
	int year = yearUpDown->GetValue();

	if (cPass.Cmp(pass) != 0)
	{
		warn1->Show();
		return;
	}

	if (nName == "" || uName == "" || pass == "" || secA == "" || secQ == 0)
	{
		//6 red star appear
		wxLogMessage("Please fill/select the required infomations.");
		return;
	}
	//check if the username already exists
	json result = handler->getUser(uName.ToStdString());

	if (result == NULL)
	{
		handler->addUser(nName.ToStdString(), lName.ToStdString(), uName.ToStdString(), pass.ToStdString(), secQ, secA.ToStdString(), date, month + 1, year);
	}
	else
	{
		wxLogMessage("Username Already Exists");
	}
}

/**
 * @brief Event handler function for the check button.
 * @param evt A reference to the wxCommandEvent object that called this function.
 */
void SignUp::checkClicked(wxCommandEvent &evt)
{
}
