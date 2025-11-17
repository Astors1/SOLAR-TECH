#include <ESP32Servo.h>

Servo horizontal;  // Servo horizontal
int servohori = 180;
int servohoriLimitHigh = 175;
int servohoriLimitLow = 5;

Servo vertical;    // Servo vertical
int servovert = 45;
int servovertLimitHigh = 100;
int servovertLimitLow = 1;

// Pines ADC del ESP32
int ldrlt = 34;  // Top left
int ldrrt = 35;  // Top right
int ldrld = 18;  // Bottom left
int ldrrd = 19;  // Bottom right

void setup() {
  // Necesario para ESP32Servo (registrar timers si se usan muchos servos)
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Attach de los servos (PIN, MIN_us, MAX_us)
  horizontal.attach(16, 500, 2400);   // Servo horizontal en pin 2
  vertical.attach(17, 500, 2400);    // Servo vertical en pin 13

  horizontal.write(180);
  vertical.write(45);

  delay(2000);
}

void loop() {
  int lt = analogRead(ldrlt);
  int rt = analogRead(ldrrt);
  int ld = analogRead(ldrld);
  int rd = analogRead(ldrrd);

  int dtime = 10;
  int tol = 200;  // Tolerancia para ADC de 12 bits

  int avt = (lt + rt) / 2;
  int avd = (ld + rd) / 2;
  int avl = (lt + ld) / 2;
  int avr = (rt + rd) / 2;

  int dvert = avt - avd;
  int dhoriz = avl - avr;

  // Movimiento vertical
  if (abs(dvert) > tol) {
    if (avt > avd) {
      servovert++;
      if (servovert > servovertLimitHigh) servovert = servovertLimitHigh;
    } else {
      servovert--;
      if (servovert < servovertLimitLow) servovert = servovertLimitLow;
    }
    vertical.write(servovert);
  }

  // Movimiento horizontal
  if (abs(dhoriz) > tol) {
    if (avl > avr) {
      servohori--;
      if (servohori < servohoriLimitLow) servohori = servohoriLimitLow;
    } else {
      servohori++;
      if (servohori > servohoriLimitHigh) servohori = servohoriLimitHigh;
    }
    horizontal.write(servohori);
  }

  delay(dtime);
}
