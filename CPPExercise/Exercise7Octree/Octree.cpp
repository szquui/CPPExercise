#include "Octree.h"

void Octree::Insert(OctreePoint* InOctreePoint)
{
	if (IsLeafNode())
	{
		if (Point == nullptr)
		{
			Point = InOctreePoint;
			return;
		}
		else
		{
			OctreePoint* OldPoint = Point;
			Point = nullptr;

			for (int i = 0; i < 8; i++)
			{
				Vector3f NewOrign = Vector3f(Origin.X, Origin.Y, Origin.Z);
				NewOrign.X += HalfDimension.X * (i & 4 ? .5f : -.5f);
				NewOrign.Y += HalfDimension.Y * (i & 2 ? .5f : -.5f);
				NewOrign.Z += HalfDimension.Z * (i & 1 ? .5f : -.5f);
				Children[i] = new Octree(NewOrign, Vector3f(HalfDimension.X * .5f, HalfDimension.Y * .5f, HalfDimension.Z * .5f));
			}

			Children[GetOctreePointIndex(OldPoint->Position)]->Insert(OldPoint);
			Children[GetOctreePointIndex(InOctreePoint->Position)]->Insert(InOctreePoint);
		}
	}
	else
	{
		int Index = GetOctreePointIndex(InOctreePoint->Position);
		Children[Index]->Insert(InOctreePoint);
	}
}

void Octree::GetPointsInSideBox(const Vector3f& InMin, const Vector3f& InMax, std::vector<OctreePoint*>& OutResult)
{
	if (IsLeafNode())
	{
		if (Point != nullptr)
		{
			const Vector3f& PointPosition = Point->Position;
			if (PointPosition.X > InMax.X || PointPosition.Y > InMax.Y || PointPosition.Z > InMax.Z)
				return;
			if (PointPosition.X < InMin.X || PointPosition.Y < InMin.Y || PointPosition.Z < InMin.Z)
				return;
			OutResult.push_back(Point);
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			Vector3f NewMax = Vector3f(Children[i]->Origin.X + Children[i]->HalfDimension.X, Children[i]->Origin.Y + Children[i]->HalfDimension.Y, Children[i]->Origin.Z + Children[i]->HalfDimension.Z);
			Vector3f NewMin = Vector3f(Children[i]->Origin.X - Children[i]->HalfDimension.X, Children[i]->Origin.Y - Children[i]->HalfDimension.Y, Children[i]->Origin.Z - Children[i]->HalfDimension.Z);
			
			if (NewMax.X < InMin.X || NewMax.Y < InMin.Y || NewMax.Z < InMin.Z) continue;
			if (NewMin.X > InMax.X || NewMin.Y > InMax.Y || NewMin.Z > InMax.Z) continue;

			Children[i]->GetPointsInSideBox(InMin, InMax, OutResult);
		}
	}
}

int Octree::GetOctreePointIndex(const Vector3f& InPoint) const
{
	int Index = 0;
	if (InPoint.X >= Origin.X)
		Index |= 4;
	if (InPoint.Y >= Origin.Y)
		Index |= 2;
	if (InPoint.Z >= Origin.Z)
		Index |= 1;
	return Index;
}


Octree* Tree = nullptr;
std::vector<Vector3f> Points;
Vector3f MinSizeBox = Vector3f(-.05f, -.05f, -.05f);
Vector3f MaxSizeBox = Vector3f(.05f, .05f, .05f);

// Query
void TestOctree()
{
	std::vector<OctreePoint*> Result;
	Tree->GetPointsInSideBox(MinSizeBox, MaxSizeBox, Result);
	
}

float RandomFloat()
{
	return -1.f + (2.f * rand()) * (1.f / RAND_MAX);
}

Vector3f RandomVec()
{

	return Vector3f(RandomFloat(), RandomFloat(), RandomFloat());
}

void Init()
{
	Vector3f VecMin = Vector3f(0.f, 0.f, 0.f);
	Vector3f VecMax = Vector3f(1.f, 1.f, 1.f);
	Tree = new Octree(VecMin, VecMax);

	for (int i = 0; i < 100; i++)
	{
		Points.push_back(RandomVec());
	}

	OctreePoint* OctreePoints = new OctreePoint[100];

	for (int i = 0; i < 100; i++)
	{
		OctreePoints[i].Position = Vector3f(Points[i].X, Points[i].Y, Points[i].Z);
		Tree->Insert(OctreePoints + i);
	}
}
