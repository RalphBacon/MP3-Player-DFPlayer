# MP3-Player-DFPlayer
How to link the DFPlayer MP3 player to an Arduino

Let the music play! This module can most certainly be used as a custom, Arduino-controlled player of music (in a pub or restaurant, for example) but it could equally be used to give out
warning messages or instructions "3D printer has run out of material!" in a factory or workshop. The possibilities are endless. All you have to do is record your .mp3 or .wav
files, put them onto a micro SD card (referred to as a TF [TransFlash] card in the documentation] and you're good to go.

We're not using any libraries in this demo, so that you can see exactly how the commands are sent to the MP3 player (and how the optional responses are returned too). It also
demonstrates how easy it is to send out those commands via the SoftwareSerial library (why not the standard Serial port? Watch the video to find out!)

However, you may feel more comfortable using the DFRobot MP3 Player library so I've included that in the links below. Just be aware that we have not
experimented with that library in the video (but it looks very easy to use and takes away all the work (aka pain) in creating the command strings). The library contains some examples
that should get you going nicely too.

---------------------------------------------------
STOP! READ THIS IF YOU VALUE YOUR MP3 PLAYER MODULE
---------------------------------------------------

The RX and TX from the Arduino Uno or Nano will be 5V and will damage the MP3 player which requires 3.3V on these pins. Connect a 1K and 2K resistor like this (see the 20160612_200645.jpg file in this repository)

Arduino TX >------- 1K -----------> RX MP3 Player  
                                   |  
                                   |   
                                  2K  
                                   |  
                                   |  
                                  GND  
  
Arduino RX <------- 1K -----------< TX MP3 Player  
							 |  
							 |  
							 2K  
							 |  
							 |  
							GND  
  
Very simple, just 4 resistors in total. Other values can work too (Instead of 1K and 2K you can use 4K7 and 10K). But don't mix and match!) Note that the RX of the Arduino goes to the TX of the MP3 player and vice versa.

I've included as many links below as I could find and I *stongly* recommend you print out the ones I've marked as you'll be referring to them often!

Essential reading (recommended print)
1. The DFrobot Wiki for the DFPlayer
   http://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299

2. Link to the Mini DF Player Manual (more technical but essential if you want to know the commands)
   https://db.tt/3ZX91wg7

Further information
1. A massive amount of extra information from Yerke (via the Banggood forum)
   http://forum.banggood.com/forum-topic-59997.html
   
2. This entry has been intentionally left blank. I think so anyway.

3. How to insert an advert track and then resume playing the original
   http://www.dfrobot.com/forum/viewtopic.php?f=2&t=1524

4. More on where I go the music for this demo
   http://www.purple-planet.com/using-our-royalty-free-music/4583818250   
   
Music: http://www.purple-planet.com


If you like this video please give it a thumbs up, share and if not already subscribed please do so :)

And my channel is here:
-----------------------------------------------------------------
https://www.youtube.com/c/RalphBacon
------------------------------------------------------------------ 
How can I remember this? Memory tip: "See" Ralph Bacon, geddit?
