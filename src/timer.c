#include "ggl.h"
#include "timer.h"

//#define MS_PER_FRAME	16	// ~60fps
#define MS_PER_FRAME	33	// ~30fps

uint32_t frame_times[99];
uint64_t current_frame = 0;
uint32_t sleep_times[99];

void ggl_calculate_fps(uint32_t elapsed)
{
	float fps = 0.0f;
	float avg_sleep = 0.0f;

	if (current_frame++ < 100)
	{
		frame_times[current_frame % 99] = elapsed;
		return;
	}

	frame_times[current_frame % 99] = elapsed;

	if (current_frame % 100 == 0) {

		float total_sum = 0.0f;
		float sleep_sum = 0.0f;
		for (int i = 0; i < 99; i++)
		{
			total_sum += frame_times[i];
			sleep_sum += sleep_times[i];
		}

		total_sum /= 100.0f;
		avg_sleep = sleep_sum / 100.0f;

		fps = (total_sum > 0) ? 1000.0f / total_sum : 1001.0f;

		debug("fps = %f, average sleep = %f", fps, avg_sleep);
	}
}

void ggl_limit_fps(uint32_t start)
{
	uint32_t difference = SDL_GetTicks() - start;
	if (difference > 0 && difference < MS_PER_FRAME)
	{
		uint32_t t = MS_PER_FRAME - difference;
		sleep_times[current_frame % 99] = t;
		_sleep(t);
	}
}