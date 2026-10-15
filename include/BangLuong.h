#pragma once
#include <string>
#include <vector>
#include "NhanVien.h"
#include "ChucDanh.h"
#include "ChamCong.h"

// Bảng lương tháng của 1 nhân viên.
//   luongCoBan  = lương hợp đồng * soNgayCong / 26
//   tienTangCa  = giờ tăng ca * (lương hợp đồng / 26 / 8) * 1.5
//   thucNhan    = luongCoBan + phuCap + tienTangCa - (bhxh + bhyt + bhtn) - thueTNCN
class BangLuong {
private:
    std::string maBL, maNV;
    int thang, nam, soNgayCong;
    double luongCoBan, phuCap, tienTangCa;
    double bhxh, bhyt, bhtn, thueTNCN, thucNhan;

    double tinhThueTNCN(double thuNhapChiuThue) const;  // biểu thuế lũy tiến từng phần

public:
    static constexpr int NGAY_CONG_CHUAN = 26;
    static constexpr double GIAM_TRU_BAN_THAN = 11000000;  // chỉnh theo quy định hiện hành

    BangLuong();
    BangLuong(const std::string& maBL, const std::string& maNV, int thang, int nam);

    std::string getMaNV() const;
    int getThang() const;
    int getNam() const;
    int getSoNgayCong() const;
    double getThucNhan() const;

    // Tổng hợp từ nhân viên (phụ cấp quản lý - đa hình), chức danh và dữ liệu chấm công
    void tinhLuong(const NhanVien& nv, const ChucDanh& cd, const std::vector<ChamCong>& dsCC);

    void inPhieuLuong() const;
    std::string toFileString() const;
};
