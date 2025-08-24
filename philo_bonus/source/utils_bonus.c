/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:24:42 by mansargs          #+#    #+#             */
/*   Updated: 2025/08/24 13:32:55 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	total_len;
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc((total_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[++j])
		res[i++] = s1[j];
	j = -1;
	while (s2[++j])
		res[i++] = s2[j];
	res[i] = '\0';
	return (res);
}

char	*ft_itoa(int num)
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
