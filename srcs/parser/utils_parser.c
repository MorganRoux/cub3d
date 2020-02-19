#include "cub3d.h"

t_cardinal	get_tex_orientation(char l)
{
	if (l == 'N')
		return (NO);
	if (l == 'S')
		return (SO);
	if (l == 'E')
		return (EA);
	if (l == 'W')
		return (WE);
	return (ERROR);
}

int		load_line(t_game_engine *ge, char *line, int *n)
{
	if ((int)ft_strlen(line) != ge->map.w)
		return (ERROR);
	ge->map.h++;
	if (!(ge->map.p_map = ft_realloc(ge->map.p_map, *n, *n + ge->map.w)))
		return ERROR;
	while(*line != 0)
		ge->map.p_map[(*n)++]= *line++ - '0';
	return (OK);
}

void	*ft_realloc(void *p, size_t l, size_t newsize)
{
	char	*ret;
	char	*ptr;
	size_t	n;

	n = -1;
	ptr = p;
	if (!(ret = (char *)malloc(newsize)))
		return (NULL);
	while (++n < l)
		ret[n] = ptr[n];
	while (++n < newsize)
		ret[n] = 0;
	if (p != NULL)
		free(p);
	return ((void *)ret);
}