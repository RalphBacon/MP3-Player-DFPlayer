#include "Arduino.h"
#include <SoftwareSerial.h>

/* Bytes are allocated:
 *
 * 0	Fixed 0x7E Start Command
 * 1	Fixed 0xFF Version info ??
 * 2	Fixed 0x06 Data length not including parity
 * 3	Command code 0x?? number
 * 4	Acknowledge 01= yes, 00 = no, returns info
 * 5	Track high byte
 * 6	Track low byte
 * 7	Checksum high byte
 * 8	Checksum low byte
 * 9	Fixed 0xEF End Command
 *
 * Example:
 * 		track number 100 (bytes 5 & 6) = 0x64 byte 6, 0x00 byte 5
 * 		volume is set to max (30) by default, to set to half volume (15)
 * 		send the following commands: 7E FF 06 06 00 00 0F FF D5 EF
 *
 * Checksum is calculated:
 * 		-Sum(bytes(1 to 6)) note the minus sign
 *
 */
SoftwareSerial mp3(10, 11);

#define startByte 0x7E
#define endByte 0xEF
#define versionByte 0xFF
#define dataLength 0x06
#define infoReq 0x01
#define isDebug false

template<typename T>
void debugPrint(T printMe, bool newLine = false) {
  if (isDebug) {
    if (newLine) {
      Serial.println(printMe);
    }
    else {
      Serial.print(printMe);
    }
    Serial.flush();
  }
}

void setup() {

	// NB For comms to MP3 player not USB
	mp3.begin(9600);

	// Serial Monitor serial
	Serial.begin(9600);

	// Set volume (otherwise full blast!) command code 0x06 followed by high byte / low byte
	sendCommand(0x06, 0, 15);

	// Equaliser setting
	sendCommand(0x07, 0, 5);

	// Specify track to play (0 = first track)
	sendCommand(0x03, 0, 0);

	// Play
	sendCommand(0x0D, 0, 0);
}

void loop() {

	// Get Serial Monitor input
	if (Serial.available()) {
		byte Command = Serial.parseInt();
		byte Parameter1 = Serial.parseInt();
		byte Parameter2 = Serial.parseInt();

		// Execute that command
		Serial.print("Sending command: ");
		Serial.print(Command);
		Serial.print(",");
		Serial.print(Parameter1);
		Serial.print(",");
		Serial.println(Parameter2);
		sendCommand(Command, Parameter1, Parameter2);
	}

	// Get MP3 player response (always 10 bytes)
	if (mp3.available() >= 10) {
		byte Returned[10];
		for (byte k = 0; k < 10; k++)
			Returned[k] = mp3.read();

		Serial.print("Returned: 0x");
		if (Returned[3] < 16) Serial.print("0");
		Serial.print(Returned[3], HEX);
		Serial.print("(");
		Serial.print(Returned[3], DEC);
		Serial.print("); Parameter: 0x");
		if (Returned[5] < 16) Serial.print("0");
		Serial.print(Returned[5], HEX);
		Serial.print("(");
		Serial.print(Returned[5], DEC);
		Serial.print("), 0x");
		if (Returned[6] < 16) Serial.print("0");
		Serial.print(Returned[6], HEX);
		Serial.print("(");
		Serial.print(Returned[6], DEC);
		Serial.println(")");
	}
}

void sendCommand(byte Command, byte Param1, byte Param2) {

	// Calculate the checksum
	unsigned int checkSum = -(versionByte + dataLength + Command + infoReq + Param1 + Param2);

	// Construct the command line
	byte commandBuffer[10] = { startByte, versionByte, dataLength, Command, infoReq, Param1, Param2,
			highByte(checkSum), lowByte(checkSum), endByte };

	for (int cnt = 0; cnt < 10; cnt++) {
		mp3.write(commandBuffer[cnt]);
	}

	// Delay needed between successive commands
	delay(30);
}

