// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectedWeightedGraph.h"

void UDirectedWeightedGraph::AddVertex(const VertexPtr Vertex)
{
		boost::add_vertex(Vertex, graph);
}

bool UDirectedWeightedGraph::HasVertex(const VertexPtr Vertex)
{
	const auto vip = vertices(graph);
	for (auto iter = vip.first; iter != vip.second; ++iter)
	{
		if (graph[*iter] == Vertex)
			return true;
	}
	return false;
}
