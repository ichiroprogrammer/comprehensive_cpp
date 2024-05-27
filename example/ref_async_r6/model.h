#pragma once

#include <list>
#include <memory>
#include <string>
#include <vector>

class Model;

// @@@ sample begin 0:0

class Observer {
public:
    Observer() = default;
    void Update(Model const& model) { update(model); }
    virtual ~Observer() = default;

private:
    virtual void update(Model const& model) = 0;
};

class Model {
public:
    Model()  = default;
    ~Model() = default;
    void                            ConvertStoreAsync(std::string&& input);
    void                            Attach(Observer& observer);
    void                            Detach(Observer& observer);
    std::vector<std::string> const& GetStrings() const noexcept { return strings_; }

private:
    void notify() const;

    std::vector<std::string> strings_{};
    std::list<Observer*>     observers_{};
};
// @@@ sample end
