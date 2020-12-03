#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

class User;

class AbstractChatRoom {
public:
  virtual void join(User *user) = 0;
  virtual void broadcast(const std::string &from,
                         const std::string &message) = 0;
  virtual void notice(const std::string &from, const std::string &name,
                      const std::string &message) = 0;
};

class User {
private:
  std::string _name;
  AbstractChatRoom *_chat;
  std::vector<std::string> _chatLog;

public:
  User(const std::string &name, AbstractChatRoom *chat)
      : _name(name), _chat(chat) {
    _chat->join(&*this);
  }

  void pm(const std::string &name, const std::string &message) const {
    _chat->notice(_name, name, message);
  }
  void say(const std::string &message) const {
    _chat->broadcast(_name, message);
  }

  void receive(const std::string &from, const std::string &message) {
    auto str = "From: " + from + ". To: " + _name + ". Message: " + message;
    std::cout << str << std::endl;
    _chatLog.push_back(str);
  }

  const std::string &name() const { return _name; }

  void printLog() const {
    for (const auto &i : _chatLog) {
      std::cout << i << std::endl;
    }
  }
};

class ConcreteChatRoom : public AbstractChatRoom {
  std::map<std::string, User *> _users;

public:
  void join(User *user) override {
    if (_users.count(user->name()) == 0) {

      broadcast("GM", user->name() + " joined our chat room.");
      _users.emplace(std::make_pair(user->name(), user));
    }
  }

  void broadcast(const std::string &from, const std::string &message) override {
    for (const auto &i : _users) {
      if (i.first != from) {
        i.second->receive(from, message);
      }
    }
  }
  void notice(const std::string &from, const std::string &name,
              const std::string &message) override {
    if (_users.count(name)) {
      _users.at(name)->receive(from, message);
    }
  }
};

int main() {
  auto chatRoom(std::make_unique<ConcreteChatRoom>());
  auto person1(std::make_unique<User>("user1", chatRoom.get()));
  auto person2(std::make_unique<User>("user2", chatRoom.get()));
  auto person3(std::make_unique<User>("user3", chatRoom.get()));
  auto person4(std::make_unique<User>("Thug Xi", chatRoom.get()));

  person4->say("fuck off!");

  person3->pm("Thug Xi", "hello!");
  return 0;
}
