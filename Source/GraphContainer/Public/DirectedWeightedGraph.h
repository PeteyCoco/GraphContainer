// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VertexInterface.h"
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
		return 1;
	}

	// Add vertex to the graph
	void AddVertex(const IVertexInterface* Vertex)
	{

	}
	
};
