
#ifndef SIGFOXNETWORK_H
#define SIGFOXNETWORK_H

#include <SigFox.h>

typedef struct __attribute__ ((packed)) sigfox_message {
  //int8_t moduleTemperature; //Soit 1 octet sur les 12 dispos
  int16_t CO2; //On utilisera 2 octets pour la valeur du C02 (car valeur oscillera entre 400 et 10 000, donc entre 9 et 14 bits)
  int8_t TVOC; //1 octets pour le TVOC
} SigfoxMessage;

//Redémmarer le système
void reboot();

//Intialiser la communication Sigfox
void sigfoxInit(SigfoxMessage msg);

//Envoyer les données sur Sigfox
void sendDataSigfox(SigfoxMessage msg);

#endif
