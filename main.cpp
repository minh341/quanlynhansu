// ============================================================
//  HE THONG QUAN LY NHAN SU (HRMS) - Bai tap lon OOP (C++)
//  Dang nhap bang ma nhan vien; menu thay doi theo vai tro
//  (dung dynamic_cast de nhan biet lop con -> da hinh).
// ============================================================
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "BanGiamDoc.h"
#include "BangLuong.h"
#include "ChamCong.h"
#include "ChucDanh.h"
#include "DonNghiPhep.h"
#include "NhanVien.h"
#include "PhongBan.h"
#include "QuanLyNhanSu.h"
using namespace std;

static const string THU_MUC = "data/";

// ---------------- Du lieu chung ----------------
struct DuLieu {
    vector<NhanVien*> dsNV;     // so huu cac doi tuong NhanVien (xoa trong destructor)
    vector<PhongBan> dsPB;
    vector<ChucDanh> dsCD;
    vector<ChamCong> dsCC;
    vector<DonNghiPhep> dsDon;
    ~DuLieu() { for (NhanVien* p : dsNV) delete p; }
};

// ---------------- Tien ich nhap/xuat ----------------
static string nhapDong(const string& nhan) {
    cout << nhan;
    string s;
    if (!getline(cin, s)) { cout << "\n[Het du lieu nhap]\n"; exit(0); }
    replace(s.begin(), s.end(), '|', '/');   // '|' la ky tu phan cach trong file
    return s;
}

static int nhapSo(const string& nhan, int lo, int hi) {
    while (true) {
        string s = nhapDong(nhan);
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos == s.size() && v >= lo && v <= hi) return v;
        } catch (...) {}
        cout << "  Gia tri khong hop le (" << lo << " - " << hi << "). Nhap lai.\n";
    }
}

static bool hopLeNgay(const string& s) {
    int d, m, y;
    if (s.size() != 10 || s[2] != '/' || s[5] != '/') return false;
    if (sscanf(s.c_str(), "%2d/%2d/%4d", &d, &m, &y) != 3) return false;
    return d >= 1 && d <= 31 && m >= 1 && m <= 12 && y >= 1900 && y <= 2100;
}

static bool hopLeGio(const string& s) {
    int h, m;
    if (s.size() != 5 || s[2] != ':') return false;
    if (sscanf(s.c_str(), "%2d:%2d", &h, &m) != 2) return false;
    return h >= 0 && h < 24 && m >= 0 && m < 60;
}

static string nhapNgay(const string& nhan) {
    while (true) {
        string s = nhapDong(nhan);
        if (hopLeNgay(s)) return s;
        cout << "  Ngay phai co dang dd/mm/yyyy.\n";
    }
}

static string nhapGio(const string& nhan) {
    while (true) {
        string s = nhapDong(nhan);
        if (hopLeGio(s)) return s;
        cout << "  Gio phai co dang HH:MM.\n";
    }
}

static void tieuDe(const string& s) { cout << "\n=== " << s << " ===\n"; }

// ---------------- Tim kiem ----------------
static PhongBan* timPB(DuLieu& d, const string& ma) {
    for (PhongBan& p : d.dsPB) if (p.getMaPB() == ma) return &p;
    return nullptr;
}
static const ChucDanh* timCD(const DuLieu& d, const string& ma) {
    for (const ChucDanh& c : d.dsCD) if (c.getMaCD() == ma) return &c;
    return nullptr;
}
static NhanVien* timNV(DuLieu& d, const string& ma) {
    for (NhanVien* p : d.dsNV) if (p->getMaNV() == ma) return p;
    return nullptr;
}

// ---------------- Doc / ghi file ----------------
static vector<string> tach(const string& s, char c) {
    vector<string> kq;
    size_t dau = 0;
    while (true) {
        size_t vt = s.find(c, dau);
        if (vt == string::npos) { kq.push_back(s.substr(dau)); break; }
        kq.push_back(s.substr(dau, vt - dau));
        dau = vt + 1;
    }
    return kq;
}

