#pragma once
#include "NhanVien.h"
#include "DonNghiPhep.h"
#include "BangLuong.h"
#include <vector>

// KẾ THỪA công khai từ NhanVien, có quyền phê duyệt nghỉ phép và xem báo cáo.
class BanGiamDoc : public NhanVien {
private:
    std::string capQuanLy;  // ví dụ: "Truong phong", "Giam doc"

public:
    BanGiamDoc();
    BanGiamDoc(const NhanVien& nv, const std::string& capQuanLy);

    std::string getCapQuanLy() const;
    void setCapQuanLy(const std::string& cap);

    // ---- Ghi đè (đa hình) ----
    void xemThongTin() const override;
    std::string vaiTro() const override;
    double tinhPhuCapQuanLy() const override;
    std::string toFileString() const override;

    // ---- Nghiệp vụ ----
    // Duyệt đơn: đổi trạng thái đơn + trừ phép của người gửi
    bool pheDuyetNghiPhep(DonNghiPhep& don, NhanVien& nguoiGui);
    bool tuChoiNghiPhep(DonNghiPhep& don);
    void xemDonChoDuyet(const std::vector<DonNghiPhep>& dsDon) const;
    void xemBaoCaoLuong(const std::vector<BangLuong>& dsBL) const;  // tổng quỹ lương
};
