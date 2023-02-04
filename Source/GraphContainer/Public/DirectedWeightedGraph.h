// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
	
};
