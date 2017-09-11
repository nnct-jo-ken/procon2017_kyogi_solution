# include <Siv3D.hpp>

String GetStringType(JSONValue::ValueType type) {
	switch(type){
	case JSONValue::ValueType::Array:
		return L"Array";
	case JSONValue::ValueType::Boolean:
		return L"Boolean";
	case JSONValue::ValueType::Null:
		return L"Null";
	case JSONValue::ValueType::Number:
		return L"Number";
	case JSONValue::ValueType::Object:
		return L"Object";
	case JSONValue::ValueType::String:
		return L"String";
	default:
		return L"other";
	}
}

void Main() {
	Window::Resize(1280, 720);

	const JSONReader json(L"data.json");

	Array<Vec2> nodes;
	Array<Array<Vec2>> pieces;

	int i = 0;

	for (const auto a : json[L"sy"].getArray()) {
		for (const auto node : a[L"points"].getArray()) {
			nodes.push_back({ node[L"x"].get<int>(),node[L"y"].get<int>() });
		}
		pieces.push_back(nodes);
		nodes.clear();
	}

	for (auto &nodes : pieces) {
		for (auto &node : nodes) {
			node.x *= 5;
			node.y *= 5;
		}
	}

	while (System::Update()) {
		if (i >= pieces.size()) {
			i = 0;
		}

		Polygon(pieces[i]).draw(10, 10);

		if (System::FrameCount() % 180 == 0) {
			i++;
		}
	}
}