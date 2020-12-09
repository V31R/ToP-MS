#pragma once
#include <vector>

typedef std::vector<double> VecD;//������ ��� double
typedef std::vector<double> VecI;//������ ��� int

VecI doubleVectorToIneteger(VecD vec) {//������� ������� ���� double � ������ int
	VecI result;
	result.resize(vec.size());
	for (int i{ 0 }; i < vec.size(); i++) {
		result[i] = vec[i];
	}
	return result;
}
VecD integerVectorToDouble(VecI vec) {//
	VecD result;
	result.resize(vec.size());
	for (int i{ 0 }; i < vec.size(); i++) {
		result[i] = vec[i];
	}
	return result;
}
VecI addZeroToStart(VecD vec) {//
	VecI result;
	result.resize(vec.size() + 1);
	result[0] = 0;
	for (int i{ 0 }; i < vec.size(); i++) {
		result[i + 1] = vec[i];
	}
	return result;
}