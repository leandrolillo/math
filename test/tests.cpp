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

    actual = 2 * actual;
    CHECK_THAT(actual, EqualsMatrix(matriz_2x2( 4, 8,
                                                12, 16)));
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

    actual = 2 * actual;
    CHECK_THAT(actual, EqualsMatrix(matriz_3x3( 4, 8, 12,
                                                16, 18, 24,
                                                28, 36, 48)));

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

TEST_CASE("matriz 4x4") {
  SECTION("Metadata") {
    matriz_4x4 actual(1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0);
    CHECK(actual.getNroFilas() == 4);
    CHECK(actual.getNroColumnas() == 4);
  }

  SECTION("Operator(i, j)") {
    matriz_4x4 actual(1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0);

    CHECK(actual(0, 0) == 1.0);
    CHECK(actual(0, 1) == 2.0);
    CHECK(actual(0, 2) == 3.0);
    CHECK(actual(0, 3) == 4.0);
    CHECK(actual(1, 0) == 5.0);
    CHECK(actual(1, 1) == 6.0);
    CHECK(actual(1, 2) == 7.0);
    CHECK(actual(1, 3) == 8.0);
    CHECK(actual(2, 0) == 9.0);
    CHECK(actual(2, 1) == 10.0);
    CHECK(actual(2, 2) == 11.0);
    CHECK(actual(2, 3) == 12.0);
    CHECK(actual(3, 0) == 13.0);
    CHECK(actual(3, 1) == 14.0);
    CHECK(actual(3, 2) == 15.0);
    CHECK(actual(3, 3) == 16.0);


  }

  SECTION("identidad") {
    matriz_4x4 actual {matriz_4x4::identidad};

    CHECK_THAT(actual, EqualsMatrix(matriz_4x4( 1, 0, 0, 0,
                                                0, 1, 0, 0,
                                                0, 0, 1, 0,
                                                0, 0, 0, 1)));
  }

  SECTION("Operator *(real)") {
    matriz_4x4 actual(1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0);

    actual = actual * 2;
    CHECK_THAT(actual, EqualsMatrix(matriz_4x4( 2, 4, 6, 8,
                                                10, 12, 14, 16,
                                                18, 20, 22, 24,
                                                26, 28, 30, 32)));

    actual = 2 * actual;
    CHECK_THAT(actual, EqualsMatrix(matriz_4x4( 4, 8, 12, 16,
                                                20, 24, 28, 32,
                                                36, 40, 44, 48,
                                                52, 56, 60, 64)));

  }

  SECTION("Operator +(matriz_4x4)") {
    matriz_4x4 left(1.0, 2.0, 3.0, 4.0,
                    5.0, 6.0, 7.0, 8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);

    matriz_4x4 right( 1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0);

    matriz_4x4 actual = left + right;
    CHECK_THAT(actual, EqualsMatrix(matriz_4x4( 2, 4, 6, 8,
                                                10, 12, 14, 16,
                                                18, 20, 22, 24,
                                                26, 28, 30, 32)));
  }

  SECTION("Operator -(matriz_4x4)") {
    matriz_4x4 left(1.0, 2.0, 3.0, 4.0,
                    5.0, 6.0, 7.0, 8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);

    matriz_4x4 right( 1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0);

    matriz_4x4 actual = left - right;
    CHECK_THAT(actual, EqualsMatrix(matriz_4x4( 0, 0, 0, 0,
                                                0, 0, 0, 0,
                                                0, 0, 0, 0,
                                                0, 0, 0, 0)));
  }

  SECTION("Operator *(matriz_4x4)") {
    matriz_4x4 left(1.0, 2.0, 3.0, 4.0,
                    5.0, 6.0, 7.0, 8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);

    matriz_4x4 right( 1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0);

    matriz_4x4 actual = left * right;
    CHECK_THAT(actual, EqualsMatrix(matriz_4x4( 90, 100, 110, 120,
                                                202, 228,  254, 280,
                                                314, 356, 398, 440,
                                                426, 484, 542, 600)));
  }

  SECTION("Operator *(vector4)") {
    matriz_4x4 left(1.0, 2.0, 3.0, 4.0,
                    5.0, 6.0, 7.0, 8.0,
                    9.0, 10.0, 11.0, 12.0,
                    13.0, 14.0, 15.0, 16.0);

    vector4 right(  1.0, 2.0, 3.0, 4.0);

    vector4 actual = left * right;
    CHECK_THAT(actual, EqualsVector(vector4( 82, 63, 106, 13+28+45+64)));
  }

  SECTION("projections") {
    matriz_4x4 projection = matriz_4x4::perspectiveProjection(800, 600, 10, 100);
    projection = matriz_4x4::perspectiveProjectionFov(45, 1.3, 10, 100);
    projection = matriz_4x4::orthographicProjection(800, 600, -1, 1);
    projection = matriz_4x4::orthographicProjection(0, 0, 800, 600, -1, 1);
  }
}

