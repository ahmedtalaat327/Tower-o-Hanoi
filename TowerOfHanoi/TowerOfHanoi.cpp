// C++ Source Example of Data Structure in Modern Programming.
//By @ahmedtalaat327 on github.

#include <iostream>
#include <string>
#include <math.h>
#include <vector>


//put some abbreviations for us
//any dims or length could be represented by doubles numbers
//color could be sring or custom class by your own immagination also search about merging (r,g,b)
//sizes, counters or indeces could be represented only in unsigned int numbers
typedef double Edge, Area, Volume;
typedef std::string Color;
typedef unsigned int Number;

//cube structure class
class Cube {
public:
    //defult constructor 
    Cube() {
        _edge = 10;
        _color = "White";
    }
    //assigned with params 
    Cube(Edge lenghtofEdge, Color surfacePaint) {
        _edge = lenghtofEdge;
        _color = surfacePaint;
    }
    //capture current cube egde as double
    const Edge getCubeEdge() {
        return _edge;
    }
    //set cube edge with new value
    void setCubeEdge(Edge newEdge) {
        _edge = newEdge;
    }
    //get current volume
    const Volume getCubeVolume() {
        return pow(getCubeEdge(), 3);
    }
    //get current area of one face
    const Area getCubeSurfaceArea() {
        return pow(getCubeEdge(), 2);
    }
    //get cuurent surface color of whole cube all the same color BTW!
    const Color getCubePaint() {
        return _color;
    }

private:
    Edge _edge;
    Color _color;
};
//stack in structure class
class Stacki {
public:
    //pushing any new cube to one stack
    void pushBack(const Cube& cube) {
        _cubes.push_back(cube);
    }
    //remove last cube but copy it to collect it again
    Cube removeTop() {
        Cube last_cube = _cubes[size() - 1];
        _cubes.pop_back();
        return last_cube;
    }
    //just quick peek to the address of last one
    //we choose to return the address because this stack is dynamic
    // address of last cube of the sack
    Cube& peekTop() {
        return _cubes[size() - 1];;
    }
    //get the whole size at that moment of calling
    const Number size() {
        return _cubes.size();
    }
    //cout the object with all details
    friend std::ostream& operator<<(std::ostream& os, const Stacki& stack) {
        for (int x = 0; x < stack._cubes.size(); x++) {
            Cube xcube = stack._cubes[x];
            auto xvolume = xcube.getCubeVolume();
            auto xcolor = xcube.getCubePaint();
            os << "[Volume " << xvolume << " Color " << xcolor << "] / ";
        }
       return os;
    }
private:
    std::vector<Cube> _cubes;
};
//whole game controller class
class Game {

public: 
    Game() {
        //initialize, three stack as game/puzzle want
        for (int i = 0; i < 3; i++) {
            Stacki stackx;
            _stacks.push_back(stackx);
        }

        //put our prefered cubes in first stack [0]th one 
        //in FILO order biggest volume enter stack first
        Cube cube_0(4,"Red");
        _stacks[0].pushBack(cube_0);
        Cube cube_1(3, "Paige");
        _stacks[0].pushBack(cube_1);
        Cube cube_2(2, "Black");
        _stacks[0].pushBack(cube_2);
        Cube cube_3(1, "Green");
        _stacks[0].pushBack(cube_3);

    }
    void solve() {
        
        //loop until third stack is full
        while (_stacks[2].size() != 4) {
            //we follow the pattern
            //search for this puzzle pattern to understand more!
            _swap(0, 1);
            _swap(0, 2);
            _swap(1, 2);
        }
    }
   
    //cout the object with all details
    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        for (int x = 0; x < game._stacks.size(); x++) {
            auto xstack = game._stacks[x];
            os << "Stack [" << x << "]-> " << xstack << std::endl;
        }
        return os;
    }
private:
    //this func responsible for making swap depend on the volume of each cube
    //also called legal movement as puzzle wants
    void _swap(Number index_left_stack,Number index_right_stack) {

        //if left stack is empty
        if (_stacks[index_left_stack].size() == 0 && _stacks[index_right_stack].size() > 0) {
            _removeThenAdd(index_left_stack, index_right_stack);
        }

        //if right stack is empty
        else if (_stacks[index_left_stack].size() > 0 && _stacks[index_right_stack].size() == 0) {
            _removeThenAdd(index_right_stack, index_left_stack);
        }
        else if (_stacks[index_left_stack].size() > 0 && _stacks[index_right_stack].size() > 0) {
            //if both stacks not empty
            //check wich cube from last indexof both stacks left & right
            if (_stacks[index_left_stack].peekTop().getCubeVolume() <
                _stacks[index_right_stack].peekTop().getCubeVolume()) {
                _removeThenAdd(index_right_stack, index_left_stack);
            }
            else {
                _removeThenAdd(index_left_stack, index_right_stack);
            }
        }
        //show movements
        std::cout << *this << std::endl;

    }
    //mechanism of taking one cube from stack and adding it to another stack
    //smallest cube will be [ index from ]
    void _removeThenAdd(Number to, Number from) {
        Cube c = _stacks[from].removeTop();
        _stacks[to].pushBack(c);
    }
    std::vector<Stacki> _stacks;

};
int main() {
    Game ToH;
    std::cout << "Intialize My Stacks" << std::endl;
    std::cout << ToH << std::endl;

    ToH.solve();

    std::cout << "My Stacks After Solution Func" << std::endl;
    std::cout << ToH << std::endl;

    return 0;
}