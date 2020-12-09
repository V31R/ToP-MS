#pragma once
#include <vector>

typedef std::vector<double> VecD;//вектор для double
typedef std::vector<double> VecI;//вектор для int

VecI doubleVectorToIneteger(VecD vec) {//перевод вектора типа double в вектор int
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