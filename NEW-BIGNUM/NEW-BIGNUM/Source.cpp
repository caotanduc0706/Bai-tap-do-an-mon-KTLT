#include "Header.h"

// hàm chèn một node vào cuối dslk BIGNUM
void chenVaoDuoiBigNum(BIGNUM& bignum, ptrNode p)
{
    // nếu bignum chưa có bất kỳ node nào
	if (bignum.pHead == NULL && bignum.pTail == NULL)
		bignum.pHead = bignum.pTail = p;
	else
	{
        // nếu bignum đã có ít nhất một node
		bignum.pTail->pNext = p;
		bignum.pTail = p;
	}
}

// xóa một bignum
void xoaBigNum(BIGNUM& bignum)
{
    // nếu bignum khong có node nào thì không xóa
    if (bignum.pHead == NULL && bignum.pTail == NULL)
        return;
    // xét từ node đầu xóa tới node cuối
    while (bignum.pHead)
    {
        // gán con p bằng node pHead của bignum
        ptrNode p = bignum.pHead;
        // dịch chuyển con trỏ pHead sang node tiếp theo
        bignum.pHead = bignum.pHead->pNext;
        // xóa p
        delete p;
    }
    // sau cùng gán con tro pHead và pTail về NULL
    bignum.pHead = bignum.pTail = NULL;
}

// chuyển từ một xâu
void chuyenTuStringSangBigNum(BIGNUM& bignum, string str, int K, int biDao)
{
    // nếu bignum đã tồn tại thì xóa bignum
    xoaBigNum(bignum);
    bignum.soLuongChuSo = str.size();
    // số lượng các node của bignum
    int soLuongNode = (int)str.size() / K;
    // nếu số lượng chữ số của số cần chuyển đổi không chia hết cho K thì số lượng Node sẽ cộng thêm 1
    if ((int)str.size() % K != 0)
        soLuongNode += 1;
    
    // duyệt từng node
    for (int i = 0; i < soLuongNode; i++)
    {
        string phanTuTrongMotNode = "";
        // xét một lượt tới K phần tử, cho đến khi số lượng phần tử còn lại = 0 hoặc một số nhỏ hơn K
        for (int j = i * K; j < (i + 1) * K && j != str.size(); j++)
        {
            phanTuTrongMotNode += str[j];
        }
        // tạo một node mới lưu phần dữ liệu vừa ghi được
        ptrNode p = new Node;
        p->data = phanTuTrongMotNode;
        // chèn node p vào cuối bignum
        chenVaoDuoiBigNum(bignum, p);
    }
    bignum.biNguocDao = biDao;
}

// đảo ngược bignum;
void daoNguocSo(BIGNUM& bignum, int K)
{
    // nếu mà bignum đã lưu chỉ chứa một node duy nhất thì đảo ngược các phần tử đã có trong node đó
    if (bignum.pHead == bignum.pTail)
    {
        reverse(bignum.pHead->data.begin(), bignum.pHead->data.end());
    }
    else
    {
        ptrNode nodeHienTai = bignum.pHead;
        ptrNode nodePhiaTruoc = NULL;
        ptrNode nodePhiaSau = NULL;

        while (nodeHienTai != NULL) {
            // lưu lại node phía sau node đảo ngược 
            nodePhiaSau = nodeHienTai->pNext;
            // gán lại node phía sau của con trỏ hiện tại
            // Reverse current node's pointer 
            nodeHienTai->pNext = nodePhiaTruoc;
            // dời một node lên phía trước
            // Move pointers one position ahead. 
            nodePhiaTruoc = nodeHienTai;
            nodeHienTai = nodePhiaSau;
        }
        // node phía trước hiện tại là node cuối cùng
        bignum.pHead = nodePhiaTruoc;

        // lần lượt đảo phần dữ liệu bên trong mỗi node
        // vd: 12->34 rồi thành 34->12 rồi thành 43->21
        for (ptrNode p = bignum.pHead; p; p = p->pNext)
            reverse(p->data.begin(), p->data.end());
        // trường hợp node cuối cùng không đủ K phần tử thì phải dời tuần tự
        // các phần tử đầu của node tiếp theo vào node hiện tại
        ptrNode p = bignum.pHead;
        while (p != NULL && p->pNext != NULL && p->data.size() < K)
        {
            // số phần tử cần thêm vào mỗi node là số phần tử còn thiếu để làm node đó có đủ K phần tử
            int n = K - p->data.size();
            for (int i = 0; i < n; i++)
            {
                // thêm vào cuối phần dữ liệu của node hiện tại bằng phần tử đầu tiên của phần dữ liệu node tiếp theo
                p->data += p->pNext->data[0];
                // xóa phần tử đầu tiên của phần dữ liệu của node tiếp theo
                p->pNext->data.erase(p->pNext->data.begin());
            }
            p = p->pNext;
        }
    }
    // gán lại giá trị thành phần
    // nếu số hiện tại chưa là đảo ngược sẽ là đảo ngược 1->0
    // nếu số hiện tại được lưu vào là số đã bị đảo ngược thì sao khi hàm daoNguocSo() thì sẽ không còn bị đảo 0->1
    if (bignum.biNguocDao == 1)
        bignum.biNguocDao = 0;
    else
        bignum.biNguocDao = 1;
}

