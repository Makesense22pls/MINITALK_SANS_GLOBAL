/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:20:42 by mafourni          #+#    #+#             */
/*   Updated: 2024/05/24 19:24:16 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

int	ft_sig(int sig, int i, int result)
{
	if (sig == SIGUSR1)
		result |= (1 << i);
	return (result);
}

int	print(char *str, int len_str_index, int *count_len)
{
	str[len_str_index] = '\0';
	ft_printf("STRING AFFICHÉ =%s=\n", str);
	free(str);
	str = NULL;
	len_str_index = 0;
	*count_len = 63;
	return (len_str_index);
}
// static int		i = 7; 0
// static int		count_len = 63; 1
// static size_t	len_str_index = 0; 2

void	signal_handler(int sig)
{
	static int		array[3] = {7, 63, 0};
	static char		result = 0;
	static char		*str = NULL;

	if (array[1] >= 0)
	{
		array[2] = ft_sig(sig, array[1], array[2]);
		if (--array[1] == -1)
		{
			str = malloc(array[2] + 1);
			array[2] = 0;
		}
	}
	else
	{
		result = ft_sig(sig, array[0], result);
		if (--array[0] != -1)
			return ;
		if (result != '\0')
			str[array[2]++] = result;
		else
			array[2] = print(str, array[2], &array[1]);
		result = 0;
		array[0] = 7;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("MAFOURNI'S MINITALK\n");
	ft_printf("PID OF SERV = %d\n", getpid());
	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
	{
		pause();
	}
}

// void	signal_handler(int sig)
// {
// 	if (glob.count_len >= 0)
// 	{
// 		glob.len_str_index = ft_sig(sig,glob.count_len, glob.len_str_index);
// 		if (--glob.count_len == -1)
// 		{
// 			glob.str = malloc(glob.len_str_index + 1);
// 			glob.len_str_index = 0;
// 		}
// 	}
// 	else
// 	{
// 		glob.result = ft_sig(sig, glob.i, glob.result);
// 		if (--glob.i != -1)
// 			return ;
// 		if (glob.result != '\0')
// 			glob.str[glob.len_str_index++] = glob.result;
// 		else
// 		{
// 			glob.len_str_index = print(glob.str, glob.len_str_index);
// 			glob.count_len = 63;
// 		}
// 		glob.result = 0;
// 		glob.i = 7;
// 	}
// }

// int	main(void)
// {
// 	struct sigaction	action;

// 	ft_printf("MAFOURNI'S MINITALK\n");
// 	ft_printf("PID OF SERV = %d\n", getpid());
// 	action.sa_handler = signal_handler;
// 	sigemptyset(&action.sa_mask);
// 	action.sa_flags = 0;
// 	sigaction(SIGUSR1, &action, NULL);
// 	sigaction(SIGUSR2, &action, NULL);
// 	while (1)
// 	{
// 		pause();
// 	}
// }
