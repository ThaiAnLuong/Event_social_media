#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "database_handler.h"
#include "single_include/nlohmann/json.hpp"

#ifndef USERBHANDLER_CLASS_H
#define USERBHANDLER_CLASS_H

/**
 * @file userdbhandler.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, William Reil
 * @brief Header file for userDBHandler.cpp file.
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

class UserDBHandler: public Handler{  

    /**
     * @brief defines constructor parameters
     * 
     */
    private:
        std::string getUserId(std::string);


    /**
     * @brief defines each of the methods in userDBHandler.cpp file with parameters
     * 
     */

    public:
        UserDBHandler(std::string, std::string);
        void addUser(std::string, std::string, std::string, std::string, int, std::string, int, int, int);
        nlohmann::json getUser(std::string);
        void deleteUser(std::string);
        void follow(std::string, std::string);
        void unfollow(std::string, std::string);
        bool isFollowing(std::string, std::string);
        void changePassword(std::string, std::string);
        void changeFirstName(std::string, std::string);
        void changeLastName(std::string, std::string);
        void changeBirthday(std::string, int, int, int);
        std::vector<std::string> getFollowing(std::string);
};

#endif