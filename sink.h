#include <image.h>
#ifndef SINK_H
#define SINK_H
class sink
{
protected:	
	const Image* Input;
	const Image* Input2;
public:	
	sink();
	void SetInput(Image* img) { Input  = img; };
	void SetInput2(Image* img2) { Input2 = img2; };
	const Image* GetInput(void) const { return Input; };
	const Image* GetInput2(void) const { return Input2; };
	virtual const char* SinkName() const = 0;
};


#endif
