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
		return 1;
	}

	// Add vertex to the graph
	void AddVertex(IVertexInterface* const Vertex);

	// Add Edge to the graph
	void AddEdge(const IEdgeInterface* Edge, IVertexInterface* const Origin, IVertexInterface* const Destination)
	{
		AddVertex(Origin);
		AddVertex(Destination);
	}

private:
	boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, IVertexInterface*, IEdgeInterface*> graph{};
};
