#include "storageDiskImp.h"

#include <cstring>
#include <vector>
#include <algorithm>
namespace WebService {

//________________________________________________________________________
class FakePartitionReader : public StoragePartitionReader
{
public:
  virtual ~FakePartitionReader() {}

  //  获取读数据的总大小
  virtual unsigned long long totalSize() const
  {
    return mTotalSize;
  }

  //  获取剩余读数据的空间大小
  virtual unsigned long long remainSize() const
  {
    return mRemainSize;
  }

  //  读数据
  virtual unsigned long long read ( unsigned char* buf, unsigned long long size )
  {
    auto bytes = std::min(mRemainSize, size);
    auto index = mTotalSize - mRemainSize;
    
    memcpy(buf, &mData[index], bytes);
    
    mRemainSize -= bytes;
    
    return bytes;
  }

  //  判断数据是否读结束
  virtual bool isEnd() const
  {
    return mRemainSize == 0;
  }
private:
  std::vector<unsigned char> mData{{
      0x55, 0x73, 0x65, 0x72, 0x2D, 0x41, 0x67, 0x65, 0x6E, 0x74, 0x3A, 0x20, 0x4D, 0x6F, 0x7A, 0x69,
      0x6C, 0x6C, 0x61, 0x2F, 0x35, 0x2E, 0x30, 0x20, 0x28, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x73,
      0x20, 0x4E, 0x54, 0x20, 0x36, 0x2E, 0x31, 0x3B, 0x20, 0x57, 0x4F, 0x57, 0x36, 0x34, 0x29, 0x20,
      0x41, 0x70, 0x70, 0x6C, 0x65, 0x57, 0x65, 0x62, 0x4B, 0x69, 0x74, 0x2F, 0x35, 0x33, 0x37, 0x2E,
      0x33, 0x36, 0x20, 0x28, 0x4B, 0x48, 0x54, 0x4D, 0x4C, 0x2C, 0x20, 0x6C, 0x69, 0x6B, 0x65, 0x20,
      0x47, 0x65, 0x63, 0x6B, 0x6F, 0x29, 0x20, 0x43, 0x68, 0x72, 0x6F, 0x6D, 0x65, 0x2F, 0x35, 0x39,
      0x2E, 0x30, 0x2E, 0x33, 0x30, 0x37, 0x31, 0x2E, 0x31, 0x31, 0x35, 0x20, 0x53, 0x61, 0x66, 0x61,
      0x72, 0x69, 0x2F, 0x35, 0x33, 0x37, 0x2E, 0x33, 0x36, 0x20, 0x4F, 0x50, 0x52, 0x2F, 0x34, 0x36,
      0x2E, 0x30, 0x2E, 0x32, 0x35, 0x39, 0x37, 0x2E, 0x35, 0x37, 0x20, 0x28, 0x45, 0x64, 0x69, 0x74,
      0x69, 0x6F, 0x6E, 0x20, 0x42, 0x61, 0x69, 0x64, 0x75, 0x29, 0x0D, 0x0A
  }};

  unsigned long long mTotalSize = mData.size();
  unsigned long long mRemainSize = mData.size();
};

//________________________________________________________________________
class FakeDiskPartition : public StoragePartition
{
public:
  virtual ~FakeDiskPartition() {}

  virtual std::string name() const
  {
    return mName;
  }

  //  获取当前分区的总容量
  virtual unsigned long long capacitySize() const
  {
    return 1024;
  }

  //  获取当前分区的已使用的空间大小
  virtual unsigned long long usedSize() const
  {
    return 256;
  }

  //  获取当前分区中最早的记录日期
  virtual bool getFirstDateTime ( std::tm* firstDateTime )
  {
    memcpy(firstDateTime, &mBegDate, sizeof(std::tm));
    return true;
  }

  //  获取当前分区中最近的记录日期
  virtual bool getLastDateTime ( std::tm* lastDateTime )
  {
    memcpy(lastDateTime, &mEndDate, sizeof(std::tm));
    return true;
  }

  //  获取当前分区中最早的里程记录
  virtual bool getFirstMileage ( unsigned long long* firstMileage )
  {
    *firstMileage = mBegMileage;
    return true;
  }

  //  获取当前分区中最近的里程记录
  virtual bool getLastMileage ( unsigned long long* lastMileage )
  {
    *lastMileage = mEndMileage;
    return true;
  }

  // 按记录日期范围创建一个数据读取者对象去读数据
  virtual StoragePartitionReader* createReader ( const std::tm &beginDateTime, const std::tm &endDateTime )
  {
    auto s = std::make_shared<FakePartitionReader>();
    mRecord.push_back(s);
    return s.get();
  }

  // 按记录里程范围创建一个数据读取者对象去读数据
  virtual StoragePartitionReader* createReader ( unsigned long long beginMileage, unsigned long long endMileage )
  {
    auto s = std::make_shared<FakePartitionReader>();
    mRecord.push_back(s);
    return s.get();
  }
private:
  std::string mName = "Fake Disk Partition";
  
  std::tm mBegDate {{}};
  std::tm mEndDate {{}};
  
  unsigned long long mBegMileage = 512;
  unsigned long long mEndMileage = 1024;
  
  std::vector<std::shared_ptr<StoragePartitionReader>> mRecord;
};

//________________________________________________________________________
FakeDisk::FakeDisk()
{
  mName.assign("Fake Disk");
  
  mPartitionNames = {
    "Fake Disk Partition",
  };
}

void FakeDisk::initPartitionTable()
{
  mPartitionTable["Fake Disk Partition"] = std::make_shared<FakeDiskPartition>();
  
  return ;
}

}
