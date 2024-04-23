#include <SoftwareSerial.h>
#include "Singleton.h"
SoftwareSerial BTSerial(13, 12); // RX | TX
bool bBluetoothConnected = true;

#define PinMode(s) pinMode(s,OUTPUT);
#define LOGSR(s) Serial.println(s);
#define LOGBT(s) BTSerial.println(s);
#define IFVAR(a, s) (a.equals(s))
#define Read(s) digitalRead(s);
#define CALL_ONCE(...) \
  { \
    static bool once = false; \
    if (!once) { \
      []() { \
        __VA_ARGS__ \
      }(); \
      once = true; \
    } \
  }

enum _STATUSLABEL
{
  SUCCESS = 1,
  FAILED = 0
};
enum _PIN
{
  IGNITION,
  KILLSWITCH,
  STARTER,
  LIGHTS,
  CDI,
  STATUS,
  HORN
};
enum _ONOFF
{
  ON = LOW,
  OFF = HIGH
};


namespace Global
{
void Write(int pin, _ONOFF bValue)
{
  digitalWrite(pin, bValue);
}
void Initialize()
{
  Serial.begin(9600);
  BTSerial.begin(9600);
}

class Var : public Singleton<Var>
{
  public:
    Var()
    {
      this->bBluetoothConnected = true;
      this->bSendOnce =true;
      
      this->PIN[IGNITION] = 2;
      this->PIN[KILLSWITCH] = 4;
      this->PIN[STARTER] = 5;
      this->PIN[LIGHTS] = 6;
      this->PIN[CDI] = 3;
      this->PIN[HORN] = 7;
      this->PIN[STATUS] = 11;
      this->BTStatus = 0;

      this->ReceivedString = "";
    };

    String ReceivedString;
    bool bBluetoothConnected, BTStatus,bSendOnce;
    int PIN[15];

};
void InitializePinMode()
{
  pinMode(Global::Var::get()->PIN[STATUS], INPUT);
  PinMode(Global::Var::get()->PIN[IGNITION]);
  PinMode(Global::Var::get()->PIN[KILLSWITCH]);
  PinMode(Global::Var::get()->PIN[STARTER]);
  PinMode(Global::Var::get()->PIN[LIGHTS]);
  PinMode(Global::Var::get()->PIN[CDI]);
  PinMode(Global::Var::get()->PIN[HORN]);

  
}

};
