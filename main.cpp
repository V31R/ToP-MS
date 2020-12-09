#include "distributions.h"
#include "mapping.h"
#include <SFML/Graphics.hpp>

int main(){
	// код для генерации последовательности
	//RandomVector generator{};
	//generator.generate();
	//generator.safe();
	sf::Font font{};
	font.loadFromFile("consola.ttf");

	Graphic graphic{ font, sf::Vector2f{ 350, 300 }, sf::Vector2f{ 50, 50 } };//создание и настройка графика
	graphic.setColor(sf::Color::Blue);
	graphic.setDisplacement(20);
	graphic.setDisplayFlag(true,true);

	Histogram histogram1{ font, sf::Vector2f{300, 300 }, sf::Vector2f{ 500, 50 } };//создание и настройка гистограммы
	histogram1.setDisplayFlag(true, true);
	histogram1.setColor(sf::Color(70,80,180));

	std::cout << "Task 1\n";
	SamplingDistribution task1{};
	task1.load();//загружаем выборку
	task1.make();//считаем частоты
	task1.outputProbs();//выводим вероятности полученные согласно цифрам зачётки
	task1.outputNumber();//вывод частот и отночительных частот
	task1.calculateUnbiasedVarianceExpectedValue();//вычисляем мат ожидание
	task1.calculateUnbiasedVarianceEstimate();//вычисляем дисперсию
	
	graphic.make(vectorToAnotherType<VecI, VecD>(task1.variables), vectorToAnotherType<VecI,VecD>(task1.number));//заполнение осей графика

	std::cout << "Task 2\n";
	ExponentialDistribution task2;
	task2.load();//загружаем выборку
	task2.calculateExponential();//вычисляем экспоненциальных значений
	task2.makeEdges();//создаём интервалы
	task2.make();//считаем частоты
	task1.outputNumber();//выводим их
	task2.calculateUnbiasedVarianceExpectedValue();//вычисляем мат ожидание
	task2.calculateUnbiasedVarianceEstimate();//вычисляем дисперсию
	

	histogram1.make(task2.edges, vectorToAnotherType<VecI, VecD>(task2.number));//заполнение осей гистограммы
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
