#pragma once

#include "MathConstants.h"
//#include "baseMath.h"

class matriz_2x2;
class matriz_4x4;
class matriz_3x3;
class cuaternion;
class vector3;
class vector2;

typedef matriz_4x4 matriz;
typedef matriz_4x4 matrix;
typedef matriz_4x4 matrix_4x4;
typedef vector3 vector;
typedef vector2 texel;
typedef cuaternion vector4; //I coded cuaternions first

//#define defaultNumberFormat "%.3e"
constexpr char const *defaultNumberFormat = "%.2f";

real rrand();

class BaseMatrix {
protected:
  unsigned int nroFilas, nroColumnas;

public:
  BaseMatrix(unsigned int nroFilas, unsigned int nroColumnas) {
    this->nroFilas = nroFilas;
    this->nroColumnas = nroColumnas;
  }
  unsigned int getNroFilas() const {
    return this->nroFilas;
  }

  unsigned int getNroColumnas() const {
    return this->nroColumnas;
  }

  unsigned int getLength() const {
    return getNroFilas() * getNroColumnas();
  }

  virtual real& operator()(unsigned int fila, unsigned int columna) = 0;

  virtual real operator()(unsigned int fila, unsigned int columna) const = 0;

  virtual String toString(String format = defaultNumberFormat) const {
    String result;

    char temp[500];

    for (unsigned int currentRow = 0; currentRow < this->getNroFilas();
        currentRow++) {
      if (currentRow == 0) {
        result += "/";
      } else if (currentRow == this->getNroFilas() - 1) {
        result += "\\";
      } else {
        result += "|";
      }

      for (unsigned int currentColumn = 0;
          currentColumn < this->getNroColumnas(); currentColumn++) {
        snprintf(temp, sizeof(temp), format.c_str(),
            this->operator()(currentRow, currentColumn));
        //sprintf(temp, "%u %u", currentRow, currentColumn);
        result += temp;

        if (currentColumn != this->getNroColumnas() - 1) {
          result += "	";
        }
      }

      //result += " ";

      if (currentRow == 0) {
        result += "\\";
      } else if (currentRow == this->getNroColumnas() - 1) {
        result += "/	";
      } else {
        result += "|";
      }

      result += "\n";
    }

    return result;

  }

  virtual ~BaseMatrix() {
  }
  ;
};

class matriz_2x2: public BaseMatrix {
  friend const vector2 operator *(const matriz_2x2 &left, const vector2 &right);
  friend const matriz_2x2 operator *(const real &left, const matriz_2x2 &right){
    return(matriz_2x2(left * right._00, left * right._01,
                      left * right._10, left * right._11));
  }
protected:
  union {
    struct {
      real _00, _01;
      real _10, _11;
    };
    real m[4];
  };

  //Factory Methods
public:
  static const matriz_2x2 matrizRotacion(real angulo);
  static const matriz_2x2 matrizZoom(real x, real y);

public:
  static matriz_2x2 identidad;

  matriz_2x2() : matriz_2x2(1.0f, 0.0f,
                            0.0f, 1.0f) {
  }
  matriz_2x2(real _00, real _01, real _10, real _11) : BaseMatrix(2, 2) {
    this->_00 = _00; this->_01 = _01;
    this->_10 = _10; this->_11 = _11;
  }
  matriz_2x2(const matriz_2x2 &right) : BaseMatrix(2, 2) {
    *this = right;
  }

  real& operator()(unsigned int fila, unsigned int columna) override {
    if (fila > 1 || columna > 1)
      throw std::out_of_range(
          "Index Out of Bounds - matriz_2x2::operator(i, j)");

    return m[fila * 2 + columna];
  }

  real operator()(unsigned int fila, unsigned int columna) const override {
    if (fila > 1 || columna > 1)
      throw std::out_of_range(
          "Index Out of Bounds - matriz_2x2::operator(i, j)");

    return m[fila * 2 + columna];
  }
  const matriz_2x2 operator +(const matriz_2x2 &right) const {
    return(matriz_2x2(this->_00 + right._00, this->_01 + right._01,
                      this->_10 + right._10, this->_11 + right._11));
  }
  const matriz_2x2 operator -(const matriz_2x2 &right) const {
    return(matriz_2x2(this->_00 - right._00, this->_01 - right._01,
                      this->_10 - right._10, this->_11 - right._11));
  }
  const matriz_2x2 operator *(const matriz_2x2 &right) const {
    return(matriz_2x2(this->_00 * right._00 + this->_01 * right._10, this->_00 * right._01 + this->_01 * right._11,
                      this->_10 * right._00 + this->_11 * right._10, this->_10 * right._01 + this->_11 * right._11));
  }
  const matriz_2x2 operator *(const real &right) const {
    return(matriz_2x2(this->_00 * right, this->_01 * right,
                      this->_10 * right, this->_11 * right));
  }

  void operator +=(const matriz_2x2 &right) {
    this->_00 += right._00; this->_01 += right._01;
    this->_10 += right._10; this->_11 += right._11;
  }
  void operator -=(const matriz_2x2 &right) {
    this->_00 -= right._00; this->_01 -= right._01;
    this->_10 -= right._10; this->_11 -= right._11;
  }
  void operator *=(const matriz_2x2 &right) {
    *this = *this * right;
  }
  void operator *=(const real &right) {
    this->_00 *= right; this->_01 *= right;
    this->_10 *= right; this->_11 *= right;
  }

	const matriz_2x2 transpuesta() const {
    return(matriz_2x2(this->_00, this->_10,
                      this->_01, this->_11));
  }
//		unsigned char esSingular() const;
//		real determinante() const;
//		const matriz_2x2 inversa() const;
};

