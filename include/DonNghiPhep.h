#pragma once
#include <string>

enum class TrangThaiDon { ChoDuyet, DaDuyet, TuChoi };

// Đơn xin nghỉ phép: nhân viên gửi -> Ban Giám đốc duyệt / từ chối.
class DonNghiPhep {
private:
    std::string maDon, maNV, loaiPhep;
    std::string tuNgay, denNgay, lyDo;   // "dd/mm/yyyy"
    int soNgay;
    TrangThaiDon trangThai;

public:
    DonNghiPhep();
    DonNghiPhep(const std::string& maDon, const std::string& maNV, const std::string& loaiPhep,
                const std::string& tuNgay, const std::string& denNgay, int soNgay,
                const std::string& lyDo);

    std::string getMaDon() const;
    std::string getMaNV() const;
    int getSoNgay() const;
    TrangThaiDon getTrangThai() const;
    void setTrangThai(TrangThaiDon tt);
    std::string trangThaiString() const;

    void guiDon();                 // đặt trạng thái = ChoDuyet
    bool pheDuyet();               // chỉ duyệt được khi đang ChoDuyet
    bool tuChoi();

    void hienThi() const;
    std::string toFileString() const;
};
