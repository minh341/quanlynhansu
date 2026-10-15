#include "QuanLyNhanSu.h"
#include <algorithm>
#include <cctype>
using namespace std;

static string thuong(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    return s;
}

QuanLyNhanSu::QuanLyNhanSu() {}
QuanLyNhanSu::QuanLyNhanSu(const NhanVien& nv, const string& chuyenMon)
    : NhanVien(nv), chuyenMon(chuyenMon) {}

string QuanLyNhanSu::getChuyenMon() const { return chuyenMon; }
void QuanLyNhanSu::setChuyenMon(const string& cm) { chuyenMon = cm; }

void QuanLyNhanSu::xemThongTin() const {
    NhanVien::xemThongTin();                       // tái sử dụng phần của lớp cha
    cout << "Chuyen mon     : " << chuyenMon << "\n";
}
string QuanLyNhanSu::vaiTro() const { return "Quan ly nhan su"; }
double QuanLyNhanSu::tinhPhuCapQuanLy() const { return 2000000; }
string QuanLyNhanSu::toFileString() const { return "QL|" + truongCoBan() + "|" + chuyenMon; }

NhanVien* QuanLyNhanSu::timNhanVien(const vector<NhanVien*>& ds, const string& maNV) const {
    for (NhanVien* p : ds)
        if (p->getMaNV() == maNV) return p;
    return nullptr;
}

vector<NhanVien*> QuanLyNhanSu::timTheoTen(const vector<NhanVien*>& ds, const string& tuKhoa) const {
    vector<NhanVien*> kq;
    string k = thuong(tuKhoa);
    for (NhanVien* p : ds)
        if (thuong(p->getHoTen()).find(k) != string::npos) kq.push_back(p);
    return kq;
}

bool QuanLyNhanSu::themNhanVien(vector<NhanVien*>& ds, NhanVien* nv) {
    if (nv == nullptr || timNhanVien(ds, nv->getMaNV()) != nullptr) return false;
    ds.push_back(nv);
    return true;
}

bool QuanLyNhanSu::suaNhanVien(vector<NhanVien*>& ds, const string& maNV) {
    NhanVien* nv = timNhanVien(ds, maNV);
    if (!nv) return false;
    string s;
    cout << "(De trong de giu nguyen)\n";
    cout << "Ho ten moi: ";        getline(cin, s); if (!s.empty()) nv->setHoTen(s);
    cout << "Dia chi moi: ";       getline(cin, s); if (!s.empty()) nv->setDiaChi(s);
    cout << "So dien thoai moi: "; getline(cin, s); if (!s.empty()) nv->setSoDienThoai(s);
    cout << "Email moi: ";         getline(cin, s); if (!s.empty()) nv->setEmail(s);
    return true;
}

// Lưu ý: hàm này giải phóng đối tượng; nơi gọi phải gỡ nhân viên khỏi PhongBan trước.
bool QuanLyNhanSu::xoaNhanVien(vector<NhanVien*>& ds, const string& maNV) {
    for (size_t i = 0; i < ds.size(); ++i) {
        if (ds[i]->getMaNV() == maNV) {
            delete ds[i];
            ds.erase(ds.begin() + i);
            return true;
        }
    }
    return false;
}

void QuanLyNhanSu::ghiNhanChamCong(vector<ChamCong>& dsCC, const ChamCong& cc) {
    for (ChamCong& x : dsCC) {
        if (x.getMaNV() == cc.getMaNV() && x.getNgay() == cc.getNgay()) {
            x = cc;  // đã có bản ghi cùng ngày -> ghi đè
            return;
        }
    }
    dsCC.push_back(cc);
}

BangLuong QuanLyNhanSu::lapBangLuong(const NhanVien& nv, const ChucDanh& cd,
                                     const vector<ChamCong>& dsCC, int thang, int nam) const {
    BangLuong bl("BL" + nv.getMaNV() + "_" + to_string(thang) + "_" + to_string(nam),
                 nv.getMaNV(), thang, nam);
    bl.tinhLuong(nv, cd, dsCC);
    return bl;
}
