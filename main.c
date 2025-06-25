//modified from keyboard.c
//https://github.com/petzval/btferret              
#include "main.h"

void mycode(){
  
sleep_ms(1000);

gpio_init(12); gpio_set_dir(12,GPIO_IN); gpio_pull_up(12);
gpio_init(13); gpio_set_dir(13,GPIO_IN); gpio_pull_up(13);
gpio_init(14); gpio_set_dir(14,GPIO_IN); gpio_pull_up(14);
gpio_init(15); gpio_set_dir(15,GPIO_IN); gpio_pull_up(15);
  
if(init_blue(devices) == 0) return;

 // Write data to local characteristics
  uuid[0] = 0x2A;
  uuid[1] = 0x00;
  write_ctic(localnode(),find_ctic_index(localnode(),UUID_2,uuid),name,3); 

  uuid[0] = 0x2A;
  uuid[1] = 0x01;
  write_ctic(localnode(),find_ctic_index(localnode(),UUID_2,uuid),appear,0);

  uuid[0] = 0x2A;
  uuid[1] = 0x4E;
  write_ctic(localnode(),find_ctic_index(localnode(),UUID_2,uuid),protocolmode,0);

  uuid[0] = 0x2A;
  uuid[1] = 0x4A;
  write_ctic(localnode(),find_ctic_index(localnode(),UUID_2,uuid),hidinfo,0);

  uuid[0] = 0x2A;
  uuid[1] = 0x4B;
  write_ctic(localnode(),find_ctic_index(localnode(),UUID_2,uuid),reportmap,0);

  uuid[0] = 0x2A;
  uuid[1] = 0x4D;
  write_ctic(localnode(),find_ctic_index(localnode(),UUID_2,uuid),report,0);

  uuid[0] = 0x2A;
  uuid[1] = 0x50;
  write_ctic(localnode(),find_ctic_index(localnode(),UUID_2,uuid),pnpinfo,0);

set_le_wait(20000);
le_pair(localnode(),JUST_WORKS,0);

set_flags(FAST_TIMER,FLAG_ON);
while(1){le_server(lecallback,100);}}  //fast timer 100 millisecond

int lecallback(int node,int op,int cticn){
  unsigned char data_received[30];
  
if(op == LE_CONNECT) cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

else if(op == LE_TIMER){
  if(!gpio_get(12)) send_key('K');//pause youtube
  else if(!gpio_get(13)) send_key('B');
  else if(!gpio_get(14)) {//skip youtube add 4 tab followed by enter
    for(int i=0; i<4; i++) send_key(9); //tab
    send_key(10);}} //enter
    
else if(op == LE_DISCONNECT) cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,0);

  return(SERVER_CONTINUE);
  }

/********* send_key function *********/
int send_key(int key)
  {
  int n,hidcode;
  unsigned char buf[8];
  static int reportindex = -1;

  // convert btferret code (key) to HID code  
  hidcode = hid_key_code(key);
  if(hidcode == 0)
    return(0);

  if(reportindex < 0)
    {  // look up Report1 index
    buf[0] = 0x2A;
    buf[1] = 0x4D;
    reportindex = find_ctic_index(localnode(),UUID_2,buf);
    if(reportindex < 0)
      {
      printf("Failed to find Report characteristic\n");
      return(0);
      }
    }     
 
  for(n = 0 ; n < 8 ; ++n)
    buf[n] = 0;
        
  // send key press to Report1
  buf[0] = (hidcode >> 8) & 0xFF;  // modifier
  buf[2] = hidcode & 0xFF;         // key code
  write_ctic(localnode(),reportindex,buf,0);
  // send no key pressed - all zero
  buf[0] = 0;
  buf[2] = 0;
  write_ctic(localnode(),reportindex,buf,0); 
  return(1);
  }

