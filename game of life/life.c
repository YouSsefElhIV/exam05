#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{

    if (argc == 4)
    {
        /*                   init block                      */
        
        int w = atoi(argv[1]);
        int h = atoi(argv[2]);
        char board[h][w];
        char instructions[1000];
        int it = atoi(argv[3]);
        int i = 0;
        int j = 0;
        int k = 0;
        int print = 0;
        int neighbor_count = 0;
    
        int bytes = read(0, instructions, 998);
        if (bytes <= 0)
            return (0);
        instructions[bytes] = '\0';
    
        for (i = 0; i < h; i++)
        {
            for (j = 0; j < w; j++)
            {
                board[i][j] = ' ';
            }
        }
        i = 0;
        j = 0;

        for (k = 0; k < bytes; k++)
        {
            if (instructions[k] == 'd')
                j++;
            else if (instructions[k] == 'a')
                j--;
            else if (instructions[k] == 'w')
                i--;
            else if (instructions[k] == 's')
                i++;
            else if (instructions[k] == 'x')
                print = !print;
            if (print == 1 && i >= 0 && i < h && j >= 0 && j < w)
                board[i][j] = '0';
        }
        
        /*                   game of life block                      */
        for (k = 0; k < it; k++)
        {
            for (i = 0; i < h; i++)
            {
                for (j = 0; j < w; j++)
                {
                    neighbor_count = 0;
                    // 1-    calculating the neighbors.
                    for (int x = -1; x < 2; x++)
                    {
                        for (int y = -1; y < 2; y++)
                        {
                            if (x == 0 && y == 0)
                                continue;
                            int x_pos = i + x;
                            int y_pos = j + y;
                            if (x_pos >= 0 && x_pos < h && y_pos >= 0 && y_pos < w)
                            {
                                if (board[x_pos][y_pos] == '0' || board[x_pos][y_pos] == '1')
                                    neighbor_count++;
                            }
                        }
                    }
                    // 2-          // curr block is it alive or dead?
                                    //alive ---->> should it survive or not
                                    //dead  ---->> should it resurect or not
                    if (board[i][j] == '0')
                    {
                        if (neighbor_count <= 1 || neighbor_count >= 4)
                            board[i][j] = '1';
                    }
                    else
                    {
                        if (neighbor_count == 3)
                            board[i][j] = 'n';
                    }
                }
            }
            for (int ii = 0; ii < h; ii++)
            {
                for (int jj = 0; jj < w; jj++)
                {
                    if (board[ii][jj] == '1')
                        board[ii][jj] = ' ';
                    else if (board[ii][jj] == 'n')
                        board[ii][jj] = '0';
                }
            }
            // break ;
        }
        
        //*1*
        //*0*
        //*1*
        // top left = (j-1, i-1), bottom right(j+1, i+1), top right = (j-1, i+1)  bottom left = (j+1, i-1).
        
        
        
        
        /*                   printng block                      */

        for (i = 0; i < h; i++)
        {
            for (j = 0; j < w; j++)
            {
                putchar(board[i][j]);
            }
            putchar('\n');
        }
    }
    return (0);
}
