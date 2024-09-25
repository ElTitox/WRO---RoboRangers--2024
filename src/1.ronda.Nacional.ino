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

  servoMotor.write(90);
  moveForward();
  delay(480);
  
  stopMotor(); // Motor detenido indefinidamente al inicio
}

void loop() {
  // El motor está detenido hasta que se detecte una distancia
  if (!haDetectadoLado) { // Es una condición para controlar el estado del motor, en este caso la condicion se hace cierta si detecto algun lado, se puede ver posteriormente en el loop una decisión para cambiar de estado esta variable.
    // Medir distancias
    distanceR = measure('R') + 2.50; // Error de medidda en el lado derecho
    distanceL = measure('L') + 2.50; // Error de medida en el lado izquierdo

    Serial.print("Distancia Derecha: "); // Impresiones para conocer el estado del ultrasonico derecho
    Serial.println(distanceR);  // Medición de la distancia del ultrasonico derecho
    Serial.print("Distancia Izquierda: "); // Impresiones para conocer el estado del ultrasonico izquierdo
    Serial.println(distanceL);  // Medición de la distancia del ultrasonico izquierdo

    // Comprobar si alguna distancia cumple la condición para girar
    if ((distanceR > 90 && distanceR < 900) || (distanceL > 90 && distanceL < 900)) { // Ésta decisión tiene condiciones con intervalos debido a tomar una posible medición de una esquina
      haDetectadoLado = true; // Una vez se cumpla cualquiera de las 2 condiciones esta variable se activa en true y 
      Serial.println("Giro detectado");

      // Determinar dirección del giro
      if (distanceR > 90 && distanceR < 900) {
        giroDerecha = true;
        servoMotor.write(180);  // Gira a la derecha
        moveForward();         // Avanzar mientras gira
        delay(550);
        servoMotor.write(90);

      } else if (distanceL > 90 && distanceL < 900) {
        giroDerecha = false;
        servoMotor.write(0);    // Gira a la izquierda
        moveForward();           // Avanzar mientras gira
        delay(450);
        servoMotor.write(90);
      }

      // Detener el motor y ajustar el servo
      stopMotor();             
      delay(600);              // Esperar medio segundo

      // Activar el motor y girar el servo simultáneamente
      analogWrite(enB, 255);  // Encender el motor a velocidad máxima

      // Ejecutar el bucle de avanzar y girar
      for (int i = 0; i < 11; i++) {
        moveForward();  // Avanzar indefinidamente
        delay(900);    // Esperar 0.9 segundos

        // Girar en la dirección determinada inicialmente
        if (giroDerecha) {
          servoMotor.write(180);  // Gira a la derecha
          delay(600);             // Mantener giro por 0.6 segundos
        } else {
          servoMotor.write(0);    // Gira a la izquierda
          delay(600);             // Mantener giro por 0.6 segundos
        }
        servoMotor.write(90);     // Ajustar el servo a la posición recta
      }

      // Detener el motor indefinidamente
      stopMotor();
      while (true);  // Pausar el motor indefinidamente
    }
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
