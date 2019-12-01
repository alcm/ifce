#include "include/execution_event_handler.h"

ExecutionEventHandler::ExecutionEventHandler()
    : IEventHandler{}
{
  qRegisterMetaType<swapping_algorithms::AlgorithmId>("swapping_algorithms::AlgorithmId");
  qRegisterMetaType<uint8_t>("uint8_t");
  qRegisterMetaType<uint32_t>("uint32_t");
}

void ExecutionEventHandler::OnExecutionStart()
{
   emit ExecutionStart();
}

void ExecutionEventHandler::OnExecutionFinish()
{
    emit ExecutionFinish();
}

void ExecutionEventHandler::OnAlgorithmStart(const swapping_algorithms::AlgorithmId id,
                                             const uint32_t q)
{
    emit AlgorithmStart(id, q);
}

void ExecutionEventHandler::OnAlgorithmFinish(const swapping_algorithms::AlgorithmId id,
                                              const uint32_t q,
                                              const uint32_t hit_count)
{
    emit AlgorithmFinish(id, q, hit_count);
}

void ExecutionEventHandler::OnProgress(const swapping_algorithms::AlgorithmId id, const uint32_t q,
                                       const uint8_t progress)
{
    emit Progress(id, q, progress);
}
