# include <Siv3D.hpp>
#include"include.h"

void Main() {
	Window::Resize(1280, 720);

	const JSONReader json(L"data.json");

	Array<Piece> piece;

	for (const auto a : json[L"sy"].getArray()) {
		piece.emplace_back(a);
	}

	int i = 0;

	while (System::Update()) {
		if (i == piece.size()) {
			i = 0;
		}

		piece[i].draw();
		piece[i].printangle();

		if (Input::KeyN.clicked) {
			i++;
		}
	}
}