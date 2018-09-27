#include "HPNL/Connection.h"
#include "HPNL/Server.h"
#include "HPNL/BufMgr.h"
#include "HPNL/Callback.h"
#include "HPNL/Common.h"
#include "PingPongBufMgr.h"

#define SIZE 4096

class ShutdownCallback : public Callback {
  public:
    ShutdownCallback() {}
    virtual ~ShutdownCallback() {}
    virtual void operator()(void *param_1, void *param_2) override {
      std::cout << "connection shutdown..." << std::endl;
    }
};

class RecvCallback : public Callback {
  public:
    RecvCallback(BufMgr *bufMgr_) : bufMgr(bufMgr_) {}
    virtual ~RecvCallback() {}
    virtual void operator()(void *param_1, void *param_2) override {
      int mid = *(int*)param_1;
      Chunk *ck = bufMgr->index(mid);
      Connection *con = (Connection*)ck->con;
      con->send((char*)ck->buffer, SIZE, SIZE, 0, 0);
    }
  private:
    BufMgr *bufMgr;
};

class SendCallback : public Callback {
  public:
    SendCallback(BufMgr *bufMgr_) : bufMgr(bufMgr_) {}
    virtual ~SendCallback() {}
    virtual void operator()(void *param_1, void *param_2) override {
      int mid = *(int*)param_1;
      Chunk *ck = bufMgr->index(mid);
      Connection *con = (Connection*)ck->con;
      con->take_back_chunk(ck);
    }
  private:
    BufMgr *bufMgr;
};

int main(int argc, char *argv[]) {
  BufMgr *recvBufMgr = new PingPongBufMgr();
  Chunk *ck;
  for (int i = 0; i < MEM_SIZE; i++) {
    ck = new Chunk();
    ck->rdma_buffer_id = recvBufMgr->get_id();
    ck->buffer = std::malloc(BUFFER_SIZE);
    ck->capacity = BUFFER_SIZE;
    recvBufMgr->add(ck->rdma_buffer_id, ck);
  }
  BufMgr *sendBufMgr = new PingPongBufMgr();
  for (int i = 0; i < MEM_SIZE; i++) {
    ck = new Chunk();
    ck->rdma_buffer_id = sendBufMgr->get_id();
    ck->buffer = std::malloc(BUFFER_SIZE);
    ck->capacity = BUFFER_SIZE;
    sendBufMgr->add(ck->rdma_buffer_id, ck);
  }

  Server *server = new Server("172.168.2.106", "123456");
  server->set_recv_buf_mgr(recvBufMgr);
  server->set_send_buf_mgr(sendBufMgr);

  RecvCallback *recvCallback = new RecvCallback(recvBufMgr);
  SendCallback *sendCallback = new SendCallback(sendBufMgr);
  ShutdownCallback *shutdownCallback = new ShutdownCallback();

  server->set_recv_callback(recvCallback);
  server->set_send_callback(sendCallback);
  server->set_connected_callback(NULL);
  server->set_shutdown_callback(shutdownCallback);

  server->run(1);

  server->wait();

  delete sendCallback;
  delete recvCallback;
  delete server;

  int recv_chunk_size = recvBufMgr->get_id();
  assert(recv_chunk_size == MEM_SIZE);
  for (int i = 0; i < recv_chunk_size; i++) {
    Chunk *ck = recvBufMgr->index(i);
    free(ck->buffer);
  }
  int send_chunk_size = sendBufMgr->get_id();
  for (int i = 0; i < send_chunk_size; i++) {
    Chunk *ck = sendBufMgr->index(i);
    free(ck->buffer);
  }

  delete recvBufMgr;
  delete sendBufMgr;

  sendCallback = NULL;
  recvCallback = NULL;
  server = NULL;
  recvBufMgr = NULL;
  sendBufMgr = NULL;

  return 0;
}