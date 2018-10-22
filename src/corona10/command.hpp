#ifndef _COMMAND_HPP
#define _COMMAND_HPP

#include <vector>

namespace corona10 {

class Light {
public:
  Light();
  ~Light() = default;

  bool brightness_up();
  bool brightness_down();

  inline bool is_turn_on() { return _is_on; }

  inline int get_brigtness() { return _brightness; }

private:
  int _brightness;
  const int _max_brightness = 100;

  bool _is_on;
};

class Command {
public:
  virtual void execute() = 0;
  virtual void undo() = 0;
};

class BrightnessUpCommand : public Command {
public:
  explicit BrightnessUpCommand(Light *light) : _light(light) {}
  void execute() override;
  void undo() override;

private:
  Light *_light;
};

class BrightnessDownCommand : public Command {
public:
  explicit BrightnessDownCommand(Light *light) : _light(light) {}
  void execute() override;
  void undo() override;

private:
  Light *_light;
};

class CmdStack {
public:
  void add(Command *c) { _commands.push_back(c); }
  void run(void) {
    for (auto &command : _commands) {
      command->execute();
    }
    _commands.clear();
  }

  void undo(void) {
    if (_commands.size() >= 1) {
      _commands.pop_back();
    }
  }

private:
  std::vector<Command *> _commands;
};
} // namespace corona10
#endif