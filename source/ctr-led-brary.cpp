#include "ctr-led-brary.hpp"
#include <3ds.h>
#include "math.h"
#include "string.h"


Handle ptmsysmHandle = 0;
bool SecureLock = false;

bool LED::IsPatternPlaying() {
	return SecureLock;
}

Result LED::Play(RGBLedPattern pat) {
	u32* ipc = getThreadCommandBuffer();
    ipc[0] = 0x8010640;
    memcpy(&ipc[1], &pat, 0x64);
    Result ret = svcSendSyncRequest(ptmsysmHandle);
    if(ret < 0) return ret;
    return ipc[1];
}

Result LED::Init() {
	if (ptmsysmHandle != 0) {
		return 0;
	}
	srvInit();
	Result res = srvGetServiceHandle(&ptmsysmHandle, "ptm:sysm");
	srvExit();
	return res;
}

bool LED::PlayLEDPattern(RGBLedPattern pattern) {
	if (IsPatternPlaying()) return false;
	pattern.unknown1 = 0;
	if (Init() < 0) return false;
	if (Play(pattern) < 0) return false;
	SecureLock = true;
	return true;
}

bool LED::SwitchLEDPattern(RGBLedPattern pattern) {
	if (!IsPatternPlaying()) return false;
	pattern.unknown1 = 0;
	if (Init() < 0) return false;
	if (Play(pattern) < 0) return false;
	SecureLock = true;
	return true;
}

bool LED::StopLEDPattern() {
	if (!IsPatternPlaying()) return false;
	RGBLedPattern pat = {0};
	if (Init() < 0) return false;
	if (Play(pat) < 0) return false;
	SecureLock = false;
	return true;
}

RGBLedPattern LED::GeneratePattern(LED_Color color, LED_PatType type, float delay_time, float loop_delay, u8 smooth, float r_shift, float g_shift, float b_shift) {
	RGBLedPattern pat = {0};

	pat.unknown1 = 0;

	float tempVal = delay_time * 0x10;
	if (tempVal >= 0x100) tempVal = 0xFF;
	pat.delay = (u8)tempVal;

	pat.smooth = (u8) smooth;

	tempVal = loop_delay * 0x10;
	if (tempVal >= 0x100) tempVal = 0xFF;
	pat.loop_delay = (u8)tempVal;

	float x, xr, xg, xb, dummy;
	switch(type) {
		case LED_PatType::WAVE_DESC:			
			for(int i = 0; i < 32; i++) {
				x = ((float)i/31) * 2*M_PI;
				pat.r[i] = ((cos(x + (2*M_PI * modf(r_shift, &dummy))) + 1) / 2) * color.r;
				pat.g[i] = ((cos(x + (2*M_PI * modf(g_shift, &dummy))) + 1) / 2) * color.g;
				pat.b[i] = ((cos(x + (2*M_PI * modf(b_shift, &dummy))) + 1) / 2) * color.b;
			}
			break;
		case LED_PatType::WAVE_ASC:
			for(int i = 0; i < 32; i++) {
				x = ((float)i/31) * 2*M_PI;
				pat.r[i] = ((cos(x + (2*M_PI * modf(r_shift, &dummy)) + M_PI) + 1) / 2) * color.r;
				pat.g[i] = ((cos(x + (2*M_PI * modf(g_shift, &dummy)) + M_PI) + 1) / 2) * color.g;
				pat.b[i] = ((cos(x + (2*M_PI * modf(b_shift, &dummy)) + M_PI) + 1) / 2) * color.b;
			}
			break;
		case LED_PatType::ASCENDENT:
			for(int i = 0; i < 32; i++) {
				xr = modf((float)i/32 + r_shift, &dummy);
				xg = modf((float)i/32 + g_shift, &dummy);
				xb = modf((float)i/32 + b_shift, &dummy);
				pat.r[i] = (u8)(xr * color.r);
				pat.g[i] = (u8)(xg * color.g);
				pat.b[i] = (u8)(xb * color.b);
			}
			break;
		case LED_PatType::DESCENDENT:
			for(int i = 0; i < 32; i++) {
				xr = 1 - modf((float)i/32 + r_shift, &dummy);
				xg = 1 - modf((float)i/32 + g_shift, &dummy);
				xb = 1 - modf((float)i/32 + b_shift, &dummy);
				pat.r[i] = (u8)(xr * color.r);
				pat.g[i] = (u8)(xg * color.g);
				pat.b[i] = (u8)(xb * color.b);
			}
			break;
		case LED_PatType::CONSTANT:
		default:
			for(int i = 0; i < 32; i++) {
				pat.r[i] = color.r;
				pat.g[i] = color.g;
				pat.b[i] = color.b;
			}
			break;
	}
	return pat;
}
