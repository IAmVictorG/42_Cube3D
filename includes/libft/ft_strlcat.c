/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victo <victo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:18:35 by fcoindre          #+#    #+#             */
/*   Updated: 2023/07/20 09:35:36 by victo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	remaing;

	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size >= 0 && size < destlen)
		return (size + srclen);
	if (destlen == size)
		return (destlen + srclen);
	while (*dest != '\0')
		dest++;
	remaing = size - destlen;
	while (remaing > 1 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		remaing--;
	}
	*dest = '\0';
	return (destlen + srclen);
}