// để thực hiện cộng, thì các số được lưu trữ phải được lưu ngược vd số 1234 thì dslk sẽ lưu 4->3->2->1 ứng với K = 1
void congHaiSo(BIGNUM& ketQua, BIGNUM& a, BIGNUM& b, int K)
{
    // nếu các số đem đi cộng chưa được lưu dưới dạng đảo ngược thì phải đảo ngược lại
    if (a.biNguocDao == 0)
    {
        daoNguocSo(a, K);
    }
    if (b.biNguocDao == 0)
    {
        daoNguocSo(b, K);
    }

    // con trỏ pa duyệt từng node của BIGNUM a
    // con trỏ pb duyệt từng node của BIGNUM b
    ptrNode pa = a.pHead;
    ptrNode pb = b.pHead;
    string xauKetQua = "";
    // kết quả của phép cộng từng số
    // phần nguyên khi chi cho 10 của phép cộng
    // cộng với nguyên tắc lấy phần dư, nhớ phần nguyên
    int phanDuSo = 0;
    int phanNguyenSo = 0;
    while (pa && pb)
    {
        // chiều dài của xâu trong một node
        int la = pa->data.size();
        int lb = pb->data.size();
        // con chạy trên từng phần tử của xâu pa->data và pb->data, lần lượt là i
        int i = 0;
        
        while (i < la && i < lb)
        {
            // kết quả được cộng ra mỗi lần sẽ cộng thêm với phần nguyên số của lượt cộng phía trước
            phanDuSo = (pa->data[i] - '0') + (pb->data[i] - '0') + phanNguyenSo;
            // nếu kết quả này lớn hơn bằng 10 thì phần nguyên số được nhớ với số nguyên phanDuSo/10
            // vd: cộng hai số hàng đơn vị ra 12 thì ghi 1 (11 % 10 = 2) nhớ 1 (11/10 = 1)
            if (phanDuSo >= 10)
                phanNguyenSo = phanDuSo / 10;
            else
                phanNguyenSo = 0;
            xauKetQua += ((phanDuSo % 10) + '0');
            i += 1;
        }
        // chỉ có ba trường hợp xảy ra: trong node đang xét có pa->data hết hoặc pb->data hết hoặc cả hai đều hết
        // nếu chạy hết số phần tử của của xâu pa->data, thì bắt đầu chạy tiếp từ vị trí i của xâu pb->data
        if (i == la && i < lb)
        {
            // phần này xem như các phần tử của pa->data[i] khong tồn tại nên = 0, không ghi vào công thức
            while (i < lb)
            {
                phanDuSo = (pb->data[i] - '0') + phanNguyenSo;
                if (phanDuSo >= 10)
                    phanNguyenSo = phanDuSo / 10;
                else
                    phanNguyenSo = 0;
                xauKetQua += ((phanDuSo % 10) + '0');
                i += 1;
            }
        }
        // nếu chạy hết số phần tử của của xâu pb->data, thì bắt đầu chạy tiếp từ vị trí i của xâu pa->data
        if (i == lb && i < la)
        {
            // phần này xem như các phần tử của pb->data[i] khong tồn tại nên = 0, không ghi vào công thức
            while (i < la)
            {
                phanDuSo = (pa->data[i] - '0') + phanNguyenSo;
                if (phanDuSo >= 10)
                    phanNguyenSo = phanDuSo / 10;
                else
                    phanNguyenSo = 0;
                xauKetQua += ((phanDuSo % 10) + '0');
                i += 1;
            }
        }
        // dời vị trí sang node tiếp theo
        pa = pa->pNext;
        pb = pb->pNext;
    }
    // có ba trường hợp xảy ra: đã xét hết các node của a hoặc đã xét hết các node của b, hoặc cả a và b đã được xét hết
    // nếu sau vòng while trên mà chưa xét hết các node của số a, mà đã xét hết các node của b
    while (pa)
    {
        // xét các node tiếp theo của a với phần nhớ (phanNguyenSo) của phép tính trước đó
        int la = pa->data.size();
        for (int i = 0; i < la; i++)
        {
            phanDuSo = (pa->data[i] - '0') + phanNguyenSo;
            if (phanDuSo >= 10)
                phanNguyenSo = phanDuSo / 10;
            else
                phanNguyenSo = 0;
            xauKetQua += ((phanDuSo % 10) + '0');
        }
        pa = pa->pNext;
    }
    // nếu sau vòng while trên mà chưa xét hết các node của số b, mà đã xét hết các node của a
    while (pb)
    {
        // xét các node tiếp theo của b với phần nhớ (phanNguyenSo) của phép tính trước đó
        int lb = pb->data.size();
        for (int i = 0; i < lb; i++)
        {
            phanDuSo = (pb->data[i] - '0') + phanNguyenSo;
            if (phanDuSo >= 10)
                phanNguyenSo = phanDuSo / 10;
            else
                phanNguyenSo = 0;
            xauKetQua += ((phanDuSo % 10) + '0');
        }
        pb = pb->pNext;
    }
    // nếu đã hoàn toàn xét hết các node trên cả a và b và nếu phần nhớ vẫn còn thì phải thêm một hàng vị trí mới
    // 1 + 99 = 100 thêm tại vị trí hàng trăm
    if (phanNguyenSo != 0)
        xauKetQua += (phanNguyenSo + '0');
    // chuyển từ phần xâu kết quả vừa tìm được và lưu vào dslk BIGNUM ketQua, lưu dưới dạng bị đảo ngược (tham số cuối cùng = 1)
    chuyenTuStringSangBigNum(ketQua, xauKetQua, K, 1);
}

