#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SOURCE_DIR "Source_files/"
#define ENCRYPT_DIR "Encrypted_files/encrypted_"
#define DECRYPTED_DIR "Decrypted_files/decrypted_"

unsigned long int LFSR_register = 0xffffffff;

// polynomial
// x^23 + x^5 + 1
unsigned long int LFSR_get_bit()
{
	unsigned long int result_bit = (LFSR_register >> 31);
	char bit_22 = (LFSR_register >> 22) & 1;
	char bit_4 = (LFSR_register >> 4) & 1;
	char xor_22_4 = bit_22 ^ bit_4;

	LFSR_register = (LFSR_register << 1) | (xor_22_4);

	return result_bit;
}

void encrypt_file(FILE *source_file, FILE *dest_file, unsigned long int register_start_value)
{
	char buffer[1];
	LFSR_register = register_start_value;

	while (fread(buffer, sizeof(char), 1, source_file) == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			buffer[0] = (char)(buffer[0] ^ (LFSR_get_bit() << (8 - i)));
		}
		fwrite(buffer, sizeof(char), 1, dest_file);
	}
}

void main()
{
	srand(time(NULL));
	unsigned long int secret_key = rand();

	printf("Enter file name: Source_files/");

	// get file name
	char source_file_name[255];
	scanf("%s", &source_file_name);
	char file_path[270] = SOURCE_DIR;
	strcat(file_path, source_file_name);

	// make encrypted file name
	char ecrypted_file_path[275] = ENCRYPT_DIR;
	strcat(ecrypted_file_path, source_file_name);
	strcat(ecrypted_file_path, ".chpr");

	// make decrypted file name
	char decrypted_file_path[275] = DECRYPTED_DIR;
	strcat(decrypted_file_path, source_file_name);

	FILE *source_file;
	FILE *dest_file;

	// encryption
	source_file = fopen(file_path, "rb");
	dest_file = fopen(ecrypted_file_path, "wb");

	encrypt_file(source_file, dest_file, secret_key);
	printf("\nFile is encrypted! Location is ./%s\n", ecrypted_file_path);

	fclose(source_file);
	fclose(dest_file);

	// decryption
	source_file = fopen(ecrypted_file_path, "rb");
	dest_file = fopen(decrypted_file_path, "wb");

	encrypt_file(source_file, dest_file, secret_key);
	printf("\nFile is decrypted! Location is ./%s\n", decrypted_file_path);

	fclose(source_file);
	fclose(dest_file);
}