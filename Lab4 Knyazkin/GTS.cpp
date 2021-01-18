#include "GTS.h"
unordered_map<int, Pipe> pGroup = unordered_map<int, Pipe>{};
unordered_map<int, CS> csGroup = unordered_map<int, CS>{};

GTS::GTS() { }

GTS::GTS(ifstream& fin)
{
	pGroup.clear();
	csGroup.clear();
	int pSize;
	int csSize;
	fin >> pSize;
	fin >> csSize;
	fin >> Pipe::pMaxId;
	fin >> CS::csMaxId;
	while (pSize--)
	{
		int id;
		fin >> id;
		pGroup.insert(make_pair(id, Pipe(fin)));
	}
	while (csSize--)
	{
		int id;
		fin >> id;
		csGroup.insert(make_pair(id, CS(fin)));
	}
}

void GTS::SaveToFile(ofstream& fout)
{
	fout << pGroup.size() << '\n'
		<< csGroup.size() << '\n'
		<< Pipe::pMaxId << '\n'
		<< CS::csMaxId << '\n';
	for (pair<int, Pipe> p : pGroup)
	{
		fout << p.first << '\n';
		p.second.SaveToFile(fout);
	}
	for (pair<int, CS> cs : csGroup)
	{
		fout << cs.first << '\n';
		cs.second.SaveToFile(fout);
	}
}

ostream& operator << (ostream& out, const GTS& gtn)
{
	out << "���������� ���� - " << gtn.pGroup.size() << "\n";
	for (const pair<int, Pipe>& p : gtn.pGroup)
	{
		out << "����� " << p.first << ".\n";
		out << p.second;
	}
	out << "���������� �� - " << gtn.csGroup.size() << "\n";
	for (const pair<int, CS>& cs : gtn.csGroup)
	{
		out << "������������� ������� " << cs.first << ".\n";
		out << cs.second;
	}
	return out;
}

template <typename T>
int GetInputId(const unordered_map<int, T>& objGroup)
{
	int id;
	while (true)
	{
		CheckValue(id, "������� ID (0 - �����): ");
		if (id == 0)
		{
			cout << "�� ����� �� ������ ������ �� ID.\n";
			return -1;
		}
		else if (objGroup.count(id))
		{
			return id;
		}
		cout << "������ ID �� ����������. ����������, ������� ������������ ID.\n";
	}
}

template <typename TParam, typename TObj>
using Filter = bool(*)(const TObj& obj, TParam param);

bool CheckPipeByRepairing(const Pipe& p, bool param)
{
	return p.GetRepairing() == param;
}

bool CheckCsByName(const CS& cs, string param)
{
	return cs.GetName() == param;
}

bool CheckCsByUnusedShops(const CS& cs, float param)
{
	return cs.GetPercentUnusedShops() <= param;
}

template <typename TFilter, typename TObj>
vector<int> FindObjByFilter(const unordered_map<int, TObj>& group, Filter<TFilter, TObj> f, TFilter param)
{
	vector <int> res;
	for (const pair<int, TObj>& obj : group)
		if (f(obj.second, param))
			res.push_back(obj.first);
	return res;
}

vector < vector < int>> GTS::GetEdgesAndVertexes(unordered_map<int, int>& indexVertexes, int& n)
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.outCsId);
			vertexes.insert(p.second.inCsId);
		}
	n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector < vector < int>> edges;
	edges.resize(n);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			edges[invertIndexVertexes[p.second.outCsId]].push_back(invertIndexVertexes[p.second.inCsId]);
	return edges;
}

