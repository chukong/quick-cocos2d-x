#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "pomelo.h"

const char *acc_gate_ip =  "127.0.0.1";
const int acc_gate_port = 4020;
const char *acc_conn_ip = "127.0.0.1";
const int acc_conn_port = 4010;
const char *gm_gate_ip =  "127.0.0.1";
const int gm_gate_port = 3020;
const char *gm_conn_ip =  "127.0.0.1";
const int gm_conn_port = 3010;


#define MAX_LINE_CHARS (1024)
#define MENUS_END -1
#define END_STR ("bye")
#define CHECK_STR ("check")
#define HELP_STR ("help")
#define CLEAR_STR ("clear")

enum msg_code {

	MSG_START = 0,
	MSG_CONN_ACC_GATE,
	MSG_CONN_ACC_CONN,
	MSG_CONN_GM_GATE,
	MSG_CONN_GM_CONN,

	MSG_ACC_CONN_REGISTERACCOUNT,

	MSG_GM_CONN_ENTER,
	MSG_MAXCODE
};


enum CONNECTING_STATUS {

	DISCONNECT,
	CONNECTING_ACC_GATE_SERVER,
	CONNECTING_ACC_CONN_SERVER,
	CONNNECTING_GAME_GATE_SERVER,
	CONNECTING_GAME_CONN_SERVER
};

enum WORKING_STATUS {
	WORKING,
	REST
};


struct msg_process {
	enum msg_code		m_cmd;
	char        *m_route;
	void			(*m_process)(char *);
};

struct menu_item {
	enum msg_code		m_cmd;
	char 	*info;
};

struct shared_communication {

	int  msg_working;  //This is used to know the message back
	int  connecting_status;
	pc_client_t *client;

};


#endif
