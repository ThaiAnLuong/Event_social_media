#include "eventdbhandler.h"

using namespace std;
using json = nlohmann::json;

EventDBHandler::EventDBHandler(string appId, string APIKey) : Handler::Handler(appId, APIKey){ 

}
string EventDBHandler::getEventId(string name, string hostId){
    return getEvent(name, hostId)["objectId"];
}

void EventDBHandler::addEvent(string name, string hostId, string streetAddress, string city, string state, string postalCode, string startDate, string endDate, double price, string purchaseLink, string description){
    ofstream myfile;

    myfile.open ("./dbhandler/request.sh");

    Handler::requestSetup("POST", myfile);

    myfile << "-d \'{\"EventName\":\"" << name << "\", ";
    myfile << "\"HostID\":\""<< hostId <<"\", ";
    myfile << "\"Address\": {\"StreetAddress\":\"" << streetAddress <<"\", \"City\":\"" << city << "\", \"State\":\"" << state <<"\", \"PostalCode\":\"" << postalCode <<"\"}, ";
    myfile << "\"Start\": { \"__type\": \"Date\", \"iso\": \"" << startDate << "\" }" << ", ";
    myfile << "\"End\": { \"__type\": \"Date\", \"iso\": \"" << endDate << "\" }" << ", ";
    myfile << "\"Price\": " << price << ", ";
    myfile << "\"Link\": \"" << purchaseLink << "\", ";
    myfile << "\"Description\": \"" << description << "\"}\' \\\n";

    myfile << "https://parseapi.back4app.com/classes/Event";
    myfile.close();
    
    Handler::doRequest();
    Handler::eraseFiles();
}

json EventDBHandler::getEvent(string name, string hostId){
    ofstream myfile;
    myfile.open ("./dbhandler/request.sh");
    
    Handler::requestSetup("GET", myfile);

    myfile << "-G \\\n";
    myfile << "--data-urlencode \"where={\\\"EventName\\\":\\\"" << name <<"\\\", \\\"HostID\\\":\\\"" << hostId << "\\\"}\" \\\n";
    myfile << "https://parseapi.back4app.com/classes/Event";
    myfile.close();

    Handler::doRequest();

    ifstream outputFile;
    outputFile.open("./dbhandler/output.txt");

    string jsonstr;
    getline (outputFile, jsonstr);

    Handler::eraseFiles();
    return json::parse(jsonstr)["results"][0];
}

void EventDBHandler::deleteEvent(string name, string hostId){
    string id = getEventId(name, hostId);
    
    ofstream myfile;
    myfile.open ("./dbhandler/request.sh");
    
    Handler::requestSetup("DELETE", myfile);

    myfile << "https://parseapi.back4app.com/classes/Event/" << id;
    myfile.close();

    Handler::doRequest();
    Handler::eraseFiles();
}

vector<json> EventDBHandler::getEventsByHosts(vector<string> hosts){
    ofstream myfile;
    myfile.open ("./dbhandler/request.sh");
    
    Handler::requestSetup("GET", myfile);

    myfile << "https://parseapi.back4app.com/classes/Event";
    myfile.close();

    Handler::doRequest();

    ifstream outputFile;
    outputFile.open("./dbhandler/output.txt");

    string jsonstr;
    getline (outputFile, jsonstr);
    
    json j = json::parse(jsonstr)["results"];
    vector<json> v;
    for(json event : j){
        string host = event["HostID"];
        for(int i = 0; i < hosts.size(); i++){
            if(host.compare(hosts[i]) == 0){
                v.push_back(event);
                break;
            }
        }
    }
    Handler::eraseFiles();
    return v;
}