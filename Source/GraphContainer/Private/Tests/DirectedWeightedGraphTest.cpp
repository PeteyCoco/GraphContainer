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

		AddExpectedError(TEXT("Tried to add nullptr vertex to graph. No action taken."), EAutomationExpectedErrorFlags::Exact, 1);
		Graph->AddVertex(nullptr);

		TestEqual(TEXT("Adding nullptr to graph does nothing"), Graph->NumVertices(), 0);
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

		TestEqual(TEXT("Graph must contain two edges"), Graph->NumEdges(), 2);
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

		TestEqual(TEXT("Number of edges remains one after adding the same edge twice"), Graph->NumEdges(), 1);
	}

	{
		auto Graph = NewObject<UDirectedWeightedGraph>();
		auto V1 = NewObject<UTestVertex>();
		auto V2 = NewObject<UTestVertex>();
		auto Edge = NewObject<UTestEdge>();

		AddExpectedError(TEXT("One of Edge, Origin, or Vertex are nullptr. No action taken."), EAutomationExpectedErrorFlags::Exact, 1);
		Graph->AddEdge(nullptr, V2, nullptr);

		TestEqual(TEXT("NumEdges() is zero after calling AddEdge() with nullptr argument(s)"), Graph->NumEdges(), 0);
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

		TestEqual(TEXT("Graph of two coincident edges has three verrtices"), Graph->NumVertices(), 3);
	}

#if 0
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