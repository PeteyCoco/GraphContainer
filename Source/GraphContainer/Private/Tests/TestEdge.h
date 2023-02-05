// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EdgeInterface.h"
#include "TestEdge.generated.h"

/**
 * Edge class for automation testing
 */
UCLASS()
class UTestEdge : public UObject, public IEdgeInterface
{
	GENERATED_BODY()
	
};
