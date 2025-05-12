#include <ESP32Servo.h>
#include <PID_v1.h>

// Pines de LDR
#define LDR_IZQ  33
#define LDR_DER  32
#define LDR_ARR  35
#define LDR_ABJ  34

// Pines de servo
#define SERVO_X_PIN  18
#define SERVO_Y_PIN  19

// Servo y PID
Servo servoX, servoY;

double SetpointX = 0, InputX, OutputX;
double SetpointY = 0, InputY, OutputY;

double Kp = 0.8, Ki = 0.1, Kd = 0.3;
PID pidX(&InputX, &OutputX, &SetpointX, Kp, Ki, Kd, DIRECT);
PID pidY(&InputY, &OutputY, &SetpointY, Kp, Ki, Kd, DIRECT);

int anguloX = 90;
int anguloY = 90;

void setup() {
  Serial.begin(115200);

  // Configurar servos
  servoX.setPeriodHertz(50);
  servoX.attach(SERVO_X_PIN, 500, 2400);
  
  servoY.setPeriodHertz(50);
  servoY.attach(SERVO_Y_PIN, 500, 2400);

  // Iniciar PID
  pidX.SetMode(AUTOMATIC);
  pidY.SetMode(AUTOMATIC);
}

void loop() {
  int luzIzq = analogRead(LDR_IZQ);
  int luzDer = analogRead(LDR_DER);
  int luzArr = analogRead(LDR_ARR);
  int luzAbj = analogRead(LDR_ABJ);

  // Corrección: invertir las diferencias para que giren en la dirección correcta
  InputX = luzDer - luzIzq;
  InputY = luzAbj - luzArr;

  pidX.Compute();
  pidY.Compute();

  anguloX = constrain(90 + OutputX, 0, 180);
  anguloY = constrain(90 + OutputY, 0, 180);

  servoX.write(anguloX);
  servoY.write(anguloY);

  Serial.print("Luz Izq: "); Serial.print(luzIzq);
  Serial.print(" - Luz Der: "); Serial.print(luzDer);
  Serial.print(" | Luz Arr: "); Serial.print(luzArr);
  Serial.print(" - Luz Abj: "); Serial.println(luzAbj);

  Serial.print("Servo X: "); Serial.print(anguloX);
  Serial.print(" | Servo Y: "); Serial.println(anguloY);

  delay(250);
}