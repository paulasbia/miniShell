

#include "../includes/minishell.h"

// < 0
// > 1
// << 2
// >> 3


typedef struct s_redireção 
{
	int  tipo_de_redireção;
	char *filenane;
}	t_redireção;

typedef struct s_dados
{
	char  			**comando;
	t_redireção 	*redireção;
	struct s_dados	*next;
} t_dados;


// ls
// dados.command[0] = "ls";
// execve("usr/bin/ls");
// dados.redireção = NULL;
// dados.next = NULL;


// ls>ficheiro.txt
// dados.comando[0] = "ls";
// dados.redireção[0].tipo_de_redireção = 1;
// dados.redireção[0].filename = "ficheiro.txt";
// dados.next = NULL;

ls -la < ficheiro.txt < file.txt | wc

// t_dados dados1 = malloc(sizeof(t_dados));  

// dados1.comando = malloc(sizeof(char *) * (2 + 1));
// dados1.comando[0] = "ls";
// dados1.comando[1] = "-la";
// dados1.comando[2] = NULL;
// dados1.redireção = malloc(sizeof(t_redireção) * (2 + 1));
// dados1.redireção[0].tipo_de_redireção = 1;
// dados1.redireção[0].filename = "ficheiro.txt";
// dados1.redireção[1].tipo_de_redireção = 0;
// dados1.redireção[1].filename = file.txt 
// dados.next = dados2;


// t_dados dados2 = malloc(sizeof(t_dados));
// dados2.comando = malloc(sizeof(char *) * (1 + 1));
// dados2.redireção = NULL;
// dados2.next = NULL;
// dados2.comando[0] = "wc";


int redirection(char *red)
{

    if(ft_strncmp("<<", red, 2) == 0)
        return (2);
    else if(ft_strncmp(">>", red, 2) == 0)
        return (3);
    else if(ft_strncmp(">", red, 1) == 0)
        return (0);
    else if(ft_strncmp("<", red, 1) == 0)
        return (1);
    else
        return (-1);
}


static int	cont(char const *s, char c)
{
	int	x;
	int	result;

	x = 0;
	result = 0;
	while (s[x] != '\0')
	{
		if (s[x] != c && ((s[x + 1]) == c || (s[x + 1]) == '\0'))
		{
			x++;
			result++;
		}
		else
			x++;
	}
	return (result);
}

static char	*word(const char *str, char c)
{
	int		i;
	char	*src;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	src = malloc(sizeof(char) * (i + 1));
	if (src == NULL)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		src[i] = str[i];
		i++;
	}
	src[i] = '\0';
	return (src);
}

char	**split_ms(char const *s, char c)
{
	char	**totals;
	int		x;
	int		y;

	totals = malloc(sizeof(char *) * (cont(s, c) + 1));
	if (totals == NULL)
		return (NULL);
	x = 0;
	y = 0;
	while (s[x] != '\0')
	{
		if (s[x] != c)
		{
			totals[y] = word(&s[x], c);
			y++;
			while (s[x] != c && s[x] != '\0')
				x++;
		}
		else
			x++;
	}
	totals[y] = NULL;
	return (totals);
}


ls-la>teste.txt

// // 0. ls
//  -la 
//  > 
//  ficheiro.txt
// < 
// file.txt
// // 1. wc

void alocacao(t_dados *dados, int redirection, int cmd)
{
    dados



}

void parsing(char *input)
{
    char **split;
    char **split_2;
    int i = 0;
    int j = 0;
    int nbr_redirections = 0;
    int nbr_comands = 0;
    t_dados *dados;

   split = split_ms(input, '|');

    while(split[i] != NULL)
    {
        split_2 = split_ms(split[i], ' ');
        j = 0;  //errado pois o bash aceita comando sem espaço
        while(split_2[j] != NULL) 
        {
            if(redirection(split_2[j]) != -1)
            {
                nbr_redirections++;
                j += 2;
            }
            else
            {  
                nbr_comands++;
                j++;
            }
        }
        alocacao(dados, nbr_redirections, nbr_comands);
        i++;
    }
}
