#include <Servo.h>

#define TRIG_PIN_R 2
#define ECHO_PIN_R 3
#define TRIG_PIN_L 12
#define ECHO_PIN_L 11
#define SERVO_PIN 6

Servo servoMotor;

const int enB = 9;
const int in3 = 8;
const int in4 = 7;

long duration;
float distanceR;
float distanceL;

const int RotacionesPorTiempo = 223;  // Número de rotaciones por tiempo
bool haDetectadoLado = false;
bool giroDerecha = false;  // Indica si el giro es a la derecha

void setup() {
  Serial.begin(9600);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  servoMotor.attach(SERVO_PIN);

  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);
  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);

  servoMotor.write(77);  
  delay(500);
}

void loop() {
  // Solo se ejecuta si no se ha detectado un lado previamente
  if (!haDetectadoLado) {
    moveForward();  // El motor sigue moviéndose a velocidad normal

    // Medir distancias
    distanceR = measure('R') + 2.50;
    distanceL = measure('L') + 2.50;

    Serial.print("Distancia Derecha: ");
    Serial.println(distanceR);
    Serial.print("Distancia Izquierda: ");
    Serial.println(distanceL);

    // Comprobar condiciones de giro
    if (distanceR > 150 || distanceL > 150) {
      haDetectadoLado = true;
      Serial.println("Giro detectado");

      // Establecer velocidad del motor antes de girar
      analogWrite(enB, 230);  // Aumentar a 230 antes de girar

      // Determinar dirección del giro
      if (distanceR > 150) {
        giroDerecha = true;
        servoMotor.write(180);  // Gira a la derecha
        moveForward();          // Avanzar mientras gira
        rotateRight(0.5);      // Girar 0.5 rotaciones a la derecha
      } else {
        giroDerecha = false;
        servoMotor.write(0);    // Gira a la izquierda
        moveForward();          // Avanzar mientras gira
        rotateLeft(0.5);       // Girar 0.5 rotaciones a la izquierda
      }

      // Detener el motor y ajustar el servo
      stopMotor();             // Detener el motor
      delay(600);              // Esperar medio segundo

      // Activar el motor y girar el servo simultáneamente
      analogWrite(enB, 255);  // Encender el motor a velocidad máxima

      // Girar completamente
      if (giroDerecha) {
        moveForward();
        rotateRight(0.5);        // Rotar el servo a la derecha
      } else {
        moveForward();
        rotateLeft(0.5);         // Rotar el servo a la izquierda
      }
      servoMotor.write(77);    // Ajustar el servo a la posición recta

      // Ejecutar el bucle de avanzar y girar
      for (int i = 0; i < 11; i++) {
        moveForward();  // Avanzar indefinidamente
        delay(1000);    // Esperar 1.4 segundos

        // Girar en la dirección determinada inicialmente
        if (giroDerecha) {
          servoMotor.write(180);  // Gira a la derecha
          delay(700);              // Mantener giro por 0.5 segundos
        } else {
          servoMotor.write(0);    // Gira a la izquierda
          delay(700);              // Mantener giro por 0.5 segundos
        }
        servoMotor.write(77);      // Ajustar el servo a la posición recta
      }

      // Detener el motor indefinidamente
      stopMotor();
      while (true);  // Pausa el motor indefinidamente
    }
  } else {
    // Mantener el motor encendido indefinidamente
    moveForward();  // Asegurarse de que sigue avanzando
  }
}

// Función para medir la distancia
float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return (duration / 2.0) / 29.1;  // Conversión
}

float measure(char C) {
  return (C == 'R') ? measureDistance(TRIG_PIN_R, ECHO_PIN_R) : measureDistance(TRIG_PIN_L, ECHO_PIN_L);
}

// Función para avanzar el robot
void moveForward() {
  analogWrite(enB, 255);  // Velocidad máxima
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Función para detener el motor
void stopMotor() {
  analogWrite(enB, 0);  // Detener el motor
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Función para girar a la derecha
void rotateRight(int rotaciones) {
  int tiempoDeRotacion = rotaciones * RotacionesPorTiempo;
  servoMotor.write(180);
  delay(tiempoDeRotacion);  // Tiempo de giro
}

// Función para girar a la izquierda
void rotateLeft(int rotaciones) {
  int tiempoDeRotacion = rotaciones * RotacionesPorTiempo;
  servoMotor.write(0);
  delay(tiempoDeRotacion);  // Tiempo de giro
}