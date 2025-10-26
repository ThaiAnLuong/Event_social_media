/**
 * @file MainFrame.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief login class, using mainframe
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/hyperlink.h>
#include <wx/image.h>
#include "Reset.h"
#include "SignUp.h"
#include "home.h"
#include "./dbhandler/userdbhandler.h"
#include "single_include/nlohmann/json.hpp"


/**
 * @brief login page of the program with login, createa account, reset password function
 *
 */
class MainFrame :public wxFrame
{

public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	home* Home;


private:
	UserDBHandler* handler;

	wxStaticText* failLog;
	wxPanel* panel1;
	wxButton* button;
	wxTextCtrl* userLog;
	wxTextCtrl* passLog;
	wxStaticText* orText;
	wxButton* resetPass;
	wxButton* createAcc;

	void loginClicked(wxCommandEvent& evt);
	void closeFrame(wxCloseEvent& evt);
	void OnCreateAccountClick(wxCommandEvent& event);
	void OnResetClick(wxCommandEvent& event);
	
};