/**
 * @file App.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, Will Reil
 * @brief Implementation of the App class which is the entry point of the application
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#pragma once
#include <wx/wx.h>

/**
* @brief The App class represents a wxWidgets application. The class inherits from wxApp.
*/
class App : public wxApp
{
public:
	/**
	* @brief The OnInit function is called when the application starts.
	* @return Returns true if the initialization is successful, false otherwise.
	*/
	bool OnInit();
};