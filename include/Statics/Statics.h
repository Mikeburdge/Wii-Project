#pragma once

#include <string>


class Debug
{
private:
    
public:
    Debug();
    ~Debug();

    static std::string getCurrentDateTime( std::string s );

    static void Log( std::string logMsg );

};