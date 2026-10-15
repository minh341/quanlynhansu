#include "PhongBan.h"
#include <iostream>
using namespace std;

PhongBan::PhongBan() {}
PhongBan::PhongBan(const string& maPB, const string& tenPB, const string& moTa)
    : maPB(maPB), tenPB(tenPB), moTa(moTa) {}

string PhongBan::getMaPB() const { return maPB; }
string PhongBan::getTenPB() const { return tenPB; }
void PhongBan::setTenPB(const string& ten) { tenPB = ten; }
void PhongBan::setMoTa(const string& mt) { moTa = mt; }

bool PhongBan::themNhanVien(NhanVien* nv) {
    if (nv == nullptr) return false;
    for (NhanVien* p : dsNhanVien)
        if (p->getMaNV() == nv->getMaNV()) return false;
    dsNhanVien.push_back(nv);
    return true;
}

bool PhongBan::xoaNhanVien(const string& maNV) {
    for (size_t i = 0; i < dsNhanVien.size(); ++i) {
        if (dsNhanVien[i]->getMaNV() == maNV) {
            dsNhanVien.erase(dsNhanVien.begin() + i);  // chỉ gỡ con trỏ, không delete
            return true;
        }
    }
    return false;
}

int PhongBan::soLuongNhanVien() const { return (int)dsNhanVien.size(); }

void PhongBan::hienThiDanhSach() const {
    if (dsNhanVien.empty()) { cout << "  (Phong chua co nhan vien)\n"; return; }
    for (const NhanVien* p : dsNhanVien) cout << "  " << *p << "\n";  // gọi vaiTro() ảo
}

void PhongBan::hienThiThongTin() const {
    cout << maPB << " - " << tenPB << " (" << soLuongNhanVien() << " nhan vien) - " << moTa << "\n";
}

string PhongBan::toFileString() const { return maPB + "|" + tenPB + "|" + moTa; }
