#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128
#define H 64
#define OLED 0x3C
#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

Adafruit_SSD1306 d(W, H, &Wire, -1);

void centerText(const char* s, int y) {
  int16_t x1, y1;
  uint16_t w, h;

  d.setTextSize(1);
  d.setTextColor(WHITE);
  d.getTextBounds(s, 0, 0, &x1, &y1, &w, &h);
  d.setCursor((W - w) / 2, y);
  d.print(s);
}

void lyric(const char* a, const char* b) {
  d.fillRect(0, 44, 128, 20, BLACK);
  d.drawLine(20, 43, 108, 43, WHITE);
  centerText(a, 46);
  centerText(b, 56);
}

void star(int x, int y, bool glow) {
  d.drawPixel(x, y, WHITE);

  if (glow) {
    d.drawPixel(x - 1, y, WHITE);
    d.drawPixel(x + 1, y, WHITE);
    d.drawPixel(x, y - 1, WHITE);
    d.drawPixel(x, y + 1, WHITE);
  }
}

void stars(int f) {
  const byte px[] = {5, 15, 28, 42, 54, 74, 87, 101, 114, 124};
  const byte py[] = {5, 14, 4, 10, 3, 12, 4, 14, 6, 11};

  for (int i = 0; i < 10; i++)
    star(px[i], py[i], ((f + i * 3) % 17) == 0);
}

void heart(int x, int y, bool big) {
  if (!big) {
    d.drawPixel(x - 2, y, WHITE);
    d.drawPixel(x + 2, y, WHITE);

    d.drawPixel(x - 3, y + 1, WHITE);
    d.drawPixel(x - 1, y + 1, WHITE);
    d.drawPixel(x + 1, y + 1, WHITE);
    d.drawPixel(x + 3, y + 1, WHITE);

    d.drawLine(x - 2, y + 2, x + 2, y + 2, WHITE);
    d.drawLine(x - 1, y + 3, x + 1, y + 3, WHITE);
    d.drawPixel(x, y + 4, WHITE);
    return;
  }

  d.fillCircle(x - 3, y + 2, 3, WHITE);
  d.fillCircle(x + 3, y + 2, 3, WHITE);
  d.fillTriangle(x - 6, y + 3, x + 6, y + 3, x, y + 10, WHITE);
}

void petal(int x, int y, int f) {
  int sway = ((f / 3) % 3) - 1;

  d.drawPixel(x + sway, y, WHITE);
  d.drawPixel(x + sway + 1, y + 1, WHITE);
  d.drawPixel(x + sway, y + 2, WHITE);
}

void flower(int x, int y) {
  d.drawPixel(x, y, WHITE);
  d.drawCircle(x - 3, y, 2, WHITE);
  d.drawCircle(x + 3, y, 2, WHITE);
  d.drawCircle(x, y - 3, 2, WHITE);
  d.drawCircle(x, y + 3, 2, WHITE);
  d.drawLine(x, y + 5, x, y + 11, WHITE);
  d.drawLine(x, y + 8, x + 4, y + 6, WHITE);
}

void boyFace(int x, int y, int f, int look) {
  bool blink = (f % 34 >= 32);
  int hair = (f / 7) % 2;

  d.drawRoundRect(x - 8, y + 7, 16, 18, 7, WHITE);

  d.drawLine(x - 9, y + 8, x - 11, y + 4, WHITE);
  d.drawLine(x - 8, y + 6, x - 7, y + 1, WHITE);
  d.drawLine(x - 6, y + 5, x - 3, y, WHITE);
  d.drawLine(x - 3, y + 4, x, y - 1, WHITE);
  d.drawLine(x, y + 4, x + 4, y, WHITE);
  d.drawLine(x + 3, y + 4, x + 8, y + 1, WHITE);
  d.drawLine(x + 7, y + 6, x + 11 + hair, y + 4, WHITE);

  d.drawLine(x - 7, y + 8, x - 4, y + 13, WHITE);
  d.drawLine(x - 3, y + 6, x - 1, y + 12, WHITE);
  d.drawLine(x + 1, y + 6, x + 2, y + 12, WHITE);
  d.drawLine(x + 5, y + 7, x + 4, y + 12, WHITE);

  if (blink) {
    d.drawLine(x - 6, y + 16, x - 2, y + 16, WHITE);
    d.drawLine(x + 2, y + 16, x + 6, y + 16, WHITE);
  } else {
    d.drawRoundRect(x - 6, y + 14, 5, 4, 2, WHITE);
    d.drawRoundRect(x + 1, y + 14, 5, 4, 2, WHITE);

    d.drawPixel(x - 3 + look, y + 16, WHITE);
    d.drawPixel(x + 4 + look, y + 16, WHITE);
  }

  d.drawPixel(x, y + 19, WHITE);
  d.drawPixel(x - 2, y + 22, WHITE);
  d.drawLine(x - 1, y + 23, x + 2, y + 23, WHITE);
}

