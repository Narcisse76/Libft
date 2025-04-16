
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include "libft.h"

void	print_sep(const char *name)
{
	printf("\n========== %s ==========" "\n", name);
}

void	check_str(const char *label, const char *ft, const char *ref)
{
	int match = (!ft && !ref) || (ft && ref && strcmp(ft, ref) == 0);
	printf("%-25s | ft: \"%s\" | std: \"%s\" | match: %s\n",
		label,
		ft ? ft : "(null)",
		ref ? ref : "(null)",
		match ? "✅" : "❌");
}

void	check_int(const char *label, int ft, int ref)
{
	printf("%-25s | ft: %d | std: %d | match: %s\n",
		label, ft, ref, (ft == ref) ? "✅" : "❌");
}

void	check_size(const char *label, size_t ft, size_t ref)
{
	printf("%-25s | ft: %zu | std: %zu | match: %s\n",
		label, ft, ref, (ft == ref) ? "✅" : "❌");
}

void	del_content(void *content)
{
	free(content);
}

void	*dup_wrapper(void *content)
{
	return (ft_strdup((char *)content));
}

void	print_str_fd(void *content)
{
	ft_putendl_fd((char *)content, 1);
}

void	increment_char(unsigned int i, char *c)
{
	(void)i;
	*c = *c + 1;
}

char	add_one_to_char(unsigned int i, char c)
{
	(void)i;
	return (c + 1);
}

void	print_split_result(char **split)
{
	if (!split)
	{
		printf("split returned NULL ❌\n");
		return;
	}
	for (int i = 0; split[i]; i++)
	{
		printf("split[%d] = \"%s\"\n", i, split[i]);
		free(split[i]);
	}
	free(split);
}

void	test_split_case(const char *input, char sep)
{
	if (!input)
	{
		printf("Input: NULL | sep: '%c'\n", sep);
		print_split_result(NULL);
		return;
	}
	printf("Input: \"%s\" | sep: '%c'\n", input, sep);
	char **result = ft_split(input, sep);
	print_split_result(result);
}

