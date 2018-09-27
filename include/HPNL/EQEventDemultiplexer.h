#ifndef EQEVENTDEMULTIPLEXER_H
#define EQEVENTDEMULTIPLEXER_H

#include <rdma/fabric.h>
#include <rdma/fi_cm.h>

#include "HPNL/ConMgr.h"
#include "HPNL/EventDemultiplexer.h"
#include "HPNL/Handle.h"
#include "HPNL/Ptr.h"

#define MAX_POLL_CNT 8

class EQEventDemultiplexer : public EventDemultiplexer {
  public:
    EQEventDemultiplexer();
    virtual ~EQEventDemultiplexer() override;
    virtual int wait_event(std::map<HandlePtr, EventHandlerPtr> &) override;
    virtual int register_event(HandlePtr) override;
    virtual int remove_event(HandlePtr) override;
    void shutdown();
  private:
    int con_inflight = 0;
    std::atomic<bool> done{false};
};

#endif