// so sánh a với b
// nếu a < b trả về -1;
// a = b trả về 0
// a > b trả về 1
int soSanhHaiSo(BIGNUM &a, BIGNUM &b, int K)
{
    // so sánh hai số nguyên lớn không âm thì số lượng chữ số ít hơn thì nhỏ hơn
    if (a.soLuongChuSo < b.soLuongChuSo)
        return -1;
    if (a.soLuongChuSo > b.soLuongChuSo)
        return 1;
    // nếu số lượng chữ số bằng nhau thì phải xét từng hàng số
    // so sánh thì số được lưu phải là dạng không bị đảo ngược
    if (a.biNguocDao == 1)
        daoNguocSo(a, K);
    if (b.biNguocDao == 1)
        daoNguocSo(b, K);

    ptrNode pa = a.pHead;
    ptrNode pb = b.pHead;
    while (pa && pb)
    {
        for (int i = 0; i < pa->data.size(); i++)
        {
            // nếu cùng một hàng số mà tại đó của a lớn hơn thì số a lớn hơn và ngược lại
            if (pa->data[i] > pb->data[i])
                return 1;
            if (pa->data[i] < pb->data[i])
                return -1;
        }
        pa = pa->pNext;
        pb = pb->pNext;
    }
    // không xảy ra bất kỳ trường hợp nào lớn hay nhỏ hơn thì hai số a và b bằng nhau
    return 0;
}

