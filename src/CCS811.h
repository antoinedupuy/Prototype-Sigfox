#ifndef CCS811_H
#define CCS811_H

#include <Arduino.h>
#include "sigfoxNetwork.h"
#include <SparkFunCCS811.h>

void displayDataCCS811(SigfoxMessage * msg);
void CCS811init();

#endif
