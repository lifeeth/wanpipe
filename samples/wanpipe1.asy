# ============================================================================
# WAN Router Configuration File.
# ============================================================================
# Protocol: Cisco HDLC  (CHDLC):  PRIMARY Port Configuration 
# ----------------------------------------------------------------------------


[devices]
wanpipe1 = WAN_CHDLC, Cisco HDLC


[interfaces]

wp1_chdlc = wanpipe1, ,API, PRI port connection (high speed 2Mbps) 


[wanpipe1]			

CARD_TYPE 	= S51X
S514CPU         = A		# S514 PCI Card CPU: A or B      (s514 only)
AUTO_PCISLOT    = NO		# Autodetect pci slot		 (s514 only)
PCISLOT 	= 5
PCIBUS		= 0
				
CommPort        = SEC		# PRI: High speed (2 MBps) primary port
				# SEC: Low speed (512 MBps) secondary port 
				#
				
Firmware	= /etc/wanpipe/firmware/cdual514.sfm	# adapter firmware
	
#
# ----- Physical interface configuration -----
Interface       = RS232           # physical interface type, RS232/V35
Clocking        = Internal      # Tx/Rx clock source, External/Internal
				#
				# * Jumpers must be set for internal or external
				#   clocking for: 
				#        s508 : RS232 SEC port 
				#        s514 : RS232 PRI and SEC port 
				#
				#
BaudRate        = 19200       # data transfer rate in bps, 1200..2048000
                                # Note: Max 256KBps for RS232 interface !!!
				#

Receive_only 	= NO            #   


# ----- Media-specific configuration ---------
MTU             = 1500          # maximum data transfer unit, bytes
TTL             = 0x7F          # Time To Live parameter for UDP packets
UDPPORT         = 9000          # UDP Port, used by cpipemon debugger



[wp1_chdlc]

# --------- Link Management parameters ---------
MULTICAST 	= NO            # Enable Multicasting
				#
IGNORE_DCD 	= NO		# Ignore DCD when determining active link status
				# (YES/NO) Default: NO (ONLY USED FOR TESTING)
				#
IGNORE_CTS 	= NO		# Ignore CTS when determining active link status
				# (YES/NO) Default: NO (ONLY USED FOR TESTING)
				#
IGNORE_KEEPALIVE= NO		# Ignore Keep alives when determining active 
				# link status (YES/NO) Default: NO
				# (ONLY USED FOR TESTING)
				#
HDLC_STREAMING = YES		# Options YES or NO
				#   YES: Turns OFF cisco hdlc protocol
				#        and uses raw frames, and no polling.
				#    NO: Turns ON the cisco hdlc protocol 
				#
KEEPALIVE_TX_TIMER   = 10000	# Interval between Keep Alive (0-60000 ms) 
				# Default 10000ms
				#
KEEPALIVE_RX_TIMER   = 11000	# Interval to expect Keepalives (10-60000 ms)
				# Default 10000ms
				#
KEEPALIVE_ERR_MARGIN = 5	# Consecutive keepalive timeouts before bringing  
                                # down the link. Default 3, range: 1 - 20
				#
SLARP_TIMER 	= 0		# Used for DYNAMIC/STATIC IP addressing 
				#
				#   0    : Static IP addressing.
                                #          IP addresses are obtained from 
				#          the interface file: 
				#          (usr/lib/wanrouter/interfaces/wp1_chdlc)
				#
				#   Non Zero : Dynamic IP addressing.
				#              IP addresses are requested from 
                                #              the remote station.
				#              Valid values are from 1-6000(ms)
       				#              Default: 5000
				#              Note: A dummy interface file 
				#                    is still required !!!

				
ASYNC_MODE 		= YES   # Enables Async mode
ASY_DATA_TRANSPARENT  	= NO
RTS_HS_FOR_RECEIVE 	= NO 
XON_XOFF_HS_FOR_RECEIVE = NO
XON_XOFF_HS_FOR_TRANSMIT = NO
DCD_HS_FOR_TRANSMIT 	= NO
CTS_HS_FOR_TRANSMIT 	= NO
TX_BITS_PER_CHAR 	= 8		
RX_BITS_PER_CHAR 	= 8
STOP_BITS 		= ONE 
PARITY 			= NONE 
BREAK_TIMER 		= 50
INTER_CHAR_TIMER 	= 123
RX_COMPLETE_LENGTH 	= 20
XON_CHAR 		= 0xFE
XOFF_CHAR 		= 0xFF



#--------------------- END OF WANPIPE CONFIGURATION ------------------------
