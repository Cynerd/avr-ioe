narray.h
========
This implements some helping functions for null terminated arrays. Null terminated
arrays are used across whole project because they are simple and don't waste
memory space.  Their disadvantage is more complicated implementation of utility
functions and much longer adding time (they are reallocated every time new data
are added).

This implementation is limited to only contains 255 elements(limited by uint8_t
type). But it should be enough for basic usage. If you need store more than that,
you should use different approach. Also only pointers can be stored.

To define null terminated array just define pointer to you required pointer and set
it to NULL. Such narray is handled as empty. Example:
```C
int **narray = 0;
```
After adding some data (in example case data of type `int*`) you can access them
same as if you would working with simple array (`narray[i]`). Last element it such
array is `NULL`. No more valid data are stored after `NULL` (This also means that
`NULL` can't be stored to narray).

All functions are taking as parameter `void ***array`, which is pointer to null
terminated array. This parameter won't be described in functions.

## Functions and macros
### narray_add
```C
void narray_add(void ***array, void *data)
```
Add data to end of the array. This increases size of the array by one (two bytes).
#### Parameters
| data | data to be stored to array |

### narray_remove
```C
void narray_remove(void ***array, void *data)
```
Remove specified data from array. This effectively decreases size of the array by
one (two bytes).
#### Parameters
| data | data to be removed from array |

### narray_size
```C
size_t narray_size(void ***array)
```
Returns size of array.

### narray_free
```C
inline void narray_free(void ***array)
```
Frees whole array if allocated.

### fornarray
```C
#define fornarray(array, i, data) for (i = 0; (data = array[i]) != 0; i++)
```
This is macro. It implements simple foreach cycle.
#### Parameters
| array | array it self (void ** not pointer)        |
| i     | unsigned integer (uint8_t)                 |
| data  | variable which will be used to access data |
