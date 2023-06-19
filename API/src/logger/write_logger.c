#include "utils.h"
#include "logger.h"
#include "config.h"

static void put_date(int fd);
static void put_ip(t_connection *conn, int fd);
static void	put_method(int fd, t_request *req);
static void	put_response(int fd, t_connection *conn);
static void	put_user_agent(int fd, t_connection *conn);
static void	put_time_to_response(int fd, time_t mseconds);
static void	put_content_length(int fd, t_connection *conn);

void	write_logger(int sig)
{
	t_log		log;
	t_llog		*llog;
	t_logger	*logger;

	if (sig == SIGUSR1)
	{
		logger = get_instance_logger();
		logger->fd = open(get_instance_config()->log_path.ptr, O_CREAT | O_APPEND | O_WRONLY, 0444);
		if (logger->list)
		{
			llog = logger->list;
			log = llog->log;

			put_ip(log.conn, logger->fd);
			put_date(logger->fd);
			put_method(logger->fd, log.req);
			put_response(logger->fd, log.conn);
			put_content_length(logger->fd, log.conn);
			put_user_agent(logger->fd, log.conn);
			put_time_to_response(logger->fd, log.mseconds);
			dprintf(logger->fd, "\n");

			logger->list = logger->list->next;
			free(llog);
		}
		close(logger->fd);
	}
}

static void put_ip(t_connection *conn, int fd)
{
	char	buffer[30];

	bzero(buffer, 30);
	mg_straddr(&(conn->peer), buffer, 30);
	dprintf(fd, "%s ", buffer);
}

static void put_date(int fd)
{
	struct tm	*date;
	time_t 		seconds;

	time(&seconds);
	date = localtime(&seconds);
	dprintf(fd, "[%02d/%02d/%d:%02d:%02d:%02d] ", date->tm_mday, date->tm_mon, (date->tm_year + 1900), date->tm_hour, date->tm_min, date->tm_sec);
}

static void	put_method(int fd, t_request *req)
{
	struct mg_str	uri;
	struct mg_str	proto;
	struct mg_str	method;

	uri = req->uri;
	proto = req->proto;
	method = req->method;

	dprintf(fd, "\"%.*s %.*s %.*s\" ", 
	(int)method.len, method.ptr,
	(int)uri.len, uri.ptr,
	(int)proto.len, proto.ptr);
}

static void	put_response(int fd, t_connection *conn)
{
	unsigned char	*aux;
	unsigned char	*res;

	res = conn->send.buf;
	res = (unsigned char *)(strchr((char *)res, ' ') + 1);
	if (res)
	{
		aux = (unsigned char *)(strchr((char *)res, ' '));
		dprintf(fd, "%.*s ", (int)(aux - res), res); 
	}
	else
		dprintf(fd, " "); 
}

static void	put_content_length(int fd, t_connection *conn)
{
	unsigned char	*aux;
	unsigned char	*user_agent;

	user_agent = conn->send.buf;
	user_agent = (unsigned char *)(strstr((char *)user_agent, "Content-Length:"));
	if (user_agent)
	{
		user_agent = (unsigned char *)(strchr((char *)user_agent, ' ') + 1);
		aux = (unsigned char *)(strchr((char *)user_agent, '\n'));
		dprintf(fd, "%.*s ", (int)(aux - user_agent - 1), user_agent); 
	}
	else
		dprintf(fd, " "); 
}

static void	put_user_agent(int fd, t_connection *conn)
{
	unsigned char	*aux;
	unsigned char	*user_agent;

	user_agent = conn->recv.buf;
	user_agent = (unsigned char *)(strstr((char *)user_agent, "User-Agent:"));
	if (user_agent)
	{
		user_agent = (unsigned char *)(strchr((char *)user_agent, ' ') + 1);
		aux = (unsigned char *)(strchr((char *)user_agent, '\n'));
		dprintf(fd, "%.*s ", (int)(aux - user_agent - 1), user_agent); 
	}
	else
		dprintf(fd, " "); 
}

static void	put_time_to_response(int fd, time_t mseconds)
{
	dprintf(fd, "- - %ld ", mseconds);
}
