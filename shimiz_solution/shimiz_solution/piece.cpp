#include "piece.h"

void Defined::edge_length_acquisition() {
	for (int i = 0; i < node_count; i++) {
		if (i == node_count - 1) {
			edge_length.push_back(Line(nodes[i], nodes[0]).lengthSq());
		}
		else {
			edge_length.push_back(Line(nodes[i], nodes[i + 1]).lengthSq());
		}
	}
}

void Defined::angle_acquisition() {
	double inside;
	double numerator, denominator, a2;
	Line me;

	for (int i = 0; i < node_count; i++) {
		me = Line(nodes[i - 1 < 0 ? node_count - 1 : i - 1], nodes[i == node_count - 1 ? 0 : i + 1]);

		a2 = me.lengthSq();

		numerator = edge_length[i] + edge_length[i - 1 < 0 ? node_count - 1 : i - 1] - a2;
		denominator = 2 * sqrt(edge_length[i])*sqrt(edge_length[i - 1 < 0 ? node_count - 1 : i - 1]);

		if (entity.intersects(me.asPolygon())) {
			inside = Math::Degrees(Math::Acos(numerator / denominator));
		}
		else {
			inside = Math::Degrees(TwoPi - Math::Acos(numerator / denominator));
		}

		angle.push_back(inside);
	}
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

void Defined::draw() {
	entity.draw(100, 10);
}

void Defined::printangle() {
	ClearPrint();
	for (int i = 0; i < node_count; i++) {
		Println(angle[i]);
	}
}

Piece::Piece(JSONValue object) :Defined(object){
	target.dir = object[L"synthesis"][L"target"][L"dir"].getOr<String>(L"\0");
	target.id = object[L"synthesis"][L"target"][L"sy_id"].getOr<uint8>(NULL);
	target.node_no = object[L"synthesis"][L"target"][L"num"].getOr<uint8>(NULL);

	source.dir = object[L"synthesis"][L"source"][L"dir"].getOr<String>(L"\0");
	source.id = object[L"synthesis"][L"source"][L"sy_id"].getOr<uint8>(NULL);
	source.node_no = object[L"synthesis"][L"source"][L"num"].getOr<uint8>(NULL);
}
