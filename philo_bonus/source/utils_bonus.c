/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:24:42 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/25 02:41:16 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	total_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((total_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

static size_t	count_char(int num)
{
	size_t	len;

	len = 1;
	if (num < 0)
		++len;
	while (num / 10)
	{
		num /= 10;
		++len;
	}
	return (len);
}

static int	minus_case(char *str, int *len, int *num)
{
	int	limit;

	limit = 0;
	if (*num < 0)
	{
		*str = '-';
		limit = 1;
		if (*num == -2147483648)
		{
			*num = (*num + 1) * -1;
			*(str + --(*len)) = '8';
			*num /= 10;
		}
		else
			*num *= -1;
	}
	return (limit);
}

static char	*ft_itoa(int num)
{
	int		len;
	char	*str;
	int		limit;

	len = count_char(num);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	*(str + len) = '\0';
	limit = minus_case(str, &len, &num);
	while (len > limit)
	{
		*(str + len - 1) = (num % 10) + '0';
		num = num / 10;
		--len;
	}
	return (str);
}

char	*individual_sem_name(const char *name, int num)
{
	char	*num_string;
	char	*new_name;

	num_string = ft_itoa(num);
	if (!num_string)
		return (NULL);
	new_name = ft_strjoin(name, num_string);
	free(num_string);
	if (!new_name)
		return (NULL);
	return (new_name);
}
