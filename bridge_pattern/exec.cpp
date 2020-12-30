#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Abstract;

// Implementation
class AbstractImpl {
public:
  virtual void executeImpl(const Abstract &abs) const = 0;
};

// Abstraction, for example an abstract OS
class Abstract {
public:
  Abstract(AbstractImpl *impl) : _impl(impl) {}
  virtual std::string osName() const = 0;
  virtual std::string appStore() const = 0;
  virtual std::string graphicAPI() const = 0;
  virtual ~Abstract() {}

  void execute() const { _impl->executeImpl(*this); }

protected:
  AbstractImpl *_impl;
};

// concrete implementation: buy game in app store
class ConcreteImpl1 : public AbstractImpl {
  void executeImpl(const Abstract &abs) const override {
    std::cout << "In " << abs.osName() << " system, buy DOTA 2 in the "
              << abs.appStore() << "." << std::endl;
  }
};

// concrete implementation: play triple A game
class ConcreteImpl2 : public AbstractImpl {
  void executeImpl(const Abstract &abs) const override {
    std::cout << "In " << abs.osName() << " system, play Tomb Raider via "
              << abs.graphicAPI() << "." << std::endl;
  }
};

// concrete: mac os
class Concrete1 : public Abstract {
public:
  Concrete1(AbstractImpl *impl) : Abstract(impl) {}
  virtual std::string osName() const { return "mac OS"; }
  virtual std::string appStore() const { return "mac app store"; }
  virtual std::string graphicAPI() const { return "Vulkan"; }
};

// concrete: windows
class Concrete2 : public Abstract {
public:
  Concrete2(AbstractImpl *impl) : Abstract(impl) {}
  virtual std::string osName() const { return "windows"; }
  virtual std::string appStore() const { return "microsoft app store"; }
  virtual std::string graphicAPI() const { return "DirectX"; }
};

int main() {
  auto buyInMacOS = new Concrete1(new ConcreteImpl1);
  auto buyInWindows = new Concrete2(new ConcreteImpl1);
  buyInMacOS->execute();
  buyInWindows->execute();

  auto playInMacOS = new Concrete1(new ConcreteImpl2);
  auto playInWindows = new Concrete2(new ConcreteImpl2);
  playInMacOS->execute();
  playInWindows->execute();
  return 0;
}
