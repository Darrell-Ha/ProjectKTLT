# **Topic 6: Student Information System (SIS) - by 20195851 & 20195849**

## 1. Hướng dẫn sử dụng các file  trong folder [entity](https://github.com/jhongithub219/ProjectKTLT/tree/master/sources/entities)
**Lưu ý:** *trước khi test cần phải include file [headerForPro.h](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/headerForPro.h) vào trong file [main.c](https://github.com/jhongithub219/ProjectKTLT/blob/master/main.c) để có thể chạy được các hàm trong đó.*
### *Chi tiết các hàm có trong file* 

Mỗi 1 file Header chứa các thông tin và hàm chức năng để tương tác với file nhị phân tương ứng ( ví dụ file [SV.h](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/entities/SV.h) tương tương tác tương ứng với [SV.bin](https://github.com/jhongithub219/ProjectKTLT/blob/master/fileBin/SV.bin) )

* Một sinh viên bao gồm 4 thông tin chính đó là: *Mã số sinh viên, Ngày tháng năm sinh* và *Giới tính*. Các thông tin chính được gộp lại tạo thành 1 bản ghi ( Ví dụ `struct SinhVien` gồm 7 thuộc tính ). Các file khác tương tự

* Các struct có sự kết nối với nhau và cũng có những ràng buộc cụ thể

    * Một sinh viên bất kì có duy nhất 1 *Mã số sinh viên* (`MSSV`) và ngược lại
    * Một mã học phần (`maHP`) chỉ duy nhất 1 học phần.
    * Một bản ghi điểm thi được xác định tính duy nhất bởi một cặp `MSSV`, `maHP` 
    ```
    struct DiemThi {long MSSV, char maHP[8], float diem}; 
    ```
    * Chỉ những Sinh viên nào có điểm thi thì mới được cập nhật điểm CPA 
    ```
    struct CPA {long MSSV, float cpa};
    ``` 

    Sự ràng buộc liên kết này giúp quá trình đồng bộ file nhị phân `.bin`, dữ liệu được đảm bảo tính nhất quán và tính đúng đắn của dữ liệu

* Khi dữ liệu đã được ghi vào file `.bin` do đã đảm bảo được **tính đúng đắn** và **nhất quán** nên mỗi một bản ghi ( trong 1 file `.bin` bất kì ) sẽ có 1 vị trí xác định. Như vậy, vị trí của bản ghi đóng vai trò quan trọng trong việc **đọc dữ liệu** file `.bin` lên màn hình console và **xác định sự tồn tại** của bản ghi.

## Các hàm cơ bản để tương tác một file `.bin`

*Ví dụ với [SV.h](https://github.com/jhongithub219/ProjectKTLT/blob/master/sources/entities/SV.h) và file [SV.bin](https://github.com/jhongithub219/ProjectKTLT/blob/master/fileBin/SV.bin)*
* Thủ tục ghi dữ liệu: 
    * **INPUT:** một struct Sinh viên mang thông tin cho một sinh viên
    * **OUTPUT:** vị trí của bản ghi mới trong file `SV.bin`
    * Viết vào file thành công sẽ in ra thông báo `SUCCESS...`, nếu không sẽ báo lỗi thông qua `printf("ERROR!")`
    * **Ràng buộc:** *Chỉ cho phép ghi vào sinh viên* ***chưa tồn tại bản ghi*** *trong file [SV.bin](https://github.com/jhongithub219/ProjectKTLT/blob/master/fileBin/SV.bin)*
    ```
    int WriteSV_toBIN(struct SinhVien new_SV);
    ``` 
* Thủ tục đọc dữ liệu file: 
    * In ra bảng chứa các thông tin sinh viên
    * Nếu không có dữ liệu sẽ chỉ hiển thị ra HEADER 

    ```
    void Print_SV_bin();
    ```

* Hàm Xóa dữ liệu bản ghi:
    * **INPUT:** một MSSV của sinh viên đang cần được xóa dữ liệu
    * **OUTPUT:** Trả về 0 về đã xóa thành công hoặc -1 nếu thất bại 
    * **Ràng buộc:** *Chỉ cho phép xóa nếu dữ liệu Sinh viên* ***có tồn tại*** *trong file [SV.bin](https://github.com/jhongithub219/ProjectKTLT/blob/master/fileBin/SV.bin)*

    ```
    int Delete_SV(long MSSV);
    ```
* Hàm Cập nhật dữ liệu:
    * **INPUT:** một MSSV của sinh viên cần cập nhật, 1 bản ghi mới cho sinh viên đó và vị trí trong file 
    * **OUTPUT:** 0 nếu update thành công, -1 nếu có sự cố xảy ra
    * **Ràng buộc:** *Chỉ cho phép update sinh viên* ***có tồn tại*** trong file [SV.bin](https://github.com/jhongithub219/ProjectKTLT/blob/master/fileBin/SV.bin) 
    ```
    int Update_SV(long MSSV, struct SinhVien new_recordSV, int position);
    ```
* **EXTRA:** Hàm Kiểm tra sự tồn tại của bản ghi
    * **IN:** một MSSV cần kiểm tra sự tồn tại của bản ghi
    * **OUT:** trả về vị trí của bản ghi trong file ( được đổi từ byte trong file nhị phân theo `sizeof(struct SinhVien)` ), hoặc -1 nếu chưa tồn tại
    * Là chức năng phụ nhưng đóng vai trò quan trọng trong việc đảm bảo sự thống nhất và toàn vẹn dữ liệu
    ```
    int CheckExist_SV_toPosition(long MSSV);
    ```
### *Các cấu trúc bản ghi và các hàm cơ bản ở các file `.h` khác cũng chức năng tương tự*
