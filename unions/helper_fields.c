#include <stdint.h>
#include <stdio.h>
typedef union packetheader
{ struct {
    uint16_t src_port;
    uint16_t dest_port;
    uint32_t seq_num;
}tcp_header;
uint8_t raw[8];
    
}packet_header_t;
int main(){
    printf("%zu\n", sizeof(packet_header_t));
}