void girlFace(int x, int y, int f, int look, bool smile) {
  bool blink = (f % 39 >= 37);
  int hair = ((f / 6) % 3) - 1;

  d.drawRoundRect(x - 7, y + 7, 14, 18, 7, WHITE);

  d.drawLine(x - 8, y + 7, x - 11, y + 18, WHITE);
  d.drawLine(x - 11, y + 18, x - 10 + hair, y + 39, WHITE);

  d.drawLine(x + 8, y + 7, x + 11, y + 18, WHITE);
  d.drawLine(x + 11, y + 18, x + 10 + hair, y + 39, WHITE);

  d.drawLine(x - 8, y + 7, x - 6, y + 2, WHITE);
  d.drawLine(x - 6, y + 2, x - 2, y, WHITE);
  d.drawLine(x - 2, y, x + 3, y + 1, WHITE);
  d.drawLine(x + 3, y + 1, x + 7, y + 5, WHITE);

  d.drawLine(x - 6, y + 7, x - 4, y + 13, WHITE);
  d.drawLine(x - 3, y + 5, x - 2, y + 12, WHITE);
  d.drawLine(x, y + 4, x, y + 12, WHITE);
  d.drawLine(x + 3, y + 5, x + 2, y + 12, WHITE);
  d.drawLine(x + 6, y + 7, x + 4, y + 13, WHITE);

  if (blink) {
    d.drawLine(x - 5, y + 16, x - 1, y + 16, WHITE);
    d.drawLine(x + 1, y + 16, x + 5, y + 16, WHITE);
  } else {
    d.drawRoundRect(x - 5, y + 14, 4, 5, 2, WHITE);
    d.drawRoundRect(x + 1, y + 14, 4, 5, 2, WHITE);

    d.drawPixel(x - 3 + look, y + 16, WHITE);
    d.drawPixel(x + 3 + look, y + 16, WHITE);
  }

  d.drawPixel(x, y + 20, WHITE);

  if (smile) {
    d.drawPixel(x - 2, y + 22, WHITE);
    d.drawLine(x - 1, y + 23, x + 1, y + 23, WHITE);
    d.drawPixel(x + 2, y + 22, WHITE);
  } else {
    d.drawLine(x - 1, y + 23, x + 1, y + 23, WHITE);
  }
}

void boyBody(int x, int y, int f, bool reach) {
  int breathe = (f / 8) % 2;

  d.drawLine(x - 3, y, x - 3, y + 3, WHITE);
  d.drawLine(x + 3, y, x + 3, y + 3, WHITE);

  d.drawLine(x - 3, y + 3, x - 9, y + 7, WHITE);
  d.drawLine(x + 3, y + 3, x + 9, y + 7, WHITE);

  d.drawLine(x - 9, y + 7, x - 8, y + 17 + breathe, WHITE);
  d.drawLine(x + 9, y + 7, x + 8, y + 17 + breathe, WHITE);
  d.drawLine(x - 8, y + 17 + breathe, x + 8, y + 17 + breathe, WHITE);

  d.drawLine(x - 3, y + 3, x, y + 8, WHITE);
  d.drawLine(x + 3, y + 3, x, y + 8, WHITE);

  d.drawLine(x - 2, y + 8, x - 2, y + 14, WHITE);
  d.drawLine(x + 2, y + 8, x + 2, y + 14, WHITE);

  d.drawLine(x - 9, y + 8, x - 13, y + 15, WHITE);

  if (reach) {
    d.drawLine(x + 9, y + 8, x + 15, y + 12, WHITE);
    d.drawLine(x + 15, y + 12, x + 20, y + 11, WHITE);
    d.drawCircle(x + 21, y + 11, 1, WHITE);
  } else {
    d.drawLine(x + 9, y + 8, x + 13, y + 15, WHITE);
  }
}

