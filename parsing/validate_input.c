
#include "../includes/minishell.h"
#include "../includes/parsing.h"

/*verificar pipe dplo, pipe sem nada escrito, aspas abertas aspas estranhas*/

/**
 * @errado:
 * "ls """
 * "ls ""
*/

int validate_input(char *s)
{
    int	i;
    //int check = 0;

	i = 0;
	while (s[i] != '\0')
	{
        if(s[i] == '|')
        {
            i++;
             while(s[i] == ' ' || s[i] == '\t')
            {
                i++;			
            }
            if(s[i] == '\0')
            {
                ft_putstr_fd("syntax error, command not found after pipe\n", 1);
                return (1);
            } 
            if (s[i] == '|')
            {
                ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
                return (1);
            }    
        }
        if(s[i] == '"')
        {
            i++;
            while(s[i] != '"')
            {
                if(s[i] == '\0')
                {
                    ft_putstr_fd("syntax error, open quotes\n", 1);
                    return (1);
                }
                i++;
            }    
        }
        if(s[i] == '\'')
        {
            i++;
            while(s[i] != '\'')
            {
                if(s[i] == '\0')
                {
                    ft_putstr_fd("syntax error, open quotes\n", 1);
                    return (1);
                }
                i++;
            }    
        }
		i++;
	}
    return (0);







}