static vector<string> docDong(const string& duongDan) {
    vector<string> kq;
    ifstream in(duongDan);
    string dong;
    while (getline(in, dong)) {
        if (!dong.empty() && dong.back() == '\r') dong.pop_back();
        if (!dong.empty()) kq.push_back(dong);
    }
    return kq;
}

static void docDuLieu(DuLieu& d) {
    for (const string& l : docDong(THU_MUC + "chucdanh.txt")) {
        auto f = tach(l, '|');
        if (f.size() < 4) continue;
        try { d.dsCD.emplace_back(f[0], f[1], stod(f[2]), stod(f[3])); } catch (...) {}
    }
    for (const string& l : docDong(THU_MUC + "phongban.txt")) {
        auto f = tach(l, '|');
        if (f.size() >= 3) d.dsPB.emplace_back(f[0], f[1], f[2]);
    }
    for (const string& l : docDong(THU_MUC + "nhanvien.txt")) {
        auto f = tach(l, '|');
        if (f.size() < 15) continue;
        int phepNam, phepDung;
        try { phepNam = stoi(f[13]); phepDung = stoi(f[14]); } catch (...) { continue; }
        NhanVien base(f[1], f[2], f[3], f[4], f[5], f[6], f[7], f[8], f[9], f[11], f[12]);
        NhanVien* p;
        if (f[0] == "QL" && f.size() >= 16)       p = new QuanLyNhanSu(base, f[15]);
        else if (f[0] == "BGD" && f.size() >= 16) p = new BanGiamDoc(base, f[15]);
        else                                      p = new NhanVien(base);
        p->setTrangThai(f[10]);
        p->setSoNgayPhepNam(phepNam);
        p->setSoNgayPhepDaDung(phepDung);
        d.dsNV.push_back(p);
    }
    for (NhanVien* p : d.dsNV) {                 // dung lai quan he PhongBan -> NhanVien
        PhongBan* pb = timPB(d, p->getMaPB());
        if (pb) pb->themNhanVien(p);
    }
    for (const string& l : docDong(THU_MUC + "chamcong.txt")) {
        auto f = tach(l, '|');
        if (f.size() < 5) continue;
        ChamCong cc(f[0], f[1], f[2]);
        if (!f[3].empty() && !f[4].empty()) cc.ghiNhanCong(f[3], f[4]);
        d.dsCC.push_back(cc);
    }
    for (const string& l : docDong(THU_MUC + "donnghiphep.txt")) {
        auto f = tach(l, '|');
        if (f.size() < 8) continue;
        try {
            DonNghiPhep dn(f[0], f[1], f[2], f[3], f[4], stoi(f[5]), f[6]);
            dn.setTrangThai(static_cast<TrangThaiDon>(stoi(f[7])));
            d.dsDon.push_back(dn);
        } catch (...) {}
    }
}

template <typename T>
static bool ghiFile(const string& ten, const vector<T>& ds) {
    ofstream out(THU_MUC + ten);
    if (!out) return false;
    for (const T& x : ds) out << x.toFileString() << "\n";
    return true;
}

static void luuDuLieu(const DuLieu& d) {
    ofstream out(THU_MUC + "nhanvien.txt");
    if (!out) {
        cout << "[Canh bao] Khong ghi duoc vao thu muc data/. Hay chay chuong trinh tu thu muc HRMS.\n";
        return;
    }
    for (const NhanVien* p : d.dsNV) out << p->toFileString() << "\n";   // virtual -> dung loai
    out.close();
    ghiFile("phongban.txt", d.dsPB);
    ghiFile("chucdanh.txt", d.dsCD);
    ghiFile("chamcong.txt", d.dsCC);
    ghiFile("donnghiphep.txt", d.dsDon);
    cout << "[Da luu du lieu vao thu muc data/]\n";
}

