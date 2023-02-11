#include "Misc/AutomationTest.h"
#include "DirectedWeightedGraph.h"
#include "Tests/TestVertex.h"
#include "Tests/TestEdge.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDirectedWeightedGraph, "Graph Container.Directed Weighted Graph", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FDirectedWeightedGraph::RunTest(FString const& Parameters) {
	{
		auto Graph = NewObject<UDirectedWeightedGraph>();

		TestTrue(TEXT("Graph is created empty"), Graph->IsEmpty());
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Vertex = NewObject<UTestVertex>();

		Graph->AddVertex(Vertex);

		TestEqual(TEXT("Graph must contain one node after adding vertex to empty graph"), Graph->NumVertices(), 1);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();

		AddExpectedError(TEXT("Tried to add nullptr vertex to graph. No action taken."), EAutomationExpectedErrorFlags::Exact, 1);
		Graph->AddVertex(nullptr);

		TestEqual(TEXT("NumVertices() remains 0 after adding nullptr vertex to an empty graph"), Graph->NumVertices(), 0);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Origin = NewObject<UTestVertex>();
		auto Destination = NewObject<UTestVertex>();
		auto Edge = NewObject<UTestEdge>();

		Graph->AddEdge(Edge, Origin, Destination);

		TestEqual(TEXT("Graph must contain two vertices after adding edge to an empty graph"), Graph->NumVertices(), 2);
		TestEqual(TEXT("Graph must contain one edge after adding edge to empty graph"), Graph->NumEdges(), 1);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Vertex = NewObject<UTestVertex>();

		Graph->AddVertex(Vertex);

		TestTrue(TEXT("Graph must contain the vertex added to the graph"), Graph->HasVertex(Vertex));
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Vertex = NewObject<UTestVertex>();

		TestFalse(TEXT("Graph must not contain vertex not present in graph"), Graph->HasVertex(Vertex));
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Vertex = NewObject<UTestVertex>();

		Graph->AddVertex(Vertex);
		Graph->AddVertex(Vertex);

		TestEqual(TEXT("NumVertices() remains one after adding the same vertex twice to an empty graph"), Graph->NumVertices(), 1);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Origin = NewObject<UTestVertex>();
		auto Destination = NewObject<UTestVertex>();
		auto Edge = NewObject<UTestEdge>();

		Graph->AddEdge(Edge, Origin, Destination);

		TestTrue(TEXT("Graph must contain the edge added to the graph"), Graph->HasEdge(Edge));
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto V1 = NewObject<UTestVertex>();
		auto V2 = NewObject<UTestVertex>();
		auto E1 = NewObject<UTestEdge>();
		auto E2 = NewObject<UTestEdge>();

		Graph->AddEdge(E1, V1, V2);
		Graph->AddEdge(E2, V2, V1);

		TestEqual(TEXT("Graph must contain two edges after adding two distinct edges to empty graph"), Graph->NumEdges(), 2);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Edge = NewObject<UTestEdge>();

		TestFalse(TEXT("Graph doesn't contain an edge not added to the graph"), Graph->HasEdge(Edge));
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto V1 = NewObject<UTestVertex>();
		auto V2 = NewObject<UTestVertex>();
		auto Edge = NewObject<UTestEdge>();

		Graph->AddEdge(Edge, V1, V2);
		AddExpectedError(TEXT("Tried to add a pre-existing edge to graph. No action taken."), EAutomationExpectedErrorFlags::Exact, 1);
		Graph->AddEdge(Edge, V2, V1);

		TestEqual(TEXT("Number of edges remains one after adding the same edge twice to an empty graph"), Graph->NumEdges(), 1);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto V1 = NewObject<UTestVertex>();
		auto V2 = NewObject<UTestVertex>();
		auto Edge = NewObject<UTestEdge>();

		AddExpectedError(TEXT("One of Edge, Origin, or Vertex are nullptr. No action taken."), EAutomationExpectedErrorFlags::Exact, 1);
		Graph->AddEdge(nullptr, V2, nullptr);

		TestEqual(TEXT("NumEdges() is zero after calling AddEdge() with nullptr argument(s) on an empty graph"), Graph->NumEdges(), 0);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto V1 = NewObject<UTestVertex>();
		auto V2 = NewObject<UTestVertex>();
		auto V3 = NewObject<UTestVertex>();
		auto E1 = NewObject<UTestEdge>();
		auto E2 = NewObject<UTestEdge>();

		Graph->AddEdge(E1, V1, V2);
		Graph->AddEdge(E2, V2, V3);

		TestEqual(TEXT("Graph of two coincident edges has three vertices"), Graph->NumVertices(), 3);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Origin = NewObject<UTestVertex>();
		auto Destination = NewObject<UTestVertex>();
		auto Edge = NewObject<UTestEdge>();

		Graph->AddEdge(Edge, Origin, Destination);

		TestTrue(TEXT("The origin vertex of a directed edge matches the vertex used in its construction"), Graph->Origin(Edge) == Origin);
		TestTrue(TEXT("The destination vertex of a directed edge matches the vertex used in its construction"), Graph->Destination(Edge) == Destination);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Edge = NewObject<UTestEdge>();

		AddExpectedError(TEXT("Tried to find origin vertex of an edge not in the graph. Returning nullptr."), EAutomationExpectedErrorFlags::Exact, 1);
		auto Origin = Graph->Origin(Edge);

		TestNull(TEXT("The origin of an edge not in the graph is null."), Origin);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto V1 = NewObject<UTestVertex>();
		auto V2 = NewObject<UTestVertex>();
		auto V3 = NewObject<UTestVertex>();
		auto E1 = NewObject<UTestEdge>();
		auto E2 = NewObject<UTestEdge>();
		auto E3 = NewObject<UTestEdge>();

		Graph->AddEdge(E1, V1, V2);
		Graph->AddEdge(E2, V2, V3);
		Graph->AddEdge(E3, V1, V3);

		TestEqual(TEXT("In-degree of V1 is 0"), Graph->InDegree(V1), 0);
	}
	return true;
}