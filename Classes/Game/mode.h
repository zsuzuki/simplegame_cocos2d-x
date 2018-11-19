//
#pragma once

namespace Game
{

//
class Mode
{
public:
  virtual ~Mode()                   = default;
  virtual void initialize()         = 0;
  virtual bool completeInitialize() = 0;
  virtual void finalize()           = 0;
  virtual bool completeFinalize()   = 0;
  virtual void update(float dt)     = 0;
};

} // namespace Game
