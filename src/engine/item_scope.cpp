#include "item_scope.h"

namespace tbe {

constexpr
void
ItemScope::verifyScopeIndex(std::size_t index)
{
  static_assert(index < SCOPE_COUNT);
}

}