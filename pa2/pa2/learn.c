#include<stdio.h>
#include<stdlib.h>

double** transpose(double **X, int r, int c){
  int i;
  int j;
  double **A = NULL;
  A = (double**) malloc(c * sizeof(double*));
  for(i=0;i<c;i++){
    A[i] = (double*) malloc(r * sizeof(double));
  }
  for(i=0;i<r;i++){
    for(j=0;j<c;j++){
      A[j][i] = X[i][j];
    }
  }
  return A;
}

double** multione(double **X, double **Y, int r, int c){
  int i;
  int j;
  int k;
  int l = c;
  double **A = NULL;
  A = (double**) malloc(l * sizeof(double*));
  for(i=0;i<l;i++){
    A[i] = (double*) malloc(c * sizeof(double));
  }
  for(i=0;i<c;i++){
    for(j=0;j<c;j++){
      for(k=0;k<r;k++){
        A[i][j] = A[i][j] + X[i][k] * Y[k][j];
      }
    }
  }
  return A;
}

double** multitwo(double **X, double **Y, int r, int c){
  int i;
  int j;
  int k;
  double **A = NULL;
  A = (double**) malloc(c * sizeof(double*));
  for(i=0;i<c;i++){
    A[i] = (double*) malloc(r * sizeof(double));
  }
  for(i=0;i<c;i++){
    for(j=0;j<r;j++){
      for(k=0;k<c;k++){
        A[i][j] = A[i][j] + X[i][k] * Y[k][j];
      }
    }
  }
  return A;
}

double** multithree(double **X, double **Y, int r, int c){
  int i;
  int k;
  double **A = NULL;
  A = (double**) malloc(c * sizeof(double*));
  for(i=0;i<c;i++){
    A[i] = (double*) malloc(1 * sizeof(double));
  }
  for(i=0;i<c;i++){
    for(k=0;k<r;k++){
      A[i][0] = A[i][0] + X[i][k] * Y[k][0];
    }
  }
  return A;
}

double** inverse(double **X, int r, int c){
  int x;
  int i;
  int j;
  double num;
  double val;
  int a;
  int b;
  double** B;
  for(x=0;x<c;x++){
    for(i=0;i<c;i++){
      if(x<=i){
        num = X[x][x];
        val = X[i][x]/X[x][x];
        for(j=0;j<r;j++){
          if(x==i){
            X[i][j] = X[i][j]/num;
          } else {
            X[i][j] = X[i][j] - X[x][j] * val;
          }
        }
      }
    }
  }
  for(x=(c-1);x>=0;x--){
    for(i=(c-1);i>=0;i--){
      if(x>=i){
        num = X[x][x];
        val = X[i][x]/X[x][x];
        for(j=0;j<r;j++){
          if(x==i){
            X[i][j] = X[i][j]/num;
          } else {
            X[i][j] = X[i][j] - X[x][j] * val;
          }
        }
      }
    }
  }
  a = c;
  B = (double**) malloc(c * sizeof(double*));
  for(i=0;i<c;i++){
    B[i] = (double*) malloc(a * sizeof(double));
  }
  for(i=0;i<c;i++){
    b = c;
    for(j=c;j<(c*2);j++){
      B[i][j-b] = X[i][j];
    }
  }
  return B;
}

void freeArray(double** F, int r){
  int i;
  for(i=0;i<r;i++){
    free(F[i]);
  }
  free(F);
  return;
}

int main(int argc, char** argv){
  double **X;
  double **Y;
  double **T;
  double **M;
  double **I;
  double **N;
  double **W;
  double **A;
  int j;
  int i;
  int k;
  int n;
  int a;
  int d;
  char ch;
  FILE *f1;
  f1 = fopen(argv[1], "r");
  if(f1 == NULL){
    exit(0);
  }
  if(argc<2){
    exit(0);
  }
  fscanf(f1, "%d\n", &n);
  fscanf(f1, "%d\n", &k);
  n = n+1;
  d = k;
  X = (double**) malloc(k * sizeof(double*));
  for(i=0;i<k;i++){
    X[i] = (double*) malloc(n * sizeof(double));
  }
  Y = (double**) malloc(k * sizeof(double*));
  for(i=0;i<k;i++){
    Y[i] = (double*) malloc(n * sizeof(double));
  }
  while(!feof(f1)){
    for(i=0;i<k;i++){
      X[i][0] = 1;
    }
    for(i=0;i<k;i++){
      for(j=1;j<n;j++){
        fscanf(f1, "%lf%c", &X[i][j], &ch);
      }
      fscanf(f1, "%lf\n", &Y[i][0]);
    }
  }
  T = transpose(X, k, n);
  M = multione(T, X, k, n);
  A = (double**) malloc(n * sizeof(double*));
  for(i=0;i<n;i++){
    A[i] = (double*) malloc((2*k) * sizeof(double));
  }
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      A[i][j] = M[i][j];
    }
  }
  for(i=0;i<n;i++){
    a = n;
    for(j=a;j<k;j++){
      if(i==(j-a)){
        A[i][j] = 1;
      } else {
        A[i][j] = 0;
      }
    }
  }
  I = inverse(A, k, n);
  N = multitwo(I, T, k, n);
  W = multithree(N, Y, k, n);
  fclose(f1);
  double** B;
  FILE *f2;
  f2 = fopen(argv[2], "r");
  if(f2 == NULL){
    exit(0);
  }
  if(argc<2){
    exit(0);
  }
  fscanf(f2, "%d\n", &k);
  B = (double**) malloc(k * sizeof(double*));
  for(i=0;i<k;i++){
    B[i] = (double*) malloc(n * sizeof(double));
  }
  while(!feof(f2)){
    for(i=0;i<k;i++){
      B[i][0] = 1;
    }
    for(i=0;i<k;i++){
      for(j=1;j<n;j++){
        fscanf(f2, "%lf%c", &B[i][j], &ch);
      }
    }
  }
  double **C;
  int l;
  C = (double**) malloc(k * sizeof(double*));
  for(i=0;i<k;i++){
    C[i] = (double*) malloc(1 * sizeof(double));
  }
  for(i=0;i<k;i++){
    for(l=0;l<n;l++){
      C[i][0] = C[i][0] + B[i][l] * W[l][0];
    }
  }
  for(i=0;i<k;i++){
    printf("%0.0lf\n", C[i][0]);
  }
  fclose(f2);
  freeArray(X, d);
  freeArray(Y, n);
  freeArray(T, n);
  freeArray(M, n);
  freeArray(A, n);
  freeArray(I, n);
  freeArray(N, n);
  freeArray(W, n);
  freeArray(B, k);
  freeArray(C, k);
  return 0;
}

