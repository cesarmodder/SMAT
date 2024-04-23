#include "Global.h"


void setup()
{
  Global::Initialize();
  Global::InitializePinMode();
  Global::Write(Global::Var::get()->PIN[KILLSWITCH], OFF);
  Global::Write(Global::Var::get()->PIN[STARTER], OFF);
  Global::Write(Global::Var::get()->PIN[LIGHTS], OFF);
  Global::Write(Global::Var::get()->PIN[CDI], OFF);
  Global::Write(Global::Var::get()->PIN[IGNITION], OFF);
  Global::Write(Global::Var::get()->PIN[HORN], OFF);
}

void BluetoothCheck()
{
  Global::Var::get()->BTStatus = Read(Global::Var::get()->PIN[STATUS]);
  if (Global::Var::get()->BTStatus == SUCCESS)
  {
    if (Global::Var::get()->bBluetoothConnected == false)
    {
      LOGSR(xorstr_("U{brcxxc7Dbttrddqb{{n7Txyyrtcrs"));

      Global::Var::get()->bBluetoothConnected = true;
    }
  }
  else if (Global::Var::get()->BTStatus == FAILED)
  {
    if (Global::Var::get()->bBluetoothConnected == true)
    {
      LOGSR(xorstr_("U{brcxxc7Yxc7Txyyrtcrs"));
      Global::Var::get()->bBluetoothConnected = false;
    }
  }
}


void BluetoothConnectionLost()
{
  if (Global::Var::get()->BTStatus == SUCCESS)
  {
    if (Global::Var::get()->bSendOnce == false)
    {
      Global::Write(Global::Var::get()->PIN[KILLSWITCH], OFF);

      Global::Var::get()->bSendOnce = true;
    }
  }
  else if (Global::Var::get()->BTStatus == FAILED)
  {
    if (Global::Var::get()->bSendOnce == true)
    {
      Global::Var::get()->bSendOnce = false;
    }
    Global::Write(Global::Var::get()->PIN[KILLSWITCH], ON);
    Global::Write(Global::Var::get()->PIN[STARTER], OFF);
    Global::Write(Global::Var::get()->PIN[CDI], OFF);
    Global::Write(Global::Var::get()->PIN[LIGHTS], OFF);
    Global::Write(Global::Var::get()->PIN[IGNITION], OFF);
    Global::Write(Global::Var::get()->PIN[HORN], OFF);
  }
}

void Function(void)
{
  if (Global::Var::get()->BTStatus == SUCCESS)
  {
    Global::Var::get()->ReceivedString = BTSerial.readString();
    if (Global::Var::get()->ReceivedString.length() > 0)
    {
      Global::Var::get()->ReceivedString.trim();

      /*~~~~~~~~~~~~~~~~~~~~~~~~ STARTER  ~~~~~~~~~~~~~~~~~~~~~~*/
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("DCVECREHXY")))
      {
        Global::Write(Global::Var::get()->PIN[STARTER], ON);
        delay(600);
        Global::Write(Global::Var::get()->PIN[STARTER], OFF);
      }
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("DCVECREHXQQ")))
      {
        Global::Write(Global::Var::get()->PIN[STARTER], OFF);
      }

      /*~~~~~~~~~~~~~~~~~~~~~~~~ KILLSWITCH  ~~~~~~~~~~~~~~~~~~~~~~*/
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("RYP^YRHXY")))
      {
        Global::Write(Global::Var::get()->PIN[KILLSWITCH], ON);
      }
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("RYP^YRHXQQ")))
      {
        Global::Write(Global::Var::get()->PIN[KILLSWITCH], OFF);
      }

      /*~~~~~~~~~~~~~~~~~~~~~~~~ IGNITION & CDI ~~~~~~~~~~~~~~~~~~~~~~*/
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("^PY^C^XYHXY")))
      {
        Global::Write(Global::Var::get()->PIN[IGNITION], ON);
        Global::Write(Global::Var::get()->PIN[CDI], ON);
      }
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("^PY^C^XYHXQQ")))
      {
        Global::Write(Global::Var::get()->PIN[IGNITION], OFF);
        Global::Write(Global::Var::get()->PIN[CDI], OFF);
      }

      /*~~~~~~~~~~~~~~~~~~~~~~~~ LIGHTS  ~~~~~~~~~~~~~~~~~~~~~~*/
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("[^P_CDHXY")))
      {
        Global::Write(Global::Var::get()->PIN[LIGHTS], ON);
      }
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("[^P_CDHXQQ")))
      {
        Global::Write(Global::Var::get()->PIN[LIGHTS], OFF);
      }

      /*~~~~~~~~~~~~~~~~~~~~~~~~ HORN  ~~~~~~~~~~~~~~~~~~~~~~*/
      if (IFVAR(Global::Var::get()->ReceivedString, xorstr_("_XEYHXY")))
      {
        for (int i = 0; i < 5; i ++)
        {
          Global::Write(Global::Var::get()->PIN[HORN], ON);
          delay(400);
          Global::Write(Global::Var::get()->PIN[HORN], OFF);
          delay(400);
        }
      }
    }
  }
}

void loop()
{
  Function();
  BluetoothCheck();
  BluetoothConnectionLost();
}
