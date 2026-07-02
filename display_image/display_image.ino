// ============================================================
// Hiển thị ảnh Hoàng Đế Quang Trung trên board ESP32-2432S028R
// (còn gọi là "Cheap Yellow Display" - CYD)
// Màn hình: 2.8" ILI9341, độ phân giải 320x240
// ============================================================
//
// CHUẨN BỊ:
// 1. Cài thư viện "TFT_eSPI" (Bodmer) qua Library Manager trong Arduino IDE
// 2. Copy file "image_data.h" vào CÙNG THƯ MỤC với file .ino này
// 3. Cấu hình TFT_eSPI cho đúng board CYD (xem hướng dẫn bên dưới)
// 4. Chọn board: ESP32 Dev Module trong Arduino IDE
//
// ============================================================
// CẤU HÌNH TFT_eSPI CHO BOARD ESP32-2432S028R:
// Mở file: <thư mục thư viện Arduino>/TFT_eSPI/User_Setup_Select.h
// Comment dòng: #include <User_Setup.h>
// Thêm/uncomment dòng:  #include <User_Setups/Setup42_ILI9341_ESP32.h>
//
// Hoặc đơn giản hơn: dùng thư viện có sẵn cấu hình cho CYD, ví dụ
// tìm "TFT_eSPI setup for ESP32-2432S028R" trên GitHub, rất nhiều
// mẫu User_Setup.h có sẵn cho board này (chân: MISO 12, MOSI 13,
// SCLK 14, CS 15, DC 2, RST -1, BL 21).
// ============================================================

#include <TFT_eSPI.h>
#include "image_data.h"   // Mảng ảnh RGB565 đã được chuyển đổi sẵn

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);       // 1 = ngang (landscape), đổi thành 3 nếu ảnh bị lộn ngược
  tft.fillScreen(TFT_BLACK);

  // Bật đèn nền màn hình (chân GPIO 21 trên board CYD)
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  // QUAN TRỌNG: khắc phục lỗi màu sai/lệch (đỏ<->xanh, màu ám...)
  // Mảng ảnh được tạo theo thứ tự byte "chuẩn" (MSB trước), nhưng
  // ESP32 lưu uint16_t theo little-endian nên cần bật swap byte
  // để SPI gửi đúng thứ tự cho panel ILI9341.
  tft.setSwapBytes(true);

  // Vẽ ảnh lên toàn màn hình (320x240) tại tọa độ (0,0)
  tft.pushImage(0, 0, IMG_WIDTH, IMG_HEIGHT, quangTrungImage);
}

void loop() {
  // Không cần làm gì thêm, ảnh đã hiển thị cố định
}
