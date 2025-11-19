#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		*fds;
	char	*line;
	int		i;
	int		round;
	int		active_fds;

	if (argc < 2)
	{
		printf("Usage: %s <file1> <file2> <file3> ...\n", argv[0]);
		printf("Example: %s file1.txt file2.txt file3.txt\n", argv[0]);
		return (1);
	}

	// Alocar array para file descriptors
	fds = malloc(sizeof(int) * (argc - 1));
	if (!fds)
		return (printf("Error: malloc failed\n"), 1);

	// Abrir todos os arquivos
	printf("Opening %d files...\n", argc - 1);
	for (i = 0; i < argc - 1; i++)
	{
		fds[i] = open(argv[i + 1], O_RDONLY);
		if (fds[i] < 0)
		{
			printf("Error: Could not open '%s'\n", argv[i + 1]);
			// Fechar os já abertos
			while (--i >= 0)
				close(fds[i]);
			free(fds);
			return (1);
		}
		printf("  FD%d: %s (fd=%d)\n", i, argv[i + 1], fds[i]);
	}

	printf("\n=== Starting Multiple FD Test ===\n\n");

	round = 1;
	active_fds = argc - 1;
	
	while (active_fds > 0)
	{
		printf("--- Round %d ---\n", round);
		active_fds = 0;

		// Ler de cada file descriptor
		for (i = 0; i < argc - 1; i++)
		{
			if (fds[i] >= 0)  // Se ainda está aberto
			{
				line = get_next_line(fds[i]);
				if (line)
				{
					printf("FD%d (%s): %s", i, argv[i + 1], line);
					free(line);
					active_fds++;
				}
				else
				{
					printf("FD%d (%s): (null) - EOF reached\n", i, argv[i + 1]);
					close(fds[i]);
					fds[i] = -1;  // Marcar como fechado
				}
			}
		}
		printf("\n");
		round++;

		// Segurança: parar após 100 rounds
		if (round > 100)
		{
			printf("Warning: Stopped after 100 rounds\n");
			break ;
		}
	}

	printf("=== All files read successfully ===\n");
	printf("Total rounds: %d\n", round - 1);

	// Fechar qualquer FD ainda aberto
	for (i = 0; i < argc - 1; i++)
	{
		if (fds[i] >= 0)
			close(fds[i]);
	}
	free(fds);

	return (0);
}