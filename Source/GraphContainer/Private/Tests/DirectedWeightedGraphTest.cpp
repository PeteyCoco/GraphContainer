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

		TestEqual(TEXT("Graph must contain one node"), Graph->NumVertices(), 1);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto Origin = NewObject<UTestVertex>();
		auto Destination = NewObject<UTestVertex>();
		auto Edge = NewObject<UTestEdge>();

		Graph->AddEdge(Edge, Origin, Destination);

		TestEqual(TEXT("Graph must contain two vertices"), Graph->NumVertices(), 2);
		TestEqual(TEXT("Graph must contain one edge"), Graph->NumEdges(), 1);
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

		TestEqual(TEXT("Adding the same vertex twice does nothing"), Graph->NumVertices(), 1);
	}
#if 0
	// Graph must contain the edge added to the graph
	{
		DirectedWeightedGraph<TestNode, TestEdge> graph;
		TestNode N1{ 0 };
		TestNode N2{ 1 };
		TestEdge E{ 0 };

		graph.AddEdge(E, N1, N2);

		TestTrue(TEXT("Graph must contain the edge added to the graph"), graph.HasEdge(E));
	}

	// Graph does not contain edge not in graph
	{
		DirectedWeightedGraph<TestNode, TestEdge> graph;
		TestNode N1{ 0 };
		TestNode N2{ 1 };
		TestEdge E1{ 0 };
		TestEdge E2{ 1 };

		graph.AddEdge(E1, N1, N2);

		TestFalse(TEXT("Graph must not contain an edge not in graph"), graph.HasEdge(E2));
	}

	// Cannot add the same node twice
	{
		DirectedWeightedGraph<TestNode, TestEdge> graph;
		TestNode N1{ 1 };
		TestNode N2{ 2 };
		TestNode N3{ 3 };
		TestEdge E{ 1 };

		graph.AddEdge(E, N1, N2);
		graph.AddEdge(E, N2, N3);

		TestEqual(TEXT("Adding edge with same ID twice does nothing"), graph.NumEdges(), 1);
	}

	// Adding two coincident edges yields a graph with 3 nodes and two edges
	{
		DirectedWeightedGraph<TestNode, TestEdge> graph;
		TestNode N1{ 1 };
		TestNode N2{ 2 };
		TestNode N3{ 3 };
		TestEdge E1{ 1 };
		TestEdge E2{ 2 };

		graph.AddEdge(E1, N1, N2);
		graph.AddEdge(E2, N2, N3);

		TestEqual(TEXT("Adding two coincident edges yields 3 nodes in graph"), graph.NumNodes(), 3);
	}

	// FGraphAStar interface tests
	{
		DirectedWeightedGraph<TestNode, TestEdge> graph;
		TestNode N1{ 1 };

		graph.AddNode(N1);

		TestTrue(TEXT("IsValidRef() is true when node is in graph"), graph.IsValidRef(1));
		TestFalse(TEXT("IsValidRef() is false when node is not in graph"), graph.IsValidRef(2));
	}

	// Count the in, out, and incident edges of a node
	{
		DirectedWeightedGraph<TestNode, TestEdge> graph;
		TestNode N1{ 1 };
		TestNode N2{ 2 };
		TestNode N3{ 3 };		
		TestNode N4{ 4 };

		graph.AddEdge(TestEdge{ 1 }, N1, N2);
		graph.AddEdge(TestEdge{ 2 }, N1, N3);
		graph.AddEdge(TestEdge{ 3 }, N1, N1);
		graph.AddEdge(TestEdge{ 4 }, N4, N1);

		TestEqual(TEXT("Count the in-degree of N1"), graph.NumInEdges(N1), 2);
		TestEqual(TEXT("Count the out-degree of N1"), graph.NumOutEdges(N1), 3);
	}
#endif
	return true;
}