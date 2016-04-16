#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
using namespace std;

class Graph
{
	int N;										// Number of nodes
	int E;										// Number of edges
	vector<pair<int, int> > *adj;				// Adjacency  list
	pair<int, int> *mst;						// Minimum spanning tree
	int total_cost;								// Total cost
public:

	// Constructor with number of nodes and edges as argument
	Graph(int n, int e)
	{
		N = n;
		E = e;
		adj = new vector<pair<int, int> > [N + 1];
		mst = new pair<int, int> [N + 1];
		total_cost = 0;
	}

	// Adds edge to the undirected graph
	void add_edge(int u, int v, int w)
	{
		adj[u].push_back(make_pair(w, v));
		adj[v].push_back(make_pair(w, u));
	}

	// Prim's Algorithm
	void prims_algorithm(int source)
	{
		int *dist     = new int [N + 1];						// keeps the min. dist. from the MST
		int *edge     = new int [N + 1];						// keeps the node to which it has min. dist.
		bool *visited = new bool[N + 1];						// keeps record of the nodes previously visited
		for(int i = 1; i <= N; ++i) { dist[i] = INT_MAX;  }		// Initiate dist as INFINITY
		for(int i = 1; i <= N; ++i)	{ edge[i] = 0;        }		// Keep edge as NULL
		for(int i = 1; i <= N; ++i) { visited[i] = false; }		// Mark all unvisited

		// Distance of source from the MST is 0
		dist[source] = 0;

		// pq keeps all the current node not included in the MST
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

		// Pushes the source in the pq
		pq.push(make_pair(dist[source], source));

		while(!pq.empty())
		{
			pair<int, int> u = pq.top();							// Node with the min. dist. from the MST
			pq.pop();
			if(visited[u.second]) { continue; }						// If previously visited, ignore

			visited[u.second] = true;								// Mark node as visited

			// Add all its unvisited neighbour to pq, and update their dist
			for(int i = 0; i < adj[u.second].size(); ++i)
			{
				pair<int, int> v = adj[u.second][i];				// Adjacent node
				if(visited[v.second]) { continue; }					// If previously visited, ignore
				if(v.first < dist[v.second])
				{
					dist[v.second] = v.first;						// Update the dist
					edge[v.second] = u.second;						// and edge
					pq.push(make_pair(dist[v.second], v.second));	// then, push again
				}
			}
		}

		// Add the edges to MST and compute minimum total cost
		for(int i = 1; i <= N; ++i)
		{
			mst[i] = make_pair(edge[i], dist[i]);
			total_cost += dist[i];
		}

		delete[] dist;
		delete[] edge;
		delete[] visited;
	}

	// Prints the MST
	void print_mst(void) const
	{
		cout << "\nThe edges of the MST are: \n";
		for(int i = 1; i <= N; ++i)
		{
			cout << i << " -> " << mst[i].first << " = " << mst[i].second << "\n";
		}
		cout << "\nThe total cost is: " << total_cost << "\n";
	}

	// Destructor
	~Graph()
	{
		delete[] adj;
		delete[] mst;
	}
};

int main()
{
	int N, E;
	cout << "Enter the number of cities: ";
	cin >> N;
	cout << "Enter the number of roads: " ;
	cin >> E;
	Graph grph(N, E);
	cout << "Enter the edges: \n\n";
	cout<<"A\t"<<"B\t"<<"Weight"<<endl;
	for(int i = 0; i < E; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		grph.add_edge(u, v, w);
	}
	grph.prims_algorithm(1);
	grph.print_mst();
	return 0;
}
