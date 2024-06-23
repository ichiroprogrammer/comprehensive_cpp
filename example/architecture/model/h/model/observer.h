#pragma once

class Model;

class Observer {
public:
    virtual void update(const Model& model) = 0;
};
