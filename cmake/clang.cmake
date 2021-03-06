# from https://arcanis.me/en/2015/10/17/cppcheck-and-clang-format
# additional target to perform clang-format run, requires clang-format 

# get all project files 

file(GLOB_RECURSE ALL_CHECK_FILES "src/*.hpp" "src/*.cpp") 

add_custom_target(clangformat 
  COMMAND clang-format
  -style=LLVM 
  ${ALL_CHECK_FILES}
  -i
  ) 