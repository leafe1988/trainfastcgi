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
  addSignal(mSignalTable, "ProductType", Signal::Type::String);
  addSignal(mSignalTable, "VendorName", Signal::Type::String);
  addSignal(mSignalTable, "SerialNumber", Signal::Type::String);
  addSignal(mSignalTable, "ManufactureDataTime", Signal::Type::String);
  addSignal(mSignalTable, "MainBoardHardwareVersion", Signal::Type::String);
  addSignal(mSignalTable, "IOBoardHardwareVersion", Signal::Type::String);
  addSignal(mSignalTable, "CommBoardHardwareVersion", Signal::Type::String);
  addSignal(mSignalTable, "SystemSoftwareVersion", Signal::Type::String);
  addSignal(mSignalTable, "AppSoftwareVersion", Signal::Type::String);
  addSignal(mSignalTable, "CommFirmwareVersion", Signal::Type::String);
  addSignal(mSignalTable, "IOBoardFirmwareVersion", Signal::Type::String);
  addSignal(mSignalTable, "BootloaderVersion", Signal::Type::String);
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
	/*
	VehicleType                 |  ³µÁ¾ÀàÐÍ
	VehicleNumber               |  ³µÁ¾±àºÅ
	TrainNumber                 |  ³µ´Î
	WheelDiameter1              |  ÂÖ¾¶1
	WheelDiameter2              |  ÂÖ¾¶2
	PulseEncode1                |  Âö³å±àÂë1
	PulseEncode2                |  Âö³å±àºÅ2
	*/
	addSignal(mSignalTable, "VehicleType", Signal::Type::String);
	addSignal(mSignalTable, "VehicleNumber", Signal::Type::String);
	addSignal(mSignalTable, "TrainNumber", Signal::Type::String);
	addSignal(mSignalTable, "WheelDiameter1", Signal::Type::String);
	addSignal(mSignalTable, "WheelDiameter2", Signal::Type::String);
	addSignal(mSignalTable, "PulseEncode1", Signal::Type::String);
	addSignal(mSignalTable, "PulseEncode2", Signal::Type::String);
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
	addSignal(mSignalTable, "ConfigVersion", Signal::Type::String);
	addSignal(mSignalTable, "TotalMileage", Signal::Type::String);
	addSignal(mSignalTable, "CurrentMileage", Signal::Type::String);
	addSignal(mSignalTable, "TotalRunTime", Signal::Type::String);
	addSignal(mSignalTable, "CurrentSystemTime", Signal::Type::String);
}

} //end namespace WebService 