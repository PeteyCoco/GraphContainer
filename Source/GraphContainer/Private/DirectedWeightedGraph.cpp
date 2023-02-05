// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectedWeightedGraph.h"

void UDirectedWeightedGraph::AddVertex(const VertexPtr Vertex)
{
	if (!Vertex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to add nullptr vertex to graph. No action taken."));
		return;
	}
	if (!HasVertex(Vertex))
	{
		const auto vd = boost::add_vertex(Vertex, graph);
		vertex_descriptor_map.Add(Vertex, vd);
	}
}

void UDirectedWeightedGraph::AddEdge(const EdgePtr Edge, const VertexPtr Origin, const VertexPtr Destination)
{
	const auto vdo = boost::add_vertex(Origin, graph);
	const auto vdd = boost::add_vertex(Destination, graph);
	const auto aer = boost::add_edge(vdo, vdd, graph);
}

bool UDirectedWeightedGraph::HasVertex(const VertexPtr Vertex)
{
	return vertex_descriptor_map.Contains(Vertex);
}

bool UDirectedWeightedGraph::HasEdge(const EdgePtr Edge)
{
	return true;
}
