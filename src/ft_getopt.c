/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeperez- <jeperez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:14:48 by jeperez-          #+#    #+#             */
/*   Updated: 2026/10/20 11:27:48 by jeperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"

void ft_getoptinit(t_getopt *info, int argc, char **argv, const char *optstr)
{
	size_t len;

	if (!info)
		return ;
	memset(info, 0, sizeof(*info));
	info->argc = argc;
	info->argv = argv;
	info->optind = 1;
	info->nextchar = 1;
	info->optarg = NULL;
	if (!optstr)
		return ;
	len = strlen(optstr);
	if (len >= sizeof(info->optstr))
		len = sizeof(info->optstr) - 1;
	memcpy(info->optstr, optstr, len);
	info->optstr[len] = '\0';
}

static bool	isopt(const char *s)
{
	return (s && s[0] == '-'
		&& s[1] != '\0'
		&& !(s[1] == '-' && s[2] == '\0'));
}

int	ft_getopt(t_getopt *info)
{
	char		curchar;
	const char	*iter;

	if (!info || !info->argv || info->optind < 0)
		return (-1);
	info->optarg = NULL;
	while (info->optind < info->argc)
	{
		if (!isopt(info->argv[info->optind]))
			return (-1);
		if (info->argv[info->optind][info->nextchar] == '\0')
		{
			info->optind++;
			info->nextchar = 1;
			continue ;
		}
		curchar = info->argv[info->optind][info->nextchar];
		info->nextchar++;
		iter = info->optstr;
		while (*iter)
		{
			if (*iter == curchar)
			{
				if (iter[1] == ':')
				{
					if (info->argv[info->optind][info->nextchar] != '\0')
					{
						info->optarg = &info->argv[info->optind][info->nextchar];
						info->optind++;
						info->nextchar = 1;
					}
					else
					{
						if (info->optind + 1 >= info->argc)
						{
							info->optind++;
							info->nextchar = 1;
							return (':');
						}
						info->optarg = info->argv[info->optind + 1];
						info->optind += 2;
						info->nextchar = 1;
					}
					return (curchar);
				}
				if (info->argv[info->optind][info->nextchar] == '\0')
				{
					info->optind++;
					info->nextchar = 1;
				}
				return (curchar);
			}
			iter++;
		}
		return ('?');
	}
	return (-1);
}
