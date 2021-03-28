#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _key_column {
	unsigned *value;
	unsigned size;
} key_column;

void execute_column_chipher(char *user_key, char *data, char mode); 
void create_key_column(key_column *key, char *user_key);
char *encryption_column(key_column *key, char *data);
char *decryption_column(key_column *key, char *chipher);
