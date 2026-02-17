# Troubleshooting

## Empfohlene Debug-Reihenfolge

1. `cam_jpeg_test` (Kamera isoliert)
2. `sd_spi_test` (SD isoliert)
3. Kombi-Sketch (`cam_sd_spi_timelapse_uxga_5s`)

## Häufige Probleme

### `fb_get FEHLER`

Mögliche Ursache: zu aggressive Kamera-Settings.

Mögliche Maßnahmen:
- Auflösung reduzieren
- JPEG-Qualität weniger aggressiv wählen
- XCLK reduzieren

### `cam_hal: FB-OVF`

Framebuffer-Overflow.

Mögliche Maßnahmen:
- `grab_mode = CAMERA_GRAB_LATEST`
- XCLK reduzieren
- Auflösung oder Qualität anpassen
- `fb_count` anpassen

### `sdmmc_init_ocr ... returned 0x107`

Kann bei SD_MMC auftreten, obwohl SD über SPI funktioniert.

Empfehlung:
- Zuerst SD über SPI verwenden (stabiler in diesem Setup)

## Qualitäts-Hinweise

- Bei wenig Licht sinkt die Bildqualität (Rauschen/Weichheit durch Auto-Gain).
- Für maximale Qualität zuerst Auflösung erhöhen (SXGA/UXGA), dann JPEG-Quality verkleinern (z. B. 6–10).
- Stabilität geht vor: bei OVF/NULL-FB zunächst Auflösung/XCLK konservativer einstellen.
