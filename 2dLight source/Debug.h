#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <SDL.h>
#include "GLGraphics.h"
#include "GLText.h"
#include <fstream>
#include <vector>

//#include "../Text/Text.h"

//////////////////////////////////////////////////////////////////////////////
//Namespace Debug
//////////////////////////////////////////////////////////////////////////////
//Outfiles a log, showing tasks accomplished (landmarks throughout program)
//Outfiles any errors that occur
//Takes in data in form "string, int" which can be displayed using DrawData()
//Sets TitleBar caption,can be used for debugging purposes
//////////////////////////////////////////////////////////////////////////////

namespace Debug
{
    //////Functions//////

    //Initializes members of Debug and opens txt files
    void Init();

     //Each opens a txt file in Logs folder
    extern std::ofstream outlog;
    extern std::ofstream outerr;

    //Writes the given data to "J_Log.txt"
    template <class T>
    void Log(T log){
        outlog << log;
    }

    //Writes the given data to "J_Err.txt"
    template <class T>
    void Error(T err){
        outerr << SDL_GetTicks() << " -- " << err << std::endl;
    }

    //Captions up to 4 integers as the title
    void Caption(int, int a = -3, int b = -3, int c = -3, int d = -3, int e = -3);

    //Captions up to 4 strings as the title
    void Caption(std::string, std::string a = "", std::string b = "", std::string c = "");

    //Captions up to 4 Captions of "string = int" data as the title
    void Caption(std::string, int, std::string a = "", int w = -3, std::string b = "", int x = -3, std::string c = "", int y = -3, std::string d = "", int z = -3);

    //Tracks fps and displays it using the Debug method. pass in num frames b/w samples
    void FPS(int);

    //Debug Event queue for menu use
    void Events();

    //runs settings menu
    void RunMenu();

    //Frees memory used by Debug, called at program exit
    void Quit();


    //////Data Structures//////

    //Stores the data Given by void Data(string, int)
    extern std::vector<std::string> vNames;
    extern std::vector<int> vNums;
    extern float last, newtime, diff, fps;
    extern int mouseY, mouseX;
//    extern Menu Settings;
//    extern bool menuRunning;


    //////Member Variables//////



    //Stores the square image used to tile the debug window background
    extern SDL_Surface* bg;
}

#endif // DEBUG_H_INCLUDED
