#include "signal.h"
#include "storageDiskImp.h"

namespace WebService {

struct storage_t{
  std::list<std::string> mDiskNames{{
    "USB Flash",
    "EMMC",
    "CF Card",
    "Fake Disk"
  }};
  
  std::unordered_map<std::string, std::shared_ptr<StorageDisk>> mDiskTable;
  
  bool mIsDiskTableInit = false;
}gStorage;

StorageManager gStorageManager;



std::list<std::string> StorageManager::diskNameList() const
{
  return gStorage.mDiskNames;
}

static void StorageManager_initDiskTable()
{
  //fake implement
  gStorage.mDiskTable["Fake Disk"] = std::make_shared<FakeDisk>();

  gStorage.mIsDiskTableInit = true;
  return ;
}

StorageDisk* StorageManager::disk ( const std::string& diskName )
{
  if(!gStorage.mIsDiskTableInit){
    StorageManager_initDiskTable();
  }
  
  auto it = gStorage.mDiskTable.find(diskName);
  if(it != gStorage.mDiskTable.end()){
    return it->second.get();
  }
  
  return NULL;
}

StorageManager* StorageManager::instance()
{
  return &gStorageManager;
}



}