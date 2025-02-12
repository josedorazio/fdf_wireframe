/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:37:22 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/12 19:02:31 by jdorazio         ###   ########.fr       */
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
	while (index < len)
	{
		if (!ft_isdigit(num[index]))
			return (0);
		index++;
	}
	return (1);
}

int	convert(char *npt)
{
	int	num;

	num = 0;
	if (!validate(npt))
		terminate(5, npt);
	if (*npt != '\0' || *npt != ' ')
		num = ft_atoi(npt);
	return (num);
}
