#include "main.h"

int main() {
	while (1)
	{
		printf_s("\nTo EXIT enter 0\n");
		printf_s("1. Column Chipher\n");
		printf_s("2. Rail fence Chiper\n");
		printf_s("3. Matrix Chipher\n");
		printf_s("4. Cesar Chiper\n");
		// add chiphers

		unsigned command = 1, unsigned_key;
		char matrix_key[5][5];

		scanf_s("%d", &command);
		char mode;
		char key[MAX_INPUT_SIZE], str[MAX_INPUT_SIZE];

		switch (command)
		{
		case EXIT_CODE:
			return 0;
		case COLUMN_CHIPHER:
			printf_s("\nSelect mode ('e' - encrypt data; 'd' - decrypt data; 'b' - encrypt and decrypt data): ");
			getchar();
			scanf_s("%c", &mode, 1);
			getchar();
			printf_s("Key: ");
			gets_s(key, MAX_INPUT_SIZE);
			printf_s("Data: ");
			gets_s(str, MAX_INPUT_SIZE);
			execute_column_chipher(key, str, mode);
			break;
		case RAILFANCE_CHIPHER:
			printf_s("\nSelect mode ('e' - encrypt data; 'd' - decrypt data; 'b' - encrypt and decrypt data): ");
			getchar();
			scanf_s("%c", &mode, 1);
			getchar();
			printf_s("Key: ");
			scanf_s("%d", &unsigned_key);
			getchar();
			printf_s("Data: ");
			gets_s(str, MAX_INPUT_SIZE);
			if (unsigned_key != 1 && unsigned_key != 0)
				execute_railfence_chipher(unsigned_key, str, mode);
			break;
		case MATRIX_CHIPHER:
			printf_s("\nSelect mode ('e' - encrypt data; 'd' - decrypt data; 'b' - encrypt and decrypt data): ");
			getchar();
			scanf_s("%c", &mode, 1);
			getchar();
			printf_s("Key: ");
			for (unsigned i = 0; i < 5; i++)
			{
				for (unsigned j = 0; j < 5; j++)
				{		
					scanf("%hhd", &matrix_key[i][j]);	
				}
			}
			getchar();
			printf_s("Data: ");
			gets_s(str, MAX_INPUT_SIZE);
			execute_matrix_chipher(matrix_key, str, mode);
			break;
		case CESAR_CHIPHER:
			printf_s("\nSelect mode ('e' - encrypt data; 'd' - decrypt data; 'b' - encrypt and decrypt data): ");
			getchar();
			scanf_s("%c", &mode, 1);
			getchar();
			printf_s("Key: ");
			scanf_s("%d", &unsigned_key);
			getchar();
			printf_s("Data: ");
			gets_s(str, MAX_INPUT_SIZE);
			if (unsigned_key >= 0)
				execute_cesar_chipher(unsigned_key, str, mode);
			break;
		}
	}
}