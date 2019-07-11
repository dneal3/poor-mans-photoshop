# Poor Man's Photoshop
>A Project that created a C++ program that manipulates PNM images, dubbed as the poor mans photoshop. 

# File Structure
>This project uses a makefile which was created for the express purpose of being used with these specific files. The files are split into a header file which contains definitions of function as well as a few short functions. Otherwise the body of each function is located inside of the corresponding .c file.

# Project Flow
>In this project a PNM image is taken in through the PNM reader class and then translated into binary data which can then be manipulated by the filters that are descibed in the filter.c file. Once this data is manipulated by the filters it is written back into the PNM structures using the PNM writer class. As a note installing the software for pnm to png conversion is highly recommended as PNM files are not always easily viewable whereas PNG files are widely supported.

# Project Highlights
> This project is memory leak free!
> All files are structured to be object oriented! 
