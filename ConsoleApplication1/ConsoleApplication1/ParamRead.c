//#include <iostream>
#pragma warning(disable : 4996)

#include <stddef.h>
#include "ParamRead.h"



Params_t Params;

static phase_t Baseline;
static phase_t Absorb;
static phase_t Pause;
static phase_t Desorb;
static phase_t Flush;
static phase_t Wait;

#define COMMS_BUFSIZE 1024

static char buff[COMMS_BUFSIZE];
static char ExperimentName[80] = "Anon";
static bool settings_changed = false;
#define SOLENOID_OFF 0
#define SOLENOID_ON 1

static bool ReadLn(FILE* fp, char* buff, int len) {
    if (fgets(buff, len, fp) == 0)
        return false;
    int end = strlen(buff) - 1;
    // now remove end of line
    if (buff[end] == '\n')
        buff[end] = '\0';
    // remove anything after //
    char* pos;
    pos = strstr(buff, "//");
 
    if ((pos) != NULL) {
        pos = (((uint64_t)buff) & 0xffffffff00000000) + (((uint64_t)pos) & 0xffffffff);
        *pos = '\0';
        //buff[pos - buff] = '\0';
    }
    return true;
}

//int strncmpi(const char* s1, const char* s2, size_t n)
//{
//    while (n && *s1 && (toupper(*s1) == toupper(*s2)))
//    {
//        ++s1;
//        ++s2;
//        --n;
//    }
//    if (n == 0)
//    {
//        return 0;
//    }
//    else
//    {
//        return (toupper(*(unsigned char*)s1) - toupper(*(unsigned char*)s2));
//    }
//}


//bool CmpString(const char* str, const char* cmp) {
//    return  strncmpi(str, cmp, strlen(cmp)) == 0;
//}

//void Log(const char* fmt, ...)
//{
// //   if (!GetParamsPtr()->LoggingEnabled)
// //       return;
//    va_list args;
//
//    /* Assemble the output string */
//    va_start(args, fmt);
//    vsprintf(TempBuffer, fmt, args);
//    va_end(args);
//
//    FIL MyFile;
//    FIL* fp = &MyFile;
//    if (f_open(fp, (TCHAR const*)"\\log.txt", FA_OPEN_ALWAYS | FA_WRITE) == FR_OK)
//    {
//        // seek to end of file
//        f_lseek(fp, f_size(&MyFile));
//    }
//    RTC_TimeTypeDef Time;
//    RTC_DateTypeDef Date;
//    char buff[80];
//    GetDateAndTime(&Date, &Time);
//    sprintf(buff, "%2d %s %2d %02u:%02u:%02u ",
//        Date.Date, months[Date.Month], Date.Year,
//        Time.Hours, Time.Minutes, Time.Seconds);
//    f_printf(fp, "%s%s\n", buff, TempBuffer);
//    printf("%s%s\n", buff, TempBuffer);
//    f_close(fp);
//}

bool GetPhase(char* buff, phase_t* phase) {
    phase_t phasevars;
    uint32_t phasetime;
    uint32_t phasepumppwm;
    char divert[80];

    if (sscanf(buff, "%u,%u,%s", &phasetime, &phasepumppwm, divert) != 3)
        return false;

    phasevars.Time = (uint8_t)phasetime;
    phasevars.PumpPWM = (uint8_t)phasepumppwm;
    if (CmpString(divert, "off"))
        phasevars.Divert = SOLENOID_OFF;
    else if (CmpString(divert, "on"))
        phasevars.Divert = SOLENOID_ON;
    else
        return false;

    *phase = phasevars;

    return true;
}

static bool PhaseChanged(phase_t* tgt, phase_t* src) {
    return (tgt->Time != src->Time)
        | (tgt->PumpPWM != src->PumpPWM)
        | (tgt->Divert != src->Divert);
}

typedef enum { fp_name, fp_uint8_t, E_fp_maxEl } E_fp;

typedef struct
{
    char ParametrName[10];
    void* ParametrPointer;
    E_fp functiontype;
} s_ParametrParsingData;

//#define PRINT_TYPE(x) _Generic((x), \
//    int: printf("Variable is of type int\n"), \
//    float: printf("Variable is of type float\n"), \
//    double: printf("Variable is of type double\n"), \
//    char: printf("Variable is of type char\n"), \
//    default: printf("Variable is of an unknown type\n") \
//)
//
//#define D_PPF(x) _Generic((x), \
//uint8_t: ParametrParsing_uint8_t ,\
//uint32_t: ParametrParsing_uint32_t \
//)
//
//void ParametrParsing_uint32_t(void* PPD) {};
//void ParametrParsing_uint8_t(void* PPD) {};
//void ParametrParsing_name(void* PPD) {};


