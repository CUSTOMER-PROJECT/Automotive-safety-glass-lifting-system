
/* Định nghĩa các chân linh kiện*/
#define BUZZER                2
#define CAM_BIEN_HONG_NGOAI   3 
#define CT_HANH_TRINH_TREN    4
#define CT_HANH_TRINH_DUOI    5
#define NUT_NHAN_LEN          6
#define NUT_NHAN_XUONG        7
#define DONG_CO_IN1           8
#define DONG_CO_IN2           9
#define DONG_CO_PWM           10
#define CT_TU_DONG_LEN        12
#define CT_TU_DONG_XUONG      13
#define BIEN_TRO              A0
/* Định nghĩa macro */
#define BAT   1
#define TAT   0
#define LEN   1
#define XUONG 0
#define OUT   OUTPUT
#define IN    INPUT
#define MAX_SPEED 255
#define MIN_SPEED 0

/* Biến toàn cục */
int TOCDO = 0;

/* Các hàm chức năng (tổng quát)*/
bool Nhan_Nut_Len();        // Nhấn nút kính lên
bool Nhan_Nut_Xuong();      // Nhấn nút kính xuống
bool Che_Do_Tu_Dong_Len();  // Bật chế độ tự động kính lên
bool Che_Do_Tu_Dong_Xuong();  // Bật chế độ tự động kính lên
bool Phat_Hien_Cham_Tren(); // Phát hiện chạm trên
bool Phat_Hien_Cham_Duoi(); // Phát hiện chạm dưới
bool Phat_Hien_Vat_The();   // Phát hiện vật thể (trường hợp bị kẹt kính)
bool Kiem_Tra_Trang_Thai(int PIN); // RÚT GỌN 7 HÀM Ở TRÊN
void Dieu_Khien_DC_Dung();  // Dừng động cơ
int  Chinh_Toc_Do_DC(int TocDo);     // Chỉnh tốc độ động cơ
void Dieu_Khien_Kinh_Len(); // Điều khiển kính lên
void Dieu_Khien_Kinh_Xuong(); // Điều khiển kính xuống
void Dieu_Khien_Kinh_Len_Tu_Dong(); // Điều khiển kính tự động lên
void Dieu_Khien_Kinh_Xuong_Tu_Dong(); // Điều khiển kính tự động xuống
void Bat_Tat_Buzzer(int TrangThai);      // Phát chuông cảnh báo khi phát hiện vật thể - Cảnh báo
void Che_Do_An_Toan();  // Chế độ an toàn
/*----------------------------------------------------*/
/* Chương trình chính*/
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUT);
  pinMode(CT_HANH_TRINH_TREN, IN);
  pinMode(CT_HANH_TRINH_DUOI, IN);
  pinMode(CT_TU_DONG_LEN, IN);
  pinMode(CT_TU_DONG_XUONG, IN);
  pinMode(DONG_CO_IN1, OUT);
  pinMode(DONG_CO_IN2, OUT);
  pinMode(DONG_CO_PWM, OUT);
  pinMode(CAM_BIEN_HONG_NGOAI, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CAM_BIEN_HONG_NGOAI), Che_Do_An_Toan, CHANGE);
}

void loop() {
  TOCDO = Chinh_Toc_Do_DC(digitalRead(BIEN_TRO));
  
  while (Nhan_Nut_Len() == true)
  {
    if (Phat_Hien_Cham_Tren() == true)
    {
      Dieu_Khien_DC_Dung();
      break;
    }
    Dieu_Khien_Kinh_Len();
  }
  
  while (Nhan_Nut_Xuong() == true)
  {
    if (Phat_Hien_Cham_Duoi() == true)
    {
      Dieu_Khien_DC_Dung();
      break;
    }
    Dieu_Khien_Kinh_Xuong();
  }

  while (Che_Do_Tu_Dong_Len() == true)
  {
    Dieu_Khien_Kinh_Len_Tu_Dong();
  }

  while (Che_Do_Tu_Dong_Xuong() == true)
  {
    Dieu_Khien_Kinh_Xuong_Tu_Dong();
  }
  
  delay(10);
}
/*----------------------------------------------------*/

/* Các hàm chức năng (chi tiết)*/
bool Kiem_Tra_Trang_Thai(int PIN)
{
  if (digitalRead(PIN) == HIGH)
    return true;
  return false;
}
bool Nhan_Nut_Len()
{
  return Kiem_Tra_Trang_Thai(NUT_NHAN_LEN);
}
bool Nhan_Nut_Xuong()
{
  return Kiem_Tra_Trang_Thai(NUT_NHAN_XUONG);
}
bool Che_Do_Tu_Dong_Len()
{
  return Kiem_Tra_Trang_Thai(CT_TU_DONG_LEN);
}
bool Che_Do_Tu_Dong_Xuong()
{
  return Kiem_Tra_Trang_Thai(CT_TU_DONG_XUONG);
}
bool Phat_Hien_Cham_Tren()
{
  return Kiem_Tra_Trang_Thai(CT_HANH_TRINH_TREN);
}
bool Phat_Hien_Cham_Duoi()
{
  return Kiem_Tra_Trang_Thai(CT_HANH_TRINH_DUOI);
}
bool Phat_Hien_Vat_The()
{
  if (digitalRead(CAM_BIEN_HONG_NGOAI) == LOW)
    return true;
  return false;
}
int Chinh_Toc_Do_DC(int TocDo)
{
  return constrain(TocDo, MIN_SPEED, MAX_SPEED);
}
void Dieu_Khien_DC_Dung()
{
  digitalWrite(DONG_CO_IN1, LOW);
  digitalWrite(DONG_CO_IN2, LOW);
}
void Dieu_Khien_Kinh_Len()
{
  analogWrite(DONG_CO_PWM, TOCDO);
  digitalWrite(DONG_CO_IN1, HIGH);
  digitalWrite(DONG_CO_IN2, LOW);
}
void Dieu_Khien_Kinh_Xuong()
{
  analogWrite(DONG_CO_PWM, TOCDO);
  digitalWrite(DONG_CO_IN1, LOW);
  digitalWrite(DONG_CO_IN2, HIGH);
}
void Dieu_Khien_Kinh_Len_Tu_Dong()
{
  while(Phat_Hien_Cham_Tren() == false)
  {
    Dieu_Khien_Kinh_Len();
  }
}
void Dieu_Khien_Kinh_Xuong_Tu_Dong()
{
  while(Phat_Hien_Cham_Duoi() == false)
  {
    Dieu_Khien_Kinh_Xuong();
  } 
}
void Bat_Tat_Buzzer(int TrangThai)
{
  if (TrangThai == BAT)
  {
    int randFreq = random(100, 500);
    tone(BUZZER, randFreq);
  }
  else
  {
    noTone(BUZZER);
  }
}
void Che_Do_An_Toan()
{
  Dieu_Khien_DC_Dung();
  while (Phat_Hien_Vat_The() == true)
  {
    Bat_Tat_Buzzer(BAT);
    delay(100);
  }
  Bat_Tat_Buzzer(TAT);
}

/* KẾT THÚC - CHÚC CÁC BẠN BẢO VỆ ĐỒ ÁN THÀNH CÔNG */
