#include "funcoes.h"

volatile wah_t wah_var;
volatile float fs = 48000;

void wah_wah_init(float d, float f_min, float f_max, float f_wah){

	wah_var.q1 = 2*d;

	if(f_min < f_max)
		wah_var.freq_min = f_min;
	else
		wah_var.freq_min = 0;

	if(f_max < (fs/2))
		wah_var.freq_max = f_max;
	else
		wah_var.freq_max = fs/2;

	if(f_wah < (fs/2))
		wah_var.delta = f_wah/fs;
	else
		wah_var.delta = fs/2;

	wah_var.freq_central = f_max/2;

}

void set_damp(float d){
	wah_var.q1 = 2*d;
}

void set_freq_min(float f_min){
	wah_var.freq_min = f_min;
}

void set_freq_max(float f_max){
	wah_var.freq_max = f_max;
}

void set_wah_delta(float f_wah){
	if(f_wah < (fs/2))
		wah_var.delta = f_wah/fs;
}

void set_freq_wah(float fc){
	if((fc <= wah_var.freq_max) && (fc >= wah_var.freq_min))
		wah_var.freq_central = fc;
}

float get_wah_delta(){
	return wah_var.delta;
}

float get_freq_wah(){
	return wah_var.freq_central;
}

void auto_wah_wah(float32_t* audio, float32_t* yb){

	static float f1;
	static int up_down = 0;
	static float32_t yh[BLOCK_SIZE];
	static float32_t yl[BLOCK_SIZE];
	static float32_t yb_anterior;
	uint32_t i;

	if(wah_var.freq_central == 0)
		wah_var.freq_central = wah_var.freq_min;

	yb[0] = yb_anterior;

	for(i = 1; i < BLOCK_SIZE; i++){
		yh[i] = audio[i] - yl[i-1] - wah_var.q1*yb[i-1];
		yb[i] = f1*yh[i] + yb[i-1];
		yl[i] = f1*yb[i] + yl[i-1];

		if(wah_var.freq_central >= wah_var.freq_max)
			up_down = 1;
		else if(wah_var.freq_central <= wah_var.freq_min)
			up_down = 0;

		if(up_down == 0)
			wah_var.freq_central = wah_var.freq_central + wah_var.delta;
		else if(up_down == 1)
			wah_var.freq_central = wah_var.freq_central - wah_var.delta;

		f1 = 2*sin((M_PI*wah_var.freq_central)/fs);

	}

	yh[0] = yh[BLOCK_SIZE-1];
	yb_anterior = yb[BLOCK_SIZE-1];
	yl[0] = yl[BLOCK_SIZE-1];

}

void wah_wah_pedal(float32_t* audio, float32_t* yb){

	static float f1;
	static float32_t yh[BLOCK_SIZE];
	static float32_t yl[BLOCK_SIZE];
	static float32_t yb_anterior;
	uint32_t i;

	f1 = 2*sin((M_PI*wah_var.freq_central)/fs);

	yb[0] = yb_anterior;

	for(i = 1; i < BLOCK_SIZE; i++){
		yh[i] = audio[i] - yl[i-1] - wah_var.q1*yb[i-1];
		yb[i] = f1*yh[i] + yb[i-1];
		yl[i] = f1*yb[i] + yl[i-1];
	}

	yh[0] = yh[BLOCK_SIZE-1];
	yb_anterior = yb[BLOCK_SIZE-1];
	yl[0] = yl[BLOCK_SIZE-1];

}
