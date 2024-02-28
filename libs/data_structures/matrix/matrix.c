#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int compare( const void* a, const void* b)
{
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_matrix(int *a, int *b, matrix *m, int col1, int col2) {
    swap(a, b);

    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];

        int temp2 = row[col1];
        row[col1] = row[col2];
        row[col2] = temp2;
    }
}

void insertionSortBySumRows(int *rows, matrix *m) {
    for (size_t i = 1; i < m->nRows; i++) {
        int t = rows[i];
        int *row = m->values[i];
        int j = i;
        while (j > 0 && rows[j - 1] > t) {
            rows[j] = rows[j - 1];
            m->values[j] = m->values[j - 1];
            j--;
        }
        rows[j] = t;
        m->values[j] = row;
    }
}

void selectionSortBySumCols(int *a, matrix *m) {
    for (int i = 0; i < m->nCols - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < m->nCols; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap_matrix(&a[i], &a[minPos], m, i, minPos);
    }
}

//--------------------------------------------------------------

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }

    free(m->values);

    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &row[j]);
        }
    }
}

void outputMatrix(matrix m) {
    outputMatrixSum(m, false);
}

void outputMatrixSum(matrix m, bool showSum) {
    for (int i = 0; i < m.nRows; i++) {
        int sum = 0;
        for (int j = 0; j < m.nCols; j++) {
            printf("%d\t", m.values[i][j]);
            sum += m.values[i][j];
        }
        if (showSum) {
            printf("=%d\n", sum);
        } else {
            printf("\n");
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int a = 0; a < nMatrices; a++) {
        inputMatrix(&ms[a]);
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int a = 0; a < nMatrices; a++) {
        outputMatrix(ms[a]);
        printf("\n");
    }
}

void swapRows(matrix m, int i1, int i2) {
    if ((i1 >= m.nRows) || (i2 >= m.nRows)) {
        fprintf(stderr, "matrix index out of bounds");
        exit(1);
    }

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nCols; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

int getSumCol(int **values, int nRows, int n) {
    int sum = 0;
    for (int i = 0; i < nRows; i++) {
        int *row = values[i];
        sum += row[n];
    }
    return sum;
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        int sum = criteria(m.values[i], m.nCols);
        arr[i] = sum;
    }
    insertionSortBySumRows(arr, &m);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    bool debug = false;
    int arr[m.nCols];

    for (int i = 0; i < m.nCols; i++) {
        int col[m.nRows];

        for (int j = 0; j < m.nRows; j++) {
            int *row = m.values[j];
            col[j] = row[i];
        }

        int sum = criteria(col, m.nRows);
        arr[i] = sum;
        if (debug) {
            printf("%d\t", sum);
        }
    }
    if (debug) {
        printf("\n");
    }
    selectionSortBySumCols(arr, &m);
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows) {
        return false;
    }
    if (m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        int *row1 = m1->values[i];
        int *row2 = m2->values[i];

        int res = memcmp(row1, row2, sizeof(int) * m1->nCols);

        if (res) {
            return false;
        }
    }
    return true;
}

bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];
        for (int j = 0; j < m->nCols; j++) {
            if (i == j) {
                if (row[j] != 1) {
                    return false;
                }
            } else {
                if (row[j] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void transposeSquareMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i; j < m->nCols; j++) {
            if (i != j) {
                swap(&m->values[i][j], &m->values[j][i]);
            }
        }
    }
}

void transposeMatrix(matrix *m) {
    matrix m_new = getMemMatrix(m->nCols, m->nRows);

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            m_new.values[j][i] = m->values[i][j];
        }
    }
    freeMemMatrix(m);
    *m = m_new;
}

position getMinValuePos(matrix m) {
    position pos = {-1, -1};

    int min = INT_MAX;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }
        }
    }
    return pos;
}

position getMaxValuePos(matrix m) {
    position pos = {1, 1};

    int max = INT_MIN;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                pos.rowIndex = i;
                pos.colIndex = j;
            }
        }
    }
    return pos;
}

matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols) {

    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = a[k++];
        }
    }
    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}

//=============================================================================================================

void replaceMinMAx(matrix m) {
    int max = INT_MIN;
    int min = INT_MAX;
    int maxI = 0;
    int minI = 0;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                minI = i;
            }
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                maxI = i;
            }
        }
    }
    swapRows(m, maxI, minI);
}

int getMax(int *a, int n) {
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

void sortRowsByMinElement(matrix m) {
    int arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        int max = getMax(m.values[i], m.nCols);
        arr[i] = max;
    }
    insertionSortBySumRows(arr, &m);
}

int getMin(int *a, int n) {
    int min = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

void sortColsByMinElement(matrix m) {
    int arr[m.nCols];

    for (int i = 0; i < m.nCols; i++) {
        int col[m.nRows];

        for (int j = 0; j < m.nRows; j++) {
            int *row = m.values[j];
            col[j] = row[i];
        }

        int sum = getMin(col, m.nRows);
        arr[i] = sum;
        selectionSortBySumCols(arr, &m);
    }
}

matrix mulMatrices(matrix m1, matrix m2) {
    matrix m_new = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            m_new.values[i][j] = 0;

            for (int k = 0; k < m2.nRows; k++) {
                m_new.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }

    return m_new;
}


void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (m->nRows != m->nCols) {
        fprintf(stderr, "Not Symmetric");
        exit(1);
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                fprintf(stderr, "Not Symmetric");
                exit(1);
            }
        }
    }
    matrix m3 = mulMatrices(*m, *m);

    freeMemMatrix(m);
    *m = m3;
}

bool isUnique(long long *a, int n) {
    qsort(a, n, sizeof(long long), compare);

    int temp = 0;
    for (int i = 0; i < n; i++) {
        if (a[i+1] == a[i]) {
            return false;
        }
    }
    return true;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        long long sum = getSum(m.values[i], m.nCols);
        arr[i] = sum;
    }
    bool res = isUnique(arr, m.nRows);

    if (res) {
        transposeSquareMatrix(&m);
    } else {
        fprintf(stderr, "Not Unique");
        exit(1);
    }
}