static void taoDuLieuMau(DuLieu& d) {
    d.dsCD = {ChucDanh("CD01", "Nhan vien", 8000000, 500000),
              ChucDanh("CD02", "Chuyen vien", 12000000, 1000000),
              ChucDanh("CD03", "Truong phong", 20000000, 3000000),
              ChucDanh("CD04", "Giam doc", 40000000, 5000000)};
    d.dsPB = {PhongBan("PB01", "Phong Nhan su", "Tuyen dung, ho so, luong"),
              PhongBan("PB02", "Phong Ke toan", "Tai chinh, ke toan"),
              PhongBan("PB03", "Phong Kinh doanh", "Ban hang, cham soc khach hang"),
              PhongBan("PB04", "Ban Giam doc", "Dieu hanh cong ty")};

    NhanVien a("NV001", "Nguyen Van An", "12/03/1992", "Nam", "001092000111", "Ha Noi",
               "0901000001", "an@congty.vn", "01/02/2020", "PB01", "CD02");
    NhanVien b("NV002", "Tran Thi Binh", "25/07/1985", "Nu", "001085000222", "Ha Noi",
               "0901000002", "binh@congty.vn", "01/01/2018", "PB04", "CD04");
    NhanVien c("NV003", "Le Van Cuong", "05/11/1998", "Nam", "001098000333", "Hai Phong",
               "0901000003", "cuong@congty.vn", "15/06/2023", "PB02", "CD01");
    NhanVien e("NV004", "Pham Thi Dung", "30/01/1999", "Nu", "001099000444", "Nam Dinh",
               "0901000004", "dung@congty.vn", "10/09/2023", "PB03", "CD01");
    NhanVien g("NV005", "Hoang Van Em", "18/09/1988", "Nam", "001088000555", "Ha Noi",
               "0901000005", "em@congty.vn", "01/03/2019", "PB03", "CD03");
    d.dsNV = {new QuanLyNhanSu(a, "Tuyen dung"), new BanGiamDoc(b, "Giam doc"),
              new NhanVien(c), new NhanVien(e), new BanGiamDoc(g, "Truong phong")};
    for (NhanVien* p : d.dsNV) {
        PhongBan* pb = timPB(d, p->getMaPB());
        if (pb) pb->themNhanVien(p);
    }
    // Cham cong mau thang 09/2026 (22 ngay) cho moi nhan vien
    for (NhanVien* p : d.dsNV) {
        for (int ngay = 1; ngay <= 22; ++ngay) {
            char buf[16];
            snprintf(buf, sizeof buf, "%02d/09/2026", ngay);
            ChamCong cc("CC" + p->getMaNV() + "_" + buf, p->getMaNV(), buf);
            cc.ghiNhanCong(ngay % 5 == 0 ? "08:15" : "08:00", ngay % 4 == 0 ? "19:00" : "17:00");
            d.dsCC.push_back(cc);
        }
    }
    DonNghiPhep dn("DN1", "NV003", "Phep nam", "20/10/2026", "21/10/2026", 2, "Ve que");
    d.dsDon.push_back(dn);
}

// ---------------- Chuc nang chung (moi vai tro) ----------------
static void xemBangLuongCuaToi(DuLieu& d, NhanVien* user) {
    tieuDe("BANG LUONG CUA TOI");
    int thang = nhapSo("Thang (1-12): ", 1, 12);
    int nam = nhapSo("Nam: ", 2000, 2100);
    const ChucDanh* cd = timCD(d, user->getMaCD());
    if (!cd) { cout << "Chua co chuc danh hop le.\n"; return; }
    BangLuong bl("BL" + user->getMaNV(), user->getMaNV(), thang, nam);
    bl.tinhLuong(*user, *cd, d.dsCC);
    if (bl.getSoNgayCong() == 0) cout << "Chua co du lieu cham cong thang nay.\n";
    else bl.inPhieuLuong();
}

static void guiDonNghiPhep(DuLieu& d, NhanVien* user) {
    tieuDe("GUI DON NGHI PHEP");
    cout << "Phep con lai: " << user->soNgayPhepConLai() << " ngay\n";
    int loai = nhapSo("Loai phep (1=Phep nam, 2=Nghi om, 3=Viec rieng): ", 1, 3);
    const char* ten[] = {"", "Phep nam", "Nghi om", "Viec rieng"};
    string tu = nhapNgay("Tu ngay (dd/mm/yyyy): ");
    string den = nhapNgay("Den ngay (dd/mm/yyyy): ");
    int soNgay = nhapSo("So ngay nghi (1-30): ", 1, 30);
    string lyDo = nhapDong("Ly do: ");
    DonNghiPhep dn("DN" + to_string(d.dsDon.size() + 1), user->getMaNV(), ten[loai], tu, den, soNgay, lyDo);
    dn.guiDon();
    d.dsDon.push_back(dn);
    cout << "Da gui don " << dn.getMaDon() << ", dang cho Ban giam doc duyet.\n";
}

