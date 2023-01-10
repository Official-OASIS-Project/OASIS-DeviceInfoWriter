#include <EEPROM.h>

#define EEPROM_SIZE 40

// Command Parsing
String Command;
char DeviceName[24];
char StrValues[42];
int TEMP = 0;
String Garbage;

void getWriteInt(byte Addr){
  while(!Serial.available()){
    // Wait for answer
  }
  TEMP = Serial.parseInt();
  Serial.println(TEMP);
  EEPROM.write(Addr, TEMP);
  Garbage = Serial.readString();
}

void readOASISInfo(){
  Serial.println("[OASIS-DeviceInfoWriter] Reading EEPROM...");

  // Read Hardware Version
  byte HW_MAJOR = EEPROM.read(0x08);
  byte HW_MINOR = EEPROM.read(0x09);
  Serial.print("[OASIS-DeviceInfoWriter] Device Hardware Version is ");
  Serial.print(HW_MAJOR);
  Serial.print(".");
  Serial.println(HW_MINOR);

  // Read Firmware Version
  byte FW_MAJOR = EEPROM.read(0x0A);
  byte FW_MINOR = EEPROM.read(0x0B);
  Serial.print("[OASIS-DeviceInfoWriter] Device Firmware Version is ");
  Serial.print(FW_MAJOR);
  Serial.print(".");
  Serial.println(FW_MINOR);

  // ADC Resolution
  byte ADC_BITS = EEPROM.read(0x0C);
  Serial.print("[OASIS-DeviceInfoWriter] ADC resolution: ");
  Serial.println(ADC_BITS);

  // Feature - TEDS
  byte F_TEDS = EEPROM.read(0x0D);
  Serial.print("[OASIS-DeviceInfoWriter] TEDS module installed (1=yes, 0=no): ");
  Serial.println(F_TEDS);

  // Feature - WSS
  byte F_WSS = EEPROM.read(0x0E);
  Serial.print("[OASIS-DeviceInfoWriter] WSS module installed (1=yes, 0=no): ");
  Serial.println(F_WSS);

  // Custom Device Name
  Serial.print("[OASIS-DeviceInfoWriter] Device name: ");
  for(int i=0; i<24; i++){
    if(EEPROM.read(0x10 + i)!=0){
      DeviceName[i] = EEPROM.read(0x10 + i);
      Serial.print(DeviceName[i]);
    }
  }
  Serial.println();
  Serial.println();
}

void setup() {
  EEPROM.begin(EEPROM_SIZE);
  Serial.begin(2000000);

  Serial.println();
  Serial.println("--------------------------------------------------------------------------");
  Serial.println("                         OASIS Device Info Writer                         ");
  Serial.println("--------------------------------------------------------------------------");
  
  readOASISInfo();
}