int truHaiSo(BIGNUM& ketQua, BIGNUM& a, BIGNUM& b, int K)
{
    // nếu số trừ mà nhỏ hơn số bị trừ thì kết quả tìm được là vô nghĩa, trả về 0
    if (soSanhHaiSo(a, b, K) == -1)
        return 0;
    // phép trừ cũng giống phép cộng, xét từ hàng đơn vị đổ lên nên cả hai số phải đề được lưu đưới dạng đảo ngược
    if (a.biNguocDao == 0)
    {
        daoNguocSo(a, K);
    }
    if (b.biNguocDao == 0)
    {
        daoNguocSo(b, K);
    }
    // con trỏ pa duyệt từng node của BIGNUM a
    // con trỏ pb duyệt từng node của BIGNUM b
    ptrNode pa = a.pHead;
    ptrNode pb = b.pHead;
    string xauKetQua = "";
    // kết quả của phép cộng từng số
    // phần nguyên khi chi cho 10 của phép cộng
    // cộng với nguyên tắc lấy phần dư, nhớ phần nguyên
    int hieuKetQua = 0;
    int phanMuonThem = 0;
    // do số bị trừ phải lớn hơn số trừ nên có trường hợp các node của số bị trừ sẽ còn khi xét vòng lặp
    while (pa && pb)
    {
        // chiều dài của xâu trong một node
        int la = pa->data.size();
        int lb = pb->data.size();
        // con chạy trên từng phần tử của xâu pa->data và pb->data, lần lượt là i
        int i = 0;

        while (i < la && i < lb)
        {
            // nếu phần hiệu của hai số trên cùng một hàng (vd đơn vị) thì khi mà đã từ luôn phần mượn của biểu thức trước đó
            // nếu vẫn nhỏ hơn 0 thì phải cộng thêm 10 và phần mượn lúc này nhớ 1
            if (pa->data[i] < (pb->data[i] + phanMuonThem))
            {
                hieuKetQua = (pa->data[i] - '0') + 10 - (pb->data[i] - '0') - phanMuonThem;
                phanMuonThem = 1;
            }
            else
            {
                hieuKetQua = (pa->data[i] - '0') - (pb->data[i] - '0') - phanMuonThem;
                phanMuonThem = 0;
            }
            // lưu phần tử tính được trên từng hàng vào xâu kết quả
            xauKetQua += (hieuKetQua + '0');
            i += 1;
        }
        // nếu chạy hết số phần tử của 
        //if (i == la && i < lb)
        //{
        //    while (i < lb)
        //    {
        //        if (pa->data[i] < pb->data[i] + muon)
        //        {
        //            hieu = (pa->data[i] - '0') + 10 - (pb->data[i] - '0') - muon;
        //            muon = 1;
        //        }
        //        else
        //        {
        //            hieu = (pa->data[i] - '0') - (pb->data[i] - '0') - muon;
        //            muon = 0;
        //        }
        //        resStr += (hieu + '0');
        //        i += 1;
        //    }
        //}
        // trường hợp i chưa duyệt hết vị trí các phần từ của node pa hiện tại
        if (i == lb && i < la)
        {
            while (i < la)
            {
                if (pa->data[i] < (phanMuonThem + '0'))
                {
                    hieuKetQua = (pa->data[i] - '0') + 10 - phanMuonThem;
                    phanMuonThem = 1;
                }
                else
                {
                    hieuKetQua = (pa->data[i] - '0') - phanMuonThem;
                    phanMuonThem = 0;
                }
                xauKetQua += (hieuKetQua + '0');
                i += 1;
            }
        }
        pa = pa->pNext;
        pb = pb->pNext;
    }
    // trường hợp chưa xét hết các node của a
    while (pa)
    {
        int la = pa->data.size();
        for (int i = 0; i < la; i++)
        {
            if (pa->data[i] < (phanMuonThem + '0'))
            {
                hieuKetQua = (pa->data[i] - '0') + 10 - phanMuonThem;
                phanMuonThem = 1;
            }
            else
            {
                hieuKetQua = (pa->data[i] - '0') - phanMuonThem;
                phanMuonThem = 0;
            }
            xauKetQua += (hieuKetQua + '0');
        }
        pa = pa->pNext;
    }
    // lưu xâu kết quả vừa tìm được vào dslk BIGNUM ketQua ở dạng đảo ngược
    chuyenTuStringSangBigNum(ketQua, xauKetQua, K, 1);
    return 1;
}

