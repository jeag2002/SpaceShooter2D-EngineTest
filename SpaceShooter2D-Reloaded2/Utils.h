#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "Stdafx.h"
#include "Global.h"

#define TAMANO 100

string getDateTime(void);
void debug_message(const std::string fmt, ...);
void debug_message_nl(const std::string fmt, ...);
void deleteLogFile();

#endif // UTILS_H_INCLUDED
