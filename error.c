
// #include <stdio.h>
// #include <string.h>
// #include <errno.h>

// int main () {
//    FILE *fp;

//    fp = fopen("file.txt","r");
//    if( fp == NULL ) 
// 	  {
//       printf("Error: %s\n", strerror(errno));
//    }
   
//    return(0);
// }

// extern int errno ;

// int main () {

//    FILE * pf;
//    int errnum;
//    pf = fopen ("unexist.txt", "rb");
	
//    if (pf == NULL) {
   
//       errnum = errno;
//       fprintf(stderr, "Value of errno: %d\n", errno);
//       perror("Error printed by perror");
//       fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
//    } else {
   
//       fclose (pf);
//    }
   
//    return 0;
// }

// int main(void)
// {

// 	// char *s1 = "--save";
// 	// char *s2 = "--Save";
// 	char *s3 = "pajarito.cub.cub";

// printf("Valor file: %d\n", ft_check_file_type(s3));
// 	if (ft_check_file_type(s3) == 0)
// 		printf("valid ext file");
// 	else
// 		printf("invalid extension file");

// 	// printf("%s\n", );
// 	// printf("la longitud de s1 es: %d\n", ft_strlen(s1));
// 	// printf("la longitud de s2 es: %d\n", ft_strlen(s2));
// 	// printf("El valor es %d\n", ft_strncmp(s1, s2, ft_strlen(s2)));
// 	return(0);

// }

// int main(int argc, char *argv[])
// {

// 	if(argc < 2) 
// 	{
// 		printf("Ha olvidado su nombre.\n");
// 		exit(1);
// 	}
// 	printf("Hola %s %s", argv[1], argv[2]);
// 	return (0);
// }

// int main(void)
// {
// 	FILE *pf;
// 	int errnum;
// 	pf = fopen("no file.txt", "rb");
// 	if (pf == NULL)
// 	{
// 		errnum = errno;
// 		fprintf(stderr,"Value of errno: %d\n", errno);
// 		perror("Error printed by perror");
// 		fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
// 	}
// 	else
// 		fclose(pf);
// }

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "../CODAM/cub3D/cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int		ft_put_error(char *error)
{
	ft_putstr_fd("\nError: ", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	return(-1);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((int)((unsigned const char)s1[i] - (unsigned const char)s2[i]));
}

size_t		ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

int ft_check_file_type(char *map_ext)
{
    int i;
    
    i = 0;
    i = ft_strlen(map_ext);

    if (map_ext[i - 4] == '.' && map_ext[i - 3] == 'c' && map_ext[i - 2] == 'u'
        && map_ext[i - 1] == 'b')
            return (0);
    return(-1);
}

int main (int argc, char **argv)
{
	int screenshot;
	int error;

	error = 0;
	if (argc < 2)
		return(ft_put_error("at least one argument was expected"));
	if (argc > 3)
		return(ft_put_error("too many arguments"));
	if (argc >= 2)
	{
		if (ft_check_file_type(argv[1]) == -1)
		{
			ft_put_error("wrong extension map file");
			error++;
		}
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", ft_strlen("--save")) == 0)
				screenshot = 1;
			else
			{
				ft_put_error("wrong argument for screenshot");
				error++;
			}
		}
	}
	if (error > 0)
		return(0);
	return (0);
}

int ft_check_resolution(t_screen res)
{
	int max_color_val;

	int = 255;
	if (res.width < 0 || res.height < 0)
		return(ft_put_error("Non negative numbers were expected"));
	if (res.width > max_color_val || res.height > max_color_val )
		return(ft_put_error("Color value(s) must be maximun 255"));
}

