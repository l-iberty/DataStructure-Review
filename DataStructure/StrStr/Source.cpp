#include <stdio.h>

int strstr(
	_In_ char *s1, 
	_In_ char *s2,
	_Out_ int *len2)
{
	int i = 0, j = 0;

	while (s1[i] && s2[j])
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (s2[j] == 0)
	{
		*len2 = j;
		return (i - j);
	}
	else
		return (-1);
}

int main()
{
	char *s1 = "ababcabcacbab";
	char *s2 = "abcac";
	int len2;
	int i = strstr(s1, s2, &len2);
	printf("%d\n", i);
	if (i != -1)
	{
		while (len2-- > 0)
			printf("%c", s1[i++]);
	}
	printf("%\n");
}