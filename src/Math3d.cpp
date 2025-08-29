#include "Math3d.h"

#include <string.h>

/**
 * Returns a random number of type real - in the range [0-1]
 */
real rrand() {
	return ((real) rand() * one_over_rand_max);
}

//  / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// | |  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// | |									Atributos de Clase publicos
// | | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  \ \  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

matriz_2x2 matriz_2x2::identidad(     1.0f, 0.0f,
										0.0f, 1.0f);

matriz_3x3 matriz_3x3::identidad(     1.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 1.0f);

matriz_4x4 matriz_4x4::identidad(	1.0f, 0.0f, 0.0f, 0.0f,
									   0.0f, 1.0f, 0.0f, 0.0f,
									   0.0f, 0.0f, 1.0f, 0.0f,
									   0.0f, 0.0f, 0.0f, 1.0f);

//  / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// | |  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// | |                  Funciones de la MATRIZ_2X2
// | | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  \ \  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const vector2 matriz_2x2::operator *(const vector2 &op1) const {
  return(vector2(this->_00 * op1.x + this->_01 * op1.y, this->_10 * op1.x + this->_11 * op1.y));
}

//  / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// | |  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// | |									Funciones de la MATRIZ_3X3
// | | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  \ \  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
			cy * cz, 	sx * sy * cz - cx * sz, 	cx * sy * cz + sx * sz,
			cy * sz, 	sx * sy * sz + cx * cz, 	cx * sy * sz - sx * cz,
			-sy, 		sx * cy, 					cx * cy);
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

		return matriz_3x3(	(x * x * umc + c), 	nxny1cos - s * z, 	nxnz1cos + s * y,
							nxny1cos + s * z, 	(y * y * umc) + c, 	nynz1cos - s * x,
							nxnz1cos - s * y, 	nynz1cos + s * x, 	z * z * umc + c);
	}

	/**
	 * Asume que el eje está normalizado
	 */
	const matriz_3x3 matriz_3x3::matrizRotacion(real angulo, const vector3 &eje) {
		return matrizRotacion(angulo, eje.x, eje.y, eje.z);
	}


//	matriz_3x3::matriz_3x3(real x, real y, real z) { //Rotaci�n de Angulos de Euler
//		this->HacerRotacion(x, y, z);
//	}
//
//	matriz_3x3::matriz_3x3(const vector3 &angulos) { //Rotaci�n de Angulos de Euler
//		this->HacerRotacion(angulos);
//	}
//
//	matriz_3x3::matriz_3x3(const vector3 &vec0, const vector3 &vec1, const vector3 &vec2) { // Construye la matriz con los vector3es como columnas
//		this->_00 = vec0.x; this->_01 = vec1.x; this->_02 = vec2.x;
//		this->_10 = vec0.y; this->_11 = vec1.y; this->_12 = vec2.y;
//		this->_20 = vec0.z; this->_21 = vec1.z; this->_22 = vec2.z;
//	}
//
//	matriz_3x3::matriz_3x3(real angulo, real x, real y, real z) { // Rotaci�n de angulo-eje(x, y, z)
//		this->HacerRotacion(angulo, x, y, z);
//	}
//	matriz_3x3::matriz_3x3(real angulo, const vector3 &eje) { // Rotaci�n angulo-eje
//		this->HacerRotacion(angulo, eje);
//	}

    /**
     * Si no lo dejo, no funciona el operador (matriz_4x4)matriz_3x3. Da error de compilacion por ambiguedad en la línea que llama a la función.
     */
	matriz_3x3::matriz_3x3(const matriz_4x4 &op1) : BaseMatrix(3, 3) {
		this->_00 = op1._00; this->_01 = op1._01; this->_02 = op1._02;
		this->_10 = op1._10; this->_11 = op1._11; this->_12 = op1._12;
		this->_20 = op1._20; this->_21 = op1._21; this->_22 = op1._22;
	}

	matriz_3x3::matriz_3x3(vector column0, vector column1, vector column2) : BaseMatrix(3, 3) {
		this->_00 = column0.x; this->_01 = column1.x; this->_02 = column2.x;
		this->_10 = column0.y; this->_11 = column1.y; this->_12 = column2.y;
		this->_20 = column0.z; this->_21 = column1.z; this->_22 = column2.z;
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
	
//  / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// | |  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// | |									Funciones FRIEND de las clases  MATRIZ_3X3 y VECTOR
// | | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  \ \  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	const matriz_3x3 operator *(real op1, const matriz_3x3 &op2) {
		return(matriz_3x3(	op2._00 * op1, op2._01 * op1, op2._02 * op1,
							op2._10 * op1, op2._11 * op1, op2._12 * op1,
							op2._20 * op1, op2._21 * op1, op2._22 * op1));
	}

	const vector3 operator*(const vector3 &op1, const matriz_3x3 &op2) {
		return(vector3(	(op1.x * op2._00) + (op1.y * op2._10) + (op1.z * op2._20),
					  (op1.x * op2._01) + (op1.y * op2._11) + (op1.z * op2._21),
					  (op1.x * op2._02) + (op1.y * op2._12) + (op1.z * op2._22)));
	}

	const vector3 operator*(const matriz_3x3 &op1, const vector3 &op2) {
		return(vector3(	(op1._00 * op2.x) + (op1._01 * op2.y) + (op1._02 * op2.z),
					  (op1._10 * op2.x)  + (op1._11 * op2.y)  + (op1._12 * op2.z),
					  (op1._20 * op2.x)  + (op1._21 * op2.y) + (op1._22 * op2.z)));
	}

