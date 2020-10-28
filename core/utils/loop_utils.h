/**
 * @file loop_utils.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief For utils macros
 * @date 2020-10-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_UTILS_LOOP_UTILS_H)
#define __TITAN_UTILS_LOOP_UTILS_H

#define for_in_range(__type, __index, __start, __end) \
    for (__type __index = (__start); (__index) < (__end); __index++)

#define for_in_array(__type, __item, __array, __len) \
    for (int _index = 0, __type __item = __array[0]; _index < __len; __item = __array[_index], _index++)

#endif  // __TITAN_UTILS_LOOP_UTILS_H
