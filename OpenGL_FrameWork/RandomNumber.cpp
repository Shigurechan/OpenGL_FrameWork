#include "RandomNumber.hpp"
#include <locale.h>
#include <Random>
#include <iostream>

namespace FrameWork
{

	int GetRandom(int start, int end)
	{
		std::random_device rnd;                         // �񌈒�I�ȗ���������𐶐�
		std::mt19937 mt(rnd());                         //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
		std::uniform_int_distribution<> Rand(start, end);    // [start, end] �͈͂̈�l����

		
		return Rand(mt);
	}

}