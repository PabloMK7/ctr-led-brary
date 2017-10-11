# ctr-led-brary
Small c++ library to play patterns with the 3DS RGB notification LED. This is only meant for developers, not an standalone homebrew app.
## Description
The 3DS notification led is a RGB led which can (theorically) display 2^24 (one byte for red, green and blue).
This library allows to play patterns using the ptm sysmodule which is 100% safe.
## LED patterns
The way the ptm sysmodule plays LED patterns is with the RGBLedPattern struct. This struct contains 32 RGB samples which are played sequentially and can be optionally looped. While all the RGB samples can be introduced manually by editing the struct, this library provides a generator to create multiple patterns. This is done using:
```LED::GeneratePattern(LED_Color color, LED_PatType type, float delay_time, float loop_delay, u8 smooth = 0, float r_shift = 0, float g_shift = 0, float b_shift = 0);```
 - ```LED_Color color```: The RGB color to be played by the LED. It can be passed using the LED_Color struct: 
   ```LED_Color(0xFF, 0x00, 0x00) // This is red```
   You can get color codes here: http://www.rapidtables.com/web/color/RGB_Color.htm
 - ```LED_PatType type```: Used to create color patterns. Read below for a complete description.
 - ```float delay_time```: The amount of seconds the pattern takes to play (this can range from 1/16th of a second to 16 seconds).
 - ```float loop_delay```: The amount of seconds the pattern waits before looping (this can range from 0 to 16 seconds). When the pattern is waiting, the latest RGB value is shown.
 - ```u8 smooth```: Smoothing applied to the resulting pattern. See here for a visual representation: https://imgur.com/ZxdPbIw
 - ```float r/g/b_shift```: Used to create color patterns. Read below for a complete description.
## Pattern Generation
The pattern generation method allows to create different kinds of patterns:
```LED_PatType::CONSTANT```: Generates a constant color with the same intensity over time.

## Credits
- MarcusD: Notification LED research.
- PabloMK7: Creation of the library.
- All the people involved in ctrulib.

## License
This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
