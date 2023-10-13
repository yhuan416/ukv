#include <stdio.h>
#include <ctype.h>

#include "ukv.h"

#include "ukv_impl.h"

static int _ukv_is_valid_char(const char ch)
{
    if (islower(ch) || isdigit(ch) || (ch == '_') || (ch == '.')) {
        return UKV_OK;
    }
    return UKV_FAIL;
}

static int _ukv_is_valid_value(const char* value, unsigned int len)
{
    size_t value_len = 0;

    if (value == NULL) {
        return UKV_FAIL;
    }

    value_len = strlen(value);
    if ((value_len == 0) || (value_len >= UKV_MAX_VALUE_LEN) || (value_len >= len)) {
        return UKV_FAIL;
    }

    return UKV_OK;
}

static int _ukv_is_valid_key(const char* key)
{
    int i = 0;
    size_t key_len = 0;

    if (!_ukv_is_valid_value(key, UKV_MAX_KEY_LEN)) {
        return UKV_FAIL;
    }

    key_len = strlen(key);
    for (i = 0; i < key_len; i++) {
        if (!_ukv_is_valid_char(key[i])) {
            return UKV_FAIL;
        }
    }

    return UKV_OK;
}

int32_t ukv_set_value(const char *namespace, const char *key, const char *value)
{
    if (!_ukv_is_valid_key(key) || !_ukv_is_valid_value(value, UKV_MAX_VALUE_LEN)) {
        return UKV_FAIL;
    }

    return UKV_OK;
}

int32_t ukv_get_value(const char *namespace, const char *key, char *value, uint32_t *value_len)
{
    if (!_ukv_is_valid_key(key) || (value == NULL)) {
        return UKV_FAIL;
    }


    return UKV_OK;
}

int32_t ukv_delete_value(const char *namespace, const char *key)
{
    if (!_ukv_is_valid_key(key)) {
        return UKV_FAIL;
    }

    return UKV_OK;
}
