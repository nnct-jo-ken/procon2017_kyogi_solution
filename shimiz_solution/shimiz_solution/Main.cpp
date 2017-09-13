# include <Siv3D.hpp>
#include"include.h"

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

	Array<Defined> piece;

	for (const auto a : json[L"sy"].getArray()) {
		piece.emplace_back(a);
	}

	int i = 0;

	while (System::Update()) {
		if (i == piece.size()) {
			i = 0;
		}

		piece[i].edge_length_acquisition();

		if (System::FrameCount() % 180 == 0) {
			i++;
		}
	}
}