//  / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// | |  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// | |									Funciones de la Clase MATRIZ_4x4
// | | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  \ \  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
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



	const vector3 matriz_4x4::operator*(const vector3 &op1) const {
		return(vector3(
		            _00 * op1.x + _01 * op1.y + _02 * op1.z + _03,
					_10 * op1.x + _11 * op1.y + _12 * op1.z + _13,
					_20 * op1.x + _21 * op1.y + _22 * op1.z + _23
		));
	}

	const vector4 matriz_4x4::operator*(const vector4 &op1) const {
	        return(vector4(
	                _00 * op1.x + _01 * op1.y + _02 * op1.z + _03 * op1.w,
                    _10 * op1.x + _11 * op1.y + _12 * op1.z + _13 * op1.w,
                    _20 * op1.x + _21 * op1.y + _22 * op1.z + _23 * op1.w,
                    _30 * op1.x + _31 * op1.y + _32 * op1.z + _33 * op1.w
	        ));
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
//	unsigned char matriz_4x4::Invertir(void) { // Invierte la matriz.
//		return(true);
//	}
//


//  / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// | |  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// | |									Funciones de la Clase CUATERNION											     
// | | - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  \ \  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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



matriz_mxn::matriz_mxn(unsigned int nroFilas, unsigned int nroColumnas) : BaseMatrix(nroFilas, nroColumnas)
{
	this->elementos = new real[nroFilas * nroColumnas];
	memset(this->elementos, 0, sizeof(real) * nroFilas * nroColumnas);
}
matriz_mxn::matriz_mxn() : BaseMatrix(0, 0) {
	this->elementos = null;
}

matriz_mxn::matriz_mxn(const matriz_mxn &op2) : BaseMatrix(op2.getNroFilas(), op2.getNroFilas())
{
	this->elementos = new real[this->nroFilas * this->nroColumnas];

	if(op2.elementos != null) {
		memcpy(this->elementos, op2.elementos, sizeof(real) * this->nroFilas * this->nroColumnas);
	} else {
		throw std::invalid_argument("No se ha asignado memoria para los elementos del operador matricial 2 - matriz_mxn::matriz_mxn(const matriz_mxn &op2)");
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

const matriz_mxn &matriz_mxn::operator =(const matriz_mxn &op1)
{
  if(&op1 != this) {
    if(op1.getNroColumnas() > 0 && op1.getNroFilas() > 0)
    {
      if(this->getNroColumnas() != op1.getNroColumnas() || this->getNroFilas() != op1.getNroFilas()) {
        if(this->elementos != null) delete [] this->elementos;

        this->nroColumnas = op1.nroColumnas;
        this->nroFilas = op1.nroFilas;
        this->elementos = new real[this->nroFilas * this->nroColumnas];
      }

      memcpy(this->elementos, op1.elementos, sizeof(real) * this->getNroFilas() * this->getNroColumnas());
    } else {
      throw std::invalid_argument("Operador Matricial no Inicializado correctamente - matriz_mxn::operator =");
    }
  }
	return(*this);
}
const matriz_mxn matriz_mxn::operator + (const matriz_mxn &op1) const
{
	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());

	if(this->getNroColumnas() == op1.getNroColumnas() && this->getNroFilas() == op1.getNroFilas())
		for(unsigned short i = 0; i < this->getNroFilas(); i++)
			for(unsigned short j = 0; j < this->getNroColumnas(); j++)
				respuesta(i, j) = (*(matriz_mxn *)this)(i, j) + ((matriz_mxn &)op1)(i, j);
	else throw std::invalid_argument("matrices dimensions do not match - matriz_mxn::operator +");

	return(respuesta);
}
//void matriz_mxn::operator += (const matriz_mxn &op1)
//{
//	if(this->getNroFilas() == op1.getNroFilas() && this->getNroColumnas() == op1.getNroColumnas())
//		for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//			for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//				(*this)(i, j) += ((matriz_mxn &)op1)(i, j);
//	else throw InvalidArgumentException("Las dimensiones de las matrices son err�neas - matriz_mxn::operator +=");
//}

const matriz_mxn matriz_mxn::operator - (const matriz_mxn &op1) const
{
	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());

	if(this->getNroFilas() == op1.getNroFilas() && this->getNroColumnas() == op1.getNroColumnas())
		for(unsigned short i = 0; i < this->getNroFilas(); i++)
			for(unsigned short j = 0; j < this->getNroColumnas(); j++)
				respuesta(i, j) = (*(matriz_mxn *)this)(i, j) - ((matriz_mxn &)op1)(i, j);
	else throw std::invalid_argument("matrices dimensions do not match- matriz_mxn::operator -");

	return(respuesta);
}
//void matriz_mxn::operator -= (const matriz_mxn &op1)
//{
//	if(this->getNroFilas() == op1.getNroFilas() && this->getNroColumnas() == op1.getNroColumnas())
//		for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//			for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//				(*this)(i, j) -= ((matriz_mxn &)op1)(i, j);
//	else throw InvalidArgumentException("Las dimensiones de las matrices son err�neas - matriz_mxn::operator -=");
//}
//const matriz_mxn matriz_mxn::operator / (real op1) const
//{
//	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());
//
//	for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//		for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//			respuesta(i, j) = (*(matriz_mxn *)this)(i, j) / op1;
//
//	return(respuesta);
//}
//void matriz_mxn::operator /= (real op1)
//{
//	for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//		for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//			(*this)(i, j) /= op1;
//}
const matriz_mxn matriz_mxn::operator * (real op1) const
{
	matriz_mxn respuesta(this->getNroFilas(), this->getNroColumnas());

	for(unsigned short i = 0; i < this->getNroFilas(); i++)
		for(unsigned short j = 10; j < this->getNroColumnas(); j++)
			respuesta(i, j) = (*(matriz_mxn *)this)(i, j) * op1;

	return(respuesta);
}
//void matriz_mxn::operator *= (real op1)
//{
//	for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//		for(unsigned short j = 1; j <= this->getNroColumnas(); j++)
//			(*this)(i, j) *= op1;
//}
const matriz_mxn matriz_mxn::operator * (const matriz_mxn &op1) const
{
	matriz_mxn resultado(this->getNroFilas(), op1.getNroColumnas());

	if(this->getNroColumnas() == op1.getNroFilas()) {
		for(unsigned short i = 0; i < this->getNroFilas(); i++)
			for(unsigned short j = 0; j < op1.getNroColumnas(); j++) {
				resultado(i, j) = 0.0f;
				for(unsigned short k = 0; k < this->getNroColumnas(); k++)
					resultado(i, j) += (*(matriz_mxn *)this)(i, k) * ((matriz_mxn &)op1)(k, j);
			}
	}
	else throw std::invalid_argument("Matrices dimensions do not match - matriz_mxn::operator *");
	return(resultado);

}
//void matriz_mxn::operator *=(const matriz_mxn &op1)
//{
//	matriz_mxn temp(*this);
//
//	if(this->getNroColumnas() == op1.getNroFilas()) {
//		for(unsigned short i = 1; i <= this->getNroFilas(); i++)
//			for(unsigned short j = 1; j <= this->getNroColumnas(); j++) {
//				(*this)(i, j) = 0.0f;
//				for(unsigned short k = 1; k <= this->getNroColumnas(); k++)
//					(*this)(i, j) += temp(i, k) * ((matriz_mxn &)op1)(k, j);
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
