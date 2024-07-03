#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int	main(void)
{
	errno = 0;
	if (open("yeah.txt", O_RDONLY) < 0)
		printf("%s\n", strerror(errno));
	return (0);
}