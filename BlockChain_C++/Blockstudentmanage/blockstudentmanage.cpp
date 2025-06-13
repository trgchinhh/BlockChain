/*
    CHƯƠNG TRÌNH CƠ BẢN MÔ PHỎNG BLOCKCHAIN QUẢN LÝ THÔNG TIN SINH VIÊN BẰNG NGÔN NGỮ C++ 
                       ____ ___  ____  _____   ______   __
                      / ___/ _ \|  _ \| ____| | __ ) \ / /
                     | |  | | | | | | |  _|   |  _ \\ V / 
                     | |__| |_| | |_| | |___  | |_) || |  
                      \____\___/|____/|_____| |____/ |_|
                  
  _______ _____  _    _  ____  _   _  _____     _____ _    _ _____ _   _ _    _ 
 |__   __|  __ \| |  | |/ __ \| \ | |/ ____|   / ____| |  | |_   _| \ | | |  | |
    | |  | |__) | |  | | |  | |  \| | |  __   | |    | |__| | | | |  \| | |__| |
    | |  |  _  /| |  | | |  | | . ` | | |_ |  | |    |  __  | | | | . ` |  __  |
    | |  | | \ \| |__| | |__| | |\  | |__| |  | |____| |  | |_| |_| |\  | |  | |
    |_|  |_|  \_\\____/ \____/|_| \_|\_____|   \_____|_|  |_|_____|_| \_|_|  |_|
*/

#include <bits/stdc++.h>
#define ___TruongChinh304___ signed main()
using namespace std;

// bien dem so lan ghi vao file 
int g_demghivaofile = 0;

struct KhoiSinhVien {
    int sokhoi;
    string tensinhvien;
    int masinhvien = 0;
    string mabamtruocdo;
    string mabamhientai;
};

string bamthongtin(string thongtin){
    hash<string> hambam;
    size_t ketqua = hambam(thongtin);
    return to_string(ketqua);
}

bool ghivaofile(string& duongdan, string noidung, int soluongsinhvien){
    if(g_demghivaofile == 0){
        ofstream file(duongdan, ios::trunc);
        file << noidung;
    } else { 
        ofstream file(duongdan, ios::app);
        file << noidung;
    }    
    if(++g_demghivaofile == soluongsinhvien) return true; 
    else return false;
}

string inthongtin(int sokhoi, string tensinhvien, 
                int masinhvien, string mabamtruocdo, string mabamhientai){
    ostringstream oss;
    if(sokhoi == 0) {
        oss << "\n┌ Khoi: " << "Khoi tao" 
            << "\n├ Ten sinh vien: " << "N/A"
            << "\n├ Ma sinh vien: " << "N/A"
            << "\n└ Ma bam khoi tao: " << mabamhientai
            << "\n";
    }
    else {
        oss << "\n┌ Khoi: " << sokhoi
            << "\n├ Ten sinh vien: " << tensinhvien
            << "\n├ Ma sinh vien: " << masinhvien
            << "\n├ Ma bam truoc do: " << mabamtruocdo
            << "\n└ Ma bam hien tai: " << mabamhientai
            << "\n";
    }        
    return oss.str();
}

bool bamhople(const string& ketquabam, int dokho) {
    return ketquabam.substr(ketquabam.size() - dokho) == string(dokho, '0');
}

void taokhoisinhvien(vector<KhoiSinhVien>& Danhsachkhoisinhvien, 
                     vector<string>& Danhsachtensinhvien, int soluongsinhvien, int dokho, string& duongdan){
    KhoiSinhVien ksv;
    string mabamtruocdo = bamthongtin("KHOI TAO");

    // tao ten sinh vien ngau nhien
    srand(time(0));
    for(int i = 0; i <= soluongsinhvien; i++){
        int vitritensinhvien = rand() % Danhsachtensinhvien.size();
        ksv.tensinhvien = Danhsachtensinhvien[vitritensinhvien];
        ksv.masinhvien = i;
        ksv.sokhoi = i;
        ksv.mabamtruocdo = mabamtruocdo;
        int nonce = 0;
        while (true) {
            string data_to_hash = ksv.tensinhvien + to_string(ksv.masinhvien) + to_string(nonce);
            ksv.mabamhientai = bamthongtin(data_to_hash);
            if (bamhople(ksv.mabamhientai, dokho)) {
                break;
            }
            nonce++;
        }
        mabamtruocdo = ksv.mabamhientai;
        Danhsachkhoisinhvien.push_back(ksv);
        string noidung = inthongtin(ksv.sokhoi, ksv.tensinhvien, ksv.masinhvien, ksv.mabamtruocdo, ksv.mabamhientai);
        bool hoanthanh = ghivaofile(duongdan, noidung, soluongsinhvien);
        if(hoanthanh) cout << "Hoan thanh ghi vao file\n\n";
    }    
    Danhsachkhoisinhvien[0].tensinhvien = "N/A";
    for (size_t i = 0; i < Danhsachkhoisinhvien.size(); i++) {
        if(i != 0){
            cout << Danhsachkhoisinhvien[i].tensinhvien << "\n"
                 << Danhsachkhoisinhvien[i].masinhvien << "\n"
                 << Danhsachkhoisinhvien[i].mabamtruocdo << "\n"
                 << Danhsachkhoisinhvien[i].mabamhientai << "\n\n";
        } else {
            cout << Danhsachkhoisinhvien[i].tensinhvien << "\n"
                 << Danhsachkhoisinhvien[i].masinhvien << "\n"
                 << Danhsachkhoisinhvien[i].mabamhientai << "\n\n";
        }         
    }
}   

___TruongChinh304___ {
    vector<KhoiSinhVien> Danhsachkhoisinhvien;
    int soluongsinhvien = 100;
    int dokho = 5;

    // danh sach ten sinh vien
    vector<string> Danhsachtensinhvien = {
        "An", "Bao", "Cuong", "Duy", "Em", "Giang", "Hai", "Hung", "Khoa", "Lam",
        "Linh", "Minh", "Nam", "Phong", "Quang", "Quoc", "Son", "Tai", "Thanh", "Thien",
        "Thinh", "Tien", "Trung", "Tuan", "Viet", "Vu", "Yen", "Anh", "Binh", "Chi",
        "Dao", "Dung", "Hanh", "Hoa", "Hoang", "Huong", "Khanh", "Loan", "Mai", "Nga",
        "Ngan", "Ngoc", "Nhi", "Oanh", "Phuong", "Quynh", "Sang", "Thao", "Thu", "Trang",
        "Trinh", "Tu", "Vy", "Xuan", "Yen", "Loc", "Anhtu", "Camtu", "Kiet", "Thaochi",
        "Phuoc", "Hieu", "Nhan", "Thuy", "Khanhlinh", "Kimanh", "Trong", "Tinh", "Dai", "Kiet",
        "Trieu", "Thanhdat", "Giahan", "Phat", "Duong", "Haiyen", "Le", "Baoan", "Tinhdo", "Kimchi",
        "Long", "Lan", "Daoanh", "Ngoctuan", "Myanh", "Nhut", "Dang", "Ngocthuy", "Phuc", "Thuan",
        "Nghi", "Tam", "Tan", "Kha", "Thanhtruc", "Bich", "Thuytien", "Kimngan", "Sonlam", "Vankhanh"
    };
    string duongdan = "D:\\Blockchain_C++\\Blockstudentmanage\\blockstudentmanage.txt";
    taokhoisinhvien(Danhsachkhoisinhvien, Danhsachtensinhvien, soluongsinhvien, dokho, duongdan);
    return 0;
}