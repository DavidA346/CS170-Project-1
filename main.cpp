#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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
};

//To compare two node costs we need a custom comparator as overloading the > operator does not work with pointers
struct cheapestCost{
    bool operator()(Node* lhs, Node* rhs) {
        return lhs->totalCost > rhs->totalCost;
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

//Helper function that returns the manhattan distance
int calculateDistance(int tile, Node* problem) {
    //Initialize totalDistance to 0
    int totalDistance = 0;

    //For tile 1 we calculate the distance given its position in the puzzle
    if ((tile == 1 && (problem->puzzle[0][1] == 1)) || (tile == 1 && (problem->puzzle[1][0] == 1))) {
        totalDistance += 1;
    }

    else if ((tile == 1 && (problem->puzzle[0][2] == 1)) || (tile == 1 && (problem->puzzle[1][1] == 1)) || (tile == 1 && (problem->puzzle[2][0] == 1))) {
        totalDistance += 2;
    }

    else if ((tile == 1 && (problem->puzzle[1][2] == 1)) || (tile == 1 && (problem->puzzle[2][1] == 1))) {
        totalDistance += 3;
    }

    else if (tile == 1 && (problem->puzzle[2][2] == 1)) {
        totalDistance += 4;
    }

    //For tile 2 we calculate the distance given its position in the puzzle
    if ((tile == 2 && (problem->puzzle[0][0] == 2)) || (tile == 2 && (problem->puzzle[0][2] == 2)) || (tile == 2 && (problem->puzzle[1][1] == 2))) {
        totalDistance += 1;
    }

    else if ((tile == 2 && (problem->puzzle[1][0] == 2)) || (tile == 2 && (problem->puzzle[1][2] == 2)) || (tile == 2 && (problem->puzzle[2][1] == 2))) {
        totalDistance += 2;
    }

    else if ((tile == 2 && (problem->puzzle[2][0] == 2)) || (tile == 2 && (problem->puzzle[2][2] == 2))) {
        totalDistance += 3;
    }
    
    //For tile 3 we calculate the distance given its position in the puzzle
    if ((tile == 3 && (problem->puzzle[0][1] == 3)) || (tile == 3 && (problem->puzzle[1][2] == 3))) {
        totalDistance += 1;
    }

    else if ((tile == 3 && (problem->puzzle[0][0] == 3)) || (tile == 3 && (problem->puzzle[1][1] == 3)) || (tile == 3 && (problem->puzzle[2][2] == 3))) {
        totalDistance += 2;
    }

    else if ((tile == 3 && (problem->puzzle[1][0] == 3)) || (tile == 3 && (problem->puzzle[2][1] == 3))) {
        totalDistance += 3;
    }

    else if (tile == 3 && (problem->puzzle[2][0]) == 3) {
        totalDistance += 4;
    }

    //For tile 4 we calculate the distance given its position in the puzzle
    if ((tile == 4 && (problem->puzzle[0][0] == 4)) || (tile == 4 && (problem->puzzle[2][0] == 4)) || (tile == 4 && (problem->puzzle[1][1] == 4))) {
        totalDistance += 1;
    }

    else if ((tile == 4 && (problem->puzzle[0][1] == 4)) || (tile == 4 && (problem->puzzle[2][1] == 4)) || (tile == 4 && (problem->puzzle[1][2] == 4))) {
        totalDistance += 2;
    }

    else if ((tile == 4 && (problem->puzzle[0][2] == 4)) || (tile == 4 && (problem->puzzle[2][2] == 4))) {
        totalDistance += 3;
    }

    //For tile 5 we calculate the distance given its position in the puzzle
    if ((tile == 5 && (problem->puzzle[0][1] == 5)) || (tile == 5 && (problem->puzzle[1][0] == 5)) || (tile == 5 && (problem->puzzle[1][2] == 5)) || (tile == 5 && (problem->puzzle[2][1] == 5))) {
        totalDistance += 1;
    }

    else if ((tile == 5 && (problem->puzzle[0][0] == 5)) || (tile == 5 && (problem->puzzle[0][2] == 5)) || (tile == 5 && (problem->puzzle[2][0] == 5)) || (tile == 5 && (problem->puzzle[2][2] == 5))) {
        totalDistance += 2;
    }

    //For tile 6 we calculate the distance given its position in the puzzle
    if ((tile == 6 && (problem->puzzle[0][2] == 6)) || (tile == 6 && (problem->puzzle[2][2] == 6)) || (tile == 6 && (problem->puzzle[1][1] == 6))) {
        totalDistance += 1;
    }

    else if ((tile == 6 && (problem->puzzle[0][1] == 6)) || (tile == 6 && (problem->puzzle[2][1] == 6)) || (tile == 6 && (problem->puzzle[1][0] == 6))) {
        totalDistance += 2;
    }

    else if ((tile == 6 && (problem->puzzle[0][0] == 6)) || (tile == 6 && (problem->puzzle[2][0] == 6))) {
        totalDistance += 3;
    }

    //For tile 7 we calculate the distance given its position in the puzzle
    if ((tile == 7 && (problem->puzzle[1][0] == 7)) || (tile == 7 && (problem->puzzle[2][1] == 7))) {
        totalDistance += 1;
    }

    else if ((tile == 7 && (problem->puzzle[0][0] == 7)) || (tile == 7 && (problem->puzzle[1][1] == 7)) || (tile == 7 && (problem->puzzle[2][2] == 7))) {
        totalDistance += 2;
    }

    else if ((tile == 7 && (problem->puzzle[1][2] == 7)) || (tile == 7 && (problem->puzzle[0][1] == 7))) {
        totalDistance += 3;
    }

    else if (tile == 7 && (problem->puzzle[0][2] == 7)) {
        totalDistance += 4;
    }

    //For tile 8 we calculate the distance given its position in the puzzle
    if ((tile == 8 && (problem->puzzle[2][0] == 8)) || (tile == 8 && (problem->puzzle[2][2] == 8)) || (tile == 8 && (problem->puzzle[1][1] == 8))) {
        totalDistance += 1;
    }

    else if ((tile == 8 && (problem->puzzle[1][0] == 8)) || (tile == 8 && (problem->puzzle[1][2] == 8)) || (tile == 8 && (problem->puzzle[0][1] == 8))) {
        totalDistance += 2;
    }

    else if ((tile == 8 && (problem->puzzle[0][0] == 8)) || (tile == 8 && (problem->puzzle[0][2] == 8))) {
        totalDistance += 3;
    }

    return totalDistance;
}

//Helper function that returns the totalDistance using calculateDistance
int manhattanDistance(Node* problem) {
    int distance = 0;

    if (problem->puzzle[0][0] != 1) {
        distance += calculateDistance(1, problem);
    }

    if (problem->puzzle[0][1] != 2) {
        distance += calculateDistance(2, problem);
    }

    if (problem->puzzle[0][2] != 3) {
        distance += calculateDistance(3, problem);
    }

    if (problem->puzzle[1][0] != 4) {
        distance += calculateDistance(4, problem);
    }

    if (problem->puzzle[1][1] != 5) {
        distance += calculateDistance(5, problem);
    }

    if (problem->puzzle[1][2] != 6) {
        distance += calculateDistance(6, problem);
    }

    if (problem->puzzle[2][0] != 7) {
        distance += calculateDistance(7, problem);
    }

    if (problem->puzzle[2][1] != 8) {
        distance += calculateDistance(8, problem);
    }

    return distance;
}

//Helper function that creates the children of the current state
vector<Node*> queueingFunction(Node* currentState, int algoChoice) {
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child3->heuristic = manhattanDistance(child3);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child3->heuristic = manhattanDistance(child3);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child3->heuristic = manhattanDistance(child3);
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
        if (algoChoice == 2) {
            child4->heuristic = misplacedTiles(child4);
            child4->totalCost = child4->cost + child4->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child4->heuristic = manhattanDistance(child4);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child3->heuristic = manhattanDistance(child3);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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
        if (algoChoice == 2) {
            child3->heuristic = misplacedTiles(child3);
            child3->totalCost = child3->cost + child3->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child3->heuristic = manhattanDistance(child3);
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
        if (algoChoice == 2) {
            child1->heuristic = misplacedTiles(child1);
            child1->totalCost = child1->cost + child1->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child1->heuristic = manhattanDistance(child1);
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
        if (algoChoice == 2) {
            child2->heuristic = misplacedTiles(child2);
            child2->totalCost = child2->cost + child2->heuristic;
        }

        //New heuristic addition for the children that calculates a child's manhattan distance and add it to total cost: f(n) = g(n) + h(n)
        else if (algoChoice == 3) {
            child2->heuristic = manhattanDistance(child2);
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

//Helper function to print out the traceback that is required
void traceback(Node* currentState) {
    cout << "The best state to expand with a g(n) = " << currentState->cost << " and h(n) = " << currentState->heuristic << " is ..." << endl;
    
    for (int i = 0; i < 3; ++i) {
        cout << "[";
        for (int j = 0; j < 3; ++j) {
            if (j != 2) {
                cout << currentState->puzzle[i][j] << ", ";
            }
            else {
                cout << currentState->puzzle[i][j];
            }
        }
        cout << "]" << endl;
    }
    cout << endl;
}

//General Search Algorithm
Node* generalSearch(Node* problem, int algoChoice) {
    //1.Create priority queue
    priority_queue<Node*, vector<Node*>, cheapestCost> nodes;

    //Have separate queue for UCS Algorithm using a vector as it is simpler
    vector<Node*> ucsQueue;

    //Create vector of visited nodes to prevent repeat states
    vector<Node*> visited;

    //Counts the nodes we expand and max queue size for stats
    int expandedNodes = 0;

    //Push root/initial state to priority queue with the the cost and heuristic cost if misplace tile algo is chosen or manhattan distance algo if not we instead push to ucsQueue
    if (algoChoice == 2) {
        problem->heuristic = misplacedTiles(problem);
        problem->totalCost = problem->cost + problem->heuristic;
        nodes.push(problem);
    }

    else if (algoChoice == 3) {
        problem->heuristic = manhattanDistance(problem);
        problem->totalCost = problem->cost + problem->heuristic;
        nodes.push(problem);
    }

    else {
        ucsQueue.push_back(problem);
    }

    //If algo is misplace tile or manhattan distance run this code
    if (algoChoice == 2 || algoChoice == 3) {
        //2. Enter while loop to see if we reach goal state and keep looping until nodes is empty
        while (!nodes.empty()) {
            //4. Pop the head node
            Node* currentNode = nodes.top();
            visited.push_back(currentNode);
            nodes.pop();
            expandedNodes++;

            //Call traceback for every node that is popped/looked at
            traceback(currentNode);

            //5. If current node is goal node return total cost and exit search
            if (isGoalState(currentNode)) {
                //Prints out all necessary stats to compare algorithms
                cout << "Goal State!" << endl;
                cout << endl;
                cout << "Solution depth was " << currentNode->cost << endl;
                cout << "Number of nodes expanded: " << expandedNodes << endl;
                cout << "Max queue size: " << nodes.size() << endl;
                return currentNode;
                break;
            }

            //6. Else enqueue all the children of current node with total cost from current node and add current node to visited list
            else {
                //Get vector of all of currentNode's children
                vector<Node*> children = queueingFunction(currentNode, algoChoice);

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

    //If algo is UCS run this code
    else {
        //2. Enter while loop to see if we reach goal state and keep looping until ucsQueue is empty
        while (!ucsQueue.empty()) {
            //4. Pop the front of the vector
            Node* currentNode = ucsQueue.front();
            visited.push_back(currentNode);
            ucsQueue.erase(ucsQueue.begin());
            expandedNodes++;

            //Call traceback for every node that is popped/looked at
            traceback(currentNode);

            //5. If current node is goal node return total cost and exit search
            if (isGoalState(currentNode)) {
                //Prints out all necessary stats to compare algorithms
                cout << "Goal State!" << endl;
                cout << endl;
                cout << "Solution depth was " << currentNode->cost << endl;
                cout << "Number of nodes expanded: " << expandedNodes << endl;
                cout << "Max queue size: " << ucsQueue.size() << endl;
                return currentNode;
                break;
            }

            //6. Else enqueue all the children of current node with total cost from current node and add current node to visited list
            else {
                //Get vector of all of currentNode's children
                vector<Node*> children = queueingFunction(currentNode, algoChoice);

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

                //Push back all new unvisited children to vector
                for (int i = 0; i < children.size(); ++i) {
                    ucsQueue.push_back(children.at(i));
                }
        }
    }

    //3.If priority queue is empty then return 'No solution'
    cout << "No solution found" << endl;
    return nullptr;
    }
}

int main() {
    //Puzzle user enters
    int userPuzzle[3][3];
    int algoChoice;

    //Prompt user to enter a puzzle
    cout << "Welcome to the 8 puzzle!!!" << endl;
    cout << "Please enter a puzzle of your choosing" << endl;
    cout << "Make sure to enter the eight numbers in any order and enter a '0' to denote the blank tile, also press enter after every number: " << endl;

    //Push into vector user puzzle
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int input;
            cin >> input;
            userPuzzle[i][j] = input;
        }
    }

    //Ask user which algorithm they want to run
    cout << endl;
    cout << "Enter 1 for Uniform Cost Search, 2 for Misplaced Tile Heuristic, or 3 for Manhattan Distance Heuristic: ";
    cin >> algoChoice;
    cout << endl;

    //Run the problem with the inputted algorithm
    Node* problem = new Node(userPuzzle);
    generalSearch(problem, algoChoice);

    return 0;
}