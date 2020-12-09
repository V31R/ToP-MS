#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <utility>
#include "vectors.h"
class Mapping {
public:
	Mapping(sf::Font & f, sf::Vector2f s, sf::Vector2f pos) :
		line{ sf::Lines,2 },
		font{ f },
		size{ s },
		position{ pos },
		thicknessAxis{ 3 },
		textDistance{ 45 },
		justDisplay{ false, false }
	{
		text.setFont(font);
		rect.setFillColor(sf::Color::Black);
		dataColor = sf::Color::Black;
		text.setCharacterSize(18);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2.f);
	}
	void make(VecD abc, VecD ord) {
		abcissa = abc;
		ordinata = ord;
		double max = 0;
		for (auto el : abc) {
			std::cout << el << " ";
			if (el > max) {
				max = el;
			}
		}
		std::cout << "\n";
		abcissa.push_back(max);
		abcissa.push_back(size.x / max);
		max = 0;
		for (auto el : ord) {
			std::cout << el << " ";
			if (el > max) {
				max = el;
			}
		}
		std::cout << "\n";
		std::cout << std::endl;
		ordinata.push_back(max);
		ordinata.push_back(size.y / max);

	}
	void setDisplayFlag(bool abc = false, bool ord = false) {
		justDisplay.first = abc;
		justDisplay.second = ord;
	}
	void setColor(sf::Color color) {
		dataColor = color;
	}
	virtual void draw(sf::RenderWindow & window) {

		rect.setPosition(position);
		rect.setSize(sf::Vector2f(thicknessAxis, size.y));
		window.draw(rect);
		sf::Vector2f temp{ position + sf::Vector2f{ 0, size.y } };
		rect.setPosition(temp);
		rect.setSize(sf::Vector2f(size.x, thicknessAxis));
		window.draw(rect);

	}
