#include "../libft/libft.h"
#include "../includes/minishell.h"
#include "../includes/parsing.h"
#include "unity.h"

t_env	*init_env;

static int run_cmd(char **cmd){
	t_dados test1 = {
		.comando = cmd,
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = NULL
	};
	return ft_execute_multiple_cmd(&test1, init_env);
}

static void assert_n_files_and_clean(char **actuals, char **expecteds)
{
	//int return_code;
	
	
	while (*actuals)
	{
		char *join1 = ft_strjoin(*actuals, " ");
		char *join2 = ft_strjoin(join1, *expecteds);
		char *join3 = ft_strjoin("diff ", join2);
		char *join4 = ft_strjoin("rm ", join2);
	//	return_code = run_cmd((char *[]){"bash", "-c", join3, NULL});
	//	TEST_ASSERT_EQUAL(0, return_code);
	//	return_code = run_cmd((char *[]){"bash", "-c", join4, NULL});
	//	TEST_ASSERT_EQUAL(0, return_code);
		actuals++;
		expecteds++;
		free(join1);
		free(join2);
		free(join3);
		free(join4);
	}
	
}

static void assert_files_and_clean(void){
	assert_n_files_and_clean((char *[]){"actual.txt", NULL}, (char *[]){"expected.txt", NULL});
}

// static void	tests_ft_out_redirect_pwd(void)
// {
// 	t_dados actual = {
// 		.comando = (char *[]){"pwd", NULL},
// 		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 0}},
// 		.nbr_redirections = 1,
// 		.next = NULL
// 	};

// 	char** expected = (char *[]){"bash", "-c", "pwd > expected.txt", NULL};

// 	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

// 	TEST_ASSERT_EQUAL(0, run_cmd(expected));

// 	assert_files_and_clean();
// }

// static void test_creat(void)
// {
// 		t_dados actual = {
// 		.comando = (char *[]){"pwd", NULL},
// 		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 0}},
// 		.nbr_redirections = 1,
// 		.next = NULL
// 	};

// 	char** expected = (char *[]){"bash", "-c", "pwd > expected.txt", NULL};

// 	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

// 	TEST_ASSERT_EQUAL(0, run_cmd(expected));
// }

// static void	tests_ft_append_redirect_ls(void)
// {
// 	test_creat();

// 		t_dados actual = {
// 		.comando = (char *[]){"pwd", NULL},
// 		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 3}},
// 		.nbr_redirections = 1,
// 		.next = NULL
// 	};

// 	char** expected = (char *[]){"bash", "-c", "pwd >> expected.txt", NULL};

// 	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

// 	TEST_ASSERT_EQUAL(0, run_cmd(expected));

// 	assert_files_and_clean();
// }

// static void	tests_ft_input_redirect(void)
// {
// 	test_creat();

// 		t_dados actual = {
// 		.comando = (char *[]){"wc", NULL},
// 		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 1}},
// 		.nbr_redirections = 1,
// 		.next = NULL
// 	};
	
// 	char** expected = (char *[]){"bash", "-c", "wc < expected.txt", NULL};

// 	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

// 	TEST_ASSERT_EQUAL(0, run_cmd(expected));

// 	assert_files_and_clean();
// }

// static void tests_return_code_error(void){

// 	TEST_ASSERT_EQUAL(1, run_cmd((char *[]){"cd", "a", NULL}));
// 	TEST_ASSERT_EQUAL(1, run_cmd((char *[]){"bash", "-c", "wc a", NULL}));

// }

// static void	tests_ft_more_redirect(void)
// {
// 		t_dados actual = {
// 		.comando = (char *[]){"pwd", NULL},
// 		.redirect = (t_redirect[]){(t_redirect) {.filename="actual2.txt", .redirect_type = 0}, (t_redirect) {.filename="actual.txt", .redirect_type = 3}},
// 		.nbr_redirections = 2,
// 		.next = NULL
// 	};
	
// 	char** expected = (char *[]){"bash", "-c", "pwd > expected2.txt >> expected.txt", NULL};

