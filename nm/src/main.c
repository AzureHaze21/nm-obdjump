/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "nm.h"

int main(int argc, char **argv)
{
		int fd;
		int i = 0;
		struct stat	st;

		if (argc < 2)
				return (0);
		while (++i < argc)
		{
				fd = open(argv[i], O_RDONLY);
				if (fd < 0 || (fstat(fd, &st) != 0))
				{
						printf("nm: '%s': No such file\n",
							   argv[i]);
				}
				else
				{
						g_input_file = argv[i];
						read_header(fd, st.st_size);
						close(fd);
				}
		}
		return (0);
}