static void xemDonCuaToi(const DuLieu& d, NhanVien* user) {
    tieuDe("DON NGHI PHEP CUA TOI");
    int dem = 0;
    for (const DonNghiPhep& dn : d.dsDon)
        if (dn.getMaNV() == user->getMaNV()) { dn.hienThi(); ++dem; }
    if (!dem) cout << "  Ban chua gui don nao.\n";
}

// ---------------- Chuc nang Quan ly nhan su ----------------
static void inDanhSachNV(const DuLieu& d) {
    cout << left << setw(8) << "Ma" << setw(24) << "Ho ten" << setw(18) << "Vai tro"
         << setw(8) << "PB" << setw(8) << "CD" << "Trang thai\n";
    for (const NhanVien* p : d.dsNV) cout << *p << "\n";   // operator<< goi vaiTro() ao
}

static void themNhanVien(DuLieu& d, QuanLyNhanSu* ql) {
    tieuDe("THEM NHAN VIEN");
    string ma = nhapDong("Ma NV: ");
    if (ma.empty()) return;
    if (timNV(d, ma)) { cout << "Ma nhan vien da ton tai.\n"; return; }
    string ten = nhapDong("Ho ten: ");
    string ns = nhapNgay("Ngay sinh (dd/mm/yyyy): ");
    string gt = nhapDong("Gioi tinh: ");
    string cccd = nhapDong("CCCD: ");
    string dc = nhapDong("Dia chi: ");
    string sdt = nhapDong("So dien thoai: ");
    string mail = nhapDong("Email: ");
    string nvl = nhapNgay("Ngay vao lam (dd/mm/yyyy): ");
    string maPB = nhapDong("Ma phong ban: ");
    PhongBan* pb = timPB(d, maPB);
    if (!pb) { cout << "Phong ban khong ton tai.\n"; return; }
    string maCD = nhapDong("Ma chuc danh: ");
    if (!timCD(d, maCD)) { cout << "Chuc danh khong ton tai.\n"; return; }
    int loai = nhapSo("Loai (1=Nhan vien, 2=Quan ly nhan su, 3=Ban giam doc): ", 1, 3);

    NhanVien base(ma, ten, ns, gt, cccd, dc, sdt, mail, nvl, maPB, maCD);
    NhanVien* p;
    if (loai == 2)      p = new QuanLyNhanSu(base, nhapDong("Chuyen mon: "));
    else if (loai == 3) p = new BanGiamDoc(base, nhapDong("Cap quan ly (Giam doc/Truong phong/...): "));
    else                p = new NhanVien(base);
    ql->themNhanVien(d.dsNV, p);
    pb->themNhanVien(p);
    cout << "Da them nhan vien " << ma << ".\n";
}

