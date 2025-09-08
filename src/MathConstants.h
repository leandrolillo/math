/*
 * mathConstants.h
 *
 *  Created on: 29/06/2013
 *      Author: Lean
 */

#pragma once

#include<math.h>
#include<float.h>
#include<string>

//typedef float real;
using real = float;
using String = std::string;

#define null nullptr

#ifndef _REAL_POW
  #define _REAL_POW
  #define powr powf
#endif

constexpr real DELTA = (real)0.005;
constexpr real one_over_rand_max = ((real)1 / (real)RAND_MAX);

#ifndef M_PI  // algunos math.h no lo definen, como el de visual studio.
  #define M_PI (real)3.14159265358979323846264338327950288419716939937510
#endif

#ifndef _MAX_MINS_
  #define _MAX_MINS_
  constexpr real REAL_MAX = FLT_MAX;  //Maximo valor positivo
  constexpr real REAL_MIN = FLT_MIN;  // Minimo valor POSITIVO
#endif

constexpr real pi = (real)M_PI;
constexpr real two_pi = (real)2.0 * M_PI;

#ifndef radian
  constexpr real pi_over_180 = M_PI  / 180.0;
  constexpr real one_over_pi_over_180 = 180.0 / M_PI;

  /*
   * 180º = PI radians / 360º = 2 * PI radians
   */
  #define radian(angulo) (angulo * pi_over_180)
  #define grado(angulo) (angulo * one_over_pi_over_180)
#endif

constexpr real MATH_EQUALS_MARGIN = (real)0.00000000000000000000000009;
#define equalsZeroAbsoluteMargin(r) (-(real)MATH_EQUALS_MARGIN <= r && r <= (real)MATH_EQUALS_MARGIN)
#define equalsAbsoluteMargin(left, right) equalsZero(left - right)