protected:
	std::pair<bool, bool> justDisplay;
	double textDistance;
	double thicknessAxis;
	sf::RectangleShape rect;
	sf::Color dataColor;
	sf::Font font;
	sf::Text text;
	sf::Vector2f size;
	VecD abcissa;
	VecD ordinata;
	sf::VertexArray line;
	sf::Vector2f position;
};
class Graphic :public Mapping {
public:
	Graphic(sf::Font & f, sf::Vector2f s, sf::Vector2f pos) :
		Mapping{ f, s, pos },
		line{ sf::Lines,2 },
		triangle{ thicknessAxis * 2,3 },
		displacement{ 0, 0 }
	{
		triangle.setFillColor(sf::Color::Black);

		triangle.setOrigin(sf::Vector2f(thicknessAxis * 2, 0));
	}
	void setDisplacement(double x = 0, double y = 0) {
		displacement.x = x;
		displacement.y = y;
	}
	void setDisplayFlag(bool abc = false, bool ord = false) {
		justDisplay.first = abc;
		justDisplay.second = ord;
	}
	void draw(sf::RenderWindow & window) {
		line[0].color = dataColor;
		line[1].color = dataColor;
		rect.setPosition(position - sf::Vector2f(0, thicknessAxis));
		rect.setSize(sf::Vector2f(thicknessAxis, size.y + displacement.y + thicknessAxis * 2));
		triangle.setRotation(0);
		triangle.setPosition(position + sf::Vector2f(thicknessAxis / 2, -thicknessAxis * 4));
		window.draw(rect);
		window.draw(triangle);
		sf::Vector2f temp{ position + sf::Vector2f{ 0, size.y + displacement.y + static_cast<float>(thicknessAxis) } };
		triangle.setRotation(90);
		triangle.setPosition(temp + sf::Vector2f(size.x + displacement.x + thicknessAxis * 4, +thicknessAxis / 2));
		rect.setPosition(temp);
		rect.setSize(sf::Vector2f(size.x + displacement.x + thicknessAxis, thicknessAxis));
		window.draw(rect);
		window.draw(triangle);
		for (int i{ 0 }; i < abcissa.size() - 3 && i < ordinata.size() - 3; i++) {
			line[0].position = temp + sf::Vector2f{ displacement.x + static_cast<float>(abcissa[i] * abcissa[abcissa.size() - 1]),-static_cast<float>(ordinata[i] * ordinata[ordinata.size() - 1]) };
			line[1].position = temp + sf::Vector2f{ displacement.x + static_cast<float>(abcissa[i + 1] * abcissa[abcissa.size() - 1]), -static_cast<float>(ordinata[i + 1] * ordinata[ordinata.size() - 1]) };
			window.draw(line);
		}
		float beforeLength{ 0 };
		if (!justDisplay.first) {
			rect.setSize(sf::Vector2f(2, thicknessAxis * 2));
			bool flag = false;
			for (int i{ 0 }; i < ((size.x) / textDistance); i++) {
				std::wostringstream value;
				value << i * textDistance / abcissa[abcissa.size() - 1];

				text.setString(value.str());
				sf::FloatRect rectangle = text.getLocalBounds();
				float displacementY = 0;
				if (!flag) {
					if (temp.x + static_cast<float>((i - 1) *textDistance) + displacement.x - rectangle.width / 3 + beforeLength > temp.x\
						+ static_cast<float>(i *textDistance) + displacement.x - rectangle.width / 3) {
						displacementY = rectangle.height + thicknessAxis;
						flag = true;
					}
				}
				else {
					flag = false;
				}
				text.setPosition(temp + sf::Vector2f{ static_cast<float>(i *textDistance) + displacement.x - rectangle.width / 3,static_cast<float>(thicknessAxis * 2) + displacementY });
				rect.setPosition(temp + sf::Vector2f{ static_cast<float>(i *textDistance) + displacement.x,static_cast<float>(thicknessAxis) });
				beforeLength = rectangle.width;
				window.draw(rect);
				window.draw(text);
			}
		}
		else {
			rect.setSize(sf::Vector2f(2, thicknessAxis * 2));
			for (int i{ 0 }; i < abcissa.size() - 2; i++) {
				std::wostringstream value;
				value << abcissa[i];
				text.setString(value.str());
				sf::FloatRect rectangle = text.getLocalBounds();
				text.setPosition(temp + sf::Vector2f{ static_cast<float>(abcissa[i] * abcissa[abcissa.size() - 1]) - rectangle.width / 3 + displacement.x,static_cast<float>(thicknessAxis) * 2 });
				rect.setPosition(temp + sf::Vector2f{ static_cast<float>(abcissa[i] * abcissa[abcissa.size() - 1]) - rect.getGlobalBounds().width / 2 + displacement.x, static_cast<float>(thicknessAxis) });
				window.draw(rect);
				window.draw(text);
			}
		}
		if (!justDisplay.second) {
			rect.setSize(sf::Vector2f(thicknessAxis * 2, 2));
			beforeLength = 0;
			for (int i{ 0 }; i < (size.y / textDistance); i++) {
				std::wostringstream value;
				value << i * textDistance / ordinata[ordinata.size() - 1];//ordinata[ordinata.size() - 2] - ordinata[ordinata.size() - 2] / static_cast<int>(size.y / textDistance)*(int(size.y / textDistance)-i);
				text.setString(value.str());
				sf::FloatRect rectangle = text.getLocalBounds();
				text.setPosition(temp - sf::Vector2f{ rectangle.width + rect.getGlobalBounds().width, static_cast<float>(i *textDistance) + rectangle.height / 3 * 2 - displacement.y });
				rect.setPosition(temp - sf::Vector2f{ rect.getGlobalBounds().width, static_cast<float>(i *textDistance) - displacement.y - rect.getGlobalBounds().height / 2 });
				beforeLength = rectangle.height;
				window.draw(rect);
				window.draw(text);
			}
		}
		else {
			rect.setSize(sf::Vector2f(thicknessAxis * 2, 2));
			for (int i{ 0 }; i < ordinata.size() - 2; i++) {
				std::wostringstream value;
				value << ordinata[i];
				text.setString(value.str());
				sf::FloatRect rectangle = text.getLocalBounds();
				text.setPosition(temp - sf::Vector2f{ rectangle.width + rect.getGlobalBounds().width,static_cast<float>(ordinata[i] * ordinata[ordinata.size() - 1]) + rectangle.height / 3 * 2 + displacement.y });
				rect.setPosition(temp - sf::Vector2f{ rect.getGlobalBounds().width,static_cast<float>(ordinata[i] * ordinata[ordinata.size() - 1]) + rect.getGlobalBounds().height / 2 + displacement.y });
				window.draw(rect);
				window.draw(text);
			}
		}

	}
protected:

