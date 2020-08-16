// main.cpp
// fire tool main

#ifdef _WIN32
#define USING_DLL 1
#endif
#include <iostream>
#include <cstdio>
#include <cstring>
#include <libattana.h>

using namespace ana;

inline void printBlock(const ResultsBlock& rb) {
    StudentRecord* sr;
    double persentage;
    
    printf("\n%7s %7s %-6s %-12s %-12s %-12s %-12s\n",
           " STU_ID",
           "NAME", "P_ID",
           "ATTEND",
           "LATE",
           "EARLY_LV",
           "ABSENT");
    printf("%7s %7s %-6s %-12s %-12s %-12s %-12s\n",
           "======",
           "======", "=====",
           "==========",
           "==========",
           "==========",
           "==========");
    
    for (int i = 0; i < rb.count(); i++) {
        sr = rb.stuList[i];
        persentage = sr->attend() / (double) rb.daysInvolved() * 100;
        printf("%8d %8s %5d %4d %6.2f%% %4d %6.2f%% %4d %6.2f%% %4d %6.2f%%\n",
               sr->stu.getStuID(),
               sr->stu.getStuName(), sr->stu.getPuncherID(),
               sr->attend(), sr->attend() / (double) rb.daysInvolved() * 100,
               sr->late(), sr->late() / (double) rb.daysInvolved() * 100,
               sr->earlyLeave(), sr->earlyLeave() / (double) rb.daysInvolved() * 100,
               sr->absent(), sr->absent() / (double) rb.daysInvolved() * 100);
    }
    printf("\n %d row(s) selected.\n\n", rb.count());
}

inline void printHelp(const char appName[]) {
    printf("Usage: %s [config-filename]\n", appName);
    printf("Arguments:\n");
    printf("\tconfig-filename\tconfig file, typically ends with '.yaml'\n");
    printf("\n");
    printf("Options:\n");
    printf("\t-h\t\tprint this help\n");
    printf("\n");
    printf("Version:\n");
    printf("\nAttendance Analyser version 1.0, built on %s %s\n", __DATE__, __TIME__);
    printf("\n");
    printf("Copyright:\n");
    printf("\t(c) 2020 Han Li Studios. All rights reserved.\n");
    printf("\tCourse design of the C++ Programming Practice Course (2).\n");
    printf("\n");
}

inline void printHead() {
    printf(" |Attendance Analyser version 1.0, built on %s %s\n", __DATE__, __TIME__);
    printf(" |Copyright (c) 2020 Han Li Studios. All rights reserved.\n");
    printf(" | - Type 'QUIT' to exit.\n");
    printf(" | - Type 'MAN' to get grammatical help.\n");
    printf(" +-----------------------------------------------------------------\n");
}

inline void printMan() {
    printf("\nHSQL GRAMMAR - HanLi SQL for Attendance Analyser version 1.0\n");
    printf("SELECT SENTENCES:\n");
    printf("\tNAME [student-name]\n");
    printf("\t\tpurpose: select a student by his/her name\n");
    printf("\t\te.g. NAME hanli\n\n");
    
    printf("\tSTUID [student-id]\n");
    printf("\t\tpurpose: select a student by his/her student ID\n");
    printf("\t\te.g. STUID 2203919\n\n");
    
    printf("\tSTART [start-date] END [end-date]\n");
    printf("\t\tpurpose: select records between two dates\n");
    printf("\t\te.g. START 2019-06-19 END 2019-07-16\n\n");
    
    printf("\tDATE [date]\n");
    printf("\t\tpurpose: select records within the date\n");
    printf("\t\te.g. DATE 2019-06-25\n\n");
    
    printf("\tRATE [BE | BN | SE | SN] [rate]\n");
    printf("\t\tpurpose: select records satisfying the rate and flag\n");
    printf("\t\tflags: BE - bigger & equal BN - begger & not equal\n\t\t\t   SE - smaller & equal SN - smaller & not equal\n");
    printf("\t\te.g. RATE SE 0.95\n\n");
    
    printf("\tRANGE [LERE | LERN | LNRE | LNRN] [left] [right]\n");
    printf("\t\tpurpose: select records between left & right\n");
    printf("\t\tflags: LERE - [left, right] LERN - [left, right)\n\t\t\t   LNRE - (left, right] LNRN - (left, right)\n");
    printf("\t\te.g. RANGE LERN 0.60 0.95 - indicates selecting range [0.60, 0.95)\n\n");
    
    printf("\tWEEKDAY [MON | TUE | WED | THU | FRI | SAT | SUN]\n");
    printf("\t\te.g. WEEKDAY WED\n\n");
}


int main(int argc, const char * argv[]) {
    // print help
    if (argc == 2 && 0 == strcmp(argv[1], "-h")) {
        printHelp(argv[0]);
        return 0;
    }
    
    // create a selector
    Selector *_se;
    if (argc < 2) {
        _se = new Selector();
    } else {
        _se = new Selector(argv[1]);
    }
    
    // check creation
    Selector& se = *_se;
    if (!se) {
        printHelp(argv[0]);
        return 0;
    }
    char buffer[200] = {0};
    
    // print head
    printHead();
    
    // select
    printf(">> ");
    std::cin.getline(buffer, 200);
    while (0 != strcmp(buffer, "quit") && 0 != strcmp(buffer, "QUIT")) {
        if (0 == strcmp(buffer, "MAN")) {
            // print manual
            printMan();
            // get another line
            printf(">> ");
            std::cin.getline(buffer, 200);
            continue;
        }
        // do select
        ResultsBlock rb = se.select(buffer);
        // show select results
        printBlock(rb);
        
        // get another line
        printf(">> ");
        std::cin.getline(buffer, 200);
    }
    
    printf("You are disconnecting from Attendance Analyse.\n\n");
    return 0;
}
