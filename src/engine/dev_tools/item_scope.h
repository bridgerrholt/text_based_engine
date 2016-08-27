/// @file item_scope.h
/// Declaration of the class template tbe::ItemScope.

/// @class tbe::ItemScope
/// Contains maps for "global", "shared", and "local" states.
/// Each map allows item access by index or
/// a specified type (std::string by default).

#ifndef TEXT_BASED_ENGINE_ENGINE_ITEM_SCOPE_H
#define TEXT_BASED_ENGINE_ENGINE_ITEM_SCOPE_H

#include <array>
#include <string>
#include <vector>
#include <unordered_map>

#include "game_state.h"

namespace tbe {

template <class T, class K = std::string>
class ItemScope
{
  public:
    typedef T Item;
    typedef K Key;

    /// Used under the hood.
    typedef std::vector<Item> ItemList;

    /// Used to access items by index rather than the slower access by key.
    typedef typename ItemList::size_type ItemIndex;

    /// Maps key values to indexes.
    typedef std::unordered_map<
      Key, ItemIndex
    > IndexMap;


    /// Used for templates.
    enum Scope
    {
      GLOBAL = 0,
      SHARED,
      LOCAL
    };


    /// Inserts a new item with the given key.
    template <Scope s>
    void insert(Key         key, Item item);

    /// Erases a specified item.
    template <Scope s>
    void erase (Key const & key);
    template <Scope s>
    void erase (ItemIndex   index);

    /// Finds the given key or index within the template-passed scope,
    /// returns nullptr if can't find.
    template <Scope s>
    Item & find(Key         key);
    template <Scope s>
    Item & find(ItemIndex   index);

    /// Finds the given key or index starting at the highest-value scope,
    /// returns nullptr if can't find.
    Item & find(Key         key);
    Item & find(ItemIndex   index);

    /// Finds the given key or index within the template-passed scope,
    /// throws an exception if can't find.
    template <Scope s>
    Item & at  (Key         key);
    template <Scope s>
    Item & at  (ItemIndex   index);

    /// Finds the given key or index starting at the highest-value scope,
    /// throws an exception if can't find.
    Item & at  (Key         key);
    Item & at  (ItemIndex   index);


  private:
    constexpr static
    std::size_t SCOPE_COUNT { 3 };

    constexpr
    void verifyScopeIndex(std::size_t index);

    template <Scope s>
    void pureErase(ItemIndex index);

    std::array<IndexMap, SCOPE_COUNT> maps_;
    std::array<ItemList, SCOPE_COUNT> lists_;
};



template <class T, class K>
constexpr
void
ItemScope<T, K>::verifyScopeIndex(std::size_t index)
{
  static_assert(index < SCOPE_COUNT, "Invalid scope index");
}



template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
void
ItemScope<T, K>::insert(Key key, Item item)
{
  verifyScopeIndex(s);

  assert(maps_[s].count(key) == 0);

  maps_[s].insert({ std::move(key), lists_[s].size() });
  lists_[s].push_back(std::move(item));
}



template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
void
ItemScope<T, K>::pureErase(ItemIndex index)
{
  assert(index < lists_[s].size());

  lists_[s].erase(lists_[s].begin() + index);

  for (auto i = maps_[s].begin(); i != maps_[s].end(); ++i) {
    if (i->second == index)
      maps_[s].erase(i);
    else if (i->second > index)
      i->second -= 1;
  }
}



template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
void
ItemScope<T, K>::erase(Key const & key)
{
  verifyScopeIndex(s);

  assert(maps_[s].count(key) == 1);

  pureErase(lists_[s][key]);
}


template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
void
ItemScope<T, K>::erase(ItemIndex index)
{
  verifyScopeIndex(s);

  pureErase(index);
}




template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::find(Key key)
{
  verifyScopeIndex(s);

  if (maps_[s].count(key) == 1)
    return lists_.at(maps_[s][key]);

  else
    return nullptr;

}


template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::find(ItemIndex index)
{
  verifyScopeIndex(s);

  if (index < lists_[s].size())
    return lists_[s].at(index);

  else
    return nullptr;
}


template <class T, class K>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::find(Key key)
{
  Item * item = &find<LOCAL>(key);

  if (item != nullptr)
    return item;

  item =        &find<SHARED>(key);

  if (item != nullptr)
    return item;

  return        &find<GLOBAL>(key);
}


template <class T, class K>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::find(ItemIndex index)
{
  Item * item = &find<LOCAL>(index);

  if (item != nullptr)
    return item;

  item =        &find<SHARED>(index);

  if (item != nullptr)
    return item;

  return        &find<GLOBAL>(index);
}



template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::at(Key key)
{
  Item & item = find<s>(key);

  assert(item != nullptr);

  return item;
}


template <class T, class K>
template <typename ItemScope<T, K>::Scope s>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::at(ItemIndex index)
{
  Item & item = find<s>(index);

  assert(item != nullptr);

  return item;
}


template <class T, class K>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::at(Key key)
{
  Item & item = find(key);

  assert(item != nullptr);

  return item;
}


template <class T, class K>
typename
ItemScope<T, K>::Item &
ItemScope<T, K>::at(ItemIndex index)
{
  Item & item = find(index);

  assert(item != nullptr);

  return item;
}



}

#endif