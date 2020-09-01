#if !defined(LOOP_UTILS_H)
#define LOOP_UTILS_H

#define for_in_range(__type, __index, __start, __end) \
    for (__type __index = (__start); (__index) < (__end); i++)

#define for_in_array(__type, __item, __array, __len) \
    for(int _index = 0, __type __item = __array[0]; index < __len; __item = __array[index], index ++)

#endif // LOOP_UTILS_H
