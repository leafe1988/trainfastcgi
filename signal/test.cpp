#include <iostream>

#include "signal.h"

void testSignal(WebService::Signal* s)
{
  
  std::cout << "signal name : " << s->name() << std::endl;

  s->setValue(std::string("hello"));
  
  std::string val;
  s->getValue(&val);
  std::cout << "signal value : " << val << std::endl;  
  
  return ;
}

void testGroup(WebService::SignalGroup* group)
{
  std::cout << "signal name list: " << std::endl;
  auto nameList = group->signalNameList();
  for(auto& i : nameList){
    std::cout << '\t' << i << std::endl;
  }
  std::cout << "\r\n" << std::endl;

  auto s = group->signal("ProductName");
  if(s){
    testSignal(s);
  }

  return ;
}

void testManager()
{
  auto sm = WebService::SignalManager::instance();
  
  auto nameList = sm->groupNameList();
  std::cout << "group name list: " << std::endl;
  for(auto& i : nameList){
    std::cout << '\t' << i << std::endl;
  }
  
  std::cout << "\r\n" << std::endl;
  
  auto group = sm->group("Product Infomation Group");
  if(group){
    testGroup(group);
  }
  
  return ;
}

int main()
{
  testManager();
  
  return 0;
}