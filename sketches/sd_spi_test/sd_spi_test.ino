#include <SPI.h>
#include <SD.h>

// AI Thinker ESP32-CAM: bewährtes SD-SPI Pinout
static const int PIN_SD_CS = 13;
static const int PIN_SD_SCK = 14;
static const int PIN_SD_MOSI = 15;
static const int PIN_SD_MISO = 2;

SPIClass spiSD(VSPI);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("[sd_spi_test] Init SD über SPI...");
  spiSD.begin(PIN_SD_SCK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);

  if (!SD.begin(PIN_SD_CS, spiSD, 20000000)) {
    Serial.println("[sd_spi_test] SD Mount FEHLER");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("[sd_spi_test] SD Mount ok");

  File f = SD.open("/test_spi.txt", FILE_WRITE);
  if (!f) {
    Serial.println("[sd_spi_test] Datei konnte nicht geöffnet werden");
    return;
  }

  f.println("ESP32-CAM SD SPI Schreibtest OK");
  f.close();
  Serial.println("[sd_spi_test] Schreibtest erfolgreich: /test_spi.txt");
}

void loop() {
  delay(1000);
}
