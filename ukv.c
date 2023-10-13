#include <stdio.h>
#include <ctype.h>

#include "ukv.h"

#include "ukv_impl.h"

#define TRUE    (1)
#define FALSE   (0)

static int _ukv_is_valid_char(const char ch)
{
    if (islower(ch) || isdigit(ch) || (ch == '_') || (ch == '.')) {
        return TRUE;
    }
    return FALSE;
}

static int _ukv_is_valid_value(const char* value, unsigned int len)
{
    size_t value_len = 0;

    if (value == NULL) {
        return FALSE;
    }

    value_len = strlen(value);
    if ((value_len == 0) || (value_len >= UKV_MAX_VALUE_LEN) || (value_len >= len)) {
        return FALSE;
    }

    return TRUE;
}

static int _ukv_is_valid_key(const char* key)
{
    int i = 0;
    size_t key_len = 0;

    if (!_ukv_is_valid_value(key, UKV_MAX_KEY_LEN)) {
        return FALSE;
    }

    key_len = strlen(key);
    for (i = 0; i < key_len; i++) {
        if (!_ukv_is_valid_char(key[i])) {
            return FALSE;
        }
    }

    return TRUE;
}

int32_t ukv_set_value(const char *namespace, const char *key, const char *value)
{
    int32_t ret = UKV_OK;

    if (!_ukv_is_valid_key(key) || !_ukv_is_valid_value(value, UKV_MAX_VALUE_LEN)) {
        return UKV_FAIL;
    }

    _ukv_mutex_lock();

    ret = _ukv_set_value(namespace, key, value);

    _ukv_mutex_unlock();

    return ret;
}

int32_t ukv_get_value(const char *namespace, const char *key, char *value, size_t *value_len)
{
    int32_t ret = UKV_OK;

    if (!_ukv_is_valid_key(key) || (value == NULL)) {
        return UKV_FAIL;
    }

    _ukv_mutex_lock();

    ret = _ukv_get_value(namespace, key, value, value_len);

    _ukv_mutex_unlock();

    return ret;
}

int32_t ukv_delete_value(const char *namespace, const char *key)
{
    int32_t ret = UKV_OK;

    if (!_ukv_is_valid_key(key)) {
        return UKV_FAIL;
    }

    _ukv_mutex_lock();

    ret = _ukv_delete_value(namespace, key);

    _ukv_mutex_unlock();

    return ret;
}
