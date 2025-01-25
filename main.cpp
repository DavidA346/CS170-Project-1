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
    int cost; //g(n)
    int heuristic; //h(n)
    int totalCost; //f(n) = g(n) + h(n)

    //Constructor that sets the node's puzzle to given puzzle as well as all the costs
    Node(int currentPuzzle[3][3], int currentCost = 0, int currentHeuristic = 0) {
        cost = currentCost;
        heuristic = currentHeuristic;
        totalCost = cost + heuristic;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                puzzle[i][j] = currentPuzzle[i][j];
            }
        }
    }

    //Have to overload '>' operator in order to compare two node costs for priority queue
    bool operator>(const Node& rhs) {
        return totalCost > rhs.totalCost;
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
        for (int j = 0; j < 3; ++j) {
            if (goalState[i][j] != currentState->puzzle[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//Helper function that returns the number of misplaced tiles
int misplacedTiles(Node* problem) {
    int count = 0;

    if (problem->puzzle[0][0] != 1) {
        ++count;
    }

    if (problem->puzzle[0][1] != 2) {
        ++count;
    }

    if (problem->puzzle[0][2] != 3) {
        ++count;
    }

    if (problem->puzzle[1][0] != 4) {
        ++count;
    }

    if (problem->puzzle[1][1] != 5) {
        ++count;
    }

    if (problem->puzzle[1][2] != 6) {
        ++count;
    }

    if (problem->puzzle[2][0] != 7) {
        ++count;
    }

    if (problem->puzzle[2][1] != 8) {
        ++count;
    }

    return count;
}

//Helper function that creates the children of the current state
vector<Node*> createChildren(Node* currentState, int useMisplacedTile) {
    //1. Find blank tile
    int blankTileRow;
    int blankTileColumn;
    for (int i  = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (currentState->puzzle[i][j] == 0) {
                blankTileRow = i;
                blankTileColumn = j;
                break;
            }
        }
    }

    //Vector to pushback all children
    vector<Node*> children;

    //Check if blank tile is in position 0,0 in the array
    if (blankTileRow == 0 && blankTileColumn == 0) {
        //Move blank tile right
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[0][1];
        child1->puzzle[0][0] = tileBeingSwapped;
        child1->puzzle[0][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //Push back newly calculated child
        children.push_back(child1);

        //Move blank tile down
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[1][0];
        child2->puzzle[0][0] = tileBeingSwapped;
        child2->puzzle[1][0] = 0;

        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);
    }

    //Check if blank tile is in position 0,1 in the array
    else if (blankTileRow == 0 && blankTileColumn == 1) {
        //Move blank tile right
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[0][2];
        child1->puzzle[0][1] = tileBeingSwapped;
        child1->puzzle[0][2] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile left
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[0][0];
        child2->puzzle[0][1] = tileBeingSwapped;
        child2->puzzle[0][0] = 0;

        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);

        //Move blank tile down
        Node* child3 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child3->puzzle[1][1];
        child3->puzzle[0][1] = tileBeingSwapped;
        child3->puzzle[1][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child3->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        children.push_back(child3);
    }

    //Check if blank tile is in position 0,2 in the array
    else if (blankTileRow == 0 && blankTileColumn == 2) {
        //Move blank tile left
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[0][1];
        child1->puzzle[0][2] = tileBeingSwapped;
        child1->puzzle[0][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile down
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[1][2];
        child2->puzzle[0][2] = tileBeingSwapped;
        child2->puzzle[1][2] = 0;
        
        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);
    }

    //Check if blank tile is in position 1,0 in the array
    else if (blankTileRow == 1 && blankTileColumn == 0) {
        //Move blank tile right
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[1][1];
        child1->puzzle[1][0] = tileBeingSwapped;
        child1->puzzle[1][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile down
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[2][0];
        child2->puzzle[1][0] = tileBeingSwapped;
        child2->puzzle[2][0] = 0;
        
        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);

        //Move blank tile up
        Node* child3 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child3->puzzle[0][0];
        child3->puzzle[1][0] = tileBeingSwapped;
        child3->puzzle[0][0] = 0;

        //Update cost to get to child in this g(n) is always 1
        child3->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        children.push_back(child3);
    }

    //Check if blank tile is in position 1,1 in the array
    else if (blankTileRow == 1 && blankTileColumn == 1) {
        //Move blank tile left
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[1][0];
        child1->puzzle[1][1] = tileBeingSwapped;
        child1->puzzle[1][0] = 0;
        
        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile right
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[1][2];
        child2->puzzle[1][1] = tileBeingSwapped;
        child2->puzzle[1][2] = 0;

        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);

        //Move blank tile down
        Node* child3 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child3->puzzle[2][1];
        child3->puzzle[1][1] = tileBeingSwapped;
        child3->puzzle[2][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child3->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        children.push_back(child3);

        //Move blank tile up
        Node* child4 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child4->puzzle[0][1];
        child4->puzzle[1][1] = tileBeingSwapped;
        child4->puzzle[0][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child4->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child4->heuristic = misplacedTiles(child4);
            child4->totalCost = child4->cost + child4->heuristic;
        }

        children.push_back(child4);
    }

    //Check if blank tile is in position 1,2 in the array
    else if (blankTileRow == 1 && blankTileColumn == 2) {
        //Move blank tile left
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[1][1];
        child1->puzzle[1][2] = tileBeingSwapped;
        child1->puzzle[1][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile down
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[2][2];
        child2->puzzle[1][2] = tileBeingSwapped;
        child2->puzzle[2][2] = 0;

        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);

        //Move blank tile up
        Node* child3 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child3->puzzle[0][2];
        child3->puzzle[1][2] = tileBeingSwapped;
        child3->puzzle[0][2] = 0;

        //Update cost to get to child in this g(n) is always 1
        child3->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        children.push_back(child3);
    }

    //Check if blank tile is in position 2,0 in the array
    else if (blankTileRow == 2 && blankTileColumn == 0) {
        //Move blank tile up
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[1][0];
        child1->puzzle[2][0] = tileBeingSwapped;
        child1->puzzle[1][0] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile right
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[2][1];
        child2->puzzle[2][0] = tileBeingSwapped;
        child2->puzzle[2][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);
    }

    //Check if blank tile is in position 2,1 in the array
    else if (blankTileRow == 2 && blankTileColumn == 1) {
        //Move blank tile left
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[2][0];
        child1->puzzle[2][1] = tileBeingSwapped;
        child1->puzzle[2][0] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile right
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[2][2];
        child2->puzzle[2][1] = tileBeingSwapped;
        child2->puzzle[2][2] = 0;

        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);

        //Move blank tile up
        Node* child3 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child3->puzzle[1][1];
        child3->puzzle[2][1] = tileBeingSwapped;
        child3->puzzle[1][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child3->cost = currentState->cost + 1;

        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        children.push_back(child3);
    }

    //Check if blank tile is in position 2,2 in the array
    else if (blankTileRow == 2 && blankTileColumn == 2) {
        //Move blank tile left
        Node* child1 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        int tileBeingSwapped = child1->puzzle[2][1];
        child1->puzzle[2][2] = tileBeingSwapped;
        child1->puzzle[2][1] = 0;

        //Update cost to get to child in this g(n) is always 1
        child1->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        children.push_back(child1);

        //Move blank tile up
        Node* child2 = new Node(*currentState); //Create an exact copy of current state in order to obtain it's cost, heuristic, and total cost
        tileBeingSwapped = child2->puzzle[1][2];
        child2->puzzle[2][2] = tileBeingSwapped;
        child2->puzzle[1][2] = 0;

        //Update cost to get to child in this g(n) is always 1
        child2->cost = currentState->cost + 1;
        
        //New heuristic addition for the children that calculates a child's misplaced tiles and add it to total cost: f(n) = g(n) + h(n)
        if (useMisplacedTile == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        children.push_back(child2);
    }

    return children;
}

//Have to check if puzzles are the same as we cannot directly compare 2D arrays
bool equalPuzzles(int puzzle1[3][3], int puzzle2[3][3]) {
    //If tile is not the same as other puzzle return false as they are not equal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j){
            if (puzzle1[i][j] != puzzle2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

//General Search Algorithm
Node* generalSearch(Node* problem, int algoChoice) {
    //1.Create priority queue
    priority_queue<Node*, vector<Node*>, greater<Node*> > nodes;
    
    //Create vector of visited nodes to prevent repeat states
    vector<Node*> visited;

    //Push root/initial state to priority queue with the the cost and heuristic cost if misplace tile algo is chosen if not we can skip it
    if (algoChoice == 2) {
        problem->heuristic = misplacedTiles(problem);
        problem->totalCost = problem->cost + problem->heuristic;
    }

    nodes.push(problem);

    //2. Enter while loop to see if we reach goal state and keep looping until nodes is empty
    while (!nodes.empty()) {
        //4. Pop the head node
        Node* currentNode = nodes.top();
        visited.push_back(currentNode);
        nodes.pop();

        //5. If current node is goal node return total cost and exit search
        if (isGoalState(currentNode)) {
            cout << "DONE" << endl;
            cout << "G(n): " << currentNode->cost << endl;
            cout << "H(n): " << currentNode->heuristic << endl;
            cout << "F(n): " << currentNode->totalCost << endl;
            return currentNode;
            break;
        }

        //6. Else enqueue all the children of current node with total cost from current node and add current node to visited list
        else {
            //Get vector of all of currentNode's children
            vector<Node*> children = createChildren(currentNode, algoChoice);

            //Erase any children that were already visited
            for (int i = 0; i < children.size(); ++i) {
                bool hasBeenVisited = false;
                for (int j = 0; j < visited.size(); ++j) {
                    if (equalPuzzles(children.at(i)->puzzle, visited.at(j)->puzzle)) {
                        hasBeenVisited = true;
                        break;
                    }
                }

                //Erase a child that has been visited already to prevent visiting the same child
                if (hasBeenVisited) {
                    children.erase(children.begin() + i);
                    --i;
                }
            }

            //Enqueue all new unvisited children to queue
            for (int i = 0; i < children.size(); ++i) {
                nodes.push(children.at(i));
            }
        }
    }

    //3.If priority queue is empty then return 'No solution'
    cout << "No solution found" << endl;
    return nullptr;
}

int main() {
    //Puzzle user enters
    int userPuzzle[3][3];
    int algoChoice;

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

    cout << endl;
    cout << "Enter 1 for Uniform Cost Search or 2 for Misplaced Tile Heuristic: " << endl;
    cin >> algoChoice;

    Node* problem = new Node(userPuzzle);
    Node* solvedPuzzle = generalSearch(problem, algoChoice);

    for (int i = 0; i < 3; ++i) {
        cout << "(";
        for (int j = 0; j < 3; ++j) {
            cout << solvedPuzzle->puzzle[i][j];
        }
        cout << ")" << endl;
    }

    return 0;
}