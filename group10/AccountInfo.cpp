/**
 * @file AccountInfo.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta,Will Reil
 * @brief this class show the user and other user infomation
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "AccountInfo.h"

//username = ""; for personal view
//username = "unique-username"; for view another account
//isUser = 1 for true, 0 for false
AccountInfo::AccountInfo(const wxString& title, const wxPoint& pos, const wxSize& size, std::string searchedUser, std::string curUser, int isUser) : wxFrame(NULL, wxID_ANY, title, pos, size) {
	sig = isUser;

	handler = new UserDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");
	eHandler = new EventDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");
	this->curUser = curUser;

	searched = searchedUser;
	
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1204, 720));
	//image here
	mainPanel->SetBackgroundColour(wxColor(68, 70, 84));

	displayPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(544, 77), wxSize(557, 506));
	displayPanel->SetBackgroundColour(wxColor(176, 200, 244));
	displayPanel->Hide();

	picPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(38, 52), wxSize(323 , 292));
	picPanel->SetBackgroundColour(wxColor(219, 217, 217));

	testPanel = new wxPanel(picPanel, wxID_ANY, wxPoint(81, 30), wxSize(150, 150));
	testPanel->SetBackgroundColour(wxColor(183, 87, 104));

	infoPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(38, 383), wxSize(323,170));
	infoPanel->SetBackgroundColour(wxColor(178, 168, 254));

	nNameText = new wxStaticText(infoPanel, wxID_ANY, "Name:", wxPoint(46, 40));

	dateText = new wxStaticText(infoPanel, wxID_ANY, "  Date of Birth\n(dd-mm-yyyy)", wxPoint(3, 72));


	wxFont font2(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	
	//get from data base
	
	if(sig==1){
		std::vector<std::string> user{curUser};
		this->data = eHandler-> getEventsByHosts(user);
		
	}else{
		std::vector<std::string> user{searchedUser};
		this->data = eHandler-> getEventsByHosts(user);
	}
	
	
	for(nlohmann::json j : data){
		std::string str = j["EventName"];
		evtList.Add(str);
	}

	
	createdEvt = new wxListBox(mainPanel, wxID_ANY, wxPoint(409, 52), wxSize(720, 563),evtList);
	createdEvt->Bind(wxEVT_LISTBOX, &AccountInfo::pickEvent,this);
	createdEvt->SetFont(font2);


	close = new wxButton(displayPanel, wxID_ANY, "X", wxPoint(503,6), wxSize(30,30));
	close->SetBackgroundColour(wxColor(229, 64, 50));
	close->Bind(wxEVT_BUTTON, &AccountInfo::closeClicked, this);


	event = new wxStaticText(displayPanel, wxID_ANY, "", wxPoint(100, 10));
	host= new wxStaticText(displayPanel, wxID_ANY, "", wxPoint(100, 40));
	addr= new wxStaticText(displayPanel, wxID_ANY, "", wxPoint(100, 70));
	price= new wxStaticText(displayPanel, wxID_ANY, "", wxPoint(100, 100));
	date= new wxStaticText(displayPanel, wxID_ANY, "", wxPoint(100, 130));
	time=new wxStaticText(displayPanel, wxID_ANY, "", wxPoint(100, 160));
	des= new wxStaticText(displayPanel, wxID_ANY, "", wxPoint(100, 200));
	
	if (isUser==1) {

		setUpFrameProfile();
	}
	else {
		setUpFrameDifProfile(searchedUser);
	}


	mainPanel->Layout();
}

/**
 * @brief This function sets up the profile frame for the current user by 
 * retrieving their information from the database and displaying it using 
 * wxStaticText widgets. The function uses a JSON object to store the retrieved
 * data and then extracts the required fields such as first name, last name, and date of 
 * birth. It then creates new wxStaticText widgets to display this information and sets the
 * appropriate labels. Overall, this function seems well-organized and clear in its implementation.
 * 
 */
void AccountInfo::setUpFrameProfile(){
	
	nlohmann::json data = handler->getUser(curUser);
	
	// Get values from JSON object
	std::cout<<"cras5\n";
	std::string nName = data["FirstName"];
	std::string lName = data["LastName"];
	int date = data["BDay"];
	int month = data["BMonth"];
	int year = data["BYear"];

	std::cout<<"cras6\n";
	// Set values to wxStaticText widgets
	nNameShow= new wxStaticText(infoPanel, wxID_ANY, "", wxPoint(95,42));
	dateShow= new wxStaticText(infoPanel, wxID_ANY, "", wxPoint(95,74));

	std::string l = nName + " " + lName;

	nNameShow->SetLabel(l);
	dateShow->SetLabel(wxString::Format("%d-%d-%d", date, month, year));

	std::cout<<"cras7\n";



}

