#pragma once
#include <map>
#include <vector>

struct PosInfo
{
	int PosX = 0;
	int PosY = 0;
	int PosID = 0;
	PosInfo(int InPosX, int InPosY, int InPosID) :PosX(InPosX), PosY(InPosY), PosID(InPosID){};
};

class PosManager
{
public:
	PosManager() = default;
	~PosManager() = default;
	void Init(int InBlockSize, int InMapSize);
	void Add(int InPosID, int InPosX, int InPosY);
	std::vector<int> Find(int InPosID);
	void Update(int InPosID, int InNewPosX, int InNewPosY);
	void Remove(int InPosID);

private:
	int GetBlockID(int InPosX, int InPosY);
	void GetSideBlockIDs(int InPosID, std::vector<int> &OutBlockIDs);

private:
	int BlockSize = 0;
	int MapSize = 0;
	int MapColumn = 0;
	std::map<int, std::vector<PosInfo>> Map;
	std::map<int, int> PositionInfo;

};

