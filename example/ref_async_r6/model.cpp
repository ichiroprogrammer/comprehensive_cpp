#include "do_heavy_algorithm.h"
#include "lib.h"
#include "model.h"

// @@@ sample begin 0:0

void Model::ConvertStoreAsync(std::string&& input)
{
    TwoPhaseTaskPtr task
        = MakeTwoPhaseTaskPtr([str = std::move(input)] { return do_heavy_algorithm(str); },
                              [this](auto&& str) {
                                  strings_.emplace_back(std::move(str));
                                  notify();
                              });

    Dispatcher::Inst().Invoke(std::move(task));
}

void Model::Attach(Observer& observer) { observers_.emplace_back(&observer); }
void Model::Detach(Observer& detach)
{
    observers_.remove_if([&detach](Observer* observer) { return &detach == observer; });
}

void Model::notify() const
{
    for (auto* observer : observers_) {
        observer->Update(*this);
    }
}
// @@@ sample end
