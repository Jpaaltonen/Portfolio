#include <iostream>
#include <stack>
#include <map>
#include <utility>
#include <vector>
//Exercises from Steven Skiena's The Algortihm Design Manual 2nd Edition chapter 3
//Coursework for a course in application efficiency
//Although functions remain uncommented, tester codes in main are commented for practical reasons - uncomment the ones you wish to try

using namespace std;
//3-1
bool checkParentheses(string s)
{
	stack<int> p = stack<int>();
	int len = s.size();

	//Loop through the string character by character
	for (int i = 0; i < len; i++)
	{
		//If the character is opening parentheses, push it's index number to the stack
		if (s[i] == '(')
			p.push(i);

		//If the character is closing parentheses attempt to pop an index number out of the stack - if the stack is empty, there is no opening parentheses
		if (s[i] == ')' && p.empty())
		{
			cout << "Unopened parentheses at " << (i + 1) << endl; //A minor thing, but the first character is character number 1, not number 0, so add 1 to the index
			return false;
		}
		if (s[i] == ')' && !p.empty())
			p.pop();
	}

	//If the stack is not empty after looping through the string, there is (at least) one unclosed parentheses
	//The topmost element in the stack is it's index number - Looping and popping indexes until the stack is empty allows
	//Us to print out all the positions of the unclosed parentheses
	if (!p.empty())
	{
		cout << "Unclosed parentheses at ";
		while (!p.empty())
		{
			cout << (p.top() + 1) << " ";
			p.pop();
		}
		cout << endl;
		return false;
	}
	else
		return true;
}

//3-2
class Node
{
public:
	int data;
	Node* next;

	Node(int d)
	{
		data = d;
	}

	~Node()
	{
		delete next;
	}
};


void reverse(Node** head)
{
	if (!head) //empty list
		return;

	Node* curr, * prev, * next;
	curr = *head;
	prev = NULL;
	next = NULL;

	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

void printList(Node* n)
{
	while (n != NULL)
	{
		cout << n->data << " ";
		n = n->next;
	}
	cout << endl;
}


//3-9
class BST
{



public:
	int data;
	BST* left, * right;
	BST()
	{
		data = 0;
		left = NULL;
		right = NULL;
	}

	BST(int n)
	{
		data = n;
		left = NULL;
		right = NULL;
	}

	BST* insert(BST* root, int n)
	{
		if (!root)
		{
			return new BST(n);
		}
		if (n <= root->data)
		{
			root->left = insert(root->left, n);
		}
		else
		{
			root->right = insert(root->right, n);
		}
		return root;
	}

	void showTree(BST* root)
	{
		if (!root)
			return;
		showTree(root->left);
		cout << root->data << endl;
		showTree(root->right);
	}

	BST* getMin(BST* root)
	{
		BST* parent = NULL;
		while (root->left)
		{
			parent = root;
			root = root->left;
		}

		//A quick and dirty way to remove a node from a tree. Since we only care about removing the minimum node (we don't want the minimum to appear twice),
		//And the other assignments don't require removal or finding a minimum, this will suffice
		if (root->right)
			parent->left = root->right;
		else
			parent->left = NULL;
		return root;

	}

	~BST()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}


};

//3-11
//Just a quick helper function for testing the algorithm - algorithm itself can be found in main
int findMin(int a[], int i, int j, int n)
{
	return a[i * n + j];
}