class matriz_3x3: public BaseMatrix {
  friend class matriz_4x4;
  friend const vector3 operator*(const vector3 &left, const matriz_3x3 &right); //TODO: Do we need this?
  friend const vector3 operator*(const matriz_3x3 &left, const vector3 &right);
  friend const matriz_3x3 operator *(real left, const matriz_3x3 &right) {
    return(matriz_3x3(  right._00 * left, right._01 * left, right._02 * left,
                        right._10 * left, right._11 * left, right._12 * left,
                        right._20 * left, right._21 * left, right._22 * left));
  }
protected:
  union {
    struct {
      real _00, _01, _02;
      real _10, _11, _12;
      real _20, _21, _22;
    };
    real m[9];
  };

public:
  // Factory methods
  static const matriz_3x3 matrizRotacion(real x, real y, real z);
  static const matriz_3x3 matrizRotacion(const vector3 &angulos);

  /**
   * Asume que el eje está normalizado
   */
  static const matriz_3x3 matrizRotacion(real angulo, real x, real y, real z);

  /**
   * Asume que el eje está normalizado
   */
  static const matriz_3x3 matrizRotacion(real angulo, const vector3 &eje);
  static const matriz_3x3 matrizRotacion(const cuaternion &rotacion);

  static const matriz_3x3 matrizZoom(real x, real y, real z);
  static const matriz_3x3 matrizZoom(const vector3 &zoom);
public:
  static matriz_3x3 identidad;

  real& operator()(unsigned int fila, unsigned int columna) override {
    if (fila > 2 || columna > 2)
      throw std::out_of_range(
          "Index Out of Bounds - matriz_3x3::operator(i, j)");

    return m[fila * 3 + columna];
  }

  real operator()(unsigned int fila, unsigned int columna) const override {
    if (fila > 2 || columna > 2)
      throw std::out_of_range("Index Out of Bounds - matriz_3x3::operator(i, j)");

    return m[fila * 3 + columna];
  }

  vector fila(unsigned int fila) const;
  vector columna(unsigned int columna) const;

  matriz_3x3(real d00, real d01, real d02, real d10, real d11, real d12,
      real d20, real d21, real d22) :
      BaseMatrix(3, 3) {
    this->_00 = d00; this->_01 = d01; this->_02 = d02;
    this->_10 = d10; this->_11 = d11; this->_12 = d12;
    this->_20 = d20; this->_21 = d21; this->_22 = d22;
  }

  matriz_3x3(const matriz_3x3 &right) :
      BaseMatrix(3, 3) { // Constructor de Copia
    memcpy(this->m, right.m, sizeof(this->m));
  }
  matriz_3x3(void) : matriz_3x3(1.0, 0.0, 0.0,
                                0.0, 1.0, 0.0,
                                0.0, 0.0, 1.0) {
  }

  matriz_3x3(vector column0, vector column1, vector column2);

  /**
   * Can't implement here functions that use types not yet defined
   */
  matriz_3x3(const matriz_4x4 &right);

  matriz_3x3 operator=(const matriz_3x3 &right) {
    if (&right != this) {
      memcpy(this->m, right.m, sizeof(this->m));
    }

    return (*this);
  }

  unsigned char operator==(const matriz_3x3 &right) const {
    return ((_00 == right._00 && _01 == right._01 && _02 == right._02
          && _10 == right._10 && _11 == right._11 && _12 == right._12
          && _20 == right._20 && _21 == right._21 && _22 == right._22));
  }

  unsigned char operator!=(const matriz_3x3 &right) const {
    return ((_00 != right._00 || _01 != right._01 || _02 != right._02
        || _10 != right._10 || _11 != right._11 || _12 != right._12 || _20 != right._20
        || _21 != right._21 || _22 != right._22));
  }

  const matriz_3x3 operator*(const matriz_3x3 &right) const {
    return (matriz_3x3(
        (this->_00 * right._00) + (this->_01 * right._10) + (this->_02 * right._20),
        (this->_00 * right._01) + (this->_01 * right._11) + (this->_02 * right._21),
        (this->_00 * right._02) + (this->_01 * right._12) + (this->_02 * right._22),

        (this->_10 * right._00) + (this->_11 * right._10) + (this->_12 * right._20),
        (this->_10 * right._01) + (this->_11 * right._11) + (this->_12 * right._21),
        (this->_10 * right._02) + (this->_11 * right._12) + (this->_12 * right._22),

        (this->_20 * right._00) + (this->_21 * right._10) + (this->_22 * right._20),
        (this->_20 * right._01) + (this->_21 * right._11) + (this->_22 * right._21),
        (this->_20 * right._02) + (this->_21 * right._12) + (this->_22 * right._22)));
  }

  const matriz_3x3 operator*(real right) const {
    return (matriz_3x3(_00 * right, _01 * right, _02 * right, _10 * right, _11 * right,
        _12 * right, _20 * right, _21 * right, _22 * right));
  }

  const matriz_3x3 operator+(const matriz_3x3 &right) const {
    return (matriz_3x3(_00 + right._00, _01 + right._01, _02 + right._02,
        _10 + right._10, _11 + right._11, _12 + right._12, _20 + right._20,
        _21 + right._21, _22 + right._22));
  }

  const matriz_3x3 operator-(const matriz_3x3 &right) const {
    return (matriz_3x3(_00 - right._00, _01 - right._01, _02 - right._02,
        _10 - right._10, _11 - right._11, _12 - right._12, _20 - right._20,
        _21 - right._21, _22 - right._22));
  }

  void operator*=(const matriz_3x3 &right) {
    *this = *this * right;
  }

  void operator*=(real right) {
    *this = *this * right;
  }

  void operator+=(const matriz_3x3 &right) {
    *this = *this + right;
  }

  void operator-=(const matriz_3x3 &right) {
    *this = *this - right;
  }

  operator real *() const {
    return ((real*) m);
  }

