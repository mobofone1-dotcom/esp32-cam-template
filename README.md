# ESP32-CAM Template (AI Thinker / OV2640) + SD (SPI)

Dieses Verzeichnis ist als Template gedacht: wiederverwendbare Sketche + Dokumentation.

## Quickstart (Arduino IDE)
1. Boardpaket installieren:
   - Board Manager URL: https://espressif.github.io/arduino-esp32/package_esp32_index.json
   - Boardpaket: "esp32 by Espressif Systems"
2. Board wählen:
   - Tools → Board → "ESP32 Wrover Module"
   - PSRAM: Enabled
   - Upload Speed: 115200
3. Test-Reihenfolge:
   1) `sketches/cam_jpeg_test/cam_jpeg_test.ino`
   2) `sketches/sd_spi_test/sd_spi_test.ino`
   3) `sketches/cam_sd_spi_timelapse_uxga_5s/cam_sd_spi_timelapse_uxga_5s.ino`

## Erwartete Ergebnisse
### cam_jpeg_test
- Ausgabe wiederholt: `JPEG ok: ... Bytes, ...`

### sd_spi_test
- Ausgabe: Card Type, Size, schreibt `/test_spi.txt`

### cam_sd_spi_timelapse_uxga_5s
- Ausgabe: `Saved /img_0001.jpg (...)` alle 5 Sekunden  
- Dateien liegen im Root der SD-Karte.

## Dokumentation
- `docs/arduino-ide-settings.md`
- `docs/hardware.md`
- `docs/troubleshooting.md`

## Notizen
- SD_MMC kann auf manchen ESP32-CAM-Boards scheitern, obwohl SD(SPI) funktioniert.
- Für bessere Bildqualität: mehr Licht ist häufig effektiver als Parameter-Tuning.
