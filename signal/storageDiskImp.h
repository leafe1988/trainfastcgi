#ifndef __STORAGE_DISK_IMP_H__
#define __STORAGE_DISK_IMP_H__

#include <unordered_map>
#include <memory>
#include "signal.h"


namespace WebService{

class StorageDiskImp : public StorageDisk
{
public:
  virtual ~StorageDiskImp(){}
  
  virtual std::string name() const
  {
    return mName;
  }
  
  virtual std::list<std::string> partitionNameList() const
  {
    return mPartitionNames;
  }
  
  virtual StoragePartition* partition ( const std::string& partitionName )
  {
    if(!mIsPartitionTableInit){
      initPartitionTable();
      mIsPartitionTableInit = true;
    }
    
    auto it = mPartitionTable.find(partitionName);
    if(it != mPartitionTable.end()){
      return it->second.get();
    }
    
    return NULL;   
  }
protected:
  virtual void initPartitionTable() = 0;  
protected:
  std::string mName;
  std::list<std::string> mPartitionNames;
  std::unordered_map<std::string, std::shared_ptr<StoragePartition>> mPartitionTable;
  bool mIsPartitionTableInit = false;   
};



class FakeDisk : public StorageDiskImp
{
public:
  FakeDisk();
  virtual ~FakeDisk(){}
protected:
  virtual void initPartitionTable();
};

}

#endif //__STORAGE_DISK_IMP_H__