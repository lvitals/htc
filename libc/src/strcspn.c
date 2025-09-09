/*
 * strcspn - find length of initial segment of s1 not containing
 * any characters from s2
 */

typedef unsigned int	size_t;

size_t
strcspn(s1, s2)
	char *s1;
	char *s2;
{
	char *p, *q;

	for (p = s1; *p; p++) {
		for (q = s2; *q; q++) {
			if (*p == *q)
				goto done;
		}
	}
done:
	return (p - s1);
}
