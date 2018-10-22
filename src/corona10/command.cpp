#include "corona10/command.hpp"

namespace corona10 {

Light::Light() : _brightness(0), _is_on(false) {}

bool Light::brightness_up() {
  _is_on = true;
  if (_brightness < _max_brightness) {
    _brightness++;
    return true;
  }
  return false;
}

bool Light::brightness_down() {
  if (_brightness > 0) {
    _brightness--;
    return true;
  }
  _is_on = false;
  return false;
}

void BrightnessUpCommand::execute() { _light->brightness_up(); }

void BrightnessUpCommand::undo() { _light->brightness_down(); }

void BrightnessDownCommand::execute() { _light->brightness_down(); }

void BrightnessDownCommand::undo() { _light->brightness_up(); }

} // namespace corona10