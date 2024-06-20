const int s0 = A0;  
const int s1 = A1;  
const int s2 = A4;  
const int s3 = A5;  
const int out = 2;    
int rojo = 0;  
int verde = 0;  
int azul = 0;  
int dv=0;
int da=0;
int dr=0;

void setup(){  
  Serial.begin(9600);
  pinMode(s0,OUTPUT);  
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);  
  digitalWrite(s0,HIGH);  
  digitalWrite(s1,HIGH);  
}  

   
void loop(){  
  color();
  Serial.print("R: ");  
  Serial.print(rojo, DEC);  
  Serial.print(" G: ");  
  Serial.print(verde, DEC);  
  Serial.print(" B: ");  
  Serial.print(azul, DEC);
  

  if(azul>verde && azul>rojo){
   dv=azul-verde;
   dr=azul-rojo;
   if(dr>5 && dv>5){ 
    Serial.println(" Azul");
   }else{
     Serial.println(" ");
   } 
  } else{
    if(verde>azul && verde>rojo){
      dr = verde - rojo;
      da = verde - azul;
      if (dr > 5 && da > 5){
      Serial.println(" Verde");
      }else{
      Serial.println (" ");
    }
    }else{
      if(rojo>azul && rojo>verde){
        dv = rojo - verde;
        da = rojo - azul;
        if (dv > 5 && da > 5){
        Serial.println(" Rojo");
        }else {
          Serial.println(" ");
        }
      }
      else{
        Serial.println(" ");
      }
    }
  }
  delay(900);    
}  
   
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(300);  
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);  
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  delay(300);
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, HIGH);    
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 
  delay(300); 
  rojo=255-rojo;
  verde=263-verde;
  azul=238-azul;
}