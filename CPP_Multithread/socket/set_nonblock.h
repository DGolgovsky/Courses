#pragma once
/*
 * blocking completed only after reading all data
 */
int set_nonblock(int fd)
{
	int flags;
	#if defined(O_NONBLOCK)
		if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
			flags = 0;
		return fcntl(fd, F_SETFL, flags|O_NONBLOCK);
	#else
		flags = 1;
		return ioctl(fd, FIOBIO, &flags);
	#endif
}

