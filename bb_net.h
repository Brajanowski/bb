#ifndef BB_NET_H_
#define BB_NET_H_

#include <stdio.h>
#include <stdint.h> // TODO: change that to <bb.h>

#ifdef _WIN32
#include <windows.h>
#include <winsock.h>
#endif

// protocol
#define BB_PROTOCOL_UDP  0x00
#define BB_PROTOCOL_TCP  0x01

struct bb_socket {
  uint32_t protocol;

  SOCKET __socket;
  sockaddr_in __addr;
};

bool bb_init_net() {
  WSADATA data;
  int res = WSAStartup(MAKEWORD(2, 2), &data);
  if (res != NO_ERROR)
    return false;

  return true;
}

bool bb_is_socket_error(bb_socket* s) {
  if (s->__socket == SOCKET_ERROR)
    return true;
  return false;
}

bool bb_init_socket(bb_socket* s, uint32_t protocol) {
  s->protocol = protocol;

  if (protocol == BB_PROTOCOL_TCP)
    s->__socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  else  
    s->__socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (s->__socket == INVALID_SOCKET) {
    WSACleanup();
    return false;
  }

  return true;
}

void bb_prepare_socket(bb_socket* s) {
  s->__socket = SOCKET_ERROR;
  memset(&s->__addr, 0, sizeof(sockaddr_in));
}

void bb_close_socket(bb_socket* s) {
  closesocket(s->__socket);
}

bool bb_bind_socket(bb_socket* s, const char* ip, uint16_t port) {
  memset(&s->__addr, 0, sizeof(s->__addr));

  s->__addr.sin_family = AF_INET;
  s->__addr.sin_addr.s_addr = inet_addr(ip);
  s->__addr.sin_port = htons(port);

  if (bind(s->__socket, (sockaddr*)&s->__addr, sizeof(sockaddr)) == SOCKET_ERROR) {
    bb_close_socket(s);
    return false;
  }

  return true;
}

bool bb_listen(bb_socket* s) {
  if (s->protocol == BB_PROTOCOL_TCP) {
    if (listen(s->__socket, 1) == SOCKET_ERROR)
      return false;
  }
  return true;
}

void bb_accept(bb_socket* s, bb_socket* accept_socket) {
  accept_socket->__socket = accept(s->__socket, NULL, NULL);
}

bool bb_connect(bb_socket* s, const char* ip, uint16_t port) {
  memset(&s->__addr, 0, sizeof(s->__addr));

  s->__addr.sin_family = AF_INET;
  s->__addr.sin_addr.s_addr = inet_addr(ip);
  s->__addr.sin_port = htons(port);
  
  if (connect(s->__socket, (sockaddr*)&s->__addr, sizeof(sockaddr)) == SOCKET_ERROR) {
    WSACleanup();
    return false;
  }

  return true;
}

int bb_send(bb_socket* s, const char* data, uint32_t sz) {
  return send(s->__socket, data, sz, 0);
}

int bb_recv(bb_socket* s, char* data, uint32_t sz) {
  return recv(s->__socket, data, sz, 0);
}

#endif

