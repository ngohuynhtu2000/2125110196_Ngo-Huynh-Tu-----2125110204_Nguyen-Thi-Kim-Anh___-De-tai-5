# 2125110196_Ngo-Huynh-Tu-----2125110204_Nguyen-Thi-Kim-Anh___-De-tai-5
## đề tài số 5 flashcard học ngoại ngữ (CLI)

## 1. Giới thiệu Đề tài & Thuật toán
đề tài được xây dứng trên thuật toán Spaced Repetition

## 2. Các Cấu trúc Dữ liệu Sử dụng (Data Structures)
Dự án quản lý dữ liệu tối ưu, giúp người dùng học từ vựng hiệu quả

## 3. Cấu trúc File & Kiến trúc Mã nguồn
Dự án được tổ chức code trên 3 file chính: main.cpp, caidat.cpp, khaibao.h
## 4. Hướng dẫn Biên dịch và Chạy Ứng dụng (Compile & Run)
            1. Mở Dự án:
               * Tìm đến thư mục dự án và nhấp đúp chuột vào file giải pháp "de5.sln`" để mở toàn bộ source code trong Visual Studio.
               * Tại cột *Solution Explorer*, đảm bảo cấu trúc các file được phân bổ chính xác: `khaibao.h` nằm trong thư mục *Header Files*; `cd.cpp` và `                         ctc.cpp` nằm trong thư mục *Source Files*.

            2. Xử lý lỗi (Nếu có)
              * Này chủ dự án không hổ trợ
            3. Biên dịch Dự án (Build):
               * Nhấn tổ hợp phím **`Ctrl + Shift + B`
               * Quan sát cửa sổ *Output* ở bên dưới, hệ thống báo `Build: 1 succeeded, 0 failed` là quá trình biên dịch hoàn tất thành công.
            
            4. Khởi chạy Ứng dụng (Run):
               * Nhấn tổ hợp phím "Ctrl + F5"
               
### Yêu cầu hệ thống:

## 5. Danh sách các Chức năng Chính (mô tả cách hoạt động)

Ứng dụng cung cấp hệ thống menu trực quan gồm 6 chức năng hoàn chỉnh:
1. Thêm Flashcard mới:** Cho phép người dùng nhập từ vựng, định nghĩa và ví dụ minh họa. Hệ thống tự động kiểm tra trùng lặp bằng cây BST trước khi chèn và đồng bộ lịch học vào Heap. Cho phép thêm liên tục nhiều từ.
2. Tra cứu từ điển:** Tìm kiếm thông tin chi tiết một từ bất kỳ dựa trên thuật toán tìm kiếm nhị phân cây BST siêu tốc, hiển thị nghĩa, ví dụ và số ngày đến hạn ôn tập (Interval).
3. Bắt đầu phiên học:** Hệ thống tự động bốc tối đa 5 từ vựng cần học nhất từ Min-Heap đưa vào Queue để bắt đầu phiên học.
  * Hỗ trợ tính năng **Undo** (Bấm số 2) để quay lại trạng thái từ liền trước thông qua Stack nếu bấm nhầm.
  * Tự động đưa các từ trả lời **Quên** (Bấm số 0) xuống cuối hàng đợi Queue để người dùng học lại ngay trong phiên.
4. Xem toàn bộ từ điển:** Duyệt cây BST theo thứ tự In-Order (Trái - Gốc - Phải) để xuất ra danh sách từ vựng sắp xếp chuẩn từ A-Z kèm theo các thông số thống kê tổng và số lượng từ khó (Interval <= 2 ngày).
5. Xóa 1 Flashcard:** Loại bỏ từ vựng hoàn toàn khỏi cây lưu trữ BST và tiến hành giải phóng, tái cấu trúc lại toàn bộ mảng Heap (Rebuild Heap từ tập dữ liệu cây còn lại) để đảm bảo đồng bộ lịch trình.
6. Lưu dữ liệu & Thoát:** Ghi toàn bộ cây từ vựng hiện tại vào file `flashcard_data.txt` theo đúng định dạng phân tách đường dẫn rồi giải phóng bộ nhớ động, kết thúc chương trình an toàn.