static void menuQuanLyNhanVien(DuLieu& d, QuanLyNhanSu* ql, NhanVien* user) {
    while (true) {
        tieuDe("QUAN LY NHAN VIEN");
        cout << "1. Danh sach nhan vien\n2. Them nhan vien\n3. Sua thong tin\n"
                "4. Xoa nhan vien\n5. Tim theo ten\n6. Xem ho so chi tiet\n0. Quay lai\n";
        int c = nhapSo("Chon: ", 0, 6);
        if (c == 0) return;
        if (c == 1) inDanhSachNV(d);
        else if (c == 2) themNhanVien(d, ql);
        else if (c == 3) {
            string ma = nhapDong("Ma NV can sua: ");
            if (!ql->suaNhanVien(d.dsNV, ma)) cout << "Khong tim thay.\n";
            else cout << "Da cap nhat.\n";
        } else if (c == 4) {
            string ma = nhapDong("Ma NV can xoa: ");
            if (ma == user->getMaNV()) { cout << "Khong the tu xoa tai khoan dang dang nhap.\n"; continue; }
            if (!timNV(d, ma)) { cout << "Khong tim thay.\n"; continue; }
            for (PhongBan& pb : d.dsPB) pb.xoaNhanVien(ma);   // go con tro truoc khi delete
            ql->xoaNhanVien(d.dsNV, ma);
            cout << "Da xoa nhan vien " << ma << ".\n";
        } else if (c == 5) {
            auto kq = ql->timTheoTen(d.dsNV, nhapDong("Tu khoa: "));
            if (kq.empty()) cout << "Khong tim thay.\n";
            for (NhanVien* p : kq) cout << *p << "\n";
        } else if (c == 6) {
            NhanVien* p = timNV(d, nhapDong("Ma NV: "));
            if (p) p->xemThongTin();       // DA HINH: moi lop in thong tin rieng
            else cout << "Khong tim thay.\n";
        }
    }
}

static void menuPhongBan(DuLieu& d) {
    while (true) {
        tieuDe("QUAN LY PHONG BAN");
        cout << "1. Danh sach phong ban\n2. Xem nhan vien trong phong\n"
                "3. Chuyen nhan vien sang phong khac\n4. Them phong ban\n0. Quay lai\n";
        int c = nhapSo("Chon: ", 0, 4);
        if (c == 0) return;
        if (c == 1) for (const PhongBan& pb : d.dsPB) pb.hienThiThongTin();
        else if (c == 2) {
            PhongBan* pb = timPB(d, nhapDong("Ma phong ban: "));
            if (pb) { pb->hienThiThongTin(); pb->hienThiDanhSach(); }
            else cout << "Khong tim thay.\n";
        } else if (c == 3) {
            NhanVien* nv = timNV(d, nhapDong("Ma NV: "));
            if (!nv) { cout << "Khong tim thay nhan vien.\n"; continue; }
            PhongBan* moi = timPB(d, nhapDong("Ma phong ban moi: "));
            if (!moi) { cout << "Khong tim thay phong ban.\n"; continue; }
            PhongBan* cu = timPB(d, nv->getMaPB());
            if (cu) cu->xoaNhanVien(nv->getMaNV());
            moi->themNhanVien(nv);
            nv->setMaPB(moi->getMaPB());
            cout << "Da chuyen " << nv->getHoTen() << " sang " << moi->getTenPB() << ".\n";
        } else if (c == 4) {
            string ma = nhapDong("Ma phong ban: ");
            if (ma.empty() || timPB(d, ma)) { cout << "Ma rong hoac da ton tai.\n"; continue; }
            string ten = nhapDong("Ten phong ban: ");
            string mt = nhapDong("Mo ta: ");
            d.dsPB.emplace_back(ma, ten, mt);
            cout << "Da them phong ban.\n";
        }
    }
}

static void menuChamCong(DuLieu& d, QuanLyNhanSu* ql) {
    while (true) {
        tieuDe("CHAM CONG");
        cout << "1. Ghi nhan cong\n2. Xem cham cong cua mot nhan vien\n0. Quay lai\n";
        int c = nhapSo("Chon: ", 0, 2);
        if (c == 0) return;
        NhanVien* nv = timNV(d, nhapDong("Ma NV: "));
        if (!nv) { cout << "Khong tim thay nhan vien.\n"; continue; }
        if (c == 1) {
            string ngay = nhapNgay("Ngay (dd/mm/yyyy): ");
            string vao = nhapGio("Gio vao (HH:MM): ");
            string ra = nhapGio("Gio ra (HH:MM): ");
            if (ra <= vao) { cout << "Gio ra phai sau gio vao.\n"; continue; }
            ChamCong cc("CC" + nv->getMaNV() + "_" + ngay, nv->getMaNV(), ngay);
            cc.ghiNhanCong(vao, ra);
            ql->ghiNhanChamCong(d.dsCC, cc);
            cout << "Da ghi nhan: di muon " << cc.getDiMuon() << " phut, ve som " << cc.getVeSom()
                 << " phut, tang ca " << fixed << setprecision(1) << cc.getSoGioTangCa() << " gio.\n";
        } else {
            int thang = nhapSo("Thang: ", 1, 12), nam = nhapSo("Nam: ", 2000, 2100);
            cout << left << setw(12) << "Ngay" << setw(8) << "Vao" << setw(8) << "Ra"
                 << setw(10) << "Gio lam" << setw(10) << "Muon(p)" << setw(10) << "Som(p)" << "Tang ca(h)\n";
            int dem = 0;
            for (const ChamCong& cc : d.dsCC)
                if (cc.getMaNV() == nv->getMaNV() && cc.getThang() == thang && cc.getNam() == nam) {
                    cc.hienThi();
                    ++dem;
                }
            if (!dem) cout << "  Khong co du lieu.\n";
        }
    }
}

