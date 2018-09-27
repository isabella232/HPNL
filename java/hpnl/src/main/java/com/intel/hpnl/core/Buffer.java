package com.intel.hpnl.core;

import java.nio.ByteBuffer;

public class Buffer {
  public Buffer(int rdmaBufferId, ByteBuffer byteBuffer) {
    this.rdmaBufferId = rdmaBufferId;
    this.byteBuffer = byteBuffer;
  }

  public int getRdmaBufferId() {
    return this.rdmaBufferId;
  }

  public ByteBuffer getByteBuffer() {
    return this.byteBuffer; 
  }

  public int getBlockBufferId() {
    return this.blockBufferId; 
  }

  public int getSeq() {
    return this.seq; 
  }

  public void put(ByteBuffer src, int blockBufferId, int seq) {
    assert byteBuffer.capacity() > src.remaining();
    byteBuffer.rewind();
    byteBuffer.limit(8+src.remaining());
    byteBuffer.putInt(blockBufferId);
    byteBuffer.putInt(seq);
    byteBuffer.put(src.slice());
    byteBuffer.flip();
  }

  public ByteBuffer get(int blockBufferSize) {
    byteBuffer.position(0); 
    byteBuffer.limit(blockBufferSize);
    this.blockBufferId = byteBuffer.getInt();
    this.seq = byteBuffer.getInt();
    return byteBuffer.slice();
  }

  private int rdmaBufferId;
  private int blockBufferId;
  private int seq;
  private ByteBuffer byteBuffer;
}