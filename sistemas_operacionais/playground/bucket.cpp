#include "bucket.h"

Bucket::Bucket(const uint8_t bucket_capacity) : capacity_(bucket_capacity)
{

}

void Bucket::Push()
{
    // TODO: increase full semaphore
    // TODO: emit signal to refresh gui.
}

void Bucket::Pull()
{
    // TODO: decrease empty semaphore
    // TODO: emit signal to refresh gui.
}
