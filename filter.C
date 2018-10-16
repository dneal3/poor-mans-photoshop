#include <filter.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <logging.h>


void filter::Update() const
{
	TimesSeen++;
	if(TimesSeen > 500) // this is a very poor way of doing this, but it works...
	{
		char msg[128];
		sprintf(msg, "%s: Potential Stack Overflow", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	char msg[128];
	sprintf(msg, "%s: about to update Input 1", this->FilterName());
	Logger::LogEvent(msg);
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	this->GetInput()->Update();
	sprintf(msg, "%s: Input1 updated", this->FilterName());
	
	Logger::LogEvent(msg);
	if (GetNumberOfInputs() == 2)
	{	
		if (Input2 == NULL)
		{
			char msg[128];
			sprintf(msg, "%s: Input 2 is NULL", FilterName());
			DataFlowException e(FilterName(), msg);
			throw e;
		}	
		sprintf(msg, "%s: about to update Input 2", this->FilterName());
		Logger::LogEvent(msg);
		this->GetInput2()->Update();
		sprintf(msg, "%s: Input2 updated", this->FilterName());
		Logger::LogEvent(msg);
	}
		sprintf(msg, "%s: about to execute", this->FilterName());
		Logger::LogEvent(msg);
	this->Execute();
	sprintf(msg, "%s: done executing", this->FilterName());
	Logger::LogEvent(msg);
	TimesSeen++;
}

Shrinker::Shrinker()
{
	this->GetOutput()->SetSource(this);
}

void Shrinker::Execute() const
{
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: NO INPUT", this->FilterName());
		DataFlowException e(this->FilterName(),msg);
		throw e;			
	}
        this->GetOutput()->SetWidth((this->GetInput()->GetWidth()/2));
        this->GetOutput()->SetHeight((this->GetInput()->GetHeight()/2));
        if (imgOut->GetBinData() == NULL)
	{
		this->GetOutput()->SetBinData(new unsigned char[3*this->GetOutput()->GetWidth()*this->GetOutput()->GetHeight()]);
		for(int c=0; c < this->GetOutput()->GetWidth(); c++)
        	{
                	for(int r = 0; r < this->GetOutput()->GetHeight(); r++)
                	{
                        	this->GetOutput()->GetBinData()[3*(r*this->GetOutput()->GetWidth()+c)+0] = this->GetInput()->GetBinData()[3*(r*this->GetInput()->GetWidth()+c)*2+0];
                        	this->GetOutput()->GetBinData()[3*(r*this->GetOutput()->GetWidth()+c)+1] = this->GetInput()->GetBinData()[3*(r*this->GetInput()->GetWidth()+c)*2+1];
                        	this->GetOutput()->GetBinData()[3*(r*this->GetOutput()->GetWidth()+c)+2] = this->GetInput()->GetBinData()[3*(r*this->GetInput()->GetWidth()+c)*2+2];
                	}
        	}
	}
}

LRCombine::LRCombine()
{
	this->GetOutput()->SetSource(this);
}

void LRCombine::Execute() const
{
	
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (Input2 == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 2 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (this->GetInput()->GetHeight() != this->GetInput2()->GetHeight())
	{
		char msg[128];
		sprintf(msg, "%s: heights must match: %d, %d",this->FilterName(), this->GetInput()->GetHeight(), this->GetInput2()->GetHeight());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
        this->GetOutput()->SetWidth(this->GetInput()->GetWidth() + this->GetInput2()->GetWidth());
        this->GetOutput()->SetHeight(this->GetInput()->GetHeight());
        if (imgOut->GetBinData() == NULL)
	{
        	this->GetOutput()->SetBinData(new unsigned char[3*this->GetOutput()->GetWidth()*this->GetOutput()->GetHeight()]);
        	for (int r = 0; r < this->GetOutput()->GetHeight(); r++)
        	{
                	memcpy(this->GetOutput()->GetBinData()+(3*(r*this->GetOutput()->GetWidth())), this->GetInput()->GetBinData()+(3*(r*this->GetInput()->GetWidth())), 3*this->GetInput()->GetWidth());
                	memcpy(this->GetOutput()->GetBinData()+(((3*(r*this->GetOutput()->GetWidth())) +(3*this->GetInput()->GetWidth()))), this->GetInput2()->GetBinData()+(3*(r*this->GetInput2()->GetWidth())), 3*this->GetInput2()->GetWidth());
        	}
	}
}

TBCombine::TBCombine()
{
	this->GetOutput()->SetSource(this);
}

void TBCombine::Execute() const
{
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (Input2 == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 2 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (Input->GetWidth() != Input2->GetWidth())
	{
		char msg[128];
		sprintf(msg,"%s: widths do not match, Input1: %d, Input2: %d",this->FilterName(), Input->GetWidth(), Input2->GetWidth());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	this->GetOutput()->SetWidth(this->GetInput()->GetWidth());
        this->GetOutput()->SetHeight(this->GetInput()->GetHeight() + this->GetInput2()->GetHeight());
       	if(imgOut->GetBinData() == NULL)
	{
        	this->GetOutput()->SetBinData(new unsigned char[3*this->GetOutput()->GetWidth()*this->GetOutput()->GetHeight()]);
		memcpy(this->GetOutput()->GetBinData(), this->GetInput()->GetBinData(), 3*(this->GetInput()->GetWidth()*this->GetInput()->GetHeight()));
        	memcpy(this->GetOutput()->GetBinData()+(3*(this->GetInput()->GetWidth()*this->GetInput()->GetHeight())) ,this->GetInput2()->GetBinData(), 3*(this->GetInput2()->GetWidth()*this->GetInput2()->GetHeight()));
	}
}

Blender::Blender()
{
	this->GetOutput()->SetSource(this);
}

void Blender::Execute() const
{
	if (this->factor > 1 || this->factor < 0 )
	{
		char msg[128];
		sprintf(msg, "%s :factor cant be greater than 1, it's: %e",this->FilterName(), this->factor);
	}
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (Input2 == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 2 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if ((Input->GetWidth() != Input2->GetWidth()) || (Input->GetHeight() != Input2->GetHeight()))
	{
		char msg[128];
		sprintf(msg, "%s: Heights or Widths do not match", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	this->GetOutput()->SetWidth(this->GetInput()->GetWidth());
        this->GetOutput()->SetHeight(this->GetInput()->GetHeight());
        if (imgOut->GetBinData() == NULL)
	{
        	this->GetOutput()->SetBinData(new unsigned char[3*this->GetInput()->GetWidth()*this->GetInput()->GetHeight()]);

        	for(int i=0; i<(this->GetOutput()->GetWidth()*this->GetOutput()->GetHeight()); i++)
        	{
                	this->GetOutput()->GetBinData()[3*i] = (this->GetInput()->GetBinData()[3*i]*this->factor + this->GetInput2()->GetBinData()[3*i]*(1-this->factor));
			this->GetOutput()->GetBinData()[3*i+1] = (this->GetInput()->GetBinData()[3*i+1]*this->factor + this->GetInput2()->GetBinData()[3*i+1]*(1-this->factor));
			this->GetOutput()->GetBinData()[3*i+2] = (this->GetInput()->GetBinData()[3*i+2]*this->factor + this->GetInput2()->GetBinData()[3*i+2]*(1-this->factor));        
		}
	}	
}

Mirror::Mirror()
{
	this->GetOutput()->SetSource(this);
}
/*
 * I ACCIDENTALLY CREATED A FLIP FUNCTION I'M KEEPING IT BECAUSE I THINK IT'S FUNNY
void 2xRotate::Execute() const
{
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	this->GetOutput()->SetWidth(this->GetInput()->GetWidth());
	this->GetOutput()->SetHeight(this->GetInput()->GetHeight());
        if (imgOut->GetBinData() == NULL)
	{
		this->GetOutput()->SetBinData(new unsigned char[3*this->GetInput()->GetWidth()*this->GetInput()->GetHeight()]);
		for(int i=0; i<this->GetOutput()->GetWidth()*this->GetOutput()->GetHeight(); i++)
		{
			this->GetOutput()->GetBinData()[3*i+0] = this->GetInput()->GetBinData()[3*(this->GetInput()->GetWidth()*this->GetOutput()->GetHeight()-i)+0];
			this->GetOutput()->GetBinData()[3*i+1] = this->GetInput()->GetBinData()[3*(this->GetInput()->GetWidth()*this->GetOutput()->GetHeight()-i)+1];
			this->GetOutput()->GetBinData()[3*i+2] = this->GetInput()->GetBinData()[3*(this->GetInput()->GetWidth()*this->GetOutput()->GetHeight()-i)+2];
		}
	}	
}
*/

void Mirror::Execute() const
{
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	this->GetOutput()->SetWidth(this->GetInput()->GetWidth());
	this->GetOutput()->SetHeight(this->GetInput()->GetHeight());
        if (imgOut->GetBinData() == NULL)
	{
		this->GetOutput()->SetBinData(new unsigned char[3*this->GetInput()->GetWidth()*this->GetInput()->GetHeight()]);
		for(int r=0;r<this->GetOutput()->GetHeight();r++)
		{
			for(int i=0; i<this->GetOutput()->GetWidth(); i++)
			{
				this->GetOutput()->GetBinData()[3*i+0+((3*this->GetOutput()->GetWidth())*r)] = this->GetInput()->GetBinData()[3*(this->GetInput()->GetWidth()-i-1)+((3*this->GetOutput()->GetWidth())*r)+0];
				this->GetOutput()->GetBinData()[3*i+1+((3*this->GetOutput()->GetWidth())*r)] = this->GetInput()->GetBinData()[3*(this->GetInput()->GetWidth()-i-1)+((3*this->GetOutput()->GetWidth())*r)+1];
				this->GetOutput()->GetBinData()[3*i+2+((3*this->GetOutput()->GetWidth())*r)] = this->GetInput()->GetBinData()[3*(this->GetInput()->GetWidth()-i-1)+((3*this->GetOutput()->GetWidth())*r)+2];
			}
		}
	}
}

Rotate::Rotate()
{
	this->GetOutput()->SetSource(this);
}

void Rotate::Execute() const
{
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	this->GetOutput()->SetWidth(this->GetInput()->GetHeight());
	this->GetOutput()->SetHeight(this->GetInput()->GetWidth());
        if (imgOut->GetBinData() == NULL)
	{
		this->GetOutput()->SetBinData(new unsigned char[3*this->GetInput()->GetWidth()*this->GetInput()->GetHeight()]);
	
		for(int i=0;i<this->GetOutput()->GetHeight();i++)
		{
			for(int r=0; r<this->GetOutput()->GetWidth(); r++)
			{
				this->GetOutput()->GetBinData()[3*r+(3*(imgOut->GetWidth()*i))+0] = this->GetInput()->GetBinData()[(3*i)+3*(Input->GetWidth()*(Input->GetHeight()-1-r))+0]; 
				this->GetOutput()->GetBinData()[3*r+(3*(imgOut->GetWidth()*i))+1] = this->GetInput()->GetBinData()[(3*i)+3*(Input->GetWidth()*(Input->GetHeight()-1-r))+1]; 
				this->GetOutput()->GetBinData()[3*r+(3*(imgOut->GetWidth()*i))+2] = this->GetInput()->GetBinData()[(3*i)+3*(Input->GetWidth()*(Input->GetHeight()-1-r))+2]; 
			}
		}
	}
}

Subtract::Subtract()
{
	this->GetOutput()->SetSource(this);
}

void Subtract::Execute() const
{
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (Input2 == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 2 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (Input->GetWidth() != Input2->GetWidth())
	{
		char msg[128];
		sprintf(msg,"%s: widths do not match, Input1: %d, Input2: %d",this->FilterName(), Input->GetWidth(), Input2->GetWidth());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	if (this->GetInput()->GetHeight() != this->GetInput2()->GetHeight())
	{
		char msg[128];
		sprintf(msg, "%s: heights must match: %d, %d",this->FilterName(), this->GetInput()->GetHeight(), this->GetInput2()->GetHeight());
		DataFlowException e(FilterName(), msg);
		throw e;
	}
	this->imgOut->SetHeight(Input->GetHeight());
	this->imgOut->SetWidth(Input->GetWidth());
        if (imgOut->GetBinData() == NULL)
	{
		this->imgOut->SetBinData(new unsigned char[3*imgOut->GetWidth()*imgOut->GetHeight()]);
	
        	for(int i=0; i<(this->GetOutput()->GetWidth()*this->GetOutput()->GetHeight()); i++)
        	{
			if (Input->GetBinData()[3*i] > Input2->GetBinData()[3*i])
			{
                		this->GetOutput()->GetBinData()[3*i] = (this->GetInput()->GetBinData()[3*i] - this->GetInput2()->GetBinData()[3*i]);
			}
			else { imgOut->GetBinData()[3*i] = 0;}

			if (Input->GetBinData()[3*i+1] > Input2->GetBinData()[3*i+1])
			{
				this->GetOutput()->GetBinData()[3*i+1] = (this->GetInput()->GetBinData()[3*i+1] - this->GetInput2()->GetBinData()[3*i+1]);
			}
			else { imgOut->GetBinData()[3*i+1] = 0;}
		
			if (Input->GetBinData()[3*i+2] > Input2->GetBinData()[3*i+2])
			{
				this->GetOutput()->GetBinData()[3*i+2] = (this->GetInput()->GetBinData()[3*i+2] - this->GetInput2()->GetBinData()[3*i+2]);        
			}
			else { imgOut->GetBinData()[3*i+2] = 0;}
		}
	}
}
Grayscale::Grayscale()
{
	this->GetOutput()->SetSource(this);
}

void Grayscale::Execute() const
{
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}

	this->imgOut->SetHeight(Input->GetHeight());
	this->imgOut->SetWidth(Input->GetWidth());
        if (imgOut->GetBinData() == NULL)
	{
		this->imgOut->SetBinData(new unsigned char[3*imgOut->GetWidth()*imgOut->GetHeight()]);

        	for(int i=0; i<(imgOut->GetWidth()*imgOut->GetHeight()); i++)
        	{
                	this->GetOutput()->GetBinData()[3*i] = (Input->GetBinData()[3*i]/5)+(Input->GetBinData()[3*i+1]/2)+(Input->GetBinData()[3*i+2]/4);
			this->GetOutput()->GetBinData()[3*i+1] = (Input->GetBinData()[3*i]/5)+(Input->GetBinData()[3*i+1]/2)+(Input->GetBinData()[3*i+2]/4);
			this->GetOutput()->GetBinData()[3*i+2] = (Input->GetBinData()[3*i]/5)+(Input->GetBinData()[3*i+1]/2)+(Input->GetBinData()[3*i+2]/4);        
		}
	}
}

Blur::Blur()
{
	this->GetOutput()->SetSource(this);
}

void Blur::Execute() const
{

	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg, "%s: Input 1 is NULL", FilterName());
		DataFlowException e(FilterName(), msg);
		throw e;
	}

	this->imgOut->SetHeight(Input->GetHeight());
	this->imgOut->SetWidth(Input->GetWidth());
        if (imgOut->GetBinData() == NULL)
	{
		this->imgOut->SetBinData(new unsigned char[3*imgOut->GetWidth()*imgOut->GetHeight()]);
		memcpy(imgOut->GetBinData(), Input->GetBinData(), 3*(Input->GetHeight()*Input->GetWidth()));

		for(int i=1;i<this->GetOutput()->GetHeight()-1;i++)
		{
			for(int r=1; r<this->GetOutput()->GetWidth()-1; r++)
			{
				this->GetOutput()->GetBinData()[(3*r)+(3*(imgOut->GetWidth()*i))+0] = 
					((Input->GetBinData()[(3*(r-1))+(3*(Input->GetWidth()*(i-1)))]/8)+
					(Input->GetBinData()[(3*(r))+(3*(Input->GetWidth()*(i-1)))]/8)+
					(Input->GetBinData()[(3*(r+1))+(3*(Input->GetWidth()*(i-1)))]/8)+
					(Input->GetBinData()[(3*(r-1))+(3*(Input->GetWidth()*(i)))]/8)+
					(Input->GetBinData()[(3*(r+1))+(3*(Input->GetWidth()*(i)))]/8)+
					(Input->GetBinData()[(3*(r-1))+(3*(Input->GetWidth()*(i+1)))]/8)+
					(Input->GetBinData()[(3*(r))+(3*(Input->GetWidth()*(i+1)))]/8)+
					(Input->GetBinData()[(3*(r+1))+(3*(Input->GetWidth()*(i+1)))]/8));

				this->GetOutput()->GetBinData()[((3*r)+(3*(imgOut->GetWidth()*i)))+1] = 
					((Input->GetBinData()[(3*(r-1))+(3*(Input->GetWidth()*(i-1)))+1]/8)+
					(Input->GetBinData()[((3*(r))+(3*(Input->GetWidth()*(i-1))))+1]/8)+
					(Input->GetBinData()[((3*(r+1))+(3*(Input->GetWidth()*(i-1))))+1]/8)+
					(Input->GetBinData()[((3*(r-1))+(3*(Input->GetWidth()*(i))))+1]/8)+
					(Input->GetBinData()[((3*(r+1))+(3*(Input->GetWidth()*(i))))+1]/8)+
					(Input->GetBinData()[((3*(r-1))+(3*(Input->GetWidth()*(i+1))))+1]/8)+
					(Input->GetBinData()[((3*(r))+(3*(Input->GetWidth()*(i+1))))+1]/8)+
					(Input->GetBinData()[((3*(r+1))+(3*(Input->GetWidth()*(i+1))))+1]/8));

				this->GetOutput()->GetBinData()[((3*r)+(3*(imgOut->GetWidth()*i)))+2] = 
					((Input->GetBinData()[((3*(r-1))+(3*(Input->GetWidth()*(i-1))))+2]/8)+
					(Input->GetBinData()[((3*(r))+(3*(Input->GetWidth()*(i-1))))+2]/8)+
					(Input->GetBinData()[((3*(r+1))+(3*(Input->GetWidth()*(i-1))))+2]/8)+
					(Input->GetBinData()[((3*(r-1))+(3*(Input->GetWidth()*(i))))+2]/8)+
					(Input->GetBinData()[((3*(r+1))+(3*(Input->GetWidth()*(i))))+2]/8)+
					(Input->GetBinData()[((3*(r-1))+(3*(Input->GetWidth()*(i+1))))+2]/8)+
					(Input->GetBinData()[((3*(r))+(3*(Input->GetWidth()*(i+1))))+2]/8)+
					(Input->GetBinData()[((3*(r+1))+(3*(Input->GetWidth()*(i+1))))+2]/8)); 
			}
		}
	}
}

Color::Color(int w, int h, int r, int g, int b)
{
	this->GetOutput()->SetSource(this);
	width = w;
	height = h;
	red = r;
	green = g;
	blue = b;
}

void Color::Execute() const
{
	
	if ((width || height || red || green || blue) < 0)
	{
		char msg[128];
		sprintf(msg,"%s: Negative values for Constant Color Constructor are not allowed.",SourceName());
		DataFlowException e(SourceName(), msg);
		throw e;
	}
	
	if ((red || green || blue) > 255)
	{
		char msg[128];
		sprintf(msg,"%s: RGB values cannot exceed 255.", SourceName());
		DataFlowException e(SourceName(), msg);
		throw e;
	}

	this->imgOut->SetHeight(height);
	this->imgOut->SetWidth(width);
        if (imgOut->GetBinData() == NULL)
	{
		this->imgOut->SetBinData(new unsigned char[3*width*height]);

        	for(int i=0; i<(width*height); i++)
        	{
                	this->GetOutput()->GetBinData()[3*i] = red;
			this->GetOutput()->GetBinData()[3*i+1] = green;
			this->GetOutput()->GetBinData()[3*i+2] = blue;        
		}
	}
}

void Color::Update() const
{
	Execute();
}

void CheckSum::OutputCheckSum(const char* filename)
{
        char msg[128];
        sprintf(msg, "%s: writing CheckSum", SinkName());
        Logger::LogEvent(msg);
        FILE *f_out;
        f_out = fopen(filename, "w");

        if (f_out == NULL)
        {
		char msg[128];
		sprintf(msg,"%s: Output file could not be opened file pointer is NULL.",SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
        }
	if (Input == NULL)
	{
		char msg[128];
		sprintf(msg,"%s: Input1 is NULL",SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
        }
	unsigned int redSum = 0;
	unsigned int greenSum = 0;
	unsigned int blueSum = 0;
	for(int i=0; i<(Input->GetWidth()*Input->GetHeight()); i++)
	{
		redSum = redSum + Input->GetBinData()[3*i];
		greenSum = greenSum + Input->GetBinData()[3*i+1];
		blueSum = blueSum + Input->GetBinData()[3*i+2];
	}

        fprintf(f_out, "CHECKSUM: %d, %d, %d\n", redSum%256, greenSum%256, blueSum%256);
	fclose(f_out);
	sprintf(msg, "%s:finished writing CheckSum", SinkName());
	Logger::LogEvent(msg);
}
