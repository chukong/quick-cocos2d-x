#include "debugger.h"

static void msg_conn_acc_gate(char *route);
static void msg_conn_acc_conn(char *route);
static void msg_conn_gm_gate(char *route);
static void msg_conn_gm_conn(char *route);
static void msg_acc_conn_registeraccount(char *route);
static void msg_gm_conn_enter(char *route);

static void show_Help();
static void on_close(pc_client_t *client, const char *event, void *data);
static void on_request_cb(pc_request_t *req, int status, json_t *resp);

struct shared_communication sc;

static char *conn_status[] = {

		"Disconnected",
		"Connected to acc gate server",
		"Connected to acc conn server",
		"Connected to game gate server",
		"Connected to game conn server"
};


//Fill this Table to add menu items
static struct menu_item menus[] = {

		{0, NULL}, //Make it from 1
		{MSG_CONN_ACC_GATE, "connect to acc gate"},
		{MSG_CONN_ACC_CONN, "connect to acc conn"},
		{MSG_CONN_GM_GATE,  "connect to game gate"},
		{MSG_CONN_GM_CONN,  "connect to game conn"},
		{MSG_ACC_CONN_REGISTERACCOUNT,  "register account"},

		{MSG_GM_CONN_ENTER,  "enter game conn"},
		{MENUS_END,  NULL}

};

//Fill this table to add mapping of msg , handler and function.
static struct msg_process msgtable[MSG_MAXCODE];
static struct msg_process msgtable2[] = {

	{MSG_CONN_ACC_GATE,					"",	 										msg_conn_acc_gate},
	{MSG_CONN_ACC_CONN,					"",  										msg_conn_acc_conn},
	{MSG_CONN_GM_GATE,					"",  										msg_conn_gm_gate},
	{MSG_CONN_GM_CONN,					"",  										msg_conn_gm_conn},

	{MSG_ACC_CONN_REGISTERACCOUNT,		"connector.entryHandler.registerAccount",   msg_acc_conn_registeraccount},

	{MSG_GM_CONN_ENTER,					"connector.entryHandler.enter",  			msg_gm_conn_enter},

};


int
main() {

	int i, cmd;
	char input[MAX_LINE_CHARS];
	pc_client_t *client = pc_client_new();
	pc_add_listener(client, PC_EVENT_DISCONNECT, on_close);

	//Init the msg table
	memset(msgtable, 0, sizeof(msgtable));
	for (i = 0 ; i < sizeof(msgtable2) / sizeof(struct msg_process); i++) {
		msgtable[msgtable2[i].m_cmd].m_cmd = msgtable2[i].m_cmd;
		msgtable[msgtable2[i].m_cmd].m_process = msgtable2[i].m_process;
		msgtable[msgtable2[i].m_cmd].m_route = msgtable2[i].m_route;
	}

	//Init the singleton communication module
	sc.client = NULL;
	sc.connecting_status = DISCONNECT;
	sc.msg_working = REST;

	system("clear");
	show_Help();

	while(1) {

		//Waiting for the message back.
		if(sc.msg_working == WORKING ){
			usleep(100);
			continue;
		}

        printf("Debugger>");
		scanf("%s", input);
		if (!strcasecmp(input, END_STR)) {
			break;
		}
		if(!strcasecmp(input, HELP_STR)) {
			show_Help();
			continue;
		}
		if(!strcasecmp(input, CHECK_STR)) {
			printf("Status: %s\n", conn_status[sc.connecting_status]);
			continue;
		}
		if(!strcasecmp(input, CLEAR_STR)) {
			system("clear");
			continue;
		}

		cmd = atoi(input);
		if (0 == cmd) {
			printf("Error input: No such command!\n");
			continue;
		}

		if(msgtable[cmd].m_process) {
			msgtable[cmd].m_process(msgtable[cmd].m_route);
		} else {
			printf("Error input: No such message!\n");
			continue;
		}
	}

	getchar();
	// release the client
	if(sc.connecting_status != DISCONNECT)
		pc_client_destroy(sc.client);
	return 0;
}

static void
msg_conn_acc_gate(char *route) {


	struct sockaddr_in address;

	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(acc_gate_port);
	address.sin_addr.s_addr = inet_addr(acc_gate_ip);

	//We must disconnect the old connection.
	if(sc.connecting_status != DISCONNECT) {
		pc_client_destroy(sc.client);
	}

	sc.client = pc_client_new();
	pc_add_listener(sc.client, PC_EVENT_DISCONNECT, on_close);
	if (pc_client_connect(sc.client, &address)) {
		printf("fail to connect acc gate server.\n");
		pc_client_destroy(sc.client);
		return;
	}

	sc.connecting_status = CONNECTING_ACC_GATE_SERVER;
	printf("Successfully Connected to Account gate server\n");

}

