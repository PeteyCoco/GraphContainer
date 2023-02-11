// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VertexInterface.h"
#include "EdgeInterface.h"
#include "boost/graph/adjacency_list.hpp"
#include "DirectedWeightedGraph.generated.h"

/**
 * 
 */
UCLASS()
class GRAPHCONTAINER_API UDirectedWeightedGraph : public UObject
{
	GENERATED_BODY()
private:
	typedef IVertexInterface* VertexPtr;
	typedef IEdgeInterface* EdgePtr;
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexPtr, EdgePtr> GraphType;
	typedef boost::graph_traits<GraphType>::vertex_descriptor VertexDescriptor;
	typedef boost::graph_traits<GraphType>::edge_descriptor EdgeDescriptor;

public:
	// Check whether the graph container is empty
	bool IsEmpty() const
	{
		return true;
	}

	// Return the number of vertices in the graph
	int NumVertices() const
	{
		return boost::num_vertices(graph);
	}

	// Return the number of vertices in the graph
	int NumEdges() const
	{
		return boost::num_edges(graph);
	}

	// Add vertex to the graph
	void AddVertex(const IVertexInterface* Vertex);

	// Add Edge to the graph
	void AddEdge(const IEdgeInterface* Edge, const IVertexInterface* Origin, const IVertexInterface* Destination);

	// Check whether the graph contains the given vertex
	bool HasVertex(const IVertexInterface* Vertex);

	// Check whether the graph contains the given edge
	bool HasEdge(const IEdgeInterface* Edge);

	// Get the origin vertex of a given edge
	IVertexInterface* Origin(const IEdgeInterface* Edge);

	// Get the destination vertex of a given edge
	IVertexInterface* Destination(const IEdgeInterface* Edge);

	// Get the in degree of a given vertex
	int InDegree(const IVertexInterface* Vertex) const;

private:
	GraphType graph{};

	TMap<IVertexInterface*, VertexDescriptor> vertex_descriptor_map;

	TMap<IEdgeInterface*, EdgeDescriptor> edge_descriptor_map;

};