void girlBody(int x, int y, int f, bool reach) {
  int breathe = (f / 9) % 2;

  d.drawLine(x - 2, y, x - 2, y + 3, WHITE);
  d.drawLine(x + 2, y, x + 2, y + 3, WHITE);

  d.drawLine(x - 2, y + 3, x - 8, y + 7, WHITE);
  d.drawLine(x + 2, y + 3, x + 8, y + 7, WHITE);

  d.drawLine(x - 8, y + 7, x - 7, y + 17 + breathe, WHITE);
  d.drawLine(x + 8, y + 7, x + 7, y + 17 + breathe, WHITE);
  d.drawLine(x - 7, y + 17 + breathe, x + 7, y + 17 + breathe, WHITE);

  d.drawLine(x - 5, y + 7, x + 5, y + 7, WHITE);
  d.drawLine(x - 5, y + 10, x + 5, y + 10, WHITE);

  if (reach) {
    d.drawLine(x - 8, y + 8, x - 15, y + 12, WHITE);
    d.drawLine(x - 15, y + 12, x - 20, y + 11, WHITE);
    d.drawCircle(x - 21, y + 11, 1, WHITE);
  } else {
    d.drawLine(x - 8, y + 8, x - 12, y + 15, WHITE);
  }

  d.drawLine(x + 8, y + 8, x + 12, y + 15, WHITE);
}

void boy(int x, int y, int f, bool reach) {
  boyFace(x, y, f, 1);
  boyBody(x, y + 25, f, reach);
}

void girl(int x, int y, int f, bool reach, bool smile) {
  girlFace(x, y, f, -1, smile);
  girlBody(x, y + 25, f, reach);
}

void sunrise(int f) {
  int y = 34 - min(f / 3, 15);

  d.drawCircle(64, y, 6, WHITE);

  if (f % 4 < 2) {
    d.drawLine(64, y - 10, 64, y - 14, WHITE);
    d.drawLine(53, y, 48, y, WHITE);
    d.drawLine(75, y, 80, y, WHITE);
    d.drawLine(56, y - 8, 52, y - 12, WHITE);
    d.drawLine(72, y - 8, 76, y - 12, WHITE);
  }
}

void sceneMorning() {
  for (int f = 0; f < 48; f++) {
    d.clearDisplay();

    sunrise(f);

    int move = min(f / 6, 6);

    boy(27 + move, 2, f, false);
    girl(101 - move, 2, f, false, false);

    lyric(
      "ROJ SOKALE TOR",
      "MAYABI CHOBI"
    );

    d.display();
    delay(75);
  }
}

void sceneSmile() {
  for (int f = 0; f < 48; f++) {
    d.clearDisplay();

    stars(f);

    boy(38, 2, f, false);
    girl(90, 2, f, false, true);

    if (f > 8) {
      int hy = 8 - ((f / 5) % 3);
      heart(64, hy, ((f / 6) % 2));
    }

    if (f > 20) {
      star(77, 17, f % 4 == 0);
      star(82, 12, f % 7 == 0);
    }

    lyric(
      "CHOKHE BHASE TOR",
      "MISHTI HASHI"
    );

    d.display();
    delay(75);
  }
}

void sceneHair() {
  for (int f = 0; f < 52; f++) {
    d.clearDisplay();

    stars(f);

    boy(37, 2, f, true);
    girl(91, 2, f, false, true);

    flower(62, 28);

    int p1x = 84 - (f % 35);
    int p2x = 110 - ((f * 2) % 60);
    int p3x = 74 - ((f * 3) % 45);

    petal(p1x, 8 + ((f / 4) % 9), f);
    petal(p2x, 18 + ((f / 5) % 7), f + 2);
    petal(p3x, 4 + ((f / 3) % 12), f + 4);

    lyric(
      "BELI GATHA TOR",
      "CHULER BENI"
    );

    d.display();
    delay(75);
  }
}