void UpdateParamsFromFile(Params_t* Params, FILE* fp_h) {
    while (!feof(fp_h)) {
        if (ReadLn(fp_h, buff, sizeof(buff))) {
            mainParameterInputA(buff, &settings_changed);//(const char* buff, bool* settings_changed)
            //if (CmpString(buff, "name:")) {
            //    strcpy(ExperimentName, &buff[5]);
            //    ExperimentName[19] = '\0';  // Truncate to 20 chars
            //    // remove trailing zeroes
            //    for (int i = (strlen(ExperimentName) - 1); i > 0; i--) {
            //        if (ExperimentName[i] != ' ')
            //            break;
            //        ExperimentName[i] = '\0';
            //    }
            //    if (strcmp((const char*)&Params->Name, ExperimentName) != 0) {
            //        //                   Log("name changed from \"%s\" to \"%s\"", Params->Name, ExperimentName);
            //                           // backup RAM for name limited to 19 characters
            //        for (int i = 0; i < 19; i++) {
            //            Params->Name[i] = ExperimentName[i];
            //        }
            //        Params->Name[19] = '\0';
            //        settings_changed = true;
            //    }
            //}
            //else
            //    if (CmpString(buff, "repeat:")) {
            //    int temp = 0;
            //    int n = sscanf(&buff[7], "%d", &temp);
            //    //        printf("n=%d\n", n);
            //    if ((n == 1) && (temp != 0)) {
            //        if (Params->Base.Iterations != temp) {
            //            //                       Log("repeats changed from %d to %d", Params->Base.Iterations, temp);
            //            Params->Base.Iterations = temp;
            //            settings_changed = true;
            //        }
            //    }
            //}
            //else 
             if (CmpString(buff, "baseline:")) {
                if (GetPhase(&buff[9], &Baseline)) {
                    if (PhaseChanged(&Params->Baseline, &Baseline)) {
                        Params->Baseline = Baseline;
                        //                       Log("Baseline changed to \"%s\"", &buff[9]);
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "absorb:")) {
                if (GetPhase(&buff[7], &Absorb)) {
                    if (PhaseChanged(&Params->Absorb, &Absorb)) {
                        Params->Absorb = Absorb;
                        //                       Log("Absorb changed to \"%s\"", &buff[7]);
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "pause:")) {
                if (GetPhase(&buff[6], &Pause)) {
                    if (PhaseChanged(&Params->Pause, &Pause)) {
                        Params->Pause = Pause;
                        //                       Log("Pause changed to \"%s\"", &buff[6]);
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "desorb:")) {
                if (GetPhase(&buff[7], &Desorb)) {
                    if (PhaseChanged(&Params->Desorb, &Desorb)) {
                        Params->Desorb = Desorb;
                        //                       Log("Desorb changed to \"%s\"", &buff[7]);
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "flush:")) {
                if (GetPhase(&buff[6], &Flush)) {
                    if (PhaseChanged(&Params->Flush, &Flush)) {
                        Params->Flush = Flush;
                        //                        Log("Flush changed to \"%s\"", &buff[6]);
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "wait:")) {
                if (GetPhase(&buff[5], &Wait)) {
                    if (PhaseChanged(&Params->Wait, &Wait)) {
                        Params->Wait = Wait;
                        //                      Log("Wait changed to \"%s\"", &buff[5]);
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "switchoffsec:")) {
                int temp;
                if (sscanf(&buff[13], "%d", &temp) == 1) {
                    if (Params->Base.SwitchOffSec != temp) {
                        //                       Log("switch off seconds changed from %d to %d", Params->Base.SwitchOffSec, temp);
                        Params->Base.SwitchOffSec = temp;
                        settings_changed = true;
                    }
                }
            }
        /*    else if (CmpString(buff, "T1:")) {
                int temp;
                if (sscanf(&buff[3], "%d", &temp) == 1) {
                    if (Params->T1 != temp) {
                        //                       Log("T1 changed from %d to %d", Params->T1, temp);
                        Params->T1 = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "T2:")) {
                int temp;
                if (sscanf(&buff[3], "%d", &temp) == 1) {
                    if (Params->T2 != temp) {
                        //                       Log("T2 changed from %d to %d", Params->T2, temp);
                        Params->T2 = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "T3:")) {
                int temp;
                if (sscanf(&buff[3], "%d", &temp) == 1) {
                    if (Params->T3 != temp) {
                        //                       Log("T3 changed from %d to %d", Params->T3, temp);
                        Params->T3 = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "T4:")) {
                int temp;
                if (sscanf(&buff[3], "%d", &temp) == 1) {
                    if (Params->T4 != temp) {
                        //                       Log("T4 changed from %d to %d", Params->T4, temp);
                        Params->T4 = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "T5:")) {
                int temp;
                if (sscanf(&buff[3], "%d", &temp) == 1) {
                    if (Params->T5 != temp) {
                        //                       Log("T5 changed from %d to %d", Params->T5, temp);
                        Params->T5 = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "T6:")) {
                int temp;
                if (sscanf(&buff[3], "%d", &temp) == 1) {
                    if (Params->T6 != temp) {
                        //                       Log("T6 changed from %d to %d", Params->T6, temp);
                        Params->T6 = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "T7:")) {
                int temp;
                if (sscanf(&buff[3], "%d", &temp) == 1) {
                    if (Params->T7 != temp) {
                        //                       Log("T7 changed from %d to %d", Params->T7, temp);
                        Params->T7 = temp;
                        settings_changed = true;
                    }
                }
            }*/
            else if (CmpString(buff, "StartHour:")) {
                int temp;
                if (sscanf(&buff[strlen("StartHour:")], "%d", &temp) == 1) {
                    if (Params->StartHour != temp) {
                        //                       Log("StartHour changed from %d to %d", Params->StartHour, temp);
                        Params->StartHour = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "StartMinute:")) {
                int temp;
                if (sscanf(&buff[strlen("StartMinute:")], "%d", &temp) == 1) {
                    if (Params->StartMinute != temp) {
                        //                      Log("StartMinute changed from %d to %d", Params->StartMinute, temp);
                        Params->StartMinute = temp;
                        settings_changed = true;
                    }
                }
            }
            else if (CmpString(buff, "RepeatCount:")) {
                int temp;
                if (sscanf(&buff[strlen("RepeatCount:")], "%d", &temp) == 1) {
                    if (Params->RepeatCount != temp) {
                        //                      Log("StartMinute changed from %d to %d", Params->RepeatCount, temp);
                        Params->RepeatCount = temp;
                        settings_changed = true;
                    }
                }
            } //TODO RDD Are all parameters processing?
        }
    }
}
