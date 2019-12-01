#include "nur.h"

namespace swapping_algorithms {

Nur::Nur(int bit_r, int q, const std::vector<MemOperation> &data)
    : Algorithm (AlgorithmId::NUR, q, "Nur", data), bit_r_(bit_r)
{

}

void Nur::Run(ExecutionListener &listener)
{
    //listener.OnExecutionStart();
    //listener.OnAlgorithmStart(id_, q_);
    //listener.OnAlgorithmFinish(id_, q_, 20);
    //listener.OnProgress(id_, q_, 33);
    //listener.OnExecutionFinish();
    // TODO
}

}
