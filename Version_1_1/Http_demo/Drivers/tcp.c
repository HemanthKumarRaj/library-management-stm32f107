#include <RTL.h>
#include <Net_Config.h>
#include "GLCD.h"

U8 soc_state;
U8 tcp_soc;
BOOL wait_ack;
void send_data (U8 *data_buf, U8 data_length) 
{
  
  static int bcount;
	//int i;
	U32 max;
  U8 *sendbuf;

  switch (soc_state) {
    case 0:
      //tcp_connect (tcp_soc, rem_IP, 2020, 0);
      bcount    = 0;
      wait_ack  = __FALSE;
      soc_state = 1;
			GLCD_clearLn (Line8);
			GLCD_displayStringLn(Line8, "Connecting...");
      return;
		case 2:
      
			if (wait_ack == __TRUE) 
				{
					return;
				}
			
			if (tcp_check_send (tcp_soc))
				{
      
					sendbuf = tcp_get_buf (data_length);
      
			
					memcpy (sendbuf, data_buf, data_length);
					tcp_send (tcp_soc, sendbuf, data_length);
			
					GLCD_clearLn (Line8);
					GLCD_displayStringLn(Line8, "Message Sent");
					wait_ack = __TRUE;
					return;
				}
			case 3:
      if (wait_ack == __TRUE) {
        return;
      }
      tcp_close (tcp_soc);
      soc_state = 4;
      return;
  }
}
U16 tcp_callback (U8 soc, U8 event, U8 *ptr, U16 par) 
{
  /* This function is called on TCP event */
	U8 data_get,i;
	unsigned char databuff[8];
	
  switch (event) {
     
    case TCP_EVT_CONNECT:
      /* Socket is now connected and ready to send data. */
      soc_state = 2;
      break;
    case TCP_EVT_ACK:
      /* Our sent data has been acknowledged by remote peer */
      wait_ack = __FALSE;
      break;
		case TCP_EVT_DATA:
      /* TCP data frame has been received, 'ptr' points to data */
      /* Data length is 'par' bytes */
      data_get = *ptr;
			
			for ( i=0; i <=8; i++)
				{
					databuff[i] = data_get++;
				}
			GLCD_clearLn (Line9);
			GLCD_displayStringLn(Line9, (unsigned char *) databuff);
		
      break;
       
		
  }
  return (0);
}