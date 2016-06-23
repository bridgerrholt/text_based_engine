#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_INFO_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_INFO_H

#include <string>
#include <unordered_map>

#include "dynamic_type.h"

namespace tbe {
  namespace sql {

class ColumnInfoBase
{
  public:
    ColumnInfoBase(std::string const & name,
                   DynamicType::Kind   kind);

    std::string const & getName() const { return name_; }
    DynamicType::Kind   getKind() const { return kind_; }


  private:
    std::string       name_;
    DynamicType::Kind kind_;
};



class ColumnList;

class ColumnInfo : public ColumnInfoBase
{
  public:
    friend ColumnList;

    ColumnInfo(std::string const & name,
               DynamicType::Kind   kind);

    size_t getId() const { return id_; }


  private:
    void setId(size_t id);

    size_t id_;
};



class ColumnInfoMapped : public ColumnInfoBase
{
  public:
    friend ColumnList;

    ColumnInfoMapped(std::string const & name,
                     DynamicType::Kind   kind);

    size_t getId(size_t columnListId) const;


  private:
    void setId(size_t id, size_t columnListId);

    std::unordered_map<size_t, size_t> idMap_;
};



  }
}

#endif