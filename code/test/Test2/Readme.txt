Lưu ý để chạy bộ test:
A. Biên Dịch
1. Đưa các file .c vào trong thư mục test
2. Chỉ sửa Makefile
3. Biên dịch các chương trình trên

B. Thực Thi

./userprog/nachos -rs 1023 -x ./test/scheduler1 => Điều chỉnh để chạy main với priority = 7

C. Kết quả

Chương trình sẽ in ra một chuỗi các chữ A và B xen kẽ lẫn nhau.
Kết thúc bằng "Ping-Pong test end."