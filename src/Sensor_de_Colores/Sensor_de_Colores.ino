const int s0 = A0;  
const int s1 = A1;  
const int s2 = A4;  
const int s3 = A5;  
const int out = 2;  
int frecuencia;  
int rojo10;
int verde10;
int azul10;
long cm_distancia=0;

void setup(){  
  Serial.begin(9600);
  pinMode(s0,OUTPUT);  
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW);  
}  

void loop(){  
 
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
  Serial.println("NEGRO");
  }else{
   if((rojo10>= 32 && rojo10<=34)&&(verde10>= 34 && verde10<=36) && (azul10 >= 24&&azul10<=26)){
    Serial.println("ROJO");
   }else{
    if((rojo10>= 29 && rojo10<=32)&&(verde10>= 33 && verde10<=36) && (azul10 >= 23&&azul10<=26)){
     Serial.println("MAGENTA");
    }
   }
   if((rojo10>= 34 && rojo10<=36)&&(verde10>= 33 && verde10<=36) && (azul10 >= 24&&azul10<=26)){
    Serial.println("VERDE");
   }

  }
 
}