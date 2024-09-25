/*
 * File: Lws_HilsCtrl_240218_v_1_0.c
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

#include "Lws_HilsCtrl_240218_v_1_0.h"
#include "Lws_HilsCtrl_240218_v_1_0_private.h"

/* Block signals (default storage) */
B_Lws_HilsCtrl_240218_v_1_0_T Lws_HilsCtrl_240218_v_1_0_B;

/* Block states (default storage) */
DW_Lws_HilsCtrl_240218_v_1_0_T Lws_HilsCtrl_240218_v_1_0_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Lws_HilsCtrl_240218_v_1__T Lws_HilsCtrl_240218_v_1_0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Lws_HilsCtrl_240218_v_1__T Lws_HilsCtrl_240218_v_1_0_Y;

/* Model step function */
void Lws_HilsCtrl_240218_v_1_0_step(void)
{
  /* Outputs for Atomic SubSystem: 'Lws_HilsCtrl' (':4548') */
  Lws_HilsCtrl();

  /* End of Outputs for SubSystem: 'Lws_HilsCtrl' (':4548') */

  /* Outport: 'LwsWtuA_HilsAO' (':2900') */
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[0] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o1;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[1] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o2;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[2] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o3;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[3] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o4;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[4] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o5;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[5] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o6;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[6] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o7;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[7] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o8;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[8] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o9;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[9] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o10;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[10] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o11;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[11] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o12;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[12] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o13;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[13] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o14;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[14] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o15;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[15] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o16;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[16] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o17;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[17] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o18;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[18] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o19;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[19] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o20;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[20] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o21;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[21] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o22;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[22] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o23;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[23] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o24;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[24] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o25;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[25] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o26;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAO[26] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o27;

  /* Outport: 'LwsWtuA_HilsDO' (':1441') */
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[0] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o1;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[1] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o2;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[2] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o3;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[3] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o4;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[4] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o5;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[5] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o6;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[6] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o7;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[7] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o8;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[8] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o9;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[9] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o10;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[10] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o11;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[11] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o12;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[12] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o13;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[13] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o14;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[14] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o15;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[15] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o16;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[16] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o17;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[17] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o18;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsDO[18] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o19;

  /* Outport: 'LwsWtuA_HilsMon' (':2923') */
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[0] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o1;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[1] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o2;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[2] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o3;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[3] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o4;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[4] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o5;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[5] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o6;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[6] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o7;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[7] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o8;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[8] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o9;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[9] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o10;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[10] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o11;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[11] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o12;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[12] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o13;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[13] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o14;
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMon[14] =
    Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o15;
}

/* Model initialize function */
void Lws_HilsCtrl_240218_v_1_0_initialize(void)
{
  /* Registration code */

  /* block I/O */
  (void) memset(((void *) &Lws_HilsCtrl_240218_v_1_0_B), 0,
                sizeof(B_Lws_HilsCtrl_240218_v_1_0_T));

  /* states (dwork) */
  (void) memset((void *)&Lws_HilsCtrl_240218_v_1_0_DW, 0,
                sizeof(DW_Lws_HilsCtrl_240218_v_1_0_T));

  /* external inputs */
  (void)memset(&Lws_HilsCtrl_240218_v_1_0_U, 0, sizeof
               (ExtU_Lws_HilsCtrl_240218_v_1__T));

  /* external outputs */
  (void) memset((void *)&Lws_HilsCtrl_240218_v_1_0_Y, 0,
                sizeof(ExtY_Lws_HilsCtrl_240218_v_1__T));

  /* SystemInitialize for Atomic SubSystem: 'Lws_HilsCtrl' (':4548') */
  Lws_HilsCtrl_Init();

  /* End of SystemInitialize for SubSystem: 'Lws_HilsCtrl' (':4548') */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
