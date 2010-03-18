/*
 * Xmini - A fast X server build on DRM
 */

#include "config.h"
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdint.h>
#include <errno.h>
#include <drm/drm.h>
#include <sys/socket.h>
#include <glib.h>

#include "Xmini.h"

int drm_fd;
int Xmini_sock;

int main()
{
	//open the socket server

	Xmini_sock = socket(AF_UNIX,SOCK_DGRAM|SOCK_CLOEXEC,0);

	if(Xmini_sock <0 )
		g_error("Err openning the socket %s :s", XMINI_SOCKET,g_strerror(errno));

	g_io_channel_unix_new(Xmini_sock);

	//open the dri device
	drm_fd = open(DRM_DEVICE,O_RDWR|O_CLOEXEC);
	if(drm_fd < 0)
		g_error("Cann't open %s! : %s",DRM_DEVICE,g_strerror(errno));

	GMainContext*  gcontext = g_main_context_new();

	GMainLoop * gloop = g_main_loop_new(gcontext,FALSE);
	g_main_loop_run(gloop);
}
