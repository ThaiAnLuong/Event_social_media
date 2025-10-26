#include "invitedbhandler.h"

/**
 * @file invitedbhandler.h
 * @author Thai Luong, Andrew Kwan, John Curran Krupa, Yash Gupta, William Reil
 * @brief meant to be used to add send invites of events to friends from user
 * @version 0.1
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

using namespace std;
using json = nlohmann::json;

/**
 * @brief Connects to invites database
 * 
 * @param appId 
 * @param APIKey 
 */

InviteDBHandler::InviteDBHandler(string appId, string APIKey) : Handler::Handler(appId, APIKey){ 

}

/**
 * @brief returns invites list
 * 
 * @param eventId 
 * @param inviteId 
 * @return string 
 */

string InviteDBHandler::getInviteId(string eventId, string inviteId){
    return getInvite(eventId, inviteId)["objectId"];
}

/**
 * @brief adds new invite
 * 
 * @param message 
 * @param eventId 
 * @param inviteId 
 * @param inviteStatus 
 */
void InviteDBHandler::addInvite(string message, string eventId, string inviteId, int inviteStatus){
    ofstream myfile;
    myfile.open ("request.sh");
    
    Handler::requestSetup("POST", myfile);

    myfile << "-d \'{\"Message\":\"" << message << "\", ";
    myfile << "\"EventID\":\"" << eventId << "\", ";
    myfile << "\"InviteID\":\"" << inviteId << "\", ";
    myfile << "\"InviteStatus\":" << inviteStatus << "}\' \\\n";

    myfile << "https://parseapi.back4app.com/classes/Invite";
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

/**
 * @brief returns invites in json format with details
 * 
 * @param eventId 
 * @param inviteId 
 * @return json 
 */
json InviteDBHandler::getInvite(string eventId, string inviteId){
    ofstream myfile;
    myfile.open ("request.sh");
    
    Handler::requestSetup("GET", myfile);

    myfile << "-G \\\n";
    myfile << "--data-urlencode \"where={\\\"EventID\\\":\\\"" << eventId <<"\\\", \\\"InviteID\\\":\\\"" << inviteId << "\\\"}\" \\\n";
    myfile << "https://parseapi.back4app.com/classes/Invite";
    myfile.close();

    Handler::doRequest();

    ifstream outputFile;
    outputFile.open("output.txt");

    string jsonstr;
    getline (outputFile, jsonstr);

    Handler::eraseFiles();
    return json::parse(jsonstr)["results"][0];
}

/**
 * @brief deletes created invite
 * 
 * @param name 
 * @param hostId 
 */

void InviteDBHandler::deleteInvite(string name, string hostId){
    string id = getInviteId(name, hostId);
    
    ofstream myfile;
    myfile.open ("request.sh");
    
    Handler::requestSetup("DELETE", myfile);

    myfile << "https://parseapi.back4app.com/classes/Invite/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}