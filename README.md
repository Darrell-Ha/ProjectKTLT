# **Topic 6: Student Information System (SIS)**

## Nhóm sinh viên:
   * Hà Trọng Đạt - 20195851 - MI1-02
   * Trịnh Xuân Đăng - 20195849 - MI1-02

## 1. Hướng dẫn sử dụng các file header trong [*sources/entities*](https://github.com/jhongithub219/ProjectKTLT/tree/master/sources/entities)  - [link](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/README_ENT.md)

## 2. Hướng dẫn sử dụng chương trình

>***Lưu ý:*** Ở máy tính Windows 10, nếu không dùng IDE như *DevC, CodeBlock....* thì cần thực hiện ở terminal là `C:Windows\System32\conhost.exe` để chạy chương trình vì chương trình dùng bảng mã màu hệ cũ theo tiêu chuẩn [ANSI](https://vi.wikipedia.org/wiki/Vi%E1%BB%87n_Ti%C3%AAu_chu%E1%BA%A9n_Qu%E1%BB%91c_gia_Hoa_K%E1%BB%B3) - nay console WIN32 không còn đọc được.

>***Lưu ý:*** Đặt toàn bộ folder vào trong ổ `D:`. Nếu không, cần thực hiện thay đổi nội dung cho `#include` các file trong folder [sources](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources) và [headerForPro.h](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/headerForPro.h)
* ***Ý tưởng tạo menu***: Theo cây thư mục , mục lục văn bản để chia chức năng chương trình cha, chương trình con (section/subsection)
* Ở giao diện **Menu bar**

    * Ấn các phím mũi tên sang phải, sang trái để di chuyển con trỏ.
    * Ấn nút mũi tên đi xuống hoặc `Enter` để mở toggle.
    * Ấn Exit để thoát khỏi chương trình
* Ở giao diện **Open Toggle List** 
    * Ấn các mũi tên lên xuống để di chuyển con trỏ
    * Ấn `Enter` để chọn chức năng cần thực hiện 
    * Ấn nút mũi tên sang trái để thoát khỏi giao diện **Open Toggle List**

* Tóm lược chương trình liên kết với [MENU](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/functions/MENU.h): Chi tiết trong file [Program.h](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/functions/Program.h), [Section1.h](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/functions/Section1.h), [Section2.h](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/functions/Section2.h)

```
|---ProgramSection1(int subsection)
|   |---Print_SV_bin()
|   |---Print_HP_bin()
|   |---Control_DiemThi()
|   |---Control_CPA()
|
|---ProgramSection2(int subsection)
|   |---Control_WriteData()
|   |     |---Process_WriteData_SV()
|   |     |---Process_WriteData_HP()
|   |     |---Process_WriteData_DT()
|   |
|   |---Control_DeleteData()
|   |   |---Process_DeleteData_SV()
|   |   |---Process_DeleteData_HP()
|   |   |---Process_DeleteData_DT()
|   |
|   |---Control_UpdateData()
|       |---Process_UpdateData_SV()
|       |---Process_UpdateData_HP()
|       |---Process_UpdateData_DT()
|       |---Process_UpdateData_CPA()
|
|---EXIT_PROGRAM()                
```

***Xem dữ liệu trong file`.bin`*** - `void ProgramSection1(int subsection);`

* *Hiển thị danh sách sinh viên* - `void Print_SV_bin();`

* *Hiển thị danh sách học phần* - `void Print_HP_bin();`

* *Xem điểm Học phần theo lựa chọn* - `void Control_DiemThi();`

* *Xem điểm CPA theo lựa chọn* - `void Control_CPA();`

***Tương tác với dữ liệu file `.bin`*** - `void ProgramSection2(int subsection);`

* *Nhập dữ liệu cho file `.bin`* - `void Control_WriteData();`

    * Cho SV.bin - `void Process_WriteData_SV();`
    * Cho HP.bin - `void Process_WriteData_HP();`
    * Cho DIEMTHI.bin - `void Process_WriteData_DT();`

* *Xóa dữ liệu cho file`.bin`* - `void Control_DeleteData();`

    * Cho SV.bin - `void Process_DeleteData_SV();`
    * Cho HP.bin - `void Process_DeleteData_HP();`
    * Cho DIEMTHI.bin - `void Process_DeleteData_DT();`

* *Cập nhật dữ liệu cho file `.bin`* - `void Control_UpdateData();`

    * Cho SV.bin - `void Process_UpdateData_SV();`
    * Cho HP.bin - `void Process_UpdateData_HP();`
    * Cho DIEMTHI.bin - `void Process_UpdateData_DT();`
    * Cho CPA.bin - `void Process_UpdateData_CPA();`

