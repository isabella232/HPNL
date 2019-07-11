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

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_intel_hpnl_core_RdmConnection */

#ifndef _Included_com_intel_hpnl_core_RdmConnection
#define _Included_com_intel_hpnl_core_RdmConnection
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_intel_hpnl_core_RdmConnection
 * Method:    init
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_intel_hpnl_core_RdmConnection_init
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_intel_hpnl_core_RdmConnection
 * Method:    get_local_name
 * Signature: (Ljava/nio/ByteBuffer;J)V
 */
JNIEXPORT void JNICALL Java_com_intel_hpnl_core_RdmConnection_get_1local_1name
  (JNIEnv *, jobject, jobject, jlong);

/*
 * Class:     com_intel_hpnl_core_RdmConnection
 * Method:    get_local_name_length
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_intel_hpnl_core_RdmConnection_get_1local_1name_1length
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_intel_hpnl_core_RdmConnection
 * Method:    send
 * Signature: (IIJ)I
 */
JNIEXPORT jint JNICALL Java_com_intel_hpnl_core_RdmConnection_send
  (JNIEnv *, jobject, jint, jint, jlong);

/*
 * Class:     com_intel_hpnl_core_RdmConnection
 * Method:    sendTo
 * Signature: (IILjava/nio/ByteBuffer;J)I
 */
JNIEXPORT jint JNICALL Java_com_intel_hpnl_core_RdmConnection_sendTo
  (JNIEnv *, jobject, jint, jint, jobject, jlong);

/*
 * Class:     com_intel_hpnl_core_RdmConnection
 * Method:    sendBuf
 * Signature: (Ljava/nio/ByteBuffer;IJ)I
 */
JNIEXPORT jint JNICALL Java_com_intel_hpnl_core_RdmConnection_sendBuf
  (JNIEnv *, jobject, jobject, jint, jlong);

/*
 * Class:     com_intel_hpnl_core_RdmConnection
 * Method:    sendBufTo
 * Signature: (Ljava/nio/ByteBuffer;ILjava/nio/ByteBuffer;J)I
 */
JNIEXPORT jint JNICALL Java_com_intel_hpnl_core_RdmConnection_sendBufTo
  (JNIEnv *, jobject, jobject, jint, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
