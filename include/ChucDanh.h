#pragma once
#include <string>

// Hàm tiện ích dùng chung: 12345678 -> "12,345,678"
std::string dinhDangTien(double so);

class ChucDanh {
private:
    std::string maCD, tenCD;
    double luongCoBan;       // lương cơ bản theo hợp đồng (tháng)
    double phuCapChucDanh;

public:
    ChucDanh();
    ChucDanh(const std::string& maCD, const std::string& tenCD,
             double luongCoBan, double phuCapChucDanh);

    std::string getMaCD() const;
    std::string getTenCD() const;
    double getLuongCoBan() const;
    double getPhuCap() const;
    void setTenCD(const std::string& ten);
    void setLuongCoBan(double luong);
    void setPhuCap(double pc);

    void hienThi() const;
    std::string toFileString() const;
};