TEST_CASE("Vector2") {
  SECTION("Metadata") {
    vector2 actual(1.0, 2.0);
    CHECK(actual.getLength() == 2);
  }

  SECTION("Operator(i)") {
    vector2 actual(1.0, 2.0);

    CHECK((actual(0) == 1.0 && actual.x == 1.0));
    CHECK((actual(1) == 2.0 && actual.y == 2.0));
  }

  SECTION("Operator+(vector2)") {
    vector2 left(1.0, 2.0);
    vector2 right(1.0, 2.0);

    vector2 actual = left + right;
    CHECK_THAT(actual, EqualsVector(vector2(2, 4)));
  }
  SECTION("Operator-(vector3)") {
    vector2 left(1.0, 2.0);
    vector2 right(1.0, 2.0);

    vector2 actual = left - right;
    CHECK_THAT(actual, EqualsVector(vector2(0, 0)));

    actual = -left;
    CHECK_THAT(actual, EqualsVector(vector2(-1, -2)));
  }

  SECTION("Operator*(real)") {
    vector2 left(1.0, 2.0);
    real right = 2.0;

    vector2 actual = left * right;
    CHECK_THAT(actual, EqualsVector(vector2(2, 4)));

    actual = right * left;
    CHECK_THAT(actual, EqualsVector(vector2(2, 4)));

  }

  SECTION("Operator*(vector) - dot product") {
    vector2 left(1.0, 2.0);
    vector2 right(3.0, 4.0);

    real actual = left * right;
    CHECK(actual == 11);

    actual = right * left;
    CHECK(actual == 11);
  }

  SECTION("Modulo") {
    vector2 left(3.0, 4.0);

    real actual = left.modulo();
    CHECK(actual == 5);
  }

  SECTION("Normalizado") {
    vector2 left(3.0, 4.0);

    vector2 actual = left.normalizado();
    CHECK_THAT(actual, EqualsVector(vector2(3/5, 4/5)));
  }

}

