#include "esp_camera.h"
#include <SPI.h>
#include <SD.h>

// Kamera-Pinout AI Thinker
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

// SD-SPI Pinout
static const int PIN_SD_CS = 13;
static const int PIN_SD_SCK = 14;
static const int PIN_SD_MOSI = 15;
static const int PIN_SD_MISO = 2;

SPIClass spiSD(VSPI);
uint32_t imageCounter = 0;

camera_config_t makeCameraConfig() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_UXGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  return config;
}

bool saveFrameToSD(camera_fb_t *fb) {
  char path[32];
  snprintf(path, sizeof(path), "/img_%05lu.jpg", (unsigned long)imageCounter++);

  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.printf("[timelapse] Konnte %s nicht öffnen\n", path);
    return false;
  }

  size_t written = file.write(fb->buf, fb->len);
  file.close();

  if (written != fb->len) {
    Serial.printf("[timelapse] Unvollständig geschrieben (%u/%u): %s\n", written, fb->len, path);
    return false;
  }

  Serial.printf("[timelapse] Gespeichert: %s (%u Bytes)\n", path, fb->len);
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("[timelapse] Init Kamera...");
  camera_config_t camConfig = makeCameraConfig();
  esp_err_t camErr = esp_camera_init(&camConfig);
  if (camErr != ESP_OK) {
    Serial.printf("[timelapse] Kamera-Init FEHLER: 0x%x\n", camErr);
    while (true) {
      delay(1000);
    }
  }

  Serial.println("[timelapse] Init SD (SPI)...");
  spiSD.begin(PIN_SD_SCK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);
  if (!SD.begin(PIN_SD_CS, spiSD, 20000000)) {
    Serial.println("[timelapse] SD Mount FEHLER");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("[timelapse] Start: Alle 5s ein UXGA-Foto");
}

void loop() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("[timelapse] fb_get FEHLER");
    delay(1000);
    return;
  }

  saveFrameToSD(fb);
  esp_camera_fb_return(fb);

  delay(5000);
}
