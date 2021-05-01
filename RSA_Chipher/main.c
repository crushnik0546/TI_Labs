#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define MAX_DATA_INPUT 2048
#define TRUE 1
#define FALSE 0
#define MIN_RAND 10
#define MAX_RAND 50

typedef long long big_int;

typedef struct _key
{
	big_int dif;
	big_int same;
} key;

 void euclid_ext(big_int a, big_int b, big_int *x, big_int *y, big_int *d)
{
	big_int q, r, x1, x2, y1, y2;

	if (b == 0)
	{
		*d = a;
		*x = 1;
		*y = 0;
		return;
	}

	x2 = 1;
	x1 = 0;
	y2 = 0;
	y1 = 1;

	while (b > 0)
	{
		q = a / b;
		r = a - q * b;
		*x = x2 - q * x1;
		*y = y2 - q * y1;
		a = b;
		b = r;
		x2 = x1;
		x1 = *x;
		y2 = y1;
		y1 = *y;
	}

	*d = a;
	*x = x2;
	*y = y2;
}

big_int reverse(big_int a, big_int n)
{
	 big_int x, y, d;
	 euclid_ext(a, n, &x, &y, &d);

	 if (d == 1)
		 return x;

	 return 0;
}

void generate_keys(key *public_key, key *private_key)
{
	char is_simple = FALSE;
	big_int p, q;
	srand(time(NULL));

	while (!is_simple)
	{
		is_simple = TRUE;
		p = rand() % (MAX_RAND - MIN_RAND) + MIN_RAND;
		for (big_int i = 2; i < (big_int)sqrt(p); i++)
		{
			if (p % i == 0)
			{
				is_simple = FALSE;
				break;
			}
		}
	}

	is_simple = FALSE;

	while (!is_simple)
	{
		is_simple = TRUE;
		q = rand() % (MAX_RAND - MIN_RAND) + MIN_RAND;
		for (big_int i = 2; i < (big_int)sqrt(q); i++)
		{
			if (q % i == 0)
			{
				is_simple = FALSE;
				break;
			}
		}
	}

	big_int mult = p * q;
	big_int euler = (p - 1) * (q - 1);
	//printf_s("\nfi = %lld\n", euler);
	big_int ferma_numbers[] = { 17, 257, 65537 };
	char index = rand() % 3;
	big_int e = ferma_numbers[index];

	public_key->dif = e;
	public_key->same = mult;
	 
	big_int d = reverse(e, euler);
	if (d < 0)
		d = euler + d;
	if (d == 0)
		generate_keys(public_key, private_key);
	else
	{
		private_key->dif = d;
		private_key->same = mult;
	}
	
}

big_int power_mod(big_int code, big_int e, big_int n)
{
	unsigned long long a1 = code, z1 = e, x = 1;
	while (z1 != 0)
	{
		while (z1 % 2 == 0)
		{
			z1 = z1 / 2;
			a1 = (a1 * a1) % n;
		}
		z1 = z1 - 1;
		x = (x * a1) % n;
	}
	return (big_int)x;
}

int main()
{
	char text[MAX_DATA_INPUT], data_txt[MAX_DATA_INPUT];
	gets_s(text, MAX_DATA_INPUT);
	key public, private;
	strcpy_s(data_txt, MAX_DATA_INPUT, text);
	generate_keys(&public, &private);
	printf_s("\nPublic key: e = %lld, r = %lld", public.dif, public.same);
	printf_s("\nPrivate key: d = %lld, r = %lld\n", private.dif, private.same);

	big_int chipher[MAX_DATA_INPUT];

	for (int i = 0; i < strlen(text); i++)
	{
		chipher[i] = power_mod((big_int)text[i], public.dif, public.same);
		printf_s("%lld ", chipher[i]);
	}
	printf_s("\n\n");
	char data[MAX_DATA_INPUT];

	for (int i = 0; i < strlen(text); i++)
	{
		data[i] = power_mod(chipher[i], private.dif, private.same);
		printf_s("%c", data[i]);
	}

	return 0;
}