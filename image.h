#ifndef IMAGE_H
#define IMAGE_H
#include <source.h>
class Image
{ 
	int width;
	int height;
	unsigned char *bin_data;
	const source* ImgSource;
public:	
	Image();
	virtual ~Image();
	Image(int width, int height);
	Image(Image &);
	void ResetSize(int width, int height);
	int GetWidth() const { return width; };
	int GetHeight() const { return height; };
	const source* GetSource(void) const { return ImgSource; };
	void SetWidth(int w) { width = w; };
	void SetHeight(int h) { height = h; };
	void SetSource(source* s) {ImgSource = s; };
	unsigned char* GetBinData() const { return bin_data; };  
	void SetBinData(unsigned char* b) { bin_data = b;};
        virtual void Update() const;
	
};

#endif
