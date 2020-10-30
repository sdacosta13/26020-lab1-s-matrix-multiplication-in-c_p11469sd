#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
int** generateMat(int m, int n){
  // handles the memory allocation for a 2d list dimensions(m,n)
  int **mat = malloc(m * sizeof(int *));
  if(mat == NULL){
    return NULL;
  }
  for(int i=0; i < m; i++){
    mat[i] = malloc(n * sizeof(int));
    if(mat[i] == NULL){
      return NULL;
    }
  }
  return mat;
}
void freeMat(int** mat, int m){
  // frees the memory for a 2d list as defined by generateMat.
  for(int i=0; i<m; i++){
    free(mat[i]);
  }
  free(mat);
}
int getRandInt(){
  // gets a random num between 0 and 99.
  // srand must be set before call
  int randInt = rand();
  randInt = randInt % 100;
  return randInt;
}

void populateMatrix(int** mat, int dimA, int dimB){
  // sets each position of the matrix to a random int
  for(int y=0; y < dimA; y++){
    for(int x=0; x < dimB; x++){
      mat[y][x] = getRandInt();
    }
  }
}
void zeroOutMatrix(int** mat, int dimA, int dimB){
  for(int y=0; y < dimA; y++){
    for(int x=0; x < dimB; x++){
      mat[y][x] = 0;
    }
  }
}
void printMatrix(int** mat, int dimA, int dimB){
  // print mat line by line.
  for(int y=0; y < dimA; y++){
    for(int x=0; x < dimB; x++){
      printf("%d ", mat[y][x]);
    }
    printf("\n");
  }
}

void multMat(int** matA, int dimXA, int dimYA, int** matB, int dimXB, int dimYB){
  /*
      Performs the multiplication operation for matA x matB
      where:
      size(matA) = (dimXA, dimYA),
      size(matB) = (dimXB, dimYB)
      no error checking is performed to check wether the result is computable,
      as this function is not meant to be called by anything but main which
      will always call a computable result
  */
  int** result = generateMat(dimXA, dimYB); // getting a matrix in the correct output form
  zeroOutMatrix(result, dimXA, dimYB);
  for(int i = 0; i < dimXA; i++){
    for(int j = 0; j < dimYB; j++){
      for(int k = 0; k < dimXB; k++){
        result[i][j] += matA[i][k] * matB[k][j];

      }
    }
  }
  printf("RESULT:\n"); // This is cleaner than returning it to main and printing it there.
  printMatrix(result,dimXA,dimYB);
  freeMat(result,dimYB); // tidying up
}


int main(int argc, char *argv[]){
  if(argc <= 3){ // basic error handling
    printf("Incorrect number of arguments supplied\n");
    return -1;
  }

  // Now some complex error handling - not very elegant but it works

  bool crash;
  int j;
  char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  for(int i = 1; i < argc; i++){
    j = 0;
    crash = false;
    while(argv[i][j] != '\0'){
      for(int k = 0; k < 26; k++){
          if(argv[i][j] == alphabet[k]){
            crash = true;
          }
      }
      if(crash){
        printf("Invalid parameters\n");
        return -1;
      }
      j++;
    }

  }
  // It should no longer crash on unexpected inputs

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int seed = atoi(argv[3]); // converting arguments
  if(n > 0 && m > 0){
    //start timer
    clock_t begin = clock();
    int **matA = generateMat(m,n); // allocating mem
    int **matB = generateMat(n,m); // allocating mem
    if((matA == NULL) || (matB == NULL)){
      printf("An error occured.\n"); // more basic error handling
      return -1;
    } else {
      srand(seed); // setting seed for randInt
      populateMatrix(matA, m, n); // assigning random nums
      populateMatrix(matB, n, m);
      printf("MATRIX 1\n"); // outputting matrices
      printMatrix(matA, m, n);
      printf("MATRIX 2\n");
      printMatrix(matB, n, m);
      multMat(matA, m, n, matB, n, m);
      freeMat(matA, m); // tidying up
      freeMat(matB, n);
      clock_t end = clock();
      double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("EXECUTION TIME: %0.6f\n",timeSpent);
    }
  } else {
    printf("Invalid inputs.\n");
    return -1;
  }
  return 0;
}
