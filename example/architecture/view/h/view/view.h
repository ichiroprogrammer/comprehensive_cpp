#pragma once
#include <iostream>
#include <memory>
#include <thread>

#include "model/observer.h"

class View : public Observer {
public:
    View(std::ostream& ostream);
    ~View();
    void ShowAsync(std::string&& msg);
    void Sync();
    void update(Model const& model);

private:
    void          show_msg(std::string const& msg);
    std::ostream& ostream_;
    struct pimpl_t;
    std::unique_ptr<pimpl_t> pimpl_;
    void                     worker_function();
    std::thread              gen_worker();
};
