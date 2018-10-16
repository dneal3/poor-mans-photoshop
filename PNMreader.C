#include <PNMreader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include <logging.h>

PNMreader::PNMreader(char *fname)
{
	this->GetOutput()->SetSource(this);
	file = new char[strlen(fname)+1];
	strcpy(file, fname);
}

PNMreader::~PNMreader()
{
	delete [] file;
}

void PNMreader::Update() const
{
	char msg[128];
	sprintf(msg, "%s: about to execute", name);
	Logger::LogEvent(msg);
	this->Execute();
	sprintf(msg, "%s: done executing", name);
	Logger::LogEvent(msg);
}
void PNMreader::Execute() const
{       
        FILE *f_in;
        int w, h, maxval;
        unsigned char magicNum[8];
        f_in = fopen(file, "r");
        if (f_in == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: unable to open file for reading", SourceName());
		DataFlowException e(SourceName(), msg);
		throw e;
	}
        fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &w, &h, &maxval);
        
        this->GetOutput()->SetWidth(w);
        this->GetOutput()->SetHeight(h);
        if (imgOut->GetBinData() == NULL)
	{
        	this->GetOutput()->SetBinData(new unsigned char[w*this->GetOutput()->GetHeight()*3]);
        	fread(this->GetOutput()->GetBinData(), sizeof(char), this->GetOutput()->GetWidth()*this->GetOutput()->GetHeight()*3, f_in);
	}
        fclose(f_in);
}
