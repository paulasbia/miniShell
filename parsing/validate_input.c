
#include "../includes/minishell.h"
#include "../includes/parsing.h"

/*verificar pipe dplo, pipe sem nada escrito, aspas abertas aspas estranhas*/

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
            if(s[i] == '|' || s[i] == '\0')
            {
                ft_putstr_fd("pipe error\n", 1);
                return (1);
            }    
        }
        if(s[i] == '"')
        {
            i++;
            while(s[i] != '"')
            {
                i++;			
            }
            i++;
        }
        if(s[i] == '\'')
        {
            i++;
            while(s[i] != '\'')
            {
                i++;				
            }
            i++;
        }
		i++;
	}
    return (0);







}