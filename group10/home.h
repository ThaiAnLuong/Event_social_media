/**
 * @file home.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta , Will Reil 
 * @brief Home page containing buttons to go to different pages that provide different functionality 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#pragma once
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/image.h>
#include "single_include/nlohmann/json.hpp"
#include <iomanip>
#include <fstream>
#include <wx/file.h>
#include <string>
#include "./dbhandler/userdbhandler.h"

#include "AccountInfo.h"
#include "CreateEvent.h"
#include "Edit.h"
#include "DisplayEvent.h"


/**
 * @brief Home page containing buttons to go to different pages that provide different functionality 
 * 
 */
class home :public wxFrame
{

public:
	home(const wxString& title, const wxPoint& pos, const wxSize& size, std::string);

private:
	//wxStaticText* uName;
	std::string user;
	
	UserDBHandler* handler;
	wxPanel* mainPanel;
	wxPanel* searchPanel;
	wxPanel* butPanel;

	wxButton* butBack;
	wxButton* butFind;
	wxButton* butBoard;
	wxButton* butSearch;
	wxButton* butAccInfo;
	wxButton* butCreateEve;
	wxButton* butA;
	wxButton* butEdit;
	wxButton* butDisplayEve;
	//wxButton* butDisplayEve2;
	wxTextCtrl* uNameBox;

	// method here
	void butBoardClicked(wxCommandEvent& evt);
	void butSearchClicked(wxCommandEvent& evt);
	void butAccountlicked(wxCommandEvent& evt);
	void butCreateClicked(wxCommandEvent& evt);
	void butBackClicked(wxCommandEvent& evt);
	void butFindClicked(wxCommandEvent& evt);
	void butEditClicked(wxCommandEvent& evt);
	void butDisplayClicked(wxCommandEvent& evt);
	void closeFrame(wxCloseEvent& evt);
	//void butDisplayClicked2(wxCommandEvent& evt);
	



};