  operator matriz_4x4() const;

  const matriz_3x3 traspuesta(void) const {
    return (matriz_3x3( this->_00, this->_10, this->_20,
                        this->_01, this->_11, this->_21,
                        this->_02, this->_12, this->_22));
  }

  real determinante(void) const { //Calcula el determinante de la matriz.
    return (this->_00 * this->_11 * this->_22
        + this->_02 * this->_10 * this->_21 + this->_01 * this->_12 * this->_20
        - this->_02 * this->_11 * this->_20 - this->_12 * this->_21 * this->_00
        - this->_01 * this->_10 * this->_22);
  }

  const matriz_3x3 inversa(void) const {
    return inversa(this->determinante());
  }

  /**
   * Assumes determinant parameter is correctly calculated. Otherwise the result is undetermined.
   */
  const matriz_3x3 inversa(real det) const {
    if (det == 0.0f) {
      throw std::invalid_argument(
          "Could not calculate inverse of singular matrix (det=0). This is the matrix equivalent of a division by zero");
    } else {
      det = 1.0f / det;

      return matriz_3x3((this->_11 * this->_22 - this->_12 * this->_21) * det,
          (-this->_01 * this->_22 + this->_02 * this->_21) * det,
          ( this->_01 * this->_12 - this->_11 * this->_02) * det,
          (-this->_10 * this->_22 + this->_12 * this->_20) * det,
          ( this->_00 * this->_22 - this->_02 * this->_20) * det,
          (-this->_00 * this->_12 + this->_02 * this->_10) * det,
          ( this->_10 * this->_21 - this->_20 * this->_11) * det,
          (-this->_00 * this->_21 + this->_01 * this->_20) * det,
          ( this->_00 * this->_11 - this->_10 * this->_01) * det);
    }
  }

//		const matriz_3x3 transpuesta(void) const;
//		unsigned char esSingular(void);
//
//		void star(const vector3 &right);
};

class matriz_4x4: public BaseMatrix {
  friend const vector3 operator*(const matriz_4x4 &left, const vector3 &right);
  friend const vector4 operator*(const matriz_4x4 &left, const vector4 &right);
  friend const matriz_4x4 operator *(real left, const matriz_4x4 &right) {
    return (matriz_4x4( left * right._00, left * right._01, left * right._02, left * right._03,
                        left * right._10, left * right._11, left * right._12, left * right._13,
                        left * right._20, left * right._21, left * right._22, left * right._23,
                        left * right._30, left * right._31, left * right._32, left * right._33));
  }

  friend class matriz_3x3;
private:
  union {
    real m[16];
    struct {
      real _00, _01, _02, _03;
      real _10, _11, _12, _13;
      real _20, _21, _22, _23;
      real _30, _31, _32, _33;
    };
  };
public:
  // Factory Methods
  static const matriz_4x4 traslacion(const vector3 &desplazamiento);
  static const matriz_4x4 traslacion(real x, real y, real z);

  static const matriz_4x4 rotacion(real x, real y, real z);
  static const matriz_4x4 rotacion(const vector3 &angulos);
  static const matriz_4x4 rotacion(real angulo, const vector3 &eje);
  static const matriz_4x4 rotacion(real angulo, real x, real y, real z);
  static const matriz_4x4 rotacion(const matriz_3x3 &orientacion);
  static const matriz_4x4 rotacion(const cuaternion &rotacion);

  static const matriz_4x4 zoom(real x, real y, real z);
  static const matriz_4x4 zoom(const vector3 &zoom);

  static const matriz_4x4 base(const matriz_3x3 &orientacion,
      const vector3 &posicion);

public:
  static matriz_4x4 identidad;

  matriz_4x4(void) :
      BaseMatrix(4, 4) {
    this->_00 = 1.0; this->_01 = 0.0; this->_02 = 0.0; this->_03 = 0.0;
    this->_10 = 0.0; this->_11 = 1.0; this->_12 = 0.0; this->_13 = 0.0;
    this->_20 = 0.0; this->_21 = 0.0; this->_22 = 1.0; this->_23 = 0.0;
    this->_30 = 0.0; this->_31 = 0.0; this->_32 = 0.0; this->_33 = 1.0;
  }

  matriz_4x4(real _00, real _01, real _02, real _03, real _10, real _11,
      real _12, real _13, real _20, real _21, real _22, real _23, real _30,
      real _31, real _32, real _33) :
      BaseMatrix(4, 4) {
    this->_00 = _00; this->_01 = _01; this->_02 = _02; this->_03 = _03;
    this->_10 = _10; this->_11 = _11; this->_12 = _12; this->_13 = _13;
    this->_20 = _20; this->_21 = _21; this->_22 = _22; this->_23 = _23;
    this->_30 = _30; this->_31 = _31; this->_32 = _32; this->_33 = _33;
  }

  matriz_4x4(const matriz_4x4 &right) :
      BaseMatrix(4, 4) { //Constructor de copia
    memcpy(this->m, right.m, sizeof(this->m));
  }

  real& operator()(unsigned int fila, unsigned int columna) override {
    if (fila > 3 || columna > 3)
      throw std::out_of_range(
          "Index Out of Bounds - matriz_4x4::operator(i, j)");
    return m[fila * 4 + columna];
  }
  real operator()(unsigned int fila, unsigned int columna) const override {
    if (fila > 3 || columna > 3)
      throw std::out_of_range(
          "Index Out of Bounds - matriz_4x4::operator(i, j)");

    return m[fila * 4 + columna];
  }

  const vector4 fila(unsigned int fila) const;
  const vector4 columna(unsigned int columna) const;

  matriz_4x4 operator=(const matriz_4x4 &right) {
    if (&right != this) {
      memcpy(this->m, right.m, sizeof(this->m));
    }

    return (*this);
  }

