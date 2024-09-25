/*
 * File: Hils_Ctrl_Block.c
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

#include "Hils_Ctrl_Block.h"

/* Include model header file for global data */
#include "Lws_HilsCtrl_240218_v_1_0.h"
#include "Lws_HilsCtrl_240218_v_1_0_private.h"

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15)
  {
    if (u >= 0.5)
    {
      y = floor(u + 0.5);
    }
    else if (u > -0.5)
    {
      y = u * 0.0;
    }
    else
    {
      y = ceil(u - 0.5);
    }
  }
  else
  {
    y = u;
  }

  return y;
}

/* System initialize for atomic system: 'Hils_Ctrl_Block' (':5129') */
void Hils_Ctrl_Block_Init(void)
{
  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator2' (':6364') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_PrevRes = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_IC_LOAD = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6434') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevRes = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LOAD = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator' (':6780') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRese = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOADI = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6781') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_d = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_c = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator' (':6690') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_b = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_a = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6691') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_g = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_p = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator' (':6433') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_n = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_e = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6363') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_k = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_n = 1U;

  /* InitializeConditions for DiscreteIntegrator: 'Discrete-Time Integrator' (':6362') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_p = 0;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_n = 1U;
}

/* Output and update for atomic system: 'Hils_Ctrl_Block' (':5129') */
void Hils_Ctrl_Block(void)
{
  real_T Align_Load_Pos;
  real_T Gain3_f;
  real_T Gain3_o;
  real_T rtb_DiscreteTransferFcn;
  real_T rtb_DiscreteTransferFcn_a;
  real_T rtb_DiscreteTransferFcn_b;
  real_T rtb_DiscreteTransferFcn_f;
  real_T rtb_DiscreteTransferFcn_g;
  real_T rtb_DiscreteTransferFcn_i;
  real_T rtb_DiscreteTransferFcn_l;
  real_T rtb_DiscreteTransferFcn_o;
  real_T rtb_DiscreteTransferFcn_ps;
  real_T rtb_Gain10;
  real_T rtb_Gain10_b;
  real_T rtb_Gain11;
  real_T rtb_Gain11_l;
  real_T rtb_Gain21;
  real_T rtb_Gain2_m;
  real_T rtb_Gain8;
  real_T rtb_MultiportSwitch10;
  real_T rtb_MultiportSwitch11;
  real_T rtb_MultiportSwitch12;
  real_T rtb_MultiportSwitch13;
  real_T rtb_Prssure_Limit;
  real_T rtb_Prssure_Limit_a;
  real_T rtb_Prssure_Limit_l;
  real_T rtb_Prssure_Limit_mc;
  real_T rtb_Q_fedcm3s_a;
  real_T rtb_UnitConversion;
  real_T rtb_UnitConversion_a;
  real_T rtb_UnitConversion_k;
  real_T rtb_UnitConversion_tmp;
  real_T rtb_mm;
  real_T rtb_mm_e;
  real_T rtb_mm_jn;
  real_T rtb_mm_nv;
  boolean_T rtb_LogicalOperator;

  /* MultiPortSwitch: 'Multiport Switch' (':6261') incorporates:
   *  Constant: 'Constant' (':6262')
   *  DataStoreRead: 'Data Store Read3' (':6260')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  DataTypeConversion: 'Data Type Conversion7' (':6001')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Emg) == 0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.PValveError_EmgDrv =
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_EmgDrv;
  }
  else
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.PValveError_EmgDrv = 10.5F;
  }

  /* End of MultiPortSwitch: 'Multiport Switch' (':6261') */

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6389:2') */
  rtb_DiscreteTransferFcn = 5.5355024632436049E-7 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states;

  /* Logic: 'Logical Operator' (':6119') incorporates:
   *  DataStoreRead: 'Data Store Read2' (':6088')
   */
  rtb_LogicalOperator = (((int32_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning) == 0);

  /* UnitConversion: 'Unit Conversion' (':6357:16') incorporates:
   *  DataStoreRead: 'Data Store Read1' (':6085')
   *  DataTypeConversion: 'Data Type Conversion28' (':6153')
   *  UnitConversion: 'Unit Conversion' (':6358:16')
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_UnitConversion_tmp = 0.017453292519943295 * ((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Winch_InitAngle);

  /* DiscreteIntegrator: 'Discrete-Time Integrator2' (':6364') incorporates:
   *  UnitConversion: 'Unit Conversion' (':6357:16')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_IC_LOAD) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_DSTATE =
      rtb_UnitConversion_tmp;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_PrevRes != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_DSTATE =
      rtb_UnitConversion_tmp;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator2' (':6364') */
  rtb_UnitConversion =
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_DSTATE + (0.0025 *
    rtb_DiscreteTransferFcn);

  /* UnitConversion: 'Unit Conversion' (':6091:16') */
  /* Unit Conversion - from: rad to: deg
     Expression: output = (57.2958*input) + (0) */
  rtb_UnitConversion_k = 57.295779513082323 * rtb_UnitConversion;

  /* DataTypeConversion: 'Data Type Conversion9' (':6024') incorporates:
   *  Constant: 'Constant31' (':6516')
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  Gain: 'Gain4' (':6500')
   *  Gain: 'Gain8' (':6501')
   *  Gain: 'Gain1' (':6517')
   *  Rounding: 'Round' (':6502')
   *  Sum: 'Add' (':6499')
   *  Sum: 'Sum13' (':6518')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.WinchDrum_Angle = (real32_T)((real_T)
    ((-(rtb_UnitConversion_k - (360.0 * rt_roundd_snf(0.0027777777777777779 *
    rtb_UnitConversion_k)))) + 180.0));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6457:2') */
  rtb_DiscreteTransferFcn_ps = 6.2451197296384117E-6 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g;

  /* Gain: 'Gain8' (':6445') incorporates:
   *  DataStoreRead: 'Data Store Read1' (':6085')
   *  DataTypeConversion: 'Data Type Conversion29' (':6154')
   *  UnitConversion: 'Unit Conversion' (':6425:16')
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_Gain8 = 0.0015915494309189536 * (0.017453292519943295 * ((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Align_InitAngle));

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6434') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LOAD) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTATE = rtb_Gain8;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevRes != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTATE = rtb_Gain8;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6434') */
  Align_Load_Pos = Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTATE +
    (0.0025 * rtb_DiscreteTransferFcn_ps);

  /* UnitConversion: 'Unit Conversion' (':6098:16') incorporates:
   *  Gain: 'Gain10' (':6858')
   */
  /* Unit Conversion - from: rad to: deg
     Expression: output = (57.2958*input) + (0) */
  rtb_UnitConversion_a = 57.295779513082323 * (628.31853071795865 *
    Align_Load_Pos);

  /* DataTypeConversion: 'Data Type Conversion10' (':6025') incorporates:
   *  Constant: 'Constant32' (':6521')
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  Gain: 'Gain4' (':6507')
   *  Gain: 'Gain8' (':6508')
   *  Rounding: 'Round' (':6509')
   *  Sum: 'Add' (':6506')
   *  Sum: 'Sum14' (':6523')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.Align_Angle = (real32_T)((real_T)
    ((rtb_UnitConversion_a - (360.0 * rt_roundd_snf(0.0027777777777777779 *
    rtb_UnitConversion_a))) + 180.0));

  /* MultiPortSwitch: 'Multiport Switch1' (':6263') incorporates:
   *  Constant: 'Constant1' (':6265')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataStoreRead: 'Data Store Read4' (':6264')
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  DataTypeConversion: 'Data Type Conversion1' (':5995')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Algin) == 0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.PValveError_AlignDrv =
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_AlignDrv;
  }
  else
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.PValveError_AlignDrv = 10.5F;
  }

  /* End of MultiPortSwitch: 'Multiport Switch1' (':6263') */

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6388:2') */
  rtb_DiscreteTransferFcn_o = 0.0021553252381704738 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_o;

  /* DataTypeConversion: 'Data Type Conversion12' (':6032') incorporates:
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  Gain: 'Gain2' (':6519')
   *  UnitConversion: 'Unit Conversion' (':6511:4')
   */
  /* Unit Conversion - from: rad/s to: rpm
     Expression: output = (9.5493*input) + (0) */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.DrumMotorA_Velocity = (real32_T)((real_T)(
    -(9.5492965855137211 * rtb_DiscreteTransferFcn_o)));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6387:2') */
  rtb_DiscreteTransferFcn_b = 0.0021553252381704738 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_a;

  /* DataTypeConversion: 'Data Type Conversion13' (':6033') incorporates:
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  Gain: 'Gain18' (':6520')
   *  UnitConversion: 'Unit Conversion' (':6512:4')
   */
  /* Unit Conversion - from: rad/s to: rpm
     Expression: output = (9.5493*input) + (0) */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.DrumMotorB_Velocity = (real32_T)((real_T)(
    -(9.5492965855137211 * rtb_DiscreteTransferFcn_b)));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6456:2') */
  rtb_DiscreteTransferFcn_f = 9.740537288764208E-8 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_i;

  /* DataTypeConversion: 'Data Type Conversion14' (':6034') incorporates:
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  Gain: 'Gain1' (':6438')
   *  UnitConversion: 'Unit Conversion' (':6513:4')
   */
  /* Unit Conversion - from: rad/s to: rpm
     Expression: output = (9.5493*input) + (0) */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.AlignMotor_Velocity = (real32_T)((real_T)
    (9.5492965855137211 * (628.31853071795865 * rtb_DiscreteTransferFcn_f)));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6411:2') */
  rtb_Gain2_m = 0.0046174624876194822 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g1;

  /* Saturate: 'Prssure_Limit' (':6408') */
  if (rtb_Gain2_m > 350.0)
  {
    rtb_Gain2_m = 350.0;
  }
  else
  {
    if (rtb_Gain2_m < -350.0)
    {
      rtb_Gain2_m = -350.0;
    }
  }

  /* End of Saturate: 'Prssure_Limit' (':6408') */

  /* Sum: 'Sum9' (':6282') incorporates:
   *  DataTypeConversion: 'Data Type Conversion34' (':6281')
   *  Gain: 'Gain6' (':6548')
   *  Gain: 'Gain7' (':6855')
   */
  rtb_MultiportSwitch13 = (100.0 * (100.0 * rtb_Gain2_m)) + ((real_T)
    Lws_HilsCtrl_240218_v_1_0_B.Pressure_WinchPwBase);

  /* Saturate: 'Sensor_Prssure_Limit' (':6105') */
  if (rtb_MultiportSwitch13 > 400.0)
  {
    rtb_MultiportSwitch13 = 400.0;
  }
  else
  {
    if (rtb_MultiportSwitch13 < -400.0)
    {
      rtb_MultiportSwitch13 = -400.0;
    }
  }

  /* End of Saturate: 'Sensor_Prssure_Limit' (':6105') */

  /* DataTypeConversion: 'Data Type Conversion27' (':6114') incorporates:
   *  Abs: 'Abs' (':6109')
   *  Constant: 'Constant4' (':6113')
   *  DataStoreWrite: 'Data Store Write1' (':6002')
   *  Gain: 'Gain3' (':6107')
   *  Sum: 'Sum' (':6111')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.Pressure_WinchPw = (real32_T)((real_T)
    ((0.04 * fabs(rtb_MultiportSwitch13)) + 4.0));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5851:2') */
  rtb_Prssure_Limit_mc = 0.0097527769320981 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_id;

  /* Saturate: 'Prssure_Limit' (':5846') */
  if (rtb_Prssure_Limit_mc > 350.0)
  {
    rtb_Prssure_Limit_mc = 350.0;
  }
  else
  {
    if (rtb_Prssure_Limit_mc < -350.0)
    {
      rtb_Prssure_Limit_mc = -350.0;
    }
  }

  /* End of Saturate: 'Prssure_Limit' (':5846') */

  /* Gain: 'Gain2' (':6550') */
  rtb_MultiportSwitch13 = 35000.0 * rtb_Prssure_Limit_mc;

  /* Saturate: 'Sensor_Prssure_Limit1' (':6202') */
  if (rtb_MultiportSwitch13 > 400.0)
  {
    rtb_MultiportSwitch13 = 400.0;
  }
  else
  {
    if (rtb_MultiportSwitch13 < -400.0)
    {
      rtb_MultiportSwitch13 = -400.0;
    }
  }

  /* End of Saturate: 'Sensor_Prssure_Limit1' (':6202') */

  /* DataTypeConversion: 'Data Type Conversion15' (':6037') incorporates:
   *  Abs: 'Abs1' (':6199')
   *  Constant: 'Constant5' (':6200')
   *  DataStoreWrite: 'Data Store Write2' (':6035')
   *  Gain: 'Gain4' (':6201')
   *  Sum: 'Sum1' (':6203')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_ExpPressure = (real32_T)((real_T)
    ((0.04 * fabs(rtb_MultiportSwitch13)) + 4.0));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6809:2') */
  rtb_DiscreteTransferFcn_i = 1.2490239459276823E-6 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_e;

  /* Gain: 'Gain10' (':6791') incorporates:
   *  DataStoreRead: 'Data Store Read1' (':6085')
   *  DataTypeConversion: 'Data Type Conversion30' (':6170')
   */
  rtb_Gain10 = 0.001 * ((real_T)
                        Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainCy01_InitPos);

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6780') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOADI) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE = rtb_Gain10;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRese != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE = rtb_Gain10;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6780') */
  rtb_Gain10 = Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE +
    (0.0025 * rtb_DiscreteTransferFcn_i);

  /* Gain: 'Gain5' (':6208') */
  rtb_mm_nv = 1000.0 * rtb_Gain10;

  /* Saturate: 'Sensor_Dis_Range' (':6207') */
  if (rtb_mm_nv > 800.0)
  {
    rtb_mm_nv = 800.0;
  }
  else
  {
    if (rtb_mm_nv < 0.0)
    {
      rtb_mm_nv = 0.0;
    }
  }

  /* End of Saturate: 'Sensor_Dis_Range' (':6207') */

  /* DataTypeConversion: 'Data Type Conversion17' (':6041') incorporates:
   *  Constant: 'Constant6' (':6212')
   *  DataStoreWrite: 'Data Store Write2' (':6035')
   *  Gain: 'Gain6' (':6209')
   *  Sum: 'Sum2' (':6211')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_LVDT = (real32_T)((real_T)((0.02 *
    rtb_mm_nv) + 4.0));

  /* MultiPortSwitch: 'Multiport Switch2' (':6266') incorporates:
   *  Constant: 'Constant3' (':6267')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataStoreRead: 'Data Store Read5' (':6268')
   *  DataStoreWrite: 'Data Store Write2' (':6035')
   *  DataTypeConversion: 'Data Type Conversion2' (':5996')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC01) == 0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_PValveError =
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_MainCy01Drv;
  }
  else
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_PValveError = 10.5F;
  }

  /* End of MultiPortSwitch: 'Multiport Switch2' (':6266') */

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5909:2') */
  rtb_Prssure_Limit = 0.0097527769320981 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_d;

  /* Saturate: 'Prssure_Limit' (':5904') */
  if (rtb_Prssure_Limit > 350.0)
  {
    rtb_Prssure_Limit = 350.0;
  }
  else
  {
    if (rtb_Prssure_Limit < -350.0)
    {
      rtb_Prssure_Limit = -350.0;
    }
  }

  /* End of Saturate: 'Prssure_Limit' (':5904') */

  /* Gain: 'Gain2' (':6551') */
  rtb_MultiportSwitch13 = 35000.0 * rtb_Prssure_Limit;

  /* Saturate: 'Sensor_Prssure_Limit2' (':6216') */
  if (rtb_MultiportSwitch13 > 400.0)
  {
    rtb_MultiportSwitch13 = 400.0;
  }
  else
  {
    if (rtb_MultiportSwitch13 < -400.0)
    {
      rtb_MultiportSwitch13 = -400.0;
    }
  }

  /* End of Saturate: 'Sensor_Prssure_Limit2' (':6216') */

  /* DataTypeConversion: 'Data Type Conversion16' (':6040') incorporates:
   *  Abs: 'Abs2' (':6213')
   *  Constant: 'Constant7' (':6214')
   *  DataStoreWrite: 'Data Store Write2' (':6035')
   *  Gain: 'Gain7' (':6215')
   *  Sum: 'Sum3' (':6217')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_ExpPressure = (real32_T)((real_T)
    ((0.04 * fabs(rtb_MultiportSwitch13)) + 4.0));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6810:2') */
  rtb_DiscreteTransferFcn_g = 1.2490239459276823E-6 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_k;

  /* Gain: 'Gain11' (':6792') incorporates:
   *  DataStoreRead: 'Data Store Read1' (':6085')
   *  DataTypeConversion: 'Data Type Conversion31' (':6172')
   */
  rtb_Gain11 = 0.001 * ((real_T)
                        Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainCy02_InitPos);

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6781') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_c) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_e = rtb_Gain11;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_d != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_e = rtb_Gain11;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6781') */
  rtb_Gain11 = Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_e +
    (0.0025 * rtb_DiscreteTransferFcn_g);

  /* Gain: 'Gain8' (':6221') */
  rtb_mm = 1000.0 * rtb_Gain11;

  /* Saturate: 'Sensor_Dis_Range1' (':6223') */
  if (rtb_mm > 800.0)
  {
    rtb_mm = 800.0;
  }
  else
  {
    if (rtb_mm < 0.0)
    {
      rtb_mm = 0.0;
    }
  }

  /* End of Saturate: 'Sensor_Dis_Range1' (':6223') */

  /* DataTypeConversion: 'Data Type Conversion18' (':6043') incorporates:
   *  Constant: 'Constant8' (':6220')
   *  DataStoreWrite: 'Data Store Write2' (':6035')
   *  Gain: 'Gain9' (':6222')
   *  Sum: 'Sum4' (':6224')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_LVDT = (real32_T)((real_T)((0.02 *
    rtb_mm) + 4.0));

  /* MultiPortSwitch: 'Multiport Switch3' (':6271') incorporates:
   *  Constant: 'Constant16' (':6269')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataStoreRead: 'Data Store Read6' (':6270')
   *  DataStoreWrite: 'Data Store Write2' (':6035')
   *  DataTypeConversion: 'Data Type Conversion3' (':5997')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC02) == 0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_PValveError =
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_MainCy02Drv;
  }
  else
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_PValveError = 10.5F;
  }

  /* End of MultiPortSwitch: 'Multiport Switch3' (':6271') */

  /* DataStoreWrite: 'Data Store Write2' (':6035') */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_ConPressure =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy01_ExpPressure;
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_ConPressure =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.MainSy02_ExpPressure;

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5875:2') */
  rtb_Prssure_Limit_a = 0.0097527769320981 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_n;

  /* Saturate: 'Prssure_Limit' (':5871') */
  if (rtb_Prssure_Limit_a > 350.0)
  {
    rtb_Prssure_Limit_a = 350.0;
  }
  else
  {
    if (rtb_Prssure_Limit_a < -350.0)
    {
      rtb_Prssure_Limit_a = -350.0;
    }
  }

  /* End of Saturate: 'Prssure_Limit' (':5871') */

  /* Gain: 'Gain2' (':6552') */
  rtb_MultiportSwitch13 = 35000.0 * rtb_Prssure_Limit_a;

  /* Saturate: 'Sensor_Prssure_Limit3' (':6242') */
  if (rtb_MultiportSwitch13 > 400.0)
  {
    rtb_MultiportSwitch13 = 400.0;
  }
  else
  {
    if (rtb_MultiportSwitch13 < -400.0)
    {
      rtb_MultiportSwitch13 = -400.0;
    }
  }

  /* End of Saturate: 'Sensor_Prssure_Limit3' (':6242') */

  /* DataTypeConversion: 'Data Type Conversion21' (':6054') incorporates:
   *  Abs: 'Abs3' (':6228')
   *  Constant: 'Constant12' (':6230')
   *  DataStoreWrite: 'Data Store Write3' (':6053')
   *  Gain: 'Gain10' (':6234')
   *  Sum: 'Sum5' (':6244')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_ExpPressure = (real32_T)((real_T)
    ((0.04 * fabs(rtb_MultiportSwitch13)) + 4.0));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6719:2') */
  rtb_DiscreteTransferFcn_l = 1.2490239459276823E-6 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_ip;

  /* Gain: 'Gain10' (':6701') incorporates:
   *  DataStoreRead: 'Data Store Read1' (':6085')
   *  DataTypeConversion: 'Data Type Conversion32' (':6174')
   */
  rtb_Gain10_b = 0.001 * ((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubCy01_InitPos);

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6690') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_a) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_c = rtb_Gain10_b;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_b != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_c = rtb_Gain10_b;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6690') */
  rtb_Gain10_b = Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_c +
    (0.0025 * rtb_DiscreteTransferFcn_l);

  /* Gain: 'Gain11' (':6235') */
  rtb_mm_e = 1000.0 * rtb_Gain10_b;

  /* Saturate: 'Sensor_Dis_Range2' (':6240') */
  if (rtb_mm_e > 400.0)
  {
    rtb_mm_e = 400.0;
  }
  else
  {
    if (rtb_mm_e < 0.0)
    {
      rtb_mm_e = 0.0;
    }
  }

  /* End of Saturate: 'Sensor_Dis_Range2' (':6240') */

  /* DataTypeConversion: 'Data Type Conversion23' (':6056') incorporates:
   *  Constant: 'Constant13' (':6231')
   *  DataStoreWrite: 'Data Store Write3' (':6053')
   *  Gain: 'Gain12' (':6236')
   *  Sum: 'Sum6' (':6245')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_LVDT = (real32_T)((real_T)((0.04 *
    rtb_mm_e) + 4.0));

  /* MultiPortSwitch: 'Multiport Switch4' (':6274') incorporates:
   *  Constant: 'Constant17' (':6272')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataStoreRead: 'Data Store Read7' (':6273')
   *  DataStoreWrite: 'Data Store Write3' (':6053')
   *  DataTypeConversion: 'Data Type Conversion4' (':5998')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC01) == 0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_PValveError =
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_SubCy01Drv;
  }
  else
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_PValveError = 10.5F;
  }

  /* End of MultiPortSwitch: 'Multiport Switch4' (':6274') */

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5933:2') */
  rtb_Prssure_Limit_l = 0.0097527769320981 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_m;

  /* Saturate: 'Prssure_Limit' (':5929') */
  if (rtb_Prssure_Limit_l > 350.0)
  {
    rtb_Prssure_Limit_l = 350.0;
  }
  else
  {
    if (rtb_Prssure_Limit_l < -350.0)
    {
      rtb_Prssure_Limit_l = -350.0;
    }
  }

  /* End of Saturate: 'Prssure_Limit' (':5929') */

  /* Gain: 'Gain2' (':6553') */
  rtb_MultiportSwitch13 = 35000.0 * rtb_Prssure_Limit_l;

  /* Saturate: 'Sensor_Prssure_Limit4' (':6243') */
  if (rtb_MultiportSwitch13 > 400.0)
  {
    rtb_MultiportSwitch13 = 400.0;
  }
  else
  {
    if (rtb_MultiportSwitch13 < -400.0)
    {
      rtb_MultiportSwitch13 = -400.0;
    }
  }

  /* End of Saturate: 'Sensor_Prssure_Limit4' (':6243') */

  /* DataTypeConversion: 'Data Type Conversion22' (':6055') incorporates:
   *  Abs: 'Abs4' (':6229')
   *  Constant: 'Constant14' (':6232')
   *  DataStoreWrite: 'Data Store Write3' (':6053')
   *  Gain: 'Gain13' (':6237')
   *  Sum: 'Sum7' (':6246')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_ExpPressure = (real32_T)((real_T)
    ((0.04 * fabs(rtb_MultiportSwitch13)) + 4.0));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6720:2') */
  rtb_DiscreteTransferFcn_a = 1.2490239459276823E-6 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_h;

  /* Gain: 'Gain11' (':6702') incorporates:
   *  DataStoreRead: 'Data Store Read1' (':6085')
   *  DataTypeConversion: 'Data Type Conversion33' (':6176')
   */
  rtb_Gain11_l = 0.001 * ((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubCy02_InitPos);

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6691') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_p) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_c = rtb_Gain11_l;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_g != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_c = rtb_Gain11_l;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6691') */
  rtb_Gain11_l = Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_c +
    (0.0025 * rtb_DiscreteTransferFcn_a);

  /* Gain: 'Gain14' (':6238') */
  rtb_mm_jn = 1000.0 * rtb_Gain11_l;

  /* Saturate: 'Sensor_Dis_Range3' (':6241') */
  if (rtb_mm_jn > 400.0)
  {
    rtb_mm_jn = 400.0;
  }
  else
  {
    if (rtb_mm_jn < 0.0)
    {
      rtb_mm_jn = 0.0;
    }
  }

  /* End of Saturate: 'Sensor_Dis_Range3' (':6241') */

  /* DataTypeConversion: 'Data Type Conversion24' (':6057') incorporates:
   *  Constant: 'Constant15' (':6233')
   *  DataStoreWrite: 'Data Store Write3' (':6053')
   *  Gain: 'Gain15' (':6239')
   *  Sum: 'Sum8' (':6247')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_LVDT = (real32_T)((real_T)((0.04 *
    rtb_mm_jn) + 4.0));

  /* MultiPortSwitch: 'Multiport Switch5' (':6277') incorporates:
   *  Constant: 'Constant18' (':6275')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataStoreRead: 'Data Store Read8' (':6276')
   *  DataStoreWrite: 'Data Store Write3' (':6053')
   *  DataTypeConversion: 'Data Type Conversion5' (':5999')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC02) == 0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_PValveError =
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_SubCy02Drv;
  }
  else
  {
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_PValveError = 10.5F;
  }

  /* End of MultiPortSwitch: 'Multiport Switch5' (':6277') */

  /* DataStoreWrite: 'Data Store Write3' (':6053') */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_ConPressure =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy01_ExpPressure;
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_ConPressure =
    Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.SubSy02_ExpPressure;

  /* Saturate: 'Sensor_Prssure_Limit5' (':6296') incorporates:
   *  DataTypeConversion: 'Data Type Conversion36' (':6293')
   */
  if (Lws_HilsCtrl_240218_v_1_0_B.Pressure_DropLiftPw > 400.0F)
  {
    rtb_MultiportSwitch12 = 400.0;
  }
  else if (Lws_HilsCtrl_240218_v_1_0_B.Pressure_DropLiftPw < -400.0F)
  {
    rtb_MultiportSwitch12 = -400.0;
  }
  else
  {
    rtb_MultiportSwitch12 = (real_T)
      Lws_HilsCtrl_240218_v_1_0_B.Pressure_DropLiftPw;
  }

  /* End of Saturate: 'Sensor_Prssure_Limit5' (':6296') */

  /* DataTypeConversion: 'Data Type Conversion35' (':6292') incorporates:
   *  Abs: 'Abs5' (':6290')
   *  Constant: 'Constant19' (':6291')
   *  DataStoreWrite: 'Data Store Write4' (':6288')
   *  Gain: 'Gain16' (':6295')
   *  Sum: 'Sum10' (':6297')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.Pressure_DropLiftPw = (real32_T)((real_T)
    ((0.04 * fabs(rtb_MultiportSwitch12)) + 4.0));

  /* Gain: 'Gain4' (':6406') */
  rtb_Q_fedcm3s_a = 278.04 * rtb_DiscreteTransferFcn_o;

  /* Sum: 'Sum19' (':6615') */
  rtb_MultiportSwitch13 = rtb_Q_fedcm3s_a + ((real_T)
    Lws_HilsCtrl_240218_v_1_0_B.OilFlow_DropLift);

  /* Saturate: 'Sensor_OilFlow_Limit' (':6306') */
  if (rtb_MultiportSwitch13 > 400.0)
  {
    rtb_MultiportSwitch13 = 400.0;
  }
  else
  {
    if (rtb_MultiportSwitch13 < -400.0)
    {
      rtb_MultiportSwitch13 = -400.0;
    }
  }

  /* End of Saturate: 'Sensor_OilFlow_Limit' (':6306') */

  /* DataTypeConversion: 'Data Type Conversion37' (':6303') incorporates:
   *  Abs: 'Abs6' (':6301')
   *  Constant: 'Constant20' (':6302')
   *  DataStoreWrite: 'Data Store Write4' (':6288')
   *  Gain: 'Gain17' (':6305')
   *  Sum: 'Sum11' (':6307')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.OilFlow_DropLift = (real32_T)((real_T)
    ((0.16 * fabs(rtb_MultiportSwitch13)) + 4.0));

  /* Saturate: 'Sensor_Tension_Limit' (':6621') incorporates:
   *  DataStoreRead: 'Data Store Read9' (':6617')
   *  DataTypeConversion: 'Data Type Conversion56' (':6623')
   */
  if (Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.TensionS_RefTension > 10.0F)
  {
    rtb_MultiportSwitch12 = 10.0;
  }
  else if (Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.TensionS_RefTension < -10.0F)
  {
    rtb_MultiportSwitch12 = -10.0;
  }
  else
  {
    rtb_MultiportSwitch12 = (real_T)
      Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.TensionS_RefTension;
  }

  /* End of Saturate: 'Sensor_Tension_Limit' (':6621') */

  /* DataTypeConversion: 'Data Type Conversion39' (':6309') incorporates:
   *  Abs: 'Abs7' (':6622')
   *  Constant: 'Constant21' (':6619')
   *  DataStoreWrite: 'Data Store Write4' (':6288')
   *  Gain: 'Gain37' (':6620')
   *  Sum: 'Sum20' (':6618')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsAO.TensionSensor = (real32_T)((real_T)(fabs
    (0.4 * rtb_MultiportSwitch12) + 4.0));

  /* MultiPortSwitch: 'Multiport Switch13' (':6464') incorporates:
   *  Constant: 'Constant29' (':6463')
   *  DataStoreRead: 'Data Store Read2' (':6088')
   *  MultiPortSwitch: 'Multiport Switch7' (':6336')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock) == 0)
  {
    rtb_MultiportSwitch13 = 0.0;
  }
  else if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning) == 0)
  {
    /* MultiPortSwitch: 'Multiport Switch7' (':6336') incorporates:
     *  Constant: 'Constant23' (':6334')
     */
    rtb_MultiportSwitch13 = 0.0;
  }
  else
  {
    /* MultiPortSwitch: 'Multiport Switch7' (':6336') incorporates:
     *  DataStoreRead: 'Data Store Read30' (':5987')
     *  DataTypeConversion: 'Data Type Conversion1' (':5995')
     */
    rtb_MultiportSwitch13 = (real_T)
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_AlignDrv;
  }

  /* End of MultiPortSwitch: 'Multiport Switch13' (':6464') */

  /* Switch: 'Switch' (':6841:5') incorporates:
   *  DataStoreRead: 'Data Store Read11' (':6846')
   *  DataTypeConversion: 'Data Type Conversion62' (':6847')
   *  RelationalOperator: 'u_GTE_up' (':6841:7')
   */
  if (rtb_MultiportSwitch13 >= ((real_T)
       Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubSy_ConRefPressure))
  {
    rtb_Gain21 = (real_T)
      Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubSy_ConRefPressure;
  }
  else
  {
    /* Gain: 'Gain21' (':6842') */
    rtb_Gain21 = -((real_T)
                   Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubSy_ConRefPressure);

    /* Switch: 'Switch1' (':6841:6') incorporates:
     *  Gain: 'Gain21' (':6842')
     *  RelationalOperator: 'u_GT_lo' (':6841:8')
     */
    if (rtb_MultiportSwitch13 > (-((real_T)
          Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubSy_ConRefPressure)))
    {
      rtb_Gain21 = rtb_MultiportSwitch13;
    }

    /* End of Switch: 'Switch1' (':6841:6') */
  }

  /* End of Switch: 'Switch' (':6841:5') */

  /* Sum: 'Diff' (':6841:4') */
  rtb_MultiportSwitch13 -= rtb_Gain21;

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6433') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_e) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_n = rtb_Gain8;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_n != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_n = rtb_Gain8;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6433') */
  rtb_Gain8 = Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_n +
    (0.0025 * rtb_DiscreteTransferFcn_f);

  /* Sum: 'Sum3' (':6453') incorporates:
   *  Gain: 'Gain6' (':6443')
   *  Gain: 'Gain7' (':6444')
   *  Sum: 'Sum' (':6451')
   *  Sum: 'Sum6' (':6455')
   */
  rtb_Gain21 = (300.0 * (rtb_Gain8 - Align_Load_Pos)) + (300.0 *
    (rtb_DiscreteTransferFcn_f - rtb_DiscreteTransferFcn_ps));

  /* Sum: 'Sum2' (':6452') incorporates:
   *  DataStoreRead: 'Data Store Read10' (':6844')
   *  DataTypeConversion: 'Data Type Conversion61' (':6845')
   *  Gain: 'Gain5' (':6442')
   *  Gain: 'Gain19' (':6525')
   *  Product: 'Product4' (':6843')
   */
  rtb_DiscreteTransferFcn_f = (100.0 * (0.03 * (((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.SubSy_ExpRefPressure) *
    rtb_MultiportSwitch13))) - rtb_Gain21;

  /* Sum: 'Sum5' (':6454') */
  rtb_MultiportSwitch13 = rtb_Gain21;

  /* MultiPortSwitch: 'Multiport Switch12' (':6418') incorporates:
   *  Constant: 'Constant28' (':6419')
   *  Constant: 'Constant30' (':6515')
   *  DataStoreRead: 'Data Store Read2' (':6088')
   *  Logic: 'Logical Operator2' (':6330')
   *  MultiPortSwitch: 'Multiport Switch6' (':6331')
   *  Sum: 'Sum12' (':6514')
   */
  if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock) == 0) ||
      (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock) == 0))
  {
    rtb_MultiportSwitch12 = 0.0;
  }
  else
  {
    if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning) == 0)
    {
      /* MultiPortSwitch: 'Multiport Switch6' (':6331') incorporates:
       *  Constant: 'Constant22' (':6333')
       */
      rtb_MultiportSwitch12 = 0.0;
    }
    else
    {
      /* MultiPortSwitch: 'Multiport Switch6' (':6331') incorporates:
       *  DataStoreRead: 'Data Store Read30' (':5987')
       *  DataTypeConversion: 'Data Type Conversion6' (':5994')
       */
      rtb_MultiportSwitch12 = (real_T)
        Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_DrumDrv;
    }

    rtb_MultiportSwitch12 -= 2.5;
  }

  /* End of MultiPortSwitch: 'Multiport Switch12' (':6418') */

  /* Switch: 'Switch' (':6852:5') incorporates:
   *  DataStoreRead: 'Data Store Read17' (':6849')
   *  DataTypeConversion: 'Data Type Conversion64' (':6851')
   *  RelationalOperator: 'u_GTE_up' (':6852:7')
   */
  if (rtb_MultiportSwitch12 >= ((real_T)
       Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainSy_ConRefPressure))
  {
    rtb_Gain21 = (real_T)
      Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainSy_ConRefPressure;
  }
  else
  {
    /* Gain: 'Gain22' (':6853') */
    rtb_Gain21 = -((real_T)
                   Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainSy_ConRefPressure);

    /* Switch: 'Switch1' (':6852:6') incorporates:
     *  Gain: 'Gain22' (':6853')
     *  RelationalOperator: 'u_GT_lo' (':6852:8')
     */
    if (rtb_MultiportSwitch12 > (-((real_T)
          Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainSy_ConRefPressure)))
    {
      rtb_Gain21 = rtb_MultiportSwitch12;
    }

    /* End of Switch: 'Switch1' (':6852:6') */
  }

  /* End of Switch: 'Switch' (':6852:5') */

  /* Gain: 'Gain3' (':6405') incorporates:
   *  DataStoreRead: 'Data Store Read16' (':6848')
   *  DataTypeConversion: 'Data Type Conversion63' (':6850')
   *  Product: 'Product5' (':6854')
   *  Sum: 'Diff' (':6852:4')
   */
  rtb_MultiportSwitch12 = 0.4 * (((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.MainSy_ExpRefPressure) *
    (rtb_MultiportSwitch12 - rtb_Gain21));

  /* MultiPortSwitch: 'Multiport Switch8' (':6339') incorporates:
   *  Constant: 'Constant24' (':6337')
   *  DataStoreRead: 'Data Store Read2' (':6088')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataTypeConversion: 'Data Type Conversion2' (':5996')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning) == 0)
  {
    rtb_Gain21 = 0.0;
  }
  else
  {
    rtb_Gain21 = (real_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_MainCy01Drv;
  }

  /* End of MultiPortSwitch: 'Multiport Switch8' (':6339') */

  /* Switch: 'Switch' (':6832:5') incorporates:
   *  Constant: 'Constant33' (':6862')
   *  RelationalOperator: 'u_GTE_up' (':6832:7')
   *  RelationalOperator: 'u_GT_lo' (':6832:8')
   *  Switch: 'Switch1' (':6832:6')
   */
  if (rtb_Gain21 >= 1.5)
  {
    Gain3_o = 1.5;
  }
  else if (rtb_Gain21 > -1.5)
  {
    /* Switch: 'Switch1' (':6832:6') */
    Gain3_o = rtb_Gain21;
  }
  else
  {
    Gain3_o = -1.5;
  }

  /* End of Switch: 'Switch' (':6832:5') */

  /* Gain: 'Gain3' (':5842') incorporates:
   *  DataStoreRead: 'Data Store Read14' (':6835')
   *  DataTypeConversion: 'Data Type Conversion59' (':6836')
   *  Product: 'Product3' (':6834')
   *  Sum: 'Diff' (':6832:4')
   */
  Gain3_f = 0.1 * (((real_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare01) *
                   (rtb_Gain21 - Gain3_o));

  /* MultiPortSwitch: 'Multiport Switch9' (':6342') incorporates:
   *  Constant: 'Constant25' (':6340')
   *  DataStoreRead: 'Data Store Read2' (':6088')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataTypeConversion: 'Data Type Conversion3' (':5997')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning) == 0)
  {
    rtb_Gain21 = 0.0;
  }
  else
  {
    rtb_Gain21 = (real_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_MainCy02Drv;
  }

  /* End of MultiPortSwitch: 'Multiport Switch9' (':6342') */

  /* Switch: 'Switch' (':6829:5') incorporates:
   *  Constant: 'Constant33' (':6862')
   *  RelationalOperator: 'u_GTE_up' (':6829:7')
   *  RelationalOperator: 'u_GT_lo' (':6829:8')
   *  Switch: 'Switch1' (':6829:6')
   */
  if (rtb_Gain21 >= 1.5)
  {
    Gain3_o = 1.5;
  }
  else if (rtb_Gain21 > -1.5)
  {
    /* Switch: 'Switch1' (':6829:6') */
    Gain3_o = rtb_Gain21;
  }
  else
  {
    Gain3_o = -1.5;
  }

  /* End of Switch: 'Switch' (':6829:5') */

  /* Gain: 'Gain3' (':5900') incorporates:
   *  DataStoreRead: 'Data Store Read14' (':6835')
   *  DataTypeConversion: 'Data Type Conversion59' (':6836')
   *  Product: 'Product2' (':6831')
   *  Sum: 'Diff' (':6829:4')
   */
  Gain3_o = 0.1 * (((real_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare01) *
                   (rtb_Gain21 - Gain3_o));

  /* MultiPortSwitch: 'Multiport Switch10' (':6345') incorporates:
   *  Constant: 'Constant26' (':6343')
   *  DataStoreRead: 'Data Store Read2' (':6088')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataTypeConversion: 'Data Type Conversion4' (':5998')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning) == 0)
  {
    rtb_MultiportSwitch10 = 0.0;
  }
  else
  {
    rtb_MultiportSwitch10 = (real_T)
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_SubCy01Drv;
  }

  /* End of MultiPortSwitch: 'Multiport Switch10' (':6345') */

  /* Switch: 'Switch' (':6823:5') incorporates:
   *  Constant: 'Constant34' (':6863')
   *  RelationalOperator: 'u_GTE_up' (':6823:7')
   *  RelationalOperator: 'u_GT_lo' (':6823:8')
   *  Switch: 'Switch1' (':6823:6')
   */
  if (rtb_MultiportSwitch10 >= 1.5)
  {
    rtb_Gain21 = 1.5;
  }
  else if (rtb_MultiportSwitch10 > -1.5)
  {
    /* Switch: 'Switch1' (':6823:6') */
    rtb_Gain21 = rtb_MultiportSwitch10;
  }
  else
  {
    rtb_Gain21 = -1.5;
  }

  /* End of Switch: 'Switch' (':6823:5') */

  /* Gain: 'Gain3' (':5867') incorporates:
   *  DataStoreRead: 'Data Store Read12' (':6820')
   *  DataTypeConversion: 'Data Type Conversion57' (':6821')
   *  Product: 'Product' (':6819')
   *  Sum: 'Diff' (':6823:4')
   */
  rtb_MultiportSwitch10 = 0.1 * (((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare02) * (rtb_MultiportSwitch10 -
    rtb_Gain21));

  /* MultiPortSwitch: 'Multiport Switch11' (':6348') incorporates:
   *  Constant: 'Constant27' (':6346')
   *  DataStoreRead: 'Data Store Read2' (':6088')
   *  DataStoreRead: 'Data Store Read30' (':5987')
   *  DataTypeConversion: 'Data Type Conversion5' (':5999')
   */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning) == 0)
  {
    rtb_MultiportSwitch11 = 0.0;
  }
  else
  {
    rtb_MultiportSwitch11 = (real_T)
      Lws_HilsCtrl_240218_v_1_0_DW.HilsAI.PValve_SubCy02Drv;
  }

  /* End of MultiPortSwitch: 'Multiport Switch11' (':6348') */

  /* Switch: 'Switch' (':6827:5') incorporates:
   *  Constant: 'Constant34' (':6863')
   *  RelationalOperator: 'u_GTE_up' (':6827:7')
   *  RelationalOperator: 'u_GT_lo' (':6827:8')
   *  Switch: 'Switch1' (':6827:6')
   */
  if (rtb_MultiportSwitch11 >= 1.5)
  {
    rtb_Gain21 = 1.5;
  }
  else if (rtb_MultiportSwitch11 > -1.5)
  {
    /* Switch: 'Switch1' (':6827:6') */
    rtb_Gain21 = rtb_MultiportSwitch11;
  }
  else
  {
    rtb_Gain21 = -1.5;
  }

  /* End of Switch: 'Switch' (':6827:5') */

  /* Gain: 'Gain3' (':5925') incorporates:
   *  DataStoreRead: 'Data Store Read12' (':6820')
   *  DataTypeConversion: 'Data Type Conversion57' (':6821')
   *  Product: 'Product1' (':6822')
   *  Sum: 'Diff' (':6827:4')
   */
  rtb_MultiportSwitch11 = 0.1 * (((real_T)
    Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.Spare02) * (rtb_MultiportSwitch11 -
    rtb_Gain21));

  /* Sum: 'Sum3' (':6410') incorporates:
   *  DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6412:2')
   *  Gain: 'Gain1' (':6403')
   *  Gain: 'Gain2' (':6404')
   */
  rtb_Q_fedcm3s_a = (183.3 * (19.894 * (0.14536400084676654 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_hp))) -
    rtb_Q_fedcm3s_a;

  /* DataTypeConversion: 'Data Type Conversion55' (':6611') incorporates:
   *  DataStoreWrite: 'Data Store Write10' (':6609')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy02_Pos = (real32_T)rtb_mm_jn;

  /* DataTypeConversion: 'Data Type Conversion54' (':6610') incorporates:
   *  DataStoreWrite: 'Data Store Write10' (':6609')
   *  Gain: 'Gain35' (':6608')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy02_Vel = (real32_T)((real_T)(1000.0 *
    rtb_DiscreteTransferFcn_a));

  /* DataTypeConversion: 'Data Type Conversion44' (':6567') incorporates:
   *  DataStoreWrite: 'Data Store Write5' (':6561')
   *  UnitConversion: 'Unit Conversion' (':6624:4')
   */
  /* Unit Conversion - from: rad/s to: rpm
     Expression: output = (9.5493*input) + (0) */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.WinchDrum_Vel = (real32_T)((real_T)
    (9.5492965855137211 * rtb_DiscreteTransferFcn));

  /* DataTypeConversion: 'Data Type Conversion45' (':6568') incorporates:
   *  DataStoreWrite: 'Data Store Write5' (':6561')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.WinchDrun_Angle = (real32_T)
    rtb_UnitConversion_k;

  /* DataTypeConversion: 'Data Type Conversion46' (':6574') incorporates:
   *  DataStoreWrite: 'Data Store Write6' (':6573')
   *  Gain: 'Gain9' (':6857')
   *  Gain: 'Gain23' (':6859')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.Align_Vel = (real32_T)((real_T)
    (0.0015915494309189536 * (628.31853071795865 * rtb_DiscreteTransferFcn_ps)));

  /* DataTypeConversion: 'Data Type Conversion47' (':6575') incorporates:
   *  DataStoreWrite: 'Data Store Write6' (':6573')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.Align_Angle = (real32_T)
    rtb_UnitConversion_a;

  /* DataTypeConversion: 'Data Type Conversion48' (':6597') incorporates:
   *  DataStoreWrite: 'Data Store Write7' (':6596')
   *  Gain: 'Gain32' (':6599')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy01_Vel = (real32_T)((real_T)(1000.0
    * rtb_DiscreteTransferFcn_i));

  /* DataTypeConversion: 'Data Type Conversion49' (':6598') incorporates:
   *  DataStoreWrite: 'Data Store Write7' (':6596')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy01_Pos = (real32_T)rtb_mm_nv;

  /* DataTypeConversion: 'Data Type Conversion50' (':6602') incorporates:
   *  DataStoreWrite: 'Data Store Write8' (':6601')
   *  Gain: 'Gain33' (':6600')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy02_Vel = (real32_T)((real_T)(1000.0
    * rtb_DiscreteTransferFcn_g));

  /* DataTypeConversion: 'Data Type Conversion51' (':6603') incorporates:
   *  DataStoreWrite: 'Data Store Write8' (':6601')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.MainCy02_Pos = (real32_T)rtb_mm;

  /* DataTypeConversion: 'Data Type Conversion52' (':6606') incorporates:
   *  DataStoreWrite: 'Data Store Write9' (':6605')
   *  Gain: 'Gain34' (':6604')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy01_Vel = (real32_T)((real_T)(1000.0 *
    rtb_DiscreteTransferFcn_l));

  /* DataTypeConversion: 'Data Type Conversion53' (':6607') incorporates:
   *  DataStoreWrite: 'Data Store Write9' (':6605')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsMon.SubCy01_Pos = (real32_T)rtb_mm_e;

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5934:2') */
  rtb_Gain21 = 0.0039192902718367265 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_oh;

  /* Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5920') */
  if (rtb_Gain21 > 1.0)
  {
    rtb_Gain21 = 1.0;
  }
  else
  {
    if (rtb_Gain21 < -1.0)
    {
      rtb_Gain21 = -1.0;
    }
  }

  /* End of Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5920') */

  /* Sum: 'Sum3' (':5932') incorporates:
   *  Gain: 'Gain1' (':5924')
   *  Gain: 'Gain4' (':5926')
   *  Gain: 'm//s --> cm//s' (':5935')
   */
  rtb_DiscreteTransferFcn_a = (1218.0 * rtb_Gain21) - (314.16 * (100.0 *
    rtb_DiscreteTransferFcn_a));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5876:2') */
  rtb_Gain21 = 0.0039192902718367265 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_m4;

  /* Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5862') */
  if (rtb_Gain21 > 1.0)
  {
    rtb_Gain21 = 1.0;
  }
  else
  {
    if (rtb_Gain21 < -1.0)
    {
      rtb_Gain21 = -1.0;
    }
  }

  /* End of Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5862') */

  /* Sum: 'Sum3' (':5874') incorporates:
   *  Gain: 'Gain1' (':5866')
   *  Gain: 'Gain4' (':5868')
   *  Gain: 'm//s --> cm//s' (':5877')
   */
  rtb_DiscreteTransferFcn_l = (1218.0 * rtb_Gain21) - (314.16 * (100.0 *
    rtb_DiscreteTransferFcn_l));

  /* Sum: 'Add2' (':6776') incorporates:
   *  Gain: 'Gain1' (':6815')
   *  Gain: 'Gain6' (':6798')
   *  Gain: 'Gain5' (':5902')
   */
  rtb_Prssure_Limit = (314.16 * rtb_Prssure_Limit) - (0.0 * (25.0 * rtb_Gain11));

  /* Sum: 'Add1' (':6775') incorporates:
   *  Gain: 'Gain2' (':6816')
   *  Gain: 'Gain5' (':6797')
   *  Gain: 'Gain5' (':5844')
   */
  rtb_Prssure_Limit_mc = (0.0 - (0.0 * (25.0 * rtb_Gain10))) + (314.16 *
    rtb_Prssure_Limit_mc);

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5908:2') */
  rtb_Gain21 = 0.0039192902718367265 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g1m;

  /* Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5895') */
  if (rtb_Gain21 > 1.0)
  {
    rtb_Gain21 = 1.0;
  }
  else
  {
    if (rtb_Gain21 < -1.0)
    {
      rtb_Gain21 = -1.0;
    }
  }

  /* End of Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5895') */

  /* Sum: 'Sum3' (':5907') incorporates:
   *  Gain: 'Gain1' (':5899')
   *  Gain: 'Gain4' (':5901')
   *  Gain: 'm//s --> cm//s' (':5910')
   */
  rtb_DiscreteTransferFcn_g = (1218.0 * rtb_Gain21) - (314.16 * (100.0 *
    rtb_DiscreteTransferFcn_g));

  /* DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5850:2') */
  rtb_Gain21 = 0.0039192902718367265 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_hf;

  /* Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5837') */
  if (rtb_Gain21 > 1.0)
  {
    rtb_Gain21 = 1.0;
  }
  else
  {
    if (rtb_Gain21 < -1.0)
    {
      rtb_Gain21 = -1.0;
    }
  }

  /* End of Saturate: 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':5837') */

  /* Sum: 'Sum3' (':5849') incorporates:
   *  Gain: 'Gain1' (':5841')
   *  Gain: 'Gain4' (':5843')
   *  Gain: 'm//s --> cm//s' (':5852')
   */
  rtb_DiscreteTransferFcn_i = (1218.0 * rtb_Gain21) - (314.16 * (100.0 *
    rtb_DiscreteTransferFcn_i));

  /* Gain: 'Gain5' (':6407') */
  rtb_Gain2_m *= 278.04;

  /* Gain: 'Gain2' (':6370') */
  rtb_Gain2_m *= 0.5;

  /* Gain: 'Gain6' (':6374') */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_UnitConversion_a = 5.0 * rtb_UnitConversion_tmp;

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6363') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_n) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_j =
      rtb_UnitConversion_a;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_k != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_j =
      rtb_UnitConversion_a;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator1' (':6363') */
  rtb_DiscreteTransferFcn_b =
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_j + (0.0025 *
    rtb_DiscreteTransferFcn_b);

  /* Gain: 'Gain9' (':6377') */
  rtb_Gain21 = 5.0 * rtb_UnitConversion;

  /* Gain: 'Gain4' (':6372') incorporates:
   *  Gain: 'Gain7' (':6375')
   *  Sum: 'Sum2' (':6382')
   */
  rtb_DiscreteTransferFcn = 150000.0 * (0.04 * (rtb_DiscreteTransferFcn_b -
    rtb_Gain21));

  /* Sum: 'Sum3' (':6383') */
  rtb_UnitConversion_k = rtb_Gain2_m - rtb_DiscreteTransferFcn;

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6362') */
  if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_n) !=
      0)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_f =
      rtb_UnitConversion_a;
  }

  if (rtb_LogicalOperator ||
      (Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_p != 0))
  {
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_f =
      rtb_UnitConversion_a;
  }

  /* DiscreteIntegrator: 'Discrete-Time Integrator' (':6362') */
  rtb_DiscreteTransferFcn_o =
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_f + (0.0025 *
    rtb_DiscreteTransferFcn_o);

  /* Gain: 'Gain1' (':6369') incorporates:
   *  Gain: 'Gain3' (':6371')
   *  Sum: 'Sum1' (':6381')
   */
  rtb_Gain21 = 150000.0 * (0.04 * (rtb_DiscreteTransferFcn_o - rtb_Gain21));

  /* Sum: 'Sum7' (':6386') */
  rtb_Gain2_m -= rtb_Gain21;

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6389:2') incorporates:
   *  Gain: 'Gain5' (':6373')
   *  Gain: 'Gain8' (':6376')
   *  Sum: 'Sum4' (':6384')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states = (5.0 * (0.95 *
    (rtb_Gain21 + rtb_DiscreteTransferFcn))) - (-0.99778579901470255 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator2' (':6364') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_IC_LOAD = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_DSTATE =
    rtb_UnitConversion;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator2_PrevRes = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6457:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g =
    rtb_MultiportSwitch13 - (-0.99843872006759038 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6434') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LOAD = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTATE = Align_Load_Pos;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevRes = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6388:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_o = rtb_Gain2_m -
    (-0.93534024285488582 *
     Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_o);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6387:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_a =
    rtb_UnitConversion_k - (-0.93534024285488582 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_a);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6456:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_i =
    rtb_DiscreteTransferFcn_f - (-0.9996154435878396 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_i);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6411:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g1 = rtb_Q_fedcm3s_a -
    (-0.53825375123805186 *
     Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g1);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5851:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_id =
    rtb_DiscreteTransferFcn_i - (-0.024722306790190128 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_id);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6809:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_e =
    rtb_Prssure_Limit_mc - (-0.99843872006759038 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_e);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator' (':6780') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOADI = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE = rtb_Gain10;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRese = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5909:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_d =
    rtb_DiscreteTransferFcn_g - (-0.024722306790190128 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_d);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6810:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_k = rtb_Prssure_Limit
    - (-0.99843872006759038 *
       Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_k);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6781') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_c = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_e = rtb_Gain11;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_d = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5875:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_n =
    rtb_DiscreteTransferFcn_l - (-0.024722306790190128 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_n);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6719:2') incorporates:
   *  Gain: 'Gain2' (':6818')
   *  Gain: 'Gain5' (':6707')
   *  Gain: 'Gain5' (':5869')
   *  Sum: 'Add1' (':6684')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_ip = ((0.0 - (0.0 *
    (25.0 * rtb_Gain10_b))) + (314.16 * rtb_Prssure_Limit_a)) -
    (-0.99843872006759038 *
     Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_ip);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator' (':6690') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_a = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_c = rtb_Gain10_b;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_b = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5933:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_m =
    rtb_DiscreteTransferFcn_a - (-0.024722306790190128 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_m);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6720:2') incorporates:
   *  Gain: 'Gain1' (':6817')
   *  Gain: 'Gain6' (':6708')
   *  Gain: 'Gain5' (':5927')
   *  Sum: 'Add2' (':6685')
   */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_h = ((314.16 *
    rtb_Prssure_Limit_l) - (0.0 * (25.0 * rtb_Gain11_l))) -
    (-0.99843872006759038 *
     Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_h);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6691') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_p = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_c = rtb_Gain11_l;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_g = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator' (':6433') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_e = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_n = rtb_Gain8;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_n = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':6412:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_hp =
    rtb_MultiportSwitch12 - (-0.85463599915323341 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_hp);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5934:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_oh =
    rtb_MultiportSwitch11 - (-0.99608070972816332 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_oh);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5876:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_m4 =
    rtb_MultiportSwitch10 - (-0.99608070972816332 *
    Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_m4);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5908:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g1m = Gain3_o -
    (-0.99608070972816332 *
     Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_g1m);

  /* Update for DiscreteTransferFcn: 'Discrete Transfer Fcn' (':5850:2') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_hf = Gain3_f -
    (-0.99608070972816332 *
     Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTransferFcn_states_hf);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator1' (':6363') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_IC_LO_n = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_DSTAT_j =
    rtb_DiscreteTransferFcn_b;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator1_PrevR_k = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);

  /* Update for DiscreteIntegrator: 'Discrete-Time Integrator' (':6362') */
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_IC_LOA_n = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_DSTATE_f =
    rtb_DiscreteTransferFcn_o;
  Lws_HilsCtrl_240218_v_1_0_DW.DiscreteTimeIntegrator_PrevRe_p = (int8_T)
    (rtb_LogicalOperator ? 1 : 0);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
