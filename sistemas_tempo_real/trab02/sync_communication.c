#include <stdio.h>

#include "sync_communication.h"

static int channels[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

int alt_wait()
{
    while (1) {
        for (int i = 0; i < 8; i++) {
            if (channels[i] != -1) {
                return i;
            }
        }	
    }
}

void receive_sync(int * msg, const int channel)
{
    while (channels[channel] == -1);

    *msg = (int)channels[channel];
    channels[channel] = -1;
}

void send_sync(const int * msg, const int channel)
{
    channels[channel] = (int)(*msg);
    while (channels[channel] != -1);
}

