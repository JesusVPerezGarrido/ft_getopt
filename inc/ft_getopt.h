/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeperez- <jeperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:23:57 by jeperez-          #+#    #+#             */
/*   Updated: 2026/10/20 11:32:46 by jeperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef struct s_getopt
{
	int		argc;
	char	**argv;
	char	optstr[32];
	int		optind;
	int		nextchar;
	char	*optarg;
} 			t_getopt;

void ft_getoptinit(t_getopt *info, int argc, char **argv, const char *optstr);
int ft_getopt(t_getopt *info);

#endif
