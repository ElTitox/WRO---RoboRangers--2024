Arduino Code
===

#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>

#define MOTOR_PIN1 5
#define MOTOR_PIN2 6
#define ENABLE_PIN 9
#define SERVO_PIN 10
#define ECHO_PIN_FRONT 7
#define TRIG_PIN_FRONT 8
#define ECHO_PIN_RIGHT_LEFT 11
#define TRIG_PIN_RIGHT_LEFT 12
#define LINE_SENSOR_PIN A0  // Pin del sensor de línea TCRT5000-1

// Definiciones del sensor TCS3200
#define S0 14  // A0
#define S1 15  // A1
#define S2 16  // A2
#define S3 17  // A3
#define OUT 3  // pin digital

Servo steeringServo;
MPU6050 gyro;

// Variables para almacenar los valores de frecuencia de los colores
int redFrequency;
int greenFrequency;
int blueFrequency;

int lapCounter = 0;                    // Conteo de vueltas en una ronda
int roundCounter = 0;                  // Conteo de rondas
int detectionCounter = 0;              // Conteo de detecciones de líneas
int speed = 255;                       // Velocidad del motor
const int lapThreshold = 4;            // Límite de vueltas por ronda
const int roundThreshold = 3;          // Límite de rondas
const int wallDistanceThreshold = 20;  // Umbral de distancia en cm para evitar colisiones con la pared
const int trackSize = 3200;            // Tamaño de la pista en mm
const int whiteThreshold = 800;        // Ajustar según la calibración
const int blueLineThreshold = 500;     // Ajustar según la calibración
const int orangeLineThreshold = 300;   // Ajustar según la calibración

// Variables para almacenar las coordenadas del aparcamiento
long parkingCoordFront = -1;
long parkingCoordRight = -1;

void setup() {
  Serial.begin(9600);

  // Configuración de pines del motor
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Configuración del servo
  steeringServo.attach(SERVO_PIN);

  // Configuración de pines del sensor ultrasónico
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIG_PIN_RIGHT_LEFT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT_LEFT, INPUT);

  // Configuración del sensor de seguimiento de líneas
  pinMode(LINE_SENSOR_PIN, INPUT);

  // Configuración de pines del sensor TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, INPUT);   // Ejemplo, configura según tu diseño
  pinMode(S3, INPUT);   // Ejemplo, configura según tu diseño
  pinMode(OUT, INPUT);  // Ejemplo, configura según tu diseño

  // Configuración del giroscopio GY-521
  Wire.begin();
  gyro.initialize();
  if (gyro.testConnection()) {
    Serial.println("MPU6050 conectado correctamente");
  } else {
    Serial.println("Error al conectar el MPU6050");
  }
}

void loop() {
  if (roundCounter < roundThreshold) {  // Solo se ejecutará para esta condición. Si el contador de rondas es menor al límite de rondas
    if (lapCounter < lapThreshold) {    // Si el contador de vueltas es menor al límite de vueltas por ronda
      navigateTrack();                  // Navegar por la pista, una función de entrada definida
      checkLapCompletion();             // Revisar las vueltas completadas, una función de entrada definida
    } else {
      lapCounter = 0;  // Reinicia el contador de vueltas para la próxima ronda
      roundCounter++;  // Incrementa el contador de rondas
      Serial.print("Rounds: ");
      Serial.println(roundCounter);
    }
  } else {
    returnToStart();
  }
}

void navigateTrack() {
  // Se definen las variables para las distancias x,y de los sensores ultrasónicos
  long distanceFront = measureDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT);
  long distanceRight = measureDistance(TRIG_PIN_RIGHT_LEFT, ECHO_PIN_RIGHT_LEFT);

  // Leer los datos del giroscopio
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  gyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("Giroscopio - ax: ");
  Serial.print(ax);
  Serial.print(" ay: ");
  Serial.print(ay);
  Serial.print(" az: ");
  Serial.print(az);
  Serial.print(" gx: ");
  Serial.print(gx);
  Serial.print(" gy: ");
  Serial.print(gy);
  Serial.print(" gz: ");
  Serial.println(gz);

  // Evitar colisiones con las paredes
  if (distanceFront < wallDistanceThreshold) {
    turnRight();
  } else if (distanceRight < wallDistanceThreshold) {
    turnLeft();
  } else if (distanceRight > (trackSize - wallDistanceThreshold)) {
    turnLeft();
  } else {
    moveForward();
  }

  // Leer el valor del sensor de línea
  int sensorValue = analogRead(LINE_SENSOR_PIN);

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue < whiteThreshold) {  // Ajusta este umbral según sea necesario
    Serial.println("Line detected");

    // Detectar líneas específicas
    if (isBlueLine(sensorValue)) {
      turnLeft();
      reduceSpeed();
      detectionCounter++;
      delay(1000);  // Añadir un pequeño retraso para evitar múltiples detecciones seguidas
    } else if (isOrangeLine(sensorValue)) {
      stopTurning();
      increaseSpeed();
      detectionCounter++;
      delay(1000);  // Añadir un pequeño retraso para evitar múltiples detecciones seguidas
    }
  } else {
    moveForward();
  }

  delay(100);  // Pequeño retraso para evitar lecturas erráticas
}

