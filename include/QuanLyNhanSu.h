#pragma once
#include "NhanVien.h"
#include "BangLuong.h"
#include "ChamCong.h"
#include "ChucDanh.h"
#include <vector>

// KẾ THỪA công khai từ NhanVien, bổ sung quyền quản trị hồ sơ/chấm công/lương.
class QuanLyNhanSu : public NhanVien {
private:
    std::string chuyenMon;

public:
    QuanLyNhanSu();
    QuanLyNhanSu(const NhanVien& nv, const std::string& chuyenMon);

    std::string getChuyenMon() const;
    void setChuyenMon(const std::string& cm);

    // ---- Ghi đè (đa hình) ----
    void xemThongTin() const override;
    std::string vaiTro() const override;
    double tinhPhuCapQuanLy() const override;
    std::string toFileString() const override;

    // ---- Quản lý hồ sơ nhân viên (CRUD trên danh sách dùng chung) ----
    bool themNhanVien(std::vector<NhanVien*>& ds, NhanVien* nv);
    bool suaNhanVien(std::vector<NhanVien*>& ds, const std::string& maNV);
    bool xoaNhanVien(std::vector<NhanVien*>& ds, const std::string& maNV);
    NhanVien* timNhanVien(const std::vector<NhanVien*>& ds, const std::string& maNV) const;
    std::vector<NhanVien*> timTheoTen(const std::vector<NhanVien*>& ds, const std::string& tuKhoa) const;

    // ---- Chấm công & lương ----
    void ghiNhanChamCong(std::vector<ChamCong>& dsCC, const ChamCong& cc);
    BangLuong lapBangLuong(const NhanVien& nv, const ChucDanh& cd,
                           const std::vector<ChamCong>& dsCC, int thang, int nam) const;
};
