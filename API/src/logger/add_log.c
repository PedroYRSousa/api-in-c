#include "utils.h"
#include "logger.h"

void	add_log(t_connection *conn, t_request *req, time_t mseconds)
{
	t_llog		*aux;
	t_llog		*llog;
	t_logger	*logger;

	logger = get_instance_logger();
	llog = (t_llog *)calloc(1, sizeof(t_llog));
	llog->log.req = req;
	llog->log.conn = conn;
	llog->log.mseconds = mseconds;

	if (!logger->list)
		logger->list = llog;
	else
	{
		aux = logger->list;
		while (aux->next)
			aux = aux->next;
		aux->next = llog;
	}

	kill(getpid(), SIGUSR1);
}
