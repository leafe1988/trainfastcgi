#include "signal.h"
#include "signalGroupImp.h"

namespace WebService{

struct sm_t{
  std::list<std::string> mGroupNames{{
    "Product Infomation Group",
    "Parameter Infomation Group",
    "Pruduct State Group",
  }};
  
  std::unordered_map<std::string, std::shared_ptr<SignalGroup>> mGroupTable;
  
  bool mIsGroupTableInit = false;
}gSmContent;

SignalManager gSignalManager;

static void SignalManager_initGroupTable()
{
  #define addGroup(name, cls) {\
      gSmContent.mGroupTable[name]=std::make_shared<cls>();\
  }

  addGroup("Product Infomation Group", ProductInfomationGroup);

  addGroup("Parameter Infomation Group", ParameterInfomationGroup);

  addGroup("Pruduct State Group", PruductStateGroup);

  //to-do: add other group
  //...    
  
  return ;
}

std::list<std::string> SignalManager::groupNameList() const
{
  return gSmContent.mGroupNames;
}

SignalGroup* SignalManager::group ( const std::string& groupName )
{
  if(!gSmContent.mIsGroupTableInit){
    SignalManager_initGroupTable();
    gSmContent.mIsGroupTableInit = true;
  }
  
  auto it = gSmContent.mGroupTable.find(groupName);
  if(it != gSmContent.mGroupTable.end()){
    return it->second.get();
  }
  
  return NULL;
}

SignalManager* SignalManager::instance()
{
  return &gSignalManager;
}

}