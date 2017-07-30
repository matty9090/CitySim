#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "SpriteHandler.hpp"
#include "IsoEngine.hpp"


class Gui {
	private:
		typedef void (Gui::*Action)();

		class GuiElement {
			public:
				virtual void render(std::shared_ptr<sf::RenderWindow> app) = 0;
				virtual void update(float dt, sf::Vector2u mouse) = 0;

			protected:
				IsoEngine::Coord<float> position;
				GuiElement(IsoEngine::Coord<float> pos) : position(pos), action(nullptr) {}

				Action action;
			};

		class GuiButton : public GuiElement {
			public:
				GuiButton(IsoEngine::Coord<float> coord, sf::Sprite &sn, sf::Sprite &sh);

				void render(std::shared_ptr<sf::RenderWindow> app);
				void update(float dt, sf::Vector2u mouse);

			private:
				bool hover;
				sf::Sprite spr, spr_hover;
		};

	public:
		Gui(std::shared_ptr<SpriteHandler> sprHandler, std::shared_ptr<sf::RenderWindow> app);

		void render(float dt);

	private:
		std::shared_ptr<sf::RenderWindow> app;
		std::shared_ptr<SpriteHandler> sprHandler;
		std::vector<std::shared_ptr<GuiElement>> elements;

		std::shared_ptr<GuiElement> createElement(std::string name, IsoEngine::Coord<float> pos);
};
	