# ctr-led-brary
Small c++ library to play patterns with the 3DS RGB notification LED. This is only meant for developers, not an standalone homebrew app.

## Description
The 3DS notification led is a RGB led which can (theorically) display 2^24 (one byte for red, green and blue).
This library allows to play patterns using the ptm sysmodule.

## LED patterns
The way the ptm sysmodule plays LED patterns is with the RGBLedPattern struct. This struct contains 32 RGB samples which are played sequentially and can be optionally looped. Additionally, it holds a delay time, smooth value, loop delay time and unknown value (?) all of them stored in one byte each (https://3dbrew.org/wiki/MCURTC:SetInfoLEDPattern). While all the RGB samples can be introduced manually by editing the struct, this library provides a generator to create multiple patterns. This is done using:
```LED::GeneratePattern(LED_Color color, LED_PatType type, float delay_time, float loop_delay, u8 smooth = 0, float r_shift = 0, float g_shift = 0, float b_shift = 0);```
 - ```LED_Color color```: The RGB color to be played by the LED. It can be passed using the LED_Color struct: 
   ```LED_Color(0xFF, 0x00, 0x00) //Red```
   You can get color codes here: http://www.rapidtables.com/web/color/RGB_Color.htm
 - ```LED_PatType type```: Used to create color patterns. Read below for a complete description.
 - ```float delay_time```: The amount of seconds the pattern takes to play (this can range from 1/16th of a second to 16 seconds).
 Setting the value to zero equals setting the value to 16.
 - ```float loop_delay```: The amount of seconds the pattern waits before looping (this can range from 0 to 16 seconds). When the pattern is waiting, the latest RGB value is kept displaying. Set this value to a value bigger than 16 to make the pattern loop only once.
 - ```u8 smooth```: Smoothing applied to the resulting pattern. See here for a visual representation: https://imgur.com/ZxdPbIw
 - ```float r/g/b_shift```: Used to create color patterns. Read below for a complete description.
 
## Pattern Generation
The pattern generation method allows to create different kinds of patterns:
 - ```LED_PatType::CONSTANT```: Generates a color pattern with the same intensity over time.
 - ```LED_PatType::ASCENDENT```: Generates a linear color pattern increasing in intensity over time. When looped, it generates a sawtooth wave.
 - ```LED_PatType::DESCENDENT```: Generates a linear color pattern decreasing in intensity over time. When looped, it generates an inverted sawtooth wave.
 - ```LED_PatType::WAVE_ASC```: Generates a sinusoidal oscillation starting from intensity zero. When looped, it generates a sinus wave.
 - ```LED_PatType::WAVE_DESC```: Generates a sinusoidal oscillation starting from max intensity. When looped, it generates a sinus wave.
The method also have three optional parameters, ```r_shift```,```g_shift```,```b_shift```. Those parameters are used to shift the individual RGB channels a certain amount (this more or less means, the value in each channel byte is moved to the next byte, shifting the whole pattern). The shift value has to be passed in radians, 2π radians being a whole shift. The shift value can be applied to any pattern type (however, applying a shift to ```LED_PatType::CONSTANT``` has no effect). The shifting operation is useful for generating patterns with more than one color.

## Pattern Playing
After a pattern has been generated, it can be played using: ```LED::PlayLEDPattern(RGBLedPattern pattern);```. To stop the current playing pattern use: ```LED::StopLEDPattern();```. It's up to the user to handle the amount of time the pattern is played and when to stop it. The pattern will infinitely play until Stop is called (or will be played once keeping the last color sample if ```loop_delay``` is bigger than 16). To inmediately switch between patterns use ```LED::SwitchLEDPattern(RGBLedPattern pattern);```

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
