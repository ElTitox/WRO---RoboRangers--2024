#include <Servo.h>

// Pines del puente H L298N para el motor DC
const int enB = 9;
const int in3 = 8;
const int in4 = 7;

// Servo motor
Servo servoMotor;
const int servoPin = 6;  // Pin del servo motor

// Variables de rotación
const int RotacionInicialServo = 78;  // Ángulo inicial del servo motor

// Pines de los sensores ultrasónicos
#define TRIG_PIN_R 2
#define ECHO_PIN_R 3
#define TRIG_PIN_L 12
#define ECHO_PIN_L 11
#define TRIG_PIN_F 4  // Definir el pin TRIG para el sensor frontal
#define ECHO_PIN_F 5  // Definir el pin ECHO para el sensor frontal

// Pines del sensor de color TCS3200
const int S0 = A0;  
const int S1 = A1;  
const int S2 = A2;  
const int S3 = A3;  
const int salidaTCS = A4; 
const int ledPin = 13;  

// Variable para controlar si la lógica ya fue ejecutada
bool logicaEjecutada = false;

// Constantes para las rotaciones
const int RotacionesPorTiempo = 100;  // Constante de rotación por tiempo

void setup() {
  // Configuración de los pines del puente H
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Configuración del servomotor
  servoMotor.attach(servoPin);
  servoMotor.write(RotacionInicialServo);  // Servo recto a 78°

  // Configuración de los pines de los sensores ultrasónicos
  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);
  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);
  pinMode(TRIG_PIN_F, OUTPUT);  // Configurar TRIG del sensor frontal
  pinMode(ECHO_PIN_F, INPUT);    // Configurar ECHO del sensor frontal
  
  // Configuración del sensor de color
  pinMode(S0, OUTPUT);		// pin 4 como salida
  pinMode(S1, OUTPUT);		// pin 5 como salida
  pinMode(S2, OUTPUT);		// pin 6 como salida
  pinMode(S3, OUTPUT);		// pin 7 como salida
  pinMode(salidaTCS, INPUT);	// pin 8 como salida
  
  digitalWrite(S0,HIGH);	// establece frecuencia de salida
  digitalWrite(S1,LOW);		// del modulo al 20 por ciento
  
  // Inicialización del Serial (opcional, para debug)
  Serial.begin(9600);
  Serial.println("Iniciando el sistema...");
}

// Función para medir distancia (en centímetros)
float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2.0) / 58.0;  // Conversión a centímetros
  return distance;
}

// Función para medir distancia basada en la dirección
float measure(char C) {
  if (C == 'R') {
    return measureDistance(TRIG_PIN_R, ECHO_PIN_R);
  } else if (C == 'L') {
    return measureDistance(TRIG_PIN_L, ECHO_PIN_L);
  } else if (C == 'F') {
    return measureDistance(TRIG_PIN_F, ECHO_PIN_F); // Medir el frente
  }
  return -1; // Si no es una dirección válida
}

// Función de movimiento al máximo
void movimientoMaximo() {
  Serial.println("Moviendo hacia adelante a máxima velocidad...");
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  // Motor hacia adelante
  analogWrite(enB, 255);    // Velocidad máxima del motor
}

// Función para mover hacia atrás
void moveBack(int rotaciones) {
  int tiempoDeRotacion = rotaciones * RotacionesPorTiempo;
  Serial.println("Moviendo hacia atrás...");
  
  // Mover hacia atrás
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // Iniciar el motor a velocidad máxima
  analogWrite(enB, 255);
  
  delay(tiempoDeRotacion);  // Esperar el tiempo de rotación

  // Apagar el motor al finalizar
  analogWrite(enB, 0);
  Serial.println("Movimiento hacia atrás completado.");
}

// Función para girar rápidamente a la derecha
void rotateRightFast(int rotaciones) {
  int tiempoDeRotacion = rotaciones * RotacionesPorTiempo;
  Serial.println("Girando rápidamente a la derecha...");
  servoMotor.write(180);
  delay(tiempoDeRotacion);  // Tiempo de giro
  Serial.println("Giro a la derecha completado.");
}

