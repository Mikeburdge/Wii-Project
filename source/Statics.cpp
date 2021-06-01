#include "Utility/Statics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <zlib.h>
#include <fat.h>

using namespace std;

bool setting_background_music = false;
bool setting_rumble = true;
bool setting_tips = true;

namespace Debug
{
    // string getCurrentDateTime(string s)
    // {
    //     time_t now;
    //     now = time(NULL);
    //     tm *tstruct = localtime(&now);
    //     char buf[80];
    //     if (s == "now")
    //         strftime(buf, sizeof(buf), "%d-%m-%Y_%H-%M-%S", tstruct);
    //     else if (s == "date")
    //         strftime(buf, sizeof(buf), "%Y-%m-%d", tstruct);

    //     return string(buf);
    // };

    // void Log(string logMsg)
    // {
    //     string filePath = "DebugLogs/log_" + getCurrentDateTime("now") + ".txt";

    //     ofstream outfile;
    //     outfile.open(filePath, std::ios_base::app);
    //     outfile << logMsg << endl;
    //     outfile.close();
    // }

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
        // mxml_node_t *xml;
        // mxml_node_t *data;
        // xml = mxmlNewXML("1.0");

        // data = mxmlNewElement(xml, "settings");

        // char set1[1];
        // sprintf(set1, "%i", setting_background_music);
        // mxmlElementSetAttr(data, "setting_background_music", set1);
        // char set2[1];
        // sprintf(set2, "%i", setting_rumble);
        // mxmlElementSetAttr(data, "setting_rumble", set2);
        // char set3[1];
        // sprintf(set3, "%i", setting_tips);
        // mxmlElementSetAttr(data, "setting_tips", set3);

        // FILE *f;
        // f = fopen("sd:/settings.xml", "wb");

        // if (f == NULL)
        // {
        //     fclose(f);
        //     printf("Settings could not be written.\n");
        // }
        // else
        // {
        //     mxmlSaveFile(xml, f, MXML_NO_CALLBACK);
        //     fclose(f);
        //     mxmlDelete(data);
        //     mxmlDelete(xml);
        //     printf("Settings Saved\n\n");
        // }
    }
}