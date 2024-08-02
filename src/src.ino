#include <Servo.h>

// Se establece el servomotor en el pin 6
#define SERVO_PIN 6

// ServoMotor
Servo servoMotor;

// Pines del puente H
const int enA = 9;
const int in1 = 8;
const int in2 = 7;

// Se define esta variable para controlar as distancias a las que va elcarrito, a velocidad maxima hace 1 rotación por cada 0.233 segundos
// Se calculo la velocidad lineal del robot para sacar este valor, puede variar dependiendo del peso 
const int RotacionesPorTiempo = 223; // 0.223 segundos por rotación
int girosTotales = 0; // Contador de giros totales

void setup() {
  Serial.begin(9600);

  // Configurar pines del puente H
    // Pin del puente H que controla la velocidad con el pin 9 del arduino
  pinMode(enA, OUTPUT);
    // Pines de entrada del puente H dependiendo de como se configuren los pines de salida del arduino, puede controlarse el sentido, si va adelante o reversa.
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Habilitar motor
  servoMotor.attach(SERVO_PIN);
}

// Este modulo es el que controla las rotaciones, la ecuación convierte la variable Rotaciones por tiempo en tiempo por rotacion multiplicando la rotaciones puestas en la variable int 
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
