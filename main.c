// #include "sudoku.c"
#include "sudoku.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i;
	int j;
	int solution;
	int valid;
	int board[9][9] = {  
		{0, 0, 0, 0, 0, 0, 0, 0, 0} ,   
		{0, 0, 0, 0, 0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0, 0, 0, 0, 0} , 
		{0, 0, 0, 0, 0, 0, 0, 0, 0} 		
		};
	valid = 1;
	if(argc == 10)
	{
		i = 1;
		while (i <= 9)
		{
			j = 0;
			while (argv[i][j])
			{
				if (argv[i][j] >= '0' && argv[i][j] <= '9')
					board[i - 1][j] = argv[i][j] - 48;
				else if (argv[i][j] == '.')
					board[i - 1][j] = 0;
				else
					valid = 0;
				j++;
			}
			i++;
		}
	}
	if(valid)
	{
		solution = 0;
		ft_put_number(board, 0, 0, &solution);
		printf("%d\n", solution);
		if(solution == 1)
		{
			solution = 0;
			ft_print_number(board, 0, 0, &solution);
		}
		else
			ft_putstr("Error\n");
	}
	else
	{
		ft_putstr("Error\n");
	}
    return (0);
}