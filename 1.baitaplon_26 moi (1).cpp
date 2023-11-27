#include <iostream>
#include <cstring>
#include <iomanip>

const float GIA_TIEN_TIN_CHI = 365500;

struct SinhVien {
    int id;
    char maSV[11]; 
    char ten[30];
    char gioiTinh[5];
    int tuoi;
    float diemmon1;
    float diemmon2;
    float diemmon3;
    float diemTB = 0;
    int soTinChi;
    float hocPhi = 0;
    char hocluc[10] = "-";
    SinhVien* next;  
};

typedef SinhVien SV;

void themSinhVien(SV*& head, int& idCount);
void hienThiDanhSach(const SV* head);
void xoaSinhVien(SV*& head, const char* maSV);
void sapXepTangDan(SV*& head);
void sapXepGiamDan(SV*& head);
void giaiPhongDanhSach(SV*& head);

void themSinhVien(SV*& head, int& idCount) {
    SV* newSV = new SV;
    newSV->next = NULL;

    std::cout << "\n Nhap ma so sinh vien: ";
    std::cin.ignore();
    std::cin.getline(newSV->maSV, 11);  
    std::cout << " Nhap ten: ";
    std::cin.getline(newSV->ten, 30);
    std::cout << " Nhap gioi tinh: ";
    std::cin.getline(newSV->gioiTinh, 5);
    std::cout << " Nhap tuoi: ";
    std::cin >> newSV->tuoi;
    std::cout << " Nhap diem mon1: ";
    std::cin >> newSV->diemmon1;
    std::cout << " Nhap diem mon2: ";
    std::cin >> newSV->diemmon2;
    std::cout << " Nhap diem mon3: ";
    std::cin >> newSV->diemmon3;
    std::cout << " Nhap so tin chi: ";
    std::cin >> newSV->soTinChi;

    newSV->id = ++idCount;
    
    // Cập nhật điểm trung bình và xếp loại
    newSV->diemTB = (newSV->diemmon1 + newSV->diemmon2 + newSV->diemmon3) / 3;
    if (newSV->diemTB >= 8) strcpy(newSV->hocluc, "Gioi");
    else if (newSV->diemTB >= 6.5) strcpy(newSV->hocluc, "Kha");
    else if (newSV->diemTB >= 5) strcpy(newSV->hocluc, "Trung binh");
    else strcpy(newSV->hocluc, "Yeu");

    // Tính học phí
    newSV->hocPhi = GIA_TIEN_TIN_CHI * newSV->soTinChi;

    // Thêm sinh viên vào cuối danh sách
    if (head == NULL) {
        head = newSV;
    } else {
        SV* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newSV;
    }
}

void xoaSinhVien(SV*& head, const char* maSV) {
    SV* current = head;
    SV* prev = NULL;

    while (current != NULL&& strcmp(current->maSV, maSV) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        std::cout << "\nKhong tim thay sinh vien voi ma so " << maSV;
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    std::cout << "\nXoa sinh vien voi ma so " << maSV << " thanh cong!";
}

void sapXepTangDan(SV*& head) {
    if (head == NULL || head->next == NULL) {
        return; 
    }

    SV* sortedHead = NULL;

    while (head != NULL) {
        SV* current = head;
        head = head->next;

        if (sortedHead == NULL || strcmp(current->maSV, sortedHead->maSV) < 0) {
            current->next = sortedHead;
            sortedHead = current;
        } else {
            SV* temp = sortedHead;
            while (temp->next != NULL && strcmp(current->maSV, temp->next->maSV) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    head = sortedHead;
}

void sapXepGiamDan(SV*& head) {
    if (head == NULL || head->next == NULL {
        return; 
    }

    SV* sortedHead = NULL;

    while (head != NULL) {
        SV* current = head;
        head = head->next;

        if (sortedHead == NULL || strcmp(current->maSV, sortedHead->maSV) > 0) {
            current->next = sortedHead;
            sortedHead = current;
        } else {
            SV* temp = sortedHead;
            while (temp->next != NULL && strcmp(current->maSV, temp->next->maSV) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    head = sortedHead;
}

void hienThiDanhSach(const SV* head) {
    std::cout << "\nDANH SACH SINH VIEN\n";
    std::cout << std::left << std::setw(5) << "STT" << std::setw(8) << "ID" << std::setw(8) << "Ma SV"
              << std::setw(15) << "Ho va ten" << std::setw(15) << "Gioi tinh" << std::setw(6) << "Tuoi"
              << std::setw(7) << "Mon 1" << std::setw(7) << "Mon 2" << std::setw(7) << "Mon 3"
              << std::setw(11) << "Diem TB" << std::setw(15) << "So tin chi" << std::setw(11) << "Hoc phi"
              << std::setw(10) << "Hoc luc" << "\n";

    int stt = 1;
    const SV* current = head;
    while (current != NULL) {
        std::cout << std::left << std::setw(5) << stt << std::setw(8) << current->id << std::setw(8) << current->maSV
                  << std::setw(15) << current->ten << std::setw(15) << current->gioiTinh << std::setw(6) << current->tuoi
                  << std::setw(7) << current->diemmon1 << std::setw(7) << current->diemmon2 << std::setw(7) << current->diemmon3
                  << std::setw(11) << std::fixed << std::setprecision(5) << current->diemTB << std::setw(15) << current->soTinChi
                  << std::setw(11) << std::fixed << std::setprecision(0) << current->hocPhi << std::setw(10) << current->hocluc << "\n";

        current = current->next;
        stt++;
    }
}

void giaiPhongDanhSach(SV*& head) {
    SV* current = head;
    SV* next;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }

    head = NULL;
}

int main() {
    SV* danhSachSV = NULL;  // Đầu danh sách liên kết đơn
    int idCount = 0;
    int key;

    do {
        std::cout << "\nCHUONG TRINH QUAN LY SINH VIEN C/C++\n";
        std::cout << "*************************MENU**************************\n";
        std::cout << "**  1. Them sinh vien.                               **\n";
        std::cout << "**  2. Hien thi danh sach sinh vien.                 **\n";
        std::cout << "**  3. Xoa sinh vien theo ma so.                    **\n";
        std::cout << "**  4. Sap xep sinh vien theo ma SV tang dan.       **\n";
        std::cout << "**  5. Sap xep sinh vien theo ma SV giam dan.       **\n";
        std::cout << "**  0. Thoat                                         **\n";
        std::cout << "*******************************************************\n";
        std::cout << "Nhap tuy chon: ";
        std::cin >> key;

        switch (key) {
            case 1:
                themSinhVien(danhSachSV, idCount);
                std::cout << "\nThem sinh vien thanh cong!";
                break;
            case 2:
                hienThiDanhSach(danhSachSV);
                break;
            case 3:
                char maSV[11];
                std::cout << "\nNhap ma so sinh vien can xoa: ";
                std::cin.ignore();
                std::cin.getline(maSV, 11);
                xoaSinhVien(danhSachSV, maSV);
                break;
            case 4:
                sapXepTangDan(danhSachSV);
                std::cout << "\nSap xep sinh vien theo ma SV tang dan thanh cong!";
                break;
            case 5:
                sapXepGiamDan(danhSachSV);
                std::cout << "\nSap xep sinh vien theo ma SV giam dan thanh cong!";
                break;
            case 0:
                std::cout << "\nBan da chon thoat chuong trinh!";
                break;
            default:
                std::cout << "\nKhong co chuc nang nay!";
                std::cout << "\nHay chon chuc nang trong hop menu.";
                break;
        }

    } while (key != 0);

    giaiPhongDanhSach(danhSachSV);

    return 0;
}