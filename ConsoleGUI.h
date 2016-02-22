#ifndef CONSOLEGUI_H
#define CONSOLEGUI_H

#include <cstring>
#include <cstdint>
#include <iostream>
#include <ncurses.h>
#include <pcap/pcap.h>
#include <unistd.h>
#include "AccessPoint.h"

using namespace std;
using std::string;

class ConsoleGUI
{
//Constructors/Destructors
public:
    ConsoleGUI();
    ~ConsoleGUI();

//attributes
public:
    string title;
    string copyright;

     /*
     _    _  ____  ___    ___   ___    __    _  _ 
    ( \/\/ )(  _ \/ __)  / __) / __)  /__\  ( \( )
     )    (  )___/\__ \  \__ \( (__  /(__)\  )  ( 
    (__/\__)(__)  (___/  (___/ \___)(__)(__)(_)\_)
    */
    string logo_line_1;
    string logo_line_2;
    string logo_line_3;
    string logo_line_4;

    int rows, cols;

//methods
public:
    void addLine(int iPositionX, int iPositionY, AccessPoint accessPoint);
    void showGUI();
    void clearGUI();

private:
    void basicTemplate();
};


#endif // CONSOLEGUI_H