  const matriz_4x4 operator*(const matriz_4x4 &right) const {
    return (matriz_4x4(
        (this->_00 * right._00) + (this->_01 * right._10) + (this->_02 * right._20) + (this->_03 * right._30),
        (this->_00 * right._01) + (this->_01 * right._11) + (this->_02 * right._21) + (this->_03 * right._31),
        (this->_00 * right._02) + (this->_01 * right._12) + (this->_02 * right._22) + (this->_03 * right._32),
        (this->_00 * right._03) + (this->_01 * right._13) + (this->_02 * right._23) + (this->_03 * right._33),

        (this->_10 * right._00) + (this->_11 * right._10) + (this->_12 * right._20) + (this->_13 * right._30),
        (this->_10 * right._01) + (this->_11 * right._11) + (this->_12 * right._21) + (this->_13 * right._31),
        (this->_10 * right._02) + (this->_11 * right._12) + (this->_12 * right._22) + (this->_13 * right._32),
        (this->_10 * right._03) + (this->_11 * right._13) + (this->_12 * right._23) + (this->_13 * right._33),

        (this->_20 * right._00) + (this->_21 * right._10) + (this->_22 * right._20) + (this->_23 * right._30),
        (this->_20 * right._01) + (this->_21 * right._11) + (this->_22 * right._21) + (this->_23 * right._31),
        (this->_20 * right._02) + (this->_21 * right._12) + (this->_22 * right._22) + (this->_23 * right._32),
        (this->_20 * right._03) + (this->_21 * right._13) + (this->_22 * right._23) + (this->_23 * right._33),

        (this->_30 * right._00) + (this->_31 * right._10) + (this->_32 * right._20) + (this->_33 * right._30),
        (this->_30 * right._01) + (this->_31 * right._11) + (this->_32 * right._21) + (this->_33 * right._31),
        (this->_30 * right._02) + (this->_31 * right._12) + (this->_32 * right._22) + (this->_33 * right._32),
        (this->_30 * right._03) + (this->_31 * right._13) + (this->_32 * right._23) + (this->_33 * right._33)));
  }

  const matriz_4x4 operator *(real right) const {
    return (matriz_4x4(_00 * right, _01 * right, _02 * right, _03 * right, _10 * right,
        _11 * right, _12 * right, _13 * right, _20 * right, _21 * right, _22 * right,
        _23 * right, _30 * right, _31 * right, _32 * right, _33 * right));
  }

  const matriz_4x4 operator +(const matriz_4x4 &right) const {
    return (matriz_4x4( _00 + right._00, _01 + right._01, _02 + right._02, _03 + right._03,
                        _10 + right._10, _11 + right._11, _12 + right._12, _13 + right._13,
                        _20 + right._20, _21 + right._21, _22 + right._22, _23 + right._23,
                        _30 + right._30, _31 + right._31, _32 + right._32, _33 + right._33));
  }
  const matriz_4x4 operator -(const matriz_4x4 &right) const {
    return (matriz_4x4( _00 - right._00, _01 - right._01, _02 - right._02, _03 - right._03,
                        _10 - right._10, _11 - right._11, _12 - right._12, _13 - right._13,
                        _20 - right._20, _21 - right._21, _22 - right._22, _23 - right._23,
                        _30 - right._30, _31 - right._31, _32 - right._32, _33 - right._33));
  }
  void operator*=(const matriz_4x4 &right) {
    *this = *this * right;
  }
  void operator *=(real right) {
    *this = *this * right;
  }
  void operator +=(const matriz_4x4 &right) {
    *this = *this + right;
  }
  void operator -=(const matriz_4x4 &right) {
    *this = *this - right;
  }
  matriz_4x4 operator =(const matriz_3x3 &right) {
    this->_00 = right._00;
    this->_01 = right._01;
    this->_02 = right._02;
    this->_10 = right._10;
    this->_11 = right._11;
    this->_12 = right._12;
    this->_20 = right._20;
    this->_21 = right._21;
    this->_22 = right._22;

    return (*this);
  }

//		unsigned char operator==(const matriz_4x4 &right) const {
//		  return
//		      this->_00 == right._00 && this->_01 == right._01 && this->_02 == right._02 && this->_03 == right._03 &&
//		      this->_10 == right._10 && this->_11 == right._11 && this->_12 == right._02 && this->_13 == right._13 &&
//		      this->_20 == right._20 && this->_21 == right._21 && this->_22 == right._02 && this->_23 == right._23 &&
//		      this->_30 == right._30 && this->_31 == right._31 && this->_32 == right._02 && this->_33 == right._33;
//		}

  operator real *() const {
    return ((real*) m);
  }

  operator matriz_3x3() const {	//Funciona solamente si dejo un constructor matriz_3x3(matriz_4x4 right) en la clase matriz_3x3
    return (matriz_3x3(_00, _01, _02, _10, _11, _12, _20, _21, _22));
  }

  const matriz_4x4 traspuesta(void) const {
    return (matriz_4x4(this->_00, this->_10, this->_20, this->_30, this->_01,
        this->_11, this->_21, this->_31, this->_02, this->_12, this->_22,
        this->_32, this->_03, this->_13, this->_23, this->_33));
  }

  real determinante(void) const { //Calcula el determinante de la matriz.
    return (  _00 * (_11 * _22 * _33 + _12 * _23 * _31 + _13 * _21 * _32 - _13 * _22 * _31 - _12 * _21 * _33 - _11 * _23 * _32)
            - _10 * (_01 * _22 * _33 + _02 * _23 * _31 + _03 * _21 * _32 - _03 * _22 * _31 - _03 * _21 * _33 - _01 * _23 * _32)
            + _20 * (_01 * _12 * _33 + _02 * _13 * _31 + _03 * _11 * _32 - _03 * _12 * _31 - _02 * _11 * _33 - _01 * _13 * _32)
            - _30 * (_01 * _12 * _23 + _02 * _13 * _21 + _03 * _11 * _22 - _03 * _12 * _21 - _02 * _11 * _23 - _01 * _13 * _22));
  }

