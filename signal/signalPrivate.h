#ifndef __SIGNAL_PRIVATE_H__
#define __SIGNAL_PRIVATE_H__

namespace WebService{

class SignalPrivate
{
public:
  std::string mName;
  Signal::Type mType;
  union {
    unsigned char cVal;
    unsigned short hVal;
    unsigned long lVal;
    unsigned long long llVal;
    bool bVal;
  }mValue;
  std::tm tmVal;
  std::string strVal;
};

}
#endif //__SIGNAL_PRIVATE_H__
