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



};
