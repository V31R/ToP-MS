#include "distributions.h"
#include "mapping.h"
#include <SFML/Graphics.hpp>

int main(){
	// ��� ��� ��������� ������������������
	//RandomVector generator{};
	//generator.generate();
	//generator.safe();
	sf::Font font{};
	font.loadFromFile("consola.ttf");

	Graphic graphic{ font, sf::Vector2f{ 350, 300 }, sf::Vector2f{ 50, 50 } };//�������� � ��������� �������
	graphic.setColor(sf::Color::Blue);
	graphic.setDisplacement(20);
	graphic.setDisplayFlag(true,true);

	Histogram histogram1{ font, sf::Vector2f{300, 300 }, sf::Vector2f{ 500, 50 } };//�������� � ��������� �����������
	histogram1.setDisplayFlag(true, true);
	histogram1.setColor(sf::Color(70,80,180));

	std::cout << "Task 1\n";
	SamplingDistribution task1{};
	task1.load();//��������� �������
	task1.make();//������� �������
	task1.outputProbs();//������� ����������� ���������� �������� ������ �������
	task1.outputNumber();//����� ������ � ������������� ������
	task1.calculateUnbiasedVarianceExpectedValue();//��������� ��� ��������
	task1.calculateUnbiasedVarianceEstimate();//��������� ���������
	
	graphic.make(vectorToAnotherType<VecI, VecD>(task1.variables), vectorToAnotherType<VecI,VecD>(task1.number));//���������� ���� �������

	std::cout << "Task 2\n";
	ExponentialDistribution task2;
	task2.load();//��������� �������
	task2.calculateExponential();//��������� ���������������� ��������
	task2.makeEdges();//������ ���������
	task2.make();//������� �������
	task1.outputNumber();//������� ��
	task2.calculateUnbiasedVarianceExpectedValue();//��������� ��� ��������
	task2.calculateUnbiasedVarianceEstimate();//��������� ���������
	

	histogram1.make(task2.edges, vectorToAnotherType<VecI, VecD>(task2.number));//���������� ���� �����������
	sf::ContextSettings settings;
	settings.antialiasingLevel=16;

	sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!",sf::Style::Default,settings);
	
	window.clear(sf::Color::White);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		graphic.draw(window);
		histogram1.draw(window);
		window.display();
	}

	return 0;
}