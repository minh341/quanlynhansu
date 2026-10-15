#include "ChucDanh.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

string dinhDangTien(double so) {
    long long v = llround(so);
    string s = to_string(llabs(v));
    for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert(i, ",");
    return (v < 0 ? "-" : "") + s;
}

ChucDanh::ChucDanh() : luongCoBan(0), phuCapChucDanh(0) {}
ChucDanh::ChucDanh(const string& maCD, const string& tenCD, double luongCoBan, double phuCapChucDanh)
    : maCD(maCD), tenCD(tenCD), luongCoBan(luongCoBan), phuCapChucDanh(phuCapChucDanh) {}

string ChucDanh::getMaCD() const { return maCD; }
string ChucDanh::getTenCD() const { return tenCD; }
double ChucDanh::getLuongCoBan() const { return luongCoBan; }
double ChucDanh::getPhuCap() const { return phuCapChucDanh; }
void ChucDanh::setTenCD(const string& ten) { tenCD = ten; }
void ChucDanh::setLuongCoBan(double luong) { luongCoBan = luong; }
void ChucDanh::setPhuCap(double pc) { phuCapChucDanh = pc; }

void ChucDanh::hienThi() const {
    cout << maCD << " - " << tenCD << " | Luong co ban: " << dinhDangTien(luongCoBan)
         << " | Phu cap: " << dinhDangTien(phuCapChucDanh) << "\n";
}

string ChucDanh::toFileString() const {
    return maCD + "|" + tenCD + "|" + to_string((long long)llround(luongCoBan)) + "|" +
           to_string((long long)llround(phuCapChucDanh));
}
