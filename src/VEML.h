#ifndef VEML_H
#define VEML_H
#include <SigFox.h>
#include <Wire.h>
#include "sigfoxNetwork.h"
#define VEML6030_ADDR  0x48

void initVEML();
void readVEML(SigfoxMessage * msg);

#endif
