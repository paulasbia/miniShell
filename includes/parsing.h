

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
t_dados *parsing(char *input);	
char	**split_ms(char const *s);
char	**split_pipe(char const *s);
int validate_input(char *s);
char *clean_quotes(char *s);
void free_dp(char **split);
void free_list(t_dados **lst);
void	print_list(t_dados *lst);




#endif