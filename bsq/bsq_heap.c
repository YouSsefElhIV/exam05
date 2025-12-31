#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int x, y, size;
} t_bsq;

typedef struct 
{
    int x, y;
    char **map;
    t_bsq bsq;
    char obstacle, full, space;
} t_data;

void free_map(char **map, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        free(map[i]);
    }
    free(map);
}

void free_map2(int **map, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        free(map[i]);
    }
    free(map);
}


int read_map(FILE *file, t_data *data)
{
    char *line = NULL;
    int y = 0;
    size_t size = 0;
    if (fscanf(file, "%i %c %c %c\n", &data->y, &data->space, &data->obstacle, &data->full) != 4 || data->y < 1 || data->obstacle == data->space || data->obstacle == data->full || data->full == data->space)
        return 1;
    data->map = malloc(data->y * sizeof(char *));
    if (!data->map)
        return (1);
    while (y < data->y && getline(&line, &size, file) != 1)
    {
        int len = strlen(line);

        if (len == 0)
            return (free_map(data->map, y), free(line), 1);
        if (line[len - 1] == '\n')
        {
            line[--len] = '\0';
        }
        if (y == 0)
            data->x = len;
        else if (data->x != len)
            return (free_map(data->map, y), free(line), 1);

        data->map[y] = malloc(data->x);

        if (!data->map[y]) // possible leak.
        {
            free(line);
            free_map(data->map, y);
            return 1;
        }
        for (int x = 0; x < data->x; x++)
        {
            if (line[x] == data->space)
                data->map[y][x] = '0';
            else if (line[x] == data->obstacle)
                data->map[y][x] = '1';
            else
                return (free(data->map[y]), free_map(data->map, y),free(line), 1);
        }
        y++;
    }
    free(line);
    if (y != data->y)
        return (free_map(data->map, y), 1);
    return 0;
}

int miiin(int a, int b, int c)
{
	if (a <= b && a <= c)
		return a;
	if (b <= a && b <= c)
		return b;
	return c;
}

int bsq(t_data *data)
{
    int **map2;
    map2 = malloc(sizeof(int *) * data->y);
    if (!map2)
    {
        fprintf(stdout, "map error");
        return (1);
    }
    for (int i = 0; i < data->y; i++)
    {
        map2[i] = malloc(sizeof(int) * data->x);
        if (map2[i] == NULL)
        {
            free_map2(map2, i);
            return (1);
        }
    }
            //real bsq work is here after all that init
    for (int y = 0; y < data->y; y++)
    {
        for (int x = 0; x < data->x; x++)
        {
            if (data->map[y][x] == '1')
                map2[y][x] = 0;
            else if (x == 0 ||y == 0)
                map2[y][x] = 1;
            else
                map2[y][x] = 1 + miiin(map2[y - 1][x], map2[y][x - 1], map2[y - 1][x - 1]);
            if (data->bsq.size < map2[y][x])
            {
                data->bsq.size = map2[y][x];
                data->bsq.y = y - map2[y][x] + 1;
                data->bsq.x = x - map2[y][x] + 1;
            }
        }
    }
    for (int y = 0; y < data->bsq.size; y++)
        for (int x = 0; x < data->bsq.size; x++)
            data->map[y + data->bsq.y][x + data->bsq.x] = '2';
    free_map2(map2, data->y);
    return (0);
}

void printing(t_data *data)
{
    for (int y = 0; y < data->y; y++)
    {
        for (int x = 0; x < data->x ; x++)
        {
            if (data->map[y][x] == '0')
                fputc(data->space, stdout);
            else if (data->map[y][x] == '1')
                fputc(data->obstacle, stdout);
            else
                fputc(data->full, stdout);
        }
        fputc('\n', stdout);
    }
}

void process_map(FILE *file)
{
    t_data data = {0};
    data.bsq.size = 0;
    if (read_map(file, &data) == 1)
    {
        fprintf(stderr, "map error\n");
        return;
    }
    else 
    {
        if (bsq(&data) == 0)
            printing(&data);
        free_map(data.map, data.y);
    }
}

int main(int ac, char **av)
{
    if (ac == 1)
        process_map(stdin);
    else
    {
        for(int i = 1; i < ac; i++)
        {
            FILE *file = fopen(av[i], "r");
            if (!file)
            {
                fprintf(stderr, "map error\n");
                continue;
            }
            process_map(file);
            if (i != ac - 1)
                fputc('\n', stdout);
        }
    }
    return (0);
}
