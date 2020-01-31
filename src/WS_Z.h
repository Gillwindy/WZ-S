#ifndef WS_Z_H
#define WS_Z_H
#define WZ_S_START_TAG 0Xff

class WS_Z
{	
public:
	struct DATA {
		uint16_t HCHO_ppb;
		uint16_t HCHO_ugm3;
		uint8_t err_code;
	};
	
	WS_Z(Stream&);
	void passiveMode();
	void activeMode();
	void requestData();
	bool dataRead(DATA& data);
	

private:
	enum STATUS { WAITING, OK };
	Stream* _wstream;
	DATA* _data;
	STATUS _status;

	
	static const uint8_t DATA_SIZE = 9;
	uint8_t raw[DATA_SIZE];
	
	bool packetAvailable(void);
	void loop();
	
};


#endif