/**
 * @brief The setUpFrameDifProfile function sets up the profile display for a different user that is being viewed.
 * It does so by checking if the current user is following the searched user, and creating a button to either follow or unfollow them based on the result.
 * It then retrieves and displays the basic user information for the searched user using JSON data.
 * 
 * @param findUsername 
 */
void AccountInfo::setUpFrameDifProfile(std::string findUsername){

	if(handler->isFollowing(curUser, searched)){
		butFollow= new wxButton(picPanel, wxID_ANY, "- Unfollow", wxPoint(60, 190), wxSize(200, 50));
		butFollow->Bind(wxEVT_BUTTON, &AccountInfo::clickedUnfollow, this);
	}else{
		butFollow= new wxButton(picPanel, wxID_ANY, "+ Follow", wxPoint(60, 190), wxSize(200, 50));
		butFollow->Bind(wxEVT_BUTTON, &AccountInfo::clickedFollow, this);
	}

	nlohmann::json data = handler->getUser(findUsername);

	std::string nName = data["FirstName"];
	std::string lName = data["LastName"];
	int date = data["BDay"];
	int month = data["BMonth"];
	int year = data["BYear"];

	// Set values to wxStaticText widgets
	nNameShow= new wxStaticText(infoPanel, wxID_ANY, "", wxPoint(95,42));
	dateShow= new wxStaticText(infoPanel, wxID_ANY, "", wxPoint(95,74));

	std::string l = nName + " " + lName;
	nNameShow->SetLabel(l);
	dateShow->SetLabel(wxString::Format("%d-%d-%d", date, month, year));


}

/**
 * @brief close the event info panel and show the list box of event
 * 
 * @param evt 
 */

void AccountInfo::closeClicked(wxCommandEvent& evt)
{
	createdEvt->Show();
	displayPanel->Hide();
}


/**
 * @brief show the detail of event when select in listbox
 * 
 * @param evt 
 */

void AccountInfo::pickEvent(wxCommandEvent& evt){

	int selection = createdEvt->GetSelection();
	this->displayPanel->Show();
	this->displayPanel->Raise();
	mainPanel->Layout();
	createdEvt->Hide();


	std::cout<<"cras1\n";
	std::string evtName = data[selection]["EventName"];
	
	std::string hostName = data[selection]["HostID"];
	std::string streetName = data[selection]["Address"]["StreetAddress"];

	std::string cityName = data[selection]["Address"]["City"];
	std::string stateName = data[selection]["Address"]["State"];
	std::string postalName = data[selection]["Address"]["PostalCode"];

	
	std::string dateName = data[selection]["Start"]["iso"];
	std::string priceNumb = "$" + to_string(data[selection]["Price"]);
	
	std::string desName = data[selection]["Description"];
	
	std::string fullAdd = streetName + ", "+cityName+", "+stateName+", "+postalName;

	std::string date_s = dateName.substr(0,10);
	std::string start_time = dateName.substr(11, 5);


	evtText = new wxStaticText(displayPanel, wxID_ANY, "Event Name:", wxPoint(10, 10));
	hostText = new wxStaticText(displayPanel, wxID_ANY, "Host:", wxPoint(10, 40));
	addrText = new wxStaticText(displayPanel, wxID_ANY, "Address:", wxPoint(10, 70));
	priceText = new wxStaticText(displayPanel, wxID_ANY, "Price:", wxPoint(10, 100));
	startText = new wxStaticText(displayPanel, wxID_ANY, "Start Date:", wxPoint(10, 130));
	timeText = new wxStaticText(displayPanel, wxID_ANY, "Start Time:", wxPoint(10, 160));
	desText =new wxStaticText(displayPanel, wxID_ANY, "Description:", wxPoint(10, 200));

	/*
	delete event;
	delete host;
	delete addr;
	delete price;
	delete date;
	delete time;
	delete des;*/

	event->SetLabel(evtName);
	host->SetLabel(hostName);
	addr ->SetLabel(fullAdd);
	price->SetLabel(priceNumb);
	date->SetLabel(date_s);
	time->SetLabel(start_time);
	des->SetLabel(desName);
}

/**
 * @brief add follow status of the searched user to the database 
 * 
 * @param evt 
 */
void AccountInfo::clickedFollow(wxCommandEvent& evt){
	handler->follow(curUser, searched);
	delete butFollow;
	butFollow= new wxButton(picPanel, wxID_ANY, "- Unfollow", wxPoint(60, 190), wxSize(200, 50));
	butFollow->Bind(wxEVT_BUTTON, &AccountInfo::clickedUnfollow, this);
}

/**
 * @brief remove follow status searched user form data base
 * 
 * @param evt 
 */
void AccountInfo::clickedUnfollow(wxCommandEvent& evt){
	handler->unfollow(curUser, searched);
	delete butFollow;
	butFollow= new wxButton(picPanel, wxID_ANY, "+ Follow", wxPoint(60, 190), wxSize(200, 50));
	butFollow->Bind(wxEVT_BUTTON, &AccountInfo::clickedFollow, this);
}