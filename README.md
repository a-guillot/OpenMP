# OpenMP

OpenMP is an extension providing an easier way to use parallelism. The following examples will be in C, and should be compiled with `-Wall -fopenmp`.

**Note:** clauses and constructs are case-sensitive. In order to be sure that the statement has been recognized warnings should be enabled.

## `parallel` Construct

Encountering this instruction will create a thread team.
There is an implicit barrier at the end of the construct, i.e. every thread will have to be waiting in order to be able to continue.

### Clauses

1. `if (*scalar-expression*)`: creates the thread team only if the conditions is met.
2. `num_threads(*integer-expression*)`: creates a thread team the size of the expression.

All these clauses are optional. However, they can also be combined.

### Example (`parallel.c`)

```C
#include <stdio.h>

int main()
{
	#pragma omp parallel
	printf("Hello,\n");
	printf("World!\n");
	return 0;
}
```

## `for` Construct

Indicates that the following for loop shall be parallelized and executed by the thread team.

### Example with evenly distributed workload (`addval.c`)
Here `addval_reference` and `addval_kernel` do the same thing without the `-fopenmp` option.
However, the OpenMP call splits the work evenly between the thread team.

```C
void addval_kernel(double a[N], double b[N], double val) {
  #pragma omp parallel for
  for (size_t i = 0; i < N; i++) {
    a[i] = b[i] + val;
  }
}
```

An interesting point here is that the iterator is private by default: each thread will have a different i, and there won't be any concurrency problem.

### `reduction` Example (`reduction.c`)

OpenMP provides us with the `reduction` clause, which is very useful when you need to apply the same operation to a structure (e.g. compute the sum of an array).

The following snippet shows how it is possible to perform a reduction:

```C
#pragma omp parallel for reduction(+:sum)
  for (size_t i = 0; i < N; i++) {
    sum += a[i];
  }
```

## `schedule` Construct

Specifies the loadsharing policy. The different policies will create a varying degree of work for the runtime, which means potentially decrasing the performance.

1. `static` will divide work among the thread team using a round-robin strategy. if `CHUNK` is not specified then each thread will get a block of a similar size.
2. `dynamic` will give work to threads that don't have anything to do. `CHUNK`'s default value is 1, and represents the number of iterations that the runtime will assign to a free thread.

### Example using the `schedule` clause (`schedule.c`)

```C
#pragma omp for schedule(dynamic, CHUNK)
    for (size_t i = 0; i < SIZE; i++) {
      c[i] = a[i] + b[i];
      printf("Thread %d: c[%2zu] = %g\n", tid, i, c[i]);
    }
```
In this case each waiting thread will be assigned CHUNK iterations.

## `nowait`

`nowait` removes the implicit barrier at the end of a parallel section.

## `single`

A single block will only be executed once by any thread.

## `sections`

A section will only be executed once. The syntax is the following:

```C
#pragma omp parallel sections [clause [clause]...]
{
#pragma omp section
// Bloc 1
. . .
#pragma omp section
// Bloc N
}
```
