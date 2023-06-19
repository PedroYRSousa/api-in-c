#include <openssl/sha.h>
#include "utils.h"

static void SHA512_string(char *string, char outputBuffer[HASH_SIZE + 1]);

void get_hash(char *src, char hash[HASH_SIZE + 1])
{
	bzero(hash, HASH_SIZE + 1);
	SHA512_string(src, hash);
}

static void SHA512_string(char *string, char outputBuffer[HASH_SIZE + 1])
{
	int				index;
	SHA512_CTX		sha512;
	unsigned char	hash[SHA512_DIGEST_LENGTH];

	SHA512_Init(&sha512);
	SHA512_Update(&sha512, string, strlen(string));
	SHA512_Final(hash, &sha512);
	index = 0;
	while (index < SHA512_DIGEST_LENGTH)
	{
		sprintf(outputBuffer + (index * 2), "%02x", hash[index]);
		index++;
	}
}
