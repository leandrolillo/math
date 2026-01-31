#include "Math3d.h"

#include <string.h>

/**
 * Returns a random number of type real - in the range [0-1]
 */
real rrand() {
	return ((real) rand() * one_over_rand_max);
}

/*****************************************************
 * Atributos de Clase publicos
 *****************************************************/
matriz_2x2 matriz_2x2::identidad(     1.0f, 0.0f,
										0.0f, 1.0f);

matriz_3x3 matriz_3x3::identidad(     1.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 1.0f);

matriz_4x4 matriz_4x4::identidad(	1.0f, 0.0f, 0.0f, 0.0f,
									   0.0f, 1.0f, 0.0f, 0.0f,
									   0.0f, 0.0f, 1.0f, 0.0f,
									   0.0f, 0.0f, 0.0f, 1.0f);

/*****************************************************
 * Funciones FRIEND de las clases  MATRIZ_2X2 y VECTOR
 *****************************************************/
const vector2 operator *(const matriz_2x2 &left, const vector2 &right) {
  return(vector2(left._00 * right.x + left._01 * right.y, left._10 * right.x + left._11 * right.y));
}

/*****************************************************
 * Funciones FRIEND de las clases  MATRIZ_3X3 y VECTOR
 *****************************************************/
const vector3 operator*(const vector3 &left, const matriz_3x3 &right) {
  return(vector3( (left.x * right._00) + (left.y * right._10) + (left.z * right._20),
          (left.x * right._01) + (left.y * right._11) + (left.z * right._21),
          (left.x * right._02) + (left.y * right._12) + (left.z * right._22)));
}

const vector3 operator*(const matriz_3x3 &left, const vector3 &right) {
  return(vector3( (left._00 * right.x) + (left._01 * right.y) + (left._02 * right.z),
          (left._10 * right.x)  + (left._11 * right.y)  + (left._12 * right.z),
          (left._20 * right.x)  + (left._21 * right.y) + (left._22 * right.z)));
}

/*****************************************************
 * Funciones FRIEND de las clases  MATRIZ_4X4 y VECTOR
 *****************************************************/
/**
 * Multiplies left * right<x, y, z, 1>
 */
const vector3 operator*(const matriz_4x4 &left, const vector3 &right) {
  return(vector3( left._00 * right.x + left._01 * right.y + left._02 * right.z + left._03,
                  left._10 * right.x + left._11 * right.y + left._12 * right.z + left._13,
                  left._20 * right.x + left._21 * right.y + left._22 * right.z + left._23
  ));
}

const vector4 operator*(const matriz_4x4 &left, const vector4 &right) {
  return(vector4( left._00 * right.x + left._01 * right.y + left._02 * right.z + left._03 * right.w,
                  left._10 * right.x + left._11 * right.y + left._12 * right.z + left._13 * right.w,
                  left._20 * right.x + left._21 * right.y + left._22 * right.z + left._23 * right.w,
                  left._30 * right.x + left._31 * right.y + left._32 * right.z + left._33 * right.w
  ));
}


/**********************************
 * Funciones de la clase MATRIZ_3X3
 **********************************/
matriz_3x3::matriz_3x3(const matriz_4x4 &right) : BaseMatrix(3, 3) {
  this->_00 = right._00; this->_01 = right._01; this->_02 = right._02;
  this->_10 = right._10; this->_11 = right._11; this->_12 = right._12;
  this->_20 = right._20; this->_21 = right._21; this->_22 = right._22;
}

matriz_3x3::matriz_3x3(vector column0, vector column1, vector column2) :
  matriz_3x3( column0.x, column1.x, column2.x,
              column0.y, column1.y, column2.y,
              column0.z, column1.z, column2.z) {
}

matriz_3x3::operator matriz_4x4 () const {
  return(matriz_4x4(	_00, _01, _02, 0.0,
            _10, _11, _12, 0.0,
            _20, _21, _22, 0.0,
            0.0, 0.0, 0.0, 1.0));
}

