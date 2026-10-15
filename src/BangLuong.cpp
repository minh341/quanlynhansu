#include "BangLuong.h"
#include <iostream>
using namespace std;

static const double TL_BHXH = 0.08, TL_BHYT = 0.015, TL_BHTN = 0.01;
static const double HE_SO_TANG_CA = 1.5;

BangLuong::BangLuong()
    : thang(0), nam(0), soNgayCong(0), luongCoBan(0), phuCap(0), tienTangCa(0),
      bhxh(0), bhyt(0), bhtn(0), thueTNCN(0), thucNhan(0) {}

BangLuong::BangLuong(const string& maBL, const string& maNV, int thang, int nam)
    : maBL(maBL), maNV(maNV), thang(thang), nam(nam), soNgayCong(0), luongCoBan(0),
      phuCap(0), tienTangCa(0), bhxh(0), bhyt(0), bhtn(0), thueTNCN(0), thucNhan(0) {}

string BangLuong::getMaNV() const { return maNV; }
int BangLuong::getThang() const { return thang; }
int BangLuong::getNam() const { return nam; }
int BangLuong::getSoNgayCong() const { return soNgayCong; }
double BangLuong::getThucNhan() const { return thucNhan; }

// Thuế lũy tiến từng phần (7 bậc: 5%,10%,15%,20%,25%,30%,35%)
double BangLuong::tinhThueTNCN(double t) const {
    if (t <= 0) return 0;
    const double moc[6] = {5e6, 10e6, 18e6, 32e6, 52e6, 80e6};
    const double suat[7] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35};
    double thue = 0, truoc = 0;
    for (int i = 0; i < 6; ++i) {
        if (t <= moc[i]) return thue + (t - truoc) * suat[i];
        thue += (moc[i] - truoc) * suat[i];
        truoc = moc[i];
    }
    return thue + (t - truoc) * suat[6];
}

void BangLuong::tinhLuong(const NhanVien& nv, const ChucDanh& cd, const vector<ChamCong>& dsCC) {
    double luongHD = cd.getLuongCoBan();
    double gioTangCa = 0;
    soNgayCong = 0;
    for (const ChamCong& cc : dsCC) {
        if (cc.getMaNV() == nv.getMaNV() && cc.getThang() == thang && cc.getNam() == nam) {
            ++soNgayCong;
            gioTangCa += cc.getSoGioTangCa();
        }
    }
    if (soNgayCong > NGAY_CONG_CHUAN) soNgayCong = NGAY_CONG_CHUAN;
    if (soNgayCong == 0) {  // không có công -> không có lương
        luongCoBan = phuCap = tienTangCa = bhxh = bhyt = bhtn = thueTNCN = thucNhan = 0;
        return;
    }

    luongCoBan = luongHD * soNgayCong / NGAY_CONG_CHUAN;
    phuCap = cd.getPhuCap() + nv.tinhPhuCapQuanLy();   // ĐA HÌNH: tuỳ loại nhân viên
    tienTangCa = gioTangCa * (luongHD / NGAY_CONG_CHUAN / 8.0) * HE_SO_TANG_CA;
    bhxh = luongHD * TL_BHXH;
    bhyt = luongHD * TL_BHYT;
    bhtn = luongHD * TL_BHTN;

    double chiuThue = luongCoBan + phuCap + tienTangCa - (bhxh + bhyt + bhtn) - GIAM_TRU_BAN_THAN;
    thueTNCN = tinhThueTNCN(chiuThue);
    thucNhan = luongCoBan + phuCap + tienTangCa - (bhxh + bhyt + bhtn) - thueTNCN;
}

void BangLuong::inPhieuLuong() const {
    cout << "============ PHIEU LUONG " << thang << "/" << nam << " ============\n"
         << "Ma nhan vien    : " << maNV << "\n"
         << "So ngay cong    : " << soNgayCong << "/" << NGAY_CONG_CHUAN << "\n"
         << "Luong co ban    : " << dinhDangTien(luongCoBan) << "\n"
         << "Phu cap         : " << dinhDangTien(phuCap) << "\n"
         << "Tien tang ca    : " << dinhDangTien(tienTangCa) << "\n"
         << "BHXH (8%)       : -" << dinhDangTien(bhxh) << "\n"
         << "BHYT (1.5%)     : -" << dinhDangTien(bhyt) << "\n"
         << "BHTN (1%)       : -" << dinhDangTien(bhtn) << "\n"
         << "Thue TNCN       : " << (thueTNCN > 0 ? "-" : "") << dinhDangTien(thueTNCN) << "\n"
         << "---------------------------------------\n"
         << "THUC NHAN       : " << dinhDangTien(thucNhan) << " VND\n";
}

string BangLuong::toFileString() const {
    return maBL + "|" + maNV + "|" + to_string(thang) + "|" + to_string(nam) + "|" +
           to_string((long long)thucNhan);
}
