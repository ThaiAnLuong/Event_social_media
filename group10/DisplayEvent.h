/**
 * @file DisplayEvent.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Contains the DisplayEvent class definition and its methods
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/image.h>
#include "single_include/nlohmann/json.hpp"
#include <iomanip>
#include <fstream>
#include <wx/file.h>
#include <iostream>
#include <wx/listctrl.h>
#include <vector>
#include "./dbhandler/eventdbhandler.h"
#include "./dbhandler/userdbhandler.h"

/**
 * @brief Defines constructor parameters
 */
class DisplayEvent :public wxFrame
{

public:
	/**
	* @brief DisplayEvent constructor.
	* @param title The title of the dialog.
	* @param pos The position of the dialog.
	* @param size The size of the dialog.
	* @param curUser The current user of the application.
	*/
	DisplayEvent(const wxString &title, const wxPoint &pos, const wxSize &size, std::string curUser);


/**
 * @brief Used to connect to UserDBHandler and EventDBHandler to access database 
 */
private:
	UserDBHandler *userHandler;	 /** A pointer to an instance of UserDBHandler. */
	EventDBHandler *eventHandler; /** A pointer to an instance of EventDBHandler. */
	std::string user;			 /** The current user of the application. */
};
