
/*
LOGENGINE.H MOTOR DE LOGS DE LA APLICACION
*/

#include "Stdafx.h"

#ifndef LOGMANAGER_H_INCLUDED
#define LOGMANAGER_H_INCLUDED

#define DEBUG_LOG 1
#define INFO_LOG 2
#define WARN_LOG 3
#define ERROR_LOG 4
#define FATAL_LOG 5
#define SIZE 300
#define SIZE_TIME 50

class LogEngine{

    public:

       LogEngine(){level = 0;} /*0=all, 1=debug, 2=info, 3=warn, 4=error, 5=fatal*/
       void startUp(int level);
       void shutDown();

       void debug(const std::string fmt, ...);
       void info(const std::string fmt, ...);
       void warn(const std::string fmt, ...);
       void error(const std::string fmt, ...);


    private:

       int level;
       void message(int type, const char *msg);
       void deleteLogFile();
       std::string getDateTime(void);

};

#endif // LOGMANAGER_H_INCLUDED

/*
(+)1.0.00
1-un thread
2-cuatro niveles de log.

(Pensar para futuras iteraciones)
1-Soporte para mas de un thread
2-inserción de logs por bloques en vez de por acción
*/
