/**
 * @file SignUp.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

/**
 * @file signup.h
 * @brief Contains the declaration of the SignUp class which is a derived class of wxFrame.
*/

#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/image.h>
#include "single_include/nlohmann/json.hpp"
#include <iomanip>
#include <fstream>
#include <wx/file.h>
#include "./dbhandler/userdbhandler.h"
#include <iostream>

/**
* @class SignUp
* @brief A derived class of wxFrame that allows the user to sign up for a new account.
*/
class SignUp : public wxFrame
{
public:
	/**
	* @brief Constructor for the SignUp class.
	* @param title A string representing the title of the frame.
	* @param pos A wxPoint object representing the position of the frame.
	* @param size A wxSize object representing the size of the frame.
	*/
	SignUp(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
	UserDBHandler *handler;

	wxPanel *panelSign;
	wxButton *m_btnSignUp;
	wxTextCtrl *nNameBox;
	wxTextCtrl *lNameBox;
	wxTextCtrl *uNameBox;
	wxTextCtrl *passBox;
	wxTextCtrl *cPassBox;
	wxSpinCtrl *dateUpDown;
	wxChoice *monthBox;
	wxSpinCtrl *yearUpDown;
	wxChoice *qBox;
	wxTextCtrl *secABox;
	wxStaticText *warn1;

	/**
	 * @brief Event handler function for the m_btnSignUp button.
	 * @param evt A reference to the wxCommandEvent object that called this function.
	 */
	void signUpClicked(wxCommandEvent &evt); /**
	 * @brief Event handler function for the check button.
	 * @param evt A reference to the wxCommandEvent object that called this function.
	 */
	void checkClicked(wxCommandEvent &evt);
};
