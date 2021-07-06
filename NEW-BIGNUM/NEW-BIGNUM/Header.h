#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>	
using namespace std;


typedef struct Node* ptrNode;
struct Node
{
	// 
	string data;
	ptrNode pNext = NULL;
};

struct BIGNUM
{
	// số lượng chữ số
	int soLuongChuSo = 0;
	// nếu isReverse = 0 khi số lưu vào là không bị đảo, 1 khi số lưu vào bị đảo ngược
	int biNguocDao = 0;
	ptrNode pHead = NULL;
	ptrNode pTail = NULL;
};

// chèn một node p vào cuối dslk bignum
void chenVaoDuoiBigNum(BIGNUM& bignum, ptrNode p);

// hàm chuyển từ một xâu str thành một số BIGNUM vào dslk theo tỉ lệ K
void chuyenTuStringSangBigNum(BIGNUM& bignum, string str, int K, int isReverse);

// hàm xóa một BIGNUM
void xoaBigNum(BIGNUM& bignum);
// hàm cộng hai số nguyên lớn a và b và lưu kết quả vào result
void congHaiSo(BIGNUM& result, BIGNUM& a, BIGNUM& b, int K);
// hàm trừ hai số nguyên lớn a và b và lưu kết quả vào biến result
// có khả năng sẽ trả về giá trị cho hàm này vd như -1, 0, 1;
int truHaiSo(BIGNUM& result, BIGNUM& a, BIGNUM& b, int K);
// so sánh hai số a và b
int soSanhHaiSo(BIGNUM &a, BIGNUM &b, int K);
void daoNguocSo(BIGNUM& a, int K);
void chenMotSoVaoMang(BIGNUM*& list, int& n, string str, int K);

// hàm thực hiện tham số dòng lệnh với lệnh -comp
void comp(int K, char* inputPath, char* outputPath);

// hàm xắp xếp một mảng các số bằng thuật toán quicksort
int partition(BIGNUM*& a, int K, int l, int r);
void quickSort(BIGNUM*& a, int K, int l, int r);

// hàm xắp xếp một mảng các số bằng thuật toán merge sort
void merge(BIGNUM*& a, int K, int l, int r, int mid);
void mergeSort(BIGNUM*& a, int K, int l, int r);

// hàm thực hiện tham số dòng lệnh với lệnh -qsort và -msort
void sort(void (*thuatToanSapXep)(BIGNUM*&, int, int, int), int K, char* duongDanFileInput, char* duongDanFileOutput);