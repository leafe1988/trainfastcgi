#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include "signal.h"

void testSignal(WebService::Signal* s)
{
  std::cout << "==========" << __func__ << "===========" << std::endl;
  
  std::cout << "signal name : " << s->name() << std::endl;

  s->setValue(std::string("hello"));
  
  std::string val;
  s->getValue(&val);
  std::cout << "signal value : " << val << std::endl;  
  
  return ;
}

void testGroup(WebService::SignalGroup* group)
{
  std::cout << "==========" << __func__ << "===========" << std::endl;
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
  std::cout << "==========" << __func__ << "===========" << std::endl;
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

void testStoragePartitionReader(WebService::StoragePartitionReader* r)
{
  std::cout << "==========" << __func__ << "===========" << std::endl;
  
  std::cout << "before read: " << std::endl
            << "totalSize : " << r->totalSize()  << std::endl
            << "remainSize : " << r->remainSize()  << std::endl;
            
  unsigned char buf[8] = {};
  while(!r->isEnd()){
    r->read(buf, 7); 
    memset(buf, 0, 8); 
  }
  
  std::cout << "after read: " << std::endl
            << "totalSize : " << r->totalSize()  << std::endl
            << "remainSize : " << r->remainSize()  << std::endl;

}

void testStoragePartition(WebService::StoragePartition* pat)
{
  std::cout << "==========" << __func__ << "===========" << std::endl;
  
  std::cout << "partition name : " << pat->name() << std::endl
            << "capacitySize : " << pat->capacitySize() << std::endl
            << "usedSize : " << pat->usedSize() << std::endl;
            
  testStoragePartitionReader(pat->createReader(0, 0));
  
  return ;
}

void testStorageDisk(WebService::StorageDisk* disk)
{
  std::cout << "==========" << __func__ << "===========" << std::endl;
  std::cout << "partition name list: " << std::endl;
  auto nameList = disk->partitionNameList();
  for(auto& i : nameList){
    std::cout << '\t' << i << std::endl;
  }
  std::cout << "\r\n" << std::endl;
  
  auto pat = disk->partition("Fake Disk Partition");
  if(pat){
    testStoragePartition(pat);
  }
  
  return ;
}

void testStorageManager()
{
  std::cout << "==========" << __func__ << "===========" << std::endl;
  
  auto sm = WebService::StorageManager::instance();
  auto nameList = sm->diskNameList();
  std::cout << "disk name list: " << std::endl;
  for(auto& i : nameList){
    std::cout << '\t' << i << std::endl;
  } 
  
  std::cout << "\r\n" << std::endl;
  auto disk = sm->disk("Fake Disk");
  if(disk){
    testStorageDisk(disk);
  }
  
  
  return ;
}

void testAssign()
{
  #define assignVal(k1, k2, v1, v2) std::cout << k1 << "_" << k2 << " = " << v1 << "_" << v2 << std::endl;

  std::vector<std::pair<std::string, std::string>> p = {
    {"S", "P"},
    {"H", "P"}
  };
  
  std::vector<std::pair<std::string, std::string>> c = {
    {"s", "s"},
    {"a", "a"},
  };

  for(auto& i : p){
    for(auto& j : c){
      assignVal(i.first, j.first, i.second, j.second);
    }
  }
  return ;
}

int main()
{
  testStorageManager();
  
  testAssign();
  
  testManager();
  
  return 0;
}

