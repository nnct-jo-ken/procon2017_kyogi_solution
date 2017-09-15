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
	/// 辺の長さの算出
	/// </summary>
	void edge_length_acquisition();

	/// <summary>
	/// 各頂点の角度の算出
	/// </summary>
	void angle_acquisition();
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="object">形状データ</param>
	Defined(JSONValue object);

	/// <summary>
	/// idの取得
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