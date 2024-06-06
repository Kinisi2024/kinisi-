// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009

#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motor(4);
AF_DCMotor motord(3);
Servo servo1;
const int Trigger = A2;         //Pin digital 2 para el Trigger del sensor
const int Echo = A3;            //Pin digital 3 para el Echo del sensor
long DistanciaSegura = 70;//Distancia Segura medida en cm
int Desplazamiento=500;
long cm_distancia=0;

//Prototipos de las funciones
long distancia();
void adelante();
void atras();
void radar_centro();
void radar_derecha();
void radar_izquierda();

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  // turn on motor
  //Ajustar Base del Sensor de Distancia
  servo1.attach(9);
  radar_derecha();
  radar_centro();
  radar_izquierda();
  radar_centro();
  //Iniciar Sensor de Distancia
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
}
void loop() {
  
}

long distancia(){
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  return d;
}

void adelante(){
//Adelante
motor.setSpeed(220);
motord.setSpeed(220);
motor.run(FORWARD);
motord.run(FORWARD);
delay(Desplazamiento);
motor.run(RELEASE);
motord.run(RELEASE);
delay(300);
}

void atras(){
//Atras
motor.setSpeed(220);
motord.setSpeed(220);
motor.run(BACKWARD);
motord.run(BACKWARD);
delay(Desplazamiento);
motor.run(RELEASE);
motord.run(RELEASE);
delay(300);
}

void radar_centro(){
//Centro
servo1.write(90);
delay(300);        
}

void radar_derecha(){
//Derecha
servo1.write(60);
delay(300);
}

void radar_izquierda(){
//Izquierda
servo1.write(130);
delay(300);
}