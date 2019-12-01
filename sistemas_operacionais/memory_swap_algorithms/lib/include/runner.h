#ifndef RUNNER_H_
#define RUNNER_H_

#include "algorithm.h"
#include "execution_listener.h"
#include "thread_pool.h"

namespace swapping_algorithms {

class Runner {
   public:
    void Run(const std::vector<std::shared_ptr<Algorithm>> &algorithms, ExecutionListener &listener);

   private:
    ThreadPool pool_;
};

}

#endif  // RUNNER_H_
