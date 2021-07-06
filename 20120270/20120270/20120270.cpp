#include "Libs.h"

int main(int argc, char* argv[])
{
	BMP srcImg;
	BMP dstImg;
	if (argc == 4 && strcmp(argv[1], "-conv") == 0)
	{
		int check_read = readBMP(argv[2], srcImg);
		if (check_read == 0)
		{
			cout << endl << "Doc file khong thanh cong.";
			return 1;
		}
		cout << "Thong tin cua anh can chuyen thanh 8 bits." << endl;
		printInfoBMPToScreen(srcImg);
		int check_conv = convertTo8Bits(srcImg, dstImg);
		if (check_conv == 0)
		{
			cout << endl << "Chuyen anh thanh 8 bits khong thanh cong." << endl;
			return 1;
		}
		cout << endl << "Thong tin cua anh 8 bits moi." << endl;
		printInfoBMPToScreen(dstImg);
		int check_write = writeBMP(argv[3], dstImg);
		if (check_write == 0)
		{
			cout << endl << "Ghi anh 8 bits khong thanh cong, loi tao file output" << endl;
			return 1;
		}
		cout << endl << "Chuyen anh thanh 8 bits thanh cong." << endl;
		return 0;
	}
	else if (argc == 5 && strcmp(argv[1], "-zoom") == 0)
	{
		// chuyển tham số thứ 5 của dòng lệnh thành kiểu nguyên
		int s = atoi(argv[4]);
		int check_read = readBMP(argv[2], srcImg);
		if (check_read == 0)
		{
			cout << endl << "Doc file khong thanh cong.";
			return 1;
		}
		cout << "Thong tin cua anh can chuyen thanh zoom." << endl;
		printInfoBMPToScreen(srcImg);
		int check_zoom = zoom(srcImg, dstImg, s);
		if (check_zoom == 0)
		{
			cout << "Thu nho anh khong thanh cong." << endl;
			return 1;
		}
		cout << endl << "Thong tin cua anh thu nho moi." << endl;
		printInfoBMPToScreen(dstImg);
		int check_write = writeBMP(argv[3], dstImg);
		if (check_write == 0)
		{
			cout << endl << "Ghi anh thu nho khong thanh cong, loi tao file output" << endl;
			return 1;
		}
		cout << endl << "Thu nho anh thanh cong." << endl;
		return 0;
	}
	else
		cout << "Tham so dong lenh khong hop le." << endl;
	return 0;
}