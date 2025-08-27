#include "Easing.h"



float EaseIn(float v1, float v2, float t) {

	float time = t * t * t;
	float v;
	v = static_cast<float>((1 - time) * v1 + time * v2);
	return v;
}

float EaseOut(float v1, float v2, float t) {
	float time = 1.0f - (1 - t) * (1 - t) * (1 - t);
	float v;
	v = static_cast<float>((1 - time) * v1 + time * v2);
	return v;
}