  const matriz_4x4 inversa(void) const {
    real invDet = this->determinante();
    if (invDet == 0.0f) {
      throw std::invalid_argument(
          "Could not calculate inverse of singular matrix (det=0). This is the matrix equivalent of a division by zero");
    } else {
      invDet = (real) 1 / invDet;

      return matriz_4x4(
          ( _11 * _22 * _33 + _12 * _23 * _31 + _13 * _21 * _32 - _13 * _22 * _31 - _12 * _21 * _33 - _11 * _23 * _32) * invDet,
          (-_01 * _22 * _33 - _02 * _23 * _31 - _03 * _21 * _32 + _03 * _22 * _31 + _02 * _21 * _33 + _01 * _23 * _32) * invDet,
          ( _01 * _12 * _33 + _02 * _13 * _31 + _03 * _11 * _32 - _03 * _12 * _31 - _02 * _11 * _33 - _01 * _13 * _32) * invDet,
          (-_01 * _12 * _23 - _02 * _13 * _21 - _03 * _11 * _22 + _03 * _12 * _21 + _02 * _11 * _23 + _01 * _13 * _22) * invDet,

          (-_10 * _22 * _33 - _12 * _23 * _30 - _13 * _20 * _32 + _13 * _22 * _30 + _12 * _20 * _33 + _10 * _23 * _32) * invDet,
          ( _00 * _22 * _33 + _02 * _23 * _30 + _03 * _20 * _32 - _03 * _22 * _30 - _02 * _20 * _33 - _00 * _23 * _32) * invDet,
          (-_00 * _12 * _33 - _02 * _13 * _30 - _03 * _10 * _32 + _03 * _12 * _30 + _02 * _10 * _33 + _00 * _13 * _32) * invDet,
          ( _00 * _12 * _23 + _02 * _13 * _20 + _03 * _10 * _22 - _03 * _12 * _20 - _02 * _10 * _23 - _00 * _13 * _22) * invDet,

          ( _10 * _21 * _33 + _11 * _23 * _30 + _13 * _20 * _31 - _13 * _21 * _30 - _11 * _20 * _33 - _10 * _23 * _31) * invDet,
          (-_00 * _21 * _33 - _01 * _23 * _30 - _03 * _20 * _31 + _03 * _21 * _30 + _01 * _20 * _33 + _00 * _23 * _31) * invDet,
          ( _00 * _11 * _33 + _01 * _12 * _30 + _03 * _10 * _31 - _03 * _11 * _30 - _01 * _10 * _33 - _00 * _12 * _31) * invDet,
          (-_00 * _11 * _23 - _01 * _13 * _20 - _03 * _10 * _21 + _03 * _11 * _20 + _01 * _10 * _23 + _00 * _13 * _21) * invDet,

          (-_10 * _21 * _32 - _11 * _22 * _30 - _12 * _20 * _31 + _12 * _21 * _30 + _11 * _20 * _32 + _10 * _22 * _31) * invDet,
          ( _00 * _21 * _32 + _01 * _22 * _30 + _02 * _20 * _31 - _02 * _21 * _30 - _01 * _20 * _32 - _00 * _22 * _31) * invDet,
          (-_00 * _11 * _32 - _01 * _12 * _30 - _02 * _10 * _31 + _02 * _11 * _30 + _01 * _10 * _32 + _00 * _12 * _31) * invDet,
          ( _00 * _11 * _22 + _01 * _12 * _20 + _02 * _10 * _21 - _02 * _11 * _20 - _01 * _10 * _22 - _00 * _12 * _21) * invDet);
    }
  }

  //
  //			unsigned char esSingular(void);
  //			real determinante(void);
  //			unsigned char invertir(void);
  //			const matriz_4x4 inversa(void) const;
  //
  //
  //			void invertirTransformacion(void);
};

class matriz_mxn: public BaseMatrix {
private:
  real *elementos;

public:

  // TODO: Warning: this matrix was initially implemented with indexes 1..height instead of 0..height-1
  real& operator()(unsigned int fila, unsigned int columna) override {
    if (0 <= fila && fila < this->getNroFilas())
      if (0 <= columna && columna < this->getNroColumnas())
        return this->elementos[fila * this->getNroColumnas() + columna];

    throw std::out_of_range(
        "Index Out of Bounds - matriz_mxn["
            + std::to_string(this->getNroFilas()) + "]" + "["
            + std::to_string(this->getNroColumnas()) + "]::" + "operator("
            + std::to_string(fila) + "," + std::to_string(columna) + ")");

  }

  real operator()(unsigned int fila, unsigned int columna) const override {
    if (0 <= fila && fila < this->getNroFilas())
      if (0 <= columna && columna < this->getNroColumnas())
        return this->elementos[fila * this->getNroColumnas() + columna];

    throw std::out_of_range(
        "Index Out of Bounds - matriz_mxn["
            + std::to_string(this->getNroFilas()) + "]" + "["
            + std::to_string(this->getNroColumnas()) + "]::" + "operator("
            + std::to_string(fila) + "," + std::to_string(columna) + ")");
  }

//		unsigned char operator==(const matriz_mxn &right) const {
//		  if(this->getNroColumnas() != right.getNroColumnas() || this->getNroFilas() != right.getNroFilas()) {
//		    return false;
//		  }
//      for(unsigned short i = 0; i < this->getNroFilas(); i++) {
//        for(unsigned short j = 0; j < this->getNroColumnas(); j++) {
//          if(this->operator ()(i, j) != right(i, j)) {
//            return false;
//          }
//        }
//      }
//      return true;
//		}

