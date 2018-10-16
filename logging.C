#include <logging.h>
#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>
#include <printf.h>


DataFlowException::DataFlowException(const char *type, const char *error)
{
	strcpy(msg, "Throwing Exception For (");
	strcat(msg, type);
	strcat(msg, "): ");
	strcat(msg, error);
	Logger::LogEvent(msg);
}

FILE* Logger::logger = fopen("logger","w");

void
Logger::LogEvent(const char *event)
{
	fprintf(logger,"%s\n", event);
}

void 
Logger::Finalize()
{
	fclose(logger);
}
