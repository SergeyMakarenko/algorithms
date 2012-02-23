#include <iostream>
#include <set>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int const ALPHABET_SIZE = 26 + 1;
int const TOTAL_LEN = 51 * 2001;

struct edge_t
{
	edge_t(int parent_node = 0, int child_node = 0, int first_char = 0, int last_char = 0):
		start_node(parent_node), end_node(child_node), start_char(first_char), end_char(last_char)
		{	
		}
	int start_char;
	int end_char;
	int start_node;
	int end_node;
};

struct node_t
{
	node_t():
		suffix_link(-1)
	{
	}

	pair<edge_t, int> edges[ALPHABET_SIZE];
	int suffix_link;
};


node_t nodes[2 * TOTAL_LEN];
int nodes_index = 0;

string str;
int active_node;
int active_start;
int active_end;

int char2index(char ch)
{
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 1;

	return 0;
}

void canonize()
{
	while (active_start <= active_end)
	{
		edge_t& edge = nodes[active_node].edges[char2index(str[active_start])].first;
		int span = edge.end_char - edge.start_char + 1;
		if (span > active_end - active_start + 1)
			break;

		active_start += span;
		active_node = edge.end_node;
	}
}

void add(int cur_pos)
{
	static int cnt = 0;
	cnt++;
	int parent_node;
	int last_node = 0;
	char cur_char = str[cur_pos];

	while (true)
	{
		if (active_start > active_end)
		{
			parent_node = active_node;
			if (nodes[active_node].edges[char2index(cur_char)].second > 0)
				break;
		}
		else
		{
			edge_t &edge = nodes[active_node].edges[char2index(str[active_start])].first;
			int span = active_end - active_start + 1;
			if (str[edge.start_char + span] == cur_char)
				break;
			parent_node = ++nodes_index;
			edge_t upper_edge = edge_t(active_node, parent_node, edge.start_char, edge.start_char + span - 1);
			edge_t bottom_edge = edge_t(parent_node, edge.end_node, edge.start_char + span, edge.end_char);
			nodes[parent_node].edges[char2index(str[edge.start_char + span])] = make_pair(bottom_edge, 1);
			edge = upper_edge;
		}

		nodes[parent_node].edges[char2index(cur_char)] = make_pair(edge_t(parent_node, ++nodes_index, cur_pos, str.size() - 1), 1);
		if (last_node > 0)
			nodes[last_node].suffix_link = parent_node;
		last_node = parent_node;
		if (active_node == 0)
			active_start++;
		else
		{
			if (nodes[active_node].suffix_link == -1)
				int a = 0;
			active_node = nodes[active_node].suffix_link;
		}

		canonize();
	}

	if (last_node > 0)
		nodes[last_node].suffix_link = parent_node;
	
	active_end++;
	canonize();
}

void dump_tree(int cur_node)
{
	node_t& node = nodes[cur_node];

	if (node.suffix_link != -1)
		cout << "Suffix link from " << cur_node << " to " << node.suffix_link << endl;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (node.edges[i].second > 0)
		{
			edge_t& edge = node.edges[i].first;
			cout << "Edge from " << edge.start_node << " to " << edge.end_node << "; (" << edge.start_char << ", " << edge.end_char << ") = ";
			for (int j = edge.start_char; j <= edge.end_char; j++)
				cout << str[j];
			cout << endl;

		}
	}

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (node.edges[i].second > 0)
		{
			edge_t& edge = node.edges[i].first;
			dump_tree(edge.end_node);
		}
	}


}

void print_string(int cur_node, int k)
{
	if (k == 0)
		return;

	int i = 1;

	node_t& node = nodes[cur_node];

	while (k > node.edges[i].second)
	{
		k -= node.edges[i].second;
		i++;
	}
	edge_t& edge = node.edges[i].first;
	for (int i = edge.start_char; i <= edge.end_char && k > 0; i++, k--)
		cout << str[i];
	if (k > 0)
		print_string(edge.end_node, k);
}

int count_substrings(int cur_node)
{
	node_t &node = nodes[cur_node];
	for (int i = 1; i < ALPHABET_SIZE; i++)
	{
		if (node.edges[i].second > 0)
		{
			edge_t& edge = node.edges[i].first;
			if (str[edge.end_char] == '$')
				edge.end_char--;

			node.edges[i].second = edge.end_char - edge.start_char  + 1 + count_substrings(edge.end_node);
		}
	}

	int cnt = 0;
	for (int i = 1; i < ALPHABET_SIZE; i++)
		cnt += node.edges[i].second;

	return cnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int prev_size = 0;
	int n;
	cin >> n;
	str.reserve(TOTAL_LEN);

	string cur_str;
	getline(cin, cur_str);
	for (int i = 0; i < n; i++)
	{
		getline(cin, cur_str);
		cur_str += "$";
		active_node = 0;
		active_start = str.size();
		active_end = active_start - 1;
		prev_size = str.size();
		str += cur_str;

		for (int i = prev_size; i < str.size(); i++)
		{
//			cout << endl << "Adding prefix " << str.substr(prev_size, i + 1 - prev_size) << endl;
//			cout << "Active node " << active_node << "; active_start " << active_start << "; active_end " << active_end << " (";
//			for (int j = active_start; j <= active_end; j++)
//				cout << str[j];
//			cout << ")" << endl;
			add(i);
//			dump_tree(0);
		}
	}


	int total = count_substrings(0);
		 
	int q;
	cin >> q;
	while(q-- > 0)
	{
		int k;
		cin >> k;
		if (k > total)
		{
			cout << "INVALID\n";
			continue;
		}

		print_string(0, k);
		cout << endl;
	}

	return 0;
}
