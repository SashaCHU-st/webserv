/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:22:19 by alli              #+#    #+#             */
/*   Updated: 2024/12/17 13:03:09 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

std::vector<std::string> Utils::splitStr(const std::string& str, std::string delim) {
	std::vector<std::string> newList;
	std::string item;
	int length = str.length();
	int start = 0;
	int end = 0;
	
	if (length == 0)
		return newList;
	while (end < length)
	{
		if (str.find(delim))
		{
			item = str.substr(start, end - start);
			newList.push_back(item);
			start = end + 1;
		}
		end++;
	}
	newList.push_back(str.substr(start)); // adds the last element from the string
	return newList;
}