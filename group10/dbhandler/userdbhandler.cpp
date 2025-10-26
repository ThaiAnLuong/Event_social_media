#include "userdbhandler.h"

/**
 * @file userdbhandler.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, William Reil
 * @brief Header file for DisplayEvent.cpp file.
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

using namespace std;
using json = nlohmann::json;

/**
 * @brief Construct connects to database handler to get individual user informatio
 * 
 * @param appId 
 * @param APIKey 
 */

UserDBHandler::UserDBHandler(string appId, string APIKey) : Handler::Handler(appId, APIKey){ 

}

/**
 * @brief gets object id of specified user
 * 
 * @param username 
 * @return string 
 */

string UserDBHandler::getUserId(string username){
    return getUser(username)["objectId"];
}

/**
 * @brief Adds new user to with user information to database
 * 
 * @param fname 
 * @param lname 
 * @param username 
 * @param password 
 * @param securityQuestion 
 * @param answer 
 * @param bday 
 * @param bmonth 
 * @param byear 
 */

void UserDBHandler::addUser(string fname, string lname, string username, string password, int securityQuestion, string answer, int bday, int bmonth, int byear){
    ofstream myfile;
    myfile.open ("./dbhandler/request.sh");
    
    Handler::requestSetup("POST", myfile);

    myfile << "-d \'{\"FirstName\":\"" << fname << "\", ";
    myfile << "\"LastName\":\"" << lname << "\", ";
    myfile << "\"Username\":\"" << username << "\", ";
    myfile << "\"Password\":\"" << password << "\", ";
    myfile << "\"SecurityQuestion\":" << securityQuestion << ", ";
    myfile << "\"SQAnswer\":\"" << answer << "\", ";
    myfile << "\"BDay\":" << bday << ", ";
    myfile << "\"BMonth\":" << bmonth << ", ";
    myfile << "\"BYear\":" << byear << ", ";
    myfile << "\"Friends\": []}\' \\\n";

    myfile << "https://parseapi.back4app.com/classes/Users";
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief Used to get user details in json format
 * 
 * @param username 
 * @return json 
 */

json UserDBHandler::getUser(string username){
    ofstream myfile;
    myfile.open ("./dbhandler/request.sh");
    
    Handler::requestSetup("GET", myfile);

    myfile << "-G \\\n";
    myfile << "--data-urlencode \"where={\\\"Username\\\":\\\"" << username << "\\\"}\" \\\n";
    myfile << "https://parseapi.back4app.com/classes/Users";
    myfile.close();

    Handler::doRequest();

    ifstream outputFile;
    outputFile.open("./dbhandler/output.txt");

    string jsonstr;
    getline (outputFile, jsonstr);
    if(jsonstr.compare("{\"results\":[]}") == 0){
        Handler::eraseFiles();
        return NULL;
    }
    Handler::eraseFiles();
    return json::parse(jsonstr)["results"][0];
}

/**
 * @brief deletes user from database
 * 
 * @param username 
 */

void UserDBHandler::deleteUser(string username){
    string id = getUserId(username);
    
    ofstream myfile;
    myfile.open ("./dbhandler/request.sh");
    
    Handler::requestSetup("DELETE", myfile);

    myfile << "https://parseapi.back4app.com/classes/Users/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief Allows user to follow another user
 * 
 * @param curUser 
 * @param toAdd 
 */

void UserDBHandler::follow(string curUser, string toAdd){
    json userInfo = getUser(curUser);
    json friendList = userInfo["Friends"];
    string id = getUserId(curUser);
   
    ofstream myfile;
    myfile.open("./dbhandler/request.sh");

    Handler::requestSetup("PUT", myfile);
    myfile << "-d \'{\"Friends\": [";

    for(string f : friendList){
        myfile << "\"" << f << "\", ";
    }
    myfile << "\"" << toAdd << "\"]}\' \\\n";
    myfile << "https://parseapi.back4app.com/classes/Users/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief ALlows user to unfollow another previously followed user
 * 
 * @param curUser 
 * @param toRemove 
 */

void UserDBHandler::unfollow(string curUser, string toRemove){
    json userInfo = getUser(curUser);
    json friendList = userInfo["Friends"];
    string id = getUserId(curUser);
   
    ofstream myfile;
    myfile.open("./dbhandler/request.sh");

    Handler::requestSetup("PUT", myfile);
    myfile << "-d \'{\"Friends\": [";

    string res = "";

    for(string f : friendList){
        if(toRemove.compare(f) != 0){
            res += "\"" + f + "\", ";
        }
    }
    myfile << res.substr(0, res.length() - 2) << "]}\' \\\n";
    myfile << "https://parseapi.back4app.com/classes/Users/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief Checks if current user is following another user
 * 
 * @param curUser 
 * @param otherUser 
 * @return true 
 * @return false 
 */

bool UserDBHandler::isFollowing(string curUser, string otherUser){
    json userInfo = getUser(curUser);
    json friendList = userInfo["Friends"];

    for(string f : friendList){
        if(otherUser.compare(f) == 0){
            return true;
        }
    }
    return false;
}

/**
 * @brief Allows user to change their account password
 * 
 * @param curUser 
 * @param password 
 */

void UserDBHandler::changePassword(string curUser, string password){
    json userInfo = getUser(curUser);
    string id = getUserId(curUser);
   
    ofstream myfile;
    myfile.open("./dbhandler/request.sh");

    Handler::requestSetup("PUT", myfile);
    myfile << "-d \'{\"Password\": \"" << password << "\"}\' \\\n";
    myfile << "https://parseapi.back4app.com/classes/Users/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief Allows user to change thier username
 * 
 * @param curUser 
 * @param newName 
 */

void UserDBHandler::changeFirstName(string curUser, string newName){
    json userInfo = getUser(curUser);
    string id = getUserId(curUser);

    ofstream myfile;
    myfile.open("./dbhandler/request.sh");

    Handler::requestSetup("PUT", myfile);
    myfile << "-d \'{\"FirstName\": \"" << newName << "\"}\' \\\n";
    myfile << "https://parseapi.back4app.com/classes/Users/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief ALlows user to change thier last name
 * 
 * @param curUser 
 * @param newName 
 */
void UserDBHandler::changeLastName(string curUser, string newName){
    json userInfo = getUser(curUser);
    string id = getUserId(curUser);

    ofstream myfile;
    myfile.open("./dbhandler/request.sh");

    Handler::requestSetup("PUT", myfile);
    myfile << "-d \'{\"LastName\": \"" << newName << "\"}\' \\\n";
    myfile << "https://parseapi.back4app.com/classes/Users/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief ALlows user to change their entered birth date
 * 
 * @param curUser 
 * @param bday 
 * @param bmonth 
 * @param byear 
 */
void UserDBHandler::changeBirthday(string curUser, int bday, int bmonth, int byear){
    json userInfo = getUser(curUser);
    string id = getUserId(curUser);

    ofstream myfile;
    myfile.open("./dbhandler/request.sh");

    Handler::requestSetup("PUT", myfile);
    myfile << "-d \'{\"BDay\":" << bday << ", ";
    myfile << "\"BMonth\":" << bmonth << ", ";
    myfile << "\"BYear\":" << byear << "}\' \\\n";
    myfile << "https://parseapi.back4app.com/classes/Users/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}
/**
 * @brief Used to retrieve a list of friends of current user in json format
 * 
 * @param curUser 
 * @return vector<string> 
 */
vector<string> UserDBHandler::getFollowing(string curUser){
    json userInfo = getUser(curUser);
    vector<string> res;
    for(string f : userInfo["Friends"]){
        res.push_back(f);
    }
    return res;
}