  matriz_mxn();
  matriz_mxn(unsigned int nroFilas, unsigned int nroColumnas);
  matriz_mxn(const matriz_mxn &right); //Constructor de copia (se necesitan cuando se maneja memoria dinamicamente reservada)
  virtual ~matriz_mxn();

  //operator const real() const;
  const matriz_mxn& operator =(const matriz_mxn &right);
  const matriz_mxn operator +(const matriz_mxn &right) const;
  const matriz_mxn operator -(const matriz_mxn &right) const;
  const matriz_mxn operator *(real right) const;
  const matriz_mxn operator *(const matriz_mxn &right) const;

//			void trasponer();
//			const matriz_mxn traspuesta() const;

  static const matriz_mxn identidad(unsigned int n);

};

class vector2 {
public:
  union {
    struct {
      real x, y;
    };
    struct {
      real u, v;
    };

    real m[2];
  };

public:
  friend const vector2 operator*(real left, const vector2 &right) {
    return (vector2(left * right.x, left * right.y));
  }

public:
  vector2() {
    *this = vector2(0.0f, 0.0f);
  }
  vector2(real x, real y) {
    this->x = x;
    this->y = y;
  }
  //vector2(const vector2 &right);

  const vector2 operator +(const vector2 &right) const {
    return(vector2(this->x + right.x, this->y + right.y));
  }
  const vector2 operator -(const vector2 &right) const {
    return(vector2(this->x - right.x, this->y - right.y));
  }
  const vector2 operator-(void) const {
    return(vector2(-this->x, -this->y));
  }
  const vector2 operator *(const real &right) const {
    return(vector2(this->x * right, this->y * right));
  }

  real operator *(const vector2 &right) const {
    return(this->productoEscalar(right));
  }
  real operator ^(const vector2 &right) const;

  void operator +=(const vector2 &right) {
    this->x += right.x;
    this->y += right.y;
  }
  void operator -=(const vector2 &right) {
    this->x -= right.x;
    this->y -= right.y;
  }
  void operator *=(const real &right) {
    this->x *= right;
    this->y *= right;
  }

  real modulo() const {
    return(sqrt(this->x * this->x + this->y * this->y));
  }

  vector2 normalizado() const {
    real modulo = this->modulo();

    if (modulo == 0.0f)
      throw std::invalid_argument(
          "Vector module is 0. Division by 0 when normalizing");

    real oneOverModule = (real) 1 / modulo;
    return vector2(this->x * oneOverModule, this->y * oneOverModule);
  }

  unsigned int getLength() const {
    return 2;
  }

  real& operator()(unsigned int i) {
    if(i < getLength()) {
      return m[i];
    } else {
      throw std::out_of_range("Index [" + std::to_string(i) + "] out of bounds - length = " + std::to_string(getLength()));
    }
  }

  real operator()(unsigned int i) const {
    if(i < getLength()) {
      return m[i];
    } else {
      throw std::out_of_range("Index [" + std::to_string(i) + "] out of bounds - length = " + std::to_string(getLength()));
    }
  }


//		void normalizar();
//		const vector2 normalizado() const;
//
//		void perpendicularizar();
//		const vector2 perpendicularizado() const;
//
//		real perpDotProduct(const vector2 &right) const;
//		real productoEscalar(const vector2 &right) const;

  operator real *() const {
    return((real *)this->m);
  }

  String toString(String numberFormat = defaultNumberFormat) const {
    char temp[256];

    snprintf(temp, sizeof(temp),
        ("<" + numberFormat + ", " + numberFormat + ">").c_str(), this->x,
        this->y);

    return String(temp);
  }

private:
  real productoEscalar(const vector2 &right) const {
    return (this->x * right.x + this->y * right.y);
  }

};

class vector3 {
  friend const vector3 operator*(real left, const vector3 &right) {
    return (vector3(left * right.x, left * right.y, left * right.z));
  }

  friend const vector3 operator*(const vector3 &left, const matriz_3x3 &right);
  friend const vector3 operator*(const matriz_3x3 &left, const vector3 &right);

public:
  union {
    struct {
      real x, y, z;
    };
    real m[3];
  };

public:
  vector3() {
  }
  vector3(real c_x, real c_y, real c_z) {
    this->x = c_x;
    this->y = c_y;
    this->z = c_z;
  }

  vector3(const vector3 &right) {  //constructor de copia
    memcpy(this->m, right.m, sizeof(this->m));
  }

  unsigned char operator==(const vector3 &right) const {
    return ((x == right.x && y == right.y && z == right.z));
  }

  unsigned char operator!=(const vector3 &right) const {
    return ((x != right.x || y != right.y || z != right.z));
  }

  const vector3 operator+(const vector3 &right) const {
    return (vector3(this->x + right.x, this->y + right.y, this->z + right.z));
  }

  const vector3 operator-(const vector3 &right) const {
    return (vector3(this->x - right.x, this->y - right.y, this->z - right.z));
  }
  const vector3 operator-(void) const {
    return (vector3(-this->x, -this->y, -this->z));
  }

  const vector3 operator*(real right) const {
    return (vector3(this->x * right, this->y * right, this->z * right));
  }

  void operator +=(const vector3 &right) {
    this->x += right.x;
    this->y += right.y;
    this->z += right.z;
  }

  void operator -=(const vector3 &right) {
    this->x -= right.x;
    this->y -= right.y;
    this->z -= right.z;
  }

  void operator*=(real right) {
    this->x *= right;
    this->y *= right;
    this->z *= right;
  }

  real operator*(const vector3 &right) const { // Producto Escalar de vector3es
    return (this->productoEscalar(right));
  }

  const vector3 operator^(const vector3 &right) const { // Producto Vectorial
    return (productoVectorial(right));
  }

