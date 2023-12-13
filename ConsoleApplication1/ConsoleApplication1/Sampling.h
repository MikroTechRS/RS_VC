/**
 * @file Sampling.h
 * @author Marc Sandusky (marc_sandusky@outlook.com)
 * @brief Sampling operation support
 * @version 0.1
 * @date 2021-12-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef INC_SAMPLING_H_
#define INC_SAMPLING_H_

//#include <peripherals.h>
//#include <fonts.h>
#include "settings.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern Params_t Params;

	void SettingsHaveChanged(void);
	void SettingsHaventChanged(void);
	void StartSamplingOnTimer(void);


#ifdef __cplusplus
}
#endif

#endif  // INC_SAMPLING_H_
