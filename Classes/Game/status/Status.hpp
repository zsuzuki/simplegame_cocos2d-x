//
// this file is auto generated
// by structbuilder<https://github.com/zsuzuki/structbuilder>
//
#pragma once

#include <cstdint>

namespace Game
{

//
class Status
{
public:
protected:
  // members
  uint32_t score;
  float    field_width;
  float    field_height;

public:
  // constructor
  Status()
  {
    setScore(0);
    setFieldWidth(1024);
    setFieldHeight(1024);
  }
  // interface
  //
  const uint32_t getScore() const { return score; }
  void           setScore(uint32_t n) { score = n; }
  //
  const float getFieldWidth() const { return field_width; }
  void        setFieldWidth(float n) { field_width = n; }
  //
  const float getFieldHeight() const { return field_height; }
  void        setFieldHeight(float n) { field_height = n; }
};
} // namespace Game
