/*
            CHƯƠNG TRÌNH CƠ BẢN MÔ PHỎNG BLOCKCHAIN BẰNG NGÔN NGỮ C++ 
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
#define ___TruongChinh___ signed main()
using namespace std;

struct GiaoDich {
    string nguoi_gui;           
    string nguoi_nhan;        
    float so_luong;
    string noi_dung;
    string don_vi_tien_ma_hoa;
};

// thông tin của một block (chứa 5 giao dịch)
struct Block {
    int so_thu_tu;            
    vector<GiaoDich> giao_dich;
    string du_lieu;
    string ma_bam;
};

string bam_du_lieu(string du_lieu_dau_vao) {
    hash<string> ham_bam;
    size_t ket_qua = ham_bam(du_lieu_dau_vao);
    return to_string(ket_qua);
}

bool bam_hop_le(const string& ket_qua_bam, int do_kho) {
    return ket_qua_bam.substr(ket_qua_bam.size() - do_kho) == string(do_kho, '0');
}
 
string in_thong_tin_block(int so_thu_tu, int so_nonce, const vector<GiaoDich>& giao_dich, 
                        string ket_qua_bam, string ma_bam_truoc_do) {
    ostringstream oss;
    if(so_thu_tu != 1) {    
        oss << "\n┌ Khoi: " << so_thu_tu
            << "\n├ So nonce: " << so_nonce;
        
        for (size_t i = 0; i < giao_dich.size(); i++) {
            oss << "\n├─────── Giao dich " << i+1 << " ───────"
                << "\n├ Nguoi gui: " << giao_dich[i].nguoi_gui
                << "\n├ Nguoi nhan: " << giao_dich[i].nguoi_nhan
                << "\n├ So luong: " << fixed << setprecision(2) << giao_dich[i].so_luong << " " << giao_dich[i].don_vi_tien_ma_hoa
                << "\n├ Noi dung: " << giao_dich[i].noi_dung;
        }
        oss << "\n├ Ma bam truoc do: " << ma_bam_truoc_do
            << "\n└ Ma bam hien tai: " << ket_qua_bam << "\n";
    } else {
        oss << "\n┌ Khoi: " << so_thu_tu
            << "\n├ So nonce: " << so_nonce
            << "\n├ Noi dung: Genesis Block"
            << "\n└ Ma bam: " << ket_qua_bam << "\n";
    }        
    return oss.str(); 
}

void ghi_thong_tin_block_vao_file(string& duongdan, string& noidung) {
    ofstream file(duongdan, ios::app); // ios::app tránh ghi đè từng giao dịch 
    file << noidung;
}

vector<GiaoDich> tao_giao_dich(vector<string>& danh_sach_ten, 
                              vector<float>& danh_sach_tien_chuyen, 
                              vector<string>& danh_sach_tien_ma_hoa) {
    vector<GiaoDich> giao_dich(5);
    srand(time(0));
    
    for (int i = 0; i < 5; i++) {
        int vi_tri_nguoi_gui = rand() % danh_sach_ten.size();
        int vi_tri_nguoi_nhan = rand() % danh_sach_ten.size();
        int vi_tri_tien_chuyen = rand() % danh_sach_tien_chuyen.size();
        int vi_tri_don_vi_tien_ma_hoa = rand() % danh_sach_tien_ma_hoa.size();
        while (vi_tri_nguoi_nhan == vi_tri_nguoi_gui) {
            vi_tri_nguoi_nhan = rand() % danh_sach_ten.size();
        }

        giao_dich[i].nguoi_gui = danh_sach_ten[vi_tri_nguoi_gui];
        giao_dich[i].nguoi_nhan = danh_sach_ten[vi_tri_nguoi_nhan];
        giao_dich[i].so_luong = danh_sach_tien_chuyen[vi_tri_tien_chuyen];
        giao_dich[i].don_vi_tien_ma_hoa = danh_sach_tien_ma_hoa[vi_tri_don_vi_tien_ma_hoa];
        ostringstream oss;
        oss << fixed << setprecision(2) << giao_dich[i].so_luong;
        string str_soluong = oss.str();
        giao_dich[i].noi_dung = giao_dich[i].nguoi_gui + " chuyen khoan toi " + giao_dich[i].nguoi_nhan + " " 
                                + str_soluong + " (" + giao_dich[i].don_vi_tien_ma_hoa + ")";
    }
    
    return giao_dich;
}

void tao_chuoi_khoi(vector<string>& chuoi_khoi, int so_luong_khoi, int do_kho, vector<string>& danh_sach_ten, 
                    vector<float>& danh_sach_tien_chuyen, vector<string>& danh_sach_tien_ma_hoa, string& duongdan) {
    string ma_bam_truoc_do = "";
    srand(time(0));
    for (int i = 1; i <= so_luong_khoi; i++) {
        Block khoi;
        khoi.so_thu_tu = i;
        
        if (i == 1) {
            khoi.du_lieu = to_string(khoi.so_thu_tu) + "Genesis Block";
        } else {
            khoi.giao_dich = tao_giao_dich(danh_sach_ten, danh_sach_tien_chuyen, danh_sach_tien_ma_hoa);
            
            // Tạo dữ liệu để băm từ các giao dịch
            ostringstream du_lieu_stream;
            du_lieu_stream << khoi.so_thu_tu;
            for (const auto& gd : khoi.giao_dich) {
                du_lieu_stream << gd.nguoi_gui << gd.nguoi_nhan << gd.so_luong 
                              << gd.don_vi_tien_ma_hoa << gd.noi_dung;
            }
            du_lieu_stream << ma_bam_truoc_do;
            khoi.du_lieu = du_lieu_stream.str();
        }
        
        int so_nonce = 0;
        string du_lieu_day_du, ket_qua_bam;
        while (true) {
            du_lieu_day_du = khoi.du_lieu + to_string(so_nonce);
            ket_qua_bam = bam_du_lieu(du_lieu_day_du);
            if (bam_hop_le(ket_qua_bam, do_kho)) {
                break;
            }
            so_nonce++;
        }

        khoi.ma_bam = ket_qua_bam;
        chuoi_khoi.push_back(khoi.ma_bam);
        
        string thongtinghivaofile;
        if (i == 1) {
            thongtinghivaofile = in_thong_tin_block(khoi.so_thu_tu, so_nonce, {}, ket_qua_bam, ma_bam_truoc_do);
        } else {
            thongtinghivaofile = in_thong_tin_block(khoi.so_thu_tu, so_nonce, khoi.giao_dich, ket_qua_bam, ma_bam_truoc_do);
        }
        
        ghi_thong_tin_block_vao_file(duongdan, thongtinghivaofile);
        cout << thongtinghivaofile;
        ma_bam_truoc_do = khoi.ma_bam;
    }
}

___TruongChinh___ {
    vector<string> chuoi_khoi; // vector chứa thông tin các block
    int so_luong_khoi = 10; // số lượng block (mỗi block chứa 5 giao dịch)
    int do_kho = 5; 

    vector<string> danh_sach_ten = {
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

    vector<float> danh_sach_tien_chuyen = {
        0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0,
        10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0,
        20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, 25.0, 25.5, 26.0, 26.5, 27.0, 27.5, 28.0, 28.5, 29.0, 29.5, 30.0,
        30.5, 31.0, 31.5, 32.0, 32.5, 33.0, 33.5, 34.0, 34.5, 35.0, 35.5, 36.0, 36.5, 37.0, 37.5, 38.0, 38.5, 39.0, 39.5, 40.0,
        40.5, 41.0, 41.5, 42.0, 42.5, 43.0, 43.5, 44.0, 44.5, 45.0, 45.5, 46.0, 46.5, 47.0, 47.5, 48.0, 48.5, 49.0, 49.5, 50.0,
        50.5, 51.0, 51.5, 52.0, 52.5, 53.0, 53.5, 54.0, 54.5, 55.0, 55.5, 56.0, 56.5, 57.0, 57.5, 58.0, 58.5, 59.0, 59.5, 60.0,
        60.5, 61.0, 61.5, 62.0, 62.5, 63.0, 63.5, 64.0, 64.5, 65.0, 65.5, 66.0, 66.5, 67.0, 67.5, 68.0, 68.5, 69.0, 69.5, 70.0,
        70.5, 71.0, 71.5, 72.0, 72.5, 73.0, 73.5, 74.0, 74.5, 75.0, 75.5, 76.0, 76.5, 77.0, 77.5, 78.0, 78.5, 79.0, 79.5, 80.0,
        80.5, 81.0, 81.5, 82.0, 82.5, 83.0, 83.5, 84.0, 84.5, 85.0, 85.5, 86.0, 86.5, 87.0, 87.5, 88.0, 88.5, 89.0, 89.5, 90.0,
        90.5, 91.0, 91.5, 92.0, 92.5, 93.0, 93.5, 94.0, 94.5, 95.0, 95.5, 96.0, 96.5, 97.0, 97.5, 98.0, 98.5, 99.0, 99.5, 100.0
    };

    vector<string> danh_sach_tien_ma_hoa = {
        "BTC", "ETH", "BNB", "SOL", "ADA", "XRP", "DOGE", "DOT", "TRX", "AVAX",
        "MATIC", "SHIB", "LTC", "BCH", "XLM", "ATOM", "LINK", "NEAR", "HBAR", "ICP",
        "FIL", "APT", "ARB", "SUI", "OP", "XTZ", "VET", "EGLD", "FTM", "THETA",
        "AAVE", "MKR", "SNX", "KSM", "ZEC", "DASH", "ENJ", "GRT", "CHZ", "CRV",
        "1INCH", "COMP", "DYDX", "LDO"
    };
    
    string duongdan = "D:\\BlockChain_C++\\Block5Transfer\\thongtinblock5transfer.txt";
    tao_chuoi_khoi(chuoi_khoi, so_luong_khoi, do_kho, danh_sach_ten, 
                    danh_sach_tien_chuyen, danh_sach_tien_ma_hoa, duongdan);
    return 0;
}
