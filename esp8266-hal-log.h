/**
 * Simple esp8266 log library for using log_i() and similar functions based on esp32-hal-log
 *
 */

#ifndef __ARDUHAL_LOG_H__
#define __ARDUHAL_LOG_H__

#ifdef __cplusplus
extern "C"
{
#endif


#define DEBUG_ESP_PORT Serial

#define ARDUHAL_LOG_LEVEL_NONE      (0)
#define ARDUHAL_LOG_LEVEL_ERROR     (1)
#define ARDUHAL_LOG_LEVEL_WARN      (2)
#define ARDUHAL_LOG_LEVEL_INFO      (3)
#define ARDUHAL_LOG_LEVEL_DEBUG     (4)
#define ARDUHAL_LOG_LEVEL_VERBOSE   (5)

#ifndef CONFIG_ARDUHAL_LOG_DEFAULT_LEVEL
#define CONFIG_ARDUHAL_LOG_DEFAULT_LEVEL ARDUHAL_LOG_LEVEL_NONE
#endif

#ifndef CORE_DEBUG_LEVEL
#define ARDUHAL_LOG_LEVEL CONFIG_ARDUHAL_LOG_DEFAULT_LEVEL
#else
#define ARDUHAL_LOG_LEVEL CORE_DEBUG_LEVEL
#endif

const char *pathToFileName(const char *path)
{
  size_t i = 0;
  size_t pos = 0;
  char *p = (char *)path;
  while (*p)
  {
    i++;
    if (*p == '/' || *p == '\\')
    {
      pos = i;
    }
    p++;
  }
  return path + pos;
}

#define ARDUHAL_LOG_FORMAT(letter, format) "[" #letter "][%s:%u] %s(): " format "\r\n", pathToFileName(__FILE__), __LINE__, __FUNCTION__

#ifdef DEBUG_ESP_PORT
#define log_printf(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)
// #define log_printf(format, ...) DEBUG_ESP_PORT.printf(format, __VA_ARGS__)
#endif

#if ARDUHAL_LOG_LEVEL >= ARDUHAL_LOG_LEVEL_VERBOSE
#define log_v(format, ...) log_printf(ARDUHAL_LOG_FORMAT(V, format), ##__VA_ARGS__)
#else
#define log_v(format, ...)
#endif

#if ARDUHAL_LOG_LEVEL >= ARDUHAL_LOG_LEVEL_DEBUG
#define log_d(format, ...) log_printf(ARDUHAL_LOG_FORMAT(D, format), ##__VA_ARGS__)
#else
#define log_d(format, ...)
#endif

#if ARDUHAL_LOG_LEVEL >= ARDUHAL_LOG_LEVEL_INFO
#define log_i(format, ...) log_printf(ARDUHAL_LOG_FORMAT(I, format), ##__VA_ARGS__)
#else
#define log_i(format, ...)
#endif

#if ARDUHAL_LOG_LEVEL >= ARDUHAL_LOG_LEVEL_WARN
#define log_w(format, ...) log_printf(ARDUHAL_LOG_FORMAT(W, format), ##__VA_ARGS__)
#else
#define log_w(format, ...)
#endif

#if ARDUHAL_LOG_LEVEL >= ARDUHAL_LOG_LEVEL_ERROR
#define log_e(format, ...) log_printf(ARDUHAL_LOG_FORMAT(E, format), ##__VA_ARGS__)
#else
#define log_e(format, ...)
#endif

#if ARDUHAL_LOG_LEVEL >= ARDUHAL_LOG_LEVEL_NONE
#define log_n(format, ...) log_printf(ARDUHAL_LOG_FORMAT(E, format), ##__VA_ARGS__)
#else
#define log_n(format, ...)
#endif






#ifdef __cplusplus
}
#endif

#endif /* __ESP_LOGGING_H__ */
