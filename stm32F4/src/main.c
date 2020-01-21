#include <stm32f4xx.h>
#include <arm_math.h>
#include <stm32f4_discovery.h>
#include <stm32f4_discovery_accelerometer.h>
#include <wolfson_pi_audio.h>
#include <diag/Trace.h>
#include <tests.h>
#include <dwt.h>
#include "filter.h"
#include "funcoes.h"
//#include "math_helper.h"

#undef DEPURAR
#undef WAH_PEDAL

int16_t TxBuffer[WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE];
int16_t RxBuffer[WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE];

__IO BUFFER_StateTypeDef buffer_offset = BUFFER_OFFSET_NONE;
__IO uint8_t Volume = 70;

uint32_t AcceleroTicks;
int16_t AcceleroAxis[3];


int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);

	float32_t inputF32Buffer[BLOCK_SIZE];
	float32_t outputF32Buffer[BLOCK_SIZE];
	float d = 0.05, f_min = 500, f_max = 3000, f_wah = 1000;
	uint32_t i, k;

	BSP_LED_Init(LED3);
	BSP_LED_Init(LED6);

	HAL_Init();
	DWT_Enable();

	WOLFSON_PI_AUDIO_Init((INPUT_DEVICE_LINE_IN << 8) | OUTPUT_DEVICE_BOTH, 80, AUDIO_FREQUENCY_48K);
	WOLFSON_PI_AUDIO_SetInputMode(INPUT_DEVICE_LINE_IN);
	WOLFSON_PI_AUDIO_SetMute(AUDIO_MUTE_ON);
	WOLFSON_PI_AUDIO_Play(TxBuffer, RxBuffer, WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE);
	WOLFSON_PI_AUDIO_SetVolume(Volume);

	BSP_ACCELERO_Init();
	TEST_Init();

#ifdef DEPURAR
	FILE * testOutput = fopen("testOutput.txt", "w");
	if (!testOutput) {
		trace_printf("Error trying to open file\n.");
		while(1);
	}
	FILE * fftOutput = fopen("fftOutput.txt", "w");
	if (!fftOutput) {
		trace_printf("Error trying to open file\n.");
		while(1);
	}
#endif

	// INICIALIZACOES
	wah_wah_init(d, f_min, f_max, f_wah);

	trace_printf("End of initialization.\n");

	while (1) {

		AcceleroTicks = HAL_GetTick();

		if(AcceleroAxis[1]<-200){
			BSP_LED_Off(LED3);
			BSP_LED_On(LED6);
		}else if(AcceleroAxis[1]>200){
			BSP_LED_On(LED3);
			BSP_LED_Off(LED6);
		}else{
			BSP_LED_Off(LED3);
			BSP_LED_Off(LED6);
		}
#ifdef WAH_PEDAL
		if((AcceleroTicks%1) == 0)
		{
#else
		if((AcceleroTicks%500) == 0)
		{
#endif
			BSP_ACCELERO_GetXYZ(AcceleroAxis);

			if(AcceleroAxis[1]<-200)
			{
#ifdef WAH_PEDAL
				set_freq_wah(get_freq_wah()-get_wah_delta());
#else
				f_wah = f_wah - 10;
				if(f_wah <= f_min)
					f_wah = f_min;
				set_wah_delta(f_wah);
#endif
				//Volume = (Volume == 0)?Volume:(Volume -1);
				//WOLFSON_PI_AUDIO_SetVolume((uint8_t) Volume);
			}

			if(AcceleroAxis[1]>200)
			{
#ifdef WAH_PEDAL
				set_freq_wah(get_freq_wah()+get_wah_delta());
#else
				f_wah = f_wah + 10;
				if(f_wah >= f_max)
					f_wah = f_max;
				set_wah_delta(f_wah);
				//Volume = (Volume == 80)?Volume:(Volume + 1);
				//WOLFSON_PI_AUDIO_SetVolume((uint8_t) Volume);
#endif
			}
		}

		if(buffer_offset == BUFFER_OFFSET_HALF)
		{
			for(i=0, k=0; i<(WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE/2); i++) {
				if(i%2) {
					inputF32Buffer[k] = (float32_t)(RxBuffer[i]/32768.0); // float LEFT
					k++;
				}
				else {
					TxBuffer[i] = RxBuffer[i]; //RIGHT
				}
			}
#ifdef WAH_PEDAL
			wah_wah_pedal(inputF32Buffer, outputF32Buffer);
#else
			auto_wah_wah(inputF32Buffer, outputF32Buffer);
#endif
			for(i=0, k=0; i<(WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE/2); i++) {
				if(i%2)	{
					TxBuffer[i] = (int16_t)(outputF32Buffer[k]*32768);
					k++;
				}else{
					TxBuffer[i] = (int16_t)(outputF32Buffer[k]*32768);
				}
			}

			buffer_offset = BUFFER_OFFSET_NONE;
		}

		if(buffer_offset == BUFFER_OFFSET_FULL)
		{
			for(i=(WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE/2), k=0; i<WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE; i++) {
				if(i%2) {
					inputF32Buffer[k] = (float32_t)(RxBuffer[i]/32768.0); // float
					k++;
				}
				else {
					TxBuffer[i] = RxBuffer[i];
				}
			}
#ifdef WAH_PEDAL
			wah_wah_pedal(inputF32Buffer, outputF32Buffer);
#else
			auto_wah_wah(inputF32Buffer, outputF32Buffer);
#endif
			for(i=(WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE/2), k=0; i<WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE; i++) {
				if(i%2)	{
					TxBuffer[i] = (int16_t)(outputF32Buffer[k]*32768);
					k++;
				}else{
					TxBuffer[i] = (int16_t)(outputF32Buffer[k]*32768);
				}
			}

			buffer_offset = BUFFER_OFFSET_NONE;
		}

		TEST_Main();

#ifdef DEPURAR
		for(k=0; k<SINALSIZE; k++){
			fprintf(testOutput, "%f, ", inputF32s[k]);
		}
		fseek(testOutput, 0, SEEK_SET);
		fclose(testOutput);
#endif

	}
	return 0;
}

/*--------------------------------
Callbacks implementation:
--------------------------------------------------------*/

/**
  * @brief  Manages the DMA full Transfer complete event.
  */
void WOLFSON_PI_AUDIO_TransferComplete_CallBack(void)
{
	buffer_offset = BUFFER_OFFSET_FULL;
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  */
void WOLFSON_PI_AUDIO_HalfTransfer_CallBack(void)
{
	  buffer_offset = BUFFER_OFFSET_HALF;
}

/**
  * @brief  Manages the DMA FIFO error interrupt.
  * @param  None
  * @retval None
  */
void WOLFSON_PI_AUDIO_OUT_Error_CallBack(void)
{
  /* Stop the program with an infinite loop */
  while (1);
}
