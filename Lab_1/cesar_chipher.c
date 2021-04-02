#include "cesar_chipher.h"

void execute_cesar_chipher(unsigned user_key, char *data, char mode)
{
	char *chipher, *decrypted_data;
	switch (mode)
	{
		//only encryption
	case 'e':
		chipher = encrypt_cesar(user_key, data);
		printf_s("\nChipher: %s\n", chipher);
		break;
		//only decryption
	case 'd':
		decrypted_data = decrypt_cesar(user_key, data);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
		// both (encryption and decryption)
	case 'b':
		chipher = encrypt_cesar(user_key, data);
		printf_s("\nChipher: %s", chipher);
		decrypted_data = decrypt_cesar(user_key, chipher);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
	}
}

char *encrypt_cesar(unsigned key, char *data)
{
	char *chipher = (char *)malloc(strlen(data) * sizeof(char));
	unsigned new_key = key % ENG_ALPHABET_COUNT;
	for (unsigned i = 0; i <= strlen(data); i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
		{
			chipher[i] = (data[i] - 'A' + new_key) % ENG_ALPHABET_COUNT + 'A';
		}
		else if (data[i] >= 'a' && data[i] <= 'z')
		{
			chipher[i] = (data[i] - 'a' + new_key) % ENG_ALPHABET_COUNT + 'a';
		}
		else
		{
			chipher[i] = data[i];
		}
	}
	return chipher;
}

char *decrypt_cesar(unsigned key, char *chipher)
{
	char *decrypted = (char *)malloc(strlen(chipher) * sizeof(char));
	unsigned new_key = key % ENG_ALPHABET_COUNT;
	for (unsigned i = 0; i <= strlen(chipher); i++)
	{
		if (chipher[i] >= 'A' && chipher[i] <= 'Z')
		{
			decrypted[i] = (chipher[i] + ENG_ALPHABET_COUNT - 'A' - new_key) % ENG_ALPHABET_COUNT + 'A';
		}
		else if (chipher[i] >= 'a' && chipher[i] <= 'z')
		{
			decrypted[i] = (chipher[i] + ENG_ALPHABET_COUNT - 'a' - new_key) % ENG_ALPHABET_COUNT + 'a';
		}
		else
		{
			decrypted[i] = chipher[i];
		}
	}
	return decrypted;
}