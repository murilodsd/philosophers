/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:03:02 by mde-souz          #+#    #+#             */
/*   Updated: 2024/09/21 20:04:33 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include "../lib/libft/include/libft.h"
# include "./structures.h"

typedef struct s_program
{
	t_mem_allocation	mem_allocation;

}	t_program;

void	check_mem(t_game *game, t_list **ptr_or_matrix_list, \
	void *ptr, char *error_msg);
#endif