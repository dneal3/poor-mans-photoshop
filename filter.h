#include <image.h>
#include <sink.h>
#include <source.h>
#ifndef FILTER_H
#define FILTER_H
class filter: public sink, public source
{
	public:
		virtual void Update() const;
		virtual const char* FilterName() const = 0;
		const char* SourceName() const {return FilterName();};
		const char* SinkName() const {return FilterName();};
		virtual int GetNumberOfInputs() const = 0;

};

class Shrinker: public filter 
{
		const char name[9] = "Shrinker";
	public:
		virtual int GetNumberOfInputs() const {return 1;};
		const char* FilterName() const {return name;};
		Shrinker();
		virtual void Execute() const;
		
};

class LRCombine: public filter
{
		const char name[10] = "LRCombine";
	public:
		virtual int GetNumberOfInputs() const {return 2;};
		const char* FilterName() const {return name;};
		LRCombine();
		virtual void Execute() const;
};

class TBCombine: public filter
{
		const char name[10] = "TBCombine";
	public:
		virtual int GetNumberOfInputs() const {return 2;};
		const char* FilterName() const {return name;};
		TBCombine();
		virtual void Execute() const;
};

class Blender: public filter
{
	private:
		const char name[8] = "Blender";
		double factor;
	public:
		virtual int GetNumberOfInputs() const {return 2;};
		const char* FilterName() const {return name;};
		Blender();
		virtual void Execute() const;
		void SetFactor(double f) { this->factor = f; };
		double GetFactor(void) { return factor; };
};

class Mirror: public filter
{
	const char name[7] = "Mirror";
	public:
		Mirror();
		const char* FilterName() const {return name;};
		virtual int GetNumberOfInputs() const {return 1;};
		virtual void Execute() const;

};

class Rotate: public filter
{	
	const char name[7] = "Rotate";
	public:
		Rotate();
		const char* FilterName() const {return name;};
		virtual int GetNumberOfInputs() const {return 1;};
		virtual void Execute() const;
	
};

class Subtract: public filter
{
	
	const char name[9] = "Subtract";
	public:
		Subtract();
		const char* FilterName() const {return name;};
		virtual int GetNumberOfInputs() const {return 2;};
		virtual void Execute() const;
};

class Grayscale: public filter
{
	
	const char name[10] = "Grayscale";
	public:
		Grayscale();
		const char* FilterName() const {return name;};
		virtual int GetNumberOfInputs() const {return 1;};
		virtual void Execute() const;
};

class Blur: public filter
{
	
	const char name[5] = "Blur";
	public:
		Blur();
		const char* FilterName() const {return name;};
		virtual int GetNumberOfInputs() const {return 1;};
		virtual void Execute() const;
};

class Color: public source
{
	int height = -1;
	int width = -1;
	int red = -1;
	int green = -1;
	int blue = -1;
	const char name[6] = "Color";
	public:
		Color();
		Color(int w, int h, int r, int g, int b);
		const char* SourceName() const {return name;};
		virtual void Execute() const;
		virtual void Update() const;
};

class CheckSum: public sink
{
	
	const char name[9] = "CheckSum";
	public:
		const char* SinkName() const {return name;};
		virtual void OutputCheckSum(const char* f);


};
#endif
