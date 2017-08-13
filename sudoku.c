/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnugroho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:56:45 by rnugroho          #+#    #+#             */
/*   Updated: 2017/08/13 17:56:47 by rnugroho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_putstr(char *str)
{
	char *c;

	c = str;
	while (*c != '\0')
	{
		ft_putchar(*c);
		c++;
	}
}

int		ft_check_number(int board[9][9], int row, int col, int number)
{
	int i;
	int j;
	int base_row;
	int base_col;
	int exist;

	exist = 0;
	base_row = (row / 3) * 3;
	base_col = (col / 3) * 3;
	i = base_row;
	while (i < base_row + 3)
	{
		j = base_col;
		while (j < base_col + 3)
		{
			if (board[i][j] == number)
			{
				exist = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (exist);
}

int		ft_is_available(int board[9][9], int row, int col, int number)
{
	int i;

	if (ft_check_number(board, row, col, number))
		return (0);
	i = 0;
	while (i < 9)
	{
		if (board[i][col] == number)
			return (0);
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (board[row][i] == number)
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_board(int board[9][9])
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			if (j > 0)
				ft_putchar(' ');
			ft_putchar(board[i][j] + '0');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	ft_count_posibilities(int board[9][9], int row, int col, int *heu)
{
	int i;
	int posib;

	i = 1;
	posib = 0;
	while (i <= 9)
	{
		if (board[row][col] != 0)
			posib = 10;
		else if (ft_is_available(board, row, col, i))
			posib++;
		i++;
	}
	if (heu[2] > posib)
	{
		heu[2] = posib;
		heu[0] = row;
		heu[1] = col;
	}
}

int		ft_mcv_heuristic(int board[9][9], int *row, int *col)
{
	int	heu[3];
	int	i;
	int	j;

	heu[0] = 0;
	heu[1] = 0;
	heu[2] = 10;
	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			ft_count_posibilities(board, i, j, heu);
			j++;
		}
		i++;
	}
	*row = heu[0];
	*col = heu[1];
	return (heu[2]);
}

int		ft_put_number(int board[9][9], int row, int col, int *solution)
{
	int number;

	if (ft_mcv_heuristic(board, &row, &col) == 10)
		return (1);
	number = 1;
	while (number <= 9)
	{
		if (ft_is_available(board, row, col, number))
		{
			board[row][col] = number;
			if (ft_put_number(board, row, col, solution))
			{
				*solution = *solution + 1;
			}
			if (*solution < 2)
				board[row][col] = 0;
		}
		number++;
	}
	return (0);
}

int		ft_print_number(int board[9][9], int row, int col, int *solution)
{
	int number;

	if (ft_mcv_heuristic(board, &row, &col) == 10)
		return (1);
	number = 1;
	while (number <= 9)
	{
		if (ft_is_available(board, row, col, number))
		{
			board[row][col] = number;
			if (ft_print_number(board, row, col, solution))
			{
				*solution = *solution + 1;
				ft_print_board(board);
			}
			if (*solution == 0)
				board[row][col] = 0;
		}
		number++;
	}
	return (0);
}
