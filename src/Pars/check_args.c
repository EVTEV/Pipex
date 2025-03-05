/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:57:31 by acaes             #+#    #+#             */
/*   Updated: 2025/03/05 14:57:31 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int	check_args(int ac)
{
	if (ac != 5)
		return (p_error("Error\n Invalid number of arguments\n"));
	return (0);
}

int	check_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		return (p_error("Error\n Invalid infile\n"));
	close(fd);
	return (0);
}
