# derived from https://arcanis.me/en/2015/10/17/cppcheck-and-clang-format/
#
# additional target to perform cppcheck run, requires cppcheck 
# get all project files 
# HACK this workaround is required to avoid qml files checking ^_^
#
file(GLOB_RECURSE ALL_CHECK_FILES "src/*.hpp" "src/*.cpp")

add_custom_target(cppcheck 
  COMMAND cppcheck
        --enable=all
        --std=c++14
        --verbose
        --quiet
  ${ALL_CHECK_FILES}
  )