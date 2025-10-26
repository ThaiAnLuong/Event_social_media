#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "single_include/nlohmann/json.hpp"

#ifndef HANDLER_CLASS_H
#define HANDLER_CLASS_H

class Handler{
    protected:
        std::string APIKey;
        std::string appId;
        void doRequest();
        void requestSetup(std::string, std::ofstream&);
        void eraseFiles();
        
    public:
        Handler(std::string, std::string);
};

#endif