#ifndef WZ_S_H
#define WZ_S_H
#define WZ_S_START_TAG 0Xff

class WZ_S
{	
public:
	struct DATA {
		uint16_t HCHO_ppb;
		uint16_t HCHO_ugm3;
	};
	
	WZ_S(Stream&);
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
