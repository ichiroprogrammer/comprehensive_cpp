#include "do_heavy_algorithm.h"
#include "model.h"

// @@@ sample begin 0:0

void Model::ConvertStoreAsync(std::string const& input)
{
    thd_.join();

    thd_ = std::thread{[this, input = input] {
        strings_.emplace_back(do_heavy_algorithm(input));
        notify();
    }};
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
