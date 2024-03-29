#ifndef _ROUTER_OPERATIONS_H_
#define _ROUTER_OPERATIONS_H_

#include <Arduino.h>

#define ROUTER_SERIAL Serial

#define ACK_MESSAGE            		"ACK"
#define TCP_MESSAGE_FIRST_BYTE  	'T'
#define TCP_MESSAGE_HEADER      	"TCP"

#define MAX_SPEED 				255
#define MAX_HIPOTENUS_VALUE		127

void InitRouterCommunication(void);
void CheckTCPMessage(void);

typedef struct
{
	uint8_t headerT;
	uint8_t headerC;
	uint8_t headerP;
	uint8_t joystickX;
	uint8_t joystickY;
    uint8_t brushSpeed;
	uint8_t driveSpeed;
	union
	{
		uint8_t buttons;
		struct
		{
			uint8_t waterButton     :1;
            uint8_t lampButton      :1;
			uint8_t startButton     :1;
			uint8_t passButton      :1;
			uint8_t brushFrontCW    :1;
			uint8_t brushFrontCCW   :1;
			uint8_t brushRearCW     :1;
            uint8_t brushRearCCW    :1;
		};
	};
    union
	{
		uint8_t data;
		struct
		{
			uint8_t emergencyButton :1;
            uint8_t                 :7;
		};
	};
	uint8_t checksum;
}TCPMessage_t;

#endif /* _ROUTER_OPERATIONS_H_ */