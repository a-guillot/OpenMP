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

### Example with evenly distributed workload

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

### `reduction` Example

OpenMP provides us with the `reduction` clause, which is very useful when you need to apply the same operation to a structure (e.g. compute the sum of an array).

The following snippet shows how it is possible to perform a reduction:


