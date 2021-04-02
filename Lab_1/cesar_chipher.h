#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENG_ALPHABET_COUNT 26

void execute_cesar_chipher(unsigned user_key, char *data, char mode);
char *encrypt_cesar(unsigned key, char *data);
char *decrypt_cesar(unsigned key, char *chipher);