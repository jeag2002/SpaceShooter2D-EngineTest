
#include "Utils.h"


//marca de tiempo log.
string getDateTime(void){

  char stringFecha[TAMANO];
  string output;
  time_t curtime;
  struct tm *loctime;

  curtime = time (NULL);
  loctime = localtime (&curtime);

  strftime (stringFecha, TAMANO, "(%d/%m/%Y - %H:%M:%S) - ", loctime);

  output = stringFecha;

  return output;
}



void debug_message(const std::string fmt, ...)
{
	va_list ap;
    char msg[200];

	int flag = 1;


    //solo si el flag de log esta 1 esto funciona
    if (flag>0){
		va_start(ap, fmt);
		vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

		string dateTime = getDateTime();

        FILE *f = fopen("data/log2D.log", "a");

		if (f) {
			fprintf(f, "\n%s - %s",dateTime.c_str(),msg);
			fclose(f);
		}
    }

}


void debug_message_nl(const std::string fmt, ...)
{
	va_list ap;
    char msg[200];

	int flag = 1;

	if (flag > 0){
		va_start(ap, fmt);
		vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

		string dateTime = getDateTime();

        FILE *f = fopen("data/log2D.log", "a");


		if (f) {
			fprintf(f, "%s",msg);
			fclose(f);
		}
	}
}


void deleteLogFile(){

    int flag = 0;

    flag = remove("data/log2D.log");


	if (flag!=0){
		cout << "error al borrar fichero de logs";
	}
}

//SDL 2.0
////////////////////////////////////////////////////////////////////////////////////////////////////

int handleKeyPress(int flipflop){

    int flag = 0;
    int left = 0; int right = 0; int up = 0; int down = 0; int sel = 0; int esc = 0; int shot = 0; int pause = 0;
	globalD->setGlobalM(up,down,left,right,sel,esc,shot,pause);
    return flag;
}



int processGlobalWin32Event(){
    int flag = 0;
    return flag;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
