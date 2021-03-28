#include "column_chipher.h"

void execute_column_chipher(char *user_key, char *data, char mode)
{
	key_column key;
	create_key_column(&key, user_key);

	char *chipher, *decrypted_data;
	switch (mode)
	{
	//only encryption
	case 'e':
		chipher = encryption_column(&key, data);
		printf_s("\nChipher: %s\n", chipher);
		break;
	//only decryption
	case 'd':
		decrypted_data = decryption_column(&key, data);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
	// both (encryption and decryption)
	case 'b':
		chipher = encryption_column(&key, data);
		printf_s("\nChipher: %s", chipher);
		decrypted_data = decryption_column(&key, chipher);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
	}
}

void create_key_column(key_column *key, char *user_key)
{
	key->size = strlen(user_key);

	unsigned *tmp_key = malloc(key->size * sizeof(unsigned));

	if (tmp_key != NULL)
		memset(tmp_key, 0, strlen(user_key) * sizeof(unsigned));
	else
		return NULL;

	for (unsigned i = 0; i < strlen(user_key) - 1; i++)
	{
		for (unsigned j = i + 1; j < strlen(user_key); j++)
		{
			if (user_key[i] > user_key[j])
				tmp_key[i]++;
			else
				tmp_key[j]++;
		}
	}

	key->value = malloc(key->size * sizeof(unsigned));
	unsigned counter = 0;
	for (unsigned i = 0; i < key->size; i++)
	{
		for (unsigned j = 0; j < key->size; j++)
		{
			if (tmp_key[j] == counter)
			{
				key->value[i] = j;
				counter++;
				break;
			}
		}
	}

	free(tmp_key);
}

char *encryption_column(key_column *key, char *data)
{
	unsigned lines_count;
	unsigned modulo = strlen(data) % key->size;

	if (modulo == 0)
		lines_count = strlen(data) / key->size;
	else
		lines_count = strlen(data) / key->size + 1;

	char **matrix = (char **)malloc(lines_count * sizeof(char *));
	for (char i = 0; i < lines_count; i++)
	{
		matrix[i] = (char *)malloc(key->size * sizeof(char));
	}

	unsigned index = 0;
	for (unsigned i = 0; i < lines_count; i++)
	{
		for (unsigned j = 0; j < key->size; j++)
		{
			if (index != strlen(data))
				matrix[i][j] = data[index++];
		}
	}

	char *chipher = (char *)malloc(strlen(data) * sizeof(char));
	unsigned chiper_index = 0;
	index = 0;

	for (unsigned c = 0; c < key->size; c++)
	{
		unsigned j = key->value[index];
		for (unsigned i = 0; i < lines_count; i++)
		{
			if ((modulo != 0) && (j + 1 > modulo) && (i == lines_count - 1))
				break;
			else
				chipher[chiper_index++] = matrix[i][j];
		}
		index++;
	}
	chipher[chiper_index] = 0;
	free(matrix);

	return chipher;
}

char *decryption_column(key_column *key, char *chipher)
{
	unsigned lines_count;
	unsigned modulo = strlen(chipher) % key->size;

	if (modulo == 0)
		lines_count = strlen(chipher) / key->size;
	else
		lines_count = strlen(chipher) / key->size + 1;

	char **matrix = (char **)malloc(lines_count * sizeof(char *));
	for (char i = 0; i < lines_count; i++)
	{
		matrix[i] = (char *)malloc(key->size * sizeof(char));
	}

	unsigned index = 0, chipher_index = 0;
	for (unsigned c = 0; c < key->size; c++)
	{
		unsigned j = key->value[index];
		for (unsigned i = 0; i < lines_count; i++)
		{
			if ((modulo != 0) && (j + 1 > modulo) && (i == lines_count - 1))
				break;
			else
				matrix[i][j] = chipher[chipher_index++];
		}
		index++;
	}

	char *decrypted_data = (char *)malloc(strlen(chipher) * sizeof(char));
	index = 0;
	for (unsigned i = 0; i < lines_count; i++)
	{
		for (unsigned j = 0; j < key->size; j++)
		{
			if (index != strlen(chipher))
				decrypted_data[index++] = matrix[i][j];
		}
	}
	decrypted_data[index] = 0;
	free(matrix);
	return decrypted_data;
}