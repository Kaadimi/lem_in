/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:29:48 by ikadimi           #+#    #+#             */
/*   Updated: 2018/10/25 21:20:52 by ikadimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*s1;
	unsigned const char	*s2;
	int					i;

	s1 = dst;
	s2 = src;
	if (s1 < s2)
	{
		i = 0;
		while (0 < len--)
		{
			*(s1 + i) = *(s2 + i);
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i >= 0)
		{
			*(s1 + i) = *(s2 + i);
			i--;
		}
	}
	return (s1);
}