// chèn một số ghi được vào vị trí cuối cùng của mảng từ xâu chứa số mới
void chenMotSoVaoMang(BIGNUM*& mangHienTai, int& n, string xauChuaSoMoi, int K)
{
    n += 1;
    // tạo mảng mới có số phần tử lớn hơn 1 phần tử so với mảng hiện tại
    BIGNUM* mangMoi = new BIGNUM[n];
    // copy từng phần tử của mảng hiện tại vào mảng mới
    for (int i = 0; i < n - 1; i++)
        mangMoi[i] = mangHienTai[i];
    // xóa mảng hiện tại
    delete[] mangHienTai;
    // cho mảng hiện tại điều khiển mảng mới
    mangHienTai = mangMoi;
    BIGNUM soCanThemVao;
    // chuyển từ xâu chứa số với vào số cần thêm vào mảng mới
    chuyenTuStringSangBigNum(soCanThemVao, xauChuaSoMoi, K, 1);
    // gán số cần thêm vào vào vị trí cuối của mảng
    mangHienTai[n - 1] = soCanThemVao;
}

// hàm thực hiện chức năng tính toán biểu thức, chức năng -comp của tham số dòng lệnh
void comp(int K, char* duongDanFileInput, char* duongDanFileOutput)
{
    ifstream input(duongDanFileInput);
    ofstream output(duongDanFileOutput);
    int n = 0;
    // lưu số lượng biểu thức cần tính vào biến n
    input >> n;
    output << n << endl;
    string s = "";
    // bỏ qua phần tử enter cuối khi đọc số n
    getline(input, s);
    // xét từng dòng biểu thức
    // cách làm: tính tổng các số trước dấu cộng, các số trước dấu trừ rồi lấy hiệu hai số trên
    for (int i = 0; i < n; i++)
    {
        // mảng lưu các số trước dấu cộng
        BIGNUM* mangCacSoTruocDauCong = NULL;
        // số phần tử của mảng chứa các số trước dấu cộng
        int soPhanTuMangDauCong = 0;
        // mảng chứa các số trước dấu trừ 
        BIGNUM* mangCacSoTruocDauTru = NULL;   
        // số phần tử của mảng chứa các số trước dấu trừ
        int soPhanTuMangDauTru = 0;

        // đọc phần dữ liệu của từ dòng biểu thức
        // thêm vào phần tử "+ " trước xâu và đảo ngược xâu đó 
        // để xâu cần tìm được lưu dúng vào mảng cộng hoặc trừ và lưu ở dạng bị nghịch đảo
        // vd 23 + 3 sẽ thành 3 + 32 + nên các số được lưu thành sẽ ở dạng nghịch đảo 3 và 32
        getline(input, s);
        s = "+ " + s;
        reverse(s.begin(), s.end());
        int lS = s.size();
        // số tìm được trước mỗi dấu biểu thức + hoặc -
        string soTimDuoc = "";
        for (int i = 0; i < lS; i++)
        {
            // nếu phần từ tại vị trí đó mà là phần tử '0' hoặc nhỏ hơn bằng '9' thì số tìm được sẽ thêm phần tử đó vào xâu
            if (s[i] >= '0' && s[i] <= '9')
                soTimDuoc += s[i];
            else
            {
                // bỏ qua khoẳng trắng giữa các số và biểu thức
                if (s[i] != ' ')
                {
                    if (s[i] == '+')
                        chenMotSoVaoMang(mangCacSoTruocDauCong, soPhanTuMangDauCong, soTimDuoc, K);
                    if (s[i] == '-')
                        chenMotSoVaoMang(mangCacSoTruocDauTru, soPhanTuMangDauTru, soTimDuoc, K);
                    soTimDuoc = "";
                }
            }
        }
        // tính tổng các phần tử các số trước dấu cộng trong mảng chứa các số trước dấu cộng
        BIGNUM tongCacSoTruocPhepCong;
        if (soPhanTuMangDauCong > 0)
        {
            tongCacSoTruocPhepCong = mangCacSoTruocDauCong[0];
            for (int i = 1; i < soPhanTuMangDauCong; i++)
                congHaiSo(tongCacSoTruocPhepCong, tongCacSoTruocPhepCong, mangCacSoTruocDauCong[i], K);
        }
        // tính tổng các phần tử các số trước dấu trừ trong mảng chứa các số trước dấu trừ
        BIGNUM tongCacSoTruocPhepTru;
        if (soPhanTuMangDauTru > 0)
        {
            tongCacSoTruocPhepTru = mangCacSoTruocDauTru[0];
            for (int i = 1; i < soPhanTuMangDauTru; i++)
                congHaiSo(tongCacSoTruocPhepTru, tongCacSoTruocPhepTru, mangCacSoTruocDauTru[i], K);
        }
        // check lưu kết quả trả về của phép trừ
        int check = 1;
        // nếu không có phần tử nào trong mảng chứa các số trước phép trừ thì xuất kết quả trước phép cộng
        // ngược lại phải tính hiệu giữa tổng các số trước phép cộng và phép trừ
        if (soPhanTuMangDauTru > 0)
            check = truHaiSo(tongCacSoTruocPhepCong, tongCacSoTruocPhepCong, tongCacSoTruocPhepTru, K);
        // nếu phép trừ hai số không thành công (số bị trừ nhỏ hơn số trừ)
        if (check == 0)
        {
            // ghi xuống NaN
            output << "NaN";
            // chỉ ghi ký tự xuống dòng khi biểu thức đang tính khong phải là biểu thức cuối cùng
            if (i < n - 1)
                output << endl;
        }
        else
        {
            // nếu trừ thành công hoặc không xảy ra phép trừ
            // đảo ngược lại số về dạng đúng
            daoNguocSo(tongCacSoTruocPhepCong, K);
            string soCanGhi = "";
            for (ptrNode p = tongCacSoTruocPhepCong.pHead; p; p = p->pNext)
                soCanGhi += p->data;;
            // nếu số cần ghi có nhiều số không ở phía trước( chỉ xảy ra ở phép trừ)
            // thì bỏ bớt các số 0 khong cần thiết đi
            // nếu số toàn là số 0 thì chỉ chừa lại một số 0 duy nhất
            while (soCanGhi.size() > 1 && soCanGhi[0] == '0')
                soCanGhi.erase(soCanGhi.begin());
            output << soCanGhi;
            // chỉ ghi ký tự xuống dòng khi biểu thức đang tính khong phải là biểu thức cuối cùng
            if (i < n - 1)
                output << endl;
        }
        // xóa các số đã ghi thành công
        xoaBigNum(tongCacSoTruocPhepCong);
        xoaBigNum(tongCacSoTruocPhepTru);
        // trong quá trình tính toán các số của mảng số trước số cộng với số trừ đã bị xóa đi
        // nêu trong mảng hiện tại chỉ còn phần tử cuối cùng
        // chỉ xóa khi số phần tử lớn hơn 1, 
        // vì nếu chỉ có 1 só cần tính đã được lưu trong tongCacSoTruocPhepCong, tongCacSoTruocPhepTri đã bị xóa
        if (soPhanTuMangDauCong > 1)
            xoaBigNum(mangCacSoTruocDauCong[soPhanTuMangDauCong - 1]);
        delete[] mangCacSoTruocDauCong;
        if (soPhanTuMangDauTru > 1)
            xoaBigNum(mangCacSoTruocDauTru[soPhanTuMangDauTru - 1]);
        delete[] mangCacSoTruocDauTru;
    }
    input.close();
    output.close();
}

