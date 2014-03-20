IRTranslator
============

Simple code to translate one IR signal to another, using a receiver and an emitter in arduino

How to use it
============

This simple program uses the Arduino-IRremote that you can download from here: https://github.com/shirriff/Arduino-IRremote/

**The hookup of the infrared receiver:**

In my case i used a VS1838B, but you can find here several diagrams of receivers to know are each pin: http://arduino-info.wikispaces.com/IR-RemoteControl

Connect the OUT in the PWN number 2.

**The hookup of the LED emitter:**

This is even more easy, connect ground and the positive on pin 9 PWN (is case of MEGA version, others varies uses 3, 16 PWN points, to know wich it uses, just look at this line in the library: https://github.com/shirriff/Arduino-IRremote/blob/master/IRremoteInt.h#L254

Then upload, and start the serial monitor and: 

Enter "O" to set up the output signals
Enter "I" to set up the input signals

after that, is ready to use !


With love from:
============

**[Ipsilon Developments Inc.](http://www.ipsilondev.com)** released under **MIT license**

Like our **[Facebook](http://www.facebook.com/ipsilondev)** page to get news about our releases

Or Follow us on **[Twitter](https://twitter.com/ipsilondev)**

You can also contact us at **info [AT] ipsilondev.com**
