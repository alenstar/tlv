#pragma once

#include "descriptor.h"
#include "errors.h"
#include "rocks_wrapper.h"
#include "table.h"
#include <iostream>

namespace aquadb
{

struct DBOption
{
    std::string dbname;
    std::string dbpath;
    bool readonly;
};

class DBManager
{
  public:
    static DBManager *get_instance()
    {
        static DBManager _instance;
        return &_instance;
    }
    ~DBManager();

    int init(const std::string &basepath);
    int init(const char *basepath)
    {
        std::string s(basepath);
        return init(s);
    }
    int open(const std::string &dbname, bool auto_create = false);
    int open(const char *dbname, bool auto_create = false)
    {
        std::string s(dbname);
        return open(s, auto_create);
    }
    int create(const std::string &dbname);
    int create_kv_table(const std::string &dbname, const std::string &tblname, FieldDescriptor::FieldType key_type = FieldDescriptor::FieldType::String, bool if_not_exists = true);
    int create_table(const std::string &dbname, TableDescriptorPtr& descriptor, bool if_not_exists = true);
    int close(const std::string &dbname);
    int close(const char *dbname)
    {
        std::string s(dbname);
        return close(s);
    }
    int close_all();
    bool exists(const std::string &dbname);
    bool drop(const std::string &dbname);

    TableReaderPtr get_table_reader(const std::string &dbname, const std::string &tblname);
    TableOperatorPtr get_table_writer(const std::string &dbname, const std::string &tblname);
    TableDescriptorPtr get_table_descriptor(const std::string &dbname, const std::string &tblname);

    RocksWrapper* get_wrapper() {return _wrapper;}
  private:
    DBManager();

    DatabaseDescriptorPtr get_db_descriptor(const std::string &dbname) { auto it = _name2dbi.find(dbname);
    if(it != _name2dbi.cend()) {return it->second;}
    return nullptr;
     }
    std::string _basepath;
    RocksWrapper* _wrapper{nullptr};
    // lmdb::env _env{nullptr};
    // std::map<std::string,uint32_t> _name2dbi;
    std::map<std::string, DatabaseDescriptorPtr> _name2dbi;
    uint32_t _last_dbid{0}; // 最近的库id
};
}