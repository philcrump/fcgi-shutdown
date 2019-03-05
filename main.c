#include "ffunc.h"

static const char sdnCommand[] = "shutdown -h now";

FFUNC postShutdown(ffunc_session_t * session)
{
	ffunc_write_out(session, "Status: 200 OK\r\n");
	ffunc_write_out(session, "Content-Type: text/plain\r\n\r\n");/* \r\n\r\n  means go to response message*/
	ffunc_write_out(session, "%s\n", "shutdown received.");
        /* Shut. It. Down */
        system(sdnCommand);
}

int ffunc_main(int argc, char *argv[], ffunc_config_t *ffunc_conf)
{
	(void) argc;
	(void) argv;
	
	ffunc_conf->sock_port = 2005;
	ffunc_conf->backlog = 4;
	ffunc_conf->max_thread = 2;

	ffunc_parse_function(ffunc_conf, "postShutdown");
	return 0;
}
