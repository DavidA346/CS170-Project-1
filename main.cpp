#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Priority queue data structure that enqueues nodes in order of cost
    //Pop first node at the beginning
    //Needs to be able pop top cheapest costing node from queue (highest priority)
    //Basically need a queue and each node in queue needs its associating cost 

//Tree Structure
    //Pop off cheapest costing node and if not goal state expands all its children
    //Create a binary tree structure expanding the cheapest node until we reach the first possible goal state
    //Need to keep track of current cost at any given node
    //Only search new paths and not already visted paths
    //if tie between costs choose first (does not matter
    //Return path to goal state and total cost

//Node struct that encapsulates all the necessary info for a node
struct Node {
    int puzzle[3][3];

    //Constructor that sets the node's puzzle to given puzzle
    Node(int currentPuzzle[3][3]) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j){
                puzzle[i][j] = currentPuzzle[i][j];
            }
        }
    }
};

//Helper function that checks if goal is reached
bool isGoalState(Node* currentState) {
    int goalState[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j){
            if (goalState[i][j] != currentState->puzzle[i][j]){
                return false;
            }
        }
    }
    return true;
}

//Helper function that creates the children of the current state
// vector<Node*> createChildren(Node* currentState) {

// }

//Uniform Cost Search Algorithm
void uniformCostSearch(Node* &problem){
    //1.Create priority queue
    priority_queue<Node*> nodes;
    //Create vector of visited nodes to prevent repeat states
    vector<Node*> visited;

    //Push root/initial state to priority queue
    nodes.push(problem);

    //2. Enter while loop to see if we reach goal state and keep looping until nodes is empty
    while (!nodes.empty()) {
        //3.If priority queue is empty then return 'No solution'
        if (nodes.empty()) {
            cout << "No solution found" << endl;
        }

        //4. Pop the head node
        Node* currentNode = nodes.top();
        visited.push_back(currentNode);
        nodes.pop();

        //5. If current node is goal node return total cost and exit search
        if (isGoalState(currentNode)) {
            cout << "DONE" << endl;
        }

        //6. Else enqueue all the children of current node with total cost from current node and add current node to visited list
        else {
            //TODO: Create children and enqueue them
            cout << "need to enqueue children" << endl;
        }
    }
}

int main() {
    //Puzzle user enters
    int userPuzzle[3][3];

    //Prompt user to enter a puzzle
    cout << "Welcome to the 8 puzzle!!!" << endl;
    cout << "Please enter a puzzle of your choosing" << endl;
    cout << "Make sure to enter the eight numbers in any order and enter a '0' to denote the blank tile: " << endl;

    //Push into vector user puzzle
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int input;
            cin >> input;
            userPuzzle[i][j] = input;
        }
    }

    Node* problem = new Node(userPuzzle);
    uniformCostSearch(problem);

    return 0;
}