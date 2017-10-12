#include <3ds.h>
#include <stdio.h>
#include "math.h"
#include "ctr-led-brary.hpp"

void updateScreens() {
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
		//Wait for VBlank
		gspWaitForVBlank();
}

void displayinfo(int d, int sec) {
	int dispSec = 0;
	while (true) {
		consoleClear();
		printf("Playing pattern: %d\nTime: %d seconds.\n\n\nHold START to exit.", d, dispSec);
		svcSleepThread(1000000000);
		hidScanInput();
		dispSec++;
		if (dispSec >= sec) return;
		if (hidKeysDown() & KEY_START) return;
		updateScreens();
	}
}

int main(int argc, char **argv)
{
	gfxInitDefault();

	consoleInit(GFX_TOP, NULL);

	int currpat = 1;
	int playtime = 10;
	bool changed = true;

	// pattern1: Constant color white, pattern delay 1 second, no loop time.
	RGBLedPattern pattern1 = LED::GeneratePattern(LED_Color(0xFF, 0xFF, 0xFF), LED_PatType::CONSTANT, 1, 0);

	// pattern2: Descending color gold, pattern delay 2 seconds, no loop time, smooth 0x50.
	RGBLedPattern pattern2 = LED::GeneratePattern(LED_Color(0xB2, 0x96, 0x00), LED_PatType::DESCENDENT, 2, 0, 0x50);

	// pattern3: Ascending color blue, pattern delay 2 seconds, loop delay 2 seconds, smooth 0x2A.
	RGBLedPattern pattern3 = LED::GeneratePattern(LED_Color(0x00, 0x00, 0xFF), LED_PatType::ASCENDENT, 2, 2, 0x2A);

	// pattern4: Sinus color green, pattern delay 3 seconds, no loop time, smooth 0x10.
	RGBLedPattern pattern4 = LED::GeneratePattern(LED_Color(0x00, 0xFF, 0x00), LED_PatType::WAVE_DESC, 3, 0, 0x10);

	// pattern5: Ascending color cyan, pattern delay 1 second, 1 second loop time.
	RGBLedPattern pattern5 = LED::GeneratePattern(LED_Color(0x00, 0xFF, 0xFF), LED_PatType::WAVE_ASC, 1, 1);

	// pattern6: Wave color purple, pattern delay 2 second, no loop time. Using shift values (shifting blue channel half way: M_PI), we can get a blue -> purple -> red pattern.
	RGBLedPattern pattern6 = LED::GeneratePattern(LED_Color(0xFF, 0x00, 0xFF), LED_PatType::WAVE_ASC, 2, 0, 0, 0, 0, 0.5);

	// pattern7: Wave color grey shade(the green has less intensity, so we give it a bigger value), pattern delay 3 second, no loop time. Using shift values (shifting each channel one third of the other), we can get a rainbow pattern. :3
	RGBLedPattern pattern7 = LED::GeneratePattern(LED_Color(0xFF, 0xFF, 0xFF), LED_PatType::WAVE_DESC, 4, 0, 0x10, 0, 2.0/3, 1.0/3);
	
	// Main loop
	while (aptMainLoop())
	{
		svcSleepThread(100000000);
		if (changed) {
			consoleClear();
			printf("ctr-led-brary example.\n\nSelected: %d.\nPlay time: %d seconds.\n\n\nPress A to play the selected pattern.\nPress UP/DOWN to change the pattern.\nPress LEFT/RIGHT to change the play time.\nPress B to exit.", currpat, playtime);
			changed = false;
		}
		hidScanInput();
		u32 kdown = hidKeysDown();
		if (kdown & KEY_UP) {
			if (currpat >= 7) currpat = 1;
			else currpat++;
			changed = true;
		}
		if (kdown & KEY_DOWN) {
			if (currpat <=1) currpat = 7;
			else currpat--;
			changed = true;
		}
		if (kdown & KEY_RIGHT) {
			if(playtime >= 12) playtime = 1;
			else playtime++;
			changed = true;
		}
		if (kdown & KEY_LEFT) {
			if (playtime <= 1) playtime = 12;
			else playtime--;
			changed = true;
		}
		if (kdown & KEY_A) {
			switch(currpat) {
				case 1:
					LED::PlayLEDPattern(pattern1);
					break;
				case 2:
					LED::PlayLEDPattern(pattern2);
					break;
				case 3:
					LED::PlayLEDPattern(pattern3);
					break;
				case 4:
					LED::PlayLEDPattern(pattern4);
					break;
				case 5:
					LED::PlayLEDPattern(pattern5);
					break;
				case 6:
					LED::PlayLEDPattern(pattern6);
					break;
				case 7:
					LED::PlayLEDPattern(pattern7);
					break;
			}
			displayinfo(currpat, playtime);
			LED::StopLEDPattern();
			changed = true;
		}
		if (kdown & KEY_B) {
			break;
		}
		updateScreens();
	}

	gfxExit();
	return 0;
}
