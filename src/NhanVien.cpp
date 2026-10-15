#include "NhanVien.h"
#include <iomanip>
using namespace std;

NhanVien::NhanVien()
    : trangThai("Dang lam"), soNgayPhepNam(12), soNgayPhepDaDung(0) {}

NhanVien::NhanVien(const string& maNV, const string& hoTen, const string& ngaySinh,
                   const string& gioiTinh, const string& cccd, const string& diaChi,
                   const string& soDienThoai, const string& email, const string& ngayVaoLam,
                   const string& maPB, const string& maCD)
    : maNV(maNV), hoTen(hoTen), ngaySinh(ngaySinh), gioiTinh(gioiTinh), cccd(cccd),
      diaChi(diaChi), soDienThoai(soDienThoai), email(email), ngayVaoLam(ngayVaoLam),
      trangThai("Dang lam"), maPB(maPB), maCD(maCD), soNgayPhepNam(12), soNgayPhepDaDung(0) {}

NhanVien::~NhanVien() {}

// ---- Getter ----
string NhanVien::getMaNV() const { return maNV; }
string NhanVien::getHoTen() const { return hoTen; }
string NhanVien::getMaPB() const { return maPB; }
string NhanVien::getMaCD() const { return maCD; }
string NhanVien::getTrangThai() const { return trangThai; }
int NhanVien::getSoNgayPhepNam() const { return soNgayPhepNam; }
int NhanVien::soNgayPhepConLai() const { return soNgayPhepNam - soNgayPhepDaDung; }

// ---- Setter ----
void NhanVien::setHoTen(const string& ten) { hoTen = ten; }
void NhanVien::setDiaChi(const string& dc) { diaChi = dc; }
void NhanVien::setSoDienThoai(const string& sdt) { soDienThoai = sdt; }
void NhanVien::setEmail(const string& mail) { email = mail; }
void NhanVien::setMaPB(const string& ma) { maPB = ma; }
void NhanVien::setMaCD(const string& ma) { maCD = ma; }
void NhanVien::setTrangThai(const string& tt) { trangThai = tt; }
void NhanVien::setSoNgayPhepNam(int n) { soNgayPhepNam = n; }
void NhanVien::setSoNgayPhepDaDung(int n) { soNgayPhepDaDung = n; }

// ---- Nghiệp vụ ----
bool NhanVien::truPhep(int soNgay) {
    if (soNgay <= 0 || soNgay > soNgayPhepConLai()) return false;
    soNgayPhepDaDung += soNgay;
    return true;
}

// ---- Đa hình ----
void NhanVien::xemThongTin() const {
    cout << "----------- HO SO NHAN VIEN -----------\n"
         << "Ma NV          : " << maNV << "\n"
         << "Ho ten         : " << hoTen << "\n"
         << "Vai tro        : " << vaiTro() << "\n"
         << "Ngay sinh      : " << ngaySinh << "\n"
         << "Gioi tinh      : " << gioiTinh << "\n"
         << "CCCD           : " << cccd << "\n"
         << "Dia chi        : " << diaChi << "\n"
         << "So dien thoai  : " << soDienThoai << "\n"
         << "Email          : " << email << "\n"
         << "Ngay vao lam   : " << ngayVaoLam << "\n"
         << "Trang thai     : " << trangThai << "\n"
         << "Phong ban      : " << maPB << "\n"
         << "Chuc danh      : " << maCD << "\n"
         << "Phep con lai   : " << soNgayPhepConLai() << "/" << soNgayPhepNam << " ngay\n";
}

string NhanVien::vaiTro() const { return "Nhan vien"; }
double NhanVien::tinhPhuCapQuanLy() const { return 0; }

// ---- File ----
string NhanVien::truongCoBan() const {
    return maNV + "|" + hoTen + "|" + ngaySinh + "|" + gioiTinh + "|" + cccd + "|" +
           diaChi + "|" + soDienThoai + "|" + email + "|" + ngayVaoLam + "|" + trangThai + "|" +
           maPB + "|" + maCD + "|" + to_string(soNgayPhepNam) + "|" + to_string(soNgayPhepDaDung);
}

string NhanVien::toFileString() const { return "NV|" + truongCoBan(); }

ostream& operator<<(ostream& os, const NhanVien& nv) {
    os << left << setw(8) << nv.maNV << setw(24) << nv.hoTen << setw(18) << nv.vaiTro()
       << setw(8) << nv.maPB << setw(8) << nv.maCD << nv.trangThai;
    return os;
}
