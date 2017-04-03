# OpenMP

OpenMP is an extension providing an easier way to use parallelism. The following examples will be in C, and should be compiled with `-Wall -fopenmp`.

**Note:** clauses and constructs are case-sensitive. In order to be sure that the statement has been recognized warnings should be enabled.

## `parallel` Construct

Encountering this instruction will create a thread team.
There is an implicit barrier at the end of the construct, i.e. every thread will have to be waiting in order to be able to continue.

### Clauses

1. `if (*scalar-expression*)`: creates the thread team only if the conditions is met.
2. `num_threads(*integer-expression*)`: creats a thread team the size of the expression.

### Example (`parallel.c`)

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
