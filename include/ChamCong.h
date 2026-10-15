#pragma once
#include <string>

// Một bản ghi chấm công của 1 nhân viên trong 1 ngày.
// Giờ lưu dạng "HH:MM"; số phút đi muộn / về sớm / tăng ca tự tính từ ca chuẩn.
class ChamCong {
private:
    std::string maCC, maNV, ngay;       // ngày: "dd/mm/yyyy"
    std::string gioVao, gioRa;          // "HH:MM"
    double soGioTangCa;
    int diMuon, veSom;                  // đơn vị: phút

    static int chuyenPhut(const std::string& hhmm);  // "08:30" -> 510

public:
    static constexpr int GIO_VAO_CHUAN = 8 * 60;   // 08:00
    static constexpr int GIO_RA_CHUAN  = 17 * 60;  // 17:00

    ChamCong();
    ChamCong(const std::string& maCC, const std::string& maNV, const std::string& ngay);

    std::string getMaNV() const;
    std::string getNgay() const;
    int getThang() const;               // tách từ chuỗi ngày
    int getNam() const;
    double getSoGioTangCa() const;
    int getDiMuon() const;
    int getVeSom() const;

    void ghiNhanCong(const std::string& gioVao, const std::string& gioRa);  // tự tính muộn/sớm/tăng ca
    double tinhGioLam() const;          // trừ 1 giờ nghỉ trưa nếu làm trên 5 giờ

    void hienThi() const;
    std::string toFileString() const;
};
