// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009

#include <AFMotor.h>
#include <Servo.h>
//iniciando motores
AF_DCMotor motor(4);
AF_DCMotor motord(3);
Servo servo1;

int Modo=0; //Boton
int BotonArranque=0;

const int Trigger = A2;         //Pin digital A2 para el Trigger del sensor
const int Echo = A3;            //Pin digital A3 para el Echo del sensor

const int TriggerD = 3;         //Pin digital A2 para el Trigger del sensor
const int EchoD = 10;            //Pin digital A3 para el Echo del sensor

const int TriggerI = 11;         //Pin digital A2 para el Trigger del sensor
const int EchoI = 13;            //Pin digital A3 para el Echo del sensor


long distanciaSegura = 25;//Distancia Segura medida en cm
int distanciaSeguraLateral = 10; //Distancia medida en cm

int Desplazamiento=350; //tiempo del pulso al moverse
long cm_distancia=0;
long cm_distanciaD=0; //Distancia Derecha
long cm_distanciaI=0; // Distancia Izquierda

const int s0 = A0; //pines para el sensor de colores:
const int s1 = A1;  
const int s2 = A4;  
const int s3 = A5;  
const int out = 2;    

String colorr = "DESCONOCIDO"; //variable para guardar el color detectado

//Prototipos de las funciones
long distancia(int Tr, int Ec);
//void detener();
void adelante();
void atras();
void radar_centro();
void radar_derecha();
void radar_izquierda();
String  color_();

void setup() {
  //Serial.begin(9600);            set up Serial library at 9600 bps
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
  pinMode(TriggerI, OUTPUT); //pin como salida
  pinMode(EchoI, INPUT);  //pin como entrada
  pinMode(TriggerD, OUTPUT); //pin como salida
  pinMode(EchoD, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  digitalWrite (TriggerD, LOW);
  digitalWrite (TriggerI, LOW);
  //iniciar el Sensor de Colores
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite (s0, HIGH);
  digitalWrite(s1, HIGH);
 
  pinMode(BotonArranque,INPUT);//declaramos el boton de inicio como entrada
}
void loop() {
  //Boton de Activacion
  if(digitalRead(BotonArranque)==HIGH){
    if(Modo==0){
      Modo=1;
    }else{
      Modo=0;
    }
  }
 
  if(Modo==1){
     //Modo Autónomo
  radar_centro ();
 
  cm_distanciaD = distancia(TriggerD, EchoD);
  cm_distanciaI = distancia(TriggerI, EchoI);
  if (cm_distanciaI < distanciaSeguraLateral && cm_distanciaI != 0){
    radar_izquierda();
    atras();
    radar_derecha();
    cm_distancia = distancia(Trigger,Echo);
    if (cm_distancia > distanciaSegura){
    adelante;
    }
   radar_centro();
    }
  if (cm_distanciaD < distanciaSeguraLateral && cm_distanciaD != 0){
    radar_derecha();
    atras();
    radar_izquierda;
    cm_distancia = distancia(Trigger,Echo);
    if (cm_distancia > distanciaSegura){
    adelante;
    }
    radar_centro;
    }
    cm_distancia = distancia(Trigger,Echo);
  //Serial.print("distancia = ");
  //Serial.println(cm_distancia);
if (cm_distancia < distanciaSegura){
 
  colorr = color_();
  //Serial.println(colorr);
  if (colorr == "VERDE"){
    radar_derecha;
    atras();
    radar_izquierda();
    adelante();
    //radar_centro();
    adelante();
   radar_derecha ();
   adelante ();
   adelante();
   radar_centro();
  }
  else if (colorr == "ROJO"){
    radar_izquierda();
    atras ();
    radar_derecha();
    adelante();
    //radar_centro;
    adelante();
    radar_izquierda();
    adelante ();
    adelante();
    radar_centro();
  }
  else if (colorr == "NEGRO"){
 cm_distanciaD = distancia(TriggerD, EchoD);
  cm_distanciaI = distancia(TriggerI, EchoI);
  /*Serial.print("distanciaD = ");
  Serial.println(cm_distanciaD);
  Serial.print("distanciaI = ");
  Serial.println(cm_distanciaI);*/
  if (cm_distanciaD > cm_distanciaI){
    radar_izquierda;
    atras();
    radar_derecha();
     
    cm_distancia = distancia(Trigger,Echo);
    if (cm_distancia > distanciaSegura){
     adelante;
    }
    }
    else if (cm_distanciaI > cm_distanciaD){
      radar_derecha();
     atras();
    radar_izquierda();
    cm_distancia = distancia(Trigger,Echo);
    if (cm_distancia > distanciaSegura){
    adelante;
    }
      }else{
        atras();
        }
  }
}
 
    radar_centro();
    cm_distancia = distancia(Trigger,Echo);
    if (cm_distancia > distanciaSegura){
      adelante();
    }
  }
}



long distancia(int Tr, int Ec){
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(Tr, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Tr, LOW);
  t = pulseIn(Ec, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  return d;
}

void adelante(){
//Adelante
motor.setSpeed(190);
motord.setSpeed(190);
motor.run(FORWARD);
motord.run(FORWARD);
delay(Desplazamiento);
motor.run(RELEASE);
motord.run(RELEASE);
//delay(300);
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
//delay(300);
}

void detener(){
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

String color_(){
  String color = "DESCONOCIDO";
 int frecuencia;
 int rojo10;
 int verde10;
 int azul10;
 
 digitalWrite(s2, LOW);
  digitalWrite (s3, LOW);
  frecuencia = pulseIn (out, LOW);
  rojo10 = frecuencia / 10;
  //rojo = map (frecuencia, 3, 37, 255, 0);
  Serial.print("R:");
  Serial.print(rojo10);
  Serial.print(" ");
  delay (300);
  digitalWrite (s2, HIGH);
  digitalWrite (s3, HIGH);
  frecuencia = pulseIn (out, LOW);
  verde10 = frecuencia / 10;
  //verde = map(frecuencia, 4, 36, 255, 0);
  Serial.print("V:");
  Serial.print(verde10);
  Serial.print(" ");
  delay (300);
  digitalWrite (s2, LOW);
  digitalWrite (s3, HIGH);
  frecuencia = pulseIn (out, LOW);
  azul10 = frecuencia / 10;
  //azul = map(frecuencia, 3, 26, 255, 0);
  Serial.print("A:");
  Serial.print(azul10);
  Serial.print(" ");
  delay (300);
  if ((rojo10 == 36 && verde10 == 36 && azul10 == 26)||(rojo10 == 35 && verde10 == 36 && azul10 == 25)||(rojo10 == 35 && verde10 == 35 && azul10 == 25)||(rojo10 == 36 && verde10 == 36 && azul10 == 25)){
  color = "NEGRO";
  Serial.println("NEGRO");
  }else{
   if((rojo10>= 32 && rojo10<=34)&&(verde10>= 34 && verde10<=36) && (azul10 >= 24&&azul10<=26)){
    color = "ROJO";
    Serial.println("ROJO");
   }else{
    if((rojo10>= 29 && rojo10<=32)&&(verde10>= 33 && verde10<=36) && (azul10 >= 23&&azul10<=26)){
      color = "MAGENTA";
     Serial.println("MAGENTA");
    }
   }
   if((rojo10>= 34 && rojo10<=36)&&(verde10>= 33 && verde10<=36) && (azul10 >= 24&&azul10<=26)){
    color = "VERDE";
    Serial.println("VERDE");
   }

  }
  return color;
  }