void topologicalSortUtil(int v, bool visited[], stack<int>& Stack, vector < vector < int>>& edges)
{
	visited[v] = true;

	vector<int>::iterator i;
	for (i = edges[v].begin(); i != edges[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack, edges);

	Stack.push(v);
}

bool dfs(int v, vector<char>& cl, vector<int>& p, int& cycle_st, const vector < vector < int>>& edges) {
	cl[v] = 1;
	for (size_t i = 0; i < edges[v].size(); ++i) {
		int to = edges[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			if (dfs(to, cl, p, cycle_st, edges))
				return true;
		}
		else if (cl[to] == 1) {
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}

bool HasCycle(vector < vector < int>>& edges, int n)
{
	vector<char> cl;
	vector<int> p;
	int cycle_st;
	p.assign(n, -1);
	cl.assign(n, 0);
	cycle_st = -1;
	for (int i = 0; i < n; ++i)
		if (dfs(i, cl, p, cycle_st, edges))
			break;

	if (cycle_st == -1)
	{
		return false;
	}
	else
	{
		cout << "��������! � ����� ���� ����, ���������� �������� ����������!\n";
		return true;
	}
}

void GTS::TopologicalSort()
{
	unordered_map<int, int> indexVertexes;
	int n;
	vector < vector < int>> edges = GetEdgesAndVertexes(indexVertexes, n);
	if (HasCycle(edges, n) == false)
	{
		stack<int> Stack;

		bool* visited = new bool[n];
		for (int i = 0; i < n; i++)
			visited[i] = false;

		for (int i = 0; i < n; i++)
			if (visited[i] == false)
				topologicalSortUtil(i, visited, Stack, edges);

		while (Stack.empty() == false)
		{
			cout << "�� " << indexVertexes[Stack.top()] << " -> ";
			Stack.pop();
		}
	}
}

int min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}

void Enque(int x, vector<int>& q, int& tail, vector<int>& color)
{
	q[tail] = x;
	tail++;
	color[x] = 1;
}

int bfs(int start, int end, vector<int>& color, vector<int>& pred, vector<int>& q, vector < vector < int>>& capacity, vector < vector < int>>& flow, int n, int& head, int& tail)
{
	for (int u = 0; u < n; u++)
		color[u] = 0;

	head = 0;
	tail = 0;
	Enque(start, q, tail, color);
	pred[start] = -1;
	while (head != tail)
	{
		int u = q[head];
		head++;
		color[u] = 2;
		for (int v = 0; v < n; v++)
		{
			if (color[v] == 0 && (capacity[u][v] - flow[u][v]) > 0) {
				Enque(v, q, tail, color);
				pred[v] = u;
			}
		}
	}
	if (color[end] == 2)
		return 0;
	else return 1;
}

void WritePath(int* T, int Start, int Vertex, unordered_map<int, int> indexVertexes)
{
	if (Vertex != Start)
		WritePath(T, Start, T[Vertex], indexVertexes);
	cout << indexVertexes[Vertex] << ' ';
}

void Dijkstra(const vector < vector < int>>& G, int N, int start, unordered_map<int, int> indexVertexes)
{
	int min, index;
	int* D;
	int* V;
	int* T;
	V = (int*)malloc(N * sizeof(int));
	D = (int*)malloc(N * sizeof(int));
	T = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
	{
		V[i] = 0;
		D[i] = INT_MAX;
		T[i] = -1;
	}
	T[start] = 0;
	D[start] = 0;
	for (int count = 0; count < N - 1; count++)
	{
		min = INT_MAX;
		for (int i = 0; i < N; i++)
			if ((V[i] == 0) && (D[i] <= min))
			{
				min = D[i];
				index = i;
			}
		V[index] = 1;
		for (int i = 0; i < N; i++)
			if ((V[i] == 0) && (G[index][i] != 0) && (D[index] != INT_MAX) && ((D[index] + G[index][i]) < D[i]))
			{
				D[i] = D[index] + G[index][i];
				T[i] = index;
			}

	}
	printf("���������� ����:\n");
	for (int i = 0; i < N; i++)
		if (D[i] != INT_MAX)
		{
			cout << indexVertexes[start] << " -> " << indexVertexes[i] << " = " << D[i] << '\n';
			cout << " ���� ����� ����� �������: ";
			WritePath(T, start, i, indexVertexes);
			cout << '\n';
		}
		else
		{
			cout << "���� " << indexVertexes[start] << " -> " << indexVertexes[i] << " �� ����������\n";
		}
}

void GTS::FindShortestPath()
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.outCsId);
			vertexes.insert(p.second.inCsId);
		}
	int n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	unordered_map<int, int> indexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector < vector < int>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i].push_back(0);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			graph[invertIndexVertexes[p.second.outCsId]][invertIndexVertexes[p.second.inCsId]] = p.second.GetLength();

	int start;
	CheckValue(start, "������� ID ��, �� ������� ����� ��������� ���� (0 - �����): ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "������! ����� �� ��� � ����((";
		return;
	}
	Dijkstra(graph, n, start, indexVertexes);
}

void GTS::AddPipe()
{
	Pipe p;
	cin >> p;

	pGroup.insert(make_pair(++Pipe::pMaxId, p));
}

void GTS::AddCs()
{
	CS cs;
	cin >> cs;
	csGroup.insert(make_pair(++CS::csMaxId, cs));
}

bool GTS::HasPipe() const
{
	return pGroup.size() != 0;
}

bool GTS::HasCs(int count) const
{
	return csGroup.size() >= count;
}

void GTS::EditPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
		pGroup[id].Edit();
}

