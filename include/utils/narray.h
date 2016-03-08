#include <stdlib.h>
#include <stdint.h>

#ifndef _IOE_NARRAY_H_
#define _IOE_NARRAY_H_
#ifdef CONFIG_IOE_NARRAY

void narray_add(void ***array, void *data);
void narray_remove(void ***array, void *data);
size_t narray_size(void ***array);
inline void narray_free(void ***array) {
    if (array != NULL) {
        free(*array);
        *array = NULL;
    }
}

#define fornarray(array, i, data) for (i = 0; (data = array[i]) != 0; i++)

#endif /* CONFIG_IOE_NARRAY */
#endif /* _IOE_NARRAY_H_ */
