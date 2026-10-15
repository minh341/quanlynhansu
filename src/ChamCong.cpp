#include "ChamCong.h"
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;

ChamCong::ChamCong() : soGioTangCa(0), diMuon(0), veSom(0) {}
ChamCong::ChamCong(const string& maCC, const string& maNV, const string& ngay)
    : maCC(maCC), maNV(maNV), ngay(ngay), soGioTangCa(0), diMuon(0), veSom(0) {}

int ChamCong::chuyenPhut(const string& hhmm) {
    int h = 0, m = 0;
    sscanf(hhmm.c_str(), "%d:%d", &h, &m);
    return h * 60 + m;
}

string ChamCong::getMaNV() const { return maNV; }
string ChamCong::getNgay() const { return ngay; }
int ChamCong::getThang() const { return ngay.size() >= 5 ? atoi(ngay.substr(3, 2).c_str()) : 0; }
int ChamCong::getNam() const { return ngay.size() >= 10 ? atoi(ngay.substr(6, 4).c_str()) : 0; }
double ChamCong::getSoGioTangCa() const { return soGioTangCa; }
int ChamCong::getDiMuon() const { return diMuon; }
int ChamCong::getVeSom() const { return veSom; }

void ChamCong::ghiNhanCong(const string& gv, const string& gr) {
    gioVao = gv;
    gioRa = gr;
    int vao = chuyenPhut(gv), ra = chuyenPhut(gr);
    diMuon = vao > GIO_VAO_CHUAN ? vao - GIO_VAO_CHUAN : 0;
    veSom = ra < GIO_RA_CHUAN ? GIO_RA_CHUAN - ra : 0;
    soGioTangCa = ra > GIO_RA_CHUAN ? (ra - GIO_RA_CHUAN) / 60.0 : 0.0;
}

double ChamCong::tinhGioLam() const {
    if (gioVao.empty() || gioRa.empty()) return 0;
    double h = (chuyenPhut(gioRa) - chuyenPhut(gioVao)) / 60.0;
    if (h > 5) h -= 1;  // nghỉ trưa
    return h < 0 ? 0 : h;
}

void ChamCong::hienThi() const {
    cout << left << setw(12) << ngay << setw(8) << gioVao << setw(8) << gioRa
         << setw(10) << fixed << setprecision(1) << tinhGioLam()
         << setw(10) << diMuon << setw(10) << veSom << soGioTangCa << "\n";
}

string ChamCong::toFileString() const {
    return maCC + "|" + maNV + "|" + ngay + "|" + gioVao + "|" + gioRa;
}
