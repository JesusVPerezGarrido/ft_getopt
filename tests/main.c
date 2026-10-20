/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeperez- <jeperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:10:37 by jeperez-          #+#    #+#             */
/*   Updated: 2026/10/20 11:28:08 by jeperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"
#include <assert.h>
#include <stdio.h>

static void	test_init(void)
{
	char		*argv[] = {"program", "-n", "name", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 3, argv, "nt:");
	assert(info.argc == 3);
	assert(info.argv == argv);
	assert(info.optind == 1);
	assert(info.optarg == NULL);
	assert(info.optstr[0] == 'n');
	assert(info.optstr[1] == 't');
	assert(info.optstr[2] == ':');
}

static void	test_flag(void)
{
	char		*argv[] = {"program", "-n", "name", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 3, argv, "n");
	assert(ft_getopt(&info) == 'n');
	assert(ft_getopt(&info) == -1);
	assert(info.optind == 2);
}

static void	test_clustered_flags(void)
{
	char		*argv[] = {"program", "-ab", "name", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 3, argv, "ab");
	assert(ft_getopt(&info) == 'a');
	assert(ft_getopt(&info) == 'b');
	assert(ft_getopt(&info) == -1);
	assert(info.optind == 2);
}

static void	test_attached_argument(void)
{
	char		*argv[] = {"program", "-t5", "name", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 3, argv, "t:");
	assert(ft_getopt(&info) == 't');
	assert(info.optarg == argv[1] + 2);
	assert(info.optind == 2);
	assert(ft_getopt(&info) == -1);
}

static void	test_separate_argument(void)
{
	char		*argv[] = {"program", "-t", "5", "name", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 4, argv, "t:");
	assert(ft_getopt(&info) == 't');
	assert(info.optarg == argv[2]);
	assert(info.optind == 3);
	assert(ft_getopt(&info) == -1);
}

static void	test_unknown_option(void)
{
	char		*argv[] = {"program", "-x", "name", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 3, argv, "n");
	assert(ft_getopt(&info) == '?');
	assert(ft_getopt(&info) == -1);
	assert(info.optind == 2);
}

static void	test_stops_at_positional_argument(void)
{
	char		*argv[] = {"program", "name", "-n", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 3, argv, "n");
	assert(ft_getopt(&info) == -1);
	assert(info.optind == 1);
}

static void	test_missing_argument(void)
{
	char		*argv[] = {"program", "-t", NULL};
	t_getopt	info;

	ft_getoptinit(&info, 2, argv, "t:");
	assert(ft_getopt(&info) == ':');
	assert(info.optarg == NULL);
	assert(info.optind == 2);
}

int	main(void)
{
	puts("> Testing Structure Intialization...");
	test_init();
	puts("> Passed");
	puts("> Testing Simple Flag...");
	test_flag();
	puts("> Passed");
	puts("> Testing Multiple Clustered Flags...");
	test_clustered_flags();
	puts("> Passed");
	puts("> Testing Attached Argument Flags...");
	test_attached_argument();
	puts("> Passed");
	puts("> Testing Separate Argument Flags...");
	test_separate_argument();
	test_attached_argument();
	puts("> Passed");
	puts("> Testing Unknown Option...");
	test_unknown_option();
	puts("> Passed");
	puts("> Testing Positional Argument...");
	test_stops_at_positional_argument();
	puts("> Passed");
	puts("> Testing Missing Argument...");
	test_missing_argument();
	puts("> Passed");
	puts("");
	puts("All ft_getopt tests passed.");
	return (0);
}
