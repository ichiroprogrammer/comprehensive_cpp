#include "model/model.h"
#include "model/observer.h"
#include <gtest/gtest.h>

class TestObserver : public Observer {
public:
    void update(const Model&) override {
        notified = true;
    }
    bool notified = false;
};

TEST(ModelTest, NotifyObservers) {
    Model model;
    TestObserver observer;

    model.addObserver(&observer);
    model.notify();

    ASSERT_TRUE(observer.notified);
}
