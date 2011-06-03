#include "syscall.h"

void main() {
	int pingPID, pongPID;
	
	Write("Ping-Pong test starting ...\n\n",50,ConsoleOutput);
		
	pingPID = Exec("./test/ping", 4);
	pongPID = Exec("./test/pong", 4);
	
	Join(pingPID);
	Join(pongPID);
	
	Write("\nPing-Pong test end.\n",50,ConsoleOutput);
}