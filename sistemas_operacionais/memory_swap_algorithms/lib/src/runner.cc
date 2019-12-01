#include "runner.h"

namespace swapping_algorithms {

void Runner::Run(const std::vector<std::shared_ptr<Algorithm>> &algorithms,
                 ExecutionListener &listener)
{
    auto cb = [&listener, algorithms] () {
        listener.OnExecutionStart();
        for (auto &algo : algorithms)
            algo->Run(listener);
        listener.OnExecutionFinish();
    };

    pool_.EnqueueTask(cb);
}

}
