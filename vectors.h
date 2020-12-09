#pragma once
#include <vector>

typedef std::vector<double> VecD;//вектор для double
typedef std::vector<double> VecI;//вектор для int
template <typename T1, typename T2>
T2 vectorToAnotherType(T1 vec) {//перевод вектора  T1 в вектор T2
	T2 result;
	result.resize(vec.size());
	for (int i{ 0 }; i < vec.size(); i++) {
		result[i] = vec[i];
	}
	return result;
}

VecI addZeroToStart(VecD vec) {//добавление нуля в начало вектора
	VecI result;
	result.resize(vec.size() + 1);
	result[0] = 0;
	for (int i{ 0 }; i < vec.size(); i++) {
		result[i + 1] = vec[i];
	}
	return result;
}