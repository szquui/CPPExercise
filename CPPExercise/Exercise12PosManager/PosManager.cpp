#include "PosManager.h"

void PosManager::Init(int InBlockSize, int InMapSize)
{
	BlockSize = InBlockSize;
	MapSize = InMapSize;
	MapColumn = InMapSize / InBlockSize;
}

void PosManager::Add(int InPosID, int InPosX, int InPosY)
{
	PosInfo Pos(InPosX, InPosY, InPosID);
	int BlockID = GetBlockID(InPosX, InPosY);
	PositionInfo[InPosID] = BlockID;
	Map[BlockID].push_back(Pos);

}

std::vector<int> PosManager::Find(int InPosID)
{
	std::vector<int> Result;
	std::vector<int> SideBlockIDs;
	GetSideBlockIDs(InPosID, SideBlockIDs);
	
	std::vector<int>::iterator Iterator = SideBlockIDs.begin();
	for (; Iterator != SideBlockIDs.end(); ++Iterator)
	{
		std::vector<PosInfo>::iterator IteratorPos = Map[*Iterator].begin();
		for (; IteratorPos != Map[*Iterator].end(); ++IteratorPos)
		{
			Result.push_back(IteratorPos->PosID);
		}
	}

	return Result;
}

void PosManager::Update(int InPosID, int InNewPosX, int InNewPosY)
{
	Remove(InPosID);
	PosInfo Pos(InNewPosX, InNewPosY, InPosID);
	Add(InPosID, InNewPosX, InNewPosY);
}

void PosManager::Remove(int InPosID)
{
	int BlockID = PositionInfo[InPosID];
	std::vector<PosInfo>::iterator Iterator = Map[BlockID].begin();
	for (; Iterator != Map[BlockID].end(); ++Iterator)
	{
		if (Iterator->PosID == InPosID)
		{
			Iterator = Map[BlockID].erase(Iterator);
			return;
		}
	}
}

int PosManager::GetBlockID(int InPosX, int InPosY)
{
	return InPosX / BlockSize + InPosY / BlockSize * MapColumn;
}

void PosManager::GetSideBlockIDs(int InPosID, std::vector<int> &OutBlockIDs)
{
	int BlockID = PositionInfo[InPosID];
	int Row = BlockID / MapColumn;
	int Column = BlockID % MapColumn;
	if (Column + 1 < MapColumn)
	{
		OutBlockIDs.push_back(BlockID + 1);
	}
	if (Column - 1 >= 0)
	{
		OutBlockIDs.push_back(BlockID - 1);
	}
	if (Row - 1 >= 0)
	{
		OutBlockIDs.push_back(BlockID - MapColumn);
	}
	if (Row + 1 < MapColumn)
	{
		OutBlockIDs.push_back(BlockID + MapColumn);
	}

	if (Column + 1 < MapColumn && Row - 1 >= 0)
	{
		OutBlockIDs.push_back(BlockID - MapColumn + 1);
	}
	if (Column + 1 < MapColumn && Row + 1 < MapColumn)
	{
		OutBlockIDs.push_back(BlockID + MapColumn + 1);
	}
	if (Column - 1 >= 0 && Row - 1 >= 0)
	{
		OutBlockIDs.push_back(BlockID - MapColumn - 1);
	}
	if (Column - 1 >= 0 && Row + 1 < MapColumn)
	{
		OutBlockIDs.push_back(BlockID + MapColumn - 1);
	}
}


//int main()
//{
//	PosManager m;
//	int blockSize = 100;
//	int mapSize = 10000;
//	m.Init(blockSize, mapSize);
//
//	int poseId1 = 1;
//	int poseId2 = 2;
//	m.Add(poseId1, 100, 200);  // 100是横坐标，200纵坐标
//	m.Add(poseId2, 200, 300);
//	std::vector<int> poseIds = m.Find(poseId1);    // 找到poseid1脚下以及周围8格的所有id
//	m.Update(poseId1, 300, 400);
//	m.Remove(poseId2);
//}