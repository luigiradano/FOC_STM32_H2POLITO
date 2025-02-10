
#include "SVPWM_Full_singlePrecision.h"

#include <math.h>

#include "FOC_STM32_Types.h"

const float pi = 3.1415926535;
const float piThird = pi / 3;
const float norm2OverSqrt3 = 1.15470053838;  // 2/sqrt(3)

abcData_uint32 SVPWM_ComputeCCR(abcData_f tAbc, float switchPeriodSecond, uint32_t ARR) {
  abcData_uint32 output = {0, 0, 0};
  float dcA, dcB, dcC;

  if (switchPeriodSecond == 0)  // Avoid divison by zero
    return output;

  dcA = tAbc.a / switchPeriodSecond;
  dcB = tAbc.b / switchPeriodSecond;
  dcC = tAbc.c / switchPeriodSecond;

  output.a = ARR * dcA;
  output.b = ARR * dcB;
  output.c = ARR * dcC;

  return output;
}

abcData_f SVPWM_ComputeTimes(alphaBetaData_f vAb, float switchPeriodSecond, float vDc) {
  float theta, vRef, modulation;
  float Ta, Tb, Tz, thetaA, thetaB;
  uint8_t quadrant;
  abcData_f output = {0, 0, 0};

  if (vAb.alpha == 0 || vDc == 0)  // Avoid divison by zero
    return output;

  theta = atan(vAb.beta / vAb.alpha);

  if (theta < 0)
    theta = theta + pi;
  if (vAb.beta < 0)
    theta = theta + pi;

  vRef = sqrt(vAb.alpha * vAb.alpha + vAb.beta * vAb.beta);  // Compute absolute value of reference
  quadrant = ceil(theta / piThird);                          // Compute in which of the six quadrants is the reference
  modulation = (3.0f / 2) * (vRef / vDc);                    // Compute the modulation factor

  thetaA = quadrant * piThird;  // Angle of the first Space Vector
  thetaB = thetaA - piThird;    // Angle of the second Space Vector

  Ta = norm2OverSqrt3 * modulation * switchPeriodSecond * sin(thetaA - theta);
  Tb = norm2OverSqrt3 * modulation * switchPeriodSecond * sin(theta - thetaB);
  Tz = switchPeriodSecond - Ta - Tb;

  switch (quadrant) {
    case 1:
      output.a = Ta + Tb + Tz / 2;
      output.b = Tb + Tz / 2;
      output.c = Tz / 2;
      break;
    case 2:
      output.a = Ta + Tz / 2;
      output.b = Ta + Tb + Tz / 2;
      output.c = Tz / 2;
      break;
    case 3:
      output.a = Tz / 2;
      output.b = Ta + Tb + Tz / 2;
      output.c = Tb + Tz / 2;
      break;
    case 4:
      output.a = Tz / 2;
      output.b = Ta + Tz / 2;
      output.c = Ta + Tb + Tz / 2;
      break;
    case 5:
      output.a = Tb + Tz / 2;
      output.b = Tz / 2;
      output.c = Ta + Tb + Tz / 2;
      break;
    case 6:
      output.a = Ta + Tb + Tz / 2;
      output.b = Tz / 2;
      output.c = Ta + Tz / 2;
      break;
  }

  return output;
}
