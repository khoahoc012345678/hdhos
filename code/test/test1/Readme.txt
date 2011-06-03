Lưu ý để chạy bộ test:
A. Biên Dịch
1. Đưa các file .c vào trong thư mục test
2. Chỉ sửa Makefile
3. Biên dịch các chương trình trên

B. Thực Thi

./userprogram/nachos -rs 1023 -x ./test/main => Điều chỉnh để chạy main với priority = 7

C. Kết quả

Chương trình sẽ in ra 1000 chữ A liên tiếp sau đó in dòng
"Ket Thuc Lower Release Lock" Cuối cùng in dòng
"Ket Thuc High Halt May"