static void lapBangLuongTatCa(DuLieu& d, QuanLyNhanSu* ql) {
    tieuDe("LAP BANG LUONG");
    int thang = nhapSo("Thang (1-12): ", 1, 12), nam = nhapSo("Nam: ", 2000, 2100);
    cout << left << setw(8) << "Ma" << setw(24) << "Ho ten" << setw(12) << "Ngay cong" << "Thuc nhan\n";
    vector<BangLuong> ds;
    for (NhanVien* p : d.dsNV) {
        const ChucDanh* cd = timCD(d, p->getMaCD());
        if (!cd) continue;
        BangLuong bl = ql->lapBangLuong(*p, *cd, d.dsCC, thang, nam);
        cout << left << setw(8) << p->getMaNV() << setw(24) << p->getHoTen()
             << setw(12) << bl.getSoNgayCong() << dinhDangTien(bl.getThucNhan()) << "\n";
        ds.push_back(bl);
    }
    string ma = nhapDong("Nhap ma NV de xem phieu luong chi tiet (Enter de bo qua): ");
    for (const BangLuong& bl : ds)
        if (bl.getMaNV() == ma) { bl.inPhieuLuong(); return; }
}

static void thongKe(const DuLieu& d) {
    tieuDe("THONG KE");
    cout << "Tong so nhan vien: " << d.dsNV.size() << "\n";
    int ql = 0, bgd = 0, nv = 0;
    for (const NhanVien* p : d.dsNV) {
        if (dynamic_cast<const QuanLyNhanSu*>(p)) ++ql;
        else if (dynamic_cast<const BanGiamDoc*>(p)) ++bgd;
        else ++nv;
    }
    cout << "  Nhan vien: " << nv << " | Quan ly nhan su: " << ql << " | Ban giam doc: " << bgd << "\n";
    cout << "So nhan vien theo phong ban:\n";
    for (const PhongBan& pb : d.dsPB) cout << "  " << pb.getTenPB() << ": " << pb.soLuongNhanVien() << "\n";
    int cho = 0;
    for (const DonNghiPhep& dn : d.dsDon) if (dn.getTrangThai() == TrangThaiDon::ChoDuyet) ++cho;
    cout << "Don nghi phep dang cho duyet: " << cho << "\n";
}

// ---------------- Chuc nang Ban giam doc ----------------
static void duyetDon(DuLieu& d, BanGiamDoc* bgd) {
    tieuDe("DUYET DON NGHI PHEP");
    bgd->xemDonChoDuyet(d.dsDon);
    string ma = nhapDong("Nhap ma don can xu ly (Enter de bo qua): ");
    if (ma.empty()) return;
    for (DonNghiPhep& dn : d.dsDon) {
        if (dn.getMaDon() != ma) continue;
        NhanVien* nguoiGui = timNV(d, dn.getMaNV());
        if (!nguoiGui) { cout << "Khong tim thay nguoi gui.\n"; return; }
        int c = nhapSo("1 = Phe duyet, 2 = Tu choi: ", 1, 2);
        if (c == 1) {
            if (bgd->pheDuyetNghiPhep(dn, *nguoiGui))
                cout << "Da duyet. " << nguoiGui->getHoTen() << " con " << nguoiGui->soNgayPhepConLai() << " ngay phep.\n";
        } else {
            cout << (bgd->tuChoiNghiPhep(dn) ? "Da tu choi don.\n" : "Don nay da duoc xu ly.\n");
        }
        return;
    }
    cout << "Khong tim thay don.\n";
}

