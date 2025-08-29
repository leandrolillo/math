#include <catch2/catch_test_macros.hpp>

#include "Math3d.h"
#include "mathMatchers.h"

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

TEST_CASE("Matriz 2x2") {
  SECTION("Metadata") {
    matriz_2x2 actual(1.0, 2.0,
                      3.0, 4.0);
    CHECK(actual.getNroFilas() == 2);
    CHECK(actual.getNroColumnas() == 2);
  }

  SECTION("Operator(i, j)") {
    matriz_2x2 actual(1.0, 2.0,
                      3.0, 4.0);

    CHECK(actual(0, 0) == 1.0);
    CHECK(actual(0, 1) == 2.0);
    CHECK(actual(1, 0) == 3.0);
    CHECK(actual(1, 1) == 4.0);
  }

  SECTION("identidad") {
    matriz_2x2 actual {matriz_2x2::identidad};

    CHECK_THAT(actual, EqualsMatrix(matriz_2x2( 1, 0,
                                                0, 1)));
  }

  SECTION("Operator *(real)") {
    matriz_2x2 actual(1.0, 2.0,
                      3.0, 4.0);

    actual = actual * 2;
    CHECK_THAT(actual, EqualsMatrix(matriz_2x2( 2, 4,
                                                6, 8)));
  }

  SECTION("Operator +(matriz_2x2)") {
    matriz_2x2 left(  1.0, 2.0,
                      3.0, 4.0);

    matriz_2x2 right(  1.0, 2.0,
                       3.0, 4.0);

    matriz_2x2 actual = left + right;
    CHECK_THAT(actual, EqualsMatrix(matriz_2x2( 2, 4,
                                                6, 8)));
  }

  SECTION("Operator -(matriz_2x2)") {
    matriz_2x2 left(  1.0, 2.0,
                      3.0, 4.0);

    matriz_2x2 right(  1.0, 2.0,
                       3.0, 4.0);

    matriz_2x2 actual = left - right;
    CHECK_THAT(actual, EqualsMatrix(matriz_2x2( 0, 0,
                                                0, 0)));
  }

  SECTION("Operator *(matriz_2x2)") {
    matriz_2x2 left(  1.0, 2.0,
                      3.0, 4.0);

    matriz_2x2 right(  1.0, 2.0,
                       3.0, 4.0);

    matriz_2x2 actual = left * right;
    CHECK_THAT(actual, EqualsMatrix(matriz_2x2( 7, 10,
                                                15, 22)));
  }

  SECTION("Operator *(vector_2)") {
    matriz_2x2 left(  1.0, 2.0,
                      3.0, 4.0);

    vector2 right(  1.0, 2.0);

    vector2 actual = left * right;
    CHECK_THAT(actual, EqualsVector(vector2( 5, 11)));
  }
}

TEST_CASE("Matriz 3x3") {
  SECTION("Metadata") {
    matriz_3x3 actual(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);
    CHECK(actual.getNroFilas() == 3);
    CHECK(actual.getNroColumnas() == 3);
  }

  SECTION("Operator(i, j)") {
    matriz_3x3 actual(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    CHECK(actual(0, 0) == 1.0);
    CHECK(actual(0, 1) == 2.0);
    CHECK(actual(0, 2) == 3.0);
    CHECK(actual(1, 0) == 4.0);
    CHECK(actual(1, 1) == 5.0);
    CHECK(actual(1, 2) == 6.0);
    CHECK(actual(2, 0) == 7.0);
    CHECK(actual(2, 1) == 8.0);
    CHECK(actual(2, 2) == 9.0);

  }

  SECTION("identidad") {
    matriz_3x3 actual {matriz_3x3::identidad};

    CHECK_THAT(actual, EqualsMatrix(matriz_3x3( 1, 0, 0,
                                                0, 1, 0,
                                                0, 0, 1)));
  }

  SECTION("Operator *(real)") {
    matriz_3x3 actual(1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    actual = actual * 2;
    CHECK_THAT(actual, EqualsMatrix(matriz_3x3( 2, 4, 6,
                                                8, 10, 12,
                                                14, 18, 18)));
  }

  SECTION("Operator +(matriz_3x3)") {
    matriz_3x3 left(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);

    matriz_3x3 right( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    matriz_3x3 actual = left + right;
    CHECK_THAT(actual, EqualsMatrix(matriz_3x3( 2, 4, 6,
                                                8, 10, 12,
                                                14, 16, 18)));
  }

  SECTION("Operator -(matriz_3x3)") {
    matriz_3x3 left(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);

    matriz_3x3 right( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    matriz_3x3 actual = left - right;
    CHECK_THAT(actual, EqualsMatrix(matriz_3x3( 0, 0, 0,
                                                0, 0, 0,
                                                0, 0, 0)));
  }

  SECTION("Operator *(matriz_3x3)") {
    matriz_3x3 left(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);

    matriz_3x3 right( 1.0, 2.0, 3.0,
                      4.0, 5.0, 6.0,
                      7.0, 8.0, 9.0);

    matriz_3x3 actual = left * right;
    CHECK_THAT(actual, EqualsMatrix(matriz_3x3( 30, 36, 42,
                                                66, 81, 96,
                                                102, 126, 150)));
  }

  SECTION("Operator *(vector3)") {
    matriz_3x3 left(1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0);

    vector3 right(  1.0, 2.0, 3.0);

    vector3 actual = left * right;
    CHECK_THAT(actual, EqualsVector(vector3( 26, 35, 42)));
  }
}
