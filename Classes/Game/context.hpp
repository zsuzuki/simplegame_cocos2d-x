//
//  context.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/20.
//

#ifndef context_hpp
#define context_hpp

#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace Game
{

class Context
{
  class Module
  {
  public:
    virtual ~Module() = default;
  };
  using ModPtr       = std::shared_ptr<Module>;
  using LabelCompare = bool (*)(const char*, const char*);
  using LabelMap     = std::map<const char*, ModPtr, LabelCompare>;
  LabelMap mod_list{[](auto* a, auto* b) { return std::strcmp(a, b) < 0; }};

public:
  //
  // コンテキスト生成 auto p = context.create<T>("name", 0, 1);
  //
  template <class T, class... Args>
  std::shared_ptr<T> create(const char* name, Args... a)
  {
    struct M : public T, Module
    {
      M(Args... a) : T(a...) {}
    };
    auto Tptr      = std::make_shared<M>(a...);
    mod_list[name] = Tptr;
    return Tptr;
  }
  //
  // コンテキスト生成 auto p = context.create<T>("name");
  //
  template <class T>
  std::shared_ptr<T> create(const char* name)
  {
    struct M : public T, Module
    {
      M() = default;
    };
    auto Tptr      = std::make_shared<M>();
    mod_list[name] = Tptr;
    return Tptr;
  }

  //
  // コンテキスト取得　auto p = context.get<T>("name");
  //
  template <class T>
  std::shared_ptr<T> get(const char* name)
  {
    auto p = mod_list[name];
    if (p)
    {
      return std::dynamic_pointer_cast<T>(p);
    }
    return nullptr;
  }
};
} // namespace Game

#endif /* context_hpp */
