// CAN Receive Example
//

#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10

int RPWM=5;
int LPWM=6;

int L_EN=7;
int R_EN=8;

int flag_1 = 0;
int flag_2 = 0;

void setup()
{

  pinMode(3,OUTPUT);  // main motor 
  pinMode(4,OUTPUT);  // buzzer 
 
  for(int i=5;i<9;i++)
  {
   pinMode(i,OUTPUT);
  }
  for(int i=5;i<9;i++)
  {
   digitalWrite(i,LOW);
  }

  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
  
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  int y = digitalRead(A0);
  int z = digitalRead(A1);
  
  digitalWrite(R_EN,HIGH);
  digitalWrite(L_EN,HIGH);
//************************************************************************  Data assign block  ****************************************************************************************
  
  if(!digitalRead(CAN0_INT))     // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:  ", rxId, len); 
      Serial.print(msgString);
  
//***************************************************************************  Data print block ****************************************************************************************
    
    if((rxId & 0x40000000) == 0x40000000)
    {    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } 
    else 
    {
      for(byte i = 0; i<len; i++)
      {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(rxBuf[i]); 
        Serial.print("  ");     
      }
    }
//*******************************************************************************  Control block  *************************************************************************************    

    {
     if(rxBuf[6]== 48) 
     {
       digitalWrite(4, HIGH);
     } 
     else
     {
       digitalWrite(4, LOW);
     } 
    }
    
    {
      if (rxBuf[7]==56 && flag_1 == 0 && flag_2 == 0)  // received hex = 0x30 = 48 Decimal
      {
       Serial.println();
       digitalWrite(3, LOW);
       analogWrite(RPWM,20);
       analogWrite(LPWM,0);
       delay(2000); 
       flag_1 = 1;
       if(flag_1 == 1 && flag_2 == 0)
       {
        analogWrite(RPWM,0);
        analogWrite(LPWM,0);
       }     
       
      }
      else if(rxBuf[7]==55 && flag_1 == 1 && flag_2 == 0) 
      {
        Serial.println();
        digitalWrite(3, HIGH);
        analogWrite(LPWM,20);
        analogWrite(RPWM,0);
        delay(2000); 
        flag_2 = 1;
        if(flag_2 == 1 && flag_1 == 1)
        {
          analogWrite(LPWM,0);
          analogWrite(RPWM,0);
          flag_1 = 0;
          flag_2 = 0;
        }   
        
      }
      else if(flag_1 == 0 || flag_2 == 0 || flag_1 == 1 || flag_2 == 1)
      {
       Serial.println();
       if(y == 0 && z == 1)
       {
        analogWrite(RPWM,20);
       }

       if(y == 1 && z == 0)
       {
        analogWrite(LPWM,20); 
       }

       if(y == 1 && z == 1)
       {
        analogWrite(LPWM,0);
        analogWrite(RPWM,0);
       }

       if(y == 0 && z == 0)
       {
        analogWrite(LPWM,0);
        analogWrite(RPWM,0); 
       }
     }
     else {Serial.println();}
    }
//**************************************************************************  End of Control block   **********************************************************************************
  }
}
