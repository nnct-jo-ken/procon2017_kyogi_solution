#include "piece.h"

void Defined::edge_length_acquisition() {
	for (int i = 0; i < node_count; i++) {
		if (i == node_count - 1) {
			edge_length.push_back(Line(nodes[i], nodes[0]).length());
		}
		else {
			edge_length.push_back(Line(nodes[i], nodes[i + 1]).length());
		}
	}
}

void Defined::angle_acquisition() {

}


Defined::Defined(JSONValue object) {
	for (const auto node : object[L"points"].getArray()) {
		nodes.push_back({ node[L"x"].get<int>(),node[L"y"].get<int>() });
	}
	id = object[L"sy_id"].get<uint8>();
	node_count = nodes.size();
	entity = Polygon(nodes);
	edge_length_acquisition();
	angle_acquisition();
}

uint8 Defined::id_acquisition() {
	return id;
}

Piece::Piece(JSONValue object) :Defined(object){
	target.dir = object[L"synthesis"][L"target"][L"dir"].getOr<String>(L"\0");
	target.id = object[L"synthesis"][L"target"][L"sy_id"].getOr<uint8>(NULL);
	target.node_no = object[L"synthesis"][L"target"][L"num"].getOr<uint8>(NULL);

	source.dir = object[L"synthesis"][L"source"][L"dir"].getOr<String>(L"\0");
	source.id = object[L"synthesis"][L"source"][L"sy_id"].getOr<uint8>(NULL);
	source.node_no = object[L"synthesis"][L"source"][L"num"].getOr<uint8>(NULL);
}
