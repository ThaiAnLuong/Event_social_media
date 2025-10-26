/**
 * @file Edit.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Class to allow for the password, name, and birthday of a user to be changed
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#pragma once
#include "single_include/nlohmann/json.hpp"
#include <wx/gauge.h>
#include <wx/spinctrl.h>
#include <wx/progdlg.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/image.h>
#include "./dbhandler/userdbhandler.h"
#include <iomanip>
#include <fstream>
#include <wx/file.h>
#include <string.h>

using namespace std;

/**
* @class Edit
* @brief A derived class of wxFrame that allows the user to edit their account information and password.
*/
class Edit : public wxFrame
{
public:
	/**
	* @brief Constructor for the Edit class.
	* @param title A string representing the title of the frame.
	* @param pos A wxPoint object representing the position of the frame.
	* @param size A wxSize object representing the size of the frame.
	* @param user A string representing the username of the current user.
	*/
	Edit(const wxString &, const wxPoint &, const wxSize &, std::string);

private:
	//data base
	string curUser;
	UserDBHandler *handler;

	wxPanel *mainPanel;
	wxPanel *infoPanel;
	wxPanel *passwordPanel;

	wxButton *saveInfo;
	wxButton *savePass;

	wxArrayString options;
	//options.Add(" name of chgane");
	wxListBox *changeOption;

	//for change password
	wxTextCtrl *curPass;
	wxTextCtrl *newPass;
	wxTextCtrl *conPass;

	wxStaticText *curPassText;
	wxStaticText *newPassText;
	wxStaticText *conPassText;
	wxStaticText *warn1;
	wxStaticText *warn2;

	//for change account info
	wxStaticText *lNameText;
	wxTextCtrl *lName;
	wxStaticText *nNameText;
	wxTextCtrl *nName;
	wxStaticText *dob;

	wxSpinCtrl *dateUpDown;
	wxChoice *monthBox;
	wxSpinCtrl *yearUpDown;

	/**
	 * @brief Event handler function for the changeOption listbox.
	 * @param evt A reference to the wxCommandEvent object that called this function.
	 */
	void pick(wxCommandEvent &evt);

	/**
	 * @brief Event handler function for the savePass button.
	 * @param evt A reference to the wxCommandEvent object that called this function.
	 */
	void savePassClicked(wxCommandEvent &evt);

	/**
	 * @brief Event handler function for the saveInfo button.
	 * @param evt A reference to the wxCommandEvent object that called this function.
	 */
	void saveInfoClicked(wxCommandEvent &evt);
};
