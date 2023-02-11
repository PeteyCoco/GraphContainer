// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectedWeightedGraph.h"

void UDirectedWeightedGraph::AddVertex(const IVertexInterface* Vertex)
{
	if (!Vertex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to add nullptr vertex to graph. No action taken."));
		return;
	}
	else if (!HasVertex(Vertex))
	{
		const auto vd = boost::add_vertex(const_cast<VertexPtr>(Vertex), graph);
		vertex_descriptor_map.Add(const_cast<VertexPtr>(Vertex), vd);
	}
}

void UDirectedWeightedGraph::AddEdge(const IEdgeInterface* Edge, const IVertexInterface* Origin, const IVertexInterface* Destination)
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
		edge_descriptor_map.Add(const_cast<EdgePtr>(Edge), aer.first);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to add a pre-existing edge to graph. No action taken."));
	}
}

bool UDirectedWeightedGraph::HasVertex(const IVertexInterface* Vertex) const
{
	return vertex_descriptor_map.Contains(Vertex);
}

bool UDirectedWeightedGraph::HasEdge(const IEdgeInterface* Edge) const
{
	return edge_descriptor_map.Contains(Edge);
}

IVertexInterface* UDirectedWeightedGraph::Origin(const IEdgeInterface* Edge) const
{
	if (HasEdge(Edge))
	{
		return graph[boost::source(edge_descriptor_map[Edge], graph)];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to find origin vertex of an edge not in the graph. Returning nullptr."));
		return nullptr;
	}
}

IVertexInterface* UDirectedWeightedGraph::Destination(const IEdgeInterface* Edge) const
{
	IVertexInterface* Destination = nullptr;
	if (HasEdge(Edge))
	{
		return graph[boost::target(edge_descriptor_map[Edge], graph)];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to find destination vertex of an edge not in the graph. Returning nullptr."))
		return nullptr;
	}
}

int UDirectedWeightedGraph::OutDegree(const IVertexInterface* Vertex) const
{
	return boost::out_degree(vertex_descriptor_map[Vertex], graph);
}
