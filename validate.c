/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:37:22 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/09 20:42:55 by jdorazio         ###   ########.fr       */
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


int	ft_atoi_base(char *color_str)
{
	int	i;
	int	result;
	char	c;

	i = 0;
	result = 0;
	if (!color_str)
		return (0xFFFFFF);
	if (color_str[0] == '0' && (color_str[1] == 'x' || color_str[1] == 'X'))
		i = 2;
	while (color_str[i])
	{
		c = ft_tolower(color_str[i]);
		if (c >= '0' && c <= '9')
			result = (result * 16) + (c - '0');
		else if (c >= 'a' && c <= 'f')
			result = (result * 16) + (c - 'a' +  10);
		else
			break;
		i++;
	}
	return (result);
}

void	convert(char *str, int *z, int *color)
{
	char	**input;

	input = ft_split(str, ',');
	if (!input || !input[0])
		terminate(1, NULL);
	if (!validate(input[0]))
		terminate(1, NULL);// CAMBIAR LUEGO
	*z = ft_atoi(input[0]);
	if (input[1])
		*color = ft_atoi_base(input[1]);
	else
		*color = 0xFFFFFF;
	free_array(input);
}
