#pragma once
#include <string>
#include <vector>
#include "NhanVien.h"

// Quan hệ TẬP HỢP (aggregation) với NhanVien: phòng ban chứa danh sách
// con trỏ tới nhân viên nhưng KHÔNG sở hữu (không delete khi phòng ban bị xoá).
class PhongBan {
private:
    std::string maPB, tenPB, moTa;
    std::vector<NhanVien*> dsNhanVien;

public:
    PhongBan();
    PhongBan(const std::string& maPB, const std::string& tenPB, const std::string& moTa);

    std::string getMaPB() const;
    std::string getTenPB() const;
    void setTenPB(const std::string& ten);
    void setMoTa(const std::string& mt);

    bool themNhanVien(NhanVien* nv);
    bool xoaNhanVien(const std::string& maNV);
    int soLuongNhanVien() const;
    void hienThiDanhSach() const;
    void hienThiThongTin() const;
    std::string toFileString() const;
};
