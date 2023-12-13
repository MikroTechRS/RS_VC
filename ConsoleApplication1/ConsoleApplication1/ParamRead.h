#ifndef _ParamRead_H_
#define _ParamRead_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
//#include <iostream>
#include <stdio.h>

#include "parsing.h"
#include "settings.h"

#ifdef __cplusplus
extern "C" {
#endif



	extern Params_t Params;

	void UpdateParamsFromFile(Params_t* Params, FILE* fp_h);

#ifdef __cplusplus
}
#endif

#endif