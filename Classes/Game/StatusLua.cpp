//
// this file is auto generated
// by structbuilder<https://github.com/zsuzuki/structbuilder>
//
#include <sol/sol.hpp>

namespace Game
{
void
Status::setLUA(sol::state& lua)
{
  lua.new_usertype<Status>("Status", "score", &Status::score);
}

} // namespace Game
