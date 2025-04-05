BÁO CÁO BÀI TẬP LỚP MÔN LẬP TRÌNH NÂNG CAO
Sinh Mã số Sinh viên: 24020183        Họ và Tên: Dương Hải Khôi
Lớp Môn học: INT 2215 - 3
Thông tin về game: link (github, google doc, youtube), game tham khảo (link, miêu tả) 
Tên game: MINIGOLF
Link GitHub :  https://github.com/haikhoi23/ProjectHK2
Link Google Drive :    
https://drive.google.com/drive/u/0/folders/1jV8VK3W7xCp08hmwXhd8toYF0I8V0nFl
Game tham khảo : CrazyGolf  : 
https://www.youtube.com/watch?v=8O8SKlCky1U
Hướng dẫn tham khảo ý tưởng game : 
https://www.youtube.com/watch?v=iEn0ozP-jxc&t=339s
Các tính năng cải tiến trong game
Sử dụng cơ chế kéo – thả chuột để đánh quả bóng
Các level khác nhau với thiết kế riêng của từng màn chơi
Cấu trúc của project game: Tổ chức lớp, Miêu tả luồng, …
Tổ chức lớp của project :
Game sử dụng các lớp để quản lý các thành phần khác nhau của trò chơi, bao gồm:
Lớp Game : Lớp chính của trò chơi, quản lý sự kiện, logic, cập nhật trạng thái và hiển thị các đối tượng của game.
Lớp Level : Đại diện cho 1 level của trò chơi, bao gồm thông tin vị trí bắt đầu của quả bóng, danh sách các vị trí chướng ngại vật, vị trí lỗ.
Lớp Obstacle : Đại diện cho 1 chướng ngại vật của trò chơi, gồm kích thước và texture của mỗi chướng ngại vật.
Lớp Menu : Quản lý giao diện Menu của trò chơi , bao gồm Menu chính quản lý các nút bấm và trạng thái.
Lớp TextureManager : Tải và quản lý các kết cấu ( texture ) trong trò chơi.
Lớp Renderer : Chịu trách nhiệm khởi tạo và quản lý cửa sổ và bộ dựng hình ( renderer ) của SDL.
Luồng hoạt động của project:
Khởi tạo trò chơi: Tạo tài nguyên, khởi tạo menu và các level.
Vòng lặp chính của game: Điều khiển luồng hoạt động của trò chơi, xử lý sự kiện, cập nhật trạng thái và hiển thị.
Xử lý sự kiện : Xử lý các sự kiện đầu vào từ người chơi.
Cập nhật trạng thái : Cập nhật trạng thái bóng, xử lý va chạm với khung màn hình và chướng ngại vật, kiểm tra điều kiện thắng.
Hiển thị : Hiển thị các đối tượng lên màn hình.
Xử lý va chạm : Đảm bảo bóng phản ứng đúng khi va chạm với các đối tượng khác nhau.
Quản lý level: Tải và khởi tạo các level trong trò chơi.
Kết thúc trò chơi: Giải phóng tài nguyên và thoát khỏi trò chơi.
Nguồn tham khảo và lấy dữ liệu: âm thanh, đồ họa, chatgpt, 
Tài nguyên đồ họa ( bóng, lỗ, chướng ngại vật ) :
https://github.com/PolyMarsDev/Twini-Golf/tree/main/res/gfx
Tài nguyên đồ họa ( nút bấm font hiển thị tính điểm) :
https://prinbles.itch.io/silent
	    https://font.download/font/apercu-movistar
Nền màn hình chơi, màn hình main menu tự thiết kế.
Các thông tin khác (nếu cần)
Hướng dẫn chơi game MINIGOLF : 
Sử dụng chuột trái để kéo thả bóng gôn trên màn hình, mỗi lần kéo thả được tính là 1 lần vụt bóng.
Bóng sẽ đi theo hướng mũi tên gắn với bóng.
Cố gắng đưa trái bóng vào trong lỗ để chơi màn tiếp theo
