#include <assert.h>	/* assert */
#include <string.h>	/* memcpy, strcpy, strncat, strndup */

/* "Checked" memcpy */
void *__memcpy_chk(void *dest, const void *src, size_t len, size_t destlen)
{
	assert(dest != NULL);
	assert(src != NULL);
	assert(len <= destlen);
	if(src < dest)
	{
		assert(!(src + len >= dest));
	} else {
		assert(!(dest + len >= src));
	}
	return memcpy(dest, src, len);
}

/* "Checked" strncat */
char *__strncat_chk(char *dest, const char *src, size_t n, size_t destlen)
{
	assert(dest != NULL);
	assert(src != NULL);
	assert(n <= destlen);

	return strncat(dest, src, n);
}

/* "Checked" strcpy */
char *__strcpy_chk(char *dest, const char *src, size_t destlen)
{
	assert(dest != NULL);
	assert(src != NULL);
	assert(strlen(src) < destlen);

	return strcpy(dest, src);
}

/* Literally a useless __ alias. */
char *__strndup(const char *str, size_t count)
{
	return strndup(str, count);
}

/* The existance of this method, and the fact it is used in real code, gives
 * me nightmares. */
void *rawmemchr(const void *s, int c)
{
	const unsigned char *haystack = s;
	unsigned char needle = (unsigned char)c;
	while(*haystack++ != needle);
	return (void *)haystack;
}

extern __typeof(rawmemchr) __rawmemchr __attribute__((weak, alias("rawmemchr")));

/* Another useless __ alias */
char *__strtok_r(char *str, const char *delim, char **saveptr)
{
	return strtok_r(str, delim, saveptr);
}

/* The "global" definition of strsep in glibc, used when architecture dependent
 * assembler versions aren't good enough. */
char *__strsep_g(char **stringp, const char *delim)
{
	return strsep(stringp, delim);
}