void GTS::EditCs()
{
	int id = GetInputId(csGroup);
	if (id != -1)
	{
		cout << "\n��� �� ������ ������� � ��?\n"
			<< "1 - ���������/��������� ����� ���������� �����\n"
			<< "2 - �������� ���������� ���������� �����\n"
			<< "0 � ��. - ������\n";
		int input;
		CheckValue(input, "�������: ");
		switch (input)
		{
		case 1:
			csGroup[id].RecountShopsCount();
			break;
		case 2:
			csGroup[id].RecountWorkingShopsCount();
			break;
		default:
			cout << "�� ����� �� ������ ��������������.";
			break;
		}
	}
}

void GTS::DeletePipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		pGroup.erase(id);
		cout << "����� ������� �������!\n";
	}
}

void GTS::DeleteCs()
{
	int id = GetInputId(csGroup);
	if (id != -1)
	{
		csGroup.erase(id);
		cout << "�� ������� �������!\n";
	}
}

void GTS::SearchPipes()
{
	int input;
	CheckValue(input, "���� ����� � �������? (1 - ��, 2 - ���, ��. - �����)\n");
	switch (input)
	{
	case 1:
	{
		for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, true))
		{
			cout << "����� " << i << ".\n";
			cout << pGroup[i];
		}
		break;
	}
	case 2:
	{
		for (int i : FindObjByFilter(pGroup, CheckPipeByRepairing, false))
		{
			cout << "����� " << i << ".\n";
			cout << pGroup[i];
		}
		break;
	}
	default:
		cout << "����� �� ������ ������ ����\n";
		break;
	}
	cout << "\n�� ������ ��������������� ��� �����?\n"
		<< "1 - �������� ���\n"
		<< "0 � ��. - �����\n";
	CheckValue(input, "�������: ");
	if (input == 1)
	{
		for (pair<int, Pipe> p : pGroup)
			p.second.Repair();
		cout << "��� ��������� ����� ������� ��������!\n";
	}
}

void GTS::SearchCss()
{
	int input;
	cout << "�� ������ ������� ���� ��?\n";
	CheckValue(input, "(1 - �� ��������, 2 - �� �������� ����������������� �����, ��. - �����): ");
	switch (input)
	{
	case 1:
	{
		string name;
		cout << "������� ��� �� ��� ����������: ";
		cin.ignore();
		getline(cin, name);
		for (int i : FindObjByFilter(csGroup, CheckCsByName, name))
		{
			cout << "������������� ������� " << i << ".\n";
			cout << csGroup[i];
		}
		break;
	}
	case 2:
	{
		float percent;
		CheckValue(percent, "������� ������� ��� ���������� (��������� �� � ��������� ������ ����������): ");
		for (int i : FindObjByFilter(csGroup, CheckCsByUnusedShops, percent))
		{
			cout << "������������� ������� " << i << ".\n";
			cout << csGroup[i];
		}
		break;
	}
	default:
		cout << "����� �� ������ ������ ����\n";
		break;
	}
}

