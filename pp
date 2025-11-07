#include <ESP32Servo.h>

// Pines de servos
#define SERVO_X_PIN 16
#define SERVO_Y_PIN 17

Servo servoX; 
Servo servoY;

// Ángulos iniciales
int anguloX = 90;
int anguloY = 90;
void setup() {
  Serial.begin(115200);

  // Configurar servos
  servoX.setPeriodHertz(50);  // Frecuencia estándar para servos
  servoX.attach(SERVO_X_PIN, 500, 2400);
  
  servoY.setPeriodHertz(50);
  servoY.attach(SERVO_Y_PIN, 500, 2400);

  // Mover a posición inicial
  servoX.write(anguloX);
  servoY.write(anguloY);

  Serial.println("Servos inicializados en 90°");
}

void loop() {
  // Ejemplo de movimiento básico
  for (int i = 0; i <= 180; i += 10) {
    servoX.write(i);
    servoY.write(180 - i);
    Serial.print("Servo X: "); Serial.print(i);
    Serial.print(" | Servo Y: "); Serial.println(180 - i);
    delay(500);
  }

  for (int i = 180; i >= 0; i -= 10) {
    servoX.write(i);
    servoY.write(180 - i);
    Serial.print("Servo X: "); Serial.print(i);
    Serial.print(" | Servo Y: "); Serial.println(180 - i);
    delay(500);
  }
}

