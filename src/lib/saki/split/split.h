/**
* @file split.h
* @brief •¶š—ñ‚Ì•ªŠ„
* @author ÎR —I
* @date 2018/12/14
*/
#pragma once
#ifndef SAKI_SPLIT_2018_12_14
#define SAKI_SPLIT_2018_12_14
#include <string>
#include <sstream>
#include <vector>

namespace saki
{
	/**
	* @brief stringŒ^‚ğ‹æØ‚Á‚½‚à‚Ì‚ğvector‚Å•Ô‚·
	* @param str ‹æØ‚é‘ÎÛ‚Ì•¶š—ñ
	* @param separation ‹æØ‚è•¶š
	* @return ‹æØ‚Á‚½•¶š—ñ‚ğŠi”[‚·‚évectorƒNƒ‰ƒX
	*/
	std::vector<std::string> split(std::string str, const char separation)
	{
		//‹æØ‚Á‚½•¶š—ñ‚ğŠi”[
		std::vector<std::string> str_list;
		std::stringstream ss(str);
		std::string buffer;
		//ƒpƒX‚ğ/‚²‚Æ‚É‹æØ‚é
		while (std::getline(ss, buffer, '/'))
		{
			str_list.push_back(buffer);
		}
		return str_list;
	}
}
#endif //SAKI_SPLIT_2018_12_14