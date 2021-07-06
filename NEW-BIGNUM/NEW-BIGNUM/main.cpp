#include "Header.h"

int main(int argc, char* argv[])
{
    // nếu số lượng tham số được truyền vào bằng 5 thì sẽ xem xét tới lệnh cần thực hiện
    if (argc == 5)
    {
        // lưu số K từ tham số thứ 2 thành kiểu số nguyên
        int K = atoi(argv[2]);
        // nếu lệnh cần thực hiện là -comp thì thực hiện hàm comp
        if (strcmp(argv[1], "-comp") == 0)
        {
            cout << "Dang thuc hien chuc nang tinh bieu thuc cong tru so nguyen lon." << endl;
            comp(K, argv[3], argv[4]);
        }
        // nếu lệnh cần thực hiện là -qsort thf thực hiện hàm sort và truyền vào tham số quickSort vào tham số đầu tiên
        else if (strcmp(argv[1], "-qsort") == 0)
        {
            cout << "Dang thuc hien chuc nang sap xep bang thuat toan quick sort." << endl;
            sort(quickSort, K, argv[3], argv[4]);
        }
        // nếu lệnh cần thực hiện là -msort thf thực hiện hàm sort và truyền vào tham số mergeSort vào tham số đầu tiên
        else if (strcmp(argv[1], "-msort") == 0)
        {
            cout << "Dang thuc hien chuc nang sap xep bang thuat toan merge sort." << endl;
            sort(mergeSort, K, argv[3], argv[4]);
        }
        // nếu đối chiếu khong có lệnh nào phù hợp thì thoát chướng trình
        else
            cout << "Lenh khong ton tai." << endl;
        return 1;
    }
    // nếu số lượng tham số khác 5 thì thoát chương trình
    cout << "Lenh khong ton tai." << endl;
	return 0;
}