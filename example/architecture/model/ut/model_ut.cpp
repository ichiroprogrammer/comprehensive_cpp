#include <iostream>

#include "gtest/gtest.h"

#include "model/model.h"
#include "model/observer.h"

class TestObserver : public Observer {
public:
    void update(const Model&) override { notified = true; }
    bool notified = false;
};

TEST(ModelTest, NotifyObservers)
{
    std::cout << "model" << std::endl;
    Model        model;
    TestObserver observer;

    model.addObserver(&observer);
    model.notify();

    ASSERT_TRUE(observer.notified);
}
