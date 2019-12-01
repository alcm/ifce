#ifndef EXECUTE_ALGORITHMS_CMD_H_
#define EXECUTE_ALGORITHMS_CMD_H_

#include <memory>
#include <vector>

#include "include/command.h"
#include "lib/include/algorithm.h"

class ExecuteAlgorithmsCmd : public ICommand {
public:
    /**
     * @brief Constructor.
     * @param sched Diagnostics schedule.
     */
    explicit ExecuteAlgorithmsCmd(const std::vector<std::shared_ptr<swapping_algorithms::Algorithm>> &algorithms)
      : ICommand{}, algorithms_{algorithms} {

    }

    std::vector<std::shared_ptr<swapping_algorithms::Algorithm>> algorithms() const
    {
        return algorithms_;
    }

private:
    std::vector<std::shared_ptr<swapping_algorithms::Algorithm>> algorithms_;
};

#endif  // EXECUTE_ALGORITHMS_CMD_H_

