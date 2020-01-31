#include <Arduino.h>
#include <Stream.h>
#include "WS_Z.h"


WS_Z::WS_Z(Stream& wstream)
{
  this->_wstream = &wstream;
}

void WS_Z::passiveMode()
{
	byte command[] = { 0xFF,0x01,0x78,0x41,0x00,0x00,0x00,0x00,0x46 };
	_wstream->write(command, sizeof(command));
}

void WS_Z::activeMode()
{
 	 byte command[] = { 0xFF,0x01,0x78,0x40,0x00,0x00,0x00,0x00,0x47 };
 	 _wstream->write(command, sizeof(command));
}

void WS_Z::requestData()
{
	byte command[] = { 0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79 };
	_wstream->write(command, sizeof(command));
}

bool WS_Z::packetAvailable(void)
{
    if (!_wstream->available()) { _data->err_code = 3; return false;}
    while ((_wstream->peek() != WZ_S_START_TAG) && _wstream->available()) {
      _wstream->read(); 
    }
    if (_wstream->available() < DATA_SIZE) { _data->err_code = 4; return false; }
  
  return true;
}

bool WS_Z::dataRead(DATA& data)
{
	_data = &data;
	uint32_t node_ws_z = millis();
	do
	{
		loop();
		if (_status == OK) break;
	} while (millis() - node_ws_z < 1000);
	return _status == OK;

}



void WS_Z::loop()
{
	_status = WAITING;
	if (packetAvailable()) 
	{
		for (int i = 0; i < DATA_SIZE; i++)
			raw[i] = _wstream->read();

		//crc
		uint8_t checksum = 0;
		for (int i = 1; i < DATA_SIZE - 1; i++)
			checksum += raw[i];

		checksum = (~checksum) + 1;
		if (checksum == raw[DATA_SIZE - 1])
		{
			_status = OK;
			
			_data->HCHO_ppb = makeWord(raw[6],raw[7]);
			_data->HCHO_ugm3 = makeWord(raw[2],raw[3]);
			
		}else _data->err_code = 1;

		_wstream->flush();
	}
	else  _data->err_code = 2;
}
