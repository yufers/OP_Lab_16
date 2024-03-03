#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"

void test_replaceMinMAx() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 8, 9,
                    4, 5, 6,
                    1, 2, 3
            },
            3, 3
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    6, 8, 9,
                    4, 5, 6,
                    1, 2, 3
            },
            3, 3
    );
    replaceMinMax(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    assert(!areTwoMatricesEqual(&m1, &m3));
}

void test_sortRowsByMinElement() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 1, 2,
                    1, 8, 1,
                    3, 2, 3
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    3, 2, 3,
                    7, 1, 2,
                    1, 8, 1
            },
            3, 3
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    4, 2, 3,
                    7, 1, 2,
                    1, 8, 1
            },
            3, 3
    );
    sortRowsByMinElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    assert(!areTwoMatricesEqual(&m1, &m3));
}

void test_sortColsByMinElement() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 2, 4, 3, 3,
                    2, 5, 1, 8, 2, 7,
                    6, 1, 4, 4, 8, 3
            },
            3, 6
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 2, 3, 3, 3, 4,
                    5, 1, 2, 2, 7, 8,
                    1, 4, 6, 8, 3, 4,
            },
            3, 6
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    6, 2, 3, 3, 3, 4,
                    5, 1, 2, 2, 7, 8,
                    1, 4, 6, 8, 3, 4,
            },
            3, 6
    );
    sortColsByMinElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    assert(!areTwoMatricesEqual(&m1, &m3));
}

void test_getSquareOfMatrixIfSymmetric() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 1, 5,
                    1, 3, 6,
                    5, 6, 4
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    30, 35, 36,
                    35, 46, 47,
                    36, 47, 77
            },
            3, 3
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    6, 2, 3, 3, 3, 4,
                    5, 1, 2, 2, 7, 8,
                    1, 4, 6, 8, 3, 4,
            },
            3, 6
    );
    getSquareOfMatrixIfSymmetric(&m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    assert(!areTwoMatricesEqual(&m1, &m3));
}

void test_transposeIfMatrixHasNotEqualSumOfRows() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9
            },
            3, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

bool test_isMutuallyInverseMatrices() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 1,
                    1, 2
            },
            2, 2
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 1,
                    1, 2
            },
            2, 2
    );

    bool res = isMutuallyInverseMatrices(m1, m2);
    assert(res);
}

long long test_findSumOfMaxesOfPseudoDiagonal() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 2, 5, 4,
                    1, 3, 6, 3,
                    3, 2, 1, 2
            },
            3, 4
    );
    long long res = findSumOfMaxesOfPseudoDiagonal(m1);
    assert(res == 20);
}

int test_getMinInArea() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    10, 7, 5, 6,
                    3, 11, 8, 9,
                    4, 1, 12, 2
            },
            3, 4
    );

    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 1, 1,
                    0, 1, 1, 1,
                    0, 0, 1, 0
            },
            3, 4
    );

    int res = getMinInArea(m1, m);
    assert(res == 5);
}

void test_sortByDistances() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    8, 3, 4,
                    1, 6, 1,
                    12, 1, 1,
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1,6,1,
                    8,3,4,
                    12,1,1
            },
            3, 3
    );

    sortByDistances(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

int test_countEqClassesByRowsSum() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 1,
                    2, 7,
                    5, 4,
                    4, 3,
                    1, 6,
                    8, 0
            },
            6, 2
    );
    int res = countEqClassesByRowsSum(m1);
    assert(res == 3);
}

int test_getNSpecialElement() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 5, 4,
                    2, 3, 6, 7,
                    12, 2, 1, 2
            },
            3, 4
    );
    int res = getNSpecialElement(m1);
    assert(res == 2);
}

void test_swapPenultimateRow() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 1
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    1, 4, 7,
                    7, 8, 1
            },
            3, 3
    );

    swapPenultimateRow(m1, 3);
    assert(areTwoMatricesEqual(&m1, &m2));
}

int test_countNonDescendingRowsMatrices() {
    int matrixes[] = {7, 1, 1, 1,
                      1, 6, 2, 2,
                      5, 4, 2, 3,
                      1, 3, 7, 9};
    matrix *ms = createArrayOfMatrixFromArray(matrixes, 4, 2, 2);

    int res = countNonDescendingRowsMatrices(ms, 4);
    assert(res == 2);
}

int test_countZeroRows() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    0,0,
                    0,0,
                    4,7,
            },
            3, 2
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    0,1,
                    0,2,
                    0,3
            },
            3, 2
    );

    int res1 = countZeroRows(m1);
    int res2 = countZeroRows(m2);
    assert(res1 == 2);
    assert(res2 == 0);
}

int test_getMatrixNorma() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    -3,6,7,
                    8,2,2,
                    -159,25,3
            },
            3, 3
    );

    int res = getMatrixNorma(m1);
    assert(res == 159);
}

int test_getNSpecialElement2() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2,3,5,5,4,
                    6,2,3,8,12,
                    12,12,2,1,2
            },
            3, 5
    );

    int res = getNSpecialElement2(m1);
    assert(res == 4);
}

int test_getVectorIndexWithMaxAngle() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1,2,3,
                    4,5,6,
                    7,8,9
            },
            3, 3
    );
    int arr[3] = {3, 6, 9};

    int res = getVectorIndexWithMaxAngle(m1, arr);
    assert(res == 2);
}

long long test_getSpecialScalarProduct() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 9, 6,
                    7, 8, 5
            },
            3, 3
    );

    long long res = getSpecialScalarProduct(m1, 3);
    assert(res == 82);
}

void test() {
    test_replaceMinMAx();
    test_sortRowsByMinElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
    test_getNSpecialElement();
    test_swapPenultimateRow();
    test_countNonDescendingRowsMatrices();
    test_countZeroRows();
    test_getMatrixNorma();
    test_getNSpecialElement2();
    test_getVectorIndexWithMaxAngle();
    test_getSpecialScalarProduct();
}

int main() {
    test();

    return 0;
}
