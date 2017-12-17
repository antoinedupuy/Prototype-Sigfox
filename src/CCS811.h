#ifndef CCS811_H
#define CCS811_H
#include <Arduino.h>
// CCS811 - Air quality

// Exemple Git : https://github.com/AKstudios/CCS811-library
// Doc CCS811 : http://www.mouser.com/ds/2/588/CCS811_DS000459_4-00-1218958.pdf

// 1) On arrive a avoir des data eCO2 et TVOC
// 2) La data eCO2 pas coherente : eCO2 = 253, normalement 400 < eCO2 < 8192 ppm
//                                 TVOC = 253, OK car 0 < TVOC < 1187 ppb
// 3) Commencer à regarder envoi Sigfox
// 4) Reflechir au format d'envoi (int, HEX), optimisations etc..

#include <Wire.h>

#define nWAKE           4      // pin 4 is tied to CCS811 nWAKE pin in sensor node
#define nINT            7      // pin 7 is tied to CCS811 nINT pin in sensor node

//#define ADDR            0x5A   // when I2C_ADDR pin is LOW
#define ADDR            0x5B   // when I2C_ADDR pin is HIGH

// Registers for CCS811
#define STATUS          0x00
#define MEAS_MODE       0x01
#define ALG_RESULT_DATA 0x02
#define ENV_DATA        0x05
#define APP_START       0xF4
#define HW_ID           0x20
#define ERROR_ID        0xE0
#define SW_RESET        0xFF

// Modes de mesure
#define MODE_CONST 0x10         //1mesure/sec

// Déclencher une mesure
bool writeMeasureMode(byte address, byte mode);

//Accèder aux variables CO2 et TVOC depuis le main (on évite ainsi la rédifinition multiple si on les déclarait dans le .h
byte getCO2();
byte getTVOC();

// Lire eCO2 et TVOC à partir de la dernière mesure
void readData(void);

//Affichage des données du capteurs CCS811 dans le moniteur série
void displayDataCCS811();

//Initialiser le capteur d'air
void CCS811init();

#endif
