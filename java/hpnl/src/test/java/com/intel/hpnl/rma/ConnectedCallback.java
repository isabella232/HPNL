package com.intel.hpnl.rma;

import java.util.List;

import com.intel.hpnl.core.Handler;
import com.intel.hpnl.core.Connection;

public class ConnectedCallback implements Handler {
  public ConnectedCallback(List<Connection> conList, boolean isServer) {
    this.conList = conList;
    this.isServer = isServer;
  }
  public void handle(Connection con, int rdmaBufferId, int blockBufferSize) {
    this.conList.add(con);
  }
  List<Connection> conList;
  boolean isServer;
}