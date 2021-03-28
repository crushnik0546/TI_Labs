#include "railfence_chipher.h"

void delete_first_symbol(char *src);

void execute_railfence_chipher(unsigned user_key, char *data, char mode)
{
	char *chipher, *decrypted_data;
	switch (mode)
	{
		//only encryption
	case 'e':
		chipher = encrypt_railfence(user_key, data);
		printf_s("\nChipher: %s\n", chipher);
		break;
	//only decryption
	case 'd':
		decrypted_data = decrypt_railfence(user_key, data);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
	// both (encryption and decryption)
	case 'b':
		chipher = encrypt_railfence(user_key, data);
		printf_s("\nChipher: %s", chipher);
		decrypted_data = decrypt_railfence(user_key, chipher);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
	}
}

void delete_first_symbol(char *src)
{
	for (unsigned i = 0; i < strlen(src) - 1; i++)
	{
		src[i] = src[i + 1];
	}
}

char *encrypt_railfence(unsigned key, char *data)
{
	char *chipher = (char *)malloc(strlen(data) * sizeof(char));
	unsigned period = 2 * (key - 1);
	unsigned chipher_index = 0;

	for (unsigned i = 0; i < key; i++)
	{
		unsigned index = 0;
		while (index < strlen(data))
		{
			if ((key - 1 - abs(key - 1 - (index % period))) == i)
			{
				chipher[chipher_index++] = data[index];
			}
			index++;
		}
	}
	chipher[chipher_index] = 0;

	return chipher;
}

char *decrypt_railfence(unsigned key, char *chipher)
{
	char **str_matrix = (char **)malloc(key * sizeof(char *));
	for (char i = 0; i < key; i++)
	{
		str_matrix[i] = (char *)malloc(strlen(chipher) * sizeof(char));
	}

	unsigned period = 2 * (key - 1), index = 0;
	for (unsigned i = 0; i < key; i++)
	{
		unsigned char_counter = 0;
		for (unsigned j = 0; j < strlen(chipher); j++)
		{
			if ((key - 1 - abs(key - 1 - (j % period))) == i)
			{
				char_counter++;
			}
		}

		for (unsigned j = 0; j < char_counter; j++)
		{
			str_matrix[i][j] = chipher[index++];
		}
	}

	char *decrypted_data = (char *)malloc(strlen(chipher) * sizeof(char));
	unsigned down = 0, i = 0;
	index = 0;
	while (index < strlen(chipher))
	{
		decrypted_data[index] = str_matrix[i][0];
		delete_first_symbol(str_matrix[i]);
		index++;
		if ((i + 1) == key)
			down = 0;
		if ((i + 1) == 1)
			down = 1;
		if (down)
			i++;
		else
			i--;
	}
	decrypted_data[index] = 0;
	//free(str_matrix);
	return decrypted_data;
}