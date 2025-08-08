#pragma once
#ifndef LPIT_CONFIG_H
#define LPT_CONFIG_H

#include <stdint.h>

void LPIT_Config(int channel, float timerSecond);
void LPIT_Disable(int channel);

#endif