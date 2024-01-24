

#ifndef PARSING_H
# define PARSING_H

typedef struct s_redirect 
{
	int  redirect_type;
	char *filename;
}	t_redirect;

typedef struct s_dados
{
	int				nbr_redirections;
	char  			**comando;
	t_redirect 	*redirect;
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