/*
 * strspn - find length of initial segment of s1 consisting
 * entirely of characters from s2
 */
typedef unsigned int	size_t;
#define NULL (char *)0

size_t
strspn(s1, s2)
	char *s1;
	char *s2;
{
	char *p, *q;

	for (p = s1; *p; p++) {
		for (q = s2; *q; q++) {
			if (*p == *q)
				break;
		}
		if (!*q)
			break;
	}
	return (p - s1);
}
