#include "../libft/libft.h"
#include "../includes/minishell.h"
#include "unity.h"

t_env	*init_env;

static void	tests_ft_isalpha(void)
{
	TEST_ASSERT_FALSE(ft_isalpha('5'));
	TEST_ASSERT_TRUE(ft_isalpha('a'));
	TEST_ASSERT_TRUE(ft_isalpha('A'));
	//TEST_ASSERT_EQUAL(isalpha('1'), ft_isalpha('1'));
	TEST_ASSERT_TRUE(ft_isalpha('A'));
	// TODO teste foi comentado devido retorno divergente
	// assert((ft_isalpha('a') == isalpha('a')));
}

static int run_cmd(char **cmd){
	t_dados test1 = {
		.comando = cmd,
		.redirect = NULL,
		.nbr_redirections = 0,
		.next = NULL
	};
	return ft_one_cmd(&test1, &init_env);
}


 static void assert_files_and_clean(void){
	int return_code;

	return_code = run_cmd((char *[]){"bash", "-c", "diff actual.txt expected.txt", NULL});
	TEST_ASSERT_EQUAL(0, return_code);
	return_code = run_cmd((char *[]){"bash", "-c", "rm actual.txt expected.txt", NULL});
	TEST_ASSERT_EQUAL(0, return_code);
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

static void	tests_ft_append_redirect_ls(void)
{
		t_dados test3 = {
		.comando = (char *[]){"ls", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="text.txt", .redirect_type = 3}},
		.nbr_redirections = 1,
		.next = NULL
	};

	ft_one_cmd(&test3, &init_env);
}

static void	tests_ft_input_redirect(void)
{
		t_dados test4 = {
		.comando = (char *[]){"wc", NULL},
		.redirect = (t_redirect[]){(t_redirect) {.filename="text.txt", .redirect_type = 1}},
		.nbr_redirections = 1,
		.next = NULL
	};
	
	ft_one_cmd(&test4, &init_env);
}

static void tests_return_code_error(void){

	TEST_ASSERT_EQUAL(1, run_cmd((char *[]){"cd", "a", NULL}));
	TEST_ASSERT_EQUAL(1, run_cmd((char *[]){"bash", "-c", "wc a", NULL}));

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
	RUN_TEST(tests_ft_isalpha);
	RUN_TEST(tests_ft_out_redirect_pwd);
	RUN_TEST(tests_ft_append_redirect_ls);
	RUN_TEST(tests_ft_input_redirect);
	RUN_TEST(tests_return_code_error);
	RUN_TEST(tests_ft_isalpha);
	return (UNITY_END());
}
