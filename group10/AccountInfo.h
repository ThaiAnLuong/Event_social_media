/**
 * @file AccountInfo.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta,Will Reil
 * @brief accountinfo class
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
#include "./dbhandler/userdbhandler.h"
#include "./dbhandler/eventdbhandler.h"
#include <iomanip>
#include <fstream>
#include <wx/file.h>
#include <string.h>
#include "AccountInfo.h"





class AccountInfo :public wxFrame
{

public:void butEditClicked(wxCommandEvent& evt);
	AccountInfo(const wxString& title, const wxPoint& pos, const wxSize& size, std::string searchedUser, std::string curUser,int isUser);

private:
	int sig;
	wxStaticText* uName;
	UserDBHandler* handler;
	EventDBHandler* eHandler;
	std::vector<nlohmann::json> data;
	std::string searched;
	
	
	std::string curUser;
	std::string searchedUser;
	
	wxPanel* mainPanel;
	wxPanel* displayPanel;//hide	//pos 565,76 (main)  size 536 , 506 ||    Raise
	wxButton* close;	// pos 503,6 (displayPanel)   size 30,30
	wxPanel* infoPanel;
	wxPanel* picPanel;
	wxPanel* testPanel;//delete this for profile picture


	wxButton* butFollow;
	wxStaticText* uNameText;

	wxStaticText* nNameText;
	wxStaticText* nNameShow;

	wxStaticText* dateText;
	wxStaticText* dateShow;
	
	wxStaticText* locText;
	wxStaticText* locShow;

	wxArrayString evtList;
	wxListBox* createdEvt;


	wxStaticText* evtText;
	wxStaticText* hostText;
	wxStaticText* addrText;
	wxStaticText* priceText;
	wxStaticText* startText;
	wxStaticText* timeText;
	wxStaticText* desText;

	wxStaticText* event;
	wxStaticText* host;
	wxStaticText* addr;
	wxStaticText* price;
	wxStaticText* date;
	wxStaticText* time;
	wxStaticText* des;

	void clickedFollow(wxCommandEvent& evt);
	void clickedUnfollow(wxCommandEvent& evt);
	void pickEvent(wxCommandEvent& evt);
	void setUpFrameProfile();
	void setUpFrameDifProfile(std::string findUsername);
	void closeClicked(wxCommandEvent& evt);
	void getDetail(std::string eventName);
};