static void baoCaoLuong(DuLieu& d, BanGiamDoc* bgd) {
    tieuDe("BAO CAO QUY LUONG");
    int thang = nhapSo("Thang (1-12): ", 1, 12), nam = nhapSo("Nam: ", 2000, 2100);
    vector<BangLuong> ds;
    for (NhanVien* p : d.dsNV) {
        const ChucDanh* cd = timCD(d, p->getMaCD());
        if (!cd) continue;
        BangLuong bl("BL" + p->getMaNV(), p->getMaNV(), thang, nam);
        bl.tinhLuong(*p, *cd, d.dsCC);
        ds.push_back(bl);
    }
    bgd->xemBaoCaoLuong(ds);
}

// ---------------- Phien lam viec sau khi dang nhap ----------------
static void phienLamViec(DuLieu& d, NhanVien* user) {
    QuanLyNhanSu* ql = dynamic_cast<QuanLyNhanSu*>(user);
    BanGiamDoc* bgd = dynamic_cast<BanGiamDoc*>(user);
    while (true) {
        tieuDe("HRMS - " + user->getHoTen() + " (" + user->vaiTro() + ")");
        cout << "1. Xem thong tin ca nhan\n2. Xem bang luong cua toi\n"
                "3. Gui don nghi phep\n4. Xem don nghi phep cua toi\n";
        int toiDa = 4;
        if (ql) {
            cout << "5. Quan ly nhan vien\n6. Quan ly phong ban\n7. Cham cong\n"
                    "8. Lap bang luong\n9. Thong ke\n";
            toiDa = 9;
        } else if (bgd) {
            cout << "5. Duyet don nghi phep\n6. Bao cao quy luong\n7. Danh sach nhan vien\n";
            toiDa = 7;
        }
        cout << "0. Dang xuat\n";
        int c = nhapSo("Chon: ", 0, toiDa);
        if (c == 0) return;
        if (c == 1) user->xemThongTin();
        else if (c == 2) xemBangLuongCuaToi(d, user);
        else if (c == 3) guiDonNghiPhep(d, user);
        else if (c == 4) xemDonCuaToi(d, user);
        else if (ql) {
            if (c == 5) menuQuanLyNhanVien(d, ql, user);
            else if (c == 6) menuPhongBan(d);
            else if (c == 7) menuChamCong(d, ql);
            else if (c == 8) lapBangLuongTatCa(d, ql);
            else if (c == 9) thongKe(d);
        } else if (bgd) {
            if (c == 5) duyetDon(d, bgd);
            else if (c == 6) baoCaoLuong(d, bgd);
            else if (c == 7) { tieuDe("DANH SACH NHAN VIEN"); inDanhSachNV(d); }
        }
    }
}

int main() {
    DuLieu d;
    docDuLieu(d);
    if (d.dsNV.empty()) {
        cout << "Chua co du lieu, nap du lieu mau...\n";
        d.dsCD.clear(); d.dsPB.clear(); d.dsCC.clear(); d.dsDon.clear();
        taoDuLieuMau(d);
    }
    cout << "=========================================\n"
            "   HE THONG QUAN LY NHAN SU (HRMS)\n"
            "=========================================\n";
    while (true) {
        cout << "\nMa nhan vien mau: NV001 (Quan ly nhan su), NV002/NV005 (Ban giam doc), NV003/NV004 (Nhan vien)\n";
        string ma = nhapDong("Dang nhap - nhap ma nhan vien (Enter de thoat): ");
        if (ma.empty()) break;
        NhanVien* user = timNV(d, ma);
        if (!user) { cout << "Khong tim thay ma nhan vien.\n"; continue; }
        phienLamViec(d, user);
    }
    luuDuLieu(d);
    cout << "Tam biet!\n";
    return 0;
}
