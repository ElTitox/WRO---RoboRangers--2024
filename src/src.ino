#include <Servo.h>

#define Pi 3.1415926535897932384626433832795
#define SERVO_PIN 6

// ServoMotor
Servo servoMotor;

// Pines del puente H
const int enA = 9;
const int in1 = 8;
const int in2 = 7;

const int RotacionesPorTiempo = 223; // 0.223 segundos por rotación
int girosTotales = 0; // Contador de giros totales

void setup() {
  Serial.begin(9600);

  // Configurar pines del puente H
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Habilitar motor
  servoMotor.attach(SERVO_PIN);
}

void moveForward(int rotaciones) {
  // Ecuacion para rotaciones
  int tiempoDeRotacion = rotaciones * RotacionesPorTiempo;

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255);

  delay(tiempoDeRotacion);
}

void loop() {
  if (girosTotales < 12) { // Verifica si se han hecho menos de 12 giros
    servoMotor.write(90); // Mover hacia adelante
    moveForward(6.5); // Moverse hacia adelante 6.5 rotaciones
    servoMotor.write(0); // Girar 90 grados
    delay(RotacionesPorTiempo * 4); // Ajustar el tiempo para un giro de 90 grados
    servoMotor.write(90); // Volver a la posición de avance
    
    girosTotales++; // Incrementar el contador de giros
  } else {
    digitalWrite(enA, LOW); // Detener el motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // El robot se detendrá y no hará más giros
    while (true) {} // Bucle infinito para detener el programa
  }
}
