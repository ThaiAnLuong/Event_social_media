#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "database_handler.h"
#include "single_include/nlohmann/json.hpp"

/**
 * @file invitedbhandler.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, William Reil
 * @brief Header file for invitedbhandler.cpp file.
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INVITEDBHANDLER_CLASS_H
#define INVITEDBHANDLER_CLASS_H


class InviteDBHandler: public Handler{  

    /**
     * @brief defines constructor parameters
     * 
     */
    private:
        std::string getInviteId(std::string, std::string);

    /**
     * @brief defines parameters for various invite functions
     * 
     */

    public:
        InviteDBHandler(std::string, std::string);
        void addInvite(std::string, std::string, std::string, int);
        nlohmann::json getInvite(std::string, std::string); //event id and invite id
        void deleteInvite(std::string, std::string);
};

#endif