#include <iostream>
#include <vector>
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

//Uniform Cost Search Algorithm
    //1.Create priority queue
    //2. Enter while loop to see if we reach goal state
        //3.If priority queue is empty then return 'No solution'
        //4.Pop the head node
        //4.If current node is goal node return total cost and exit search
        //5.Else enqueue all the children of current node with total cost from current node and add current node to visited list
        
int main() {
    //Puzzle user enters
    vector<int> userPuzzle;

    //Prompt user to enter a puzzle
    cout << "Welcome to the 8 puzzle!!!" << endl;
    cout << "Please enter a puzzle of your choosing" << endl;
    cout << "Make sure to enter the eight numbers in any order and enter a '0' to denote the blank tile: " << endl;

    //Push into vector user puzzle
    for (int i = 0; i < 9; ++i) {
        int input;
        cin >> input;
        userPuzzle.push_back(input);
    }

    return 0;
}