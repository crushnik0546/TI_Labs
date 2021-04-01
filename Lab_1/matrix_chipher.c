#include "matrix_chipher.h"

void execute_matrix_chipher(char user_key[5][5], char *data, char mode)
{
	char *chipher, *decrypted_data;
	char tmp_key[5][5];
	memcpy(tmp_key, user_key, KEY_MEMCPY);

	switch (mode)
	{
		//only encryption
	case 'e':
		chipher = encrypt_matrix(user_key, data);
		printf_s("\nChipher: %s\n", chipher);
		break;
		//only decryption
	case 'd':
		decrypted_data = decrypt_matrix(user_key, data);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
		// both (encryption and decryption)
	case 'b':
		chipher = encrypt_matrix(user_key, data);
		printf_s("\nChipher: %s", chipher);
		decrypted_data = decrypt_matrix(tmp_key, chipher);
		printf_s("\nDecryption: %s\n", decrypted_data);
		break;
	}
}

char *encrypt_matrix(char key[5][5], char *data)
{
	unsigned blocks_count = strlen(data) / 25;
	if (strlen(data) % 25)
		blocks_count++;

	char tmp[25];
	for (unsigned i = 0; i < 25; i++)
		tmp[i] = ' ';
	strcat(data, tmp);

	char *chipher = (char *)malloc(blocks_count * 25 * sizeof(char));
	unsigned data_index = 0, chipher_index = 0;

	for (unsigned k = 0; k < blocks_count; k++)
	{
		char block[5][5];
		for (unsigned i = 0; i < 5; i++)
		{
			for (unsigned j = 0; j < 5; j++)
			{
				if (key[i][j])
					block[i][j] = data[data_index++];
				else
					block[i][j] = ' ';
			}
		}
		key[2][2] = 0;

		for (unsigned j = 0; j < 5; j++)
		{
			for (int i = 4; i >= 0; i--)
			{
				if (key[i][j])
					block[j][4 - i] = data[data_index++];
			}
		}

		for (int i = 4; i >= 0; i--)
		{
			for (int j = 4; j >= 0; j--)
			{
				if (key[i][j])
					block[4 - i][4 - j] = data[data_index++];
			}
		}

		for (int j = 4; j >= 0; j--)
		{
			for (unsigned i = 0; i < 5; i++)
			{
				if (key[i][j])
					block[4 - j][i] = data[data_index++];
			}
		}

		for (unsigned i = 0; i < 5; i++)
		{
			for (unsigned j = 0; j < 5; j++)
			{
				chipher[chipher_index++] = block[i][j];
			}
		}
	}
	chipher[chipher_index] = 0;
	return chipher;
}

char* decrypt_matrix(char key[5][5], char *chipher)
{
	unsigned blocks_count = strlen(chipher) / 25;
	char *decryption = (char *)malloc(blocks_count * 25 * sizeof(char));
	unsigned decryption_index = 0, chipher_index = 0;

	for (unsigned k = 0; k < blocks_count; k++)
	{
		char block[5][5];

		for (unsigned i = 0; i < 5; i++)
		{
			for (unsigned j = 0; j < 5; j++)
			{
				block[i][j] = chipher[chipher_index++];
				if (key[i][j])
					decryption[decryption_index++] = block[i][j];
			}
		}

		key[2][2] = 0;

		for (unsigned j = 0; j < 5; j++)
		{
			for (int i = 4; i >= 0; i--)
			{
				if (key[i][j])
					decryption[decryption_index++] = block[j][4 - i];
			}
		}

		for (int i = 4; i >= 0; i--)
		{
			for (int j = 4; j >= 0; j--)
			{
				if (key[i][j])
					decryption[decryption_index++] = block[4 - i][4 - j];
			}
		}

		for (int j = 4; j >= 0; j--)
		{
			for (unsigned i = 0; i < 5; i++)
			{
				if (key[i][j])
					decryption[decryption_index++] = block[4 - j][i];
			}
		}
	}
	decryption[decryption_index] = 0;
	return decryption;
}
