//
// this file is auto generated
// by structbuilder<https://github.com/zsuzuki/structbuilder>
//
#pragma once

#include <string>

namespace Game
{

//
class Player
{
public:
protected:
  struct BitField
  {
    unsigned hp : 10;
  };
  BitField bit_field;
  // members
  std::string name;
  float       x;
  float       y;

public:
  // constructor
  Player()
  {
    setHp(0);
    setX(0);
    setY(0);
  }
  // interface
  //
  unsigned getHp() const { return bit_field.hp * 1 + 0; }
  void     setHp(unsigned n) { bit_field.hp = (n - 0) / 1; }
  //
  const std::string& getName() const { return name; }
  void               setName(std::string n) { name = n; }
  //
  const float getX() const { return x; }
  void        setX(float n) { x = n; }
  //
  const float getY() const { return y; }
  void        setY(float n) { y = n; }
};
} // namespace Game
