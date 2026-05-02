#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BUZZER_PIN 25
#define BUZZER_CHANNEL 0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
MPU6050 mpu;

bool wasColliding = false;

// Bola
float x = 10, y = 10;
float vx = 0, vy = 0;

// Física
float friction = 0.96;
float accelScale = 2.0;
float bounce = -0.4;

// Goal (topo direito)
int goalX = 112;
int goalY = 2;
int goalSize = 12;

// ❌ X perigosos
int xA = 50, yA = 20;
int xB = 80, yB = 40;
int xSize = 10;

// Estado
bool win = false;
bool lose = false;
unsigned long stateTime = 0;

// Parede
struct Wall {
  int x, y, w, h;
};

Wall walls[] = {
  {0,0,128,2}, {0,62,128,2}, {0,0,2,64}, {126,0,2,64},
  {20,0,2,40}, {40,24,2,40}, {60,0,2,40},
  {80,24,2,40}, {100,0,2,40}
};

int wallCount = sizeof(walls)/sizeof(walls[0]);

// 🔊 SOM
void beep(int freq, int duration) {
  ledcWriteTone(BUZZER_CHANNEL, freq);
  delay(duration);
  ledcWriteTone(BUZZER_CHANNEL, 0);
}

void soundWin() {
  beep(1000, 100);
  beep(1400, 100);
  beep(1800, 120);
}

void soundLose() {
  beep(700, 200);
  beep(400, 250);
}

void soundHit() {
  ledcWriteTone(BUZZER_CHANNEL, 1200);
  delay(10);
  ledcWriteTone(BUZZER_CHANNEL, 0);
}

// Reset
void resetGame() {
  x = 10;
  y = 10;
  vx = 0;
  vy = 0;
  win = false;
  lose = false;
}

bool hitBox(float bx, float by, int rx, int ry, int size) {
  return (bx > rx && bx < rx + size &&
          by > ry && by < ry + size);
}

void setup() {
  Wire.begin(21,22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  mpu.initialize();

  ledcSetup(BUZZER_CHANNEL, 2000, 8);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
}

void loop() {

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float axf = ay / 4000.0;
  float ayf = ax / 4000.0;

  if (!win && !lose) {

    vx += axf * accelScale;
    vy += ayf * accelScale;

    vx *= friction;
    vy *= friction;

    bool isColliding = false;

// --- colisão X ---
float nextX = x + vx;
for(int i=0; i<wallCount; i++) {
  Wall w = walls[i];

  if(nextX + 3 > w.x && nextX - 3 < w.x + w.w &&
     y + 3 > w.y && y - 3 < w.y + w.h) {

    vx *= bounce;
    nextX = x;
    isColliding = true;
  }
}

// --- colisão Y ---
float nextY = y + vy;
for(int i=0; i<wallCount; i++) {
  Wall w = walls[i];

  if(x + 3 > w.x && x - 3 < w.x + w.w &&
     nextY + 3 > w.y && nextY - 3 < w.y + w.h) {

    vy *= bounce;
    nextY = y;
    isColliding = true;
  }
}

// 🔊 som apenas quando começa a colisão
if (isColliding && !wasColliding) {
  soundHit();
}

wasColliding = isColliding;

    x = constrain(nextX, 3, 125);
    y = constrain(nextY, 3, 61);

    // 🏁 WIN
    if (hitBox(x, y, goalX, goalY, goalSize)) {
      win = true;
      stateTime = millis();
      soundWin();
    }

    // 💀 LOSE
    if (hitBox(x, y, xA, yA, xSize) ||
        hitBox(x, y, xB, yB, xSize)) {
      lose = true;
      stateTime = millis();
      soundLose();
    }
  }

  // reset automático
  if ((win || lose) && millis() - stateTime > 1200) {
    resetGame();
  }

  // 🎨 desenho
  display.clearDisplay();

  if (!win && !lose) {

    for(int i=0; i<wallCount; i++) {
      display.fillRect(walls[i].x, walls[i].y, walls[i].w, walls[i].h, WHITE);
    }

    // goal
    display.drawRect(goalX, goalY, goalSize, goalSize, WHITE);

    // X perigosos
    display.drawLine(xA, yA, xA + xSize, yA + xSize, WHITE);
    display.drawLine(xA + xSize, yA, xA, yA + xSize, WHITE);

    display.drawLine(xB, yB, xB + xSize, yB + xSize, WHITE);
    display.drawLine(xB + xSize, yB, xB, yB + xSize, WHITE);

    // bola
    display.fillCircle(x, y, 3, WHITE);

  } else if (win) {
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(28, 20);
    display.println("WIN!");

  } else {
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(25, 20);
    display.println("LOSE");
  }

  display.display();
  delay(16);
}