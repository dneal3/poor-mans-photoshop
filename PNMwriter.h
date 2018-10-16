#include <sink.h>
#include <image.h>
#ifndef PNMWRITER_H
#define PNMWRITER_H

class PNMwriter: public sink 
{
		const char name[10] = "PNMwriter";
	public:
		const char* SinkName() const {return name;};
		virtual void Write(const char* f);
};

#endif
