#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define ERROR   1.e-20   // Acceptable precision
#define MAX_VAL 5        // Random values are [0, MAX_VAL]
#define N       51200000 // Matrix and vector sizes (5120: UHD TV)

// Reference computation kernel (do not touch)
void reduction_reference(double a[N], double* val) {
  double sum = 0.;

  for (size_t i = 0; i < N; i++) {
    sum += a[i];
  }

  *val = sum;
}

// Computation kernel (to parallelize)
void reduction_kernel(double a[N], double* val) {
  double sum = 0.;

  #pragma omp parallel for reduction(+:sum)
  for (size_t i = 0; i < N; i++) {
    sum += a[i];
  }

  *val = sum;
}

int main() {
  double* a   = malloc(N * sizeof(double));
  double sum, sum_ref;
  double time_reference, time_kernel; 
    
  // Initialization by random values
  srand((unsigned int)time(NULL));
  for (size_t i = 0; i < N; i++) {
    a[i] = (float)rand()/(float)(RAND_MAX/MAX_VAL);
  }

  time_reference = omp_get_wtime();
  reduction_reference(a, &sum_ref);
  time_reference = omp_get_wtime() - time_reference;
  printf("Reference time : %3.5lf s\n", time_reference);
  
  time_kernel = omp_get_wtime();
  reduction_kernel(a, &sum);
  time_kernel = omp_get_wtime() - time_kernel;
  printf("Kernel time    : %3.5lf s\n", time_kernel);

  // Check if the result differs from the reference
  //if (abs(sum_ref - sum) > ERROR) {
  if (abs(sum_ref - sum) > ERROR) {
    printf("Bad results :-(((\n");
    exit(1);
  }
  printf("OK results :-)\n");
  
  free(a);
  return 0;
}
