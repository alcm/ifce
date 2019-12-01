#ifndef TYPES_H_
#define TYPES_H_

#include <map>

namespace swapping_algorithms {

/**
 * @brief The AlgorithmId enum
 */
enum class AlgorithmId { FIFO, OPTIMAL, MRU, NUR, SECOND_CHANCE };

/**
 * @brief The MemOperation struct
 */
struct MemOperation {
    int page; //!<
    char op;  //!<
};

struct AlgorithmResult {
    std::string name;
    int hit_count;
};

/**
 * @brief ExecutionId
 */
typedef std::pair<AlgorithmId, int> ExecutionId;

}

#endif // TYPES_H_
