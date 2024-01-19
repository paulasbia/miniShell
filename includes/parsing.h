

#ifndef PARSING_H
# define PARSING_H

typedef struct s_redireção 
{
	int  tipo_de_redireção;
	char *filenane;
}	t_redireção;

typedef struct s_dados
{
	int				nbr_redirections;
	char  			**comando;
	t_redireção 	*redireção;
	struct s_dados	*next;
} t_dados;

//PARSING
void parsing(char *input);
char	**split_ms(char const *s);
char	**split_pipe(char const *s);
int validate_input(char *s);
char *clean_quotes(char *s);


#endif