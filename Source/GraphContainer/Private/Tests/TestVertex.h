// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VertexInterface.h"
#include "TestVertex.generated.h"

/**
 * Vertex class for automation testing
 */
UCLASS()
class UTestVertex : public UObject, public IVertexInterface
{
	GENERATED_BODY()
	
};
