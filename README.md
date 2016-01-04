# libds - datastructures

`libds` is a library providing simple datastructures. It is designed to be portable (to the point only
requiring memory allocation and ffreestanding environment).

## Provided data structures
* `ds/random.h` - random number generator
* `ds/array.h` - resizable array list
* `ds/btree.h` - ballanced tree (red/black tree)
* `ds/hmap.h` - hashmap 
* `ds/queue.h` - (FIFO) queue
* `ds/funcops.h` - standard function interfaces used by previous data structures (along with some defined concrete functions) 

## Requirements 

`libds` requires these headers to be present at build environment:

* `<stdbool.h>`
* `<stddef.h>`
* `<stdint.h>`

`libds` also requires these extern functions:

* `extern void* malloc(size_t n)`
* `extern void* calloc(size_t num, size_t n)`
* `extern void* realloc(void* a, size_t n)`
* `extern void  free(void* a)`
* `extern int   strcmp(const char* a, const char* b)`
* `extern void* memset(void* c, int v, size_t s)`

## Building libds

To build libds, simply invoke `make all` in the root directory. You will need to provide suitable `SYSROOT` argument or a `PREFIX` argument. `INCLUDE` argument can be overwritten to change where headers will be copied to (they will always be in `INCLUDE`/`ds` directory).