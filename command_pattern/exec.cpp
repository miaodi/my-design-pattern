#include <iostream>
#include <memory>
#include <string>

class Command {
public:
  ~Command() {}
  virtual void execute() const = 0;
};

class JumpCommand : public Command {
public:
  void execute() const override { std::cout << "Jump\n"; }
};

class FireCommand : public Command {
public:
  void execute() const override { std::cout << "Fire\n"; }
};

class OptionCommand : public Command {
public:
  void execute() const override { std::cout << "Option\n"; }
};

class ReloadCommand : public Command {
public:
  void execute() const override { std::cout << "Reload\n"; }
};

class JoyPad {
public:
  void pushA() const { _keyA->execute(); }

  void pushB() const { _keyB->execute(); }

  void pushX() const { _keyX->execute(); }

  void pushY() const { _keyY->execute(); }

private:
  std::unique_ptr<Command> _keyX;
  std::unique_ptr<Command> _keyY;
  std::unique_ptr<Command> _keyA;
  std::unique_ptr<Command> _keyB;
};

int main() {
  std::cout << "?";
  return 0;
}
