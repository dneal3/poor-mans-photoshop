#ifndef SOURCE_H
#define SOURCE_H
#include <iostream>
#include <string>
class Image;
class source
{
	protected:
		mutable int TimesSeen = 0;
		Image *imgOut;
	public:
		source();
		virtual ~source();
		void SetOutput(Image* i) {imgOut = i; };
		Image* GetOutput(void) const { return imgOut; };	
		virtual void Update(void) const {};
		virtual void Execute() const = 0;
		virtual const char* SourceName() const = 0;
};

#endif
