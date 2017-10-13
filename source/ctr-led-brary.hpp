
#include <3ds.h>


typedef struct 
{
	u8 delay;
	u8 smooth;
	u8 loop_delay;
	u8 unknown1;	
    u8 r[32];
    u8 g[32];
    u8 b[32];
} RGBLedPattern;

class LED_Color
{
	public:
		u8 r;
		u8 g;
		u8 b;
		LED_Color(u8 r1, u8 g1, u8 b1) {
			r = r1;
			g = g1;
			b = b1;
		}
};

enum class LED_PatType
{
	CONSTANT = 0, // Constant
	DESCENDENT = 1, // linear down
	ASCENDENT = 2, // linear up
	WAVE_ASC = 3, // sine wave up
	WAVE_DESC = 4, // sine wave down
};

class LED {
	private:
		static Result Init();
		static Result Play(RGBLedPattern pattern);
	public:
		// Returns true if pattern is playing, false otherwise.
		static bool IsPatternPlaying();
		// Plays a generated pattern, returns true if played successfully.
		static bool PlayLEDPattern(RGBLedPattern pattern);
		// Switches the current playing pattern in no time, returns true if switched successfully.
		static bool SwitchLEDPattern(RGBLedPattern pattern);
		// Stops any playing pattern, returns true if stopped successfully.
		static bool StopLEDPattern();
		// Generates a Led Pattern, only one led pattern can be played at the same.
		static RGBLedPattern GeneratePattern(LED_Color color, LED_PatType type, float delay_time, float loop_delay, u8 smooth = 0, float r_shift = 0, float g_shift = 0, float b_shift = 0);
};
