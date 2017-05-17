////////////////////////////////
// asi_zmq_publish.cpp //
////////////////////////////////


#include <zmq.hpp>
#include "asi_zmq.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <uchar.h>


zmq::context_t context (1);

zmq::socket_t get_ventilator() {
    zmq::socket_t publisher(context, ZMQ_PUSH);

    publisher.bind(server_addr);
    
    // Configure the message queue to drop all messages but the most recent
    //int conflate = 1;
    //publisher.setsockopt(ZMQ_CONFLATE, &conflate, sizeof(conflate));
    int linger = 0;
    publisher.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));

    return publisher;
}

int zmq_pub_frame(void *mat, asi_info *info_ptr) {
    // Size in bytes of the array
    size_t size = info_ptr->height * info_ptr->width + sizeof(asi_info);
    zmq::message_t message(size);
    static zmq::socket_t publisher = get_ventilator();

    // Send message to subscribers
    char *msg_ptr = (char *) message.data();

    // Copy camera config struct. Note that alignment matters here.
    // Previous testing with four-byte members in *info_ptr cause
    // publisher.send to fail.
    memcpy(msg_ptr, info_ptr, sizeof(asi_info));
    msg_ptr += sizeof(asi_info);

    // Copy array
    std::memcpy(msg_ptr, mat, size);
    publisher.send(message);
    return 0;
}

