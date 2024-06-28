#include <iostream>

#include "model/model.h"
#include "model/observer.h"

void Model::addObserver(Observer* observer) { observers.push_back(observer); }

void Model::notify()
{
    std::cout << "model::notify" << std::endl;
    for (Observer* observer : observers) {
        observer->update(*this);
    }
}
