/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikunne <sikunne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:26:14 by sikunne           #+#    #+#             */
/*   Updated: 2025/08/08 18:10:21 by sikunne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snooper.hpp"

int	is_cwd(char *target)
{
	if (target[0] != 'P')
		return (0);
	if (target[1] != 'W')
		return (0);
	if (target[2] != 'D')
		return (0);
	if (target[3] != '=')
		return (0);
	return (1);
}

static char	*get_cwd(char **env)
{
	int	i = -1;
	while (env[++i])
	{
		if (is_cwd(env[i]))
			return (&(env[i][4]));
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char *target;

	if (argc < 2)
		target = get_cwd(envp);
	else
		target = argv[1];
	if (target)
	{
		Snooper snoopy(target);
		snoopy.showRestFiles();
	}
	else
	{
		Snooper snoopy("/pathdoesnotexist");
		snoopy.showRestFiles();
	}
	return (0);
}
