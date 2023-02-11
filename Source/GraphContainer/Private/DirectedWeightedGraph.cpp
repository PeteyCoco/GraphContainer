// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectedWeightedGraph.h"

void UDirectedWeightedGraph::AddVertex(const VertexPtr Vertex)
{
	if (!Vertex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to add nullptr vertex to graph. No action taken."));
		return;
	}
	else if (!HasVertex(Vertex))
	{
		const auto vd = boost::add_vertex(Vertex, graph);
		vertex_descriptor_map.Add(Vertex, vd);
	}
}

void UDirectedWeightedGraph::AddEdge(const EdgePtr Edge, const VertexPtr Origin, const VertexPtr Destination)
{
	if (!Edge || !Origin || !Destination)
	{
		UE_LOG(LogTemp, Warning, TEXT("One of Edge, Origin, or Vertex are nullptr. No action taken."));
	}
	else if (!HasEdge(Edge))
	{
		AddVertex(Origin);
		AddVertex(Destination);
		const auto aer = boost::add_edge(vertex_descriptor_map[Origin], vertex_descriptor_map[Destination], graph);
		edge_descriptor_map.Add(Edge, aer.first);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to add a pre-existing edge to graph. No action taken."));
	}
}

bool UDirectedWeightedGraph::HasVertex(const VertexPtr Vertex)
{
	return vertex_descriptor_map.Contains(Vertex);
}

bool UDirectedWeightedGraph::HasEdge(const EdgePtr Edge)
{
	return edge_descriptor_map.Contains(Edge);
}

IVertexInterface* UDirectedWeightedGraph::Origin(const EdgePtr Edge)
{
	return graph[boost::source(edge_descriptor_map[Edge], graph)];
}
