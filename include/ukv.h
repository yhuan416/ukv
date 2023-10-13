#ifndef _UKV_H_
#define _UKV_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define UKV_OK      (0)
#define UKV_FAIL    (-1)

#define UKV_NAMESPACE_MAX_LEN  (32)

int32_t ukv_set_value(const char *namespace, const char *key, const char *value);
int32_t ukv_get_value(const char *namespace, const char *key, char *value, size_t *value_len);
int32_t ukv_delete_value(const char *namespace, const char *key);

#endif // !_UKV_H_
