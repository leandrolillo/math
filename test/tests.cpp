#include <catch2/catch_test_macros.hpp>

#include "Math3d.h"

TEST_CASE("Test matrices indexers") {
  REQUIRE(1 == 1);

  //matriz nula
  matriz_mxn matriz;

  SECTION( "matrix_mxn identidad(2)" ) {
    matriz = matriz_mxn::identidad(2);

    //printf("%s", matriz.toString().c_str());

    REQUIRE(matriz(0, 0) == 1.0);
    REQUIRE(matriz(1, 1) == 1.0);
    REQUIRE(matriz(1, 0) == 0.0);
    REQUIRE(matriz(0, 1) == 0.0);
  }


  SECTION( "matrix_mxn identidad(3)" ) {
    matriz = matriz_mxn::identidad(3);
    REQUIRE(matriz(1, 1) == 1.0);
    REQUIRE(matriz(0, 0) == 1.0);
    REQUIRE(matriz(0, 1) == 0.0);
    REQUIRE(matriz(0, 2) == 0.0);
    REQUIRE(matriz(1, 0) == 0.0);
    REQUIRE(matriz(1, 1) == 1.0);
    REQUIRE(matriz(1, 2) == 0.0);
    REQUIRE(matriz(2, 0) == 0.0);
    REQUIRE(matriz(2, 1) == 0.0);
    REQUIRE(matriz(2, 2) == 1.0);
  }

  SECTION( "matrix_2x2" ) {
    matriz_2x2 matriz2(1, 2, 3, 4);
    REQUIRE(matriz2(0, 0) == 1.0);
    REQUIRE(matriz2(0, 1) == 2.0);
    REQUIRE(matriz2(1, 0) == 3.0);
    REQUIRE(matriz2(1, 1) == 4.0);
  }

//  //Ideally a matrix_2x2 should be a matrix_mxn thus casting should be possible. However I will not implement this until having a use case
//  matriz = matriz_2x2(1, 2, 3, 4);
//  REQUIRE(matriz(0, 0) == 1.0);
//  REQUIRE(matriz(0, 1) == 2.0);
//  REQUIRE(matriz(1, 0) == 3.0);
//  REQUIRE(matriz(1, 1) == 4.0);

//  matriz_2x2 = matriz * 2.0;
//  REQUIRE(matriz(0, 0) == 2.0);
//  REQUIRE(matriz(0, 1) == 4.0);
//  REQUIRE(matriz(1, 0) == 6.0);
//  REQUIRE(matriz(1, 1) == 8.0);


}

/**
 * Check if rotation * translation equals manually building with orientation matrix top-left 3x3 and top-right column vector
 */
TEST_CASE("Test basis") {
  vector angles(radian(45), radian(45), radian(45));
  vector position(1, 2, 3);
  matriz_3x3 orientation = matriz_3x3::matrizRotacion(angles);


  matriz expected = matriz::base(orientation, position);
  matriz actual = matriz::rotacion(angles) * matriz::traslacion(position);

  //REQUIRE(expected == actual); //TODO: review operator ==
}
