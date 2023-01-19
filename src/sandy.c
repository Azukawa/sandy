#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<strings.h>
#include	<time.h>
#define		MAX = 
void 	ft_swap(int *a, int*b)
{
		int c;

		c = *a;
		*a = *b;
		*b = c;
}

void	ft_delay(int ms)
{
	ms *= 1000;
	clock_t	start_time = clock();
	while (clock() < start_time + ms)
		;
}

void	printmap(int w, int h, int *map)
{
	int x, y;
	x = y = 0;
	char *sym = ".~OXÖ7@QSzäölojppihp";
//	char *sym = ".O123456zäölojppihp";
	while(y < h)
	{
		while(x < w)
		{
			write(1, &sym[map[w * y + x]], 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
		x = 0;
	}
	write(1, "\n", 1);
}

void	physics(int w, int h, int *map)
{
	int x, y;
	x = w - 1;
	y = h - 1;

	while(y >= 0)
	{
		while(x >= 0)
		{
			
			if(map[w * y + x] != 0 && y < h -1)
			{
				if(map[w * y + x + w] < map[w * y + x])
					ft_swap(&map[w * y + x], &map[w * y + x + w]);
				else if(x > 0 && map[w * y + x + w - 1] < map[w * y + x])
					ft_swap(&map[w * y + x], &map[w * y + x + w - 1]);
				else if(x < w -1 && map[w * y + x + w + 1] < map[w * y + x])
					ft_swap(&map[w * y + x], &map[w * y + x + w + 1]);
				else if(x > 0 &&  map[w * y + x] == 1 && map[w * y + x - 1] == 0)
					ft_swap(&map[w * y + x], &map[w * y + x - 1]);
				else if(x < w -1 && map[w * y + x] == 1 && map[w * y + x + 1] == 0)
					ft_swap(&map[w * y + x], &map[w * y + x + 1]);
			
			}
			x--;
		}
		y--;
		x = w - 1;
	}
}

void	funnel(int *map, int start, int end, int rate, int place, int type, int i)
{
	if(i % rate == 0 && i > start && i < end)
		map[place] = type;
}

void	loop(int w, int h, int *map)
{
	ft_delay(100);
	static int i;
	funnel(map, 0, 390, 2, 10, 2, i);
	funnel(map, 0, 390, 3, 34, 2, i);
	funnel(map, 400, 6000, 2, 21, 1, i);
	physics(w, h, map);	
	printmap(w, h, map);
	i++;
}


int		main(int argc, char **argv)
{
	if(argc != 3)
		return(0);
	int w, h;
	int *map;
	int i = 6000;
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	if(w < 1 || h < 1)
		return(0);
	map = malloc(sizeof(int) * w * h);
	bzero(map, sizeof(int) * w * h);
	map[99] = 1;
	map[0] = 1;
	printmap(w, h, map);
	while(i-- > 0)
		loop(w, h, map);
	free(map);
	return(0);
}
