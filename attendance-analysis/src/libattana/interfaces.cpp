// interfaces.cpp
// libattana.h interfaces

#include <sstream>
#include <cstdio>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "attana.h"

namespace ana {

Analyser* createAnalyser(const char *configFile) {
    HourMin tInBeg, tInEnd, tOutBeg, tOutEnd;
    
    // get
    try {
        YAML::Node root = YAML::LoadFile(configFile);
        std::string stuList = root["stu_list"].as<std::string>(); //
        std::string punchList = root["punch_list"].as<std::string>(); //
        std::string startDate = root["start_date"].as<std::string>(); //
        std::string endDate = root["end_date"].as<std::string>(); //
        std::string pInBeg = root["p_in_begin"].as<std::string>(); //
        std::string pInEnd = root["p_in_end"].as<std::string>(); //
        std::string pOutBeg = root["p_out_begin"].as<std::string>(); //
        std::string pOutEnd = root["p_out_end"].as<std::string>(); //
        
        // parse time
        sscanf(pInBeg.c_str(), "%d.%d", &tInBeg.hr, &tInBeg.min);
        sscanf(pInEnd.c_str(), "%d.%d", &tInEnd.hr, &tInEnd.min);
        sscanf(pOutBeg.c_str(), "%d.%d", &tOutBeg.hr, &tOutBeg.min);
        sscanf(pOutEnd.c_str(), "%d.%d", &tOutEnd.hr, &tOutEnd.min);
        
        // create analyser
        Analyser* ana = new Analyser(tInBeg, tInEnd, tOutBeg, tOutEnd,
                                     Date(startDate.c_str()),
                                     Date(endDate.c_str()));
        
        // assign lists
        ana->readLists(stuList.c_str(), punchList.c_str());
        
        return ana;
    } catch (YAML::BadFile) {
        return NULL;
    } catch (...) {
        // any thrown
        std::cerr << "FATAL: invalid config file." << std::endl;
        exit(0);
    }
}

Selector::Selector(const char *configFile)
: ana(createAnalyser(configFile))
, isOK(true) {
    if (!ana) {
        isOK = false;
    }
}
    
Selector::Selector()
: ana(createAnalyser("conf.yaml"))
, isOK(true) {
    if (!ana) {
        isOK = false;
    }
}

Selector::~Selector() {
    delete ana;
}


ResultsBlock Selector::select(const char *expression) {
    std::istringstream ss(expression);
    static char buffer[100];
    
    ss.getline(buffer, 100, ' ');
    if (0 == strcmp(buffer, "NAME")) { // pass
        // search by name
        ss.getline(buffer, 100);
        return ResultsBlock(ana->get(buffer));
    }
    else if (0 == strcmp(buffer, "STUID")) { // pass
        // search by number
        ss.getline(buffer, 100);
        return ResultsBlock(ana->get(atoi(buffer)));
    }
    else if (0 == strcmp(buffer, "START")) { // MAYBE PASS
        // search by date scope
        char left[15], right[15];
        ss.getline(left, 15, ' ');
        ss.getline(buffer, 15, ' ');
        if (0 == strcmp(buffer, "END")) {
            ss.getline(right, 15);
            return ResultsBlock(ana->get(Date(left), Date(right)));
        }
        return ResultsBlock(0);
    }
    else if (0 == strcmp(buffer, "DATE")) { // PASS
        // search by date
        ss.getline(buffer, 100);
        return ResultsBlock(ana->get(Date(buffer), Date(buffer)));
    }
    else if (0 == strcmp(buffer, "RATE")) { // pass
        // search by attend rate
        ss.getline(buffer, 100, ' ');
        if (0 == strcmp(buffer, "BE")) {
            // bigger or equal
            ss >> buffer;
            return ResultsBlock(ana->get(atof(buffer), true, true));
        }
        else if (0 == strcmp(buffer, "BN")) {
            // bigger
            ss >> buffer;
            return ResultsBlock(ana->get(atof(buffer), true, false));
        }
        if (0 == strcmp(buffer, "SE")) {
            // smaller or equal
            ss >> buffer;
            return ResultsBlock(ana->get(atof(buffer), false, true));
        }
        else if (0 == strcmp(buffer, "SN")) {
            // smaller
            ss >> buffer;
            return ResultsBlock(ana->get(atof(buffer), false, false));
        }
        else {
            return ResultsBlock(0);
        }
    }
    else if (0 == strcmp(buffer, "RANGE")) { // pass
        // search rate between two values
        ss.getline(buffer, 100, ' ');
        char left[10], right[10];
        ss >> left >> right;
        if (0 == strcmp(buffer, "LERE")) {
            // bigger or equal
            return ResultsBlock(ana->get(atof(left), atof(right), true, true));
        }
        else if (0 == strcmp(buffer, "LERN")) {
            // bigger
            ss >> buffer;
            return ResultsBlock(ana->get(atof(left), atof(right), true, false));
        }
        if (0 == strcmp(buffer, "LNRE")) {
            // smaller or equal
            ss >> buffer;
            return ResultsBlock(ana->get(atof(left), atof(right), false, true));
        }
        else if (0 == strcmp(buffer, "LNRN")) {
            // smaller
            ss >> buffer;
            return ResultsBlock(ana->get(atof(left), atof(right), false, false));
        }
        else {
            return ResultsBlock(0);
        }
    }
    else if (0 == strcmp(buffer, "WEEKDAY")) {
        // search by weekday
        ss.getline(buffer, 100);
        if (0 == strcmp(buffer, "MON")) {
            return ResultsBlock(ana->get(MON));
        }
        else if (0 == strcmp(buffer, "TUE")) {
            return ResultsBlock(ana->get(TUE));
        }
        else if (0 == strcmp(buffer, "WED")) {
            return ResultsBlock(ana->get(WED));
        }
        else if (0 == strcmp(buffer, "THU")) {
            return ResultsBlock(ana->get(THU));
        }
        else if (0 == strcmp(buffer, "FRI")) {
            return ResultsBlock(ana->get(FRI));
        }
        else if (0 == strcmp(buffer, "SAT")) {
            return ResultsBlock(ana->get(SAT));
        }
        else if (0 == strcmp(buffer, "SUN")) {
            return ResultsBlock(ana->get(SUN));
        }
        else {
            return ResultsBlock(0);
        }
    }
    
    return ResultsBlock(0);
}

}
