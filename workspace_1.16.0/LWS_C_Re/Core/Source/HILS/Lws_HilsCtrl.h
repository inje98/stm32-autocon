/*
 * File: Lws_HilsCtrl.h
 *
 * Code generated for Simulink model 'Lws_HilsCtrl_240218_v_1_0'.
 *
 * Model version                  : 1.0.9
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Mon Jun 17 14:47:57 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Lws_HilsCtrl_h_
#define RTW_HEADER_Lws_HilsCtrl_h_
#ifndef Lws_HilsCtrl_240218_v_1_0_COMMON_INCLUDES_
#define Lws_HilsCtrl_240218_v_1_0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                          /* Lws_HilsCtrl_240218_v_1_0_COMMON_INCLUDES_ */

#include "Lws_HilsCtrl_240218_v_1_0_types.h"

/* Child system includes */
#include "Hils_Ctrl_Block.h"
#include "Hils_SequenceCtrl.h"
#include "Input_Processor.h"
#include "Output_Processor.h"

extern void Lws_HilsCtrl_Init(void);
extern void Lws_HilsCtrl(void);

#endif                                 /* RTW_HEADER_Lws_HilsCtrl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
