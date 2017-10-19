#include "IsoEngine.hpp"

#include <iostream>

using namespace sf;
using namespace std;
using namespace City;

IsoEngine::IsoEngine(const SpriteHandler &_spr, std::shared_ptr<RenderWindow> _app)
	: sprHandler(_spr)
{
	app = _app;

	tiles["grass"]		= { sprHandler.create("grass") };
	tiles["pavement"]	= { sprHandler.create("pavement") };
	tiles["building1"]	= { sprHandler.create("building1") };
	tiles["building2"]  = { sprHandler.create("building2") };
	tiles["building3"]  = { sprHandler.create("building3") };
	tiles["zone_res"]	= { sprHandler.create("zone_res") };
	tiles["road_v"]		= { sprHandler.create("road_v") };
	tiles["road_h"]		= { sprHandler.create("road_h") };
	tiles["road_t"]		= { sprHandler.create("road_t") };
	tiles["road_b"]		= { sprHandler.create("road_b") };

	map_layers.push_back(make_shared<IsoMap>(13, 13));
	map_layers.push_back(make_shared<IsoMap>(13, 13));
	map_layers.push_back(make_shared<IsoMap>(13, 13, false));

	offset = origin(map_layers[Ground]);

	//for (int y = 0; y < map_layers[Ground]->getH(); y++)
	//	for (int x = 0; x < map_layers[Ground]->getW(); x++)
	//		setTile(Coord<int>(x, y), "grass");
}

void IsoEngine::render() {
	for (int y = 0; y < map_layers[Ground]->getH(); y++) {
		for (int x = 0; x < map_layers[Ground]->getW(); x++) {
			for (unsigned z = 0; z < map_layers.size(); z++) {
				if (map_layers[z]->isActive()) {
					shared_ptr<IsoMap::Tile> tile = map_layers[z]->data[y][x];

					if (tile != nullptr) {
						tiles[tile->tile].spr.setPosition(tile->iso.x + offset.x, tile->iso.y + offset.y);
						app->draw(tiles[tile->tile].spr);
					}
				}
			}
		}
	}
}

void IsoEngine::setTile(Coord<int> position, string tile, int layer) {
	IsoMap::Tile t;
	t.iso = xy_iso(Coord<float>((float)position.x, (float)position.y));
	t.screen = Coord<int>(position.x, position.y);
	t.tile = tile;

	map_layers[layer]->data[position.y][position.x] = make_shared<IsoMap::Tile>(t);
}

inline Coord<float> IsoEngine::xy_iso(Coord<float> c) {
	return Coord<float>((c.x - c.y) * 32.f, (c.x + c.y) * 16.f);
}

inline Coord<float> IsoEngine::iso_xy(Coord<float> iso) {
	return Coord<float>(iso.x / 16.f + iso.y / 32.f, iso.y / 16.f - iso.x / 32.f);
}

inline Coord<float> IsoEngine::origin(std::shared_ptr<IsoMap> map) {
	return Coord<float>(512.f, 384.f - (float)(map->getH() * 16));
}

IsoEngine::IsoMap::IsoMap(int _w, int _h, bool a) : active(a) {
	w = _w;
	h = _h;

	data.resize(h);
	
	for (int y = 0; y < h; y++)
		data[y].resize(w);
}