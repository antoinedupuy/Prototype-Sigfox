#ifndef SIGFOXNETWORK_H
#define SIGFOXNETWORK_H

#include <SigFox.h>

typedef struct __attribute__ ((packed)) sigfox_message { // see http://www.catb.org/esr/structure-packing/#_structure_alignment_and_padding
  int8_t moduleTemperature; //Soit 1 octet sur les 12 dispos
  int8_t temp2;
} SigfoxMessage;

//Redémmarer le système
void reboot();

//Intialiser la communication Sigfox
void sigfoxInit(SigfoxMessage msg);

//Envoyer les données sur Sigfox
void sendDataSigfox(SigfoxMessage msg);

#endif