//3-20
Node* findMiddle(class Node* node)
{
	Node* fast = node, * slow = node;

	while (fast && fast->next)
	{
		//Move one pointer ahead twice the speed than the slower one - when it reaches the end, the slower one is at the middle
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

//3-26
string invertString(string s)
{
	vector<string> v;
	string tmp = "";
	int i = 0;
	while (i < s.length())
	{
		if (s[i] == ' ')
		{
			v.push_back(tmp);
			tmp = "";
		}
		else
			tmp += s[i];
		i++;
	}
	v.push_back(tmp);
	s = "";
	for (int i = v.size()-1; i >=0; i--)
	{
		s += v[i] + " ";
	}
	return s;
}

//3-27
//While traversing through the list we'll use a map to keep track of nodes (key) and their indexes (value)
//If a node is found from the map, we return a pair of ints with the indexes of the start and endpoints
pair<int, int> findLoop(Node* node)
{
	map<Node*, int> m;
	int curr = 0;
	while (node->next)
	{
		if (m.find(node) != m.end())
		{
			return make_pair(curr - 1, m[node]); //Subtract from the current index, since the loop started at the previous node
		}
		m.insert({ node, curr });
		curr++;
		node = node->next;
	}
	return make_pair(-1, -1); //Return negatives if no loop was found
}


//Testing codes
int main()
{
	//3-1
	/*string s = "(()(()(";
	checkParentheses(s);*/

	//3-9
	/*	
	BST bst, bst2, bst3, * root = NULL, * root2 = NULL, * root3 = NULL, * min = NULL;
	root = bst.insert(root, 3);
	bst.insert(root, 1);
	bst.insert(root, 2);
	bst.insert(root, 5);
	bst.insert(root, 4);

	root2 = bst2.insert(root2, 14);
	bst.insert(root2, 11);
	bst.insert(root2, 12);
	bst.insert(root2, 10);
	bst.insert(root2, 13);
	bst.insert(root2, 15);

	cout << "\nbst1:" << endl;
	bst.showTree(root);
	cout << "\nbst2:" << endl;
	bst2.showTree(root2);
	min = bst2.getMin(root2);
	cout << "\nbst2 after deleting min value:" << endl;
	bst2.showTree(root2);
	root3 = bst3.insert(root3, min->data); //Create a third BST with minimun leaf from the second tree as root
	root3->left = root; //Assign root from tree 1 as left leaf
	root3->right = root2; //Assign root from tree 2 as right leaf

	cout << "\nbst3:" << endl;
	bst2.showTree(root3);
	delete root;
	delete root2;
	delete min;
	*/


	//3-11
	/*
	const int n = 10;
	int max = 0, iMin;
	int arr[n],lookup[n*n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
		//if (arr[i] > max)
		//	max = arr[i];
		cout << "Value in index " << i << " in array: " << arr[i] << endl;
	}

	int cnt = 0;
	for (int i = 0; i < n ; i++)
		for (int j = i ; j < n; j++)
			cnt++;

	cout << cnt << endl;

	//Go through every possible combination of ranges, and store the minimum value into a lookup table
	for (int i = 0; i < n-1 ; i++)
		//Since we are speaking of ranges we are dealing with at least two numbers, so j must always be larger than i
		//Admittedly, this reduces the space needed for the lookup table from n*n to the arithmetic sum of n-1
		//If a range CAN be only one then the demand for space would be sum of n - in both cases rest of the table is left unused
		//Technically this solution misses both a) AND b)
		for (int j = i+1; j < n; j++)
		{
			iMin = arr[i]; //Set the defaul min value as the ith element in array - the first in range to be checked
			for (int k = i; k <= j; k++)
			{
				if (arr[k] < iMin)
					iMin = arr[k];
			}
			lookup[i * n + j] = iMin;
		}

	//Proof - draw random ranges and compare the minimum with original array
	for (int k = 0; k < 25; k++)
	{
		int i = rand() % (n - 1);
		int j = 0;
		while (j <= i)
		{
			j = 1+rand() % (n-1);
		}
		cout << "Min value in range " << i << " and " << j << ": " << findMin(lookup, i, j, n) << endl;
	}
	*/


	//3-19
	//Sort shirts by some attribute (e.g. color), do a binary search


	//3-2, 3-20 & 3-27 can be all found here
	/*
	Node* head, * first, * second, * third, *mid;
	head = new Node(1);
	first = new Node(2);
	second = new Node(3);
	third = new Node(4);
	head->next = first;
	first->next = second;

	//3-2
	printList(head);
	reverse(&head);
	printList(head);

	//3-20
	mid = findMiddle(head);
	cout << "Data in the middle element of the list: "<< mid->data << endl;

	//3-27
	reverse(&head); //Revert the list back to original - I had these exercises as separate at first and couldn't be bothered to reassign the loop
	second->next = first; //Create the loop
	pair<int, int> res = findLoop(head);
	res.first == -1 ? cout << "No loop found" << endl : cout << "Loop found from index " << res.first << " to " << res.second << endl;

	second->next = third; //Remove the loop
	res = findLoop(head);
	res.first == -1 ? cout << "No loop found" << endl : cout << "Loop found from index " << res.first << " to " << res.second << endl;

	delete head;
	*/

	//3-26
	/*
	string s = "aa bb cc dd ee";
	cout <<"\""<<s << "\"" <<" inverted is " << "\"" <<invertString(s) << "\"" <<endl;
	*/

}

