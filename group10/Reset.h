#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/image.h>
#include "single_include/nlohmann/json.hpp"
#include <iomanip>
#include <fstream>
#include <wx/file.h>
#include <string>
#include "./dbhandler/userdbhandler.h"

/**
 * @file Reset.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * @brief This is the Reset class it defines a reset object. Our reset object is a window that pops-up.
 * This window has an input box for the user that checks for valid Usernames then prompts them with the security question
 * they answered when making an account.
 * 
 */

class Reset :public wxFrame
{

public:
	Reset(const wxString& title, const wxPoint& pos, const wxSize& size, wxArrayString);

	
private:
	UserDBHandler* handler;
	std::string securityAns;

	wxPanel* mainPanel;
	wxTextCtrl* uNameBox;
	wxButton* butCheck;
	wxPanel* infoPanel;
	wxChoice* questionChoice;
	wxTextCtrl* secABox;
	wxTextCtrl* newPassBox;
	wxTextCtrl* confirmPassBox;
	wxButton* butReset;

	wxStaticText* uName;
	wxStaticText* secQ;
	wxStaticText* secA;
	wxStaticText* newPass;
	wxStaticText* conPass;

	wxStaticText* warn1;
	wxStaticText* warn2;
	wxStaticText* warn3;
	
	void butResetClicked(wxCommandEvent& evt);
	std::string ansSave;


	void butCheckClicked(wxCommandEvent& evt);






};