	sf::Vector2f displacement;
	sf::CircleShape triangle;
	sf::VertexArray line;

};
class Histogram : public Mapping {
public:
	Histogram(sf::Font f, sf::Vector2f s, sf::Vector2f pos) :
		Mapping{ f, s, pos }
	{
		thicknessAxis = 2;
		rectPtr.setFillColor(sf::Color::Black);
		rect.setOutlineThickness(thicknessAxis);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Black);

	}
	void draw(sf::RenderWindow & window) {
		int quantity = abcissa.size() < ordinata.size() ? abcissa.size() - 2 : ordinata.size() - 2;
		float widthPost = size.x / quantity;
		rect.setSize(size + sf::Vector2f(quantity - 1 + thicknessAxis * 2, thicknessAxis));
		rect.setPosition(position);
		window.draw(rect);

		sf::Vector2f temp = position + sf::Vector2f(0, size.y + thicknessAxis * 2);
		if (!justDisplay.first) {
			rectPtr.setSize(sf::Vector2f(1, 8));
			rectPtr.setPosition(temp + sf::Vector2f(thicknessAxis - 1, -rectPtr.getGlobalBounds().height));
			window.draw(rectPtr);
			post.setFillColor(dataColor);
			for (int i{ 0 }; i < quantity; i++) {
				post.setSize(sf::Vector2f(widthPost, -ordinata[i] * ordinata[ordinata.size() - 1]));
				post.setPosition(temp + sf::Vector2f(i*widthPost + i + thicknessAxis, -thicknessAxis));
				window.draw(post);
				std::wostringstream value;
				value << abcissa[i];
				text.setString(value.str());
				text.setPosition(post.getPosition() + sf::Vector2f(post.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2, 0));
				window.draw(text);
				//if (i < quantity - 1) {
				rectPtr.setPosition(temp + sf::Vector2f((i + 1)*widthPost + i + thicknessAxis, -rectPtr.getGlobalBounds().height));
				window.draw(rectPtr);
				//}
			}
		}
		else {
			rectPtr.setSize(sf::Vector2f(1, 16));
			{
				std::wostringstream value;
				value << 0;
				text.setString(value.str());
				text.setPosition(temp + sf::Vector2f(-text.getGlobalBounds().width / 2 + thicknessAxis, thicknessAxis));
				window.draw(text);
				rectPtr.setPosition(temp + sf::Vector2f(thicknessAxis - 1, -rectPtr.getGlobalBounds().height / 4 * 3));
				window.draw(rectPtr);
			}
			post.setFillColor(dataColor);
			bool flag = false;
			double lastLength = text.getGlobalBounds().width;
			for (int i{ 0 }; i < quantity; i++) {
				post.setSize(sf::Vector2f(widthPost, -ordinata[i] * ordinata[ordinata.size() - 1]));
				post.setPosition(temp + sf::Vector2f(i*widthPost + i + thicknessAxis, -thicknessAxis));
				window.draw(post);
				std::wostringstream value;
				value << abcissa[i];
				text.setString(value.str());
				sf::FloatRect textRect = text.getGlobalBounds();
				double disY = 0;
				if (!flag) {
					if (temp.x + (i + 1)*widthPost + i + thicknessAxis - textRect.width / 2 < temp.x + (i + 1)*widthPost + i + thicknessAxis + lastLength / 2) {
						disY = textRect.height + thicknessAxis;
						flag = true;
					}
				}
				else {
					flag = false;
				}

				text.setPosition(temp + sf::Vector2f((i + 1)*widthPost + i + thicknessAxis - textRect.width / 2, thicknessAxis + disY));
				lastLength = textRect.width;
				window.draw(text);
				//if (i < quantity - 1) {
				rectPtr.setPosition(temp + sf::Vector2f((i + 1)*widthPost + i + thicknessAxis, -rectPtr.getGlobalBounds().height / 4 * 3));
				window.draw(rectPtr);
				//}
			}
		}
		rectPtr.setSize(sf::Vector2f(6, 2));
		if (!justDisplay.second) {
			for (int i{ 0 }; i < quantity; i++) {
				std::wostringstream value;
				value << ordinata[i];
				text.setString(value.str());
				sf::FloatRect rectangle = text.getLocalBounds();
				text.setPosition(temp - sf::Vector2f{ rectangle.width + rectPtr.getGlobalBounds().width,static_cast<float>(ordinata[i] * ordinata[ordinata.size() - 1]) + rectangle.height / 3 * 2 });
				rectPtr.setPosition(temp - sf::Vector2f{ rectPtr.getGlobalBounds().width,static_cast<float>(ordinata[i] * ordinata[ordinata.size() - 1]) + rectPtr.getGlobalBounds().height });
				window.draw(rectPtr);
				window.draw(text);
			}
		}
		else {
			sf::FloatRect lastRectangle{};
			double lastHeight = temp.y + text.getCharacterSize() * 4;
			for (int i{ 0 }; i < quantity; i++) {
				std::wostringstream value;
				value << ordinata[i];
				text.setString(value.str());
				sf::FloatRect rectangle = text.getGlobalBounds();

				text.setPosition(temp - sf::Vector2f{ rectangle.width + rectPtr.getGlobalBounds().width,static_cast<float>(ordinata[i] * ordinata[ordinata.size() - 1]) + rectangle.height / 3 * 2 });
				rectPtr.setPosition(temp - sf::Vector2f{ rectPtr.getGlobalBounds().width,static_cast<float>(ordinata[i] * ordinata[ordinata.size() - 1]) + rectPtr.getGlobalBounds().height });
				rectangle = text.getGlobalBounds();

				if (!(lastRectangle.intersects(rectangle))) {
					window.draw(rectPtr);
					window.draw(text);
					lastHeight = text.getPosition().y + rectangle.height;
				}
				lastRectangle = rectangle;
			}
		}
	}
protected:
	sf::RectangleShape rectPtr;
	sf::RectangleShape post;
};