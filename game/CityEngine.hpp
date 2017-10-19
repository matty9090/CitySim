#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>

#include "Net.hpp"
#include "EngineInterface.hpp"

class CityEngine {
	public:
		CityEngine(EngineInterface *renderer);

		void update(float dt);

	private:
		EngineInterface *renderer;
		std::shared_ptr<Net> net;

		std::map<std::string, double> sValues;
		std::map<std::string, double> dValues;

		std::shared_ptr<City::CityMap<City::Tile>> map_ground;
		std::shared_ptr<City::CityMap<City::Building>> map_build;
		std::shared_ptr<City::CityMap<City::Tile>> map_zones;

		enum MapLayers { Ground, Build, Zones };

		void initMaps();
		void initValues();

		float speed, counter;

	public:
		

	private:
		
};