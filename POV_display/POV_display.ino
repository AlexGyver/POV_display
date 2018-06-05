#define NUM_LEDS 72     // количество светодиодов
#define BRIGHTNESS 200  // яркость
#define MOTOR_MAX 160   // скорость мотора (0-255)
#define RES 10          // разрешение (каждые n градусов)
#define COEF 0.3        // коэф. сглаживания частоты оборотов
#define PODGON 1.3      // коэф. подгона (у, блет)
#define OFFSET 240      // сдвиг по углу (0-360)
#define NUM_FRAMES 8    // количество фреймов анимации
#define FRAME_RATE 30   // количество перерисовок между сменой кадра

#define PIN 4           // пин ленты
#define MOS 3           // пин мосфета (мотора)
#define BTN1 8          // пин кнопки 1
#define BTN1_G 6        // земля кнопки 1
#define BTN2 11         // пин кнопки 2      
#define BTN2_G 9        // земля кнопки 2

// наборы битмапов. Выбери один!
//#include "cube.h"
//#include "eye.h"
//#include "face.h"
//#include "homer.h"
//#include "jake.h"
//#include "ping.h"
//#include "sonic.h"
//#include "sponge.h"
#include "static.h"
//#include "tech1.h"
//#include "tech2.h"
//#include "tits.h"

// ---------------- ДЛЯ РАЗРАБОТЧИКОВ ----------------
#include <TimerOne.h>
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
#include "gamma.h"

boolean motor_state = false;
volatile uint32_t timer;
volatile uint32_t period, new_period, period_f;
volatile boolean timer_isr, hall_isr, new_loop;

uint16_t counter1, counter2;
uint8_t counter;
const byte n_segm = 360 / RES;
const byte offset = (float)OFFSET / 360 * n_segm;
//const byte offset = 0;
byte this_frame = 0, count_frame;

static uint32_t expandColor(uint16_t color) {
  return ((uint32_t)pgm_read_byte(&gamma5[ color >> 11       ]) << 16) |
         ((uint32_t)pgm_read_byte(&gamma6[(color >> 5) & 0x3F]) <<  8) |
         pgm_read_byte(&gamma5[ color       & 0x1F]);
}
// ---------------- ДЛЯ РАЗРАБОТЧИКОВ ----------------

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN1_G, OUTPUT);
  pinMode(BTN2_G, OUTPUT);
  digitalWrite(BTN1_G, LOW);
  digitalWrite(BTN2_G, LOW);
  pinMode(MOS, OUTPUT);

  attachInterrupt(0, hall, RISING);
  Timer1.initialize();
  Timer1.stop();

  strip.clear();
  strip.show();
}

void hall() {   // тут у нас тахометр
  if (micros() - timer > 30000) {     // фильтруем ложные
    new_period = micros() - timer;    // вот он вот он период оборота
    timer = micros();
    hall_isr = true;
  }
}

// прерывания таймера
void timer_interrupt() {
  timer_isr = true;
}

// вот тут у нас просиходит целая куча всего
// из PROGMEM получаем цвета пикселей с глубиной 16 бит, переводим в 24 бита (спасибо adafruit) и включаем ленту
void setPix(byte i, int counter, int this_pix) {
  switch (this_frame) {
    case 0: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame0[counter][this_pix]))));
      break;
    case 1: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame1[counter][this_pix]))));
      break;
    case 2: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame2[counter][this_pix]))));
      break;
    case 3: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame3[counter][this_pix]))));
      break;
    case 4: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame4[counter][this_pix]))));
      break;
    case 5: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame5[counter][this_pix]))));
      break;
    case 6: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame6[counter][this_pix]))));
      break;
    case 7: strip.setPixelColor(i, expandColor(pgm_read_word(&(frame7[counter][this_pix]))));
      break;
  }
}

void animation() {
  timer_isr = false;
  strip.clear();

  byte this_pix = 0;
  for (int i = NUM_LEDS / 2 - 1; i >= 0; i--) {
    setPix(i, counter1, this_pix);
    this_pix++;
  }
  this_pix = 0;
  for (int i = NUM_LEDS / 2 ; i < NUM_LEDS; i++) {
    setPix(i, counter2, this_pix);
    this_pix++;
  }

  counter1++;   // счётчик первой половины ленты
  counter2++;   // счётчик второй половины
  if (counter2 > n_segm) counter2 = 0;
  if (counter1 > n_segm) counter1 = 0;

  strip.show();
}

void loop() {
  if (hall_isr) {
    hall_isr = false;
    counter1 = 0 + offset;
    counter2 = n_segm / 2 + offset;
    if (counter2 > n_segm) counter2 = counter2 - n_segm;

    // выбор кадра и скорости отображения
    count_frame++;
    if (count_frame > FRAME_RATE) {
      count_frame = 0;
      this_frame = ++this_frame % NUM_FRAMES;
    }

    animation();
    period_f = (float)new_period * COEF + (float)period_f * ((float)1 - COEF);
    Timer1.setPeriod(period_f / n_segm * PODGON);
    Timer1.restart();
    //Serial.println(isr_counter2);
  }

  if (timer_isr) {
    timer_isr = false;
    animation();
  }

  if (!digitalRead(BTN1)) {
    motor_state = !motor_state;
    if (motor_state) {
      for (int i = 0; i < MOTOR_MAX; i++) {
        analogWrite(MOS, i);
        delay(20);
      }
      Timer1.attachInterrupt(timer_interrupt);
    } else {
      for (int i = MOTOR_MAX; i > 0; i--) {
        analogWrite(MOS, i);
        delay(20);
      }
      analogWrite(MOS, 0);
      Timer1.stop();
      Timer1.detachInterrupt();
      // не работает нихера, лента всё равно горит
      strip.clear();
      strip.show();
    }
  }
}
