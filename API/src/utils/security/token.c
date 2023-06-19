#include <time.h>
#include <openssl/evp.h>
#include <openssl/blowfish.h>
#include "utils.h"
#include "config.h"

static void	decrypt(const u_int8_t *data);
static void	encrypt(const u_int8_t *data);
static void	exec(void action(unsigned int *, const BF_KEY *), const u_int8_t *data);

char	*digest_token(const u_int8_t *token)
{
	char		*id;
	time_t		_now;
	u_int8_t	*raw;
	char 		*timer;

	_now = now();
	timer = (asctime(localtime(&_now)));
	raw = (u_int8_t *)calloc((SIZE_ID) + (strlen(timer)) + 2, sizeof(u_int8_t));

	strhex_to_str(token, (char *)raw);
	decrypt((const u_int8_t *)(raw));

	id = strndup((const char *)raw, SIZE_ID);

	free(raw);

	return (id);
}

char	*get_token(const u_int8_t *id)
{
	time_t		_now;
	u_int8_t	*raw;
	char 		*timer;
	char		*token;

	_now = now();	
	timer = (asctime(localtime(&_now)));
	raw = (u_int8_t *)calloc((SIZE_ID) + (strlen(timer)) + 3, sizeof(u_int8_t));
	token = (char *)calloc((SIZE_ID * 2) + (strlen(timer) * 2) + 3, sizeof(char));

	strcat((char *)raw, (char *)id);
	strcat((char *)raw, " ");
	strcat((char *)raw, timer);

	encrypt(raw);
	str_to_strhex(raw, token);

	free(raw);

	return (token);
}

static void	exec(void action(unsigned int *, const BF_KEY *), const u_int8_t *data)
{
	BF_KEY		key;
	size_t		size;
	size_t		rounds;
	u_int8_t	*__key;

	__key = (u_int8_t *)get_instance_config()->secret.ptr;
	BF_set_key(&key, strlen((const char *)__key), __key);

	rounds = 0;
	size = strlen((const char *)data);
	while (rounds < (size / BF_BLOCK))
	{
		action((unsigned int *)(data + (BF_BLOCK * rounds)), &key);
		rounds++;
	}
}

static void	decrypt(const u_int8_t *data)
{
	exec(BF_decrypt, data);
}

static void	encrypt(const u_int8_t *data)
{
	exec(BF_encrypt, data);
}
