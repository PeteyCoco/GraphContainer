// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectedWeightedGraph.h"

void UDirectedWeightedGraph::AddVertex(IVertexInterface* const Vertex)
{
		boost::add_vertex(Vertex, graph);
}
