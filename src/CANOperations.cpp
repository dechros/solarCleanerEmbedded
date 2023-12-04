#include "CANOperations.h"
#include "globals.h"
#include "pinOperations.h"
#include "waterPumpDriver.h"
#include "mcp_can.h"

#define RPM_MAX_SPEED   		(7)
#define RPM_MIN_SPEED   		(3)

MCP_CAN CAN(SPI_CS_PIN); 
Message_t CANMessage;
uint8_t RPM_SPEED = 3; /* 1 - 5 */
uint8_t waterPumpButtonOldState = 0;

void InitCANBus()
{
    memset(&CANMessage, 0, sizeof(Message_t));
    while (CAN_OK != CAN.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ))
	{
		delay(100);	
	}
	CAN.setMode(MCP_NORMAL);
}

void RemoteStart()
{
    uint8_t startRemote = 1;
	CAN.sendMsgBuf(0x0, 1, &startRemote);
}

void CheckCANMessage()
{
    if (CANMessageReceived)
	{
		uint8_t messageLength = 0;
		uint32_t canMessageId = 0;

		if (CAN.readMsgBuf(&canMessageId, &messageLength, CANMessage.data) == CAN_OK)
		{
			if (canMessageId == REMOTE_CONTROL_MESSAGE_ID_1)
			{
				static uint8_t previousRampUpValue = 0;
				static uint8_t previousRampDownValue = 0;
				if (CANMessage.byte3.bit6 == 1 && previousRampUpValue == 0)
				{
					RPM_SPEED++;
					if (RPM_SPEED > RPM_MAX_SPEED)
					{
						RPM_SPEED = RPM_MAX_SPEED;
					}
				}
				else if (CANMessage.byte3.bit7 == 1 && previousRampDownValue == 0)
				{
					RPM_SPEED--;
					if (RPM_SPEED < RPM_MIN_SPEED)
					{
						RPM_SPEED = RPM_MIN_SPEED;
					}
				}
				previousRampUpValue = CANMessage.byte3.bit6;
				previousRampDownValue = CANMessage.byte3.bit7;
				
				if (CANMessage.byte5.paddleAValue > JOYSTICK_DEAD_ZONE_CAN_REMOTE)
				{
					RightTrackMotor.SetTargetSpeed((uint8_t)((CANMessage.byte5.paddleAValue / 3) * ((double)RPM_SPEED / RPM_MAX_SPEED)));
				}
				else
				{
					RightTrackMotor.SetTargetSpeed(0);
				}
				
				if (CANMessage.byte2.paddleANorth == 1 && CANMessage.byte2.paddleASouth == 0)
				{
					RightTrackMotor.SetTargetDirection(REVERSE);
				}
				else if (CANMessage.byte2.paddleANorth == 0 && CANMessage.byte2.paddleASouth == 1)
				{
					RightTrackMotor.SetTargetDirection(FORWARD);
				}

				if (CANMessage.byte8.paddleDValue > JOYSTICK_DEAD_ZONE_CAN_REMOTE)
				{
					LeftTrackMotor.SetTargetSpeed((uint8_t)((CANMessage.byte8.paddleDValue / 3) * ((double)RPM_SPEED / RPM_MAX_SPEED)));
				}
				else
				{
					LeftTrackMotor.SetTargetSpeed(0);
				}
				
				if (CANMessage.byte2.paddleDNorth == 1 && CANMessage.byte2.paddleDSouth == 0)
				{
					LeftTrackMotor.SetTargetDirection(FORWARD);
				}
				else if (CANMessage.byte2.paddleDNorth == 0 && CANMessage.byte2.paddleDSouth == 1)
				{
					LeftTrackMotor.SetTargetDirection(REVERSE);
				}

				if (CANMessage.byte7.potantiometerValue > JOYSTICK_DEAD_ZONE_CAN_REMOTE)
				{
					BrushesMotor.SetTargetSpeed(CANMessage.byte7.potantiometerValue);
				}
				else
				{
					BrushesMotor.SetTargetSpeed(0);
				}
				
				if (CANMessage.byte3.bit3 == 0 && CANMessage.byte3.bit4 == 1)
				{
					BrushesMotor.SetTargetDirection(FORWARD);
				}
				else if (CANMessage.byte3.bit3 == 1 && CANMessage.byte3.bit4 == 0)
				{
					BrushesMotor.SetTargetDirection(REVERSE);
				}

				if (CANMessage.byte3.bit2 == 1 && waterPumpButtonOldState == 0)
				{
					WaterPumpToggle();
				}
				waterPumpButtonOldState = CANMessage.byte3.bit2;
			}
		}
	}
}