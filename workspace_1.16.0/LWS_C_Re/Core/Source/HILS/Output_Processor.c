/*
 * File: Output_Processor.c
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

#include "Output_Processor.h"

/* Include model header file for global data */
#include "Lws_HilsCtrl_240218_v_1_0.h"
#include "Lws_HilsCtrl_240218_v_1_0_private.h"

/* Output and update for atomic system: 'HilsOutput_Processor' (':5024') */
void Output_Processor(void)
{
  int32_T bitIdx;
  int32_T j;
  uint32_T bitMask;
  uint32_T intVal;
  uint16_T rtb_TmpSignalConversionAtBitt_i[16];
  uint16_T rtb_TmpSignalConversionAtBitt_j[16];
  uint16_T rtb_TmpSignalConversionAtBittoI[16];

  /* SignalConversion generated from: 'Bit to Integer Converter3' (':5028') incorporates:
   *  DataStoreRead: 'Data Store Read10' (':5033')
   */
  rtb_TmpSignalConversionAtBittoI[0] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning;
  rtb_TmpSignalConversionAtBittoI[1] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.Power_On;
  rtb_TmpSignalConversionAtBittoI[2] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WinchPower_On;
  rtb_TmpSignalConversionAtBittoI[3] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BoostPower_On;
  rtb_TmpSignalConversionAtBittoI[4] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.DlPower_On;
  rtb_TmpSignalConversionAtBittoI[5] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock;
  rtb_TmpSignalConversionAtBittoI[6] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock;
  rtb_TmpSignalConversionAtBittoI[7] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock;
  rtb_TmpSignalConversionAtBittoI[8] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Algin;
  rtb_TmpSignalConversionAtBittoI[9] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Emg;
  rtb_TmpSignalConversionAtBittoI[10] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC01;
  rtb_TmpSignalConversionAtBittoI[11] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC02;
  rtb_TmpSignalConversionAtBittoI[12] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC01;
  rtb_TmpSignalConversionAtBittoI[13] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC02;
  rtb_TmpSignalConversionAtBittoI[14] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.a14;
  rtb_TmpSignalConversionAtBittoI[15] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.a15;

  /* SignalConversion generated from: 'Bit to Integer Converter5' (':5030') incorporates:
   *  DataStoreRead: 'Data Store Read7' (':5041')
   */
  rtb_TmpSignalConversionAtBitt_j[0] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a;
  rtb_TmpSignalConversionAtBitt_j[1] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a1;
  rtb_TmpSignalConversionAtBitt_j[2] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a2;
  rtb_TmpSignalConversionAtBitt_j[3] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a3;
  rtb_TmpSignalConversionAtBitt_j[4] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a4;
  rtb_TmpSignalConversionAtBitt_j[5] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a5;
  rtb_TmpSignalConversionAtBitt_j[6] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a6;
  rtb_TmpSignalConversionAtBitt_j[7] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a7;
  rtb_TmpSignalConversionAtBitt_j[8] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a8;
  rtb_TmpSignalConversionAtBitt_j[9] = Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a9;
  rtb_TmpSignalConversionAtBitt_j[10] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a10;
  rtb_TmpSignalConversionAtBitt_j[11] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a11;
  rtb_TmpSignalConversionAtBitt_j[12] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a12;
  rtb_TmpSignalConversionAtBitt_j[13] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a13;
  rtb_TmpSignalConversionAtBitt_j[14] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a14;
  rtb_TmpSignalConversionAtBitt_j[15] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsError.a15;

  /* SignalConversion generated from: 'Bit to Integer Converter1' (':5026') incorporates:
   *  DataStoreRead: 'Data Store Read4' (':5038')
   */
  rtb_TmpSignalConversionAtBitt_i[0] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a;
  rtb_TmpSignalConversionAtBitt_i[1] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a1;
  rtb_TmpSignalConversionAtBitt_i[2] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a2;
  rtb_TmpSignalConversionAtBitt_i[3] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a3;
  rtb_TmpSignalConversionAtBitt_i[4] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a4;
  rtb_TmpSignalConversionAtBitt_i[5] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a5;
  rtb_TmpSignalConversionAtBitt_i[6] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a6;
  rtb_TmpSignalConversionAtBitt_i[7] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a7;
  rtb_TmpSignalConversionAtBitt_i[8] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a8;
  rtb_TmpSignalConversionAtBitt_i[9] = Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a9;
  rtb_TmpSignalConversionAtBitt_i[10] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a10;
  rtb_TmpSignalConversionAtBitt_i[11] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a11;
  rtb_TmpSignalConversionAtBitt_i[12] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a12;
  rtb_TmpSignalConversionAtBitt_i[13] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a13;
  rtb_TmpSignalConversionAtBitt_i[14] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a14;
  rtb_TmpSignalConversionAtBitt_i[15] =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAlarm.a15;

  /* S-Function (scominttobit): 'Bit to Integer Converter3' (':5028') */
  /* Bit to Integer Conversion */
  bitIdx = 0;
  intVal = 0U;
  bitMask = 1U;
  for (j = 0; j < 16; j++)
  {
    /* Input bit order is LSB first */
    if (((uint32_T)rtb_TmpSignalConversionAtBittoI[bitIdx]) != 0U)
    {
      intVal |= bitMask;
    }

    bitIdx++;
    bitMask <<= 1ULL;
  }

  /* Outport: 'LwsWtuA_HilsStatus' (':1446') incorporates:
   *  S-Function (scominttobit): 'Bit to Integer Converter3' (':5028')
   */
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsStatus = (uint16_T)intVal;

  /* S-Function (scominttobit): 'Bit to Integer Converter5' (':5030') */
  /* Bit to Integer Conversion */
  bitIdx = 0;
  intVal = 0U;
  bitMask = 1U;
  for (j = 0; j < 16; j++)
  {
    /* Input bit order is LSB first */
    if (((uint32_T)rtb_TmpSignalConversionAtBitt_j[bitIdx]) != 0U)
    {
      intVal |= bitMask;
    }

    bitIdx++;
    bitMask <<= 1ULL;
  }

  /* Outport: 'LwsWtuA_HilsError' (':1448') incorporates:
   *  S-Function (scominttobit): 'Bit to Integer Converter5' (':5030')
   */
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsError = (uint16_T)intVal;

  /* S-Function (scominttobit): 'Bit to Integer Converter1' (':5026') */
  /* Bit to Integer Conversion */
  bitIdx = 0;
  intVal = 0U;
  bitMask = 1U;
  for (j = 0; j < 16; j++)
  {
    /* Input bit order is LSB first */
    if (((uint32_T)rtb_TmpSignalConversionAtBitt_i[bitIdx]) != 0U)
    {
      intVal |= bitMask;
    }

    bitIdx++;
    bitMask <<= 1ULL;
  }

  /* Outport: 'LwsWtuA_HilsAlarm' (':2921') incorporates:
   *  S-Function (scominttobit): 'Bit to Integer Converter1' (':5026')
   */
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsAlarm = (uint16_T)intVal;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o1 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_Boost;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o2 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_DropLift;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o3 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_PreOver;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o4 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_Wind;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o5 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_Unwind;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o6 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignDrv;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o7 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_Return;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o8 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_BoostPump;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o9 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_WinchDrv;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o10 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_DropLift;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o11 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightA;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o12 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightB;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o13 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftA;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o14 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftB;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o15 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FiveTurn_Switch;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o16 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignBk;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o17 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_MainBk;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o18 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_SubBk;

  /* DataStoreRead: 'Data Store Read1' (':5032') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead1_o19 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PValveError_WinchPw;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o1 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.Pressure_WinchPw;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o2 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.Pressure_DropLiftPw;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o3 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.OilFlow_DropLift;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o4 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.PValveError_EmgDrv;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o5 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.WinchDrum_Angle;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o6 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.Align_Angle;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o7 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.PValveError_AlignDrv;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o8 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.DrumMotorA_Velocity;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o9 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.DrumMotorB_Velocity;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o10 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.AlignMotor_Velocity;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o11 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.TensionSensor;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o12 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_ExpPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o13 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_ConPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o14 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_LVDT;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o15 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_PValveError;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o16 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_ExpPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o17 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_ConPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o18 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_LVDT;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o19 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_PValveError;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o20 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_ExpPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o21 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_ConPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o22 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_LVDT;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o23 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_PValveError;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o24 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_ExpPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o25 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_ConPressure;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o26 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_LVDT;

  /* DataStoreRead: 'Data Store Read2' (':5036') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead2_o27 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_PValveError;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o1 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.WinchDrun_Angle;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o2 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.WinchDrum_Vel;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o3 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.Align_Angle;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o4 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.Align_Vel;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o5 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy01_Pos;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o6 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy01_Vel;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o7 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy02_Pos;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o8 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy02_Vel;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o9 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy01_Pos;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o10 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy01_Vel;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o11 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy02_Pos;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o12 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy02_Vel;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o13 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.Spare01;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o14 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.Spare02;

  /* DataStoreRead: 'Data Store Read8' (':5042') */
  Lws_HilsCtrl_240218_v_1_0_B.DataStoreRead8_o15 =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.Spare03;

  /* Outport: 'LwsWtuA_HilsMode' (':1445') incorporates:
   *  DataStoreRead: 'Data Store Read3' (':5037')
   */
  Lws_HilsCtrl_240218_v_1_0_Y.LwsWtuA_HilsMode =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
