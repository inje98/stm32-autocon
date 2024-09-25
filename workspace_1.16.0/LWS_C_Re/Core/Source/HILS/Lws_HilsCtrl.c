/*
 * File: Lws_HilsCtrl.c
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

#include "Lws_HilsCtrl.h"

/* Include model header file for global data */
#include "Lws_HilsCtrl_240218_v_1_0.h"
#include "Lws_HilsCtrl_240218_v_1_0_private.h"

/* System initialize for atomic system: 'Lws_HilsCtrl' (':4548') */
void Lws_HilsCtrl_Init(void)
{
  /* SystemInitialize for Chart: 'Hils_SequenceCtrl' (':5237') */
  Hils_SequenceCtrl_Init();

  /* SystemInitialize for Atomic SubSystem: 'Hils_Ctrl_Block' (':5129') */
  Hils_Ctrl_Block_Init();

  /* End of SystemInitialize for SubSystem: 'Hils_Ctrl_Block' (':5129') */
}

/* Output and update for atomic system: 'Lws_HilsCtrl' (':4548') */
void Lws_HilsCtrl(void)
{
  /* Outputs for Atomic SubSystem: 'HilsOutput_Processor' (':5024') */
  Output_Processor();

  /* End of Outputs for SubSystem: 'HilsOutput_Processor' (':5024') */

  /* Outputs for Atomic SubSystem: 'HilsInput_Processor' (':4741') */
  Input_Processor();

  /* End of Outputs for SubSystem: 'HilsInput_Processor' (':4741') */

  /* Chart: 'Hils_SequenceCtrl' (':5237') */
  Hils_SequenceCtrl();

  /* Outputs for Atomic SubSystem: 'Hils_Ctrl_Block' (':5129') */
  Hils_Ctrl_Block();

  /* End of Outputs for SubSystem: 'Hils_Ctrl_Block' (':5129') */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
