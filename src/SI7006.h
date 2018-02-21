#ifndef SI7006_H
#define SI7006_H
#include <stdint.h>
#include <Wire.h>
#include <SigFox.h>
#include "sigfoxNetwork.h"
#define SI7006_ADDR  0x40

void readSI7006(SigfoxMessage * msg);

#endif