void sceneApproach() {
  for (int f = 0; f < 46; f++) {
    d.clearDisplay();

    stars(f);

    int move = min(f / 4, 8);

    boy(34 + move, 2, f, true);
    girl(94 - move, 2, f, true, true);

    if (f > 25)
      heart(64, 5, (f / 5) % 2);

    lyric(
      "MAYAPURNO TOR",
      "CHOKHER CHAHNI"
    );

    d.display();
    delay(75);
  }
}

void eyeCloseup() {
  for (int f = 0; f < 50; f++) {
    d.clearDisplay();

    bool blink = (f == 18 || f == 19 || f == 36);

    d.drawLine(0, 5, 30, 2, WHITE);
    d.drawLine(30, 2, 55, 8, WHITE);
    d.drawLine(55, 8, 58, 42, WHITE);

    d.drawLine(128, 5, 98, 2, WHITE);
    d.drawLine(98, 2, 73, 8, WHITE);
    d.drawLine(73, 8, 70, 42, WHITE);

    if (blink) {
      d.drawLine(24, 24, 48, 24, WHITE);
      d.drawLine(80, 24, 104, 24, WHITE);
    } else {
      d.drawRoundRect(24, 18, 24, 13, 6, WHITE);
      d.drawRoundRect(80, 18, 24, 13, 6, WHITE);

      d.drawCircle(39, 24, 4, WHITE);
      d.drawCircle(89, 24, 4, WHITE);

      d.fillCircle(41, 24, 2, WHITE);
      d.fillCircle(87, 24, 2, WHITE);

      d.drawPixel(42, 23, BLACK);
      d.drawPixel(86, 23, BLACK);
    }

    if (f > 25)
      heart(64, 17, (f / 5) % 2);

    lyric(
      "MAYAPURNO TOR",
      "CHOKHER CHAHNI"
    );

    d.display();
    delay(80);
  }
}

void handTouch() {
  for (int f = 0; f < 38; f++) {
    d.clearDisplay();

    stars(f);

    int gap = max(0, 12 - f / 3);

    d.drawLine(17, 29, 49 + gap, 25, WHITE);
    d.drawLine(17, 34, 49 + gap, 29, WHITE);

    d.drawLine(111, 29, 79 - gap, 25, WHITE);
    d.drawLine(111, 34, 79 - gap, 29, WHITE);

    d.drawCircle(52 + gap, 27, 3, WHITE);
    d.drawCircle(76 - gap, 27, 3, WHITE);

    if (gap == 0) {
      d.drawLine(55, 27, 73, 27, WHITE);

      heart(
        64,
        8,
        ((f / 4) % 2)
      );
    }

    centerText("...", 48);

    d.display();
    delay(75);
  }
}

void finalCouple() {
  for (int f = 0; f < 50; f++) {
    d.clearDisplay();

    stars(f);

    boyFace(40, 7, f, 1);
    girlFace(88, 7, f, -1, true);

    heart(64, 12, (f / 5) % 2);

    if (f > 15) {
      star(57, 35, f % 5 == 0);
      star(71, 34, f % 6 == 0);
    }

    d.display();
    delay(80);
  }
}

void credits() {
  for (int f = 0; f < 35; f++) {
    d.clearDisplay();

    stars(f);

    if (f > 4)
      centerText("ESP32LyricPixel", 20);

    if (f > 11)
      centerText("BY PRAYANGSHU", 34);

    if (f > 18)
      heart(64, 48, (f / 5) % 2);

    d.display();
    delay(85);
  }

  d.clearDisplay();

  centerText("ESP32LyricPixel", 20);
  centerText("BY PRAYANGSHU", 34);
  heart(64, 48, true);

  d.display();
}

void setup() {
  Wire.begin(21, 22);

  if (!d.begin(SSD1306_SWITCHCAPVCC, OLED))
    while (true);

  d.clearDisplay();
  d.display();

  sceneMorning();
  sceneSmile();
  sceneHair();
  sceneApproach();
  eyeCloseup();
  handTouch();
  finalCouple();
  credits();
}

void loop() {
}