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
	merge join_target;
	merge join_source;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="object">�`��f�[�^</param>
	Piece(JSONValue object);

	/// <summary>
	/// �s�[�X�̌���
	/// </summary>
	/// <param name="target">������̃s�[�X</param>
	/// <param name="target_no">���_�ԍ�</param>
	/// <param name="target_dir">��������</param>
	/// <param name="source">�������̃s�[�X</param>
	/// <param name="source_no">���_�ԍ�</param>
	/// <param name="source_dir">��������</param>
	void synthesis(Piece target, uint8 target_no, String target_dir, Piece source, uint8 source_no, String source_dir);
};