#include "Statics/Statics.h"


/**
 * Debugger Log
*/
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

Debug::Debug()
{

}
Debug::~Debug()
{
    
}


string Debug::getCurrentDateTime(string s)
{
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    localtime_s(&tstruct, &now);
    if (s == "now")
        strftime(buf, sizeof(buf), "%d-%m-%Y_%H-%M-%S", &tstruct);
    else if (s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return string(buf);
};

void Debug::Log(string logMsg) {
    string filePath = "DebugLogs/log_" + getCurrentDateTime("now") + ".txt";

    ofstream outfile;
    outfile.open(filePath, std::ios_base::app);
    outfile << logMsg << endl;
    outfile.close();
}
