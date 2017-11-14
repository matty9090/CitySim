#pragma once

#include <vector>
#include <memory>

#include "EngineInterface.hpp"

struct TNode {
	std::shared_ptr<TNode> parent;
	std::vector<std::shared_ptr<TNode>> children;

	TNode(std::shared_ptr<TNode> _parent) : parent(_parent) {}
	virtual ~TNode() {};
};

template <class N = TNode> class NTree {
	public:
		NTree() {}

		N getRoot() { return root; }
		void addNode(N node, N child) { node->children.push_back(child); }

	protected:
		N root;
};

namespace City {
	struct RoadNetworkNode : public TNode {
		int n, level;
		Coord<int> pos;

		RoadNetworkNode(std::shared_ptr<RoadNetworkNode> _parent, Coord<int> _pos, int _n, int _level) : TNode(_parent) {
			pos = _pos; n = _n, level = _level;
		}
	};

	typedef std::shared_ptr<RoadNetworkNode> RoadNode;
	
	class RoadNetwork : public NTree<RoadNode> {
		public:
			RoadNetwork(Coord<int> initial_pos) : NTree(), counter(0) {
				root = std::make_shared<RoadNetworkNode>(nullptr, initial_pos, 0, 0);
			}

			RoadNode addRoad(RoadNode node, Coord<int> pos);
			RoadNode searchPosition(RoadNode node, Coord<int> pos);

		private:
			int counter;
	};
}