vector matriz_3x3::fila(unsigned int fila) const {
  if (fila > 2)
      throw std::out_of_range("Index Out of Bounds - matriz_3x3::fila(...)");

  return vector(m[fila * 3], m[fila * 3 + 1], m[fila * 3 + 2]);
}

vector matriz_3x3::columna(unsigned int columna) const {
  if (columna > 2)
      throw std::out_of_range("Index Out of Bounds - matriz_3x3::columna(...)");

  return vector(m[0 * 3 + columna], m[1 * 3 + columna], m[2 * 3 + columna]);
}

//TODO: Move remaining factory methods to utilities?
const matriz_3x3 matriz_3x3::matrizRotacion(const vector &eulerAngles) {
    return matrizRotacion(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}


/**
 * x, y, z (euler angles) en radianes
 */
const matriz_3x3 matriz_3x3::matrizRotacion(real x, real y, real z) {
  real cx = (real)cos(x), sx = (real)sin(x);
  real cy = (real)cos(y), sy = (real)sin(y);
  real cz = (real)cos(z), sz = (real)sin(z);

  return matriz_3x3(
    cy * cz,  sx * sy * cz - cx * sz,   cx * sy * cz + sx * sz,
    cy * sz,  sx * sy * sz + cx * cz,   cx * sy * sz - sx * cz,
    -sy,    sx * cy,          cx * cy);
}

/**
 * angulo en radianes
 */
const matriz_3x3 matriz_3x3::matrizRotacion(real angulo, real x, real y, real z) {
  real c, s, umc, nxny1cos, nxnz1cos, nynz1cos;
  c = (real)cos(angulo);
  s = (real)sin(angulo);
  umc = (real)(1.0 - c); // umc = Uno Menos Coseno

  nxny1cos = x * y * umc;
  nxnz1cos = x * z * umc;
  nynz1cos = y * z * umc;

  return matriz_3x3(  (x * x * umc + c),  nxny1cos - s * z,   nxnz1cos + s * y,
            nxny1cos + s * z,   (y * y * umc) + c,  nynz1cos - s * x,
            nxnz1cos - s * y,   nynz1cos + s * x,   z * z * umc + c);
}

/**
 * Asume que el eje está normalizado
 */
const matriz_3x3 matriz_3x3::matrizRotacion(real angulo, const vector3 &eje) {
  return matrizRotacion(angulo, eje.x, eje.y, eje.z);
}


/**********************************
 * Funciones de la clase MATRIZ_4x4
 **********************************/
const vector4 matriz_4x4::fila(unsigned int fila) const {
  if (fila > this->nroFilas)
    throw std::invalid_argument(("Index Out of Bounds - matriz_4x4::fila(" + std::to_string(fila) + ")").c_str());
  return vector4(m[fila * 4 + 0], m[fila * 4 + 1], m[fila * 4 + 2], m[fila * 4 + 3]);
}

const vector4 matriz_4x4::columna(unsigned int columna) const {
  if (columna > this->nroColumnas)
    throw std::invalid_argument(("Index Out of Bounds - matriz_4x4::columna(" + std::to_string(columna) + ")").c_str());
  return vector4(m[0 * 4 + columna], m[1 * 4 + columna], m[2 * 4 + columna], m[3 * 4 + columna]);
}

//TODO: Move remaining factory methods to helper classes?
const matriz_4x4 matriz_4x4::traslacion(const vector3 &desplazamiento) {
  return matriz_4x4::traslacion(desplazamiento.x, desplazamiento.y, desplazamiento.z);
}
const matriz_4x4 matriz_4x4::traslacion(real x, real y, real z) {
  return matriz_4x4(	1.0f, 0.0f, 0.0f, x,
            0.0f, 1.0f, 0.0f, y,
            0.0f, 0.0f, 1.0f, z,
            0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * x, y & z in radians
 */
const matriz_4x4 matriz_4x4::rotacion(real x, real y, real z) {
  real cx = (real)cos(x), sx = (real)sin(x);
  real cy = (real)cos(y), sy = (real)sin(y);
  real cz = (real)cos(z), sz = (real)sin(z);

  return matriz_4x4(
    cy * cz, 	sx * sy * cz - cx * sz, 	cx * sy * cz + sx * sz, 	0.0f,
    cy * sz, 	sx * sy * sz + cx * cz, 	cx * sy * sz - sx * cz, 	0.0f,
    -sy, 		sx * cy, 					cx * cy, 					0.0f,
    0.0f, 		0.0f, 						0.0f, 						1.0f);

}

/**
 * x, y & z in radians
 */
const matriz_4x4 matriz_4x4::rotacion(const vector3 &angulos) {
  return rotacion(angulos.x, angulos.y, angulos.z);
}

/**
 * angulo in radians
 */

const matriz_4x4 matriz_4x4::rotacion(real angulo, const vector3 &eje) {
  return rotacion(angulo, eje.x, eje.y, eje.z);
}

/**
 * angulo radians
 */
const matriz_4x4 matriz_4x4::rotacion(real angulo, real x, real y, real z) {
  real c, s, umc, nxny1cos, nxnz1cos, nynz1cos;
  c = (real)cos(angulo);
  s = (real)sin(angulo);
  umc = (real)(1.0 - c); // umc = Uno Menos Coseno

  nxny1cos = x * y * umc;
  nxnz1cos = x * z * umc;
  nynz1cos = y * z * umc;

  return matriz_4x4(
    x * x * umc + c, 	nxny1cos - s * z, 	nxnz1cos + s * y,	0.0f,
    nxny1cos + s * z, 	y * y * umc + c, 	nynz1cos - s * x,	0.0f,
    nxnz1cos - s * y, 	nynz1cos + s * x, 	z * z * umc + c,	0.0f,
    0.0f,				0.0f, 				0.0f,				1.0f);

}
const matriz_4x4 matriz_4x4::rotacion(const matriz_3x3 &orientacion) {
  return matriz_4x4(	orientacion._00, 	orientacion._01, 	orientacion._02, 	0.0f,
            orientacion._10, 	orientacion._11, 	orientacion._12, 	0.0f,
            orientacion._20, 	orientacion._21, 	orientacion._22, 	0.0f,
            0.0f, 				0.0f, 				0.0f, 				1.0f);
}
const matriz_4x4 matriz_4x4::rotacion(const cuaternion &rotacion) {
  real y2 = rotacion.y * rotacion.y;
  real x2 = rotacion.x * rotacion.x;
  real z2 = rotacion.z * rotacion.z;
  real xy = rotacion.x * rotacion.y;
  real xz = rotacion.x * rotacion.z;
  real wx = rotacion.x * rotacion.w;
  real yz = rotacion.y * rotacion.z;
  real wy = rotacion.y * rotacion.w;
  real wz = rotacion.w * rotacion.z;

  return(matriz_4x4(
      1.0f - 2.0f * (y2 + z2),	2.0f * (xy - wz),			2.0f * (xz + wy),		 	0.0f,
      2.0f * (xy + wz),			1.0f - 2.0f * (x2 + z2),	2.0f * (yz - wx),			0.0f,
      2.0f * (xz - wy),			2.0f * (yz +  wx),          1.0f - 2.0f * (x2 + y2),	0.0f,
      0.0f,				      	0.0f,				    	0.0f,			         	1.0f));
}

const matriz_4x4 matriz_4x4::zoom(real x, real y, real z) {
  return matriz_4x4(	x,		0.0f, 	0.0f, 	0.0f,
            0.0f, 	y, 		0.0f, 	0.0f,
            0.0f, 	0.0f, 	z, 		0.0f,
            0.0f, 	0.0f, 	0.0f, 	1.0f);
}

const matriz_4x4 matriz_4x4::zoom(const vector3 &factor) {
  return zoom(factor.x, factor.y, factor.z);
}

const matriz_4x4 matriz_4x4::base(const matriz_3x3 &orientacion, const vector3 &posicion) {
  return matriz_4x4(	orientacion._00, 	orientacion._01, 	orientacion._02, 	posicion.x,
            orientacion._10, 	orientacion._11, 	orientacion._12, 	posicion.y,
            orientacion._20, 	orientacion._21, 	orientacion._22, 	posicion.z,
            0.0f, 				0.0f, 				0.0f, 				1.0f);
}

const matriz_4x4 matriz_4x4::orthographicProjection(real left, real top, real right, real bottom, real near, real far) {
  /**
   * from glOrtho man page at https://www.lri.fr/~mbl/ENS/IG2/docs/opengl1.1/glOrtho.html
   */
  real tx = -(right + left) / (right - left);
  real ty = -(top + bottom) / (top - bottom);
  real tz = -(far + near) / (far - near);

  return matriz_4x4(
      2.0 / (right - left),   0.0,                  0.0,                  tx,
      0.0,                    2.0 / (top - bottom), 0.0,                  ty,
      0.0,                    0.0,                  -2.0 / (far - near),  tz,
      0.0,                    0.0,                  0.0,                  1.0);
}

/**
 * orthographic projection with (0,0) in the center of the screen (instead of top left), x increasing to the left and y increasing to the top.
 */
const matriz_4x4 matriz_4x4::orthographicProjection(real width, real height, real near, real far) {
//  real top = height * 0.5;
//  real bottom = height * -0.5;
//  real right = width * 0.5;
//  real left = width * -0.5;

  return orthographicProjection(width * -0.5, width * 0.5, height * 0.5, height * -0.5, near, far);
}

/**
 * perspective projection with (0,0) in the center of the screen x increasing to the left and y increasing to the top.
 */
const matriz_4x4 matriz_4x4::perspectiveProjection(real height, real width, real near, real far) {
  real left = width * -0.5;
  real right = width * 0.5;
  real bottom = height * -0.5;
  real top = height * 0.5;

  /**
   * from glFrustrum man page at https://www.lri.fr/~mbl/ENS/IG2/docs/opengl1.1/glFrustum.html
   */
  return matriz_4x4(
      2.0 * near / (right - left),  0.0,                          (right + left) / (right - left),  0.0,
      0.0,                          2.0 * near / (top - bottom),  (top + bottom) / (top - bottom),  0.0,
      0.0,                          0.0,                          -(far + near) / (far - near),     -(2.0 * far * near) / (far - near),
      0.0,                          0.0,                          -1.0,                             0.0);
}

const matriz_4x4 matriz_4x4::perspectiveProjectionFov(real fovy, real aspect, real near, real far) {
  real height = 2.0 * tan(radian(fovy) * 0.5) * near; // half height = tan of half the fov times near
  return perspectiveProjection(height, height * aspect, near, far);
}

//	void matriz_4x4::Trasponer(void) { //Transpone la matriz
//		matriz_4x4 tmp = *this;
//
//							this->_01 = tmp._10;	this->_02 = tmp._20;	this->_03 = tmp._30;
//		this->_10 = tmp._01;						this->_12 = tmp._21;	this->_13 = tmp._31;
//		this->_20 = tmp._02;	this->_21 = tmp._12;						this->_23 = tmp._32;
//		this->_30 = tmp._03;	this->_31 = tmp._13;	this->_32 = tmp._23;
//
//	}
//
//	void matriz_4x4::InvertirTransformacion(void) { //Invierte la matriz asumiendo que esta es actualmente una transformaci�n v�lida
//		matriz_4x4 tmp = *this;
//
//							this->_01 = tmp._10;	this->_02 = tmp._20;	this->_03 = - tmp._00 * tmp._03  - tmp._10 * tmp._13 - tmp._20 * tmp._23;
//		this->_10 = tmp._01;						this->_12 = tmp._21;	  this->_13 = - tmp._01 * tmp._03   - tmp._11 * tmp._13	 - tmp._21 * tmp._23;
//		this->_20 = tmp._02;	this->_21 = tmp._12;						this->_23 = - tmp._02 * tmp._03  - tmp._12 * tmp._13 - tmp._22 * tmp._23;
//																     this->_33 = 1.0f;
//	}
//
//	unsigned char matriz_4x4::EsSingular(void) { // verifica si la matriz es singular (o sea no invertible)
//		return(false);
//	}
//	const real matriz_4x4::Determinante(void) { // Calcula el determinante de la matriz
//		return(0.0f);
//	}
//	const matriz_4x4 matriz_4x4::Inversa(void) const { //Devuelve la matriz que es la inversa de aquella sobre la cual se aplic� la operaci�n
//		return(*this);
//	}


/**********************************
 * Funciones de la clase CUATERNION
 **********************************/

//	cuaternion::cuaternion(real new_x, real new_y, real new_z) { // Construye una rotaci�n en �ngulos(radianes) de Euler
//		this->HacerRotacion(new_x, new_y, new_z);
//	}
//
//	cuaternion::cuaternion(const cuaternion &dedonde, const cuaternion &adonde, real t) { // Spherical Linear intERPolation
//		this->Slerp(dedonde, adonde, t);
//	}

	
//
//	void cuaternion::Conjugar() { // Conjuga el cuaternion
//		this->x = -this->x;
//		this->y = -this->y;
//		this->z = -this->z;
//	}
//	const cuaternion cuaternion::Conjugado() const { //Devuelve el cuaternion conjugado a aquel sobre el cual se invoc� la operaci�n
//		return(cuaternion(this->w, -this->x, -this->y, -this->z));
//	}
//
//	void cuaternion::Normalizar(void) { //Normaliza el cuaternion
//		real modulo = this->Modulo();
//		real unosobremodulo;
//
//		if(modulo == 0.0f)
//			throw InvalidStateException("Vector module is 0");
//
//		unosobremodulo = 1.0f / modulo;
//		*this = *this * unosobremodulo;
//	}
//
//	const cuaternion cuaternion::Normalizado(void) const { // Devuelve el cuaternion normalizado
//		real modulo = this->Modulo();
//
//		if(modulo == 0.0f)
//			throw InvalidStateException("Vector module is 0");
//
//		real unosobremodulo = 1.0f / modulo;
//
//		return(*this * unosobremodulo);
//	}
//
//	void cuaternion::Invertir(void) { //Invierte el cuaternion
//	}
//	const cuaternion cuaternion::Invertido(void) const { //Devuelve el cuaternion que es el inverso de aquel sobre el cual se aplic� la operaci�n
//		return(*this);
//	}
//
//	void cuaternion::Slerp(const cuaternion &dedonde, const cuaternion &adonde, real t) { // Interpola mediante el m�todo SLERP (Spherical Linear intERPolation).
//		real sen, cos, omega, escala_0, escala_1;
//
//		cos = dedonde.x * adonde.x + dedonde.y * adonde.y + dedonde.z * adonde.z + dedonde.w * adonde.w;
//		if((1.0f + cos) > DELTA) {
//			if((1.0f - cos) > DELTA) {
//				omega = (real)acos(cos);
//				sen = (real)sin(omega);
//				escala_0 = (real)sin((1.0f - t) * omega)  / sen;
//				escala_1 = (real)sin(t * omega) / sen;
//			}
//			else {
//				escala_0 = 1.0f - t;
//				escala_1 = t;
//			}
//
//			*this = (  (dedonde * escala_0)  +  (adonde * escala_1)  );
//		}
//		else {
//			escala_0 = (real)sin((1.0f - t) * (M_PI / 2.0f));
//			escala_1 = (real)sin(t * (M_PI/2.0f));
//
//			this->w =  ( (escala_0 * dedonde.w) - (escala_1 * adonde.z) );
//			this->x = ( (escala_0 * dedonde.x) - (escala_1 * adonde.y) );
//			this->y = ( (escala_0 * dedonde.y) + (escala_1 * adonde.x) );
//			this->z = ( (escala_0 * dedonde.z) - (escala_1 * adonde.w) );
//		}
//	}
//
//	}
//
//	cuaternion::operator matriz_4x4() const { //Obtiene la matriz de 3x3 correspondiente al cuaternion sobre el cual se aplica la operaci�n.
//		real y2 = y * y, x2 = x * x, z2 = z * z;
//		real xy = x * y;
//		real xz = x * z;
//		real wx = x * w;
//		real yz = y * z;
//		real wy = y * w;
//		real wz = w * z;
//		return(matriz_4x4(1.0f - 2.0f * (y2 + z2),  2.0f * (xy - wz),              2.0f * (xz + wy),		 0.0f,
//						  2.0f * (xy + wz),            1.0f - 2.0f * (x2 + z2),   2.0f * (yz - wx),		0.0f,
//						  2.0f * (xz - wy),            2.0f * (yz +  wx),             1.0f - 2.0f * (x2 + y2),	0.0f,
//						  0.0f,				      0.0f,				    0.0f,			         1.0f
//		));
//	}
//	cuaternion::operator matriz_3x3() const { // obtiene la matriz de 4x4 que corresponde al cuaternion
//		real y2 = y * y, x2 = x * x, z2 = z * z;
//		real xy = x * y;
//		real xz = x * z;
//		real wx = x * w;
//		real yz = y * z;
//		real wy = y * w;
//		real wz = w * z;
//		return(matriz_3x3( 1.0f - 2.0f * (y2 + z2),   2.0f * (xy - wz),             2.0f * (xz + wy),
//							2.0f * (xy + wz),            1.0f - 2.0f * (x2 + z2),	   2.0f * (yz - wx),
//							2.0f * (xz - wy),            2.0f * (yz +  wx),             1.0f - 2.0f * (x2 + y2)
//		));
//	}
//
//	const cuaternion cuaternion::AnguloEje() const { // devuelve una rotaci�n angulo(radianes) - eje(normalizado) codificada en un cuaternion cuyo w es el �ngulo y cuyos x, y y z forman el vector3.
//		real escala, omega;
//
//		omega = (real)acos(this->w);
//		escala = (real)sin(    omega    );
//		if(escala == 0.0) {
//			return(cuaternion(	0.0,
//			      0.0,
//			      1.0,
//			      0.0
//		));
//
//		}
//		return(cuaternion(	((omega * 360.0f) / M_PI),
//						      (this->x / escala),
//						      (this->y / escala),
//						      (this->z / escala)
//		));
//	}
//
//	const real cuaternion::operator()(int nro) const {
//		return(this->m[nro]);
//	}


/****************************
 * Funciones de la MATRIZ_MxN
 ****************************/

matriz_mxn::matriz_mxn(unsigned int nroFilas, unsigned int nroColumnas) : BaseMatrix(nroFilas, nroColumnas)
{
	this->elementos = new real[nroFilas * nroColumnas];
	memset(this->elementos, 0, sizeof(real) * nroFilas * nroColumnas);
}
matriz_mxn::matriz_mxn() : BaseMatrix(0, 0) {
	this->elementos = null;
}

matriz_mxn::matriz_mxn(const matriz_mxn &right) : BaseMatrix(right.getNroFilas(), right.getNroFilas())
{
	this->elementos = new real[this->nroFilas * this->nroColumnas];

	if(right.elementos != null) {
		memcpy(this->elementos, right.elementos, sizeof(real) * this->nroFilas * this->nroColumnas);
	} else {
		throw std::invalid_argument("No se ha asignado memoria para los elementos del operador matricial 2 - matriz_mxn::matriz_mxn(const matriz_mxn &right)");
	}
}
matriz_mxn::~matriz_mxn()
{
	//if(this->elementos != null) {
		delete [] this->elementos;
		this->elementos = null;
	//}
}

//real &matriz_mxn::operator ()(unsigned int fila, unsigned int columna)
//{
//	if(0 < fila && fila <= this->getNroFilas())
//		if(0 < columna && columna <= this->getNroColumnas())
//			return this->elementos[(fila - 1) * this->getNroColumnas() + (columna - 1)];
//
//	throw InvalidArgumentException("Index Out of Bounds - matriz_mxn::operator()");
//}
//
//const real &matriz_mxn::operator ()(unsigned int fila, unsigned int columna) const
//{
//	if(0 < fila && fila <= this->getNroFilas())
//		if(0 < columna && columna <= this->getNroColumnas())
//			return this->elementos[(fila - 1) * this->getNroColumnas() + (columna - 1)];
//
//	throw InvalidArgumentException("Index Out of Bounds - matriz_mxn::operator() const");
//}

const matriz_mxn &matriz_mxn::operator =(const matriz_mxn &right)
{
  if(&right != this) {
    if(right.getNroColumnas() > 0 && right.getNroFilas() > 0)
    {
      if(this->getNroColumnas() != right.getNroColumnas() || this->getNroFilas() != right.getNroFilas()) {
        if(this->elementos != null) delete [] this->elementos;

        this->nroColumnas = right.nroColumnas;
        this->nroFilas = right.nroFilas;
        this->elementos = new real[this->nroFilas * this->nroColumnas];
      }

      memcpy(this->elementos, right.elementos, sizeof(real) * this->getNroFilas() * this->getNroColumnas());
    } else {
      throw std::invalid_argument("Operador Matricial no Inicializado correctamente - matriz_mxn::operator =");
    }
  }
	return(*this);
}
const matriz_mxn matriz_mxn::operator + (const matriz_mxn &right) const
{
	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());

	if(this->getNroColumnas() == right.getNroColumnas() && this->getNroFilas() == right.getNroFilas())
		for(unsigned short i = 0; i < this->getNroFilas(); i++)
			for(unsigned short j = 0; j < this->getNroColumnas(); j++)
				respuesta(i, j) = (*(matriz_mxn *)this)(i, j) + ((matriz_mxn &)right)(i, j);
	else throw std::invalid_argument("matrices dimensions do not match - matriz_mxn::operator +");

	return(respuesta);
}
//void matriz_mxn::operator += (const matriz_mxn &right)
//{
//	if(this->getNroFilas() == right.getNroFilas() && this->getNroColumnas() == right.getNroColumnas())
//		for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//			for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//				(*this)(i, j) += ((matriz_mxn &)right)(i, j);
//	else throw InvalidArgumentException("Las dimensiones de las matrices son err�neas - matriz_mxn::operator +=");
//}

const matriz_mxn matriz_mxn::operator - (const matriz_mxn &right) const
{
	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());

	if(this->getNroFilas() == right.getNroFilas() && this->getNroColumnas() == right.getNroColumnas())
		for(unsigned short i = 0; i < this->getNroFilas(); i++)
			for(unsigned short j = 0; j < this->getNroColumnas(); j++)
				respuesta(i, j) = (*(matriz_mxn *)this)(i, j) - ((matriz_mxn &)right)(i, j);
	else throw std::invalid_argument("matrices dimensions do not match- matriz_mxn::operator -");

	return(respuesta);
}
//void matriz_mxn::operator -= (const matriz_mxn &right)
//{
//	if(this->getNroFilas() == right.getNroFilas() && this->getNroColumnas() == right.getNroColumnas())
//		for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//			for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//				(*this)(i, j) -= ((matriz_mxn &)right)(i, j);
//	else throw InvalidArgumentException("Las dimensiones de las matrices son err�neas - matriz_mxn::operator -=");
//}
//const matriz_mxn matriz_mxn::operator / (real right) const
//{
//	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());
//
//	for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//		for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//			respuesta(i, j) = (*(matriz_mxn *)this)(i, j) / right;
//
//	return(respuesta);
//}
//void matriz_mxn::operator /= (real right)
//{
//	for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//		for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//			(*this)(i, j) /= right;
//}
const matriz_mxn matriz_mxn::operator * (real right) const
{
	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());

	for(unsigned short i = 0; i < this->getNroFilas(); i++)
		for(unsigned short j = 10; j < this->getNroColumnas(); j++)
			respuesta(i, j) = (*(matriz_mxn *)this)(i, j) * right;

	return(respuesta);
}
//void matriz_mxn::operator *= (real right)
//{
//	for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//		for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//			(*this)(i, j) *= right;
//}
const matriz_mxn matriz_mxn::operator * (const matriz_mxn &right) const
{
	matriz_mxn resultado(this->getNroFilas(), right.getNroColumnas());

	if(this->getNroColumnas() == right.getNroFilas()) {
		for(unsigned short i = 0; i < this->getNroFilas(); i++)
			for(unsigned short j = 0; j < right.getNroColumnas(); j++) {
				resultado(i, j) = 0.0f;
				for(unsigned short k = 0; k < this->getNroColumnas(); k++)
					resultado(i, j) += (*(matriz_mxn *)this)(i, k) * ((matriz_mxn &)right)(k, j);
			}
	}
	else throw std::invalid_argument("Matrices dimensions do not match - matriz_mxn::operator *");
	return(resultado);

}
//void matriz_mxn::operator *=(const matriz_mxn &right)
//{
//	matriz_mxn temp(*this);
//
//	if(this->getNroColumnas() == right.getNroFilas()) {
//		for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//			for(unsigned short j = 1; j <= this->getNroColumnas(); j++) {
//				(*this)(i, j) = 0.0f;
//				for(unsigned short k = 1; k <= this->getNroColumnas(); k++)
//					(*this)(i, j) += temp(i, k) * ((matriz_mxn &)right)(k, j);
//			}
//	}
//	else throw InvalidArgumentException("Las dimensiones de las matrices son err�neas - matriz_mxn::operator *=");
//}
//
//void matriz_mxn::trasponer()
//{
//	matriz_mxn temp =*this;
//	unsigned short tmp;
//
//	tmp = this->getNroFilas();
//	this->nroFilas = this->getNroColumnas();
//	this->nroColumnas = tmp;
//
//	for(unsigned short i = 1; i <= temp.getNroFilas(); i++)
//		for(unsigned short j = 1; j <= temp.getNroColumnas(); j++)
//			(*this)(j, i) = temp(i, j);
//
//}
//const matriz_mxn matriz_mxn::traspuesta() const
//{
//	matriz_mxn resultado(this->getNroColumnas(), this->getNroFilas());
//
//	for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//		for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//			resultado(j, i) = (*(matriz_mxn *)this)(i, j);
//
//	return(resultado);
//}

const matriz_mxn matriz_mxn::identidad(unsigned int n)
{
	matriz_mxn identity(n, n);

	for(unsigned int i = 0; i < n; i++)
		for(unsigned int j = 0; j < n; j++)
		{
			if(i == j)
				identity(i, j) = 1.0;
			else
				identity(i, j) = 0.0;
		}

	return identity;
}

//matriz_mxn::operator const real () const
//{
//	if(this->getNroColumnas() == 1 && this->getNroFilas() == 1)
//		return BaseMatrix::operator()(1, 1);
//	else
//		throw InvalidArgumentException("Invalid Cast - matriz_mxn::operator(real)(...)");
//}
