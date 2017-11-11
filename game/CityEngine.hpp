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

		long pop;
		float speed, counter;

		enum MapLayers { Ground, Build, Zones };

		std::shared_ptr<City::CityMap<City::Tile>> map_ground;
		std::shared_ptr<City::CityMap<City::Tile>> map_build;

		City::Coord<int> center;

		std::shared_ptr<City::RoadNetwork> roadNetwork;
		std::vector<City::RoadNetwork::RoadNode> topRoads;

		void initMaps();
		void initValues();
		
		void createRoadBetween(City::RoadNetwork::RoadNode n1, City::RoadNetwork::RoadNode n2);
		void setTile(int x, int y, std::string tile, int layer = 1);

	public:
		void expandRoads();
		void updateRoadNetwork(City::RoadNetwork::RoadNode node);

	private:
		
};