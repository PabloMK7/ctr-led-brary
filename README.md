# ctr-led-brary
Small c++ library to play patterns with the 3DS RGB notification LED. This is only meant for developers, not an standalone homebrew app.
## Description
The 3DS notification led is a RGB led which can (theorically) display 2^24 (one byte for red, green and blue).
This library allows to play patterns using the ptm sysmodule which is 100% safe.
## LED patterns
First of all you'll have to generate a RGBLedpattern. This is done using:
```LED::GeneratePattern(LED_Color color, LED_PatType type, float delay_time, float loop_delay, u8 smooth = 0, float r_shift = 0, float g_shift = 0, float b_shift = 0);```
 - LED_Color color: The RGB color to be played by the LED. It can be passed using the LED_Color struct: 
   ```LED_Color(0xFF, 0x00, 0x00) // This is red```
   You can get color codes here: http://www.rapidtables.com/web/color/RGB_Color.htm
 - LED_PatType type: Used to create color patterns. Read below for a complete description.
 - float delay_time: The amount of seconds the pattern takes to play (this can range from 1/16th of a second to 16 seconds).
 - float loop_delay: The amount of seconds the pattern waits before looping (this can range from 0 to 16 seconds). When the pattern is        waiting, the latest RGB value is shown.
 - u8 smooth: Smoothing applied to the resulting pattern. See here for a visual representation: https://imgur.com/ZxdPbIw
 - float r/g/b_shift: Used to create color patterns. Read below for a complete description.
