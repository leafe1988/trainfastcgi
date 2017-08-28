#ifndef __SIGNAL_GROUP_IMP_H__
#define __SIGNAL_GROUP_IMP_H__

#include <unordered_map>
#include <memory>

#define private public
#include "signal.h"
#undef private

namespace WebService{
//________________________________________________________________________
class SignalGroupImp : public SignalGroup
{
public:
  virtual ~SignalGroupImp(){}
  
  virtual std::string name() const
  {
    return mName;
  }
  
  virtual std::list<std::string> signalNameList() const
  {
    return mSignalNames;
  }
  
  virtual Signal* signal (const std::string& signalName)
  {
    if(!mIsSignalTableInit){
      initSignalTable();
      mIsSignalTableInit = true;
    }
    
    auto it = mSignalTable.find(signalName);
    if(it != mSignalTable.end()){
      return it->second.get();
    }
    
    return NULL;    
  }
protected:
  virtual void initSignalTable() = 0;
protected:
  std::string mName;
  std::list<std::string> mSignalNames;
  std::unordered_map<std::string, std::shared_ptr<Signal>> mSignalTable;
  bool mIsSignalTableInit = false; 
};

//________________________________________________________________________
class ProductInfomationGroup : public SignalGroupImp
{
public:
  ProductInfomationGroup();
  
  virtual ~ProductInfomationGroup(){}
protected:
  virtual void initSignalTable();
};

//________________________________________________________________________
class ParameterInfomationGroup : public SignalGroupImp
{
public:
  ParameterInfomationGroup();
  
  virtual ~ParameterInfomationGroup(){}
protected:
  virtual void initSignalTable();
};

//________________________________________________________________________
class PruductStateGroup : public SignalGroupImp
{
public:
  PruductStateGroup();
  
  virtual ~PruductStateGroup(){}
protected:
  virtual void initSignalTable();
};

}
#endif //__SIGNAL_GROUP_IMP_H__
