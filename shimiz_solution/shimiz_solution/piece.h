#pragma once
#include<Siv3D.hpp>

typedef struct {
	uint8 id;
	String dir;
	uint8 node_no;
}merge;

class Defined {
protected:
	Array<Vec2> nodes;
	size_t node_count;
	Polygon entity;
	uint8 id;
	Array<double> edge_length;
	Array<double> angle;

	/// <summary>
	/// �ӂ̒����̎Z�o
	/// </summary>
	void edge_length_acquisition();

	/// <summary>
	/// �e���_�̊p�x�̎Z�o
	/// </summary>
	void angle_acquisition();
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

	void draw();
	void printangle();
};

class Piece :public Defined {
private:
	merge target;
	merge source;
public:
	Piece(JSONValue object);
};