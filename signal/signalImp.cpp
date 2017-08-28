#include "signal.h"
#include "signalPrivate.h"
#include <cstring>
// #include <iostream>


namespace WebService{

static bool Signal_getValue(SignalPrivate* priv, /*OUT*/void* value);
static bool Signal_setValue(SignalPrivate* priv, const void* value);

//________________________________________________________________________
Signal::Signal()
  :priv(nullptr){}
  
Signal::~Signal()
{
  // std::cout << __func__ << std::endl;
  if(priv){
    delete priv;
  }
}

//   获取信号名称
std::string Signal::name() const
{
  if(priv){
    return priv->mName;
  }
  
  return "";
}

//  获取信号类型
Signal::Type Signal::type() const
{
  if(priv){
    return priv->mType;
  }
  
  return Signal::Type::Int64;
}

//  获取/设置信号的值
bool Signal::getValue ( unsigned char* value )
{
  return Signal_getValue(priv, value);
}

bool Signal::setValue ( unsigned char value )
{
  return Signal_setValue(priv, &value);
}

bool Signal::getValue ( unsigned short* value )
{
  return Signal_getValue(priv, value);
}

bool Signal::setValue ( unsigned short value )
{
  return Signal_setValue(priv, &value);
}

bool Signal::getValue ( unsigned long* value )
{
  return Signal_getValue(priv, value);
}

bool Signal::setValue ( unsigned long value )
{
  return Signal_setValue(priv, &value);
}

bool Signal::getValue ( unsigned long long* value )
{
  return Signal_getValue(priv, value);
}

bool Signal::setValue ( unsigned long long value )
{
  return Signal_setValue(priv, &value);
}

bool Signal::getValue ( bool* value )
{
  return Signal_getValue(priv, value);
}

bool Signal::setValue ( bool value )
{
  return Signal_setValue(priv, &value);
}

bool Signal::getValue ( std::string* value )
{
  return Signal_getValue(priv, value);
}

bool Signal::setValue ( const std::string& value )
{
  return Signal_setValue(priv, &value);
}

bool Signal::getValue ( std::tm* value )
{
  return Signal_getValue(priv, value);
}

bool Signal::setValue ( const std::tm& value )
{
  return Signal_setValue(priv, &value);
}

//________________________________________________________________________
static bool Signal_getValue(SignalPrivate* priv, /*OUT*/void* value)
{
  if(!priv || !value){
    return false;
  }
  
  switch(priv->mType){
  case Signal::Type::Uint64:
    *(unsigned long long*)value = priv->mValue.llVal;
    return true;
  case Signal::Type::UInt32:
    *(unsigned long*)value = priv->mValue.lVal;
    return true;
  case Signal::Type::UInt16:
    *(unsigned short*)value = priv->mValue.hVal;
    return true;
  case Signal::Type::UInt8:
    *(unsigned char*)value = priv->mValue.cVal;
    return true;
  case Signal::Type::Bool:
    *(bool*)value = priv->mValue.bVal;
    return true;
  case Signal::Type::DateTime:
    memcpy(value, &(priv->tmVal), sizeof(std::tm));
    return true;
  case Signal::Type::String:
    ((std::string*)value)->assign(priv->strVal);
    return true;
  default:
    break;
  }
  
  return false;
}

//________________________________________________________________________
static bool Signal_setValue(SignalPrivate* priv, const void* value)
{
  if(!priv || !value){
    return false;
  }
  
  switch(priv->mType){
  case Signal::Type::Uint64:
    priv->mValue.llVal = *(unsigned long long*)value;
    return true;
  case Signal::Type::UInt32:
    priv->mValue.lVal = *(unsigned long*)value;
    return true;
  case Signal::Type::UInt16:
    priv->mValue.hVal = *(unsigned short*)value;
    return true;
  case Signal::Type::UInt8:
    priv->mValue.cVal = *(unsigned char*)value;
    return true;
  case Signal::Type::Bool:
    priv->mValue.bVal = *(bool*)value;
    return true;
  case Signal::Type::DateTime:
    memcpy(&(priv->tmVal), value, sizeof(std::tm));
    return true;
  case Signal::Type::String:
    priv->strVal.assign(*(std::string*)value);
    return true;
  default:
    break;
  }
  
  return false;
}

}