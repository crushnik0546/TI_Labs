#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEY_MEMCPY 25 * sizeof(char)

void execute_matrix_chipher(char user_key[5][5], char *data, char mode);
char *encrypt_matrix(char key[5][5], char *data);
char *decrypt_matrix(char key[5][5], char *chipher);