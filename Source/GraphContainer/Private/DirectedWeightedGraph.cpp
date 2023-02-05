// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectedWeightedGraph.h"

void UDirectedWeightedGraph::AddVertex(const VertexPtr Vertex)
{
	if (!Vertex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to add nullptr vertex to graph. No action taken."));
		return;
	}
	if(!HasVertex(Vertex))
		boost::add_vertex(Vertex, graph);
}

void UDirectedWeightedGraph::AddEdge(const EdgePtr Edge, const VertexPtr Origin, const VertexPtr Destination)
{
	AddVertex(Origin);
	AddVertex(Destination);
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
