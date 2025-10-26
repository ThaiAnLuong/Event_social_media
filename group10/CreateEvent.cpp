/**
 * @file CreateEvent.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief 
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "CreateEvent.h"

using json = nlohmann::json;
using namespace std;

/**
* @brief The CreateEvent class represents a dialog for creating an event. The dialog contains various fields for inputting event details and a button for creating the event. The class inherits from wxFrame.
* @param title The title of the dialog.
* @param pos The position of the dialog.
* @param size The size of the dialog.
* @param host The host of the event.
*/
CreateEvent::CreateEvent(const wxString& title, const wxPoint& pos, const wxSize& size, string curUser): wxFrame(NULL, wxID_ANY, title, pos, size) {
	handler = new EventDBHandler("ZFnmztRFXdNoVb3346Pb7tXUKvXhBkYFqk5SJqqq", "30lMxOm9wNbWf2bOJ5g859A7LmsCITY5bNHZf7k6");
	this->host = curUser;

	//SHIFTS ELEMENTS ON THE PAGE
	int y_adjust = -40;
	wxColour text_colour = wxColour(255, 255, 255);
	wxColour backg_colour = wxColour(22, 41, 110);

	// Create a sizer to manage the layout of the widgets
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	// Add the existing widgets to the sizer

	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	mainPanel->SetBackgroundColour(wxColor(13, 28, 83));

	// EVENT LOGO
	wxImage::AddHandler(new wxPNGHandler());
	wxImage image;
	if (!image.LoadFile("./images/logo_text_white.png", wxBITMAP_TYPE_PNG))
	{
		// Handle the error (e.g. show an error message)
		return;
	}
	image.Rescale(200, 208);

	wxBitmap bitmap(image);
	if (!bitmap.IsOk())
	{
		// Handle the error (e.g. show an error message)
		return;
	}

	wxStaticBitmap *staticBitmap = new wxStaticBitmap(mainPanel, wxID_ANY, bitmap);
	staticBitmap->SetPosition(wxPoint(500, -35));

	// Calculate the size of the image
	wxSize imageSize = bitmap.GetSize();

	// Set the size of the static bitmap to be the same as the size of the image
	staticBitmap->SetSize(wxSize(200,208));

	// Static text that serves as labels for the input boxes.
	wxStaticText* eventNameLabel = new wxStaticText(mainPanel, wxID_ANY, "Event Name:", wxPoint(300, 175 + y_adjust), wxDefaultSize, 0);
	wxStaticText* streetAddressLabel = new wxStaticText(mainPanel, wxID_ANY, "Street Address:", wxPoint(550, 175 + y_adjust), wxDefaultSize, 0);
	wxStaticText* cityLabel = new wxStaticText(mainPanel, wxID_ANY, "City:", wxPoint(300, 250 + y_adjust), wxDefaultSize, 0);
	wxStaticText* stateLabel = new wxStaticText(mainPanel, wxID_ANY, "State:", wxPoint(520, 250 + y_adjust), wxDefaultSize, 0);
	wxStaticText* postalCodeLabel = new wxStaticText(mainPanel, wxID_ANY, "Postal Code:", wxPoint(733, 250 + y_adjust), wxDefaultSize, 0);

	wxStaticText* startDateLabel = new wxStaticText(mainPanel, wxID_ANY, "Start Date:", wxPoint(300, 325 + y_adjust), wxDefaultSize, 0);
	wxStaticText* endDateLabel = new wxStaticText(mainPanel, wxID_ANY, "End Date:", wxPoint(300, 400 + y_adjust), wxDefaultSize, 0);
	wxStaticText* priceLabel = new wxStaticText(mainPanel, wxID_ANY, "Price:", wxPoint(300, 475 + y_adjust), wxDefaultSize, 0);
	wxStaticText* purchaseLinkLabel = new wxStaticText(mainPanel, wxID_ANY, "Purchase Link:", wxPoint(550, 475 + y_adjust), wxDefaultSize, 0);
	wxStaticText* descriptionLabel = new wxStaticText(mainPanel, wxID_ANY, "Description:", wxPoint(300, 550 + y_adjust), wxDefaultSize, 0);

	eventNameLabel->SetForegroundColour(text_colour);
	streetAddressLabel->SetForegroundColour(text_colour);
	cityLabel->SetForegroundColour(text_colour);
	stateLabel->SetForegroundColour(text_colour);
	postalCodeLabel->SetForegroundColour(text_colour);
	startDateLabel->SetForegroundColour(text_colour);
	endDateLabel->SetForegroundColour(text_colour);
	priceLabel->SetForegroundColour(text_colour);
	purchaseLinkLabel->SetForegroundColour(text_colour);
	descriptionLabel->SetForegroundColour(text_colour);

	// Text boxes for the user to enter the party location information.
	eventName = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(300, 200 + y_adjust), wxSize(200, 30));
	streetAddress = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(550, 200 + y_adjust), wxSize(350, 30));
	city = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(300, 275 + y_adjust), wxSize(166, 30));
	state = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(520, 275 + y_adjust), wxSize(167, 30));
	postalCode = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(733, 275 + y_adjust), wxSize(167, 30));

	eventName->SetBackgroundColour(backg_colour);
	streetAddress->SetBackgroundColour(backg_colour);
	city->SetBackgroundColour(backg_colour);
	state->SetBackgroundColour(backg_colour);
	postalCode->SetBackgroundColour(backg_colour);


	wxArrayString days;
	wxArrayString months;
	wxArrayString years;
	wxArrayString times;

	for(int i = 1; i <= 31; i++){
		string temp = to_string(i);
		days.Add(temp);
	}

	for(int i = 1; i <= 12; i++){
		string temp = to_string(i);
		months.Add(temp);
	}

	for(int i = 2023; i <= 2050; i++){
		string temp = to_string(i);
		years.Add(temp);
	}

	for(int i = 0; i <= 23; i++){
		string temp = to_string(i) + ":00";
		string temp2 = to_string(i) + ":30";

		times.Add(temp);
		times.Add(temp2);
	}

	// List of selectors for the start data
	startDay = new wxChoice(mainPanel, wxID_ANY, wxPoint(300, 350 + y_adjust), wxSize(112, 29), days);
	startMonth = new wxChoice(mainPanel, wxID_ANY, wxPoint(462, 350 + y_adjust), wxSize(113, 29), months);
	startYear = new wxChoice(mainPanel, wxID_ANY, wxPoint(625, 350 + y_adjust), wxSize(113, 29), years);
	startTime = new wxChoice(mainPanel, wxID_ANY, wxPoint(788, 350 + y_adjust), wxSize(112, 29), times);

	// List of selectors for the start data
	endDay = new wxChoice(mainPanel, wxID_ANY, wxPoint(300, 425 + y_adjust), wxSize(112, 29), days);
	endMonth = new wxChoice(mainPanel, wxID_ANY, wxPoint(462, 425 + y_adjust), wxSize(113, 29), months);
	endYear = new wxChoice(mainPanel, wxID_ANY, wxPoint(625, 425 + y_adjust), wxSize(113, 29), years);
	endTime = new wxChoice(mainPanel, wxID_ANY, wxPoint(788, 425 + y_adjust), wxSize(112, 29), times);

	// Input fields for price, the purchase link, and party description.
	price = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(300, 500 + y_adjust), wxSize(200, 30));
	purchaseLink = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(550, 500 + y_adjust), wxSize(350, 30));
	description = new wxTextCtrl(mainPanel, wxID_ANY, "", wxPoint(300, 575 + y_adjust), wxSize(600, 30));

	price->SetBackgroundColour(backg_colour);
	purchaseLink->SetBackgroundColour(backg_colour);
	description->SetBackgroundColour(backg_colour);

	create = new wxButton(mainPanel, wxID_ANY, "Create", wxPoint(800, 625 + y_adjust), wxSize(100, 30));
	create->SetWindowStyle(wxBORDER_NONE);
	create->Bind(wxEVT_BUTTON, &CreateEvent::onCreate, this);
}


