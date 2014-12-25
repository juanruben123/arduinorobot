#include "movimiento.h"
#include "motor.h"
#include "PID_v1.h"

int ajuste;


//motores rueda0 (2,45,44);
//motores rueda1 (3,5,46);
movimiento mover(2, 45, 44, 3, 5, 46);

void setup() {
	TCCR5B = TCCR5B & B11111000 | 0x05;
	TCCR3B = TCCR3B & B11111000 | 0x05;

	pinMode(4,INPUT_PULLUP);
	pinMode(13, OUTPUT);
	pinMode(6, INPUT_PULLUP);
	pinMode(7, INPUT_PULLUP);

	attachInterrupt(0,sumar0,FALLING);
	attachInterrupt(1,sumar1,FALLING);

	Serial.begin(115200);
	Serial.flush();
}

void loop(){
	if (digitalRead(4)==LOW) {
//		mover.vel=0;
		mover.velocidadRueda = 0;
//		mover.rueda1.velocidadRueda = 0;
		mover.rueda0.velAng = 0;
		mover.rueda1.velAng = 0;
		mover.velAng = 0;
		mover.velocidadSupuesta = 0;
		mover.cambiar(512, 512);
//		ajustarVel();
		mover.myPID.SetMode(MANUAL);
		delay(10);
		mover.myPID.SetMode(AUTOMATIC);
//		mover.rueda1.myPID.SetMode(AUTOMATIC);
	}
//  Serial.print('+');
	mover.cambiar(analogRead(A1), analogRead(A0));
	mover.comprobarVel();
//	Serial.println(digitalRead(6));
//  serial();


//  mover.rueda0.mover(255);
//  mover.rueda1.mover(255);
  mover.fijarPeriodo();
//  Serial.print('\n');
//  delay(100);
}

void sumar0(){
	unsigned long tiempo =   millis() - mover.rueda0.ultMillis;
	if (tiempo > 20){
		mover.rueda0.velAng = mover.rueda0.velAng == 0 ? 100 * PI / tiempo : 
			10000 * PI / (tiempo* multiplicadorAjusteMedia2 + abs(100 * PI / mover.rueda0.velAng)* multiplicadorAjusteMedia1);
		mover.rueda0.ultMillis = millis();
		mover.rueda0.velAng = mover.rueda0.direccion ? -mover.rueda0.velAng : mover.rueda0.velAng;
	}
};

void sumar1(){
	unsigned long tiempo = millis() - mover.rueda1.ultMillis;
	if (tiempo > 20){
		mover.rueda1.velAng = mover.rueda1.velAng == 0 ? 100 * PI / tiempo :
			10000 * PI / (tiempo* multiplicadorAjusteMedia2 + abs(100 * PI / mover.rueda1.velAng)* multiplicadorAjusteMedia1);
		mover.rueda1.ultMillis = millis();
		mover.rueda1.velAng = mover.rueda1.direccion ? -mover.rueda1.velAng : mover.rueda1.velAng;
	}
};

/*void sumar1(){
	static unsigned long ultMillis = 0;
	if (millis() - ultMillis > 20){
		mover.contadorEncoder++;
		ultMillis = millis();
	}
}*/

/*void sumar1(){
//	mover.rueda1.velAng = mover.rueda1.velAng == 0 ? 10000 * PI / (millis() - mover.rueda1.ultMillis) : 10000 * PI / ((millis() - mover.rueda1.ultMillis)* multiplicadorAjusteMedia2 + abs(100 * PI / mover.rueda1.velAng)* multiplicadorAjusteMedia1);
//	mover.rueda1.ultMillis=millis();
}*/

/*void ajustarVel(){
    if (giro>1){
      mover.rueda0.fijarVel (vel);
      mover.rueda1.fijarVel (vel/giro);
      }
  else if (giro<-1){
      mover.rueda0.fijarVel (vel/-giro);
      mover.rueda1.fijarVel (vel);
      }
  else {
      mover.rueda0.fijarVel (vel);
      mover.rueda1.fijarVel (vel);
      }
    }*/




