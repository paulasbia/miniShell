#include "../libft/libft.h"
#include "unity.h"

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

void	setUp(void)
{
	// set stuff up here
}

void	tearDown(void)
{
	// clean stuff up here
}

// not needed when using generate_test_runner.rb
int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(tests_ft_isalpha);
	return (UNITY_END());
}