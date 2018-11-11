3D POPUP AUDIO BOOK
-------------------

This is a 3D popup book for kids with audio playback features. Turning over each page will play a specific prerecorded audio automatically. No switches need to be pressed. 

Components:
1) Arduino Nano V3
2) Reed switches
3) Coin magnets
4) PAM8403 2 Channel USB Power Audio Amplifier Module: http://bdspeedytech.com/index.php?route=product/product&product_id=2311&search=amplifier&page=2
5) MicroSD card breakout module
6) 2 x 9V batteries
7) Small speaker (salvaged from old parts)
8) 7805 voltage regulator IC
9) 10K resistors

How it works?

Reed Switches and Magnets:

Reed switches are switches that are activated in presence of a magnetic field. Each page contains one reed switch and one coin magnet hidden inside the folds. Whenever a page is turned, the magnet activates the corresponding switch, which is then read by the Arduino Nano. 
One end of each reed switch are shorted together and connected to 5V of the Arduino Nano. The other end of each reed switch is connected to Arduino Nano’s GND through a 10K resistor each. Reading is taken from the other end of the resistor for each reed switch by connecting it to a digital pin of Arduino Nano. So, whenever a page is turned, that corresponding reed switch is activated, which can be detected by the Arduino Nano.

Audio playback:

Audio playback is achieved using the TMRpcm library to play prerecorded .wav files stored in the SD card. The MicroSD card module and Arduino NANO connections are as follows:

SD CS --> Arduino D10

SD SCK --> Arduino D13

SD MOSI --> Arduino D11

SD MISO --> Arduino D12

SD VCC --> Arduino 5V

SD GND --> Arduino GND

Whenever a reed switch is activated, the corresponding .wav file is played from the SD card. This audio is then amplified using a “PAM8403 2 Channel USB Power Audio Amplifier Module”. It supports two speakers, but only one was used for this project. The connections are as follows:

Amp R(+) --> Speaker (+)

Amp R(-) --> Speaker (-)

Amp 5V(+) --> Battery (+)

Amp GND(-) --> Battery (-) and Arduino GND

Amp R --> Arduino D9

Amp (common) --> Battery (-) and Arduino GND

Two separate batteries are used, one for the Arduino Nano and one for the audio amplifier.

Currently, 5 reed switches and 5 pages of the book have been used for this project. The popup book design was done by a third party. 


