#pragma once
#include"Tilemap.h"
#include<unordered_map>


class Pathfinder
{
public:
	Tilemap* map = nullptr;


private:
	std::unordered_map<TileCoord, float, std::hash<TileCoord>, std::equal_to<TileCoord>> unvisited;
	std::unordered_map<TileCoord, float, std::hash<TileCoord>, std::equal_to<TileCoord>> visited;
	std::unordered_map<TileCoord, TileCoord, std::hash<TileCoord>, std::equal_to<TileCoord>> cheapestEdgeTo;

	TileCoord startNode;
	TileCoord endNode;
	TileCoord currentNode;
	
public:
	Pathfinder()
	{

	};

	Pathfinder(Tilemap* levelToNavigate, TileCoord startTile, TileCoord endTile)
	{
		map = levelToNavigate;
		startNode = startTile;
		endNode = endTile;
		currentNode = startTile;
		Restart();
	}

	void Restart()
	{
		visited.clear();
		cheapestEdgeTo.clear();

		unvisited.clear();
		for (TileCoord position : map->GetAllTraversableTiles())
		{
			unvisited[position] = INFINITY;
		}
		unvisited[startNode] = 0;
	}

	std::pair<TileCoord, float> GetLowestCostIn(std::unordered_map<TileCoord, float> set)
	{
		TileCoord cheapestPosition = { -1,-1 };
		float lowestCost = INFINITY;
		for (auto nodeValuepair:set)
		{
			TileCoord tile = nodeValuepair.first;
			float cost = nodeValuepair.second;


			if (cost<lowestCost)
			{
				cheapestPosition = tile;
				lowestCost = cost;
			}
		}
		return  { cheapestPosition, lowestCost };
	}

	bool IsVisited(TileCoord pos)const{ return visited.count(pos); }
	bool IsSolved()const { return IsVisited(endNode); }
	bool IsCompleted() { return IsVisited(endNode) || GetLowestCostIn(unvisited).second == INFINITY; }


	/*void ProcessNextIterationFunctional()
	{
		if (IsCompleted()) return;
		currentNode = GetLowestCostIn(unvisited).first;
		TileCoord currentNode = GetLowestCostIn(unvisited).first;

		for (auto adjacent : map->GetTraversableTilesAdjacentTo(currentNode))
		{
			if (IsVisited(adjacent)) continue;
			float costThisWay = GetTotalCostToReach(currentNode) + map->GetCostForTile(adjacent);

			float oldCost = GetTotalCostToReach(adjacent);
			if (costThisWay < oldCost)
			{
				SetCostToReach(adjacent, costThisWay);
				cheapestEdgeTo[adjacent] = currentNode;
			}
		}

		MoveToVisitiedSet(currentNode);
	}*/

	void MoveToVisitiedSet(TileCoord node)
	{
		visited[currentNode] = unvisited[currentNode];
		unvisited.erase(currentNode);
	}


	bool SolvePath()
	{
		Restart();
		while (!IsCompleted())
		{
			//ProcessNextIterationFunctional();
		}

		return IsSolved();
	}

	
	float GetTotalCostToReach(TileCoord pos) { return unvisited[pos]; }

	void SetCostToReach(TileCoord pos, float newCost)
	{
		unvisited[pos] = newCost;
	}

	std::list<TileCoord> Getsolution()
	{
		std::list<TileCoord>solution;
		auto currentNode = endNode;
		while (currentNode!=startNode)
		{
			solution.push_front(currentNode);
			currentNode = cheapestEdgeTo[currentNode];
		}
		return solution;
	}

};