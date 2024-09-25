/*
 * LTC2668.c
 *
 *  Created on: 2022. 8. 31.
 *      Author: hgson
 */

/*!
LTC2668: 16-Channel SPI 16-/12-Bit +/-10V Vout SoftSpan DACs with 10ppm/C Max Reference

@verbatim

The LTC2668 is a family of 16-channel, 12/16-bit +/-10V digital-to-analog converters with integrated
precision references. They are guaranteed monotonic and have built-in rail-to-rail output buffers.
These SoftSpan DACs offer five output ranges up to +/-10V. The range of each channel is independently
programmable, or the part can be hardware-configured for operation in a fixed range.

@endverbatim

http://www.linear.com/product/LTC2668

http://www.linear.com/product/LTC2668#demoboards

REVISION HISTORY
$Revision: 5079 $
$Date: 2016-05-10 09:25:00 -0700 (Tue, 10 May 2016) $

Copyright (c) 2013, Linear Technology Corp.(LTC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Linear Technology Corp.

The Linear Technology Linduino is not affiliated with the official Arduino team.
However, the Linduino is only possible because of the Arduino team's commitment
to the open-source community.  Please, visit http://www.arduino.cc and
http://store.arduino.cc , and consider a purchase that will help fund their
ongoing work.
*/

//! @defgroup LTC2668 LTC2668 16-Channel SPI 16-/12-Bit +/-10V Vout SoftSpan DACs with 10ppm/C Max Reference

/*! @file
    @ingroup LTC2668
    LTC2668 16-Channel SPI 16-/12-Bit +/-10V Vout SoftSpan DACs with 10ppm/C Max Reference
*/
#include "main.h"
#include <stdint.h>
#include <math.h>
#include <../Source/DAC/LTC2668.h>

/* Private variables ---------------------------------------------------------*/
extern SPI_HandleTypeDef hspi4;
_LTC2668 LTC2668;

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
void FUN_DAC_SPI4_Init(void)
{
	SPI4_LDAC_LOW();
	SPI4_CLR_HIGH();
}

// -10 ~ 10 V 범위
// 사용 범위 : 0 ~ -10V
// 적용  : 0 ~ -10 V => 0 ~ 20mA

/****************************************************************************/
/*	Overview	:	get DAC_CODE / Transmit									*/
/*	Return value:	void													*/
/****************************************************************************/
// 입력 값 미정. uint16_t u2t_dac_volt
// 변환 값 미정. float ft_volatge
// u1t_dac_address : DAC_SPI4.h - DAC Adresss n 참조
void FUN_DAC_LTC2668_Get_Dac_Code(uint8_t SPI_Select, uint8_t u1t_dac_address, float ft_dac_volt)
{
	uint16_t LTC2668_VoltToCode = 0;

	// 변환 수식 이후 수정 필요!
	// Volatge = 5.000V 형식
	// dac_volt = 현재 알 수 없음.

	// ft_volatge : 실수형이 전압값 입력.
	// MIN : 0 / MAX : 5
	// 출력 값 : u2t_dac_code 해당 전압의 code로 출력
	LTC2668_VoltToCode = LTC2668_voltage_to_code(ft_dac_volt, DAC4_MIN_OUTPUT, DAC4_MAX_OUTPUT);

	// DAC IC에 전송
	// command : LTC2666_CMD_WRITE_N_UPDATE_N - 해당 채널에 쓰기와 업데이트 동시 실행 명령어
	LTC2668.SPI4_ReceiveCheck_flag = LTC2668_write(SPI_4, LTC2668_CMD_WRITE_N_UPDATE_N, u1t_dac_address, LTC2668_VoltToCode);
}

/****************************************************************************/
/*	Overview	:															*/
/*	Return value:	void													*/
/****************************************************************************/
int8_t LTC2668_write(uint8_t SPI_Select, uint8_t dac_command, uint8_t dac_address, uint16_t dac_code)
// Write the 16-bit dac_code to the LTC2668
{
  static uint8_t SPI4_last_data_array[4];
  uint8_t data_array[4], rx_array[4];
  int8_t ret;
  uint16_t data;

  data = dac_code;                              // Copy DAC code to union
  data_array[0] = 0;                                     // Only required for 32 byte readback transaction
  data_array[1] = dac_command | dac_address;             // Build command / address byte
  data_array[2] = (uint8_t)(data >> 8);          // MS Byte
  data_array[3] = (uint8_t)(data & 0xFF);        // LS Byte

  if(SPI_Select == SPI_4)
  {
  	// SPI4 Data 전송 준비
	SPI4_NSS_Enable();
	// SPI4 Data 전송
	HAL_SPI_TransmitReceive(&hspi4, data_array, rx_array,  (uint8_t) 4, 10);
	// 데이터 송수신 확인
	while(HAL_SPI_GetState(&hspi4) != HAL_SPI_STATE_READY)
	{

	}
	// 데이터 송수신 완료 후 종료
	SPI4_NSS_Disable();

	// 이전 전송 데이터와 수신 데이터의 비교
	// Compare data read back to data that was sent the previous time this function was called
	if ((rx_array[2] == SPI4_last_data_array[2]) && (rx_array[1] == SPI4_last_data_array[1]) && (rx_array[0] == SPI4_last_data_array[0]))
	{
	  ret = 0;
	}
	else
	{
	  ret = 1;
	}

	SPI4_last_data_array[0] = data_array[0]; // Copy data array to a static array to compare
	SPI4_last_data_array[1] = data_array[1]; // the next time the function is called
	SPI4_last_data_array[2] = data_array[2];
  }
  else
  {
	  ret = 1;
  }

  // 비교 결과 리턴	0 : 정상 / 1 : 비정상
  return(ret);
}

/****************************************************************************/
/*	Overview	:	voltage to code											*/
/*	Return value:	uint16_t	전압값 코드로 리턴								*/
/****************************************************************************/
// Calculate a LTC2666 DAC code given the desired output voltage and the minimum / maximum
// outputs for a given softspan range.
// min_output = 0V
// max_output = 5V
uint16_t LTC2668_voltage_to_code(float dac_voltage, float min_output, float max_output)
{
  uint16_t dac_code;
  float float_code;
  float_code = 65535.0 * (dac_voltage - min_output) / (max_output - min_output);                    // Calculate the DAC code
  float_code = (float_code > (floor(float_code) + 0.5)) ? ceil(float_code) : floor(float_code);     // Round
  if (float_code < 0.0) float_code = 0.0;
  if (float_code > 65535.0) float_code = 65535.0;
  dac_code = (uint16_t) (float_code);                                                               // Convert to unsigned integer
  return (dac_code);
}

/****************************************************************************/
/*	Overview	:	code to voltage											*/
/*	Return value:	float	실수 범위의 전압 리턴									*/
/****************************************************************************/
// Calculate the LTC2666 DAC output voltage given the DAC code and and the minimum / maximum
// outputs for a given softspan range.
// min_output = 0V
// max_output = 5V
float LTC2668_code_to_voltage(uint16_t dac_code, float min_output, float max_output)
{
  float dac_voltage;
  dac_voltage = (((float) dac_code / 65535.0) * (max_output - min_output)) + min_output;            // Calculate the dac_voltage
  return (dac_voltage);
}
