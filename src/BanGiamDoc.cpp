#include "BanGiamDoc.h"
#include <iomanip>
using namespace std;

BanGiamDoc::BanGiamDoc() {}
BanGiamDoc::BanGiamDoc(const NhanVien& nv, const string& capQuanLy)
    : NhanVien(nv), capQuanLy(capQuanLy) {}

string BanGiamDoc::getCapQuanLy() const { return capQuanLy; }
void BanGiamDoc::setCapQuanLy(const string& cap) { capQuanLy = cap; }

void BanGiamDoc::xemThongTin() const {
    NhanVien::xemThongTin();
    cout << "Cap quan ly    : " << capQuanLy << "\n";
}
string BanGiamDoc::vaiTro() const { return "Ban giam doc"; }

double BanGiamDoc::tinhPhuCapQuanLy() const {
    if (capQuanLy == "Giam doc") return 10000000;
    if (capQuanLy == "Truong phong") return 5000000;
    return 3000000;
}
string BanGiamDoc::toFileString() const { return "BGD|" + truongCoBan() + "|" + capQuanLy; }

bool BanGiamDoc::pheDuyetNghiPhep(DonNghiPhep& don, NhanVien& nguoiGui) {
    if (don.getMaNV() != nguoiGui.getMaNV()) {
        cout << "  Don khong thuoc nhan vien nay.\n";
        return false;
    }
    if (nguoiGui.getMaNV() == getMaNV()) {
        cout << "  Khong the tu duyet don cua chinh minh.\n";
        return false;
    }
    if (don.getTrangThai() != TrangThaiDon::ChoDuyet) {
        cout << "  Don nay da duoc xu ly.\n";
        return false;
    }
    if (nguoiGui.soNgayPhepConLai() < don.getSoNgay()) {
        cout << "  Khong du phep: con " << nguoiGui.soNgayPhepConLai()
             << " ngay, xin " << don.getSoNgay() << " ngay.\n";
        return false;
    }
    don.pheDuyet();
    nguoiGui.truPhep(don.getSoNgay());
    return true;
}

bool BanGiamDoc::tuChoiNghiPhep(DonNghiPhep& don) { return don.tuChoi(); }

void BanGiamDoc::xemDonChoDuyet(const vector<DonNghiPhep>& dsDon) const {
    int dem = 0;
    for (const DonNghiPhep& d : dsDon) {
        if (d.getTrangThai() == TrangThaiDon::ChoDuyet) {
            d.hienThi();
            ++dem;
        }
    }
    if (dem == 0) cout << "  Khong co don nao dang cho duyet.\n";
}

void BanGiamDoc::xemBaoCaoLuong(const vector<BangLuong>& dsBL) const {
    double tong = 0;
    int soNguoi = 0;
    cout << left << setw(10) << "Ma NV" << setw(12) << "Ngay cong" << "Thuc nhan\n";
    for (const BangLuong& bl : dsBL) {
        if (bl.getSoNgayCong() == 0) continue;
        cout << left << setw(10) << bl.getMaNV() << setw(12) << bl.getSoNgayCong()
             << dinhDangTien(bl.getThucNhan()) << "\n";
        tong += bl.getThucNhan();
        ++soNguoi;
    }
    cout << "So nhan vien co cong : " << soNguoi << "\n"
         << "Tong quy luong       : " << dinhDangTien(tong) << " VND\n";
}
