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
	double inside, arg_diff;
	Vec2 Z_1, Z_2, unit_1, unit_2, arg;

	for (int i = 0; i < node_count; i++) {
		Z_1 = nodes[i - 1 < 0 ? node_count - 1 : i - 1] - nodes[i];
		Z_2 = nodes[i == node_count - 1 ? 0 : i + 1] - nodes[i];

		unit_1 = Z_1 / Z_1.length();
		unit_2 = Z_2 / Z_2.length();

		arg = Vec2((unit_1.x*unit_2.x + unit_1.y*unit_2.y) / unit_2.lengthSq(),
			(unit_1.y*unit_2.x - unit_1.x*unit_2.y) / unit_2.lengthSq());

		arg_diff = arg.y < 0 ? Math::Acos(arg.x) : -Math::Acos(arg.x);

		inside = TwoPi - arg_diff < TwoPi ? TwoPi - arg_diff : -arg_diff;

		angle.push_back(Math::Degrees(inside));
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
	//entity.drawFrame(1.0, Palette::Red);
}

void Defined::printangle() {
	ClearPrint();
	for (int i = 0; i < node_count; i++) {
		Println(angle[i]);
	}
}

Piece::Piece(JSONValue object) :Defined(object){
	join_target.dir = object[L"synthesis"][L"target"][L"dir"].getOr<String>(L"\0");
	join_target.id = object[L"synthesis"][L"target"][L"sy_id"].getOr<uint8>(NULL);
	join_target.node_no = object[L"synthesis"][L"target"][L"num"].getOr<uint8>(NULL);

	join_source.dir = object[L"synthesis"][L"source"][L"dir"].getOr<String>(L"\0");
	join_source.id = object[L"synthesis"][L"source"][L"sy_id"].getOr<uint8>(NULL);
	join_source.node_no = object[L"synthesis"][L"source"][L"num"].getOr<uint8>(NULL);
}

void Piece::synthesis(Piece target, uint8 target_no, String target_dir, Piece source, uint8 source_no, String source_dir) {
	join_target.dir = target_dir;
	join_target.id = target.id_acquisition();
	join_target.node_no = target_no;

	join_source.dir = source_dir;
	join_source.id = source.id_acquisition();
	join_source.node_no = source_no;
}
