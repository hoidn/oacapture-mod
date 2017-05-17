#ifndef ASI_ZMQ_H
#define ASI_ZMQ_H

#include <stdint.h>
// Structure to hold array metadata.
typedef struct asi_info
{
    uint16_t height;
    uint16_t width;
} asi_info;


// Functions to push and get data from ZMQ pub and sub sockets,
// respectively.
int zmq_pub_frame(void *mat, asi_info *info_ptr);
uint8_t *zmq_sub_array();

// IPC socket address
const char* const server_addr = "tcp://127.0.0.1:5555";

#endif // ASI_ZMQ_H
