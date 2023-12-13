#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>


#define PRINT_TYPE(x) _Generic((x) \
    ,char*: EVT_string \
    ,uint8_t: EVT_uint8 \
)

typedef enum {EVT_string, EVT_uint8, EVT_NumOfEl} E_VariableType;

typedef struct
{
  const char *string;
  //void (*func)(struct ParameterInput_t *ParametrData,const char* buff, bool * settings_changed);
  void (*func)(void* ParametrData, const char* buff, bool* settings_changed);
  const char *format;
  void* parameter;
  E_VariableType ParameterType;
} ParameterInput_t;

#ifdef __cplusplus
extern "C" {
#endif

void mainParameterInputA(const char* buff, bool * settings_changed);


#ifdef __cplusplus
}
#endif

#endif /* PARSING_H_INCLUDED */
