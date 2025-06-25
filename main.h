#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btlib.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

  // callback for LE server
int lecallback(int node,int op,int cticn);
int send_key(int key);

unsigned char reportmap[47] = {0x05,0x01,0x09,0x06,0xA1,0x01,0x85,0x01,0x05,0x07,0x19,0xE0,0x29,0xE7,0x15,0x00,
                               0x25,0x01,0x75,0x01,0x95,0x08,0x81,0x02,0x95,0x01,0x75,0x08,0x81,0x01,0x95,0x06,
                               0x75,0x08,0x15,0x00,0x25,0x65,0x05,0x07,0x19,0x00,0x29,0x65,0x81,0x00,0xC0};

    // NOTE the size of report (8 in this case) must appear in keyboard.txt as follows:
    //   LECHAR=Report1         SIZE=8  Permit=92  UUID=2A4D  
unsigned char report[8] = {0,0,0,0,0,0,0,0};

unsigned char *name = "HID"; 
unsigned char appear[2] = {0xC1,0x03};  // 03C1 = keyboard icon appears on connecting device 
unsigned char pnpinfo[7] = {0x02,0x6B,0x1D,0x46,0x02,0x37,0x05};
unsigned char protocolmode[1] = {0x01};
unsigned char hidinfo[4] = {0x01,0x11,0x00,0x02};
unsigned char battery[1] = {100}; 

unsigned char uuid[2],randadd[6];

char *devices = { 
"DEVICE = pico   TYPE=Mesh  node=1  ADDRESS = LOCAL  \n\
  PRIMARY_SERVICE = 1800                               \n\
    LECHAR=Device Name   SIZE=4   Permit=02 UUID=2A00  \n\
    LECHAR=Appearance    SIZE=2   Permit=02 UUID=2A01  \n\
  PRIMARY_SERVICE = 180A                               \n\
    LECHAR= PnP ID           SIZE=7 Permit=02   UUID=2A50 \n\
  PRIMARY_SERVICE = 1812                                  \n\
    LECHAR=Protocol Mode   SIZE=1  Permit=06  UUID=2A4E  \n\
    LECHAR=HID Info        SIZE=4  Permit=02  UUID=2A4A  \n\
    LECHAR=HID Ctl Point   SIZE=8  Permit=04  UUID=2A4C   \n\
    LECHAR=Report Map      SIZE=47 Permit=02  UUID=2A4B  \n\
    LECHAR=Report1         SIZE=8  Permit=92  UUID=2A4D  \n\
"};
                                                                 
void mycode(void);