  real modulo(void) const { // Devuelve el modulo del vector3
    return ((real) sqrt(
        (this->x * this->x) + (this->y * this->y) + (this->z * this->z)));
  }

  operator real *() const {
    return ((real*) this->m);
  }

  const vector3 normalizado(void) const {
    real modulo = this->modulo();

    if (modulo == 0.0f)
      throw std::invalid_argument(
          "Vector module is 0. Division by 0 when normalizing");

    real oneOverModule = (real) 1 / modulo;
    return (vector3(this->x * oneOverModule, this->y * oneOverModule, this->z * oneOverModule));
  }

  unsigned int getLength() const {
    return 3;
  }

  real& operator()(unsigned int i) {
    if(i < getLength()) {
      return m[i];
    } else {
      throw std::out_of_range("Index [" + std::to_string(i) + "] out of bounds - length = " + std::to_string(getLength()));
    }
  }

  real operator()(unsigned int i) const {
    if(i < getLength()) {
      return m[i];
    } else {
      throw std::out_of_range("Index [" + std::to_string(i) + "] out of bounds - length = " + std::to_string(getLength()));
    }
  }

//
//		const matriz_3x3 star() const;

  String toString(String numberFormat = defaultNumberFormat) const {
    char temp[256];

    snprintf(temp, sizeof(temp),
        ("<" + numberFormat + ", " + numberFormat + ", " + numberFormat + ">").c_str(),
        this->x, this->y, this->z);

    return String(temp);
  }
private:
  real productoEscalar(const vector3 &right) const {
    return ((this->x * right.x) + (this->y * right.y) + (this->z * right.z));
  }

  vector3 productoVectorial(const vector3 &right) const {
    return (vector3((this->z * right.y - this->y * right.z),
        (this->x * right.z - this->z * right.x),
        (this->y * right.x - this->x * right.y)));
  }
};

class cuaternion {
  friend const vector3 operator*(real left, const vector4 &right) {
    return (vector4(left * right.x, left * right.y, left * right.z, left * right.w));
  }

public:
  union {
    struct {
      real x, y, z, w;
    };
    real m[4];
  };

public:
  cuaternion(void) {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 1.0;
  }

  cuaternion(real new_x, real new_y, real new_z, real new_w) {
    this->x = new_x;
    this->y = new_y;
    this->z = new_z;
    this->w = new_w;
  }
  cuaternion(const vector3 &right) { // copia los atributos x, y y z a los del cuaternion, dejando w = 0
    this->x = right.x;
    this->y = right.y;
    this->z = right.z;
    this->w = 0.0;
  }

  cuaternion(const cuaternion &right) {
    memcpy(this->m, right.m, sizeof(this->m));
  }
  const cuaternion operator+(const cuaternion &right) const {
    return (cuaternion(this->x + right.x, this->y + right.y, this->z + right.z,
        this->w + right.w));
  }

  const cuaternion operator-(const cuaternion &right) const {
    return (cuaternion(this->x - right.x, this->y - right.y, this->z - right.z,
        this->w - right.w));
  }
  const cuaternion operator-(void) const {
    return (cuaternion(-this->x, -this->y, -this->z, -this->w));
  }

  const cuaternion operator*(const real right) const {
    return (cuaternion(this->x * right, this->y * right, this->z * right,
        this->w * right));
  }
  void operator *=(const real right) {
    this->x *= right;
    this->y *= right;
    this->z *= right;
    this->w *= right;
  }

  const cuaternion operator*(const cuaternion &right) const {
    return (cuaternion(
        this->w * right.x + this->x * right.w + this->y * right.z - this->z * right.y,
        this->w * right.y + this->y * right.w + this->z * right.x - this->x * right.z,
        this->w * right.z + this->z * right.w + this->x * right.y - this->y * right.x,
        this->w * right.w - this->x * right.x - this->y * right.y - this->z * right.z));
  }

  operator real *() const {
    return ((real*) m);
  }

  real modulo() const { // Devuelve el modulo del cuaternion
    return ((real) sqrt(
        this->w * this->w + this->x * this->x + this->y * this->y
            + this->z * this->z));
  }

  const cuaternion normalizado(void) const { // Devuelve el cuaternion normalizado
    real modulo = this->modulo();

    if (modulo == (real) 0)
      throw std::invalid_argument(
          "Cuaternion module is 0. Division by 0 when normalizing");

    real unosobremodulo = (real) 1 / modulo;

    return (*this * unosobremodulo);
  }

  operator vector3() const {
    return vector3(this->x, this->y, this->z);
  }

  operator matriz_4x4() const { //Obtiene la matriz de 4x4 correspondiente al cuaternion sobre el cual se aplica la operacion.
    real y2 = y * y, x2 = x * x, z2 = z * z;
    real xy = x * y;
    real xz = x * z;
    real wx = x * w;
    real yz = y * z;
    real wy = y * w;
    real wz = w * z;
    return (matriz_4x4(1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz),
        2.0f * (xz + wy), 0.0f, 2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2),
        2.0f * (yz - wx), 0.0f, 2.0f * (xz - wy), 2.0f * (yz + wx),
        1.0f - 2.0f * (x2 + y2), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
  }
  operator matriz_3x3() const { // obtiene la matriz de 3x3 que corresponde al cuaternion
    real y2 = y * y, x2 = x * x, z2 = z * z;
    real xy = x * y;
    real xz = x * z;
    real wx = x * w;
    real yz = y * z;
    real wy = y * w;
    real wz = w * z;
    return (matriz_3x3(1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz),
        2.0f * (xz + wy), 2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2),
        2.0f * (yz - wx), 2.0f * (xz - wy), 2.0f * (yz + wx),
        1.0f - 2.0f * (x2 + y2)));
  }

  unsigned int getLength() const {
    return 4;
  }

  real& operator()(unsigned int i) {
    if (i < getLength()) {
      return m[i];
    } else {
      throw std::out_of_range("Index [" + std::to_string(i) + "] out of bounds - length = " + std::to_string(getLength()));
    }
  }

  real operator()(unsigned int i) const {
    if (i < getLength()) {
      return m[i];
    } else {
      throw std::out_of_range("Index [" + std::to_string(i) + "] out of bounds - length = " + std::to_string(getLength()));
    }
  }

  String toString(const String format = defaultNumberFormat) const {
    char temp[256];

    snprintf(temp, sizeof(temp),
        ("<" + format + ", " + format + ", " + format + ", " + format + ">").c_str(),
        this->x, this->y, this->z, this->w);

    return String(temp);
  }
