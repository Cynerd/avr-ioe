#include <utils/narray.h>

#ifdef CONFIG_IOE_NARRAY

void narray_add(void ***array, void *data) {
    if (*array == NULL) {
        *array = malloc(2 * sizeof(void *));
        (*array)[0] = data;
        (*array)[1] = NULL;
    } else {
        uint8_t size = narray_size(array);
        *array = realloc(*array, (size + 2) * sizeof(void *));
        (*array)[size] = data;
        (*array)[size + 1] = NULL;
    }
}

void narray_remove(void ***array, void *data) {
    uint8_t i = 0;
    while ((*array)[i] != NULL || (*array)[i] != data)
        i++;
    while ((*array)[i + 1] != NULL) {
        (*array)[i] = (*array)[i + 1];
        i++;
    }
    (*array)[i] = NULL;
    *array = realloc(*array, (i + 1) * sizeof(void *));
}

uint8_t narray_size(void ***array) {
    uint8_t size = 0;
    while ((*array)[size++] != NULL);
    return size;
}

#endif /* CONFIG_IOE_NARRAY */
