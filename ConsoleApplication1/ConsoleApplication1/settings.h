#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    void DrawSettingsScreen(void);

    typedef struct {
        uint8_t index;       // offset
        uint8_t next;
        uint8_t x;           // x position
        uint8_t y;           // y position
        uint8_t min;         // minimum value
        uint8_t max;         // maximum value
        uint8_t digit;       // current value
        void (*fn)(void);  // enter function
    } digit_t;

    typedef enum
    {
        SWOFF_30 = 1,
        SWOFF_60 = 2,
        SWOFF_90 = 3,
        SWOFF_120 = 4,
        SWOFF_150 = 5,
        SWOFF_180 = 6,
        SWOFF_210 = 7,
        SWOFF_240 = 8,
        SWOFF_270 = 9,
        SWOFF_300 = 10
    } swoff_t;

    typedef struct
    {
        uint8_t Time;     // time in seconds for the phase
        uint8_t PumpPWM;  // pump rate in percentage
        uint8_t Divert;   // Solenoid divert 0-1
    } /*__attribute__((packed))*/ phase_t;

    typedef struct
    {
        uint8_t SamplesPerSec;
        uint8_t Iterations;
        uint8_t BacklightPWM;
        uint8_t SwitchOffSec;
    } /*__attribute__((packed))*/ base_params_t;

    // Structure definition for parameters held in  the RTC backup registers
    typedef struct {
        base_params_t Base;
        phase_t  Baseline;
        phase_t  Absorb;
        phase_t  Pause;
        phase_t  Desorb;
        phase_t  Flush;
        phase_t  Wait;
        uint8_t Unused1;
        uint8_t Unused2;
        uint32_t  T1;
        uint32_t  T2;
        uint32_t  T3;
        uint32_t  T4;
        uint32_t  T5;
        uint32_t  T6;
        uint32_t  T7;
        uint8_t  StartHour;
        uint8_t  StartMinute;
        uint8_t  RepeatCount;
        uint8_t Unused;
        char     Name[20];
        uint32_t ForceBootstrap;  // RTC_BKP16R, force the bootstrap to run if set to FEEDCODE
        uint32_t LoggingEnabled;
        uint32_t Timestamp;
        uint32_t crc;
    } /*__attribute__((packed))*/ Params_t;

    typedef struct
    {
        uint32_t T1; //factor for convert to ms
        uint32_t T2;
        uint32_t T3;
        uint32_t T4;
        uint32_t T5;
        uint32_t T6;
        uint32_t T7;
    } ParamsFormat_t;






    // returns pointer to the backup registers
    Params_t* GetParamsPtr(void);
    void SetParamsTimeStamp(Params_t* Params);
    uint8_t GetBrightness(void);
    uint16_t GetSwitchOffSeconds(void);
    void ValidateParams(void);


    // for finding the size of a structure member
#define member_size(type, member) sizeof(((type *)0)->member)

#define size_and_pos( t, m) member_size(t, m), offsetof(t, m)

#ifdef __cplusplus
}
#endif

#endif //_SETTINGS_H_
