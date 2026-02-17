# AGENTS.md

## Ziel
ESP32-CAM (AI Thinker / OV2640) in Arduino IDE:
- Kamera verlässlich initialisieren
- Bilder als JPEG auf microSD speichern
- SD bevorzugt über SPI (bewiesen stabil), SD_MMC optional

## Standard-Tooling (Arduino IDE)
- Board: ESP32 Wrover Module
- PSRAM: Enabled
- Upload Speed: 115200
- Serial Monitor: 115200

## Hardware-Pinouts (AI Thinker)

### Kamera (OV2640 / AI Thinker Pinout)
PWDN=32, RESET=-1, XCLK=0, SIOD=26, SIOC=27,  
Y9=35, Y8=34, Y7=39, Y6=36, Y5=21, Y4=19, Y3=18, Y2=5,  
VSYNC=25, HREF=23, PCLK=22

### SD über SPI (bewährtes Setup)
CS=13, SCK=14, MOSI=15, MISO=2

## Bewährte Sketche (in /sketches)
- cam_jpeg_test: Kamera-Init + fortlaufend JPEG-Frames (Größen-Ausgabe)
- sd_spi_test: SD(SPI) mount + Schreibtest (/test_spi.txt)
- cam_sd_spi_timelapse_uxga_5s: alle 5s 1 Foto (UXGA) auf SD (SPI)

## Bekannte Fakten aus diesem Setup
- SD(SPI) funktioniert.
- SD_MMC kann mit Fehlern wie `sdmmc_init_ocr ... returned 0x107` scheitern, obwohl SD(SPI) ok ist.
- Kamera kann bei zu aggressiven Settings `fb_get FEHLER` liefern.
- Kamera kann `cam_hal: FB-OVF` ausgeben (Framebuffer-Overflow).
  Gegenmaßnahmen: `grab_mode=CAMERA_GRAB_LATEST`, XCLK reduzieren, Auflösung/Qualität anpassen, fb_count anpassen.

## Debug-Regeln
- Bei Problemen immer zuerst: cam_jpeg_test (Kamera isoliert), dann sd_spi_test (SD isoliert), dann Kombi-Sketch.
- Serielle Ausgabe immer mit 115200 prüfen (sonst Zeichensalat).

## Qualitäts-Regeln
- Bildqualität hängt stark von Licht ab (dunkel => Rauschen/Weichheit durch Auto-Gain).
- Für “max. Qualität” zuerst Auflösung erhöhen (SXGA/UXGA), dann JPEG-Quality verkleinern (z.B. 6–10).
- Stabilität geht vor: wenn OVF/NULL-FB auftreten, Auflösung runter oder XCLK runter.
