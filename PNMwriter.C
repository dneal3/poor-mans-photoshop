#include <PNMwriter.h>
#include <image.h>
#include <string.h>
#include <stdlib.h>
#include <printf.h>
#include <stdio.h>
#include <logging.h>

using namespace std;

void PNMwriter::Write(const char* filename)
{
	char msg[128];
	sprintf(msg, "%s: writing final image", SinkName());
	Logger::LogEvent(msg);
	FILE *f_out;
        f_out = fopen(filename, "w");
 	
	if (f_out == NULL)
	{
		cerr << "Unable to open file in write: " << filename << endl;
		exit(EXIT_FAILURE);
	}
	
	if (Input == NULL)
	{
		cerr << "Input for writer is NULL" << endl;
		exit(EXIT_FAILURE);
	}

        
        fprintf(f_out, "P6\n%d %d\n255\n", this->GetInput()->GetWidth(), Input->GetHeight()); 
        fwrite(Input->GetBinData(), sizeof(char), Input->GetWidth()*Input->GetHeight()*3, f_out);
        
        fclose(f_out);
	sprintf(msg, "%s:finished  writing final image", SinkName());
	Logger::LogEvent(msg);
}


