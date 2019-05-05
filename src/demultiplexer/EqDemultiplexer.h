#ifndef EQEVENTDEMULTIPLEXER_H
#define EQEVENTDEMULTIPLEXER_H

#include <sys/epoll.h>
#include <unistd.h>

#include <atomic>
#include <map>
#include <memory>
#include <unordered_map>
#include <string.h>

#include <rdma/fabric.h>
#include <rdma/fi_cm.h>

class EventHandler;
class FiStack;

#define MAX_POLL_CNT 8

class EqDemultiplexer {
  public:
    EqDemultiplexer(FiStack*);
    ~EqDemultiplexer();
    int init();
    int wait_event(std::map<fid*, std::shared_ptr<EventHandler>> eventMap);
    int register_event(fid*);
    int remove_event(fid*);
    void shutdown();
  private:
    FiStack *stack;
    fid_fabric *fabric;
    struct epoll_event event;
    int epfd;
};

#endif