TEST_CASE("vector3") {
  SECTION("Metadata") {
    vector3 actual(1.0, 2.0, 3.0);
    CHECK(actual.getLength() == 3);
  }

  SECTION("Operator(i)") {
    vector3 actual(1.0, 2.0, 3.0);

    CHECK((actual(0) == 1.0 && actual.x == 1.0));
    CHECK((actual(1) == 2.0 && actual.y == 2.0));
    CHECK((actual(2) == 3.0 && actual.z == 3.0));
  }

  SECTION("Operator+(vector3)") {
    vector3 left(1.0, 2.0, 3.0);
    vector3 right(1.0, 2.0, 3.0);

    vector3 actual = left + right;
    CHECK_THAT(actual, EqualsVector(vector3(2, 4, 6)));
  }
  SECTION("Operator-(vector3)") {
    vector3 left(1.0, 2.0, 3.0);
    vector3 right(1.0, 2.0, 3.0);

    vector3 actual = left - right;
    CHECK_THAT(actual, EqualsVector(vector3(0, 0, 0)));

    actual = -left;
    CHECK_THAT(actual, EqualsVector(vector3(-1, -2, -3)));
  }

  SECTION("Operator*(real)") {
    vector3 left(1.0, 2.0, 3.0);
    real right = 2.0;

    vector3 actual = left * right;
    CHECK_THAT(actual, EqualsVector(vector3(2, 4, 6)));

    actual = right * left;
    CHECK_THAT(actual, EqualsVector(vector3(2, 4, 6)));

  }

  SECTION("Operator*(vector) - dot product") {
    vector3 left(1.0, 2.0, 3.0);
    vector3 right(3.0, 4.0, 5.0);

    real actual = left * right;
    CHECK(actual == 26);

    actual = right * left;
    CHECK(actual == 26);
  }

  SECTION("Operator(vector) - cross product") {
    vector3 left(1.0, 0.0, 0.0);
    vector3 right(0.0, 1.0, 0.0);

    vector actual = left ^ right;
    CHECK_THAT(actual, EqualsVector(vector3(0, 0, 1)));
  }

  SECTION("Modulo") {
    vector3 left(2.0, 2.0, 1.0);

    real actual = left.modulo();
    CHECK(actual == 3);
  }

  SECTION("Normalizado") {
    vector3 left(2.0, 2.0, 1.0);

    vector3 actual = left.normalizado();
    CHECK_THAT(actual, EqualsVector(vector3(2/3, 2/3, 1/3)));
  }

}

TEST_CASE("vector4") {
  SECTION("Metadata") {
    vector4 actual(1.0, 2.0, 3.0, 4.0);
    CHECK(actual.getLength() == 4);
  }

  SECTION("Operator(i)") {
    vector4 actual(1.0, 2.0, 3.0, 4.0);

    CHECK((actual(0) == 1.0 && actual.x == 1.0));
    CHECK((actual(1) == 2.0 && actual.y == 2.0));
    CHECK((actual(2) == 3.0 && actual.z == 3.0));
    CHECK((actual(3) == 4.0 && actual.w == 4.0));
  }

  SECTION("Operator+(vector4)") {
    vector4 left(1.0, 2.0, 3.0, 4.0);
    vector4 right(1.0, 2.0, 3.0, 4.0);

    vector4 actual = left + right;
    CHECK_THAT(actual, EqualsVector(vector4(2, 4, 6, 8)));
  }
  SECTION("Operator-(vector4)") {
    vector4 left(1.0, 2.0, 3.0, 4.0);
    vector4 right(1.0, 2.0, 3.0, 4.0);

    vector4 actual = left - right;
    CHECK_THAT(actual, EqualsVector(vector4(0, 0, 0, 0)));

    actual = -left;
    CHECK_THAT(actual, EqualsVector(vector4(-1, -2, -3, -4)));
  }

  SECTION("Operator*(real)") {
    vector4 left(1.0, 2.0, 3.0, 4.0);
    real right = 2.0;

    vector4 actual = left * right;
    CHECK_THAT(actual, EqualsVector(vector4(2, 4, 6, 8)));

    actual = right * left;
    CHECK_THAT(actual, EqualsVector(vector4(2, 4, 6, 8)));

  }

  //TODO: Review vector4/quaternion operator * is not dot product but quaternion multiplication
//  SECTION("Operator*(vector4) - quaternion multiplication") {
//    vector4 left(1.0, 2.0, 3.0, 4.0);
//    vector4 right(5.0, 6.0, 7.0, 8.0);
//
//    real actual = left * right;
//    CHECK(actual == 70);
//
//    actual = right * left;
//    CHECK(actual == 70);
//  }

  SECTION("Modulo") {
    vector4 left(1.0, 1.0, 1.0, 1.0);

    real actual = left.modulo();
    CHECK(actual == 2);
  }

  SECTION("Normalizado") {
    vector4 left(1.0, 1.0, 1.0, 1.0);

    vector4 actual = left.normalizado();
    CHECK_THAT(actual, EqualsVector(vector4(1/2, 1/2, 1/2, 1/2)));
  }

}
