#include <iostream>
#include <list>
#include <memory>
#include <string>

class Command {
public:
  virtual ~Command() {}
  virtual void execute() const = 0;
};

// TV is the receiver of a command
class TV {
public:
  TV(const std::string &name) : _name(name) {}
  std::string name() const { return _name; }

private:
  std::string _name;
};

class Channel1 : public Command {
  TV *_tv;

public:
  Channel1(TV *tv) : _tv(tv) {}
  void execute() const override {
    std::cout << "Switch to channel 1 for " + _tv->name() << std::endl;
  }
};

class Channel2 : public Command {
  TV *_tv;

public:
  Channel2(TV *tv) : _tv(tv) {}
  void execute() const override {
    std::cout << "Switch to channel 2 for " + _tv->name() << std::endl;
  }
};

class TurnOn : public Command {
  TV *_tv;

public:
  TurnOn(TV *tv) : _tv(tv) {}
  void execute() const override {
    std::cout << "Turn on " + _tv->name() << std::endl;
  }
};

class TurnOff : public Command {
  TV *_tv;

public:
  TurnOff(TV *tv) : _tv(tv) {}
  void execute() const override {
    std::cout << "Turn off " + _tv->name() << std::endl;
  }
};
class Remoter {
public:
  void executeCommand(std::unique_ptr<Command> &&ptr) {
    _commands.emplace_back(std::move(ptr));
    _commands.back()->execute();
  }

  void back() {
    if (_commands.empty())
      return;
    _commands.pop_back();
    _commands.back()->execute();
  }

private:
  std::list<std::unique_ptr<Command>> _commands;
};

int main() {
  auto tv(std::make_unique<TV>("tv1"));
  auto remoter(std::make_unique<Remoter>());
  remoter->executeCommand(std::make_unique<TurnOn>(tv.get()));
  auto ptr{std::make_unique<TurnOff>(tv.get())};
  remoter->executeCommand(std::move(ptr));
  remoter->executeCommand(std::make_unique<Channel1>(tv.get()));
  remoter->back();
  return 0;
}
