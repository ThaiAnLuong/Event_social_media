#include "database_handler.h"

using namespace std;
using json = nlohmann::json;

Handler::Handler(string appId, string APIKey){
    Handler::appId = appId;
    Handler::APIKey = APIKey;
}

void Handler::doRequest(){
    system("./dbhandler/request.sh > ./dbhandler/output.txt");
}

void Handler::requestSetup(string type, ofstream &file){
    file << "curl -X " << type << " \\\n";
    file << "-H \"X-Parse-Application-Id:" << Handler::appId << "\" \\\n";
    file << "-H \"X-Parse-REST-API-Key:" << Handler::APIKey << "\" \\\n";

    if(type.compare("POST") == 0 || type.compare("PUT") == 0){
        file << "-H \"Content-Type: application/json\" \\\n";
    }
}

void Handler::eraseFiles(){
    ofstream myfile;
    myfile.open ("./dbhandler/request.sh");
    myfile.close();

    myfile.open ("./dbhandler/output.txt");
    myfile.close();
}