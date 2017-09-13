#pragma once
#include<Siv3D.hpp>

typedef struct merge {
	uint8 id;
};

class Defined {
private:
	Array<Vec2> nodes;
	size_t node_count;
	Polygon entity;
	uint8 id;
	Array<double> edge_length;
	Array<double> angle;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="object">�`��f�[�^</param>
	Defined(JSONValue object);

	/// <summary>
	/// id�̎擾
	/// </summary>
	/// <returns>id</returns>
	uint8 id_acquisition();

	/// <summary>
	/// �ӂ̒����̎Z�o
	/// </summary>
	void edge_length_acquisition();

	/// <summary>
	/// �e���_�̊p�x�̎Z�o
	/// </summary>
	void angle_acquisition();
};

class Piece :protected Defined {
private:

};