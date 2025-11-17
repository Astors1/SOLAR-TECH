#include <ESP32Servo.h>

Servo miServo;

void setup() {
  miServo.attach(16);  // Pin RX2 = 16
}

void loop() {
  // Mover de 0° a 180°
  for (int ang = 0; ang <= 180; ang++) {
    miServo.write(ang);
    delay(10);  // Ajusta velocidad del movimiento
  }

  // Regresar de 180° a 0°
  for (int ang = 180; ang >= 0; ang--) {
    miServo.write(ang);
    delay(10);
  }
}
