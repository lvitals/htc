/*
 * strpbrk - find first occurrence of any character from s2 in s1
 */
#define NULL (char *)0

char *
strpbrk(s1, s2)
	char *s1;
	char *s2;
{
	char *p, *q;

	for (p = s1; *p; p++) {
		for (q = s2; *q; q++) {
			if (*p == *q)
				return (p);
		}
	}
	return (NULL);
}
