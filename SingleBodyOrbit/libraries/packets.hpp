#pragma once

#define PING_PACKET 0x01

#define THRUST_SET_REQUEST 0x02

struct packet_header {
  unsigned char magic = 0x29;
  unsigned char type;
};

struct thrust_set_body {
  unsigned char id;
  double thrust;
};