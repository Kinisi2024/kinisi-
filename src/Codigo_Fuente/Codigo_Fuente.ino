// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009

#include <AFMotor.h>
#include <Servo.h>
//iniciando motores
AF_DCMotor motor(4);
AF_DCMotor motord(3);
Servo servo1;

int modo=0; //Boton
int botonArranque=0;

const int Trigger = A2;         //Pin digital A2 para el Trigger del sensor
const int Echo = A3;            //Pin digital A3 para el Echo del sensor

const int TriggerD = 3;         //Pin digital A2 para el Trigger del sensor
const int EchoD = 10;            //Pin digital A3 para el Echo del sensor

const int TriggerI = 11;         //Pin digital A2 para el Trigger del sensor
const int EchoI = 13;            //Pin digital A3 para el Echo del sensor

int distanciaSegura = 50;//Distancia Segura medida en cm
int distanciaSeguraLateralI = 22; //Distancia medida en cm
int distanciaSeguraLateralD = 19; //Distancia medida en cm

int Desplazamiento=700; //tiempo del pulso al moverse
long cm_distancia=0;
long cm_distanciaD=0; //Distancia Derecha
long cm_distanciaI=0; // Distancia Izquierda
int SumaLaterales;

const int s0 = A0; //pines para el sensor de colores:
const int s1 = A1;
const int s2 = A4;
const int s3 = A5;
const int out = 2;  

String colorr = "DESCONOCIDO"; //variable para guardar el color detectado

unsigned long Tiempo1;
unsigned long Tiempo2;
unsigned long Tiempo3;
unsigned long Tiempo_Prim_Esq;
int nro_esquinas;
int nro_vueltas;
int esquina;
int esquinaOld;

//Prototipos de las funciones
long distancia(int Tr, int Ec);
void detener();
void adelante();
void atras();
void radar_centro();
void radar_derecha();
void radar_izquierda();
String  color_();

void setup() {
  Serial.begin(9600);       //     set up Serial library at 9600 bps
  // turn on motor
  //Ajustar Base del Sensor de Distancia
  Tiempo1 = millis();
  servo1.attach(9);
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
 
// pinMode(BotonArranque,INPUT);//declaramos el boton de inicio como entrada
  adelante();
}

void loop() {
cm_distancia = distancia(Trigger, Echo);
cm_distanciaD = distancia(TriggerD, EchoD);
cm_distanciaI = distancia(TriggerI, EchoI);

Serial.println(cm_distancia);
Serial.println(cm_distanciaD);
Serial.println(cm_distanciaI);

//detecta la esquina
if(cm_distancia < 110 && ((cm_distanciaD > 80) || (cm_distanciaI > 80))){
  esquina = 1;
  Serial.println("Esquina=1");
}
    else if (cm_distancia > 110 && cm_distanciaD < 80 && cm_distanciaI < 80){
  esquina = 0;
  Serial.println("Esquina=0");
}
//acciones si esta en una esquina
if (esquina == 1){
  if (cm_distanciaD > 80){
   radar_derecha();
    delay (1050);
    radar_centro();
  }
  if (cm_distanciaI > 80){
    radar_izquierda();
    delay(1050);
    radar_centro();
  }
}
//acciones si esta en una recta
if (esquina == 0){
  radar_centro();
  if (cm_distancia > 110){
  if(cm_distanciaD<distanciaSeguraLateralD){
  radar_izquierda();
  delay (40);
  radar_centro();
}
if(cm_distanciaI<distanciaSeguraLateralI){
  radar_derecha();
  delay(40);
  radar_centro();
}
}
   
    }
//contador de vueltas
if (esquinaOld == 0 && esquina == 1){
        nro_esquinas++;
    }
   
if(nro_esquinas == 4){
    nro_vueltas++;
    nro_esquinas = 0;
}

if(nro_vueltas==3){
    detener();
}
  esquinaOld = esquina;
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
motor.setSpeed(135);
motord.setSpeed(135);
motor.run(FORWARD);
motord.run(FORWARD);
/*delay(Desplazamiento);
motor.run(RELEASE);
motord.run(RELEASE);*/
//delay(300);
}

void atras(){
//Atras
motor.setSpeed(180);
motord.setSpeed(180);
motor.run(BACKWARD);
motord.run(BACKWARD);
delay(Desplazamiento);
motor.run(RELEASE);
motord.run(RELEASE);
delay(300);
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
servo1.write(53);
delay(300);
}

void radar_izquierda(){
//Izquierda
servo1.write(119);
delay(300);
}
