#pragma once
#include "vectors.h"
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>

const int Quantity = 10000;
//142
const int i = 1;
const int j = 4;
const int k = 2;
const int NumberInList = 6;
//�0 = i / 2 * (i + j + k), �1 = (j + k) / 2 * (i + j + k), �2 = (i + k) / 2 * (i + j + k), �3 = j / 2 * (i + j + k)
class RandomVector {//����� ��� ���������, �������� � ���������� ��������� ������������������ �������� �� 0 �� 1
public:
	VecD data;
	RandomVector() :
		randDev{},
		generator{ randDev() },
		dis{ 0.0 , 1.0 }
	{
		data.resize(Quantity);
	}
	void generate() {
		for (int i{ 0 }; i < data.size(); i++) {
			data[i] = dis(generator);
		}
	}
	void output() {
		for (int i{ 0 }; i < data.size(); i++) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}
	void load() {
		std::ifstream in{ "data" };
		for (int i{ 0 }; i < data.size() && !in.eof(); i++) {
			in >> data[i];
		}
		in.close();
	}
	void safe() {
		std::ofstream out{ "data" };
		for (int i{ 0 }; i < data.size(); i++) {
			out << data[i] << " ";
		}
		out.close();
	}
private:
	std::random_device randDev;
	std::mt19937 generator;//����� �������� 
	std::uniform_real_distribution<> dis;
};
class Distribution {//������������ ����� ��� ���������� ����������� ������������� � ���������� ������
public:
	RandomVector randomVec;
	VecD edges;
	VecI number;
	Distribution():
		randomVec{},
		Mx_{ 0 },
		S_{ 0 }
	{}
	void load() {
		randomVec.load();
	}
	virtual void make() {//����������� ������� ���������� ������
		for (int i{ 0 }; i < randomVec.data.size(); i++) {
			for (int j{ 0 }; j < edges.size(); j++) {
				if (randomVec.data[i] < edges[j]) {
					number[j]++;
					break;
				}
			}
		}
	}
	virtual void calculateUnbiasedVarianceExpectedValue() {//����������� ������� ���������� ������������ ��������������� ��������
		Mx_ = 0;
		for (int i{ 0 }; i < randomVec.data.size(); i++) {
			Mx_ += randomVec.data[i];
		}
		Mx_ /= Quantity;
		std::cout << Mx_ << std::endl;
	}
	virtual void calculateUnbiasedVarianceEstimate() {//����������� ������� ���������� ����������� ���������
		/*�� ������� ������������ ���������� ���������*/
		S_ = 0;
		for (int i{ 0 }; i < randomVec.data.size(); i++) {
			S_ += (randomVec.data[i] - Mx_)*(randomVec.data[i] - Mx_);
		}
		S_ /= Quantity - 1;
		std::cout << S_ << std::endl;
	}
	void generate() {
		randomVec.generate();
		randomVec.safe();
	}
	void outputNumber() {
		for (int i{ 0 }; i < number.size(); i++) {
			std::cout << number[i] << " ";
		}
		std::cout << std::endl;

		for (int i{ 0 }; i < number.size(); i++) {
			std::cout << static_cast<double>(number[i]) / Quantity << " ";
		}
		std::cout << std::endl;
	}
protected:

	double Mx_;
	double S_;
};
class SamplingDistribution:public Distribution {// ����� ��� ����������� ������������� ���������� ��������
public:
	VecI variables;
	SamplingDistribution() :
		Distribution{}		
	{
		variables.resize(4);//������ ��� �������� ���������� ��������� ��������
		for (int i{ 0 }; i < variables.size(); i++) {
			variables[i] = i;
		}
		dataOut.resize(Quantity);//������ ��� ����������� � ������ �������� ��������� �������� �� �������
		for (int i{ 0 }; i < dataOut.size(); i++) {
			dataOut[i] = 0;
		}

		probability.resize(4);//��������� ������� ������������� �������� ��������
		probability[0] = static_cast<double>(i) / (2 * (i + j + k));
		probability[1] = static_cast<double>(j + k) / (2 * (i + j + k));
		probability[2] = static_cast<double>(i + k) / (2 * (i + j + k));
		probability[3] = static_cast<double>(j) / (2 * (i + j + k));

		edges.resize(probability.size());//���������� ������� ������ ���������� ��� ���������� ������

		edges[0] = probability[0];
		for (int i{ 1 }; i < probability.size(); i++) {
			edges[i] = edges[i - 1] + probability[i];
		}

		number.resize(probability.size());//������ ��� ������
		for (int i{ 0 }; i < number.size(); i++) {
			number[i] = 0;
		}
	}
	void make() {//������� ������ � ����������� ��������
		for (int i{ 0 }; i < randomVec.data.size(); i++) {
			for (int j{ 0 }; j < edges.size(); j++) {
				if (randomVec.data[i] < edges[j]) {
					dataOut[i] = variables[j];
					number[j]++;
					break;
				}
			}
		}
	}
	
