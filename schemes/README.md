# Diagramas Electromecánicos
### Podran ver en fotos y archivos los esquemas de la propia plataforma del robot, del sistema de dirección y del circuito eléctrico. 

## Esquemático y diseño del circuito eléctrico
Para hacer el esquemático usamos el software Fritzing, si desea ver con mas detalle o modificar el circuito deberá de tenerlo descargado. Descargar Fritzing: https://fritzing.org/download

[Archivo del circuito](Primera_ronda_wro.fzz) Descarga del archivo del circuito eléctrico.

[Imagen del circuito](Primera_ronda_wro.fzz.jpeg) Imagen del archivo del circuito eléctrico.

[Diseño del circuito eléctrico](Diseño_del_circuito_eléctrico.jpeg)
El diseño es muy parecido al setup real del circuito, la única diferencia es el medio en donde fueron construidos, el real en placa perforadas y este con ayuda de una protoboard.

[Esquematico del circuito eléctrico](Esquematico_del_circuito.jpeg)
Una vista mas clara de cada modelo de forma esquematica y sus conexiones.

## Diagramas del chasis y el sistema de dirección
Estos diagramas no tienen su medición en las fotos, las mediciones están en la descripción de cada foto. Los diagramas se hicieron en una hoja milímetrada, cada cuadrado mide 0.5cm. Para la dirección nos inspiramos en hacerla de este video: https://www.youtube.com/watch?v=0pgU9oZoR14

[Diagramas del carro](Chasis_de_la_plataforma_del_carro_y_soportes_de_la_dirección.jpeg)
Se dividen en 3 piezas, plataforma del carro, rectangulos en paralelo y piezas de forma circular al final dibujadas en la parte delantera de la plataforma:
-  La plataforma tiene un largo de 17.5cm, al principio se penso hacerlo de 15cm, pero para solucionar problemas de espacio se decidio ampliar el largo, el ancho del frente y atras es de 7cm y el ancho del medio es de 9cm.
-  Los rectángulos que estan dibujados de forma paralela miden 2.6cm de largo y 0.7cm de ancho.
-  Las piezas dibujadas junto con la parte delantera del chasis y las ruedas, sostienen las piezaz de la balineras, son 4 piezas que hacer, en la parte de arriba y abajo. Esta pieza mide 2.3cm de largo y 0.8cm de ancho.

[Pieza de la balinera](Pieza_para_la_balinera.jpeg)
Mediciones de cada parte de la pieza:
-  La pieza tiene un diametro de 2.3cm, el círculo grande del medio (no el chico) tiene un diametro de 1.8cm. El círculo grande del medio va vacío ya que este círculo es donde va la balinera.
-  Las patitas sobresalientes donde va la lanza tienen un ancho de 0.3cm, el espacio que los separa es de 0.4cm y un largo de 1cm, tanto como la patita como el espacio vacío.

[Diseño de la lanza](Lanza_de_la_dirección_anterior.jpeg)
La lanza tiene un largo de 8cm y un ancho de 0.8cm ademas de la lanza anterior para el nuevo diseño del carro nos guiamos de la misma, para hacer el [diseño de la lanza nueva.](Lanza_de_la_dirección_nueva.jpeg).

[MRU](Movimiento_rectilíneo_uniforme.jpeg)
para calcular la velocidad lineal usamos un metro y pusimos la punta del carro en el inicio del metro y calculamos el tiempo en el recorria el metro, nos dio los siguiente resultados: 75,85 y 88 milisegundos de ellos sacamos el promedio que fue 83 y tener un aproximado de velocidad; llegamos a la conclución que la velocidad maxima del carrito es 1.20m/s. 

## Desglose de Corrientes en mA
- Arduino Uno R4: ~70 mA
- Sensor ultrasónico HC-SR04: ~15 mA
- Puente H L298N: ~30 mA
- Motor DC: ~250 mA 
- Servo SG-92: ~250 mA (en movimiento)

### Cálculo del Consumo Total de Corriente
- Arduino Uno R4: 70 mA
- 3 Sensores ultrasónicos HC-SR04: 3 * 15 mA = 45 mA
- Puente H L298N: 30 mA
- Motor DC: 250 mA
- Servo SG-92: 250 mA

Consumo total: 655mA


## Actualización del Desglose de Corrientes en mA
Arduino Uno R3: ~50 mA
Sensor ultrasónico HC-SR04: ~15 mA
Puente H L298N: ~30 mA
Motor DC: ~250 mA
Servo SG-92: ~250 mA (en movimiento)

### Cálculo del Consumo Total de Corriente
Arduino Uno R3: 50 mA
3 Sensores ultrasónicos HC-SR04: 3 * 15 mA = 45 mA
Puente H L298N: 30 mA
Motor DC: 250 mA
Servo SG-92: 250 mA

Consumo total: 50 + 45 + 30 + 250 + 250 = 625 mA