void loop() {

   Serial.println("--------------------------------------------------------------------------");
   Serial.println("                                   MENU                                   ");
   Serial.println("--------------------------------------------------------------------------");
   Serial.println("[OASIS-DeviceInfoWriter] (1): Update all values");
   Serial.println("[OASIS-DeviceInfoWriter] (2): Update Hardware Revision");
   Serial.println("[OASIS-DeviceInfoWriter] (3): Update Firmware Revision");
   Serial.println("[OASIS-DeviceInfoWriter] (4): Update ADC Resolution");
   Serial.println("[OASIS-DeviceInfoWriter] (5): Update TEDS module installed");
   Serial.println("[OASIS-DeviceInfoWriter] (6): Update WSS module installed");
   Serial.println("[OASIS-DeviceInfoWriter] (7): Update Device Name");
   Serial.println("--------------------------------------------------------------------------");
   Serial.println();
   Serial.println("[OASIS-DeviceInfoWriter] Update Information [Option]: ");
  
   while(!Serial.available()){
    // Wait for answer
   }
   Command = Serial.readString();
   Command.toCharArray(StrValues,42);
   Serial.println();
   
   if(StrValues[0]=='1'){ 
    // Hardware Version
    Serial.print("[OASIS-DeviceInfoWriter] Enter new major hardware revision HW_VER_0: ");
    getWriteInt(0x08);
    
    Serial.print("[OASIS-DeviceInfoWriter] Enter new minor hardware revision HW_VER_1: ");
    getWriteInt(0x09);

    // Firmware Version
    Serial.print("[OASIS-DeviceInfoWriter] Enter new major firmware revision FW_VER_0: ");
    getWriteInt(0x0A);
    
    Serial.print("[OASIS-DeviceInfoWriter] Enter new minor firmware revision FW_VER_1: ");
    getWriteInt(0x0B);

    // Hardware Info
    Serial.print("[OASIS-DeviceInfoWriter] Enter ADC Resolution ADC_BIT: ");
    getWriteInt(0x0C);
    Serial.print("[OASIS-DeviceInfoWriter] Is a TEDS module installed? F_TEDS (1=yes, 0=no): ");
    getWriteInt(0x0D);
    Serial.print("[OASIS-DeviceInfoWriter] Is a WSS module installed? F_WSS (1=yes, 0=no): ");
    getWriteInt(0x0E);

    // Device Name
    Serial.print("[OASIS-DeviceInfoWriter] Enter new device name: ");
    while(!Serial.available()){
      // Wait for answer
    }
    Command = Serial.readString();
    int len = Command.length();
    Command.toCharArray(DeviceName,24);
    for(int i=0; i<len-1; i++){
    EEPROM.write(0x10 + i,DeviceName[i]);
    Serial.print(DeviceName[i]);
    }
    Serial.println();
    for(int i=len-1; i<24; i++){
    EEPROM.write(0x10 + i, 0);
    }
   }
   else if(StrValues[0]=='2'){
    // Hardware Version
    Serial.print("[OASIS-DeviceInfoWriter] Enter new major hardware revision HW_VER_0: ");
    getWriteInt(0x08);
    
    Serial.print("[OASIS-DeviceInfoWriter] Enter new minor hardware revision HW_VER_1: ");
    getWriteInt(0x09);
   }
   else if(StrValues[0]=='3'){
    // Firmware Version
    Serial.print("[OASIS-DeviceInfoWriter] Enter new major firmware revision FW_VER_0: ");
    getWriteInt(0x0A);
    
    Serial.print("[OASIS-DeviceInfoWriter] Enter new minor firmware revision FW_VER_1: ");
    getWriteInt(0x0B);
   }
   else if(StrValues[0]=='4'){
    Serial.print("[OASIS-DeviceInfoWriter] Enter ADC Resolution ADC_BIT: ");
    getWriteInt(0x0C);
   }
   else if(StrValues[0]=='5'){
    Serial.print("[OASIS-DeviceInfoWriter] Is a TEDS module installed? F_TEDS (1=yes, 0=no): ");
    getWriteInt(0x0D);
   }
   else if(StrValues[0]=='6'){
    Serial.print("[OASIS-DeviceInfoWriter] Is a WSS module installed? F_WSS (1=yes, 0=no): ");
    getWriteInt(0x0E);
   }
   else if(StrValues[0]=='7'){
    // Device Name
    Serial.print("[OASIS-DeviceInfoWriter] Enter new device name: ");
    while(!Serial.available()){
      // Wait for answer
    }
    Command = Serial.readString();
    int len = Command.length();
    Command.toCharArray(DeviceName,24);
    for(int i=0; i<len-1; i++){
    EEPROM.write(0x10 + i,DeviceName[i]);
    Serial.print(DeviceName[i]);
    }
    Serial.println();
    for(int i=len-1; i<24; i++){
    EEPROM.write(0x10 + i, 0);
    }
   }
  Serial.println();
  EEPROM.commit();
  Serial.println("[OASIS-DeviceInfoWriter] Changes have been commited to EEPROM ");
  Serial.println();
  readOASISInfo();
}
