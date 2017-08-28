#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>
#include <list>
#include <ctime>

namespace WebService {
    class SignalPrivate;

    ///
    /// \brief 信号类
    ///        定义了读一个信号的操作
    ///
    class Signal
    {
        public:
            enum Type { //  信号的数据类型定义
                Uint64,
                Int64,
                UInt32,
                Int32,
                UInt16,
                Int16,
                UInt8,
                Int8,
                Bool,
                DateTime,
                String,
            };

            Signal();
            ~Signal();

            std::string name() const;  //   获取信号名称

            Signal::Type type() const;  //  获取信号类型

            //  获取/设置信号的值
            bool getValue ( unsigned char* value );
            bool setValue ( unsigned char value );

            bool getValue ( unsigned short* value );
            bool setValue ( unsigned short value );

            bool getValue ( unsigned long* value );
            bool setValue ( unsigned long value );

            bool getValue ( unsigned long long* value );
            bool setValue ( unsigned long long value );

            bool getValue ( bool* value );
            bool setValue ( bool value );

            bool getValue ( std::string* value );
            bool setValue ( const std::string &value );

            bool getValue ( std::tm* value );
            bool setValue ( const std::tm &value );

        private:
            SignalPrivate* priv;
    };

    ///
    /// \brief 信号组类
    ///        信号是分组组织管理，每个信号组中包含多个信号
    ///
    class SignalGroup
    {
        public:
            virtual ~SignalGroup() {}

            virtual std::string name() const = 0;   //  获取信号组的名称

            virtual std::list<std::string> signalNameList() const = 0;  //  获取当前信号组中所有信号的名称列表

            virtual Signal* signal ( const std::string &signalName ) = 0;   //  根据信号名称获取信号指针
    };

    ///
    /// \brief 信号组管理类
    ///        管理当前系统中所有的信号组
    ///
    class SignalManager
    {
        public:
            std::list<std::string> groupNameList() const;   //  获取信号组名称列表

            SignalGroup* group ( const std::string &groupName );    //  更具信号组名称获取信号组的指针

            static SignalManager* instance();   //  单例模式，返回信号组管理者的指针
    };

    ///
    /// \brief 数据存储分区读取类
    ///        定义如何在存储磁盘分区读取数据
    ///
    class StoragePartitionReader
    {
        public:
            virtual ~StoragePartitionReader() {}

            virtual unsigned long long totalSize() const = 0;   //  获取读数据的总大小

            virtual unsigned long long remainSize() const = 0;  //  获取剩余读数据的空间大小

            virtual unsigned long long read ( unsigned char* buf, unsigned long long size ) = 0;    //  读数据

            virtual bool isEnd() const = 0; //  判断数据是否读结束
    };

    ///
    /// \brief 数据存储分区类
    ///        一个存储介质上可能存在多个分区
    ///
    class StoragePartition
    {
        public:
            virtual ~StoragePartition() {}

            virtual std::string name() const = 0;   //  获取当前分区的名称

            virtual unsigned long long capacitySize() const = 0;    //  获取当前分区的总容量

            virtual unsigned long long usedSize() const = 0;    //  获取当前分区的已使用的空间大小

            virtual bool getFirstDateTime ( std::tm* firstDateTime ) = 0;   //  获取当前分区中最早的记录日期

            virtual bool getLastDateTime ( std::tm* lastDateTime ) = 0;  //  获取当前分区中最近的记录日期

            virtual bool getFirstMileage ( unsigned long long* firstMileage ) = 0;   //  获取当前分区中最早的里程记录

            virtual bool getLastMileage ( unsigned long long* lastMileage ) = 0;  //  获取当前分区中最近的里程记录

            virtual StoragePartitionReader* createReader ( const std::tm &beginDateTime, const std::tm &endDateTime ) = 0;  // 按记录日期范围创建一个数据读取者对象去读数据

            virtual StoragePartitionReader* createReader ( unsigned long long beginMileage, unsigned long long endMileage ) = 0;  // 按记录里程范围创建一个数据读取者对象去读数据
    };

    ///
    /// \brief 存储介质类
    ///        一个设备中可能存在多个不同类型的存储介质
    ///        例如：USB Flash，EMMC，CF Card
    ///
    class StorageDisk
    {
        public:
            virtual ~StorageDisk() {}

            virtual std::string name() const = 0;   //  获取当前存储介质的名称

            virtual std::list<std::string> partitionNameList() const = 0;   //  获取当前存储介质上的所有分区名称列表

            virtual StoragePartition* partition ( const std::string &partitionName ) = 0;   //  根据分区名称获取分区的指针
    };

    ///
    /// \brief 数据存储管理者类
    ///
    class StorageManager
    {
        public:
            std::list<std::string> diskNameList() const;    //  获取当前设备中所有的存储介质名称列表

            StorageDisk* disk ( const std::string &diskName );  //  根据介质名称获取介质的指针

            static StorageManager* instance();  //  获取存储管理者的指针
    };

}

#endif // SIGNAL_H