int	main(void)
{
	char	buf[20];

	// is* + logic
	print_sep("Logical is* checks");
	check_int("ft_isalpha('3')", !!ft_isalpha('3'), !!isalpha('3'));
	check_int("ft_isdigit('4')", !!ft_isdigit('4'), !!isdigit('4'));
	check_int("ft_isalnum('Z')", !!ft_isalnum('Z'), !!isalnum('Z'));
	check_int("ft_isascii(127)", !!ft_isascii(127), !!isascii(127));
	check_int("ft_isprint(' ')", !!ft_isprint(' '), !!isprint(' '));

	// Standard string/mem
	print_sep("Standard string/mem functions");
	check_size("ft_strlen", ft_strlen("Hello"), strlen("Hello"));
	check_int("ft_atoi", ft_atoi("   -123"), atoi("   -123"));
	check_int("ft_strncmp", ft_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));
	check_str("ft_strchr", ft_strchr("libft", 'f'), strchr("libft", 'f'));
	check_str("ft_strrchr", ft_strrchr("libftft", 'f'), strrchr("libftft", 'f'));

	char *dup1 = ft_strdup("test");
	char *dup2 = strdup("test");
	check_str("ft_strdup", dup1, dup2);
	free(dup1); free(dup2);

	char memset1[10] = "abcdefghi";
	char memset2[10] = "abcdefghi";
	ft_memset(memset1, 'x', 3);
	memset(memset2, 'x', 3);
	check_str("ft_memset", memset1, memset2);

	char bzero1[10] = "abcdefghi";
	char bzero2[10] = "abcdefghi";
	ft_bzero(bzero1, 3);
	memset(bzero2, 0, 3);
	check_str("ft_bzero", bzero1, bzero2);

	char memcpy1[10] = "abcdefghi";
	char memcpy2[10] = "abcdefghi";
	ft_memcpy(memcpy1, "123", 3);
	memcpy(memcpy2, "123", 3);
	check_str("ft_memcpy", memcpy1, memcpy2);

	char memmove1[10] = "abcdefghi";
	char memmove2[10] = "abcdefghi";
	ft_memmove(memmove1 + 2, memmove1, 3);
	memmove(memmove2 + 2, memmove2, 3);
	check_str("ft_memmove", memmove1, memmove2);

	check_int("ft_memcmp", ft_memcmp("abc", "abd", 2), memcmp("abc", "abd", 2));
	check_str("ft_memchr", ft_memchr("hello", 'e', 5), memchr("hello", 'e', 5));

	char slc1[10], slc2[10];
	check_size("ft_strlcpy", ft_strlcpy(slc1, "test", 10), strlcpy(slc2, "test", 10));
	char slcat1[20] = "Hello ", slcat2[20] = "Hello ";
	check_size("ft_strlcat", ft_strlcat(slcat1, "World", 20), strlcat(slcat2, "World", 20));

	check_int("ft_tolower", ft_tolower('A'), tolower('A'));
	check_int("ft_toupper", ft_toupper('a'), toupper('a'));

	// Allocation / Strings
	print_sep("Allocation / strings");
	char *sub = ft_substr("Hello World", 6, 5);
	check_str("ft_substr", sub, "World"); free(sub);

	char *join = ft_strjoin("Hello", "42");
	check_str("ft_strjoin", join, "Hello42"); free(join);

	char *trim = ft_strtrim("..Hello..", ".");
	check_str("ft_strtrim", trim, "Hello"); free(trim);

	char *itoa = ft_itoa(-123);
	check_str("ft_itoa", itoa, "-123"); free(itoa);

	char *map = ft_strmapi("abc", add_one_to_char);
	check_str("ft_strmapi", map, "bcd"); free(map);

	char s[] = "abc";
	ft_striteri(s, increment_char);
	check_str("ft_striteri", s, "bcd");

	// split advanced
	print_sep("Tests avancés de ft_split");
	test_split_case("", ' ');
	test_split_case("abc", ',');
	test_split_case("  je suis  là ", ' ');
	test_split_case("a,,b,c", ',');
	test_split_case(",,,,", ',');
	test_split_case("un deux trois", ' ');
	test_split_case(NULL, ' ');

	// FD output
	print_sep("FD functions (visuel)");
	ft_putchar_fd('A', 1); write(1, "\n", 1);
	ft_putstr_fd("Hello", 1); write(1, "\n", 1);
	ft_putendl_fd("World", 1);
	ft_putnbr_fd(123, 1); write(1, "\n", 1);

	// BONUS: lst
	print_sep("BONUS: ft_lst*");
	t_list *l = ft_lstnew(ft_strdup("node1"));
	ft_lstadd_front(&l, ft_lstnew(ft_strdup("node0")));
	ft_lstadd_back(&l, ft_lstnew(ft_strdup("node2")));
	check_int("ft_lstsize", ft_lstsize(l), 3);
	check_str("ft_lstlast", (char *)ft_lstlast(l)->content, "node2");
	ft_lstiter(l, print_str_fd);
	t_list *mapped = ft_lstmap(l, dup_wrapper, free);
	if (!mapped)
	{
		printf("ft_lstmap failed\n");
		ft_lstclear(&l, free);
		return (1);
	}
	ft_lstiter(mapped, print_str_fd);
	ft_lstclear(&mapped, del_content);
	ft_lstclear(&l, del_content);

	// Extreme edge cases
	print_sep("ft_atoi - overflow tests");
	printf("Input: '2147483648' → ft: %d\n", ft_atoi("2147483648"));
	printf("Input: '-2147483649' → ft: %d\n", ft_atoi("-2147483649"));
	printf("Input: '00000123' → ft: %d\n", ft_atoi("00000123"));

	print_sep("ft_memcpy - NULL and zero bytes");
	void *mem = ft_memcpy(NULL, NULL, 0);
	printf("memcpy(NULL, NULL, 0) returned: %p (✅ if not segfault)\n", mem);

	print_sep("ft_strlcpy - size = 0");
	char dst1[10] = "123456";
	size_t lcpy = ft_strlcpy(dst1, "abc", 0);
	printf("ft_strlcpy result (size=0): %zu, dst1 = \"%s\"\n", lcpy, dst1);

	print_sep("ft_strlcat - size = 0");
	char dst2[10] = "xyz";
	size_t lcat = ft_strlcat(dst2, "abc", 0);
	printf("ft_strlcat result (size=0): %zu, dst2 = \"%s\"\n", lcat, dst2);

	print_sep("ft_calloc - overflow check");
	void *c = ft_calloc(SIZE_MAX, 2);
	printf("ft_calloc(SIZE_MAX, 2) = %s\n", c ? "Allocated ❌" : "NULL ✅");

	print_sep("ft_substr - start > len");
	char *sb = ft_substr("abc", 42, 10);
	printf("ft_substr('abc', 42, 10) = \"%s\"\n", sb);
	free(sb);

	print_sep("ft_split - only separators");
	char **split = ft_split(",,,,", ',');
	if (split && split[0] == NULL)
		printf("split[0] == NULL ✅\n");
	else
		printf("split result invalid ❌\n");
	free(split);

	print_sep("ft_lstmap - NULL return from f()");
	t_list *lst = ft_lstnew(ft_strdup("ok"));
	t_list *mapfail = ft_lstmap(lst, NULL, free);
	printf("ft_lstmap with NULL f() returned: %p\n", (void *)mapfail);
	ft_lstclear(&lst, free);

	return (0);
}