// Función para la lógica del giro y decisiones
void logicaMovimiento() {
  // El servo gira 65° para iniciar el giro
  Serial.println("Iniciando movimiento lógico...");
  servoMotor.write(62);  
  delay(500);  // Espera a que el servo complete el giro

  // Encender el motor por 200 milisegundos
  analogWrite(enB, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  // Motor hacia adelante
  delay(250);  // Motor encendido por 250 ms
  
  // Apagar el motor
  analogWrite(enB, 0);
  servoMotor.write(88);

  // El carro continuará girando por inercia 82°
  delay(500);  // Simular inercia

  // Medir la distancia frontal
  float distanciaFrontal = measure('F');
  Serial.print("Distancia al frente: ");
  Serial.println(distanciaFrontal);

  // Si la distancia es mayor a 100 cm (1 metro), cambiar de línea
  if (distanciaFrontal > 25.0) {
    Serial.println("Distancia mayor a 100 cm, cambiar de línea.");
    // Llamar a la corrección de línea
    lineCorrection();
  } else {
    analogWrite(enB, 0);
    Serial.println("Distancia menor a 100 cm, implementar lógica después.");

    // Sensor de color
    digitalWrite(S2, LOW);			// establece fotodiodos con filtro rojo
    digitalWrite(S3, LOW);			
    int rojo = pulseIn(salidaTCS, LOW);	
    delay(200);				// demora de 200 mseg
    
    digitalWrite(S2, HIGH);		// establece fotodiodos con filtro verde
    digitalWrite(S3, HIGH);		
    int verde = pulseIn(salidaTCS, LOW);	
    delay(200);				// demora de 200 mseg
    
    digitalWrite(S2, LOW);			// establece fotodiodos con filtro azul
    digitalWrite(S3, HIGH);		
    int azul = pulseIn(salidaTCS, LOW);	
    delay(200);				// demora de 200 mseg
    
    Serial.print("R:");			
    Serial.print(rojo);			
    Serial.print("\t");			
    
    Serial.print("V:");			
    Serial.print(verde);			
    Serial.print("\t");			

    if (rojo < 208 && verde > 428 && azul > 312) {		
      Serial.println("ROJO");				
      // Imprimir mensaje cuando se identifica el rojo
      Serial.println("¡Se detectó el color ROJO!");  
      // Gira 62° y luego retrocede
      servoMotor.write(62);  
      delay(700);  // Esperar que el servo complete el giro
      moveBack(3.5);  // Llamar a moveBack con 3.5 rotaciones
      analogWrite(enB, 0); // Detener el carro después de retroceder
    } 
    else if (verde < 541 && rojo > 446 && azul > 347) {	
      Serial.println("VERDE");				
      // Imprimir mensaje cuando se identifica el verde
      Serial.println("¡Se detectó el color VERDE!");  
      // Gira 110° y luego retrocede
      servoMotor.write(110);  
      delay(700);  // Esperar que el servo complete el giro
      moveBack(3.5);  // Llamar a moveBack con 3.5 rotaciones
      analogWrite(enB, 0); // Detener el carro después de retroceder
    }
  }
}

// Función para la corrección de línea
void lineCorrection() {
  Serial.println("Iniciando corrección de línea...");
  rotateRightFast(100);  // Rotar rápidamente
  delay(500);  // Esperar que el servo complete el giro

  // Después de la corrección, reanudar el movimiento
  movimientoMaximo();
}

// Función principal loop
void loop() {
  // Medir la distancia del sensor frontal
  float distanciaFrontal = measure('F');

  // Si la distancia es menor a 100 cm, activar la lógica
  if (distanciaFrontal < 100 && !logicaEjecutada) {
    logicaEjecutada = true;  // Evitar que la lógica se ejecute múltiples veces
    logicaMovimiento();
  } 
  else if (distanciaFrontal >= 100) {
    logicaEjecutada = false;  // Reiniciar la lógica cuando la distancia es segura
    movimientoMaximo();
  }
}