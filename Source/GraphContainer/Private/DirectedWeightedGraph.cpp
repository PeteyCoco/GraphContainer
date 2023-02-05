// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectedWeightedGraph.h"

void UDirectedWeightedGraph::AddVertex(const VertexPtr& Vertex)
{
		boost::add_vertex(Vertex, graph);
}
