#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void execute_railfence_chipher(unsigned user_key, char *data, char mode);
char *encrypt_railfence(unsigned key, char *data);
char *decrypt_railfence(unsigned key, char *chipher);