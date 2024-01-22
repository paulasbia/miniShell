#include "../libft/libft.h"
#include "../includes/minishell.h"
#include "unity.h"

t_env	*init_env;

static int run_cmd(char **cmd){
	t_dados test1 = {
		.comando = cmd,
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = NULL
	};
	return ft_one_cmd(&test1, &init_env);
}




static void assert_n_files_and_clean(char **actuals, char **expecteds)
{
	int return_code;
	
	while (*actuals)
	{
		return_code = run_cmd((char *[]){"bash", "-c", ft_strjoin("diff ", ft_strjoin(ft_strjoin(*actuals, " "), *expecteds)), NULL});
		TEST_ASSERT_EQUAL(0, return_code);
		return_code = run_cmd((char *[]){"bash", "-c", ft_strjoin("rm ", ft_strjoin(ft_strjoin(*actuals, " "), *expecteds)), NULL});
		TEST_ASSERT_EQUAL(0, return_code);
		actuals++;
		expecteds++;
	}
}

static void assert_files_and_clean(void){
	assert_n_files_and_clean((char *[]){"actual.txt", NULL}, (char *[]){"expected.txt", NULL});
}

static void	tests_ft_out_redirect_pwd(void)
{
	t_dados actual = {
		.comando = (char *[]){"pwd", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 0}},
		.nbr_redirections = 1,
		.next = NULL
	};

	char** expected = (char *[]){"bash", "-c", "pwd > expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_one_cmd(&actual, &init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

	assert_files_and_clean();
}

static void test_creat(void)
{
		t_dados actual = {
		.comando = (char *[]){"pwd", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 0}},
		.nbr_redirections = 1,
		.next = NULL
	};

	char** expected = (char *[]){"bash", "-c", "pwd > expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_one_cmd(&actual, &init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));
}

static void	tests_ft_append_redirect_ls(void)
{
	test_creat();

		t_dados actual = {
		.comando = (char *[]){"ls", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 3}},
		.nbr_redirections = 1,
		.next = NULL
	};

	char** expected = (char *[]){"bash", "-c", "ls >> expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_one_cmd(&actual, &init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

	assert_files_and_clean();
}

static void	tests_ft_input_redirect(void)
{
	test_creat();

		t_dados actual = {
		.comando = (char *[]){"wc", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="actual.txt", .redirect_type = 1}},
		.nbr_redirections = 1,
		.next = NULL
	};
	
	char** expected = (char *[]){"bash", "-c", "wc < expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_one_cmd(&actual, &init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

	assert_files_and_clean();
}

static void tests_return_code_error(void){

	TEST_ASSERT_EQUAL(1, run_cmd((char *[]){"cd", "a", NULL}));
	TEST_ASSERT_EQUAL(1, run_cmd((char *[]){"bash", "-c", "wc a", NULL}));

}

static void	tests_ft_more_redirect(void)
{
		t_dados actual = {
		.comando = (char *[]){"pwd", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="actual2.txt", .redirect_type = 0}, (t_redirect) {.filename="actual.txt", .redirect_type = 3}},
		.nbr_redirections = 2,
		.next = NULL
	};
	
	char** expected = (char *[]){"bash", "-c", "pwd > expected2.txt >> expected.txt", NULL};

	TEST_ASSERT_EQUAL(0, ft_one_cmd(&actual, &init_env));

	TEST_ASSERT_EQUAL(0, run_cmd(expected));

	assert_n_files_and_clean((char *[]){"actual.txt", "actual2.txt", NULL}, (char *[]){"expected.txt", "expected2.txt", NULL});
}
	//start_execution(&test1, &init_env);

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
	RUN_TEST(tests_ft_out_redirect_pwd);
	RUN_TEST(tests_ft_append_redirect_ls);
	RUN_TEST(tests_ft_input_redirect);
	RUN_TEST(tests_return_code_error);
	RUN_TEST(tests_ft_more_redirect);
	return (UNITY_END());
}
