# Robo Rangers 

## Los integrantes del equipo son:
- Eldens Quintero  (Coordinador del equipo)  
- Hezir Corrales (Constructor del robot)
- Jose Gutierrez (Programador)
  
## Institución: Instituo América 
- Tutor: Hector Ortega
  
## Breve resumen del diseño:
Diseñamos el robot en sus inicios con distintos materiales como: ganchos de ropa, tubos de PVC, plastico de botella anticongelante y laminas de acrílico. Concluimos en diseñarlo con una lamina de placa perforada. Al inicio pensabamos en hacerlo de 15cm de largo, pero decidimos ampliar unos 3cm de largo y tenga un buen ancho para la bateria y sensores para que los demas componentes quepan de manera mas ordenada. LLegamos a diseñar nuestro sistema de dirección, más adelante entramos en detalles en los sistemas y programación del robot. 

### Materiales:                                                                                                                
-  PVC                                                                                                                         
-  Lamina de acrilico                                                                                                           
-  Placa perforada                                                                                                                  
-  Tornillos con sus tuercas                                                                                                    
-  Tacos azules para soporte                                                                                                   
-  Nanocinta acrílica doble contacto                                                                                            
-  Rollo de Estaño y Flux                                                                                                      
-  Clavos y tornillos                                                                                                           
-  Sunchos                                                                                                                      

### Herramientas:
-  Taladro con diferentes brocas y lijas
-  Arco Calar
-  Cautin
-  Destornilladores punta plana
-  Destornillador punta de estrella
-  Alicate
-  Pinza Pelacables
-  Pinza punta plana
-  multimetro

### Componentes:
-  base: hecha por una placa perforada
-  batería: 2 pilas recargables de litio conectadas en serie de 3,200mah
-  sensores: 3 sensores ultrasónicos HC-S04, 1 sensor de color TCS3200
-  ARDUINO 1 R3
-  Servo: 2 servo motores SG90
-  Puente H 298N
-  Motor DC12V
-  Cables: Macho-Macho, Macho-Hembra y Cable Rígido
-  Switch on/off

## Procedimientos de contruccion del carro:

[Construccion y procedimiento del carro ](./other/)

- Construcción de la base del carro:  
Usamos la placa fenólica (placa perforada) de base para nuestro coche, esta placa tambien nos sirve para hacer conexiones de cables con soldadura.
En ella colocamos un motor de 12V en la parte trasera, en el centro de la placa un Rack de Baterias en serie, 3 sensores ultrasonicos, 4 Taquillos plasticos azules atornillados en vertical desde abajo, y en la parte delantera un sistema de direccion hecha con PVC y operadas por un servo mediante un alambre de aluminio con el calibre suficiente para ser moldeado pero preferiblemente que sea duro.

- Colocación de elementos:  
Sobre el motor colocamos Puente H Doble con pegamento epoxy, los 4 tacos plasticos azules sirven de soporte para colocar un Arduino 1 R3 a su vez dan espacio para colocar y retirar las pilas con mayor facilidad.

  Los sensores ultrasonicos van colocado en los extremos Norte, Este y Oeste del carro midiendo la pista a los lados y delante.
  Los 2 sensores ultasonicos laterales van colocados en los bordes del Rack de la bateria con cinta adhesiva doble contacto y el sensor delantero es sostenido sobre un servo motor para que se mueva como un radar, colocado arriba del sensor de color. 


- Parte trasera del carro:  
El motor se modifico con una caja de cambio, esta se encuentra ubicada en la parte de atras y se mantiene en su lugar usando una corra de cuero atornillada a la placa fenólica y usando una tecnica de pegado con Pegamento (cianoacrilato) y Poliestireno.
En la parte inferior izquierda de la placa fenolica conectamos y soldamos todos los cables negativos (tierra común) y al otro lado todos los positivos de forma que la bateria alimenta al puenta H con un intervalo de 11.1V a 12.6V y a todo el circuito con 5V regulado por el puente H.

- Parte delantera del carro:  
El [sistema de direccion](schemes/Lanza_de_la_dirección.jpeg) esta hecha con PVC unidas con pegamento epoxy, usamos balineras y clavos para sostener y permitir el giro de las ruedas, por ultimo la Lanza de la direccion (hecha de PVC) y unida servo con un alambre para que está se mueva. El Servo sobresale por la parte superior para facilitar la conexion de los pines hacia el arduino y no estorbe en el giro del carro; ademas agregamos un sensor de color TCS3200 lo cual nos ayudara a la hora de la segunda ronda donde el carro tendra que dectectar los colores.