// 	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

// 	TEST_ASSERT_EQUAL(0, run_cmd(expected));

// 	assert_n_files_and_clean((char *[]){"actual2.txt", "actual.txt", NULL}, (char *[]){"expected2.txt", "expected.txt", NULL});
// }

static void	tests_ft_pipe(void)
{
		t_dados actual2 = {
		.comando = (char *[]){"grep", "a", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 0}},
		.nbr_redirections = 1,
		.next = NULL,
	};

		t_dados actual = {
		.comando = (char *[]){"ls", NULL},
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = &actual2,
	};

	char** expected = (char *[]){"bash", "-c", "ls | grep a > expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

	assert_files_and_clean();
}

static void	compare_dados(t_dados *expected, t_dados *t_parsing)
{
	int		i;
	t_dados	*aux = expected;
	t_dados	*aux_p = t_parsing;

	i = 0;
	while (aux)
	{
		while (aux->comando[i])
		{
			TEST_ASSERT_NOT_NULL(aux_p);
			TEST_ASSERT_NOT_NULL(aux_p->comando[i]);
			printf("expec: %s\n", aux->comando[i]);
			printf("parsing: %s\n", aux_p->comando[i]);
			TEST_ASSERT_EQUAL_STRING(aux->comando[i], aux_p->comando[i]);
			i++;
		}
		i = 0;
		aux = aux->next;
		aux_p = aux_p->next;
	}
	free_list(&t_parsing);
}

static void	tests_ft_pipe_parsing(void)
{
	char	*input = {"ls | grep a"};
	t_dados	*t_parsing = parsing(input);

	t_dados expected2 = {
		.comando = (char *[]){"grep", "a", NULL},
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = NULL,
	};

		t_dados expected = {
		.comando = (char *[]){"ls", NULL},
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = &expected2,
	};

	compare_dados(&expected, t_parsing);
}

static void	tests_ft_2_pipe(void)
{
	t_dados actual3 = {
	.comando = (char *[]){"wc", NULL},
	.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 0}},
	.nbr_redirections = 1,
	.next = NULL,
	};

		t_dados actual2 = {
		.comando = (char *[]){"grep", "a", NULL},
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = &actual3,
	};

		t_dados actual = {
		.comando = (char *[]){"ls", NULL},
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = &actual2,
	};

	char** expected = (char *[]){"bash", "-c", "ls | grep a | wc > expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

	assert_files_and_clean();
}

static void	tests_ft_builtin_pwd(void)
{
		t_dados actual = {
		.comando = (char *[]){"pwd", NULL},
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = NULL,
	};

	char** expected = (char *[]){"bash", "-c", "pwd", NULL};

	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

//	assert_files_and_clean();
}

static void	tests_ft_builtin_pwd_red(void)
{
		t_dados actual = {
		.comando = (char *[]){"pwd", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 0}},
		.nbr_redirections = 1,
		.next = NULL,
	};

	char** expected = (char *[]){"bash", "-c", "pwd > expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_execute_multiple_cmd(&actual, init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

	assert_files_and_clean();
}

void	setUp(void)
{
	// set stuff up here
}

void	tearDown(void)
{
	// clean stuff up here
}

// not needed when using generate_test_runner.rb
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_env = init_minienv(env);
	UNITY_BEGIN();
	// RUN_TEST(tests_ft_append_redirect_ls);
	// RUN_TEST(tests_ft_out_redirect_pwd);
	// RUN_TEST(tests_ft_input_redirect);
	// RUN_TEST(tests_return_code_error);
	//RUN_TEST(tests_ft_more_redirect);
	RUN_TEST(tests_ft_pipe);
	RUN_TEST(tests_ft_2_pipe);
	RUN_TEST(tests_ft_pipe_parsing);
	RUN_TEST(tests_ft_builtin_pwd);
	RUN_TEST(tests_ft_builtin_pwd_red);
	RUN_TEST(tests_ft_builtin_pwd_red);
	return (UNITY_END());
}
