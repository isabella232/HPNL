#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <memory>

#include "HPNL/Callback.h"
#include "demultiplexer/EventType.h"

class Handle;

class EventHandler {
  public:
    virtual ~EventHandler() {}
    virtual int handle_event(EventType, void*) = 0;
    virtual std::shared_ptr<Handle> get_handle(void) const = 0;
    virtual void set_accept_request_callback(Callback *callback) = 0;
    virtual void set_connected_callback(Callback *callback) = 0;
    virtual void set_shutdown_callback(Callback *callback) = 0;
    virtual void set_recv_callback(Callback *callback) = 0;
    virtual void set_send_callback(Callback *callback) = 0;
    virtual void set_read_callback(Callback *callback) = 0;
};

#endif