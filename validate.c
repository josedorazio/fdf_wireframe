/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:37:22 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 15:59:44 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	ft_is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	validate(char *num)
{
	int	len;
	int	index;

	if (ft_is_sign(*num))
		num++;
	len = ft_strlen(num);
	while (len > 0 && (num[len - 1] == ' ' || num[len -1] == '\n') && num != NULL)
		len--;
	if (len > 0)
		num[len] = '\0';
	index = 0;
	while(index < len)
	{
		if (!ft_isdigit(num[index]))
			return (0);
		index++;
	}
	return (1);
}

int	hexa(char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	if (!str)
		return (0xFFFFFF);
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		result *= 16;
		if (str[i] >= '0' && str[i]  <= '9')
			result += str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += str[i] - 'a' + 10;
		else
			return (0xFFFFFF);
	}
	return (result);

}

void	convert(char *str, int *z, int *color)
{
	char	**input;

	input = ft_split(str, ',');
	if (!input || !input[0])
		terminate(1, NULL); // CAMBIAR LUEGO
	if (!validate(input[0]))
		terminate(1, NULL);// CAMBIAR LUEGO
	*z = ft_atoi(input[0]);
	if (input[1])
		*color = hexa(input[1]);
	else
		*color = 0xFFFFFF;
	free_array(input);
}
