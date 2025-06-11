# CHƯƠNG TRÌNH MÔ PHỎNG BLOCKCHAIN BẰNG C++

<!--## Link bài viết: [Xem tại đây](https://www.facebook.com/groups/116078792627399/permalink/1425201805048418/?rdid=XusG0jcgLmKJ0mA9#)-->

## Chức năng
- Từ genesis block ban đầu liên kết với block tiếp theo thông qua previous hash
- Có 2 bản:
  - -> Bản 1: lưu mỗi giao dịch là 1 block
  - -> Bản 2: lưu 5 giao dịch thành 1 block (có thể thay đổi số giao dịch trong 1 block)
- Mỗi block đều có mã hash theo quy luật số nonce (proof of work)
  - -> Tăng độ tìm kiếm -> đào coin
  - -> Chống thay đổi thông tin -> hack
- Tính bất biến vả bảo mật toàn phần -> chống thay đổi dữ liệu
- Nhiều máy phân tán cùng tham gia nên khó thay đổi khi 1 máy bị tấn công 
- Áp dụng cho nhiều công nghệ hiện nay như ngân hàng, hóa đơn mua thuốc bằng app, ...   
  
# Screenshot 

<p align="center">
  <img src="https://github.com/user-attachments/assets/e6c4a405-6bf3-4412-828c-a3a1da684333" width="45%" />
  <img src="https://github.com/user-attachments/assets/883960d6-697a-4aac-8b47-650b0e38cb21" width="45%" />
</p>
