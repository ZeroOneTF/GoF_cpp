#include <fstream>

#include "gtest/gtest.h"

#include "corona10/command.hpp"

TEST(command, LightTurnOnTest) {
  corona10::Light* light = new corona10::Light();
  EXPECT_EQ(light->get_brigtness(), 0);
  EXPECT_FALSE(light->is_turn_on());
  corona10::CmdStack cmd;
  corona10::BrightnessUpCommand up(light);
  cmd.add(&up);
  cmd.run();
  EXPECT_TRUE(light->is_turn_on());
  EXPECT_EQ(light->get_brigtness(), 1);
  delete light;
}

TEST(command, LightTurnOffTest) {
  corona10::Light* light = new corona10::Light();
  EXPECT_EQ(light->get_brigtness(), 0);
  EXPECT_FALSE(light->is_turn_on());
  corona10::CmdStack cmd;
  corona10::BrightnessDownCommand down(light);
  cmd.add(&down);
  cmd.run();
  EXPECT_FALSE(light->is_turn_on());
  EXPECT_EQ(light->get_brigtness(), 0);
  delete light;
}

TEST(command, LightBrightnessUpDown1000Test) {
  corona10::Light* light = new corona10::Light();
  EXPECT_EQ(light->get_brigtness(), 0);
  EXPECT_FALSE(light->is_turn_on());
  corona10::CmdStack cmd;
  for(int i = 0; i < 1000; i++) {
    corona10::BrightnessUpCommand up(light);
    cmd.add(&up);
  }
  cmd.run();
  EXPECT_TRUE(light->is_turn_on());
  EXPECT_EQ(light->get_brigtness(), 100);
  for(int i = 0; i < 2000; i++) {
    corona10::BrightnessDownCommand down(light);
    cmd.add(&down);
  }
  cmd.run();
  EXPECT_FALSE(light->is_turn_on());
  EXPECT_EQ(light->get_brigtness(), 0);
  delete light;
}