bool isBlueLine(int sensorValue) {
  // Lógica específica para detectar la línea azul
  return sensorValue < blueLineThreshold && sensorValue > orangeLineThreshold;
}

bool isOrangeLine(int sensorValue) {
  // Lógica específica para detectar la línea naranja
  return sensorValue < orangeLineThreshold;
}

void moveForward() {
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  analogWrite(ENABLE_PIN, speed);  // Velocidad actual
}

void turnLeft() {
  steeringServo.write(135);  // Ajustar el ángulo según sea necesario
}

void turnRight() {
  steeringServo.write(45);
}

void stopTurning() {
  steeringServo.write(90);  // Centrar el servo
}

void reduceSpeed() {
  speed = 150;  // Reducir la velocidad
  analogWrite(ENABLE_PIN, speed);
}

void increaseSpeed() {
  speed = 255;  // Aumentar la velocidad
  analogWrite(ENABLE_PIN, speed);
}

void checkLapCompletion() {
  if (detectionCounter >= 8) {  // Detecta 4 líneas azules y 4 líneas naranjas
    lapCounter++;
    detectionCounter = 0;  // Reinicia el contador de detecciones para la próxima vuelta
    Serial.print("Laps: ");
    Serial.println(lapCounter);
  }
}

void returnToStart() {
  // Mueve hacia atrás hasta que se encuentre a una distancia segura del muro trasero
  while (measureDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT) < 50) {
    moveBackward();
  }

  // Centra el servo
  stopTurning();

  // Mueve hacia adelante hasta que se encuentre a una distancia segura del muro delantero
  moveToParkingCoordinates();

  // Detenerse
  stopMoving();
  Serial.println("Race Completed! :D");
}

void moveBackward() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
  analogWrite(ENABLE_PIN, speed);  // Velocidad actual
}

void stopMoving() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  analogWrite(ENABLE_PIN, 0);
}

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;  // Convertir a milímetros
  return distance;
}

bool detectMagenta() {
  // Configurar el sensor TCS3200 para leer el color rojo
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  redFrequency = pulseIn(OUT, LOW);

  // Configurar el sensor TCS3200 para leer el color verde
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  greenFrequency = pulseIn(OUT, LOW);

  // Configurar el sensor TCS3200 para leer el color azul
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  blueFrequency = pulseIn(OUT, LOW);

  bool isMagenta = isColor(redFrequency, greenFrequency, blueFrequency, "magenta");

  // Guardar las coordenadas del aparcamiento magenta la primera vez que se detecta
  if (isMagenta && parkingCoordFront == -1 && parkingCoordRight == -1) {
    parkingCoordFront = measureDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT);
    parkingCoordRight = measureDistance(TRIG_PIN_RIGHT_LEFT, ECHO_PIN_RIGHT_LEFT);
    Serial.println("Parking coordinates saved.");
  }

  return isMagenta;
}

boolean isColor(int red, int green, int blue, String colorName) {
  // Aquí defines los rangos o umbrales para cada color
  if (colorName == "green") {
    // Ejemplo de umbral para detectar verde
    if (green > red && green > blue) {
      return true;
    }
  } else if (colorName == "red") {
    // Ejemplo de umbral para detectar rojo
    if (red > green && red > blue) {
      return true;
    }
  } else if (colorName == "magenta") {
    // Ejemplo de umbral para detectar magenta
    if (red > green && blue > green) {
      return true;
    }
  }

  return false;
}

void moveToParkingCoordinates() {
  if (parkingCoordFront != -1 && parkingCoordRight != -1) {
    // Moverse hacia adelante hasta las coordenadas del aparcamiento
    while (measureDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT) > parkingCoordFront) {
      moveForward();
    }
    stopMoving();

    // Moverse lateralmente hacia las coordenadas del aparcamiento
    while (measureDistance(TRIG_PIN_RIGHT_LEFT, ECHO_PIN_RIGHT_LEFT) > parkingCoordRight) {
      turnRight();
      moveForward();
    }
    stopTurning();
    stopMoving();

    adjustParking();
  }
}

void adjustParking() {
  // Ajusta la posición del coche para estacionarse entre las paredes magentas sin tocarlas
  stopMoving();

  while (measureDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT) > wallDistanceThreshold) {
    moveForward();
  }
  stopMoving();

  while (measureDistance(TRIG_PIN_RIGHT_LEFT, ECHO_PIN_RIGHT_LEFT) > wallDistanceThreshold) {
    turnRight();
    moveForward();
  }
  stopTurning();
  stopMoving();
  Serial.println("Parked between magenta walls.");
}
