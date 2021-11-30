#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int c, char **v)
{
	char *str;

	while (1)
	{
		str = readline("Insert your commands:\n$> ");
		if (!str || !*str)
		{
			printf("Exit\n");
			free(str);
			return (1);
		}
		add_history(str); // adiciona o comando 'str' ao histórico
		printf("Command instruction: %s\n", str);
		free(str); // sem o free dá leak usando fsanitize
	}
	
	rl_clear_history(); // limpa o histórico também para próximas chamadas do readline
	return (0);
}

/* compile using -lreadline */

// Function: void rl_clear_history (void)
// Clear the history list by deleting all of the entries, in the same manner as the History library's clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.

// Function: void rl_replace_line (const char *text, int clear_undo)
// Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
// rl_line_buffer contém a linha que está sendo digitada

// Function: int rl_on_new_line (void)
// Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

// Function: void rl_redisplay (void)
// Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