	void calculateUnbiasedVarianceExpectedValue() {//���������� ������������ ��������������� ��������
		Mx_ = 0;
		for (int i{ 0 }; i < dataOut.size(); i++) {
			Mx_ += dataOut[i] * randomVec.data[i];
		}
		Mx_ /= Quantity;
		std::cout << Mx_ << std::endl;
	}
	void calculateUnbiasedVarianceEstimate() {
		/*�� ������� ������������ ���������� ���������,
		�� ��-�� ��������� ����������� � ������� ����� � ��������� ������ ������������� �����������,
		������� �������� ����� M(x^2)-(M(x))^2*/
		//S_ = 0;
		//for (int i{ 0 }; i < dataExp.size(); i++) {
			//S_ += (dataExp[i] - Mx_)*(dataExp[i] - Mx_);
		//}
		//S_ /= Quantity - 1;
		double m_ = 0;
		for (int i{ 0 }; i < randomVec.data.size(); i++) {
			m_ += randomVec.data[i] * dataOut[i] * dataOut[i];
		}
		m_ /= Quantity;
		S_ = m_ - Mx_ * Mx_;
		std::cout << S_ << std::endl;
	}
	
	void outputProbs() {
		for (int i{ 0 }; i < probability.size(); i++) {
			std::cout << probability[i] << " ";
		}
		std::cout << std::endl;
	}
protected:
	VecD probability;
	VecI dataOut;
};
class ExponentialDistribution: public Distribution {
public:
	ExponentialDistribution() :
		Distribution{} 
	{}
	
	void calculateExponential() {//���������� ���������������� ��������
		double coef = -1 / (NumberInList / 4.);
		dataExp.resize(randomVec.data.size());
		for (int i{ 0 }; i < dataExp.size(); i++) {
			dataExp[i] = coef * log(randomVec.data[i]);
		}
	}
	void make() {//���������� ������ 
		for (int i{ 0 }; i <dataExp.size(); i++) {
			for (int j{ 0 }; j < edges.size(); j++) {
				if (dataExp[i] < edges[j]) {
					number[j]++;
					break;
				}
			}
		}
	}
	void makeEdges() {//���������� ������ ����������
		double min{ dataExp[0] }, max{ dataExp[0] };
		for (int i{ 1 }; i < dataExp.size(); i++) {//������� ������������ � ����������� ��������
			if (dataExp[i] > max) {
				max = dataExp[i];
			}
			else if (dataExp[i] < min) {
				min = dataExp[i];
			}
		}
		double diff = max - min;
		double h = diff/6;//������ ���������

		edges.resize(7);//���������� ������� ����������� �� ���� �������� ������, ����� ������� ������������ �������
		edges[0] = h;
		std::cout << min << " " << max << " "<<diff<<" " << h << std::endl;
		for (int i{ 1 }; i<edges.size();i++) {
			edges[i] = edges[i - 1] + h;
		}
		number.resize(edges.size());
	}
	void calculateUnbiasedVarianceExpectedValue() {//���������� ��� �������� ��� �������� ���������������
		Mx_ = 0;
		for (int i{ 0 }; i < dataExp.size(); i++) {
			Mx_ += dataExp[i];
		}
		Mx_ /= Quantity;
		std::cout << Mx_ << std::endl;
	}
	void calculateUnbiasedVarianceEstimate() {//���������� ���������
		double m_ = 0;
		for (int i{ 0 }; i < dataExp.size(); i++) {
			m_ += dataExp[i]*dataExp[i];
		}
		m_ /= Quantity;
		//S_ = 0;
		//for (int i{ 0 }; i < dataExp.size(); i++) {
			//S_ += (dataExp[i] - Mx_)*(dataExp[i] - Mx_);
		//}
		//S_ /= Quantity - 1;
		S_ = m_ - Mx_ * Mx_;
		std::cout << S_ << std::endl;
	}
protected:
	VecD dataExp;
};