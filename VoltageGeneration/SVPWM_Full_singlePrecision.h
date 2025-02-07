#include <math.h>

#include "FOC_STM32_Types.h"

#ifndef SVPWM_INC
#define SVPWM_INC

/*
 *  @brief  Computes the switching times give a certain reference given in the alpha-beta plane
 *
 *  @param  vAb                 AlphaBeta reference to produce at the output
 *  @param  switchPeriodSecond  Period of the PWM in seconds
 *  @param  vDc                 DC Voltage present at the input of the inverter stage
 *
 *  @return Returns the on times for the A,B,C phases
 */
abcData_f SVPWM_ComputeTimes(alphaBetaData_f vAb, float switchPeriodSecond, float vDc);

/*
 *  @brief  Computes the CCR times for the timers necessary to generate an alpha-beta reference
 *
 *  @param  tAbc                On times for each phase of the inverter, this should be obtained from SVPWM_ComputeTimes
 *  @param  switchPeriodSecond  Period of the PWM in the timer, in seconds
 *  @param  ARR                 Value of the ARR for the chosen timer
 */
abcData_uint32 SVPWM_ComputeCCR(abcData_f tAbc, float switchPeriodSecond, uint32_t ARR);

#endif
