/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 11:46:25 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:59:23 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 32
# include <unistd.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
int		ft_atoi_max_int(const char *str);
int		ft_isemptyline(char *str);
int		ft_isnumber(char *str);
int		ft_iswhitespace(char c);
int		ft_put_error(char *error);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		get_next_line(int fd, char **line);
char	*ft_strtrim(const char *s1, const char *set);
int		ft_strcmp_trim(const char *s1, const char *s2);
void	ft_free_array(char **array);
int		ft_array_size(char **array);
int		ft_max(int num1, int num2);
int		ft_min(int num1, int num2);
int		ft_ispositive_number(char *str);

#endif
