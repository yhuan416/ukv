#include "ukv.h"
#include "ukv_impl.h"

#include "esp_log.h"
#include "nvs_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define TAG "ukv/esp"

static SemaphoreHandle_t _get_mutex(void)
{
    static SemaphoreHandle_t g_mutex = NULL;
    if (g_mutex == NULL) {
        g_mutex = xSemaphoreCreateMutex();
    }
    return g_mutex;
}

static int32_t _open_nvs(const char *namespace, nvs_handle_t *handle)
{
    esp_err_t err;
    nvs_handle_t nvs_handle;

    err = nvs_open(namespace, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
        return UKV_FAIL;
    }

    printf("nvs_handle: %ld\n", nvs_handle);

    *handle = nvs_handle;
    return UKV_OK;
}

static int32_t _mutex_lock_(void)
{
    return (int32_t)xSemaphoreTakeRecursive(_get_mutex(), portMAX_DELAY);
}

static int32_t _mutex_unlock_(void)
{
    return (int32_t)xSemaphoreGiveRecursive(_get_mutex());
}

static int32_t _ukv_set_value_(const char *namespace, const char *key, const char *value)
{
    int32_t ret;
    esp_err_t err;
    nvs_handle_t nvs_handle;

    ret = _open_nvs(namespace, &nvs_handle);
    if (ret != UKV_OK) {
        return UKV_FAIL;
    }

    err = nvs_set_str(nvs_handle, key, value);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) set str!", esp_err_to_name(err));
        return UKV_FAIL;
    }

    return UKV_OK;
}

static int32_t _ukv_get_value_(const char *namespace, const char *key, char *value, size_t *value_len)
{
    int32_t ret;
    esp_err_t err;
    nvs_handle_t nvs_handle;

    ret = _open_nvs(namespace, &nvs_handle);
    if (ret != UKV_OK) {
        return UKV_FAIL;
    }

    err = nvs_get_str(nvs_handle, key, value, (size_t *)value_len);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) get str!", esp_err_to_name(err));
        return UKV_FAIL;
    }

    return UKV_OK;
}

static int32_t _ukv_delete_value_(const char *namespace, const char *key)
{
    int32_t ret;
    esp_err_t err;
    nvs_handle_t nvs_handle;

    ret = _open_nvs(namespace, &nvs_handle);
    if (ret != UKV_OK) {
        return UKV_FAIL;
    }

    err = nvs_erase_key(nvs_handle, key);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) erase str!", esp_err_to_name(err));
        return UKV_FAIL;
    }

    return UKV_OK;
}

ukv_impl_t g_ukv_impl = {
    .mutex_lock = _mutex_lock_,
    .mutex_unlock = _mutex_unlock_,

    .set_value = _ukv_set_value_,
    .get_value = _ukv_get_value_,

    .delete_value = _ukv_delete_value_,
};
