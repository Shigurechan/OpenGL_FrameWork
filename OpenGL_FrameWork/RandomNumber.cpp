#include "RandomNumber.hpp"
#include <locale.h>
#include <Random>
#include <iostream>

namespace FrameWork
{

	int GetRandom(int start, int end)
	{
		std::random_device rnd;                         // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());                         //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> Rand(start, end);    // [start, end] 範囲の一様乱数

		
		return Rand(mt);
	}

}