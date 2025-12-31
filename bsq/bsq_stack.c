#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int x, y, size;
} t_bsq;


typedef struct{
    int x, y;
    char map[1000][1000];
    char ob, full, space;
    t_bsq bsq;
} t_data;



int read_map(FILE *file, t_data *data)
{
    if (fscanf(file, "%i %c %c %c\n", &data->y, &data->space, &data->ob, &data->full) != 4 || data->y < 1 || data->ob == data->full || data->ob == data->space || data->space == data->ob)
        return (1);
    
    char *line = NULL;
    int y = 0;
    size_t size;

    while (y < data->y && getline(&line, &size, file) != -1)
    {
        int len = strlen(line);
        if (len == 0 || len > 1000)
            return (free(line), 1);
        if (line[len - 1] == '\n')
            line[--len] = '\0';
        if (y == 0)
            data->x = len;
        else if (data->x != len)
            return (free(line), 1);
        for (int x = 0; x < data->x; x++)
        {
            if (line[x] == data->ob)
                data->map[y][x] = '0';
            else if (line[x] == data->space)
                data->map[y][x] = '1';
            else
                return (free(line), 1);
        }
        y++;
    }
    free(line);
    if (y != data->y)   
        return (1);
    return (0);
}

void printing(t_data *data)
{
    for (int i = 0; i < data->y; i++)
    {
        for (int j = 0; j < data->x; j++)
        {
            if (data->map[i][j] == '0')
                fputc (data->ob, stdout);
            else if (data->map[i][j] == '1')
                fputc (data->space, stdout);
            else
                fputc (data->full, stdout);
        }
        fputc ('\n', stdout);
    }
}

int min_of_3(int a, int b, int c)
{
    if (a <= b && a <= c)
        return (a);
    else if (b <= a && b <= c)
        return (b);
    return (c);
}

void bsq (t_data *data)
{

    int map2[1000][1000] = {0};
    for (int y = 0; y < data->y; y++)
    {
        for (int x = 0; x < data->x; x++)
        {
            if (data->map[y][x] == '0')
                map2[y][x] = 0;
            else if (x == 0 || y == 0)
                map2[y][x] = 1;
            else
                map2[y][x] = 1 + min_of_3(map2[y - 1][x], map2[y][x - 1], map2[y - 1][x - 1]);
            if (map2[y][x] > data->bsq.size)
            {
                data->bsq.size = map2[y][x];
                data->bsq.x = x - map2[y][x] + 1;
                data->bsq.y = y - map2[y][x] + 1;
            }

        }
    }
	for (int j = 0; j < data->bsq.size; j++)
		for (int i = 0; i < data->bsq.size; i++)
			data->map[data->bsq.y + j][data->bsq.x + i] = '2';
}

void process_map (FILE *file)
{
    t_data data = {0};
    if (read_map(file, &data) == 1)
    {
        fprintf(stderr, "map error\n");
        return;
    }
    bsq(&data);
    printing(&data);
}


int main (int ac, char **av)
{
    if (ac == 1)
        process_map(stdin);
    else
    {
        for (int i = 1; i < ac ; i++)
        {
            FILE *file = fopen(av[i], "r");
            if (!file)
            {
                fprintf(stderr, "map error\n");
                continue;
            }
            process_map(file);
            fclose(file);
            if (i != ac - 1)
                fputc('\n', stdout);
        }
    }
    return (0);
}
