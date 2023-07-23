#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <string>
#include <set>

class Folder {
private:
    std::string name;
public:
    explicit Folder(const std::string &name) : name{name} {}

    void save(const std::string &msg);
    void remove(const std::string &msg);
};

class Message {
private:
    std::string contents;
    std::set<Folder*> folders;

public:
    explicit Message(const std::string &str = "") : contents{str} {}
    
    Message(const Message& other);
    Message& operator=(const Message& other);

    void save(Folder &folder) {
        folder.save(contents);
        folders.insert(&folder);
    }
    void remove(Folder &folder) {
        folder.remove(contents);
        folders.erase(&folder);
    }

    const std::string& get() const {
        return contents;
    }

    ~Message();
};

#endif
