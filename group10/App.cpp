/**
 * @file App.cpp
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Implementation of the App class which is the entry point of the application
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include <wx/wx.h>
#include "MainFrame.h"
#include "App.h"

/**
* @brief The entry point of the application
* @return bool Whether the initialization was successful
*/
bool App::OnInit()
{
	MainFrame *mainFrame = new MainFrame("Login", wxPoint(50, 50), wxSize(1204, 720)); // Create a new instance of the main frame
	mainFrame->Center();															   // Center the main frame
	mainFrame->Show();																   // Show the main frame
	return true;																	   // Return true to indicate successful initialization
}

wxIMPLEMENT_APP(App); // Define the entry point for the wxWidgets application. This creates the wxApp instance and calls OnInit() method.
