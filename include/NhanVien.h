#pragma once
#include <string>
#include <iostream>

// Lớp cha của hệ thống. Thể hiện ĐÓNG GÓI (thuộc tính protected + getter/setter)
// và là gốc của cây KẾ THỪA: NhanVien <- QuanLyNhanSu, BanGiamDoc.
class NhanVien {
protected:
    std::string maNV, hoTen, ngaySinh, gioiTinh, cccd;
    std::string diaChi, soDienThoai, email, ngayVaoLam, trangThai;
    std::string maPB;   // phòng ban đang thuộc về (liên kết bằng mã)
    std::string maCD;   // chức danh đang giữ
    int soNgayPhepNam;  // quỹ phép năm
    int soNgayPhepDaDung;

    std::string truongCoBan() const;  // các trường chung, ngăn bằng '|' (dùng cho toFileString)

public:
    NhanVien();
    NhanVien(const std::string& maNV, const std::string& hoTen,
             const std::string& ngaySinh, const std::string& gioiTinh,
             const std::string& cccd, const std::string& diaChi,
             const std::string& soDienThoai, const std::string& email,
             const std::string& ngayVaoLam, const std::string& maPB,
             const std::string& maCD);
    virtual ~NhanVien();  // destructor ảo: bắt buộc khi xoá qua con trỏ lớp cha

    // ---- Getter ----
    std::string getMaNV() const;
    std::string getHoTen() const;
    std::string getMaPB() const;
    std::string getMaCD() const;
    std::string getTrangThai() const;
    int getSoNgayPhepNam() const;
    int soNgayPhepConLai() const;

    // ---- Setter ----
    void setHoTen(const std::string& ten);
    void setDiaChi(const std::string& dc);
    void setSoDienThoai(const std::string& sdt);
    void setEmail(const std::string& mail);
    void setMaPB(const std::string& ma);
    void setMaCD(const std::string& ma);
    void setTrangThai(const std::string& tt);
    void setSoNgayPhepNam(int n);
    void setSoNgayPhepDaDung(int n);

    // ---- Nghiệp vụ ----
    bool truPhep(int soNgay);  // false nếu không đủ phép

    // ---- ĐA HÌNH: lớp con ghi đè ----
    virtual void xemThongTin() const;          // in hồ sơ
    virtual std::string vaiTro() const;        // "Nhan vien" / "Quan ly nhan su" / ...
    virtual double tinhPhuCapQuanLy() const;   // mặc định 0, lớp con ghi đè

    // ---- Lưu/đọc file ----
    virtual std::string toFileString() const;  // 1 dòng, các trường ngăn bằng '|'
    friend std::ostream& operator<<(std::ostream& os, const NhanVien& nv);
};
