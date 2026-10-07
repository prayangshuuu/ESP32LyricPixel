# ESP32LyricPixel 🎵

> Animated lyrics, pixel-art couples, and visual storytelling on an ESP32-powered OLED.

**ESP32LyricPixel** turns a tiny **128×64 OLED** into a monochrome animated music story using an ESP32.

Instead of simply displaying lyrics, each line gets its own pixel-art scene with character animations, blinking, moving hair, flowers, hearts, stars, and transitions.

## Hardware

- ESP32 DevKit / ESP-WROOM-32
- HW-239 0.96" SSD1306 OLED
- 4× jumper wires
- USB cable

## Wiring

```text
ESP32                     SSD1306 OLED
┌───────────┐            ┌─────────────┐
│       3V3 ●────────────● VCC         │
│       GND ●────────────● GND         │
│  GPIO 22  ●────────────● SCL         │
│  GPIO 21  ●────────────● SDA         │
└───────────┘            └─────────────┘
```

| OLED | ESP32 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SCL | GPIO 22 |
| SDA | GPIO 21 |

I²C address: `0x3C`

## Libraries

Install through Arduino Library Manager:

```text
Adafruit GFX Library
Adafruit SSD1306
Adafruit BusIO
```

## Lyrics

```text
ROJ SOKALE TOR MAYABI CHOBI
CHOKHE BHASE TOR MISHTI HASHI
BELI GATHA TOR CHULER BENI
MAYAPURNO TOR CHOKHER CHAHNI
```

The original lyrics are Bengali. Transliteration is currently used because the default Adafruit GFX font doesn't support Bengali Unicode.

## Animation

```text
Sunrise
   ↓
Couple Appears
   ↓
Smile + Blinking
   ↓
Flowers + Moving Hair
   ↓
Couple Moves Closer
   ↓
Eye Contact
   ↓
Hands Touch ♥
   ↓
Final Couple
```

The story plays **once after boot/reset**.

`ESP32 × OLED × Pixel Art × Lyrics`