#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#pragma pack(push, 1)
struct Header
{
	unsigned char _signature[2];
	unsigned int _size;
	unsigned int _reserved;
	unsigned int _offset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DIB
{
	unsigned int _size;
	unsigned int _width;
	unsigned int _height;
	unsigned short int _planes;
	unsigned short int _bits_per_pixel;
	unsigned int _compression;
	unsigned int _image_size;
	unsigned int _x_pixels_per_m;
	unsigned int _y_pixels_per_m;
	unsigned int _colors_used;
	unsigned int _important_colors;
};
#pragma pack(pop)

// cấu trúc cho một file ảnh bmp
struct BMP
{
	Header _header;
	DIB _dib;
	unsigned char* _dib_reserved = NULL; // phần dữ liệu bổ sung của dib
	unsigned char* _pixels_data = NULL; // phần dữ liệu điểm ảnh
};

int readBMP(char* filename, BMP& bmp);
void printInfoBMPToScreen(BMP bmp);
int writeBMP(char* filename, BMP bmp);
int convertTo8Bits(BMP srcImg, BMP& dstImg);
int zoom(BMP srcImg, BMP& dstImg, int s);