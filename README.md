# ctr-led-brary
Small c++ library to play patterns with the 3DS RGB notification LED. This is only meant for developers, not an standalone homebrew app.

## Description
The 3DS notification led is a RGB256 led which can (theorically) display 2^24 different colors (including black).
This library allows to play patterns using the ptm sysmodule. Read below for an explanation of how the library works.

## LED Patterns
The way the ptm sysmodule plays LED patterns is with the RGBLedPattern struct. This struct contains 32 RGB256 samples (three bytes each for red, green and blue) which are played sequentially and can be optionally looped. Additionally, it holds the amount of time the whole pattern takes to be played, a smooth value, the amount of time between loops and an unknown value (?) all of them stored in one byte each (https://3dbrew.org/wiki/MCURTC:SetInfoLEDPattern). While all the RGB samples can be introduced manually by editing the struct, this library provides a generator to create multiple pattern types. This is done using the pattern generation method: ```LED::GeneratePattern(LED_Color color, LED_PatType type, float delay_time, float loop_delay, u8 smooth = 0, float r_shift = 0, float g_shift = 0, float b_shift = 0);```
 - ```LED_Color color```: The RGB color to be played by the LED. It can be passed using the LED_Color struct, for example the color red would be: 
   ```LED_Color(0xFF, 0x00, 0x00)```. You can get color codes here: http://www.rapidtables.com/web/color/RGB_Color.htm
 - ```LED_PatType type```: Used to generate color patterns. Read below for a complete description.
 - ```float delay_time```: The amount of seconds the pattern takes to play (this can range from 1/16th of a second to 16 seconds).
 Setting the value to zero equals setting the value to 16.
 - ```float loop_delay```: The amount of seconds the pattern waits between each loop (this can range from 0 to 16 seconds). When the pattern is waiting, the latest RGB sample is displayed until it loops again. Set this to a value bigger than 16 to make the pattern loop only once.
 - ```u8 smooth```: Smoothing applied to the resulting pattern. See here for a visual representation: https://imgur.com/ZxdPbIw
 - ```float r/g/b_shift```: Used to generate color patterns. Read below for a complete description.
 
## Pattern Generation
The pattern generation method allows to create different kinds of patterns:
 - ```LED_PatType::CONSTANT```: Generates a color pattern with the same intensity over time.
 - ```LED_PatType::ASCENDENT```: Generates a linear color pattern increasing in intensity over time. When looped, it generates a sawtooth wave.
 - ```LED_PatType::DESCENDENT```: Generates a linear color pattern decreasing in intensity over time. When looped, it generates an inverted sawtooth wave.
 - ```LED_PatType::WAVE_ASC```: Generates a sinusoidal oscillation starting from intensity zero. When looped, it generates a sinus wave.
 - ```LED_PatType::WAVE_DESC```: Generates a sinusoidal oscillation starting from max intensity. When looped, it generates a sinus wave.

The method also has three optional parameters, ```r_shift```,```g_shift```,```b_shift```. Those parameters are used to shift the individual RGB channels a certain amount (this means more or less that the value in each channel sample is moved to the next sample a certain amount, shifting the whole pattern. Internally, this process is made in another way to increase the precision). The shift value has to between 0 and 1, being 1 a whole shift (in the case the value is bigger than 1, only the decimal part will be used). The shift value can be applied to any pattern type (however, applying a shift to ```LED_PatType::CONSTANT``` has no effect). The shifting operation is useful for generating patterns with more than one color (see patterns 6 and 7 in the example).

## Pattern Playing
After a pattern has been generated, it can be played using: ```LED::PlayLEDPattern(RGBLedPattern pattern);```. To stop the current playing pattern use: ```LED::StopLEDPattern();```. It's up to the user to handle the amount of time the pattern is played and when to stop it as it will loop infinitely until Stop is called (or will be played once keeping the last color sample if ```loop_delay``` is bigger than 16). To inmediately switch between patterns use ```LED::SwitchLEDPattern(RGBLedPattern pattern);``` this method needs a pattern to be already playing.

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
