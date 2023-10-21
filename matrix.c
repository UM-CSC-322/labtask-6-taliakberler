//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//-----------------------------------------------------------------------------
double* input_matrix(int* numRows, int* numCols, char* name) {
  //read in matrix dimensions
  printf("Enter dimensions for %s: ", name);
  scanf("%d %d",numRows,numCols);
  //dynamically allocate memory for matrix
  double* matrix;
  int matrixSize = (*numRows)*(*numCols);
  matrix = (double *)malloc(matrixSize*sizeof(double));
  //read values into memory with row major ordering
  printf("Enter values for %s: ", name);
  for (int i = 0; i < matrixSize; i++) {
    scanf("%lf",&matrix[i]);
  }
  //return filled in matrix
  return matrix;
}
//-----------------------------------------------------------------------------
// take input of row and column of matrix elem and return array index of elem
int indexHelper(int m_cols, int row, int col) {
  return (row*m_cols + col);
}
//-----------------------------------------------------------------------------
//return 1 for success, 0 for failure
int matrix_multiply(double* matrix1, int m1_rows, int m1_cols, double* matrix2,\
 int m2_rows, int m2_cols, double* matrixResult) {
  
  //check for multiplication compatibility
  if (m1_cols != m2_rows) {
    printf("Matrices incompatible for multiplication\n");
    return 0;
  }
  else {
    int index = 0;

    for (int i = 0; i < m1_rows; i++) {
      for (int j = 0; j < m2_cols; j++) {
        for (int k = 0; k < m2_rows; k++) {
          matrixResult[indexHelper(m2_cols,i,j)] += matrix1[indexHelper(m1_cols,i,k)]\
           * matrix2[indexHelper(m2_cols,k,j)];
        }
      }
    }
  
    return 1;
  }
}
//-----------------------------------------------------------------------------
void output_matrix(double* matrixResult, int m1_rows, int m2_cols) {
  
  int matrixSize = m1_rows*m2_cols;
  int index = 0;

  for (int i = 0; i < m1_rows; i++) {
    for (int j = 0; j < m2_cols; j++) {
        printf("%.2lf ",matrixResult[index]);
        index++;
    }
    printf("\n");
  }
} 
/*---------------------------------------------------------------------------*/
int main(void) {

  double *m1,*m2,*m3;
  int m1_rows,m1_columns,m2_rows,m2_columns;

  if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&\
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&\
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
    printf("Matrix 1\n");
    output_matrix(m1,m1_rows,m1_columns);
    printf("Matrix 2\n");
    output_matrix(m2,m2_rows,m2_columns);
        
    if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
      printf("Product\n");
      output_matrix(m3,m1_rows,m2_columns);
      free(m1);
      free(m2);
      free(m3);
      return(0);
      } 
    else {
      printf("Error in dimensions\n");
      free(m1);
      free(m2);
      free(m3);
      return(-1);
      }
  } 
  else {
    free(m1);
    free(m2);
    free(m3);
    printf("Error allocating memory\n");
    return(-2);
  }
}