/**
 * @brief The onCreate function is called when the create button is clicked. It submits the information in the respective input fields.
 * @param evt The event that triggered the function.
 */
void CreateEvent::onCreate(wxCommandEvent& evt){
	string _name = (eventName->GetValue()).ToStdString();
	string _address = (streetAddress->GetValue()).ToStdString();
	string _city = (city->GetValue()).ToStdString();
	string _state = (state->GetValue()).ToStdString();
	string _postalCode = (postalCode->GetValue()).ToStdString();

	string _startDay = (startDay->GetString(startDay->GetSelection())).ToStdString();
	if(startDay->GetSelection() < 9){
		_startDay = "0" + _startDay;
	}
	string _startMonth = (startMonth->GetString(startMonth->GetSelection())).ToStdString();
	if(startMonth->GetSelection() < 9){
		_startMonth = "0" + _startMonth;
	}
	string _startYear = (startYear->GetString(startYear->GetSelection())).ToStdString();
	string _startTime = (startTime->GetString(startTime->GetSelection())).ToStdString();
	string startDate = _startYear + "-" + _startMonth + "-" + _startDay + "T" + _startTime + ":00.000Z";
	
	string _endDay = (endDay->GetString(endDay->GetSelection())).ToStdString();
	if(endDay->GetSelection() < 9){
		_endDay = "0" + _endDay;
	}
	string _endMonth = (endMonth->GetString(endMonth->GetSelection())).ToStdString();
	if(endMonth->GetSelection() < 9){
		_endMonth = "0" + _endMonth;
	}
	string _endYear = (endYear->GetString(endYear->GetSelection())).ToStdString();
	string _endTime = (endTime->GetString(endTime->GetSelection())).ToStdString();
	string endDate = _endYear + "-" + _endMonth + "-" + _endDay + "T" + _endTime + ":00.000Z";

	if(((price->GetValue()).ToStdString()).compare("") == 0){
		wxLogMessage("Please Fill In All Fields");
		return;
	}

	double _price = stof((price->GetValue()).ToStdString());
	string _link = (purchaseLink->GetValue()).ToStdString();
	string _description = (description->GetValue()).ToStdString();


	if(_name.compare("") != 0 && _address.compare("") != 0 && _city.compare("") != 0 && _state.compare("") != 0 && _postalCode.compare("") != 0 && (price->GetValue()).ToStdString().compare("") != 0){
		handler->addEvent(_name, this->host, _address, _city, _state, _postalCode, startDate, endDate, _price, _link, _description);
		wxLogMessage("Event Created");
		this->Hide();
	}else{
		wxLogMessage("Please Fill In All Fields");
	}
}