void GTS::ConnectPipe()
{
	cout << "������� ID �����:\n";
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		cout << "��, �� ������� ������� �����:\n";
		int outCsId = GetInputId(csGroup);
		cout << "��, � ������� ������ �����:\n";
		int inCsId = GetInputId(csGroup);
		while (inCsId == outCsId)
		{
			cout << "����� �� ����� ������� � �� �� ����� ��! ������� ������ Id:\n";
			int inCsId = GetInputId(csGroup);
		}
		if (outCsId != -1 && inCsId != -1)
		{
			pGroup[id].outCsId = outCsId;
			pGroup[id].inCsId = inCsId;
		}
	}
	else
	{
		cout << "����� �� ������ ����� ����� � ��...\n";
	}
}

void GTS::DisonnectPipe()
{
	int id = GetInputId(pGroup);
	if (id != -1)
	{
		pGroup[id].outCsId = -1;
		pGroup[id].inCsId = -1;
	}
	else
	{
		cout << "����� �� ������ ����� ����� � ��...\n";
	}
}

bool GTS::CanBeUsed(const Pipe& p) const
{
	return p.inCsId > 0 &&
		p.outCsId > 0 &&
		!p.GetRepairing() &&
		csGroup.find(p.inCsId) != csGroup.end()
		&& csGroup.find(p.outCsId) != csGroup.end();
}

void GTS::ShowNetwork()
{
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			cout << "�� " << p.second.outCsId << " � ����� " << p.first << " -> �� " << p.second.inCsId << '\n';
}

void GTS::FindMaxFlow()
{
	set<int> vertexes;
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
		{
			vertexes.insert(p.second.outCsId);
			vertexes.insert(p.second.inCsId);
		}
	int n = vertexes.size();
	unordered_map<int, int> invertIndexVertexes;
	unordered_map<int, int> indexVertexes;
	int i = 0;
	for (const int& vertex : vertexes)
	{
		indexVertexes.insert(make_pair(i, vertex));
		invertIndexVertexes.insert(make_pair(vertex, i++));
	}
	vector < vector < int>> graph;
	graph.resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i].push_back(0);
	for (const pair<int, Pipe>& p : pGroup)
		if (CanBeUsed(p.second))
			graph[invertIndexVertexes[p.second.outCsId]][invertIndexVertexes[p.second.inCsId]] = p.second.GetProductivity();

	int start;
	CheckValue(start, "������� ID ��, �� ������� ����� ���� ����� (0 - �����): ");
	if (invertIndexVertexes.find(start) != invertIndexVertexes.end())
		start = invertIndexVertexes[start];
	else
	{
		cout << "������! ����� �� ��� � ����((";
		return;
	}
	int end;
	CheckValue(end, "������� ID ��, � ������� ����� ����� (0 - �����): ");
	if (invertIndexVertexes.find(end) != invertIndexVertexes.end())
		end = invertIndexVertexes[end];
	else
	{
		cout << "������! ����� �� ��� � ����((";
		return;
	}

	int head, tail;
	vector < vector < int>> flow;
	vector<int> color, pred, q;

	int maxflow = 0;
	flow.resize(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			flow[i].push_back(0);
		color.push_back(-1);
		pred.push_back(-1);
		q.push_back(0);
	}
	q.push_back(0); q.push_back(0);
	while (bfs(start, end, color, pred, q, graph, flow, n, head, tail) == 0)
	{
		int delta = 10000;
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			delta = min(delta, (graph[pred[u]][u] - flow[pred[u]][u]));
		}
		for (int u = end; pred[u] >= 0; u = pred[u])
		{
			flow[pred[u]][u] += delta;
			flow[u][pred[u]] -= delta;
		}
		maxflow += delta;
	}
	cout << "������������ �����: " << maxflow << endl;
}