// chia theo vị trí pivot ở cuối
// K là số phần tử tối đa trong một node của một BIGNUM
int partition(BIGNUM*& a, int K, int l, int r)
{
    BIGNUM pivot = a[r];
    int i = (l - 1);
    for (int j = l; j <= r - 1; j++)
    {
        if (soSanhHaiSo(a[j], pivot, K) == -1)
        {
            i++;
            if (i != j)
                swap(a[i], a[j]);
        }
    }
    if (i + 1 != r)
        swap(a[i + 1], a[r]);
    return (i + 1);
}

// hàm xắp xếp quicksort chia theo vị trí pivot ở cuối
void quickSort(BIGNUM*& a, int K, int l, int r)
{
    if (l < r)
    {
        int pv = partition(a, K, l, r);
        quickSort(a, K,  l, pv - 1);
        quickSort(a, K, pv + 1, r);
    }
}

void merge(BIGNUM*& a, int K, int l, int r, int mid)
{
    int nL = mid - l + 1;
    int nR = r - (mid + 1) + 1;
    BIGNUM* L = new BIGNUM[nL];
    BIGNUM* R = new BIGNUM[nR];

    for (int i = 0; i < nL; i++)
        L[i] = a[l + i];
    for (int i = 0; i < nR; i++)
        R[i] = a[mid + 1 + i];

    int iL = 0, iR = 0, ia = l;

    while (iL < nL && iR < nR)
    {
        if (soSanhHaiSo(L[iL], R[iR], K) == -1)
        {
            a[ia++] = L[iL++];
        }
        else
            a[ia++] = R[iR++];
    }
    while (iL < nL)
    {
        a[ia++] = L[iL++];
    }
    while (iR < nR)
    {
        a[ia++] = R[iR++];
    }
    if (L != NULL)
        delete[] L;
    if (R != NULL)
        delete[] R;
}

