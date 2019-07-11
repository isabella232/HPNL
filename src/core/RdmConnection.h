// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef RDMCONNECTION_H
#define RDMCONNECTION_H

#include <rdma/fi_domain.h>
#include <rdma/fabric.h>
#include <rdma/fi_cm.h>
#include <rdma/fi_endpoint.h>
#include <string.h>

#include <vector>
#include <map>
#include <unordered_map>
#include <atomic>
#include <mutex>

#include "HPNL/Connection.h"
#include "HPNL/ChunkMgr.h"

class RdmConnection : public Connection {
  public:
    RdmConnection(const char*, const char*, fi_info*, fid_domain*, fid_cq*, ChunkMgr*, int, bool);
    ~RdmConnection() override;

    int init() override;
    int shutdown() override;

    int send(Chunk*) override;
    int send(int, int) override;
    int sendBuf(const char*, int) override;
    int sendTo(int, int, const char*) override;
    int sendBufTo(const char*, int, const char*) override;

    char* get_peer_name() override;
    char* get_local_name();
    int get_local_name_length();
    void activate_send_chunk(Chunk*) override;
    int activate_recv_chunk(Chunk*) override;
    std::vector<Chunk*> get_send_chunk();

    void set_recv_callback(Callback*) override;
    void set_send_callback(Callback*) override;
    Callback* get_recv_callback() override;
    Callback* get_send_callback() override;

    void decode_peer_name(void*, char*, int) override;
    char* decode_buf(void *buf) override;
    Chunk* encode(void *buf, int size, char*) override;

    void add_chunk_in_flight(Chunk *ck);
    void delete_chunk_in_flight(Chunk *ck);
    void get_chunks_in_flight(std::unordered_map<int, Chunk *> &);
    int chunks_size_in_flight();
  private:
    const char* ip;
    const char* port;

    fi_info *info;
    fid_domain *domain;
    fid_ep *ep;
    fid_av *av;
    fid_cq *conCq;

    ChunkMgr *buf_mgr;
    int buffer_num;
    bool is_server;
    
    char local_name[64];
    size_t local_name_len = 64;
    std::map<std::string, fi_addr_t> addr_map;

    std::vector<Chunk*> recv_chunks;
    std::vector<Chunk*> send_chunks;
    std::unordered_map<int, Chunk*> send_chunks_map;
    std::mutex in_flight_mtx;
    std::unordered_map<int, Chunk*> chunks_in_flight;

    Callback* recv_callback;
    Callback* send_callback;
};

#endif
