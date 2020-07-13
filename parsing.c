/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:40 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/13 14:50:27 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main (int argc, char **argv)
{
    if(argc < 2)
        return(ft_puterror("Arguments missing"));
    if(argc > 3)
        return(ft_puterror("Too many arguments"));
}