void mergeSort(BIGNUM*& a, int K, int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(a, K, l, mid);
        mergeSort(a, K, mid + 1, r);
        merge(a, K, l, r, mid);
    }
}

// hàm thực hiện chức năng xắp xếp, chức năng -qsort và -msort của tham số dòng lệnh
void sort(void (*thuatToanSapXep)(BIGNUM*&, int, int, int), int K, char* duongDanFileInput, char* duongDanFileOutput)
{
    ifstream input(duongDanFileInput);
    ofstream output(duongDanFileOutput);
    int soLuongPhanTu = 0;
    // lưu số lượng phần tử của mảng cần xấp xếp vào biến soLuongPhanTu
    input >> soLuongPhanTu;
    // ghi số lượng của mảng vào file output
    output << soLuongPhanTu << endl;
    // tạo mảng chứa các số với số lượng n phần tử 
    BIGNUM* mangChuaSo = new BIGNUM[soLuongPhanTu];
    string xauChuaSo = "";
    // bỏ qua phần tử enter cuối khi đọc số n
    getline(input, xauChuaSo);
    int step = 0;
    // duyệt từng hang
    for (int i = 0; i < soLuongPhanTu; i++)
    {
        getline(input, xauChuaSo);
        // xóa phần tử '0' nếu người dùng nhập dư trong file input
        while (xauChuaSo.size() > 1 && xauChuaSo[0] == '0')
            xauChuaSo.erase(xauChuaSo.begin());
        // lưu từ xâu vừa tìm được vào mảng với định dạng không đảo ngược số
        chuyenTuStringSangBigNum(mangChuaSo[step], xauChuaSo, K, 0);
        step += 1;
    }
    // truyền thuật toán sắp xếp
    thuatToanSapXep(mangChuaSo, K, 0, soLuongPhanTu - 1);
    // ghi mảng sau khi đã sắp xếp vào file output
    for (int i = 0; i < soLuongPhanTu; i++)
    {
        string soCanGhi = "";
        for (ptrNode p = mangChuaSo[i].pHead; p; p = p->pNext)
            soCanGhi += p->data;
        if (mangChuaSo[i].biNguocDao == 1)
            daoNguocSo(mangChuaSo[i], K);
        output << soCanGhi;
        // chỉ xuất kí tự xuống dòng khi phần tử đang ghi khong phải là phần tử cuối cùng để đúng định dạng
        if (i < soLuongPhanTu - 1)
            output << endl;
    }

    // lần lượt xóa các số trong mảng
    for (int i = 0; i < soLuongPhanTu; i++)
        xoaBigNum(mangChuaSo[i]);
    // xóa mảng
    delete[] mangChuaSo;
    mangChuaSo = NULL;
    input.close();
    output.close();
}