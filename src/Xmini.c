/*
 * Xmini - A fast X server build on DRM
 */

#include "config.h"
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdint.h>
#include <errno.h>
#include <drm/drm.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <glib.h>

#include "Xmini.h"

int drm_fd;
int Xmini_sock;

static gboolean Xmini_giofunc_accpet_client_cb(GIOChannel *source,GIOCondition condition, gpointer data)
{
	g_print("new connect come\n");

}

static void on_sig_INT(int signum);
static void at_exit();

int main()
{
	struct sockaddr_un unix_socket_addr = { AF_UNIX};

	strcpy(unix_socket_addr.sun_path,XMINI_SOCKET);

	//open the socket server

	Xmini_sock = socket(AF_UNIX,SOCK_DGRAM|SOCK_CLOEXEC,0);

	{int opt = 1; setsockopt(Xmini_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));}

	if(bind(Xmini_sock,(struct sockaddr *)&unix_socket_addr,SUN_LEN(&unix_socket_addr)) < 0 )
		g_error("Err openning the socket %s :%s", XMINI_SOCKET,g_strerror(errno));

	atexit(at_exit);
	signal(SIGINT,on_sig_INT);

	listen(Xmini_sock,20);

	GIOChannel * gio_socket = g_io_channel_unix_new(Xmini_sock);

	g_io_add_watch(gio_socket,G_IO_IN,Xmini_giofunc_accpet_client_cb,0);

	//open the dri device
	drm_fd = open(DRM_DEVICE,O_RDWR|O_CLOEXEC);
	if(drm_fd < 0) g_error("Cann't open %s! : %s",DRM_DEVICE,g_strerror(errno));

	GMainLoop * gloop = g_main_loop_new(NULL,FALSE);
	g_main_loop_run(gloop);
}

static void at_exit()
{
	unlink(XMINI_SOCKET);
}

static void on_sig_INT(int signum)
{
	exit(0);
}
