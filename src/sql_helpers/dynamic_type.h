#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_DYNAMIC_TYPE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_DYNAMIC_TYPE_H

namespace tbe {
  namespace sql {

class DynamicType
{
  public:
    enum Kind
    {
      INT = 1,
      TEXT
    };

    DynamicType(Kind kind);
    
    virtual
    ~DynamicType() = 0;

    Kind getKind() const;


  private:
    Kind kind_;
};

  }
}

#endif