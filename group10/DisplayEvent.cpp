/**
 * @file DisplayEvent.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief This file contains the implementation of the DisplayEvent class.
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "DisplayEvent.h"
#include "single_include/nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;

/**
* @brief Constructor for the DisplayEvent class.
*
* @param title The title of the frame.
* 
* @param pos The position of the frame.
* 
* @param size The size of the frame.
* 
* @param curUser The current user.
*/
DisplayEvent::DisplayEvent(const wxString& title, const wxPoint& pos, const wxSize& size, string curUser): wxFrame(NULL, wxID_ANY, title, pos, size) {
	
	// Create EventDBHandler and UserDBHandler objects
	EventDBHandler *eventHandler = new EventDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");
	UserDBHandler *userHandler = new UserDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");

	// Get the current user
	string user = curUser;

	// Create a panel to hold the events list
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	mainPanel->SetBackgroundColour(wxColor(68, 70, 84));

	// Create a list view to display events
	wxListView *eventsList=new wxListView(mainPanel);
	eventsList->SetBackgroundColour(wxColor(176,200,244));
	eventsList->AppendColumn("Host ");
	eventsList->AppendColumn("Event Name");
	eventsList->AppendColumn("Event Date");
	eventsList->AppendColumn("Start Time");
	eventsList->SetColumnWidth(0, 300);
	eventsList->SetColumnWidth(1, 300);
	eventsList->SetColumnWidth(2, 300);
	eventsList->SetColumnWidth(3, 300);

	// Set font for the list view
    wxFont myFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    eventsList->SetFont(myFont);

	// Add the list view to the sizer
	auto sizer= new wxBoxSizer(wxVERTICAL);
	sizer->Add(eventsList, 1, wxALL | wxEXPAND, 0);
	mainPanel->SetSizerAndFit(sizer);

	// Get the list of friends and events
    vector<string> friendsList= userHandler ->getFollowing(user);
	vector<json> eventsReturned= eventHandler ->getEventsByHosts(friendsList);

	// Add events to the list view
	int n= eventsReturned.size();
	for(int i=0; i<n; i++){
		std::string hostId=eventsReturned[i]["HostID"];
		std::string eventName=eventsReturned[i]["EventName"];
		std::string eventDate=eventsReturned[i]["Start"]["iso"];
		std::string year=eventDate.substr(0, 4);
		std::string month=eventDate.substr(5, 2);
		std::string day=eventDate.substr(8, 2);
		std::string finalDate=day+"/"+month+"/"+year;
		std::string time=eventDate.substr(11, 5);

		eventsList->InsertItem(i, hostId);
		eventsList->SetItem(i, 1, eventName);
		eventsList->SetItem(i, 2, finalDate);
		eventsList->SetItem(i, 3, time);
    }

	
}




