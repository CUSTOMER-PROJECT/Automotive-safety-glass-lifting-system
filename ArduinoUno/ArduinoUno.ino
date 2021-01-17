
/* Định nghĩa các chân linh kiện*/
#define NUT_NHAN_LEN
#define NUT_NHAN_XUONG
#define CAM_BIEN_HONG_NGOAI
#define BIEN_TRO
#define CT_HANH_TRINH_TREN
#define CT_HANH_TRINH_DUOI
/* Định nghĩa macro */
#define BAT 1
#define TAT 0

/* Các hàm chức năng (tổng quát)*/
bool Phat_Hien_Cham_Tren(); // Phát hiện chạm trên
bool Phat_Hien_Cham_Duoi(); // Phát hiện chạm dưới
bool Phat_Hien_Vat_The();   // Phát hiện vật thể (trường hợp bị kẹt kính)
void Dieu_Khien_Kinh_Len(); // Điều khiển kính lên
void Dieu_Khien_Kinh_Xuong(); // Điều khiển kính xuống
void Dieu_Khien_Kinh_Len_Tu_Dong(); // Điều khiển kính tự động lên
void Dieu_Khien_Kinh_Xuong_Tu_Dong(); // Điều khiển kính tự động xuống
void Dieu_Khien_Kinh_Len_Xuong(); // Điều khiển kính lên - xuống
void Bat_Tat_Buzzer();      // Phát chuông cảnh báo khi phát hiện vật thể - Cảnh báo

/* Chương trình chính*/
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/* Các hàm chức năng (chi tiết)*/
