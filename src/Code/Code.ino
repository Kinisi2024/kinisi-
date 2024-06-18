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
int Desplazamiento=900;
long cm_distancia=0;
const int s0 = A0;  
const int s1 = A1;  
const int s2 = A4;  
const int s3 = A5;  
const int out = 2;    
int rojo = 0;  
int verde = 0;  
int azul = 0;

//Prototipos de las funciones
long distancia();
void stop();
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
  //iniciar el Sensor de Colores
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite (s0, HIGH);
  digitalWrite(s1, LOW);
}
void loop() {
  digitalWrite(s2, LOW);
  digitalWrite (s3, LOW);
  rojo = pulseIn (out, LOW);
  delay (200);
  digitalWrite(s2, HIGH);
  digitalWrite (s3, HIGH);
  verde = pulseIn (out, LOW);
  delay(200);
  digitalWrite(s2, LOW);
  digitalWrite (s3, HIGH);
  azul = pulseIn (out, LOW);
  delay(200);

  Serial.print("R:");
  Serial.print(rojo);
  Serial.print("\t");
   Serial.print("V:");
  Serial.print(verde);
  Serial.print("\t");
   Serial.print("A:");
  Serial.print(azul);
  Serial.print("\t");
  if (rojo < 40 && verde > 50 && azul < 40) {
    Serial.println ("ROJO");}
  if (rojo > 55 && verde < 60 && azul < 35){
    Serial.println ("AZUL");}
  if (rojo < 65 && verde < 50 && azul > 40){
    Serial.println ("VERDE");}
     //Modo Autónomo
        radar_centro();
        cm_distancia=distancia();
        if(cm_distancia>DistanciaSegura){
          adelante();
        }
    else{
      stop();
          radar_derecha();
          cm_distancia = distancia();
  if(cm_distancia>DistanciaSegura){
            adelante();
            delay (1000);
            radar_centro();
          }else{
          radar_izquierda();
          cm_distancia = distancia ();
     if (cm_distancia>DistanciaSegura){
                adelante();
                delay(1000);
                radar_centro ();
            }else{
    atras();
            }
        }
        }
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
motor.setSpeed(180);
motord.setSpeed(180);
motor.run(FORWARD);
motord.run(FORWARD);

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

void stop(){
  //detener
  motor.run (RELEASE);
  motord.run (RELEASE);
}

void radar_centro(){
//Centro
servo1.write(86);
delay(300);        
}

void radar_derecha(){
//Derecha
servo1.write(56);
delay(300);
}

void radar_izquierda(){
//Izquierda
servo1.write(116);
delay(300);
}