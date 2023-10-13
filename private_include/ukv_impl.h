#ifndef _UKV_IMPL_H_
#define _UKV_IMPL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define UKV_MAX_KEY_LEN     (32)
#define UKV_MAX_VALUE_LEN   (128)

typedef int32_t (*mutex_lock_func)(void);
typedef int32_t (*mutex_unlock_func)(void);

typedef int32_t (*set_value_func)(const char *namespace, const char *key, const char *value);
typedef int32_t (*get_value_func)(const char *namespace, const char *key, char *value, size_t *value_len);
typedef int32_t (*delete_value_func)(const char *namespace, const char *key);

typedef struct ukv_impl_s
{
    mutex_lock_func mutex_lock;
    mutex_unlock_func mutex_unlock;

    set_value_func set_value;
    get_value_func get_value;

    delete_value_func delete_value;
} ukv_impl_t;

extern ukv_impl_t g_ukv_impl;

#define _ukv_mutex_lock()       g_ukv_impl.mutex_lock()
#define _ukv_mutex_unlock()     g_ukv_impl.mutex_unlock()

#define _ukv_set_value(namespace, key, value) g_ukv_impl.set_value(namespace, key, value)

#define _ukv_get_value(namespace, key, value, value_len) g_ukv_impl.get_value(namespace, key, value, value_len)

#define _ukv_delete_value(namespace, key) g_ukv_impl.delete_value(namespace, key)

#endif // !_UKV_IMPL_H_