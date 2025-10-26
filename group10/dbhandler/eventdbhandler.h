#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "single_include/nlohmann/json.hpp"
#include "database_handler.h"

/**
 * @file eventdbhandler.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, William Reil
 * @brief Header file for eventdbhandler.cpp file.
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EVENTDBHANDLER_CLASS_H
#define EVENTDBHANDLER_CLASS_H

class EventDBHandler: public Handler{  

    /**
     * @brief defines parameters for constructor
     * 
     */
    private:
        std::string getEventId(std::string, std::string);

    /**
     * @brief defines constructor parameters for the various event functions
     * 
     */

    public:
        EventDBHandler(std::string, std::string);
        void addEvent(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string, double, std::string, std::string);
        nlohmann::json getEvent(std::string, std::string);
        void deleteEvent(std::string, std::string);
        std::vector<nlohmann::json> getEventsByHosts(std::vector<std::string>);

        //to do: add update methods
};

#endif