#include "DonNghiPhep.h"
#include <iostream>
using namespace std;

DonNghiPhep::DonNghiPhep() : soNgay(0), trangThai(TrangThaiDon::ChoDuyet) {}
DonNghiPhep::DonNghiPhep(const string& maDon, const string& maNV, const string& loaiPhep,
                         const string& tuNgay, const string& denNgay, int soNgay, const string& lyDo)
    : maDon(maDon), maNV(maNV), loaiPhep(loaiPhep), tuNgay(tuNgay), denNgay(denNgay),
      lyDo(lyDo), soNgay(soNgay), trangThai(TrangThaiDon::ChoDuyet) {}

string DonNghiPhep::getMaDon() const { return maDon; }
string DonNghiPhep::getMaNV() const { return maNV; }
int DonNghiPhep::getSoNgay() const { return soNgay; }
TrangThaiDon DonNghiPhep::getTrangThai() const { return trangThai; }
void DonNghiPhep::setTrangThai(TrangThaiDon tt) { trangThai = tt; }

string DonNghiPhep::trangThaiString() const {
    switch (trangThai) {
        case TrangThaiDon::ChoDuyet: return "Cho duyet";
        case TrangThaiDon::DaDuyet:  return "Da duyet";
        default:                     return "Tu choi";
    }
}

void DonNghiPhep::guiDon() { trangThai = TrangThaiDon::ChoDuyet; }

bool DonNghiPhep::pheDuyet() {
    if (trangThai != TrangThaiDon::ChoDuyet) return false;
    trangThai = TrangThaiDon::DaDuyet;
    return true;
}

bool DonNghiPhep::tuChoi() {
    if (trangThai != TrangThaiDon::ChoDuyet) return false;
    trangThai = TrangThaiDon::TuChoi;
    return true;
}

void DonNghiPhep::hienThi() const {
    cout << "  [" << maDon << "] NV " << maNV << " | " << loaiPhep << " | " << tuNgay << " -> "
         << denNgay << " (" << soNgay << " ngay) | Ly do: " << lyDo
         << " | " << trangThaiString() << "\n";
}

string DonNghiPhep::toFileString() const {
    return maDon + "|" + maNV + "|" + loaiPhep + "|" + tuNgay + "|" + denNgay + "|" +
           to_string(soNgay) + "|" + lyDo + "|" + to_string((int)trangThai);
}
