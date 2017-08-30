#include "signalGroupImp.h"

#include "signalPrivate.h"

namespace WebService{

#define addSignal(group, name, type) {\
  auto p = new SignalPrivate();\
  p->mName.assign(name);\
  p->mType = type;\
  auto s = std::make_shared<Signal>();\
  s->priv = p;\
  group.insert(std::make_pair(name, s));\
}

//________________________________________________________________________
ProductInfomationGroup::ProductInfomationGroup()
{
  mName.assign("Product Infomation Group");
  
  mSignalNames = {
    "ProductName",
    "ProductType",
    "VendorName",
    "SerialNumber",
    "ManufactureDataTime",
    "MainBoardHardwareVersion",
    "IOBoardHardwareVersion",
    "CommBoardHardwareVersion",
    "SystemSoftwareVersion",
    "AppSoftwareVersion",
    "CommFirmwareVersion",
    "IOBoardFirmwareVersion",
    "BootloaderVersion",
  };
}

void ProductInfomationGroup::initSignalTable()
{
  addSignal(mSignalTable, "ProductName", Signal::Type::String);
  //to-do: add other signal
  //...
  
  return ;
}

//________________________________________________________________________
ParameterInfomationGroup::ParameterInfomationGroup()
{
  mName.assign("Parameter Infomation Group");
  
  mSignalNames = {
    "VehicleType",
    "VehicleNumber",
    "TrainNumber",
    "WheelDiameter1",
    "WheelDiameter2",
    "PulseEncode1",
    "PulseEncode2",
  };
}

void ParameterInfomationGroup::initSignalTable()
{
  //to-do: add other signal
  //...
}

//________________________________________________________________________
PruductStateGroup::PruductStateGroup()
{
  mName.assign("Pruduct State Group");
  
  mSignalNames = {
    "ConfigVersion",
    "TotalMileage",
    "CurrentMileage",
    "TotalRunTime",
    "CurrentSystemTime",
  };
}

void PruductStateGroup::initSignalTable()
{
  //to-do: add other signal
  //...
}

} //end namespace WebService 