/*
 * File: Input_Processor.c
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

#include "Input_Processor.h"

/* Include model header file for global data */
#include "Lws_HilsCtrl_240218_v_1_0.h"
#include "Lws_HilsCtrl_240218_v_1_0_private.h"

/* Output and update for atomic system: 'HilsInput_Processor' (':4741') */
void Input_Processor(void)
{
  real32_T denAccum;

  /* S-Function (sdspbiquad): 'Digital Filter' (':5362:26') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  denAccum = ((0.000241359056F * Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[0])
              - (-1.95557821F *
                 Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES[0])) -
    (0.956543684F * Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES[1]);

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  S-Function (sdspbiquad): 'Digital Filter' (':5362:26')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_EmgDrv = (denAccum + (2.0F *
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES[0])) +
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES[1];

  /* S-Function (sdspbiquad): 'Digital Filter' (':5362:26') */
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES[0];
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES[0] = denAccum;

  /* S-Function (sdspbiquad): 'Digital Filter' (':5421:26') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  denAccum = ((0.000241359056F * Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[1])
              - (-1.95557821F *
                 Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_o[0])) -
    (0.956543684F * Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_o[1]);

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  S-Function (sdspbiquad): 'Digital Filter' (':5421:26')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_DrumDrv = (denAccum + (2.0F *
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_o[0])) +
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_o[1];

  /* S-Function (sdspbiquad): 'Digital Filter' (':5421:26') */
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_o[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_o[0];
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_o[0] = denAccum;

  /* S-Function (sdspbiquad): 'Digital Filter' (':5426:26') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  denAccum = ((0.000241359056F * Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[2])
              - (-1.95557821F *
                 Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_g[0])) -
    (0.956543684F * Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_g[1]);

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  S-Function (sdspbiquad): 'Digital Filter' (':5426:26')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_AlignDrv = (denAccum + (2.0F *
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_g[0])) +
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_g[1];

  /* S-Function (sdspbiquad): 'Digital Filter' (':5426:26') */
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_g[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_g[0];
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_g[0] = denAccum;

  /* S-Function (sdspbiquad): 'Digital Filter' (':5431:26') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  denAccum = ((0.000241359056F * Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[3])
              - (-1.95557821F *
                 Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_a[0])) -
    (0.956543684F * Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_a[1]);

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  S-Function (sdspbiquad): 'Digital Filter' (':5431:26')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_MainCy01Drv = (denAccum + (2.0F *
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_a[0])) +
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_a[1];

  /* S-Function (sdspbiquad): 'Digital Filter' (':5431:26') */
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_a[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_a[0];
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_a[0] = denAccum;

  /* S-Function (sdspbiquad): 'Digital Filter' (':5436:26') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  denAccum = ((0.000241359056F * Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[4])
              - (-1.95557821F *
                 Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_c[0])) -
    (0.956543684F * Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_c[1]);

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  S-Function (sdspbiquad): 'Digital Filter' (':5436:26')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_MainCy02Drv = (denAccum + (2.0F *
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_c[0])) +
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_c[1];

  /* S-Function (sdspbiquad): 'Digital Filter' (':5436:26') */
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_c[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_c[0];
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_c[0] = denAccum;

  /* S-Function (sdspbiquad): 'Digital Filter' (':5441:26') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  denAccum = ((0.000241359056F * Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[5])
              - (-1.95557821F *
                 Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_h[0])) -
    (0.956543684F * Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_h[1]);

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  S-Function (sdspbiquad): 'Digital Filter' (':5441:26')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_SubCy01Drv = (denAccum + (2.0F *
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_h[0])) +
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_h[1];

  /* S-Function (sdspbiquad): 'Digital Filter' (':5441:26') */
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_h[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_h[0];
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_h[0] = denAccum;

  /* S-Function (sdspbiquad): 'Digital Filter' (':5446:26') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  denAccum = ((0.000241359056F * Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[6])
              - (-1.95557821F *
                 Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_m[0])) -
    (0.956543684F * Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_m[1]);

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  S-Function (sdspbiquad): 'Digital Filter' (':5446:26')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_SubCy02Drv = (denAccum + (2.0F *
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_m[0])) +
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_m[1];

  /* S-Function (sdspbiquad): 'Digital Filter' (':5446:26') */
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_m[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_m[0];
  Lws_HilsCtrl_240218_v_1_0_DW.DigitalFilter_FILT_STATES_m[0] = denAccum;

  /* DataStoreWrite: 'Data Store Write1' (':4764') incorporates:
   *  Inport: 'LwsWtuA_HilsAI' (':3999')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.Spare =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsAI[7];

  /* DataStoreWrite: 'Data Store Write2' (':4765') incorporates:
   *  Inport: 'LwsWtuA_HilsDI' (':4')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_Winch =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[0];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_DropLift =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[1];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.CutValve_Winch =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[2];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.DirValve_AlignBk =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[3];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.DirValve_MainBk =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[4];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.DirValve_SubBk =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[5];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.Spare01 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[6];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.Spare02 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsDI[7];

  /* DataStoreWrite: 'Data Store Write3' (':4766') incorporates:
   *  Inport: 'LwsWtuA_HilsCmd' (':20')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsMode_Start =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsCmd[0];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsMode_Stop =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsCmd[1];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsOutSet_Change =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsCmd[2];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.Spare =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsCmd[3];

  /* DataStoreWrite: 'Data Store Write4' (':4767') incorporates:
   *  Inport: 'LwsWtuA_HilsOutSet' (':21')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_Return =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[0];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_BoostPump =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[1];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_WinchDrv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[2];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_DropLift =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[3];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_RightA =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[4];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_RightB =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[5];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_LeftA =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[6];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_LeftB =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[7];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.FiveTurnSwitch =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[8];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_WinchDrv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[9];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_AlignDrv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[10];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_EmgDrv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[11];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_MainCy01Drv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[12];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_MainCy02Drv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[13];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_SubCy01Drv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[14];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_SubCy02Drv =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[15];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.OverPressure =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[16];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Spare =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWtuA_HilsOutSet[17];

  /* DataStoreWrite: 'Data Store Write6' (':4769') incorporates:
   *  Inport: 'LwsWutA_HilsPara' (':11')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Winch_InitAngle =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[0];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Align_InitAngle =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[1];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainCy01_InitPos =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[2];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainCy02_InitPos =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[3];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubCy01_InitPos =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[4];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubCy02_InitPos =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[5];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.WinchPw_RefPressure =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[6];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.DropLiftPw_RefPressure =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[7];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.OilFlowS_RefFlow =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[8];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.TensionS_RefTension =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[9];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainSy_ExpRefPressure =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[10];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainSy_ConRefPressure =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[11];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubSy_ExpRefPressure =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[12];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubSy_ConRefPressure =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[13];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare01 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[14];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare02 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[15];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare03 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[16];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare04 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[17];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare05 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[18];
  Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare06 =
    Lws_HilsCtrl_240218_v_1_0_U.LwsWutA_HilsPara[19];
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
