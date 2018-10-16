#include <source.h>
#include <image.h>
#include <string.h>
#ifndef PNMREADER_H
#define PNMREADER_H
using namespace std;

class PNMreader : public source
{
	private:
		const char name[10] = "PNMreader";
		char* file;
	public:
		const char* SourceName() const {return name;};
		PNMreader(char *f);
		virtual ~PNMreader();
		virtual void Update() const;
		virtual void Execute() const;
};

#endif
