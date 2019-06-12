#ifndef SYNC_COMMUNICATION_H_
#define SYNC_COMMUNICATION_H_

void receive_sync(int * msg, const int channel);
void send_sync(const int * msg, const int channel);
int alt_wait();
 
#endif

