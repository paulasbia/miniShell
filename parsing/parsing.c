

#include "../includes/minishell.h"
#include "../includes/parsing.h"


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

// < 1
// > 0
// << 2
// >> 3

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



void print_list(t_dados *lst)
{
	int i = 0;
	int j = 0;
	t_dados *temp;

	temp = lst;
	while(temp != NULL)
	{
		printf("%d\n", temp->nbr_redirections);
		i = 0;
		while(i < temp->nbr_redirections)
		{
			printf("%s\n", temp->redireção[i].filenane);
			printf("%d\n", temp->redireção[i].tipo_de_redireção);
			i++;

		}
		j = 0;
		while(temp->comando[j] != NULL)
		{
			printf("%s\n", temp->comando[j]);
			j++;
		}
		temp = temp->next;
	}

}

void	ms_lstadd_back(t_dados **lst, t_dados *node) //posso usar da lib pois n tem alteração
{
	t_dados	*temp;

	temp = *lst;
	if (*lst == NULL)
		*lst = node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

t_dados	*ft_lstnew_p(int n_reds, int n_cmd, char **split_space)
{
	t_dados	*node;
	int i = 0;
	int j = 0;
	int x = 0;

	node = (t_dados *)malloc(sizeof(t_dados)); //aloco memoria para meu node
	if (!node)
		return (NULL);
    node->comando = malloc(sizeof(char *) * (n_cmd + 1)); //aloco memoria para o tanto de cmd que tenho
    node->redireção = malloc(sizeof(t_redireção) * (n_reds + 1)); // e tbm para o n de redireções
	
	while(split_space[i] != NULL)
	{
		if(redirection(split_space[i]) != -1) //se minha redirection for diferente de -1 é pq  há alguma
		{
			node->redireção[j].tipo_de_redireção = redirection(split_space[i]); // eu guardo o tipo e o nome
			node->redireção[j++].filenane = split_space[i + 1]; 
			i += 2; // ando duas pq depois da redirecao sempre tem o arquivo
		}
		else
		{  
			node->comando[x++] = split_space[i++]; //se n for redirecao ou filename é comando. 
		}

	}
	node->nbr_redirections = n_reds; //salvo o n de red para paula saber qnts há.
	node->comando[x] = NULL;
	node->next = NULL;
	return (node);
}

void alocacao(t_dados **dados_head, int redirection, int cmd, char **split_space)
{
	t_dados *node;

	node = ft_lstnew_p(redirection, cmd, split_space);

	ms_lstadd_back(dados_head, node);
}

void parsing(char *input)
{
    char **split_pipe;
    char **split_space;
    int i = 0;
    int j = 0;
    int nbr_redirections = 0;
    int nbr_comands = 0;
    t_dados *dados_head;

	dados_head = NULL;
	split_pipe = split_ms(input, "|");

    while(split_pipe[i] != NULL)
    {
        split_space = split_ms(split_pipe[i], ">< \t");
        j = 0;
		nbr_redirections = 0;
		nbr_comands = 0;  //errado pois o bash aceita comando sem espaço
        while(split_space[j] != NULL) 
        {
            if(redirection(split_space[j]) != -1)
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
        alocacao(&dados_head, nbr_redirections, nbr_comands, split_space);
        i++;
    }
	print_list(dados_head);
}

