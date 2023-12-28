#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>


#define PRINT_TYPE(x) _Generic((x) \
    ,char*: EVT_string \
    ,uint8_t: EVT_Uint8 \
    ,uint32_t:EVT_Uint32 \
    ,phase_t:EVT_Phase\
)

typedef enum {EVT_string, EVT_Uint8,EVT_Uint32,EVT_Phase ,EVT_NumOfEl } E_VariableType;

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

    
bool CmpString(char* str, char* cmp);
int strncmpi(const char* s1, const char* s2, size_t n);
void mainParameterInputA(const char* buff, bool * settings_changed);


#ifdef __cplusplus
}
#endif

#endif /* PARSING_H_INCLUDED */
