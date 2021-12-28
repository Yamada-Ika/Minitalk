#include "test.h"

#define TEST(args...)							\
{												\
	int res_ft_printf = ft_printf(args);		\
	int res_printf = printf(args);				\
	fflush(stdout);								\
	ft_check_value(res_ft_printf, res_printf);	\
}

int main(void) {
	// non-conversion
	#ifdef N
	TEST("Hello, world\n");
	TEST("");
	#endif

	// c
	#ifdef C
	TEST("%c\n", 'a');
	TEST("%c%c\n", 'a', 'b');
	TEST("%c %c\n", 'a', 'b');
	#endif

	// s
	#ifdef S
	TEST("%s\n", "hello");
	TEST("%s%s\n", "hello", "world");
	TEST("%s %s\n", "hello", "world");
	#endif

	// p
	#ifdef P
	int ptr_1;
	char ptr_2;
	long ptr_3;
	double ptr_4;
	TEST("%p\n", &ptr_1);
	TEST("%p%p\n", &ptr_2, &ptr_2);
	TEST("%p %p\n", &ptr_3, &ptr_4);
	#endif

	// d
	#ifdef D
	TEST("%d\n", 0);
	TEST("%d%d\n", -1, 100);
	TEST("%d %d\n", -100, 100);
	TEST("%d %d\n", INT_MIN, INT_MAX);
	TEST("%d %d\n", LONG_MIN, LONG_MAX);
	TEST("%d %d\n", LLONG_MIN, LLONG_MAX);
	TEST("%d\n", ULONG_MAX);
	#endif

	// i
	#ifdef I
	TEST("%i\n", 0);
	TEST("%i%i\n", -1, 100);
	TEST("%i %i\n", -100, 100);
	TEST("%i %i\n", INT_MIN, INT_MAX);
	TEST("%i %i\n", LONG_MIN, LONG_MAX);
	TEST("%i %i\n", LLONG_MIN, LLONG_MAX);
	TEST("%i\n", ULONG_MAX);
	#endif

	// u
	#ifdef U
	TEST("%u\n", 0);
	TEST("%u%u\n", 0, 100);
	TEST("%u %u\n", UINT_MAX, 123);
	TEST("%u %u %u\n", -1, INT_MIN, LLONG_MAX);
	#endif

	// x
	#ifdef LX
	TEST("%x\n", 0);
	TEST("%x%x\n", 10, 11);
	TEST("%x %x\n", -1, INT_MAX);
	TEST("%x %x %x\n", INT_MIN, LLONG_MIN, 0);
	#endif

	// X
	#ifdef UX
	TEST("%X\n", 0);
	TEST("%X%X\n", 100, -1);
	TEST("%X %X\n", INT_MIN, INT_MAX);
	TEST("%X %X %X\n", LLONG_MIN, UINT_MAX, LLONG_MAX);
	#endif

	// %
	#ifdef PERCENT
	TEST("%%\n");
	TEST("%%%%\n");
	TEST("%% %%\n");
	TEST("%% %% %%\n");
	#endif

	// mix
	#ifdef MIX
	int num;
	TEST("%c %s %p %d %i %u %x %X %%\n", 'J', "string", &num, LONG_MIN, LONG_MAX, -1, -1, INT_MAX);
	#endif

	// Over INT_MAX length
	#ifdef BIG_STR
	long long size = 1LL * INT_MAX + 10LL;
	char *str = (char *)malloc(size * sizeof(char));
	memset(str, 'a', size - 1LL);
	str[size - 1] = '\0';
	fflush(stdout);
	printf("%d\n", printf("%s", str));
	printf("%d\n", ft_printf("%s", str));
	#endif

	// Over INT_MAX length
	#ifdef BIG_MIX
	long long size = 1LL * INT_MAX + 0LL;
	char *str = (char *)malloc(size * sizeof(char));
	memset(str, '_', size - 1LL);
	str[size - 1LL] = '\0';
	printf("%d\n", printf("ab\n%s", str));
	printf("%d\n", ft_printf("ab\n%s", str));
	#endif

	// minimum field
	#ifdef FIELD
	// c
	printf("-------- c --------\n");
	printf("-------- c --------\n");

	// s
	printf("-------- s --------\n");
	TEST("[%%0s] : [%0s]\n", "");
	TEST("[%%0s] : [%0s]\n", NULL);
	TEST("[%%0s] : [%0s]\n", "abcd");
	TEST("[%%0s] : [%0s]\n", "01234567890123456");
	TEST("[%%0s] : [%0s]\n", "9876");
	TEST("[%%0s] : [%0s]\n", "-1234");
	TEST("[%%0s] : [%0s]\n", "f");

	TEST("[%%1s] : [%1s]\n", "");
	TEST("[%%1s] : [%1s]\n", NULL);
	TEST("[%%1s] : [%1s]\n", "abcd");
	TEST("[%%1s] : [%1s]\n", "01234567890123456");
	TEST("[%%1s] : [%1s]\n", "9876");
	TEST("[%%1s] : [%1s]\n", "-1234");
	TEST("[%%1s] : [%1s]\n", "f");

	TEST("[%%5s] : [%5s]\n", "");
	TEST("[%%5s] : [%5s]\n", NULL);
	TEST("[%%5s] : [%5s]\n", "abcd");
	TEST("[%%5s] : [%5s]\n", "01234567890123456");
	TEST("[%%5s] : [%5s]\n", "9876");
	TEST("[%%5s] : [%5s]\n", "-1234");
	TEST("[%%5s] : [%5s]\n", "f");

	TEST("[%%10s] : [%10s]\n", "");
	TEST("[%%10s] : [%10s]\n", NULL);
	TEST("[%%10s] : [%10s]\n", "abcd");
	TEST("[%%10s] : [%10s]\n", "01234567890123456");
	TEST("[%%10s] : [%10s]\n", "9876");
	TEST("[%%10s] : [%10s]\n", "-1234");
	TEST("[%%10s] : [%10s]\n", "f");
	printf("-------- s --------\n");

	// p
	printf("-------- p --------\n");
	TEST("[%%0p] : [%0p]\n", 0);
	TEST("[%%0p] : [%0p]\n", NULL);
	TEST("[%%0p] : [%0p]\n", -1);
	TEST("[%%0p] : [%0p]\n", 12345);
	TEST("[%%0p] : [%0p]\n", 9876);
	TEST("[%%0p] : [%0p]\n", -1234);
	TEST("[%%0p] : [%0p]\n", (void *)1);

	TEST("[%%1p] : [%1p]\n", 0);
	TEST("[%%1p] : [%1p]\n", NULL);
	TEST("[%%1p] : [%1p]\n", -1);
	TEST("[%%1p] : [%1p]\n", 12345);
	TEST("[%%1p] : [%1p]\n", 9876);
	TEST("[%%1p] : [%1p]\n", -1234);
	TEST("[%%1p] : [%1p]\n", (void *)1);

	TEST("[%%5p] : [%5p]\n", 0);
	TEST("[%%5p] : [%5p]\n", NULL);
	TEST("[%%5p] : [%5p]\n", -1);
	TEST("[%%5p] : [%5p]\n", 12345);
	TEST("[%%5p] : [%5p]\n", 9876);
	TEST("[%%5p] : [%5p]\n", -1234);
	TEST("[%%5p] : [%5p]\n", (void *)1);

	TEST("[%%10p] : [%10p]\n", 0);
	TEST("[%%10p] : [%10p]\n", NULL);
	TEST("[%%10p] : [%10p]\n", -1);
	TEST("[%%10p] : [%10p]\n", 12345);
	TEST("[%%10p] : [%10p]\n", 9876);
	TEST("[%%10p] : [%10p]\n", -1234);
	TEST("[%%10p] : [%10p]\n", (void *)1);
	printf("-------- p --------\n");

	// d
	printf("-------- d --------\n");
	TEST("[%%0d] : [%0d]\n", 0);
	TEST("[%%0d] : [%0d]\n", -1);
	TEST("[%%0d] : [%0d]\n", 4321);
	TEST("[%%0d] : [%0d]\n", 12345);
	TEST("[%%0d] : [%0d]\n", 9876);
	TEST("[%%0d] : [%0d]\n", INT_MIN);
	TEST("[%%0d] : [%0d]\n", INT_MAX);
	TEST("[%%0d] : [%0d]\n", LONG_MIN);
	TEST("[%%0d] : [%0d]\n", LONG_MAX);

	TEST("[%%1d] : [%1d]\n", 0);
	TEST("[%%1d] : [%1d]\n", -1);
	TEST("[%%1d] : [%1d]\n", 4321);
	TEST("[%%1d] : [%1d]\n", 12345);
	TEST("[%%1d] : [%1d]\n", 9876);
	TEST("[%%1d] : [%1d]\n", INT_MIN);
	TEST("[%%1d] : [%1d]\n", INT_MAX);
	TEST("[%%1d] : [%1d]\n", LONG_MIN);
	TEST("[%%1d] : [%1d]\n", LONG_MAX);

	TEST("[%%5d] : [%5d]\n", 0);
	TEST("[%%5d] : [%5d]\n", -1);
	TEST("[%%5d] : [%5d]\n", 4321);
	TEST("[%%5d] : [%5d]\n", 12345);
	TEST("[%%5d] : [%5d]\n", 9876);
	TEST("[%%5d] : [%5d]\n", INT_MIN);
	TEST("[%%5d] : [%5d]\n", INT_MAX);
	TEST("[%%5d] : [%5d]\n", LONG_MIN);
	TEST("[%%5d] : [%5d]\n", LONG_MAX);

	TEST("[%%10d] : [%10d]\n", 0);
	TEST("[%%10d] : [%10d]\n", -1);
	TEST("[%%10d] : [%10d]\n", 4321);
	TEST("[%%10d] : [%10d]\n", 12345);
	TEST("[%%10d] : [%10d]\n", 9876);
	TEST("[%%10d] : [%10d]\n", INT_MIN);
	TEST("[%%10d] : [%10d]\n", INT_MAX);
	TEST("[%%10d] : [%10d]\n", LONG_MIN);
	TEST("[%%10d] : [%10d]\n", LONG_MAX);
	printf("-------- d --------\n");
	// i
	printf("-------- i --------\n");
	TEST("[%%0i] : [%0i]\n", 0);
	TEST("[%%0i] : [%0i]\n", -1);
	TEST("[%%0i] : [%0i]\n", 4321);
	TEST("[%%0i] : [%0i]\n", 12345);
	TEST("[%%0i] : [%0i]\n", 9876);
	TEST("[%%0i] : [%0i]\n", INT_MIN);
	TEST("[%%0i] : [%0i]\n", INT_MAX);
	TEST("[%%0i] : [%0i]\n", LONG_MIN);
	TEST("[%%0i] : [%0i]\n", LONG_MAX);

	TEST("[%%1i] : [%1i]\n", 0);
	TEST("[%%1i] : [%1i]\n", -1);
	TEST("[%%1i] : [%1i]\n", 4321);
	TEST("[%%1i] : [%1i]\n", 12345);
	TEST("[%%1i] : [%1i]\n", 9876);
	TEST("[%%1i] : [%1i]\n", INT_MIN);
	TEST("[%%1i] : [%1i]\n", INT_MAX);
	TEST("[%%1i] : [%1i]\n", LONG_MIN);
	TEST("[%%1i] : [%1i]\n", LONG_MAX);

	TEST("[%%5i] : [%5i]\n", 0);
	TEST("[%%5i] : [%5i]\n", -1);
	TEST("[%%5i] : [%5i]\n", 4321);
	TEST("[%%5i] : [%5i]\n", 12345);
	TEST("[%%5i] : [%5i]\n", 9876);
	TEST("[%%5i] : [%5i]\n", INT_MIN);
	TEST("[%%5i] : [%5i]\n", INT_MAX);
	TEST("[%%5i] : [%5i]\n", LONG_MIN);
	TEST("[%%5i] : [%5i]\n", LONG_MAX);

	TEST("[%%10i] : [%10i]\n", 0);
	TEST("[%%10i] : [%10i]\n", -1);
	TEST("[%%10i] : [%10i]\n", 4321);
	TEST("[%%10i] : [%10i]\n", 12345);
	TEST("[%%10i] : [%10i]\n", 9876);
	TEST("[%%10i] : [%10i]\n", INT_MIN);
	TEST("[%%10i] : [%10i]\n", INT_MAX);
	TEST("[%%10i] : [%10i]\n", LONG_MIN);
	TEST("[%%10i] : [%10i]\n", LONG_MAX);
	printf("-------- i --------\n");
	// u
	printf("-------- u --------\n");
	TEST("[%%0u] : [%0u]\n", 0);
	TEST("[%%0u] : [%0u]\n", -1);
	TEST("[%%0u] : [%0u]\n", 4321);
	TEST("[%%0u] : [%0u]\n", 12345);
	TEST("[%%0u] : [%0u]\n", 9876);
	TEST("[%%0u] : [%0u]\n", INT_MIN);
	TEST("[%%0u] : [%0u]\n", INT_MAX);
	TEST("[%%0u] : [%0u]\n", LONG_MIN);
	TEST("[%%0u] : [%0u]\n", LONG_MAX);

	TEST("[%%1u] : [%1u]\n", 0);
	TEST("[%%1u] : [%1u]\n", -1);
	TEST("[%%1u] : [%1u]\n", 4321);
	TEST("[%%1u] : [%1u]\n", 12345);
	TEST("[%%1u] : [%1u]\n", 9876);
	TEST("[%%1u] : [%1u]\n", INT_MIN);
	TEST("[%%1u] : [%1u]\n", INT_MAX);
	TEST("[%%1u] : [%1u]\n", LONG_MIN);
	TEST("[%%1u] : [%1u]\n", LONG_MAX);

	TEST("[%%5u] : [%5u]\n", 0);
	TEST("[%%5u] : [%5u]\n", -1);
	TEST("[%%5u] : [%5u]\n", 4321);
	TEST("[%%5u] : [%5u]\n", 12345);
	TEST("[%%5u] : [%5u]\n", 9876);
	TEST("[%%5u] : [%5u]\n", INT_MIN);
	TEST("[%%5u] : [%5u]\n", INT_MAX);
	TEST("[%%5u] : [%5u]\n", LONG_MIN);
	TEST("[%%5u] : [%5u]\n", LONG_MAX);

	TEST("[%%10u] : [%10u]\n", 0);
	TEST("[%%10u] : [%10u]\n", -1);
	TEST("[%%10u] : [%10u]\n", 4321);
	TEST("[%%10u] : [%10u]\n", 12345);
	TEST("[%%10u] : [%10u]\n", 9876);
	TEST("[%%10u] : [%10u]\n", INT_MIN);
	TEST("[%%10u] : [%10u]\n", INT_MAX);
	TEST("[%%10u] : [%10u]\n", LONG_MIN);
	TEST("[%%10u] : [%10u]\n", LONG_MAX);
	printf("-------- u --------\n");
	// x
	printf("-------- x --------\n");
	TEST("[%%0x] : [%0x]\n", 0);
	TEST("[%%0x] : [%0x]\n", NULL);
	TEST("[%%0x] : [%0x]\n", -1);
	TEST("[%%0x] : [%0x]\n", 12345);
	TEST("[%%0x] : [%0x]\n", 9876);
	TEST("[%%0x] : [%0x]\n", -1234);
	TEST("[%%0x] : [%0x]\n", (void *)1);

	TEST("[%%1x] : [%1x]\n", 0);
	TEST("[%%1x] : [%1x]\n", NULL);
	TEST("[%%1x] : [%1x]\n", -1);
	TEST("[%%1x] : [%1x]\n", 12345);
	TEST("[%%1x] : [%1x]\n", 9876);
	TEST("[%%1x] : [%1x]\n", -1234);
	TEST("[%%1x] : [%1x]\n", (void *)1);

	TEST("[%%5x] : [%5x]\n", 0);
	TEST("[%%5x] : [%5x]\n", NULL);
	TEST("[%%5x] : [%5x]\n", -1);
	TEST("[%%5x] : [%5x]\n", 12345);
	TEST("[%%5x] : [%5x]\n", 9876);
	TEST("[%%5x] : [%5x]\n", -1234);
	TEST("[%%5x] : [%5x]\n", (void *)1);

	TEST("[%%10x] : [%10x]\n", 0);
	TEST("[%%10x] : [%10x]\n", NULL);
	TEST("[%%10x] : [%10x]\n", -1);
	TEST("[%%10x] : [%10x]\n", 12345);
	TEST("[%%10x] : [%10x]\n", 9876);
	TEST("[%%10x] : [%10x]\n", -1234);
	TEST("[%%10x] : [%10x]\n", (void *)1);
	printf("-------- x --------\n");

	// X
	printf("-------- X --------\n");
	TEST("[%%0X] : [%0X]\n", 0);
	TEST("[%%0X] : [%0X]\n", NULL);
	TEST("[%%0X] : [%0X]\n", -1);
	TEST("[%%0X] : [%0X]\n", 12345);
	TEST("[%%0X] : [%0X]\n", 9876);
	TEST("[%%0X] : [%0X]\n", -1234);
	TEST("[%%0X] : [%0X]\n", (void *)1);

	TEST("[%%1X] : [%1X]\n", 0);
	TEST("[%%1X] : [%1X]\n", NULL);
	TEST("[%%1X] : [%1X]\n", -1);
	TEST("[%%1X] : [%1X]\n", 12345);
	TEST("[%%1X] : [%1X]\n", 9876);
	TEST("[%%1X] : [%1X]\n", -1234);
	TEST("[%%1X] : [%1X]\n", (void *)1);

	TEST("[%%5X] : [%5X]\n", 0);
	TEST("[%%5X] : [%5X]\n", NULL);
	TEST("[%%5X] : [%5X]\n", -1);
	TEST("[%%5X] : [%5X]\n", 12345);
	TEST("[%%5X] : [%5X]\n", 9876);
	TEST("[%%5X] : [%5X]\n", -1234);
	TEST("[%%5X] : [%5X]\n", (void *)1);

	TEST("[%%10X] : [%10X]\n", 0);
	TEST("[%%10X] : [%10X]\n", NULL);
	TEST("[%%10X] : [%10X]\n", -1);
	TEST("[%%10X] : [%10X]\n", 12345);
	TEST("[%%10X] : [%10X]\n", 9876);
	TEST("[%%10X] : [%10X]\n", -1234);
	TEST("[%%10X] : [%10X]\n", (void *)1);
	printf("-------- X --------\n");
	// %
	printf("-------- %% --------\n");
	printf("-------- %% --------\n");
	#endif

	// zero padding
	#ifdef ZERO
	// s
	printf("-------- s --------\n");
	TEST("[%%00s] : [%00s]\n", "");
	TEST("[%%00s] : [%00s]\n", NULL);
	TEST("[%%00s] : [%00s]\n", "abcd");
	TEST("[%%00s] : [%00s]\n", "01234567890123456");
	TEST("[%%00s] : [%00s]\n", "9876");
	TEST("[%%00s] : [%00s]\n", "-1234");
	TEST("[%%00s] : [%00s]\n", "f");

	TEST("[%%01s] : [%01s]\n", "");
	TEST("[%%01s] : [%01s]\n", NULL);
	TEST("[%%01s] : [%01s]\n", "abcd");
	TEST("[%%01s] : [%01s]\n", "01234567890123456");
	TEST("[%%01s] : [%01s]\n", "9876");
	TEST("[%%01s] : [%01s]\n", "-1234");
	TEST("[%%01s] : [%01s]\n", "f");

	TEST("[%%05s] : [%05s]\n", "");
	TEST("[%%05s] : [%05s]\n", NULL);
	TEST("[%%05s] : [%05s]\n", "abcd");
	TEST("[%%05s] : [%05s]\n", "01234567890123456");
	TEST("[%%05s] : [%05s]\n", "9876");
	TEST("[%%05s] : [%05s]\n", "-1234");
	TEST("[%%05s] : [%05s]\n", "f");

	TEST("[%%010s] : [%010s]\n", "");
	TEST("[%%010s] : [%010s]\n", NULL);
	TEST("[%%010s] : [%010s]\n", "abcd");
	TEST("[%%010s] : [%010s]\n", "01234567890123456");
	TEST("[%%010s] : [%010s]\n", "9876");
	TEST("[%%010s] : [%010s]\n", "-1234");
	TEST("[%%010s] : [%010s]\n", "f");
	printf("-------- s --------\n");

	// p
	printf("-------- p --------\n");
	TEST("[%%0p] : [%0p]\n", 0);
	TEST("[%%0p] : [%0p]\n", NULL);
	TEST("[%%0p] : [%0p]\n", -1);
	TEST("[%%0p] : [%0p]\n", 12345);
	TEST("[%%0p] : [%0p]\n", 9876);
	TEST("[%%0p] : [%0p]\n", -1234);
	TEST("[%%0p] : [%0p]\n", (void *)1);

	TEST("[%%01p] : [%01p]\n", 0);
	TEST("[%%01p] : [%01p]\n", NULL);
	TEST("[%%01p] : [%01p]\n", -1);
	TEST("[%%01p] : [%01p]\n", 12345);
	TEST("[%%01p] : [%01p]\n", 9876);
	TEST("[%%01p] : [%01p]\n", -1234);
	TEST("[%%01p] : [%01p]\n", (void *)1);

	TEST("[%%05p] : [%05p]\n", 0);
	TEST("[%%05p] : [%05p]\n", NULL);
	TEST("[%%05p] : [%05p]\n", -1);
	TEST("[%%05p] : [%05p]\n", 12345);
	TEST("[%%05p] : [%05p]\n", 9876);
	TEST("[%%05p] : [%05p]\n", -1234);
	TEST("[%%05p] : [%05p]\n", (void *)1);

	TEST("[%%010p] : [%010p]\n", 0);
	TEST("[%%010p] : [%010p]\n", NULL);
	TEST("[%%010p] : [%010p]\n", -1);
	TEST("[%%010p] : [%010p]\n", 12345);
	TEST("[%%010p] : [%010p]\n", 9876);
	TEST("[%%010p] : [%010p]\n", -1234);
	TEST("[%%010p] : [%010p]\n", (void *)1);
	printf("-------- p --------\n");

	// d
	printf("-------- d --------\n");
	TEST("[%%0d] : [%0d]\n", 0);
	TEST("[%%0d] : [%0d]\n", -1);
	TEST("[%%0d] : [%0d]\n", 4321);
	TEST("[%%0d] : [%0d]\n", 12345);
	TEST("[%%0d] : [%0d]\n", 9876);
	TEST("[%%0d] : [%0d]\n", INT_MIN);
	TEST("[%%0d] : [%0d]\n", INT_MAX);
	TEST("[%%0d] : [%0d]\n", LONG_MIN);
	TEST("[%%0d] : [%0d]\n", LONG_MAX);

	TEST("[%%01d] : [%01d]\n", 0);
	TEST("[%%01d] : [%01d]\n", -1);
	TEST("[%%01d] : [%01d]\n", 4321);
	TEST("[%%01d] : [%01d]\n", 12345);
	TEST("[%%01d] : [%01d]\n", 9876);
	TEST("[%%01d] : [%01d]\n", INT_MIN);
	TEST("[%%01d] : [%01d]\n", INT_MAX);
	TEST("[%%01d] : [%01d]\n", LONG_MIN);
	TEST("[%%01d] : [%01d]\n", LONG_MAX);

	TEST("[%%05d] : [%05d]\n", 0);
	TEST("[%%05d] : [%05d]\n", -1);
	TEST("[%%05d] : [%05d]\n", 4321);
	TEST("[%%05d] : [%05d]\n", 12345);
	TEST("[%%05d] : [%05d]\n", 9876);
	TEST("[%%05d] : [%05d]\n", INT_MIN);
	TEST("[%%05d] : [%05d]\n", INT_MAX);
	TEST("[%%05d] : [%05d]\n", LONG_MIN);
	TEST("[%%05d] : [%05d]\n", LONG_MAX);

	TEST("[%%010d] : [%010d]\n", 0);
	TEST("[%%010d] : [%010d]\n", -1);
	TEST("[%%010d] : [%010d]\n", 4321);
	TEST("[%%010d] : [%010d]\n", 12345);
	TEST("[%%010d] : [%010d]\n", 9876);
	TEST("[%%010d] : [%010d]\n", INT_MIN);
	TEST("[%%010d] : [%010d]\n", INT_MAX);
	TEST("[%%010d] : [%010d]\n", LONG_MIN);
	TEST("[%%010d] : [%010d]\n", LONG_MAX);
	printf("-------- d --------\n");
	// i
	printf("-------- i --------\n");
	TEST("[%%0i] : [%0i]\n", 0);
	TEST("[%%0i] : [%0i]\n", -1);
	TEST("[%%0i] : [%0i]\n", 4321);
	TEST("[%%0i] : [%0i]\n", 12345);
	TEST("[%%0i] : [%0i]\n", 9876);
	TEST("[%%0i] : [%0i]\n", INT_MIN);
	TEST("[%%0i] : [%0i]\n", INT_MAX);
	TEST("[%%0i] : [%0i]\n", LONG_MIN);
	TEST("[%%0i] : [%0i]\n", LONG_MAX);

	TEST("[%%01i] : [%01i]\n", 0);
	TEST("[%%01i] : [%01i]\n", -1);
	TEST("[%%01i] : [%01i]\n", 4321);
	TEST("[%%01i] : [%01i]\n", 12345);
	TEST("[%%01i] : [%01i]\n", 9876);
	TEST("[%%01i] : [%01i]\n", INT_MIN);
	TEST("[%%01i] : [%01i]\n", INT_MAX);
	TEST("[%%01i] : [%01i]\n", LONG_MIN);
	TEST("[%%01i] : [%01i]\n", LONG_MAX);

	TEST("[%%05i] : [%05i]\n", 0);
	TEST("[%%05i] : [%05i]\n", -1);
	TEST("[%%05i] : [%05i]\n", 4321);
	TEST("[%%05i] : [%05i]\n", 12345);
	TEST("[%%05i] : [%05i]\n", 9876);
	TEST("[%%05i] : [%05i]\n", INT_MIN);
	TEST("[%%05i] : [%05i]\n", INT_MAX);
	TEST("[%%05i] : [%05i]\n", LONG_MIN);
	TEST("[%%05i] : [%05i]\n", LONG_MAX);

	TEST("[%%010i] : [%010i]\n", 0);
	TEST("[%%010i] : [%010i]\n", -1);
	TEST("[%%010i] : [%010i]\n", 4321);
	TEST("[%%010i] : [%010i]\n", 12345);
	TEST("[%%010i] : [%010i]\n", 9876);
	TEST("[%%010i] : [%010i]\n", INT_MIN);
	TEST("[%%010i] : [%010i]\n", INT_MAX);
	TEST("[%%010i] : [%010i]\n", LONG_MIN);
	TEST("[%%010i] : [%010i]\n", LONG_MAX);
	printf("-------- i --------\n");
	// u
	printf("-------- u --------\n");
	TEST("[%%0u] : [%0u]\n", 0);
	TEST("[%%0u] : [%0u]\n", -1);
	TEST("[%%0u] : [%0u]\n", 4321);
	TEST("[%%0u] : [%0u]\n", 12345);
	TEST("[%%0u] : [%0u]\n", 9876);
	TEST("[%%0u] : [%0u]\n", INT_MIN);
	TEST("[%%0u] : [%0u]\n", INT_MAX);
	TEST("[%%0u] : [%0u]\n", LONG_MIN);
	TEST("[%%0u] : [%0u]\n", LONG_MAX);

	TEST("[%%01u] : [%01u]\n", 0);
	TEST("[%%01u] : [%01u]\n", -1);
	TEST("[%%01u] : [%01u]\n", 4321);
	TEST("[%%01u] : [%01u]\n", 12345);
	TEST("[%%01u] : [%01u]\n", 9876);
	TEST("[%%01u] : [%01u]\n", INT_MIN);
	TEST("[%%01u] : [%01u]\n", INT_MAX);
	TEST("[%%01u] : [%01u]\n", LONG_MIN);
	TEST("[%%01u] : [%01u]\n", LONG_MAX);

	TEST("[%%05u] : [%05u]\n", 0);
	TEST("[%%05u] : [%05u]\n", -1);
	TEST("[%%05u] : [%05u]\n", 4321);
	TEST("[%%05u] : [%05u]\n", 12345);
	TEST("[%%05u] : [%05u]\n", 9876);
	TEST("[%%05u] : [%05u]\n", INT_MIN);
	TEST("[%%05u] : [%05u]\n", INT_MAX);
	TEST("[%%05u] : [%05u]\n", LONG_MIN);
	TEST("[%%05u] : [%05u]\n", LONG_MAX);

	TEST("[%%010u] : [%010u]\n", 0);
	TEST("[%%010u] : [%010u]\n", -1);
	TEST("[%%010u] : [%010u]\n", 4321);
	TEST("[%%010u] : [%010u]\n", 12345);
	TEST("[%%010u] : [%010u]\n", 9876);
	TEST("[%%010u] : [%010u]\n", INT_MIN);
	TEST("[%%010u] : [%010u]\n", INT_MAX);
	TEST("[%%010u] : [%010u]\n", LONG_MIN);
	TEST("[%%010u] : [%010u]\n", LONG_MAX);
	printf("-------- u --------\n");

	// x
	printf("-------- x --------\n");
	TEST("[%%0x] : [%0x]\n", 0);
	TEST("[%%0x] : [%0x]\n", NULL);
	TEST("[%%0x] : [%0x]\n", -1);
	TEST("[%%0x] : [%0x]\n", 12345);
	TEST("[%%0x] : [%0x]\n", 9876);
	TEST("[%%0x] : [%0x]\n", -1234);
	TEST("[%%0x] : [%0x]\n", (void *)1);

	TEST("[%%01x] : [%01x]\n", 0);
	TEST("[%%01x] : [%01x]\n", NULL);
	TEST("[%%01x] : [%01x]\n", -1);
	TEST("[%%01x] : [%01x]\n", 12345);
	TEST("[%%01x] : [%01x]\n", 9876);
	TEST("[%%01x] : [%01x]\n", -1234);
	TEST("[%%01x] : [%01x]\n", (void *)1);

	TEST("[%%05x] : [%05x]\n", 0);
	TEST("[%%05x] : [%05x]\n", NULL);
	TEST("[%%05x] : [%05x]\n", -1);
	TEST("[%%05x] : [%05x]\n", 12345);
	TEST("[%%05x] : [%05x]\n", 9876);
	TEST("[%%05x] : [%05x]\n", -1234);
	TEST("[%%05x] : [%05x]\n", (void *)1);

	TEST("[%%010x] : [%010x]\n", 0);
	TEST("[%%010x] : [%010x]\n", NULL);
	TEST("[%%010x] : [%010x]\n", -1);
	TEST("[%%010x] : [%010x]\n", 12345);
	TEST("[%%010x] : [%010x]\n", 9876);
	TEST("[%%010x] : [%010x]\n", -1234);
	TEST("[%%010x] : [%010x]\n", (void *)1);
	printf("-------- x --------\n");

	// X
	printf("-------- X --------\n");
	TEST("[%%0X] : [%0X]\n", 0);
	TEST("[%%0X] : [%0X]\n", NULL);
	TEST("[%%0X] : [%0X]\n", -1);
	TEST("[%%0X] : [%0X]\n", 12345);
	TEST("[%%0X] : [%0X]\n", 9876);
	TEST("[%%0X] : [%0X]\n", -1234);
	TEST("[%%0X] : [%0X]\n", (void *)1);

	TEST("[%%01X] : [%01X]\n", 0);
	TEST("[%%01X] : [%01X]\n", NULL);
	TEST("[%%01X] : [%01X]\n", -1);
	TEST("[%%01X] : [%01X]\n", 12345);
	TEST("[%%01X] : [%01X]\n", 9876);
	TEST("[%%01X] : [%01X]\n", -1234);
	TEST("[%%01X] : [%01X]\n", (void *)1);

	TEST("[%%05X] : [%05X]\n", 0);
	TEST("[%%05X] : [%05X]\n", NULL);
	TEST("[%%05X] : [%05X]\n", -1);
	TEST("[%%05X] : [%05X]\n", 12345);
	TEST("[%%05X] : [%05X]\n", 9876);
	TEST("[%%05X] : [%05X]\n", -1234);
	TEST("[%%05X] : [%05X]\n", (void *)1);

	TEST("[%%010X] : [%010X]\n", 0);
	TEST("[%%010X] : [%010X]\n", NULL);
	TEST("[%%010X] : [%010X]\n", -1);
	TEST("[%%010X] : [%010X]\n", 12345);
	TEST("[%%010X] : [%010X]\n", 9876);
	TEST("[%%010X] : [%010X]\n", -1234);
	TEST("[%%010X] : [%010X]\n", (void *)1);
	printf("-------- X --------\n");
	// %
	printf("-------- %% --------\n");
	printf("-------- %% --------\n");
	#endif

	// dot
	#ifdef DOT
	printf("........ DOT ........\n");
	// c
	printf("-------- c --------\n");
	printf("-------- c --------\n");

	// s
	printf("-------- s --------\n");
	TEST("[%%.s] : [%.s]\n", "");
	TEST("[%%.s] : [%.s]\n", NULL);
	TEST("[%%.s] : [%.s]\n", "abcd");
	TEST("[%%.s] : [%.s]\n", "01234567890123456");
	TEST("[%%.s] : [%.s]\n", "9876");
	TEST("[%%.s] : [%.s]\n", "-1234");
	TEST("[%%.s] : [%.s]\n", "f");

	TEST("[%%0.1s] : [%0.1s]\n", "");
	TEST("[%%0.1s] : [%0.1s]\n", NULL);
	TEST("[%%0.1s] : [%0.1s]\n", "abcd");
	TEST("[%%0.1s] : [%0.1s]\n", "01234567890123456");
	TEST("[%%0.1s] : [%0.1s]\n", "9876");
	TEST("[%%0.1s] : [%0.1s]\n", "-1234");
	TEST("[%%0.1s] : [%0.1s]\n", "f");

	TEST("[%%10.5s] : [%10.5s]\n", "");
	TEST("[%%10.5s] : [%10.5s]\n", NULL);
	TEST("[%%10.5s] : [%10.5s]\n", "abcd");
	TEST("[%%10.5s] : [%10.5s]\n", "01234567890123456");
	TEST("[%%10.5s] : [%10.5s]\n", "9876");
	TEST("[%%10.5s] : [%10.5s]\n", "-1234");
	TEST("[%%10.5s] : [%10.5s]\n", "f");

	TEST("[%%5.10s] : [%5.10s]\n", "");
	TEST("[%%5.10s] : [%5.10s]\n", NULL);
	TEST("[%%5.10s] : [%5.10s]\n", "abcd");
	TEST("[%%5.10s] : [%5.10s]\n", "01234567890123456");
	TEST("[%%5.10s] : [%5.10s]\n", "9876");
	TEST("[%%5.10s] : [%5.10s]\n", "-1234");
	TEST("[%%5.10s] : [%5.10s]\n", "f");
	printf("-------- s --------\n");

	// p
	printf("-------- p --------\n");
	TEST("[%%.p] : [%.p]\n", 0);
	TEST("[%%.p] : [%.p]\n", NULL);
	TEST("[%%.p] : [%.p]\n", -1);
	TEST("[%%.p] : [%.p]\n", 12345);
	TEST("[%%.p] : [%.p]\n", 9876);
	TEST("[%%.p] : [%.p]\n", -1234);
	TEST("[%%.p] : [%.p]\n", (void *)1);

	TEST("[%%0.1p] : [%0.1p]\n", 0);
	TEST("[%%0.1p] : [%0.1p]\n", NULL);
	TEST("[%%0.1p] : [%0.1p]\n", -1);
	TEST("[%%0.1p] : [%0.1p]\n", 12345);
	TEST("[%%0.1p] : [%0.1p]\n", 9876);
	TEST("[%%0.1p] : [%0.1p]\n", -1234);
	TEST("[%%0.1p] : [%0.1p]\n", (void *)1);

	TEST("[%%10.5p] : [%10.5p]\n", 0);
	TEST("[%%10.5p] : [%10.5p]\n", NULL);
	TEST("[%%10.5p] : [%10.5p]\n", -1);
	TEST("[%%10.5p] : [%10.5p]\n", 12345);
	TEST("[%%10.5p] : [%10.5p]\n", 9876);
	TEST("[%%10.5p] : [%10.5p]\n", -1234);
	TEST("[%%10.5p] : [%10.5p]\n", (void *)1);

	TEST("[%%5.10p] : [%5.10p]\n", 0);
	TEST("[%%5.10p] : [%5.10p]\n", NULL);
	TEST("[%%5.10p] : [%5.10p]\n", -1);
	TEST("[%%5.10p] : [%5.10p]\n", 12345);
	TEST("[%%5.10p] : [%5.10p]\n", 9876);
	TEST("[%%5.10p] : [%5.10p]\n", -1234);
	TEST("[%%5.10p] : [%5.10p]\n", (void *)1);
	printf("-------- p --------\n");

	// d
	printf("-------- d --------\n");
	TEST("[%%.d] : [%.d]\n", 0);
	TEST("[%%.d] : [%.d]\n", -1);
	TEST("[%%.d] : [%.d]\n", 4321);
	TEST("[%%.d] : [%.d]\n", 12345);
	TEST("[%%.d] : [%.d]\n", 9876);
	TEST("[%%.d] : [%.d]\n", INT_MIN);
	TEST("[%%.d] : [%.d]\n", INT_MAX);
	TEST("[%%.d] : [%.d]\n", LONG_MIN);
	TEST("[%%.d] : [%.d]\n", LONG_MAX);

	TEST("[%%0.1d] : [%0.1d]\n", 0);
	TEST("[%%0.1d] : [%0.1d]\n", -1);
	TEST("[%%0.1d] : [%0.1d]\n", 4321);
	TEST("[%%0.1d] : [%0.1d]\n", 12345);
	TEST("[%%0.1d] : [%0.1d]\n", 9876);
	TEST("[%%0.1d] : [%0.1d]\n", INT_MIN);
	TEST("[%%0.1d] : [%0.1d]\n", INT_MAX);
	TEST("[%%0.1d] : [%0.1d]\n", LONG_MIN);
	TEST("[%%0.1d] : [%0.1d]\n", LONG_MAX);

	TEST("[%%10.5d] : [%10.5d]\n", 0);
	TEST("[%%10.5d] : [%10.5d]\n", -1);
	TEST("[%%10.5d] : [%10.5d]\n", 4321);
	TEST("[%%10.5d] : [%10.5d]\n", 12345);
	TEST("[%%10.5d] : [%10.5d]\n", 9876);
	TEST("[%%10.5d] : [%10.5d]\n", INT_MIN);
	TEST("[%%10.5d] : [%10.5d]\n", INT_MAX);
	TEST("[%%10.5d] : [%10.5d]\n", LONG_MIN);
	TEST("[%%10.5d] : [%10.5d]\n", LONG_MAX);

	TEST("[%%10.5d] : [%10.5d]\n", 0);
	TEST("[%%10.5d] : [%10.5d]\n", -1);
	TEST("[%%10.5d] : [%10.5d]\n", 4321);
	TEST("[%%10.5d] : [%10.5d]\n", 12345);
	TEST("[%%10.5d] : [%10.5d]\n", 9876);
	TEST("[%%10.5d] : [%10.5d]\n", INT_MIN);
	TEST("[%%10.5d] : [%10.5d]\n", INT_MAX);
	TEST("[%%10.5d] : [%10.5d]\n", LONG_MIN);
	TEST("[%%10.5d] : [%10.5d]\n", LONG_MAX);
	printf("-------- d --------\n");
	// i
	printf("-------- i --------\n");
	TEST("[%%.i] : [%.i]\n", 0);
	TEST("[%%.i] : [%.i]\n", -1);
	TEST("[%%.i] : [%.i]\n", 4321);
	TEST("[%%.i] : [%.i]\n", 12345);
	TEST("[%%.i] : [%.i]\n", 9876);
	TEST("[%%.i] : [%.i]\n", INT_MIN);
	TEST("[%%.i] : [%.i]\n", INT_MAX);
	TEST("[%%.i] : [%.i]\n", LONG_MIN);
	TEST("[%%.i] : [%.i]\n", LONG_MAX);

	TEST("[%%0.1i] : [%0.1i]\n", 0);
	TEST("[%%0.1i] : [%0.1i]\n", -1);
	TEST("[%%0.1i] : [%0.1i]\n", 4321);
	TEST("[%%0.1i] : [%0.1i]\n", 12345);
	TEST("[%%0.1i] : [%0.1i]\n", 9876);
	TEST("[%%0.1i] : [%0.1i]\n", INT_MIN);
	TEST("[%%0.1i] : [%0.1i]\n", INT_MAX);
	TEST("[%%0.1i] : [%0.1i]\n", LONG_MIN);
	TEST("[%%0.1i] : [%0.1i]\n", LONG_MAX);

	TEST("[%%10.5i] : [%10.5i]\n", 0);
	TEST("[%%10.5i] : [%10.5i]\n", -1);
	TEST("[%%10.5i] : [%10.5i]\n", 4321);
	TEST("[%%10.5i] : [%10.5i]\n", 12345);
	TEST("[%%10.5i] : [%10.5i]\n", 9876);
	TEST("[%%10.5i] : [%10.5i]\n", INT_MIN);
	TEST("[%%10.5i] : [%10.5i]\n", INT_MAX);
	TEST("[%%10.5i] : [%10.5i]\n", LONG_MIN);
	TEST("[%%10.5i] : [%10.5i]\n", LONG_MAX);

	TEST("[%%10.5i] : [%10.5i]\n", 0);
	TEST("[%%10.5i] : [%10.5i]\n", -1);
	TEST("[%%10.5i] : [%10.5i]\n", 4321);
	TEST("[%%10.5i] : [%10.5i]\n", 12345);
	TEST("[%%10.5i] : [%10.5i]\n", 9876);
	TEST("[%%10.5i] : [%10.5i]\n", INT_MIN);
	TEST("[%%10.5i] : [%10.5i]\n", INT_MAX);
	TEST("[%%10.5i] : [%10.5i]\n", LONG_MIN);
	TEST("[%%10.5i] : [%10.5i]\n", LONG_MAX);
	printf("-------- i --------\n");

	// u
	printf("-------- u --------\n");
	TEST("[%%.u] : [%.u]\n", 0);
	TEST("[%%.u] : [%.u]\n", -1);
	TEST("[%%.u] : [%.u]\n", 4321);
	TEST("[%%.u] : [%.u]\n", 12345);
	TEST("[%%.u] : [%.u]\n", 9876);
	TEST("[%%.u] : [%.u]\n", INT_MIN);
	TEST("[%%.u] : [%.u]\n", INT_MAX);
	TEST("[%%.u] : [%.u]\n", LONG_MIN);
	TEST("[%%.u] : [%.u]\n", LONG_MAX);

	TEST("[%%0.1u] : [%0.1u]\n", 0);
	TEST("[%%0.1u] : [%0.1u]\n", -1);
	TEST("[%%0.1u] : [%0.1u]\n", 4321);
	TEST("[%%0.1u] : [%0.1u]\n", 12345);
	TEST("[%%0.1u] : [%0.1u]\n", 9876);
	TEST("[%%0.1u] : [%0.1u]\n", INT_MIN);
	TEST("[%%0.1u] : [%0.1u]\n", INT_MAX);
	TEST("[%%0.1u] : [%0.1u]\n", LONG_MIN);
	TEST("[%%0.1u] : [%0.1u]\n", LONG_MAX);

	TEST("[%%10.5u] : [%10.5u]\n", 0);
	TEST("[%%10.5u] : [%10.5u]\n", -1);
	TEST("[%%10.5u] : [%10.5u]\n", 4321);
	TEST("[%%10.5u] : [%10.5u]\n", 12345);
	TEST("[%%10.5u] : [%10.5u]\n", 9876);
	TEST("[%%10.5u] : [%10.5u]\n", INT_MIN);
	TEST("[%%10.5u] : [%10.5u]\n", INT_MAX);
	TEST("[%%10.5u] : [%10.5u]\n", LONG_MIN);
	TEST("[%%10.5u] : [%10.5u]\n", LONG_MAX);

	TEST("[%%10.5u] : [%10.5u]\n", 0);
	TEST("[%%10.5u] : [%10.5u]\n", -1);
	TEST("[%%10.5u] : [%10.5u]\n", 4321);
	TEST("[%%10.5u] : [%10.5u]\n", 12345);
	TEST("[%%10.5u] : [%10.5u]\n", 9876);
	TEST("[%%10.5u] : [%10.5u]\n", INT_MIN);
	TEST("[%%10.5u] : [%10.5u]\n", INT_MAX);
	TEST("[%%10.5u] : [%10.5u]\n", LONG_MIN);
	TEST("[%%10.5u] : [%10.5u]\n", LONG_MAX);
	printf("-------- u --------\n");

	// x
	printf("-------- x --------\n");
	TEST("[%%.x] : [%.x]\n", 0);
	TEST("[%%.x] : [%.x]\n", NULL);
	TEST("[%%.x] : [%.x]\n", -1);
	TEST("[%%.x] : [%.x]\n", 12345);
	TEST("[%%.x] : [%.x]\n", 9876);
	TEST("[%%.x] : [%.x]\n", -1234);
	TEST("[%%.x] : [%.x]\n", (void *)1);

	TEST("[%%0.1x] : [%0.1x]\n", 0);
	TEST("[%%0.1x] : [%0.1x]\n", NULL);
	TEST("[%%0.1x] : [%0.1x]\n", -1);
	TEST("[%%0.1x] : [%0.1x]\n", 12345);
	TEST("[%%0.1x] : [%0.1x]\n", 9876);
	TEST("[%%0.1x] : [%0.1x]\n", -1234);
	TEST("[%%0.1x] : [%0.1x]\n", (void *)1);

	TEST("[%%10.5x] : [%10.5x]\n", 0);
	TEST("[%%10.5x] : [%10.5x]\n", NULL);
	TEST("[%%10.5x] : [%10.5x]\n", -1);
	TEST("[%%10.5x] : [%10.5x]\n", 12345);
	TEST("[%%10.5x] : [%10.5x]\n", 9876);
	TEST("[%%10.5x] : [%10.5x]\n", -1234);
	TEST("[%%10.5x] : [%10.5x]\n", (void *)1);

	TEST("[%%5.10x] : [%5.10x]\n", 0);
	TEST("[%%5.10x] : [%5.10x]\n", NULL);
	TEST("[%%5.10x] : [%5.10x]\n", -1);
	TEST("[%%5.10x] : [%5.10x]\n", 12345);
	TEST("[%%5.10x] : [%5.10x]\n", 9876);
	TEST("[%%5.10x] : [%5.10x]\n", -1234);
	TEST("[%%5.10x] : [%5.10x]\n", (void *)1);
	printf("-------- x --------\n");

	// X
	printf("-------- X --------\n");
	TEST("[%%.X] : [%.X]\n", 0);
	TEST("[%%.X] : [%.X]\n", NULL);
	TEST("[%%.X] : [%.X]\n", -1);
	TEST("[%%.X] : [%.X]\n", 12345);
	TEST("[%%.X] : [%.X]\n", 9876);
	TEST("[%%.X] : [%.X]\n", -1234);
	TEST("[%%.X] : [%.X]\n", (void *)1);

	TEST("[%%0.1X] : [%0.1X]\n", 0);
	TEST("[%%0.1X] : [%0.1X]\n", NULL);
	TEST("[%%0.1X] : [%0.1X]\n", -1);
	TEST("[%%0.1X] : [%0.1X]\n", 12345);
	TEST("[%%0.1X] : [%0.1X]\n", 9876);
	TEST("[%%0.1X] : [%0.1X]\n", -1234);
	TEST("[%%0.1X] : [%0.1X]\n", (void *)1);

	TEST("[%%10.5X] : [%10.5X]\n", 0);
	TEST("[%%10.5X] : [%10.5X]\n", NULL);
	TEST("[%%10.5X] : [%10.5X]\n", -1);
	TEST("[%%10.5X] : [%10.5X]\n", 12345);
	TEST("[%%10.5X] : [%10.5X]\n", 9876);
	TEST("[%%10.5X] : [%10.5X]\n", -1234);
	TEST("[%%10.5X] : [%10.5X]\n", (void *)1);

	TEST("[%%5.10X] : [%5.10X]\n", 0);
	TEST("[%%5.10X] : [%5.10X]\n", NULL);
	TEST("[%%5.10X] : [%5.10X]\n", -1);
	TEST("[%%5.10X] : [%5.10X]\n", 12345);
	TEST("[%%5.10X] : [%5.10X]\n", 9876);
	TEST("[%%5.10X] : [%5.10X]\n", -1234);
	TEST("[%%5.10X] : [%5.10X]\n", (void *)1);
	printf("-------- X --------\n");
	printf("....................\n");
	#endif

	// sharp
	#ifdef SHARP
	printf("#######SHARP#######\n");

	// s
	printf("-------- s --------\n");
	TEST("[%%#s] : [%#s]\n", "");
	TEST("[%%#s] : [%#s]\n", NULL);
	TEST("[%%#s] : [%#s]\n", "abcd");
	TEST("[%%#s] : [%#s]\n", "01234567890123456");
	TEST("[%%#s] : [%#s]\n", "9876");
	TEST("[%%#s] : [%#s]\n", "-1234");
	TEST("[%%#s] : [%#s]\n", "f");

	TEST("[%%#1s] : [%#1s]\n", "");
	TEST("[%%#1s] : [%#1s]\n", NULL);
	TEST("[%%#1s] : [%#1s]\n", "abcd");
	TEST("[%%#1s] : [%#1s]\n", "01234567890123456");
	TEST("[%%#1s] : [%#1s]\n", "9876");
	TEST("[%%#1s] : [%#1s]\n", "-1234");
	TEST("[%%#1s] : [%#1s]\n", "f");

	TEST("[%%#5s] : [%#5s]\n", "");
	TEST("[%%#5s] : [%#5s]\n", NULL);
	TEST("[%%#5s] : [%#5s]\n", "abcd");
	TEST("[%%#5s] : [%#5s]\n", "01234567890123456");
	TEST("[%%#5s] : [%#5s]\n", "9876");
	TEST("[%%#5s] : [%#5s]\n", "-1234");
	TEST("[%%#5s] : [%#5s]\n", "f");

	TEST("[%%#10s] : [%#10s]\n", "");
	TEST("[%%#10s] : [%#10s]\n", NULL);
	TEST("[%%#10s] : [%#10s]\n", "abcd");
	TEST("[%%#10s] : [%#10s]\n", "01234567890123456");
	TEST("[%%#10s] : [%#10s]\n", "9876");
	TEST("[%%#10s] : [%#10s]\n", "-1234");
	TEST("[%%#10s] : [%#10s]\n", "f");
	printf("-------- s --------\n");

	// d
	printf("-------- d --------\n");
	TEST("[%%#d] : [%#d]\n", 0);
	TEST("[%%#d] : [%#d]\n", -1);
	TEST("[%%#d] : [%#d]\n", 4321);
	TEST("[%%#d] : [%#d]\n", 12345);
	TEST("[%%#d] : [%#d]\n", 9876);
	TEST("[%%#d] : [%#d]\n", INT_MIN);
	TEST("[%%#d] : [%#d]\n", INT_MAX);
	TEST("[%%#d] : [%#d]\n", LONG_MIN);
	TEST("[%%#d] : [%#d]\n", LONG_MAX);

	TEST("[%%#1d] : [%#1d]\n", 0);
	TEST("[%%#1d] : [%#1d]\n", -1);
	TEST("[%%#1d] : [%#1d]\n", 4321);
	TEST("[%%#1d] : [%#1d]\n", 12345);
	TEST("[%%#1d] : [%#1d]\n", 9876);
	TEST("[%%#1d] : [%#1d]\n", INT_MIN);
	TEST("[%%#1d] : [%#1d]\n", INT_MAX);
	TEST("[%%#1d] : [%#1d]\n", LONG_MIN);
	TEST("[%%#1d] : [%#1d]\n", LONG_MAX);

	TEST("[%%#5d] : [%#5d]\n", 0);
	TEST("[%%#5d] : [%#5d]\n", -1);
	TEST("[%%#5d] : [%#5d]\n", 4321);
	TEST("[%%#5d] : [%#5d]\n", 12345);
	TEST("[%%#5d] : [%#5d]\n", 9876);
	TEST("[%%#5d] : [%#5d]\n", INT_MIN);
	TEST("[%%#5d] : [%#5d]\n", INT_MAX);
	TEST("[%%#5d] : [%#5d]\n", LONG_MIN);
	TEST("[%%#5d] : [%#5d]\n", LONG_MAX);

	TEST("[%%#10d] : [%#10d]\n", 0);
	TEST("[%%#10d] : [%#10d]\n", -1);
	TEST("[%%#10d] : [%#10d]\n", 4321);
	TEST("[%%#10d] : [%#10d]\n", 12345);
	TEST("[%%#10d] : [%#10d]\n", 9876);
	TEST("[%%#10d] : [%#10d]\n", INT_MIN);
	TEST("[%%#10d] : [%#10d]\n", INT_MAX);
	TEST("[%%#10d] : [%#10d]\n", LONG_MIN);
	TEST("[%%#10d] : [%#10d]\n", LONG_MAX);
	printf("-------- d --------\n");

	// i
	printf("-------- i --------\n");
	TEST("[%%#i] : [%#i]\n", 0);
	TEST("[%%#i] : [%#i]\n", -1);
	TEST("[%%#i] : [%#i]\n", 4321);
	TEST("[%%#i] : [%#i]\n", 12345);
	TEST("[%%#i] : [%#i]\n", 9876);
	TEST("[%%#i] : [%#i]\n", INT_MIN);
	TEST("[%%#i] : [%#i]\n", INT_MAX);
	TEST("[%%#i] : [%#i]\n", LONG_MIN);
	TEST("[%%#i] : [%#i]\n", LONG_MAX);

	TEST("[%%#1i] : [%#1i]\n", 0);
	TEST("[%%#1i] : [%#1i]\n", -1);
	TEST("[%%#1i] : [%#1i]\n", 4321);
	TEST("[%%#1i] : [%#1i]\n", 12345);
	TEST("[%%#1i] : [%#1i]\n", 9876);
	TEST("[%%#1i] : [%#1i]\n", INT_MIN);
	TEST("[%%#1i] : [%#1i]\n", INT_MAX);
	TEST("[%%#1i] : [%#1i]\n", LONG_MIN);
	TEST("[%%#1i] : [%#1i]\n", LONG_MAX);

	TEST("[%%#5i] : [%#5i]\n", 0);
	TEST("[%%#5i] : [%#5i]\n", -1);
	TEST("[%%#5i] : [%#5i]\n", 4321);
	TEST("[%%#5i] : [%#5i]\n", 12345);
	TEST("[%%#5i] : [%#5i]\n", 9876);
	TEST("[%%#5i] : [%#5i]\n", INT_MIN);
	TEST("[%%#5i] : [%#5i]\n", INT_MAX);
	TEST("[%%#5i] : [%#5i]\n", LONG_MIN);
	TEST("[%%#5i] : [%#5i]\n", LONG_MAX);

	TEST("[%%#10i] : [%#10i]\n", 0);
	TEST("[%%#10i] : [%#10i]\n", -1);
	TEST("[%%#10i] : [%#10i]\n", 4321);
	TEST("[%%#10i] : [%#10i]\n", 12345);
	TEST("[%%#10i] : [%#10i]\n", 9876);
	TEST("[%%#10i] : [%#10i]\n", INT_MIN);
	TEST("[%%#10i] : [%#10i]\n", INT_MAX);
	TEST("[%%#10i] : [%#10i]\n", LONG_MIN);
	TEST("[%%#10i] : [%#10i]\n", LONG_MAX);
	printf("-------- i --------\n");

	// u
	printf("-------- u --------\n");
	TEST("[%%#u] : [%#u]\n", 0);
	TEST("[%%#u] : [%#u]\n", -1);
	TEST("[%%#u] : [%#u]\n", 4321);
	TEST("[%%#u] : [%#u]\n", 12345);
	TEST("[%%#u] : [%#u]\n", 9876);
	TEST("[%%#u] : [%#u]\n", INT_MIN);
	TEST("[%%#u] : [%#u]\n", INT_MAX);
	TEST("[%%#u] : [%#u]\n", LONG_MIN);
	TEST("[%%#u] : [%#u]\n", LONG_MAX);

	TEST("[%%#1u] : [%#1u]\n", 0);
	TEST("[%%#1u] : [%#1u]\n", -1);
	TEST("[%%#1u] : [%#1u]\n", 4321);
	TEST("[%%#1u] : [%#1u]\n", 12345);
	TEST("[%%#1u] : [%#1u]\n", 9876);
	TEST("[%%#1u] : [%#1u]\n", INT_MIN);
	TEST("[%%#1u] : [%#1u]\n", INT_MAX);
	TEST("[%%#1u] : [%#1u]\n", LONG_MIN);
	TEST("[%%#1u] : [%#1u]\n", LONG_MAX);

	TEST("[%%#5u] : [%#5u]\n", 0);
	TEST("[%%#5u] : [%#5u]\n", -1);
	TEST("[%%#5u] : [%#5u]\n", 4321);
	TEST("[%%#5u] : [%#5u]\n", 12345);
	TEST("[%%#5u] : [%#5u]\n", 9876);
	TEST("[%%#5u] : [%#5u]\n", INT_MIN);
	TEST("[%%#5u] : [%#5u]\n", INT_MAX);
	TEST("[%%#5u] : [%#5u]\n", LONG_MIN);
	TEST("[%%#5u] : [%#5u]\n", LONG_MAX);

	TEST("[%%#10u] : [%#10u]\n", 0);
	TEST("[%%#10u] : [%#10u]\n", -1);
	TEST("[%%#10u] : [%#10u]\n", 4321);
	TEST("[%%#10u] : [%#10u]\n", 12345);
	TEST("[%%#10u] : [%#10u]\n", 9876);
	TEST("[%%#10u] : [%#10u]\n", INT_MIN);
	TEST("[%%#10u] : [%#10u]\n", INT_MAX);
	TEST("[%%#10u] : [%#10u]\n", LONG_MIN);
	TEST("[%%#10u] : [%#10u]\n", LONG_MAX);
	printf("-------- u --------\n");

	// p
	printf("-------- p --------\n");
	TEST("[%%#p] : [%#p]\n", 0);
	TEST("[%%#p] : [%#p]\n", NULL);
	TEST("[%%#p] : [%#p]\n", -1);
	TEST("[%%#p] : [%#p]\n", 12345);
	TEST("[%%#p] : [%#p]\n", 9876);
	TEST("[%%#p] : [%#p]\n", -1234);
	TEST("[%%#p] : [%#p]\n", (void *)1);

	TEST("[%%#1p] : [%#1p]\n", 0);
	TEST("[%%#1p] : [%#1p]\n", NULL);
	TEST("[%%#1p] : [%#1p]\n", -1);
	TEST("[%%#1p] : [%#1p]\n", 12345);
	TEST("[%%#1p] : [%#1p]\n", 9876);
	TEST("[%%#1p] : [%#1p]\n", -1234);
	TEST("[%%#1p] : [%#1p]\n", (void *)1);

	TEST("[%%#5p] : [%#5p]\n", 0);
	TEST("[%%#5p] : [%#5p]\n", NULL);
	TEST("[%%#5p] : [%#5p]\n", -1);
	TEST("[%%#5p] : [%#5p]\n", 12345);
	TEST("[%%#5p] : [%#5p]\n", 9876);
	TEST("[%%#5p] : [%#5p]\n", -1234);
	TEST("[%%#5p] : [%#5p]\n", (void *)1);

	TEST("[%%#10p] : [%#10p]\n", 0);
	TEST("[%%#10p] : [%#10p]\n", NULL);
	TEST("[%%#10p] : [%#10p]\n", -1);
	TEST("[%%#10p] : [%#10p]\n", 12345);
	TEST("[%%#10p] : [%#10p]\n", 9876);
	TEST("[%%#10p] : [%#10p]\n", -1234);
	TEST("[%%#10p] : [%#10p]\n", (void *)1);
	printf("-------- p --------\n");

	// x
	printf("-------- x --------\n");
	TEST("[%%#x] : [%#x]\n", 0);
	TEST("[%%#x] : [%#x]\n", NULL);
	TEST("[%%#x] : [%#x]\n", -1);
	TEST("[%%#x] : [%#x]\n", 12345);
	TEST("[%%#x] : [%#x]\n", 9876);
	TEST("[%%#x] : [%#x]\n", -1234);
	TEST("[%%#x] : [%#x]\n", (void *)1);

	TEST("[%%#1x] : [%#1x]\n", 0);
	TEST("[%%#1x] : [%#1x]\n", NULL);
	TEST("[%%#1x] : [%#1x]\n", -1);
	TEST("[%%#1x] : [%#1x]\n", 12345);
	TEST("[%%#1x] : [%#1x]\n", 9876);
	TEST("[%%#1x] : [%#1x]\n", -1234);
	TEST("[%%#1x] : [%#1x]\n", (void *)1);

	TEST("[%%#5x] : [%#5x]\n", 0);
	TEST("[%%#5x] : [%#5x]\n", NULL);
	TEST("[%%#5x] : [%#5x]\n", -1);
	TEST("[%%#5x] : [%#5x]\n", 12345);
	TEST("[%%#5x] : [%#5x]\n", 9876);
	TEST("[%%#5x] : [%#5x]\n", -1234);
	TEST("[%%#5x] : [%#5x]\n", (void *)1);

	TEST("[%%#10x] : [%#10x]\n", 0);
	TEST("[%%#10x] : [%#10x]\n", NULL);
	TEST("[%%#10x] : [%#10x]\n", -1);
	TEST("[%%#10x] : [%#10x]\n", 12345);
	TEST("[%%#10x] : [%#10x]\n", 9876);
	TEST("[%%#10x] : [%#10x]\n", -1234);
	TEST("[%%#10x] : [%#10x]\n", (void *)1);
	printf("-------- x --------\n");

	// X
	printf("-------- X --------\n");
	TEST("[%%#X] : [%#X]\n", 0);
	TEST("[%%#X] : [%#X]\n", NULL);
	TEST("[%%#X] : [%#X]\n", -1);
	TEST("[%%#X] : [%#X]\n", 12345);
	TEST("[%%#X] : [%#X]\n", 9876);
	TEST("[%%#X] : [%#X]\n", -1234);
	TEST("[%%#X] : [%#X]\n", (void *)1);

	TEST("[%%#1X] : [%#1X]\n", 0);
	TEST("[%%#1X] : [%#1X]\n", NULL);
	TEST("[%%#1X] : [%#1X]\n", -1);
	TEST("[%%#1X] : [%#1X]\n", 12345);
	TEST("[%%#1X] : [%#1X]\n", 9876);
	TEST("[%%#1X] : [%#1X]\n", -1234);
	TEST("[%%#1X] : [%#1X]\n", (void *)1);

	TEST("[%%#5X] : [%#5X]\n", 0);
	TEST("[%%#5X] : [%#5X]\n", NULL);
	TEST("[%%#5X] : [%#5X]\n", -1);
	TEST("[%%#5X] : [%#5X]\n", 12345);
	TEST("[%%#5X] : [%#5X]\n", 9876);
	TEST("[%%#5X] : [%#5X]\n", -1234);
	TEST("[%%#5X] : [%#5X]\n", (void *)1);

	TEST("[%%#10X] : [%#10X]\n", 0);
	TEST("[%%#10X] : [%#10X]\n", NULL);
	TEST("[%%#10X] : [%#10X]\n", -1);
	TEST("[%%#10X] : [%#10X]\n", 12345);
	TEST("[%%#10X] : [%#10X]\n", 9876);
	TEST("[%%#10X] : [%#10X]\n", -1234);
	TEST("[%%#10X] : [%#10X]\n", (void *)1);
	printf("-------- X --------\n");
	printf("###################\n");
	#endif

	// space
	#ifdef SPACE
	printf("       SPACE       \n");

	// d
	printf("-------- d --------\n");
	TEST("[%% d] : [% d]\n", 0);
	TEST("[%% d] : [% d]\n", -1);
	TEST("[%% d] : [% d]\n", 4321);
	TEST("[%% d] : [% d]\n", 12345);
	TEST("[%% d] : [% d]\n", 9876);
	TEST("[%% d] : [% d]\n", INT_MIN);
	TEST("[%% d] : [% d]\n", INT_MAX);
	TEST("[%% d] : [% d]\n", LONG_MIN);
	TEST("[%% d] : [% d]\n", LONG_MAX);

	TEST("[%% 1d] : [% 1d]\n", 0);
	TEST("[%% 1d] : [% 1d]\n", -1);
	TEST("[%% 1d] : [% 1d]\n", 4321);
	TEST("[%% 1d] : [% 1d]\n", 12345);
	TEST("[%% 1d] : [% 1d]\n", 9876);
	TEST("[%% 1d] : [% 1d]\n", INT_MIN);
	TEST("[%% 1d] : [% 1d]\n", INT_MAX);
	TEST("[%% 1d] : [% 1d]\n", LONG_MIN);
	TEST("[%% 1d] : [% 1d]\n", LONG_MAX);

	TEST("[%% 5d] : [% 5d]\n", 0);
	TEST("[%% 5d] : [% 5d]\n", -1);
	TEST("[%% 5d] : [% 5d]\n", 4321);
	TEST("[%% 5d] : [% 5d]\n", 12345);
	TEST("[%% 5d] : [% 5d]\n", 9876);
	TEST("[%% 5d] : [% 5d]\n", INT_MIN);
	TEST("[%% 5d] : [% 5d]\n", INT_MAX);
	TEST("[%% 5d] : [% 5d]\n", LONG_MIN);
	TEST("[%% 5d] : [% 5d]\n", LONG_MAX);

	TEST("[%% 10d] : [% 10d]\n", 0);
	TEST("[%% 10d] : [% 10d]\n", -1);
	TEST("[%% 10d] : [% 10d]\n", 4321);
	TEST("[%% 10d] : [% 10d]\n", 12345);
	TEST("[%% 10d] : [% 10d]\n", 9876);
	TEST("[%% 10d] : [% 10d]\n", INT_MIN);
	TEST("[%% 10d] : [% 10d]\n", INT_MAX);
	TEST("[%% 10d] : [% 10d]\n", LONG_MIN);
	TEST("[%% 10d] : [% 10d]\n", LONG_MAX);
	printf("-------- d --------\n");

	// i
	printf("-------- i --------\n");
	TEST("[%% i] : [% i]\n", 0);
	TEST("[%% i] : [% i]\n", -1);
	TEST("[%% i] : [% i]\n", 4321);
	TEST("[%% i] : [% i]\n", 12345);
	TEST("[%% i] : [% i]\n", 9876);
	TEST("[%% i] : [% i]\n", INT_MIN);
	TEST("[%% i] : [% i]\n", INT_MAX);
	TEST("[%% i] : [% i]\n", LONG_MIN);
	TEST("[%% i] : [% i]\n", LONG_MAX);

	TEST("[%% 1i] : [% 1i]\n", 0);
	TEST("[%% 1i] : [% 1i]\n", -1);
	TEST("[%% 1i] : [% 1i]\n", 4321);
	TEST("[%% 1i] : [% 1i]\n", 12345);
	TEST("[%% 1i] : [% 1i]\n", 9876);
	TEST("[%% 1i] : [% 1i]\n", INT_MIN);
	TEST("[%% 1i] : [% 1i]\n", INT_MAX);
	TEST("[%% 1i] : [% 1i]\n", LONG_MIN);
	TEST("[%% 1i] : [% 1i]\n", LONG_MAX);

	TEST("[%% 5i] : [% 5i]\n", 0);
	TEST("[%% 5i] : [% 5i]\n", -1);
	TEST("[%% 5i] : [% 5i]\n", 4321);
	TEST("[%% 5i] : [% 5i]\n", 12345);
	TEST("[%% 5i] : [% 5i]\n", 9876);
	TEST("[%% 5i] : [% 5i]\n", INT_MIN);
	TEST("[%% 5i] : [% 5i]\n", INT_MAX);
	TEST("[%% 5i] : [% 5i]\n", LONG_MIN);
	TEST("[%% 5i] : [% 5i]\n", LONG_MAX);

	TEST("[%% 10i] : [% 10i]\n", 0);
	TEST("[%% 10i] : [% 10i]\n", -1);
	TEST("[%% 10i] : [% 10i]\n", 4321);
	TEST("[%% 10i] : [% 10i]\n", 12345);
	TEST("[%% 10i] : [% 10i]\n", 9876);
	TEST("[%% 10i] : [% 10i]\n", INT_MIN);
	TEST("[%% 10i] : [% 10i]\n", INT_MAX);
	TEST("[%% 10i] : [% 10i]\n", LONG_MIN);
	TEST("[%% 10i] : [% 10i]\n", LONG_MAX);
	printf("-------- i --------\n");

	// u
	printf("-------- u --------\n");
	TEST("[%% u] : [% u]\n", 0);
	TEST("[%% u] : [% u]\n", -1);
	TEST("[%% u] : [% u]\n", 4321);
	TEST("[%% u] : [% u]\n", 12345);
	TEST("[%% u] : [% u]\n", 9876);
	TEST("[%% u] : [% u]\n", INT_MIN);
	TEST("[%% u] : [% u]\n", INT_MAX);
	TEST("[%% u] : [% u]\n", LONG_MIN);
	TEST("[%% u] : [% u]\n", LONG_MAX);

	TEST("[%% 1u] : [% 1u]\n", 0);
	TEST("[%% 1u] : [% 1u]\n", -1);
	TEST("[%% 1u] : [% 1u]\n", 4321);
	TEST("[%% 1u] : [% 1u]\n", 12345);
	TEST("[%% 1u] : [% 1u]\n", 9876);
	TEST("[%% 1u] : [% 1u]\n", INT_MIN);
	TEST("[%% 1u] : [% 1u]\n", INT_MAX);
	TEST("[%% 1u] : [% 1u]\n", LONG_MIN);
	TEST("[%% 1u] : [% 1u]\n", LONG_MAX);

	TEST("[%% 5u] : [% 5u]\n", 0);
	TEST("[%% 5u] : [% 5u]\n", -1);
	TEST("[%% 5u] : [% 5u]\n", 4321);
	TEST("[%% 5u] : [% 5u]\n", 12345);
	TEST("[%% 5u] : [% 5u]\n", 9876);
	TEST("[%% 5u] : [% 5u]\n", INT_MIN);
	TEST("[%% 5u] : [% 5u]\n", INT_MAX);
	TEST("[%% 5u] : [% 5u]\n", LONG_MIN);
	TEST("[%% 5u] : [% 5u]\n", LONG_MAX);

	TEST("[%% 10u] : [% 10u]\n", 0);
	TEST("[%% 10u] : [% 10u]\n", -1);
	TEST("[%% 10u] : [% 10u]\n", 4321);
	TEST("[%% 10u] : [% 10u]\n", 12345);
	TEST("[%% 10u] : [% 10u]\n", 9876);
	TEST("[%% 10u] : [% 10u]\n", INT_MIN);
	TEST("[%% 10u] : [% 10u]\n", INT_MAX);
	TEST("[%% 10u] : [% 10u]\n", LONG_MIN);
	TEST("[%% 10u] : [% 10u]\n", LONG_MAX);
	printf("-------- u --------\n");

	// p
	printf("-------- p --------\n");
	printf("-------- p --------\n");

	// s
	printf("-------- s --------\n");
	TEST("[%% s] : [% s]\n", "");
	TEST("[%% s] : [% s]\n", NULL);
	TEST("[%% s] : [% s]\n", "abcd");
	TEST("[%% s] : [% s]\n", "01234567890123456");
	TEST("[%% s] : [% s]\n", "9876");
	TEST("[%% s] : [% s]\n", "-1234");
	TEST("[%% s] : [% s]\n", "f");

	TEST("[%% 1s] : [% 1s]\n", "");
	TEST("[%% 1s] : [% 1s]\n", NULL);
	TEST("[%% 1s] : [% 1s]\n", "abcd");
	TEST("[%% 1s] : [% 1s]\n", "01234567890123456");
	TEST("[%% 1s] : [% 1s]\n", "9876");
	TEST("[%% 1s] : [% 1s]\n", "-1234");
	TEST("[%% 1s] : [% 1s]\n", "f");

	TEST("[%% 5s] : [% 5s]\n", "");
	TEST("[%% 5s] : [% 5s]\n", NULL);
	TEST("[%% 5s] : [% 5s]\n", "abcd");
	TEST("[%% 5s] : [% 5s]\n", "01234567890123456");
	TEST("[%% 5s] : [% 5s]\n", "9876");
	TEST("[%% 5s] : [% 5s]\n", "-1234");
	TEST("[%% 5s] : [% 5s]\n", "f");

	TEST("[%% 10s] : [% 10s]\n", "");
	TEST("[%% 10s] : [% 10s]\n", NULL);
	TEST("[%% 10s] : [% 10s]\n", "abcd");
	TEST("[%% 10s] : [% 10s]\n", "01234567890123456");
	TEST("[%% 10s] : [% 10s]\n", "9876");
	TEST("[%% 10s] : [% 10s]\n", "-1234");
	TEST("[%% 10s] : [% 10s]\n", "f");
	printf("-------- s --------\n");
	printf("       SPACE       \n");
	#endif

	// plus
	#ifdef PLUS
	printf("+++++++PLUS++++++++\n");

	// s
	printf("-------- s --------\n");
	TEST("[%%+s] : [%+s]\n", "");
	TEST("[%%+s] : [%+s]\n", NULL);
	TEST("[%%+s] : [%+s]\n", "abcd");
	TEST("[%%+s] : [%+s]\n", "01234567890123456");
	TEST("[%%+s] : [%+s]\n", "9876");
	TEST("[%%+s] : [%+s]\n", "-1234");
	TEST("[%%+s] : [%+s]\n", "f");

	TEST("[%%+1s] : [%+1s]\n", "");
	TEST("[%%+1s] : [%+1s]\n", NULL);
	TEST("[%%+1s] : [%+1s]\n", "abcd");
	TEST("[%%+1s] : [%+1s]\n", "01234567890123456");
	TEST("[%%+1s] : [%+1s]\n", "9876");
	TEST("[%%+1s] : [%+1s]\n", "-1234");
	TEST("[%%+1s] : [%+1s]\n", "f");

	TEST("[%%+5s] : [%+5s]\n", "");
	TEST("[%%+5s] : [%+5s]\n", NULL);
	TEST("[%%+5s] : [%+5s]\n", "abcd");
	TEST("[%%+5s] : [%+5s]\n", "01234567890123456");
	TEST("[%%+5s] : [%+5s]\n", "9876");
	TEST("[%%+5s] : [%+5s]\n", "-1234");
	TEST("[%%+5s] : [%+5s]\n", "f");

	TEST("[%%+10s] : [%+10s]\n", "");
	TEST("[%%+10s] : [%+10s]\n", NULL);
	TEST("[%%+10s] : [%+10s]\n", "abcd");
	TEST("[%%+10s] : [%+10s]\n", "01234567890123456");
	TEST("[%%+10s] : [%+10s]\n", "9876");
	TEST("[%%+10s] : [%+10s]\n", "-1234");
	TEST("[%%+10s] : [%+10s]\n", "f");
	printf("-------- s --------\n");

	// p
	printf("-------- p --------\n");
	TEST("[%%+p] : [%+p]\n", 0);
	TEST("[%%+p] : [%+p]\n", NULL);
	TEST("[%%+p] : [%+p]\n", -1);
	TEST("[%%+p] : [%+p]\n", 12345);
	TEST("[%%+p] : [%+p]\n", 9876);
	TEST("[%%+p] : [%+p]\n", -1234);
	TEST("[%%+p] : [%+p]\n", (void *)1);

	TEST("[%%+1p] : [%+1p]\n", 0);
	TEST("[%%+1p] : [%+1p]\n", NULL);
	TEST("[%%+1p] : [%+1p]\n", -1);
	TEST("[%%+1p] : [%+1p]\n", 12345);
	TEST("[%%+1p] : [%+1p]\n", 9876);
	TEST("[%%+1p] : [%+1p]\n", -1234);
	TEST("[%%+1p] : [%+1p]\n", (void *)1);

	TEST("[%%+5p] : [%+5p]\n", 0);
	TEST("[%%+5p] : [%+5p]\n", NULL);
	TEST("[%%+5p] : [%+5p]\n", -1);
	TEST("[%%+5p] : [%+5p]\n", 12345);
	TEST("[%%+5p] : [%+5p]\n", 9876);
	TEST("[%%+5p] : [%+5p]\n", -1234);
	TEST("[%%+5p] : [%+5p]\n", (void *)1);

	TEST("[%%+10p] : [%+10p]\n", 0);
	TEST("[%%+10p] : [%+10p]\n", NULL);
	TEST("[%%+10p] : [%+10p]\n", -1);
	TEST("[%%+10p] : [%+10p]\n", 12345);
	TEST("[%%+10p] : [%+10p]\n", 9876);
	TEST("[%%+10p] : [%+10p]\n", -1234);
	TEST("[%%+10p] : [%+10p]\n", (void *)1);
	printf("-------- p --------\n");

	// d
	printf("-------- d --------\n");
	TEST("[%%+d] : [%+d]\n", 0);
	TEST("[%%+d] : [%+d]\n", -1);
	TEST("[%%+d] : [%+d]\n", 4321);
	TEST("[%%+d] : [%+d]\n", 12345);
	TEST("[%%+d] : [%+d]\n", 9876);
	TEST("[%%+d] : [%+d]\n", INT_MIN);
	TEST("[%%+d] : [%+d]\n", INT_MAX);
	TEST("[%%+d] : [%+d]\n", LONG_MIN);
	TEST("[%%+d] : [%+d]\n", LONG_MAX);

	TEST("[%%+1d] : [%+1d]\n", 0);
	TEST("[%%+1d] : [%+1d]\n", -1);
	TEST("[%%+1d] : [%+1d]\n", 4321);
	TEST("[%%+1d] : [%+1d]\n", 12345);
	TEST("[%%+1d] : [%+1d]\n", 9876);
	TEST("[%%+1d] : [%+1d]\n", INT_MIN);
	TEST("[%%+1d] : [%+1d]\n", INT_MAX);
	TEST("[%%+1d] : [%+1d]\n", LONG_MIN);
	TEST("[%%+1d] : [%+1d]\n", LONG_MAX);

	TEST("[%%+5d] : [%+5d]\n", 0);
	TEST("[%%+5d] : [%+5d]\n", -1);
	TEST("[%%+5d] : [%+5d]\n", 4321);
	TEST("[%%+5d] : [%+5d]\n", 12345);
	TEST("[%%+5d] : [%+5d]\n", 9876);
	TEST("[%%+5d] : [%+5d]\n", INT_MIN);
	TEST("[%%+5d] : [%+5d]\n", INT_MAX);
	TEST("[%%+5d] : [%+5d]\n", LONG_MIN);
	TEST("[%%+5d] : [%+5d]\n", LONG_MAX);

	TEST("[%%+10d] : [%+10d]\n", 0);
	TEST("[%%+10d] : [%+10d]\n", -1);
	TEST("[%%+10d] : [%+10d]\n", 4321);
	TEST("[%%+10d] : [%+10d]\n", 12345);
	TEST("[%%+10d] : [%+10d]\n", 9876);
	TEST("[%%+10d] : [%+10d]\n", INT_MIN);
	TEST("[%%+10d] : [%+10d]\n", INT_MAX);
	TEST("[%%+10d] : [%+10d]\n", LONG_MIN);
	TEST("[%%+10d] : [%+10d]\n", LONG_MAX);
	printf("-------- d --------\n");

	// i
	printf("-------- i --------\n");
	TEST("[%%+i] : [%+i]\n", 0);
	TEST("[%%+i] : [%+i]\n", -1);
	TEST("[%%+i] : [%+i]\n", 4321);
	TEST("[%%+i] : [%+i]\n", 12345);
	TEST("[%%+i] : [%+i]\n", 9876);
	TEST("[%%+i] : [%+i]\n", INT_MIN);
	TEST("[%%+i] : [%+i]\n", INT_MAX);
	TEST("[%%+i] : [%+i]\n", LONG_MIN);
	TEST("[%%+i] : [%+i]\n", LONG_MAX);

	TEST("[%%+1i] : [%+1i]\n", 0);
	TEST("[%%+1i] : [%+1i]\n", -1);
	TEST("[%%+1i] : [%+1i]\n", 4321);
	TEST("[%%+1i] : [%+1i]\n", 12345);
	TEST("[%%+1i] : [%+1i]\n", 9876);
	TEST("[%%+1i] : [%+1i]\n", INT_MIN);
	TEST("[%%+1i] : [%+1i]\n", INT_MAX);
	TEST("[%%+1i] : [%+1i]\n", LONG_MIN);
	TEST("[%%+1i] : [%+1i]\n", LONG_MAX);

	TEST("[%%+5i] : [%+5i]\n", 0);
	TEST("[%%+5i] : [%+5i]\n", -1);
	TEST("[%%+5i] : [%+5i]\n", 4321);
	TEST("[%%+5i] : [%+5i]\n", 12345);
	TEST("[%%+5i] : [%+5i]\n", 9876);
	TEST("[%%+5i] : [%+5i]\n", INT_MIN);
	TEST("[%%+5i] : [%+5i]\n", INT_MAX);
	TEST("[%%+5i] : [%+5i]\n", LONG_MIN);
	TEST("[%%+5i] : [%+5i]\n", LONG_MAX);

	TEST("[%%+10i] : [%+10i]\n", 0);
	TEST("[%%+10i] : [%+10i]\n", -1);
	TEST("[%%+10i] : [%+10i]\n", 4321);
	TEST("[%%+10i] : [%+10i]\n", 12345);
	TEST("[%%+10i] : [%+10i]\n", 9876);
	TEST("[%%+10i] : [%+10i]\n", INT_MIN);
	TEST("[%%+10i] : [%+10i]\n", INT_MAX);
	TEST("[%%+10i] : [%+10i]\n", LONG_MIN);
	TEST("[%%+10i] : [%+10i]\n", LONG_MAX);
	printf("-------- i --------\n");

	// u
	printf("-------- u --------\n");
	TEST("[%%+u] : [%+u]\n", 0);
	TEST("[%%+u] : [%+u]\n", -1);
	TEST("[%%+u] : [%+u]\n", 4321);
	TEST("[%%+u] : [%+u]\n", 12345);
	TEST("[%%+u] : [%+u]\n", 9876);
	TEST("[%%+u] : [%+u]\n", INT_MIN);
	TEST("[%%+u] : [%+u]\n", INT_MAX);
	TEST("[%%+u] : [%+u]\n", LONG_MIN);
	TEST("[%%+u] : [%+u]\n", LONG_MAX);

	TEST("[%%+1u] : [%+1u]\n", 0);
	TEST("[%%+1u] : [%+1u]\n", -1);
	TEST("[%%+1u] : [%+1u]\n", 4321);
	TEST("[%%+1u] : [%+1u]\n", 12345);
	TEST("[%%+1u] : [%+1u]\n", 9876);
	TEST("[%%+1u] : [%+1u]\n", INT_MIN);
	TEST("[%%+1u] : [%+1u]\n", INT_MAX);
	TEST("[%%+1u] : [%+1u]\n", LONG_MIN);
	TEST("[%%+1u] : [%+1u]\n", LONG_MAX);

	TEST("[%%+5u] : [%+5u]\n", 0);
	TEST("[%%+5u] : [%+5u]\n", -1);
	TEST("[%%+5u] : [%+5u]\n", 4321);
	TEST("[%%+5u] : [%+5u]\n", 12345);
	TEST("[%%+5u] : [%+5u]\n", 9876);
	TEST("[%%+5u] : [%+5u]\n", INT_MIN);
	TEST("[%%+5u] : [%+5u]\n", INT_MAX);
	TEST("[%%+5u] : [%+5u]\n", LONG_MIN);
	TEST("[%%+5u] : [%+5u]\n", LONG_MAX);

	TEST("[%%+10u] : [%+10u]\n", 0);
	TEST("[%%+10u] : [%+10u]\n", -1);
	TEST("[%%+10u] : [%+10u]\n", 4321);
	TEST("[%%+10u] : [%+10u]\n", 12345);
	TEST("[%%+10u] : [%+10u]\n", 9876);
	TEST("[%%+10u] : [%+10u]\n", INT_MIN);
	TEST("[%%+10u] : [%+10u]\n", INT_MAX);
	TEST("[%%+10u] : [%+10u]\n", LONG_MIN);
	TEST("[%%+10u] : [%+10u]\n", LONG_MAX);
	printf("-------- u --------\n");

	printf("++++++++++++++++++++\n");
	#endif

	// minus
	#ifdef MINUS
	printf("-------MINUS-------\n");
	printf("-------- c --------\n");
	printf("-------- c --------\n");
	// s
	printf("-------- s --------\n");
	TEST("[%%-s] : [%-s]\n", "");
	TEST("[%%-s] : [%-s]\n", NULL);
	TEST("[%%-s] : [%-s]\n", "abcd");
	TEST("[%%-s] : [%-s]\n", "01234567890123456");
	TEST("[%%-s] : [%-s]\n", "9876");
	TEST("[%%-s] : [%-s]\n", "-1234");
	TEST("[%%-s] : [%-s]\n", "f");

	TEST("[%%-1s] : [%-1s]\n", "");
	TEST("[%%-1s] : [%-1s]\n", NULL);
	TEST("[%%-1s] : [%-1s]\n", "abcd");
	TEST("[%%-1s] : [%-1s]\n", "01234567890123456");
	TEST("[%%-1s] : [%-1s]\n", "9876");
	TEST("[%%-1s] : [%-1s]\n", "-1234");
	TEST("[%%-1s] : [%-1s]\n", "f");

	TEST("[%%-5s] : [%-5s]\n", "");
	TEST("[%%-5s] : [%-5s]\n", NULL);
	TEST("[%%-5s] : [%-5s]\n", "abcd");
	TEST("[%%-5s] : [%-5s]\n", "01234567890123456");
	TEST("[%%-5s] : [%-5s]\n", "9876");
	TEST("[%%-5s] : [%-5s]\n", "-1234");
	TEST("[%%-5s] : [%-5s]\n", "f");

	TEST("[%%-10s] : [%-10s]\n", "");
	TEST("[%%-10s] : [%-10s]\n", NULL);
	TEST("[%%-10s] : [%-10s]\n", "abcd");
	TEST("[%%-10s] : [%-10s]\n", "01234567890123456");
	TEST("[%%-10s] : [%-10s]\n", "9876");
	TEST("[%%-10s] : [%-10s]\n", "-1234");
	TEST("[%%-10s] : [%-10s]\n", "f");
	printf("-------- s --------\n");

	// p
	printf("-------- p --------\n");
	TEST("[%%-p] : [%-p]\n", 0);
	TEST("[%%-p] : [%-p]\n", NULL);
	TEST("[%%-p] : [%-p]\n", -1);
	TEST("[%%-p] : [%-p]\n", 12345);
	TEST("[%%-p] : [%-p]\n", 9876);
	TEST("[%%-p] : [%-p]\n", -1234);
	TEST("[%%-p] : [%-p]\n", (void *)1);

	TEST("[%%-1p] : [%-1p]\n", 0);
	TEST("[%%-1p] : [%-1p]\n", NULL);
	TEST("[%%-1p] : [%-1p]\n", -1);
	TEST("[%%-1p] : [%-1p]\n", 12345);
	TEST("[%%-1p] : [%-1p]\n", 9876);
	TEST("[%%-1p] : [%-1p]\n", -1234);
	TEST("[%%-1p] : [%-1p]\n", (void *)1);

	TEST("[%%-5p] : [%-5p]\n", 0);
	TEST("[%%-5p] : [%-5p]\n", NULL);
	TEST("[%%-5p] : [%-5p]\n", -1);
	TEST("[%%-5p] : [%-5p]\n", 12345);
	TEST("[%%-5p] : [%-5p]\n", 9876);
	TEST("[%%-5p] : [%-5p]\n", -1234);
	TEST("[%%-5p] : [%-5p]\n", (void *)1);

	TEST("[%%-10p] : [%-10p]\n", 0);
	TEST("[%%-10p] : [%-10p]\n", NULL);
	TEST("[%%-10p] : [%-10p]\n", -1);
	TEST("[%%-10p] : [%-10p]\n", 12345);
	TEST("[%%-10p] : [%-10p]\n", 9876);
	TEST("[%%-10p] : [%-10p]\n", -1234);
	TEST("[%%-10p] : [%-10p]\n", (void *)1);
	printf("-------- p --------\n");

	// d
	printf("-------- d --------\n");
	TEST("[%%-d] : [%-d]\n", 0);
	TEST("[%%-d] : [%-d]\n", -1);
	TEST("[%%-d] : [%-d]\n", 4321);
	TEST("[%%-d] : [%-d]\n", 12345);
	TEST("[%%-d] : [%-d]\n", 9876);
	TEST("[%%-d] : [%-d]\n", INT_MIN);
	TEST("[%%-d] : [%-d]\n", INT_MAX);
	TEST("[%%-d] : [%-d]\n", LONG_MIN);
	TEST("[%%-d] : [%-d]\n", LONG_MAX);

	TEST("[%%-1d] : [%-1d]\n", 0);
	TEST("[%%-1d] : [%-1d]\n", -1);
	TEST("[%%-1d] : [%-1d]\n", 4321);
	TEST("[%%-1d] : [%-1d]\n", 12345);
	TEST("[%%-1d] : [%-1d]\n", 9876);
	TEST("[%%-1d] : [%-1d]\n", INT_MIN);
	TEST("[%%-1d] : [%-1d]\n", INT_MAX);
	TEST("[%%-1d] : [%-1d]\n", LONG_MIN);
	TEST("[%%-1d] : [%-1d]\n", LONG_MAX);

	TEST("[%%-5d] : [%-5d]\n", 0);
	TEST("[%%-5d] : [%-5d]\n", -1);
	TEST("[%%-5d] : [%-5d]\n", 4321);
	TEST("[%%-5d] : [%-5d]\n", 12345);
	TEST("[%%-5d] : [%-5d]\n", 9876);
	TEST("[%%-5d] : [%-5d]\n", INT_MIN);
	TEST("[%%-5d] : [%-5d]\n", INT_MAX);
	TEST("[%%-5d] : [%-5d]\n", LONG_MIN);
	TEST("[%%-5d] : [%-5d]\n", LONG_MAX);

	TEST("[%%-10d] : [%-10d]\n", 0);
	TEST("[%%-10d] : [%-10d]\n", -1);
	TEST("[%%-10d] : [%-10d]\n", 4321);
	TEST("[%%-10d] : [%-10d]\n", 12345);
	TEST("[%%-10d] : [%-10d]\n", 9876);
	TEST("[%%-10d] : [%-10d]\n", INT_MIN);
	TEST("[%%-10d] : [%-10d]\n", INT_MAX);
	TEST("[%%-10d] : [%-10d]\n", LONG_MIN);
	TEST("[%%-10d] : [%-10d]\n", LONG_MAX);
	printf("-------- d --------\n");

	// i
	printf("-------- i --------\n");
	TEST("[%%-i] : [%-i]\n", 0);
	TEST("[%%-i] : [%-i]\n", -1);
	TEST("[%%-i] : [%-i]\n", 4321);
	TEST("[%%-i] : [%-i]\n", 12345);
	TEST("[%%-i] : [%-i]\n", 9876);
	TEST("[%%-i] : [%-i]\n", INT_MIN);
	TEST("[%%-i] : [%-i]\n", INT_MAX);
	TEST("[%%-i] : [%-i]\n", LONG_MIN);
	TEST("[%%-i] : [%-i]\n", LONG_MAX);

	TEST("[%%-1i] : [%-1i]\n", 0);
	TEST("[%%-1i] : [%-1i]\n", -1);
	TEST("[%%-1i] : [%-1i]\n", 4321);
	TEST("[%%-1i] : [%-1i]\n", 12345);
	TEST("[%%-1i] : [%-1i]\n", 9876);
	TEST("[%%-1i] : [%-1i]\n", INT_MIN);
	TEST("[%%-1i] : [%-1i]\n", INT_MAX);
	TEST("[%%-1i] : [%-1i]\n", LONG_MIN);
	TEST("[%%-1i] : [%-1i]\n", LONG_MAX);

	TEST("[%%-5i] : [%-5i]\n", 0);
	TEST("[%%-5i] : [%-5i]\n", -1);
	TEST("[%%-5i] : [%-5i]\n", 4321);
	TEST("[%%-5i] : [%-5i]\n", 12345);
	TEST("[%%-5i] : [%-5i]\n", 9876);
	TEST("[%%-5i] : [%-5i]\n", INT_MIN);
	TEST("[%%-5i] : [%-5i]\n", INT_MAX);
	TEST("[%%-5i] : [%-5i]\n", LONG_MIN);
	TEST("[%%-5i] : [%-5i]\n", LONG_MAX);

	TEST("[%%-10i] : [%-10i]\n", 0);
	TEST("[%%-10i] : [%-10i]\n", -1);
	TEST("[%%-10i] : [%-10i]\n", 4321);
	TEST("[%%-10i] : [%-10i]\n", 12345);
	TEST("[%%-10i] : [%-10i]\n", 9876);
	TEST("[%%-10i] : [%-10i]\n", INT_MIN);
	TEST("[%%-10i] : [%-10i]\n", INT_MAX);
	TEST("[%%-10i] : [%-10i]\n", LONG_MIN);
	TEST("[%%-10i] : [%-10i]\n", LONG_MAX);
	printf("-------- i --------\n");

	// u
	printf("-------- u --------\n");
	TEST("[%%-u] : [%-u]\n", 0);
	TEST("[%%-u] : [%-u]\n", -1);
	TEST("[%%-u] : [%-u]\n", 4321);
	TEST("[%%-u] : [%-u]\n", 12345);
	TEST("[%%-u] : [%-u]\n", 9876);
	TEST("[%%-u] : [%-u]\n", INT_MIN);
	TEST("[%%-u] : [%-u]\n", INT_MAX);
	TEST("[%%-u] : [%-u]\n", LONG_MIN);
	TEST("[%%-u] : [%-u]\n", LONG_MAX);

	TEST("[%%-1u] : [%-1u]\n", 0);
	TEST("[%%-1u] : [%-1u]\n", -1);
	TEST("[%%-1u] : [%-1u]\n", 4321);
	TEST("[%%-1u] : [%-1u]\n", 12345);
	TEST("[%%-1u] : [%-1u]\n", 9876);
	TEST("[%%-1u] : [%-1u]\n", INT_MIN);
	TEST("[%%-1u] : [%-1u]\n", INT_MAX);
	TEST("[%%-1u] : [%-1u]\n", LONG_MIN);
	TEST("[%%-1u] : [%-1u]\n", LONG_MAX);

	TEST("[%%-5u] : [%-5u]\n", 0);
	TEST("[%%-5u] : [%-5u]\n", -1);
	TEST("[%%-5u] : [%-5u]\n", 4321);
	TEST("[%%-5u] : [%-5u]\n", 12345);
	TEST("[%%-5u] : [%-5u]\n", 9876);
	TEST("[%%-5u] : [%-5u]\n", INT_MIN);
	TEST("[%%-5u] : [%-5u]\n", INT_MAX);
	TEST("[%%-5u] : [%-5u]\n", LONG_MIN);
	TEST("[%%-5u] : [%-5u]\n", LONG_MAX);

	TEST("[%%-10u] : [%-10u]\n", 0);
	TEST("[%%-10u] : [%-10u]\n", -1);
	TEST("[%%-10u] : [%-10u]\n", 4321);
	TEST("[%%-10u] : [%-10u]\n", 12345);
	TEST("[%%-10u] : [%-10u]\n", 9876);
	TEST("[%%-10u] : [%-10u]\n", INT_MIN);
	TEST("[%%-10u] : [%-10u]\n", INT_MAX);
	TEST("[%%-10u] : [%-10u]\n", LONG_MIN);
	TEST("[%%-10u] : [%-10u]\n", LONG_MAX);
	printf("-------- u --------\n");

	// x
	printf("-------- x --------\n");
	printf("-------- x --------\n");

	// X
	printf("-------- X --------\n");
	printf("-------- X --------\n");
	printf("-------------------\n");
	#endif

	#ifdef ALL_MIX
	TEST("[%04c][%10.5s][%5.5p][%+10.9d][%+u][%#12.1x][% X][%%]\n", 'a', "hello", 100000, INT_MAX, -1, -1, -900);
	#endif

	#ifdef COMPLEX
	// If a precision is given with a numeric conversion (d, i, o, u, i, x, and X), the 0 flag is ignored.
	// d
	printf("-------- d --------\n");
	TEST("[%%00.0d] : [%00.0d]\n", 0);
	TEST("[%%+.0d] : [%+.0d]\n", 0);
	TEST("[%%00.1d] : [%00.1d]\n", -1);
	TEST("[%%00.2d] : [%00.2d]\n", 123);
	TEST("[%%00.3d] : [%00.3d]\n", -9032);
	TEST("[%%00.4d] : [%00.4d]\n", INT_MAX);
	TEST("[%%01.0d] : [%01.0d]\n", INT_MIN);
	TEST("[%%02.1d] : [%02.1d]\n", LONG_MAX);
	TEST("[%%03.2d] : [%03.2d]\n", LONG_MIN);
	TEST("[%%04.3d] : [%04.3d]\n", ULONG_MAX);
	TEST("[%%05.4d] : [%05.4d]\n", -100);
	printf("-------- d --------\n");

	// i
	printf("-------- i --------\n");
	TEST("[%%00.0i] : [%00.0i]\n", 0);
	TEST("[%%00.1i] : [%00.1i]\n", -1);
	TEST("[%%00.2i] : [%00.2i]\n", 123);
	TEST("[%%00.3i] : [%00.3i]\n", -9032);
	TEST("[%%00.4i] : [%00.4i]\n", INT_MAX);
	TEST("[%%01.0i] : [%01.0i]\n", INT_MIN);
	TEST("[%%02.1i] : [%02.1i]\n", LONG_MAX);
	TEST("[%%03.2i] : [%03.2i]\n", LONG_MIN);
	TEST("[%%04.3i] : [%04.3i]\n", ULONG_MAX);
	TEST("[%%05.4i] : [%05.4i]\n", -100);
	printf("-------- i --------\n");

	// u
	printf("-------- u --------\n");
	TEST("[%%00.0u] : [%00.0u]\n", 0);
	TEST("[%%00.1u] : [%00.1u]\n", 0);
	TEST("[%%00.2u] : [%00.2u]\n", 0);
	TEST("[%%00.3u] : [%00.3u]\n", 0);
	TEST("[%%00.4u] : [%00.4u]\n", 0);
	TEST("[%%01.0u] : [%01.0u]\n", 0);
	TEST("[%%02.1u] : [%02.1u]\n", 0);
	TEST("[%%03.2u] : [%03.2u]\n", 0);
	TEST("[%%04.3u] : [%04.3u]\n", 0);
	TEST("[%%05.4u] : [%05.4u]\n", 0);

	TEST("[%%00.0u] : [%00.0u]\n", 123);
	TEST("[%%00.1u] : [%00.1u]\n", 123);
	TEST("[%%00.2u] : [%00.2u]\n", 123);
	TEST("[%%00.3u] : [%00.3u]\n", 123);
	TEST("[%%00.4u] : [%00.4u]\n", 123);
	TEST("[%%01.0u] : [%01.0u]\n", 123);
	TEST("[%%02.1u] : [%02.1u]\n", 123);
	TEST("[%%03.2u] : [%03.2u]\n", 123);
	TEST("[%%04.3u] : [%04.3u]\n", 123);
	TEST("[%%05.4u] : [%05.4u]\n", 123);
	printf("-------- u --------\n");

	// x
	printf("-------- x --------\n");
	TEST("[%%00.0x] : [%00.0x]\n", 0);
	TEST("[%%00.1x] : [%00.1x]\n", 0);
	TEST("[%%00.2x] : [%00.2x]\n", 0);
	TEST("[%%00.3x] : [%00.3x]\n", 0);
	TEST("[%%00.4x] : [%00.4x]\n", 0);
	TEST("[%%01.0x] : [%01.0x]\n", 0);
	TEST("[%%02.1x] : [%02.1x]\n", 0);
	TEST("[%%03.2x] : [%03.2x]\n", 0);
	TEST("[%%04.3x] : [%04.3x]\n", 0);
	TEST("[%%05.4x] : [%05.4x]\n", 0);

	TEST("[%%00.0x] : [%00.0x]\n", 123);
	TEST("[%%00.1x] : [%00.1x]\n", 123);
	TEST("[%%00.2x] : [%00.2x]\n", 123);
	TEST("[%%00.3x] : [%00.3x]\n", 123);
	TEST("[%%00.4x] : [%00.4x]\n", 123);
	TEST("[%%01.0x] : [%01.0x]\n", 123);
	TEST("[%%02.1x] : [%02.1x]\n", 123);
	TEST("[%%03.2x] : [%03.2x]\n", 123);
	TEST("[%%04.3x] : [%04.3x]\n", 123);
	TEST("[%%05.4x] : [%05.4x]\n", 123);
	printf("-------- x --------\n");

	// X
	printf("-------- X --------\n");
	TEST("[%%00.0X] : [%00.0X]\n", 0);
	TEST("[%%00.1X] : [%00.1X]\n", 0);
	TEST("[%%00.2X] : [%00.2X]\n", 0);
	TEST("[%%00.3X] : [%00.3X]\n", 0);
	TEST("[%%00.4X] : [%00.4X]\n", 0);
	TEST("[%%01.0X] : [%01.0X]\n", 0);
	TEST("[%%02.1X] : [%02.1X]\n", 0);
	TEST("[%%03.2X] : [%03.2X]\n", 0);
	TEST("[%%04.3X] : [%04.3X]\n", 0);
	TEST("[%%05.4X] : [%05.4X]\n", 0);

	TEST("[%%00.0X] : [%00.0X]\n", 123);
	TEST("[%%00.1X] : [%00.1X]\n", 123);
	TEST("[%%00.2X] : [%00.2X]\n", 123);
	TEST("[%%00.3X] : [%00.3X]\n", 123);
	TEST("[%%00.4X] : [%00.4X]\n", 123);
	TEST("[%%01.0X] : [%01.0X]\n", 123);
	TEST("[%%02.1X] : [%02.1X]\n", 123);
	TEST("[%%03.2X] : [%03.2X]\n", 123);
	TEST("[%%04.3X] : [%04.3X]\n", 123);
	TEST("[%%05.4X] : [%05.4X]\n", 123);
	printf("-------- X --------\n");

	// p
	printf("-------- p --------\n");
	TEST("[%%00.0p] : [%00.0p]\n", 0);
	TEST("[%%00.1p] : [%00.1p]\n", 0);
	TEST("[%%00.2p] : [%00.2p]\n", 0);
	TEST("[%%00.3p] : [%00.3p]\n", 0);
	TEST("[%%00.4p] : [%00.4p]\n", 0);
	TEST("[%%01.0p] : [%01.0p]\n", 0);
	TEST("[%%02.1p] : [%02.1p]\n", 0);
	TEST("[%%03.2p] : [%03.2p]\n", 0);
	TEST("[%%04.3p] : [%04.3p]\n", 0);
	TEST("[%%05.4p] : [%05.4p]\n", 0);

	TEST("[%%00.0p] : [%00.0p]\n", 123);
	TEST("[%%00.1p] : [%00.1p]\n", 123);
	TEST("[%%00.2p] : [%00.2p]\n", 123);
	TEST("[%%00.3p] : [%00.3p]\n", 123);
	TEST("[%%00.4p] : [%00.4p]\n", 123);
	TEST("[%%01.0p] : [%01.0p]\n", 123);
	TEST("[%%02.1p] : [%02.1p]\n", 123);
	TEST("[%%03.2p] : [%03.2p]\n", 123);
	TEST("[%%04.3p] : [%04.3p]\n", 123);
	TEST("[%%05.4p] : [%05.4p]\n", 123);

	TEST("[%%010.5p] : [%00.0p]\n", 123);
	TEST("[%%010.6p] : [%00.1p]\n", 123);
	TEST("[%%010.7p] : [%00.2p]\n", 123);
	TEST("[%%010.8p] : [%00.3p]\n", 123);
	TEST("[%%010.9p] : [%00.4p]\n", 123);
	TEST("[%%011.5p] : [%01.0p]\n", 123);
	TEST("[%%012.6p] : [%02.1p]\n", 123);
	TEST("[%%013.7p] : [%03.2p]\n", 123);
	TEST("[%%014.8p] : [%04.3p]\n", 123);
	TEST("[%%015.9p] : [%05.4p]\n", 123);
	printf("-------- p --------\n");

	// A - overrides a 0 if both are given.
	printf("-------- c --------\n");
	TEST("[%%0-0.0c] : [%0-0.0c]\n", 0);
	TEST("[%%0-1.0c] : [%0-1.0c]\n", 0);
	TEST("[%%0-2.0c] : [%0-2.0c]\n", 0);
	TEST("[%%0-3.0c] : [%0-3.0c]\n", 0);
	TEST("[%%0-4.0c] : [%0-4.0c]\n", 0);

	TEST("[%%0-0.1c] : [%0-0.1c]\n", 0);
	TEST("[%%0-1.2c] : [%0-1.2c]\n", 0);
	TEST("[%%0-2.3c] : [%0-2.3c]\n", 0);
	TEST("[%%0-3.4c] : [%0-3.4c]\n", 0);
	TEST("[%%0-4.5c] : [%0-4.5c]\n", 0);

	TEST("[%%0-0.0c] : [%0-0.0c]\n", 'a');
	TEST("[%%0-1.0c] : [%0-1.0c]\n", '=');
	TEST("[%%0-2.0c] : [%0-2.0c]\n", '?');
	TEST("[%%0-3.0c] : [%0-3.0c]\n", '\\');
	TEST("[%%0-4.0c] : [%0-4.0c]\n", '{');

	TEST("[%%0-0.1c] : [%0-0.1c]\n", '2');
	TEST("[%%0-1.2c] : [%0-1.2c]\n", '#');
	TEST("[%%0-2.3c] : [%0-2.3c]\n", '(');
	TEST("[%%0-3.4c] : [%0-3.4c]\n", '\"');
	TEST("[%%0-4.5c] : [%0-4.5c]\n", '&');
	printf("-------- c --------\n");

	printf("-------- s --------\n");
	TEST("[%%0-0.0s] : [%0-0.0s]\n", NULL);
	TEST("[%%0-1.0s] : [%0-1.0s]\n", NULL);
	TEST("[%%0-2.0s] : [%0-2.0s]\n", NULL);
	TEST("[%%0-3.0s] : [%0-3.0s]\n", NULL);
	TEST("[%%0-4.0s] : [%0-4.0s]\n", NULL);

	TEST("[%%0-0.1s] : [%0-0.1s]\n", NULL);
	TEST("[%%0-1.2s] : [%0-1.2s]\n", NULL);
	TEST("[%%0-2.3s] : [%0-2.3s]\n", NULL);
	TEST("[%%0-3.4s] : [%0-3.4s]\n", NULL);
	TEST("[%%0-4.5s] : [%0-4.5s]\n", NULL);

	TEST("[%%0-0.0s] : [%0-0.0s]\n", "");
	TEST("[%%0-1.0s] : [%0-1.0s]\n", "");
	TEST("[%%0-2.0s] : [%0-2.0s]\n", "");
	TEST("[%%0-3.0s] : [%0-3.0s]\n", "");
	TEST("[%%0-4.0s] : [%0-4.0s]\n", "");

	TEST("[%%0-0.1s] : [%0-0.1s]\n", "");
	TEST("[%%0-1.2s] : [%0-1.2s]\n", "");
	TEST("[%%0-2.3s] : [%0-2.3s]\n", "");
	TEST("[%%0-3.4s] : [%0-3.4s]\n", "");
	TEST("[%%0-4.5s] : [%0-4.5s]\n", "");

	TEST("[%%0-0.0s] : [%0-0.0s]\n", "abc");
	TEST("[%%0-1.0s] : [%0-1.0s]\n", "abc");
	TEST("[%%0-2.0s] : [%0-2.0s]\n", "abc");
	TEST("[%%0-3.0s] : [%0-3.0s]\n", "abc");
	TEST("[%%0-4.0s] : [%0-4.0s]\n", "abc");

	TEST("[%%0-0.1s] : [%0-0.1s]\n", "abc");
	TEST("[%%0-1.2s] : [%0-1.2s]\n", "abc");
	TEST("[%%0-2.3s] : [%0-2.3s]\n", "abc");
	TEST("[%%0-3.4s] : [%0-3.4s]\n", "abc");
	TEST("[%%0-4.5s] : [%0-4.5s]\n", "abc");
	printf("-------- s --------\n");

	printf("-------- p --------\n");
	TEST("[%%0-0.0p] : [%0-0.0p]\n", NULL);
	TEST("[%%0-1.0p] : [%0-1.0p]\n", NULL);
	TEST("[%%0-2.0p] : [%0-2.0p]\n", NULL);
	TEST("[%%0-3.0p] : [%0-3.0p]\n", NULL);
	TEST("[%%0-4.0p] : [%0-4.0p]\n", NULL);

	TEST("[%%0-0.1p] : [%0-0.1p]\n", NULL);
	TEST("[%%0-1.2p] : [%0-1.2p]\n", NULL);
	TEST("[%%0-2.3p] : [%0-2.3p]\n", NULL);
	TEST("[%%0-3.4p] : [%0-3.4p]\n", NULL);
	TEST("[%%0-4.5p] : [%0-4.5p]\n", NULL);

	TEST("[%%0-0.0p] : [%0-0.0p]\n", 0);
	TEST("[%%0-1.0p] : [%0-1.0p]\n", 0);
	TEST("[%%0-2.0p] : [%0-2.0p]\n", 0);
	TEST("[%%0-3.0p] : [%0-3.0p]\n", 0);
	TEST("[%%0-4.0p] : [%0-4.0p]\n", 0);

	TEST("[%%0-0.1p] : [%0-0.1p]\n", 0);
	TEST("[%%0-1.2p] : [%0-1.2p]\n", 0);
	TEST("[%%0-2.3p] : [%0-2.3p]\n", 0);
	TEST("[%%0-3.4p] : [%0-3.4p]\n", 0);
	TEST("[%%0-4.5p] : [%0-4.5p]\n", 0);

	TEST("[%%0-0.0p] : [%0-0.0p]\n", 1);
	TEST("[%%0-1.0p] : [%0-1.0p]\n", 10);
	TEST("[%%0-2.0p] : [%0-2.0p]\n", -1);
	TEST("[%%0-3.0p] : [%0-3.0p]\n", 23);
	TEST("[%%0-4.0p] : [%0-4.0p]\n", INT_MIN);

	TEST("[%%0-0.1p] : [%0-0.1p]\n", 123456);
	TEST("[%%0-1.2p] : [%0-1.2p]\n", 2);
	TEST("[%%0-2.3p] : [%0-2.3p]\n", -100);
	TEST("[%%0-3.4p] : [%0-3.4p]\n", -292);
	TEST("[%%0-4.5p] : [%0-4.5p]\n", 19);
	printf("-------- p --------\n");

	// d
	printf("-------- d --------\n");
	TEST("[%% -10.0d] : [% -10.0d]\n", 0);
	TEST("[%% -10.1d] : [% -10.1d]\n", -1);
	TEST("[%% -10.2d] : [% -10.2d]\n", 123);
	TEST("[%% -10.3d] : [% -10.3d]\n", -9032);
	TEST("[%% -10.4d] : [% -10.4d]\n", INT_MAX);
	TEST("[%%- 10.0d] : [%- 10.0d]\n", INT_MIN);
	TEST("[%%- 10.1d] : [%- 10.1d]\n", LONG_MAX);
	TEST("[%%- 10.2d] : [%- 10.2d]\n", LONG_MIN);
	TEST("[%%- 10.3d] : [%- 10.3d]\n", ULONG_MAX);
	TEST("[%%- 10.4d] : [%- 10.4d]\n", -100);
	printf("-------- d --------\n");

	// A + overrides a space if both are used.
	#endif

	#ifdef BIG
	// d
	printf("-------- d --------\n");
	TEST("%2147483647d\n", 10);\
	TEST("s%2147483647d\n", 10);
	TEST("%2147483647ds\n", 10);
	TEST("s%2147483646d\n", 10);
	TEST("%2147483646ds\n", 10);
	printf("-------- d --------\n");
	#endif
	// sleep(30);
	// system("leaks ./a.out");
}
