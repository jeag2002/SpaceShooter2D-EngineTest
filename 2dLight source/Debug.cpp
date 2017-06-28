#include "Debug.h"

namespace Debug
{
    std::ofstream outlog;
    std::ofstream outerr;

    float last, newtime, diff, fps;
    int mouseX;
    int mouseY;

    std::vector<std::string> vNames;
    std::vector<int> vNums;

    SDL_Surface* bg;

    char buffer2[33];

    void Init(){
        outlog.open("Logs/D_Log.txt");
        outerr.open("Logs/D_Err.txt");
    }

    void Caption(int num, int a, int b, int c, int d, int e){
        std::string caption = itoa(num, buffer2, 10);

        //a, b, and c are Caption to default values in case the user wants less than the full amount of integers
        if(a != -3)  {caption += "   "; caption+=itoa(a, buffer2, 10);}
        if(b != -3)  {caption += "   "; caption+=itoa(b, buffer2, 10);}
        if(c != -3)  {caption += "   "; caption+=itoa(c, buffer2, 10);}
        if(d != -3)  {caption += "   "; caption+=itoa(d, buffer2, 10);}
        if(e != -3)  {caption += "   "; caption+=itoa(e, buffer2, 10);}
        Text::DrawString(5, 10, 0, GLUT_BITMAP_TIMES_ROMAN_10, caption.c_str());
    }

    void Caption(std::string caption, std::string a, std::string b, std::string c){
        std::string total = caption;

        //a, b, and c are Caption to default values in case the user wants less than the full amount of integers
        if(a != "")  {total += a;}
        if(b != "")  {total += b;}
        if(c != "")  {total += c;}

        Text::DrawString(5, 10, 0, GLUT_BITMAP_TIMES_ROMAN_10, caption.c_str());
    }

    void Caption(std::string c1s, int c1i, std::string c2s, int c2i, std::string c3s, int c3i, std::string c4s, int c4i, std::string c5s, int c5i){
        std::string total = c1s + " = " + itoa(c1i, buffer2, 10);

        //Other parameters are Caption to default values in case the user wants less than the full amount of integers
        if(c2s != "")  {total += "       " + c2s + " = " + itoa(c2i, buffer2, 10);}
        if(c3s != "")  {total += "       " + c3s + " = " + itoa(c3i, buffer2, 10);}
        if(c4s != "")  {total += "       " + c4s + " = " + itoa(c4i, buffer2, 10);}
        if(c5s != "")  {total += "       " + c5s + " = " + itoa(c5i, buffer2, 10);}

        Text::DrawString(5, 10, 0, GLUT_BITMAP_TIMES_ROMAN_10, total.c_str());
    }

    void FPS(int frames){
        static int count = 0;

        count++;
        if(count>=frames){
        newtime = SDL_GetTicks();
        diff    = newtime-last;
        fps     = 1000/diff;
        last    = newtime;
        count = 0;
        fps *= frames;
        }
        sprintf(buffer2, "%f fps -- %f", fps, (diff/1000)/frames);
        Text::DrawString(5, 25, 0, GLUT_BITMAP_TIMES_ROMAN_10, buffer2);
    }

    void Events(){
//    static SDL_Event Event;
//        while(SDL_PollEvent(&Event)){
//            switch(Event.type){
//                    case SDL_MOUSEMOTION:
//                        mouseX = Event.motion.x;
//                        mouseY = Event.motion.y;
//                        break;
//
//                    case SDL_MOUSEBUTTONDOWN:
//
//                    switch(Event.button.button){
//                        case SDL_BUTTON_LEFT:
//                            //OnClick();
//                        break;
//
//                        default: break;
//                    }
//                    case SDL_KEYDOWN:   //handle keydown event
//                    switch(Event.key.keysym.sym){
//                        case SDLK_F8:
//                            if(MenuRunning)MenuRunning^=1;else RunMenu();
//                            break;
//                        default: break;
//                    }
//                        break;
//                    default: break;
//            } // end of event.type
//        }
    }

    void RunMenu(){
//        Settings.Init(GLGraphics::win_width/2 - 100, GLGraphics::win_height/2 - 100);
//        Settings.AddButton(10, 10, "option1!", 1);
//        Settings.AddButton(10, 30, "option2!", 2);
//        Settings.AddButton(10, 50, "option3!", 3);
//        Settings.AddButton(10, 70, "option4!", 4);;
//        boxColor(GLGraphics::screen,
//                 GLGraphics::win_width/2 - 100,
//                 GLGraphics::win_height/2 - 200,
//                 GLGraphics::win_width/2 + 100,
//                 GLGraphics::win_width/2 + 200,
//                 0x3d3d3dFF);
//        while(MenuRunning){
//        Events();
//        Settings.DrawButtons();
//            switch(Settings.Update()){
//
//            }
//        }
//        Settings.CloseMenu();
    }

    void Quit(){
        outlog.close();
        outerr.close();
        SDL_FreeSurface(bg);
    }
}
