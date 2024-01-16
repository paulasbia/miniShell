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

static void	tests_ft_ls(void)
{
	char **cmd = ft_split("ls", ' ');

	ft_execute_child(cmd, init_env);
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
	RUN_TEST(tests_ft_isalpha);
	RUN_TEST(tests_ft_ls);
	return (UNITY_END());
}
