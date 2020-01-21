#ifndef NOKIA5110_H_
#define NOKIA5110_H_

#include <stm32f4xx.h>
#include <arm_math.h>
#include <stm32f4_discovery.h>
#include <stm32f4_discovery_accelerometer.h>
#include <wolfson_pi_audio.h>
#include <diag/Trace.h>
#include <tests.h>
#include <dwt.h>
#include "filter.h"

#define BLOCK_SIZE (WOLFSON_PI_AUDIO_TXRX_BUFFER_SIZE)/4

typedef struct wah_t
{
	float q1;
	float freq_min;
	float freq_max;
	float delta;
	float freq_central;
} wah_t;

void wah_wah_init(float d, float f_min, float f_max, float f_wah);
void set_damp(float d);
void set_freq_min(float f_min);
void set_freq_max(float f_max);
void set_wah_delta(float f_wah);
void set_freq_wah(float fc);
float get_wah_delta();
float get_freq_wah();
void auto_wah_wah(float32_t* audio, float32_t* yb);
void wah_wah_pedal(float32_t* audio, float32_t* yb);

#endif
