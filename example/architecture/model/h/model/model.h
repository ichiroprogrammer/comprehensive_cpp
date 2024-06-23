#pragma once
#include <vector>

class Observer;

class Model {
public:
    void addObserver(Observer* observer);
    void notify();

private:
    std::vector<Observer*> observers;
};
