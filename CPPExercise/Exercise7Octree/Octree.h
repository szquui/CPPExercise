#pragma once
#include<vector>
#include <random>

class Vector3f
{
public:
	Vector3f() = default;
	Vector3f(float InX, float InY, float InZ) :X(InX), Y(InY), Z(InZ) {};
	~Vector3f() {};

	float X = 0.f;
	float Y = 0.f;
	float Z = 0.f;
};


class OctreePoint
{
public:
	OctreePoint(){};
	~OctreePoint(){};

	Vector3f Position = Vector3f(0.f, 0.f, 0.f);
};



class Octree
{
public:
	Octree() = default;
	Octree(Vector3f InOrigin, Vector3f InHalfDimension) :Origin(InOrigin), HalfDimension(InHalfDimension), Children{}{};
	~Octree() { delete Point; delete[] Children; };

	void Insert(OctreePoint *InOctreePoint);
	void GetPointsInSideBox(const Vector3f& InMin, const Vector3f& InMax, std::vector<OctreePoint*> &OutResult);

private:
	bool IsLeafNode() const { return Children[0] == NULL; };
	int GetOctreePointIndex(const Vector3f& InPoint) const;

private:
	Vector3f Origin = Vector3f(0.f, 0.f, 0.f);
	Vector3f HalfDimension = Vector3f(0.f, 0.f, 0.f);

	Octree* Children[8];
	OctreePoint* Point = nullptr;
};

