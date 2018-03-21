#ifndef DUST_H
#define DUST_H

#include <Arduino.h>
#include "sigfoxNetwork.h"

/* Dust Density in µg/m3 */
#define DUST_OUT A2
#define DUST_IN 5

void readDust(SigfoxMessage * msg);

#endif
