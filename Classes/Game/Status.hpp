//
// this file is auto generated
// by structbuilder<https://github.com/zsuzuki/structbuilder>
//
#pragma once

#include <sol.hpp>
namespace Game
{

//
class Status
{
public:
protected:
  // members
  uint32_t score;

public:
  // constructor
  Status() { setScore(0); }
  //
  static void setLUA(sol::state& lua);
  // interface
  //
  const uint32_t getScore() const { return score; }
  void           setScore(uint32_t n) { score = n; }
};
} // namespace Game
