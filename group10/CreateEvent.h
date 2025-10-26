/**
 * @file CreateEvent.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Contains the CreateEvent class definition and its methods
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
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
#include <iostream>
#include "./dbhandler/eventdbhandler.h"

/**
* @brief The CreateEvent class represents a dialog for creating an event. The dialog contains various fields for inputting event details and a button for creating the event. The class inherits from wxFrame.
*/
class CreateEvent : public wxFrame
{
public:
	/**
	* @brief CreateEvent constructor.
	* @param title The title of the dialog.
	* @param pos The position of the dialog.
	* @param size The size of the dialog.
	* @param host The host of the event.
	*/
	CreateEvent(const wxString &title, const wxPoint &pos, const wxSize &size, std::string);

private:
	EventDBHandler *handler; /** A pointer to an instance of EventDBHandler. */
	std::string host;		 /** The host of the event. */

	wxTextCtrl *eventName;	   /** A pointer to the text control for inputting the event name. */
	wxTextCtrl *streetAddress; /** A pointer to the text control for inputting the street address. */
	wxTextCtrl *city;		   /** A pointer to the text control for inputting the city. */
	wxTextCtrl *state;		   /** A pointer to the text control for inputting the state. */
	wxTextCtrl *postalCode;	   /** A pointer to the text control for inputting the postal code. */
	wxChoice *startDay;		   /** A pointer to the choice control for selecting the start day. */
	wxChoice *startMonth;	   /** A pointer to the choice control for selecting the start month. */
	wxChoice *startYear;	   /** A pointer to the choice control for selecting the start year. */
	wxChoice *startTime;	   /** A pointer to the choice control for selecting the start time. */
	wxChoice *endDay;		   /** A pointer to the choice control for selecting the end day. */
	wxChoice *endMonth;		   /** A pointer to the choice control for selecting the end month. */
	wxChoice *endYear;		   /** A pointer to the choice control for selecting the end year. */
	wxChoice *endTime;		   /** A pointer to the choice control for selecting the end time. */
	wxTextCtrl *price;		   /** A pointer to the text control for inputting the event price. */
	wxTextCtrl *purchaseLink;  /** A pointer to the text control for inputting the purchase link. */
	wxTextCtrl *description;   /** A pointer to the text control for inputting the event description. */
	wxButton *create;		   /** A pointer to the button for creating the event. */

	/**
	 * @brief The onCreate function is called when the create button is clicked.
	 * @param evt The event that triggered the function.
	 */
	void onCreate(wxCommandEvent &evt);
};
