#include "distributions.h"
#include "mapping.h"
#include <SFML/Graphics.hpp>

int main(){
	//RandomVector test2{};
	//test2.generate();
	//test2.safe();
	sf::Font font{};
	font.loadFromFile("consola.ttf");
	Graphic graphic{ font, sf::Vector2f{ 250, 200 }, sf::Vector2f{ 150, 150 } };
	graphic.setColor(sf::Color::Blue);
	graphic.setDisplacement(20);
	graphic.setDisplayFlag(true,true);

	//Histogram histogram{ font, sf::Vector2f{ 300, 250 }, sf::Vector2f{ 150, 150 } };
	//histogram.setColor(sf::Color::Cyan);
	//RandomVector test{};
	////test.generate();
	////test.safe();
	//test.load();
	//test.output();
	SamplingDistribution test{};
	test.load();
	test.make();
	test.outputProbs();
	test.outputNumber();
	test.calculateUnbiasedVarianceExpectedValue();
	test.calculateUnbiasedVarianceEstimate();
	VecD t;
	t.push_back(0);
	t.push_back(1);
	t.push_back(2);
	t.push_back(3);
	graphic.make(t,integerVectorToDouble(test.number));
	//histogram.make(t, integerVectorToDouble(test.number));
	ExponentialDistribution test1;
	test1.load();
	test1.calculateExponential();
	test1.makeEdges();
	test1.make();
	test1.calculateUnbiasedVarianceExpectedValue();
	test1.calculateUnbiasedVarianceEstimate();
	Histogram histogram1{ font, sf::Vector2f{ 400, 500 }, sf::Vector2f{ 100, 10 } };
	histogram1.setDisplayFlag(true,true);
	histogram1.setColor(sf::Color::Cyan);

	histogram1.make(test1.edges, integerVectorToDouble(test1.number));
	sf::ContextSettings settings;
	settings.antialiasingLevel=16;
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!",sf::Style::Default,settings);
	
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
		//histogram.draw(window);
		//histogram1.draw(window);
		window.display();
	}

	return 0;
	getchar();
	return 0;
}