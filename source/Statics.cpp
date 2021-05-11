#include "Utility/Statics.h"

/**
 * Debugger Log
*/
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

namespace Debug
{
    string getCurrentDateTime(string s)
    {
        time_t now;
        now = time(NULL);
        tm *tstruct = localtime(&now);
        char buf[80];
        if (s == "now")
            strftime(buf, sizeof(buf), "%d-%m-%Y_%H-%M-%S", tstruct);
        else if (s == "date")
            strftime(buf, sizeof(buf), "%Y-%m-%d", tstruct);

        return string(buf);
    };

    void Log(string logMsg)
    {
        string filePath = "DebugLogs/log_" + getCurrentDateTime("now") + ".txt";

        ofstream outfile;
        outfile.open(filePath, std::ios_base::app);
        outfile << logMsg << endl;
        outfile.close();
    }
}