static void
msg_conn_acc_conn(char *route) {

	struct sockaddr_in address;

	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(acc_conn_port);
	address.sin_addr.s_addr = inet_addr(acc_conn_ip);

	//We must disconnect the old connection.
	if(sc.connecting_status != DISCONNECT) {
		pc_client_destroy(sc.client);
	}
	sc.client = pc_client_new();
	pc_add_listener(sc.client, PC_EVENT_DISCONNECT, on_close);
	if (pc_client_connect(sc.client, &address)) {
		printf("fail to connect acc connector server.\n");
		pc_client_destroy(sc.client);
		return;
	}

	sc.connecting_status = CONNECTING_ACC_CONN_SERVER;
	printf("Successfully Connected to Account connector server\n");

}

static void
msg_conn_gm_gate(char *route) {


	struct sockaddr_in address;

	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(gm_gate_port);
	address.sin_addr.s_addr = inet_addr(gm_gate_ip);

	//We must disconnect the old connection.
	if(sc.connecting_status != DISCONNECT) {
			pc_client_destroy(sc.client);
		}
	sc.client = pc_client_new();
	pc_add_listener(sc.client, PC_EVENT_DISCONNECT, on_close);

	if (pc_client_connect(sc.client, &address)) {
		printf("fail to connect gm gate server.\n");
		pc_client_destroy(sc.client);
		return;
	}

	sc.connecting_status = CONNNECTING_GAME_GATE_SERVER;
	printf("Successfully Connected to game gate server\n");

}

static void
msg_conn_gm_conn(char *route) {


	struct sockaddr_in address;

	memset(&address, 0, sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(gm_conn_port);
	address.sin_addr.s_addr = inet_addr(gm_conn_ip);

	//We must disconnect the old connection.
	if(sc.connecting_status != DISCONNECT) {
			pc_client_destroy(sc.client);
		}
	sc.client = pc_client_new();
	pc_add_listener(sc.client, PC_EVENT_DISCONNECT, on_close);

	if (pc_client_connect(sc.client, &address)) {
		printf("fail to connect gm conn server.\n");
		pc_client_destroy(sc.client);
		return;
	}

	sc.connecting_status = CONNECTING_GAME_CONN_SERVER;
	printf("Successfully Connected to game gate server\n");

}


static void
msg_acc_conn_registeraccount(char *route) {

	char param[1024], buf[64 + 1];;
	json_t *msg = json_object();
	json_t *str;
	pc_request_t *request;

	sc.msg_working = WORKING;

	memset(param, 0, sizeof(param));
	printf("[Please input the following parameters]\n");
	printf("usrname= ");
	scanf("%s", param);
	str = json_string(param);
	json_object_set(msg, "usrname", str);
	json_decref(str);

	printf("passwd=");
	scanf("%s", param);
#if 0
	gen_sha256(param, buf);
#endif
	str = json_string(buf);
	json_object_set(msg, "passwd", str);
	json_decref(str);

	printf("email=");
	scanf("%s", param);
	str = json_string(param);
	json_object_set(msg, "email", str);
	json_decref(str);

	request = pc_request_new();
	pc_request(sc.client, request, route, msg, on_request_cb);
}


static void
msg_gm_conn_enter(char *route) {

	char param[1024];
	json_t *msg = json_object();
	json_t *str;
	pc_request_t *request;

	sc.msg_working = WORKING;
	memset(param, 0, sizeof(param));
	printf("[Please input the following parameters]\n");
	printf("token= ");
	scanf("%s", param);
	str = json_string(param);

	json_object_set(msg, "token", str);

	json_decref(str);
	request = pc_request_new();
	pc_request(sc.client, request, route, msg, on_request_cb);

}

static void
on_request_cb(pc_request_t *req, int status, json_t *resp) {


	if (status == -1) {
		sc.msg_working = REST;
		printf("Fail to send request to server.\n");
	} else if (status == 0) {
		char *json_str = json_dumps(resp, 0);
		if (json_str != NULL) {
			printf("\n");
			printf("server response: %s\n", json_str);
			free(json_str);
		}
		sc.msg_working = REST;
	}

	// release relative resource with pc_request_t
	json_t *msg = req->msg;
	pc_client_t *client = req->client;
	json_decref(msg);
	pc_request_destroy(req);

}

static void
on_close(pc_client_t *client, const char *event, void *data) {
	printf("client closed: %d.\n", client->state);
}


static void
show_Help() {

	struct menu_item *menu_p = menus+1;
	int i = 1;
    printf("Server Debugger@storm\n");
	printf("-----------------------------------------\n");
	while(menu_p->m_cmd != MENUS_END) {
		printf("[%d]\t\t%s\n", i++, menu_p->info);
		menu_p++;
	}
	printf("\n");

	printf("[check]\t\tcheck connecting status\n");
	printf("[clear]\t\tclear the screen\n");
	printf("[help]\t\tshow the menu\n");
	printf("[bye]\t\texit the program\n");
	printf("-----------------------------------------\n");
	printf("Please type the command: \n");

}
