#include "LogEngine.h"

inline string tagLevel(int level){

    string data;

    switch(level){
        case 1: data = "[DEBUG] "; break;
        case 2: data = "[INFO]  "; break;
        case 3: data = "[WARN]  "; break;
        case 4: data = "[ERROR] "; break;
        default:
                data = "[IDLE]  "; break;
    }

    return data;
}

void LogEngine::startUp(int level){
    this->level = level;
    deleteLogFile();
    this->info("LogEngine - INITIALIZED! to %s",tagLevel(level).c_str());
}


void LogEngine::shutDown(){

}

void LogEngine::deleteLogFile(){

    int flag = 0;
    flag = remove("./data/Sin2DEng.log");

	if (flag!=0){
		cout << "error al borrar fichero de logs";
	}
}


string LogEngine::getDateTime(void){

  char buffer[SIZE_TIME];
  string output;
  time_t curtime;
  struct tm *loctime;

  curtime = time (NULL);
  loctime = localtime (&curtime);

  strftime (buffer, SIZE, "(%d/%m/%Y - %H:%M:%S) - ", loctime);

  output = buffer;

  return output;
}

void LogEngine::message(int type, const char *msg)
{
    string dateTime = getDateTime();
    FILE *f = fopen("data/Sin2DEng.log", "a");

    if (f) {
        fprintf(f, "\n%s%s - %s",tagLevel(type).c_str(), dateTime.c_str(),msg);
        fclose(f);
    }
}


void LogEngine::debug(const std::string fmt, ...){
    if (this->level <= DEBUG_LOG){

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        message(DEBUG_LOG, msg);
    }
}


void LogEngine::info(const std::string fmt, ...){
    if (this->level <= INFO_LOG){

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        message(INFO_LOG, msg);


    }
}


void LogEngine::warn(const std::string fmt, ...){
    if (this->level <= WARN_LOG){

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        message(WARN_LOG, msg);

    }
}


void LogEngine::error(const std::string fmt, ...){
    if (this->level <= ERROR_LOG){

        va_list ap;
        char msg[SIZE];

        va_start(ap, fmt);
        vsnprintf(msg, (sizeof(msg)/sizeof(*msg))-1, fmt.c_str(), ap);

        message(ERROR_LOG, msg);

    }
}
