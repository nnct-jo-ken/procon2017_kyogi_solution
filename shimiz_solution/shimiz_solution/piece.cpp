#include "piece.h"

Defined::Defined(JSONValue object) {
	for (const auto node : object[L"points"].getArray()) {
		nodes.push_back({ node[L"x"].get<int>(),node[L"y"].get<int>() });
	}
	id = object[L"sy_id"].get<uint8>();
	node_count = nodes.size();
	entity = Polygon(nodes);
}

uint8 Defined::id_acquisition() {
	return id;
}

void Defined::edge_length_acquisition() {
	for (int i = 0; i < node_count; i++) {
		if (i==node_count-1) {
			edge_length.push_back(Line(nodes[i], nodes[0]).length());
		}
		else {
			edge_length.push_back(Line(nodes[i], nodes[i + 1]).length());
		}
	}
}

void Defined::angle_acquisition() {

}
