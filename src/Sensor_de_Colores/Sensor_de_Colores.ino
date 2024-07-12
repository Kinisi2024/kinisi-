#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Arreglo para representar la funcion gamma
int gammatable[256];

// Inicializar un objeto tcs con tiempo de integracion de 600 ms y ganancia de 16x
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_16X);

// Definir estructura para almacenar valores de calibracion blanco y negro
struct colorCalibration {
  unsigned int blackValue;
  unsigned int whiteValue;
};

colorCalibration redCal, greenCal, blueCal;


void setup() {
  // Iniciar TCS3472 I2C
  if (tcs.begin()) {
   //Encontrado
  } 
  else {
    //No encontrado
    while (1); // Detener
  }

  redCal.blackValue = 4703;
  redCal.whiteValue = 49027;
  greenCal.blackValue = 4373;
  greenCal.whiteValue = 65535;
  blueCal.blackValue = 4028;
  blueCal.whiteValue = 65535;


  // Gamma function is Out = In^2.5
  // Required to correct for human vision
  // Store values in an array
  // normalized for 0 to 255
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    gammatable[i] = int(x);
    }  
}


void loop() {
  unsigned int r, g, b, c; 
  // Variables 0 - 255
  int redValue;
  int greenValue;
  int blueValue;
  int clearValue;
    tcs.getRawData(&r, &g, &b, &c);
 
    redValue = RGBmap(r, redCal.blackValue, redCal.whiteValue, 0, 255);
    greenValue = RGBmap(g, greenCal.blackValue, greenCal.whiteValue, 0, 255);
    blueValue = RGBmap(b, blueCal.blackValue, blueCal.whiteValue, 0, 255);

  }
  
}


int RGBmap(unsigned int x, unsigned int inlow, unsigned int inhigh, int outlow, int outhigh){
  float flx = float(x);
  float fla = float(outlow);
  float flb = float(outhigh);
  float flc = float(inlow);
  float fld = float(inhigh);

  float res = ((flx-flc)/(fld-flc))*(flb-fla) + fla;

  return int(res);
}
