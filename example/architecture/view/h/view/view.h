#pragma once
#include <iostream>
#include <memory>
#include <thread>

#include "model/model.h"

class View : public Model::Observer {
public:
    View(std::ostream& ostream);
    ~View();
    void ShowAsync(std::string&& msg);
    void Sync();
    void Update(Model const& model) override;

private:
    void          show_msg(std::string const& msg);
    std::ostream& ostream_;
    struct pimpl_t;
    std::unique_ptr<pimpl_t> pimpl_;
    void                     worker_function();
    std::thread              gen_worker();
};