//
//			void conjugar(void);
//			const cuaternion conjugado(void) const;
//
//			void invertir(void);
//			const cuaternion invertido(void) const;
//
//			void normalizar(void);
//			const cuaternion normalizado(void) const;
//
//			void slerp(const cuaternion &dedonde, const cuaternion &adonde, real t);
//
//			operator matriz_4x4() const;
//			operator matriz_3x3() const;
//			real operator()(int nro) const;

  //Factory methods
  static const cuaternion cuaternionRotacion(real angulo, const vector3 &eje) {
    return cuaternion(eje.x * (real) sin(angulo * 0.5),
        eje.y * (real) sin(angulo * 0.5), eje.z * (real) sin(angulo * 0.5),
        (real) cos(angulo * 0.5));
  }
  static const cuaternion cuaternionRotacion(real x, real y, real z) {
    real ex, ey, ez;
    real cr, cp, cy, sr, sp, sy, cpcy, spsy;		// temp vars in roll,pitch yaw

    ex = x * (real) 0.5;	// convert to rads and half them
    ey = y * (real) 0.5;
    ez = z * (real) 0.5;

    cr = cos(ex);
    sr = sin(ex);
    cp = cos(ey);
    sp = sin(ey);
    cy = cos(ez);
    sy = sin(ez);

    cpcy = cp * cy;
    spsy = sp * sy;

    return cuaternion(real(sr * cpcy - cr * spsy),
        real(cr * sp * cy + sr * cp * sy), real(cr * cp * sy - sr * sp * cy),
        real(cr * cpcy + sr * spsy)).normalizado();
  }
  static const cuaternion cuaternionRotacion(const vector3 &angulos) {
    return cuaternionRotacion(angulos.x, angulos.y, angulos.z);
  }
//		static const cuaternion cuaternionAnguloEje(real angulo, const vector3 &eje) {
//
//		}

  static const cuaternion slerp(const cuaternion &dedonde,
      const cuaternion &adonde, real t) { // Interpola mediante el metodo SLERP (Spherical Linear intERPolation).
    real sen, cos, omega, escala_0, escala_1;

    cos = dedonde.x * adonde.x + dedonde.y * adonde.y + dedonde.z * adonde.z
        + dedonde.w * adonde.w;
    if ((1.0f + cos) > DELTA) {
      if ((1.0f - cos) > DELTA) {
        omega = (real) acos(cos);
        sen = (real) sin(omega);
        escala_0 = (real) sin((1.0f - t) * omega) / sen;
        escala_1 = (real) sin(t * omega) / sen;
      } else {
        escala_0 = 1.0f - t;
        escala_1 = t;
      }

      return ((dedonde * escala_0) + (adonde * escala_1));
    } else {
      escala_0 = (real) sin((1.0f - t) * (M_PI / 2.0f));
      escala_1 = (real) sin(t * (M_PI / 2.0f));

      return cuaternion((escala_0 * dedonde.x) - (escala_1 * adonde.y),
          (escala_0 * dedonde.y) + (escala_1 * adonde.x),
          (escala_0 * dedonde.z) - (escala_1 * adonde.w),
          (escala_0 * dedonde.w) - (escala_1 * adonde.z));
    }
  }
};

class vectorN: public matriz_mxn {
public:
  vectorN(unsigned int longitud, bool vectorFila = true) :
      matriz_mxn(1, longitud) {
//				if(!vectorFila)
//					this->hacerVectorColumna();
  }
  vectorN(const matriz_mxn &right) :
      matriz_mxn(right) {
  }
//			vectorN(const vectorN &right) : matriz_mxn((matriz_mxn &)right), BaseVector(right.getLength())
//			{
//			}

  virtual real& operator()(unsigned int index) {
    if (this->getNroFilas() == 1)
      return ((BaseMatrix*) this)->operator ()(1, index);

    return ((BaseMatrix*) this)->operator ()(index, 1);
  }

  const vectorN& operator =(const vectorN &right) {
    if (((const matriz_mxn&) right).getNroColumnas() == 1
        || ((const matriz_mxn&) right).getNroFilas() == 1) {
      this->matriz_mxn::operator=(right);
      return *this;
    } else
      throw std::invalid_argument(
          "Not a vector - one of the dimensions must be 1 (trying to assign a matrix to a vector");
  }

  real punto(vectorN &right) {
    if (this->getLength() == right.getLength()) {
      real resultado = 0;

      for (unsigned int index = 1; index <= this->getLength(); index++)
        resultado += vectorN::operator ()(index) * right(index);

      return resultado;
    } else
      throw std::invalid_argument("vectors should have the same length");
  }

//			bool esVectorColumna() const
//			{
//				return this->getNroColumnas() < this->getNroFilas();
//			}
//
//			void hacerVectorColumna()
//			{
//				if(!this->esVectorColumna())
//					this->matriz_mxn::trasponer();
//			}
//			void hacerVectorFila()
//			{
//				if(this->esVectorColumna())
//					this->matriz_mxn::trasponer();
//			}
};
