#include <iostream>
using namespace std;

void load_all_data();
void reset_visited();
bool find_path(int current, int destination);

class Cave {
private:
    int num_doors; // number of doors out of the cave
    int door[25];  // hold index number of cave behind the door
    bool visited;  // mark a cave when you visit it
public:
    void load_data(int n, int a, int b, int c, int d, int e);
    int get_num_doors() { return num_doors; }
    int get_door(int i) { return door[i]; }
    void set_visited(bool b) { visited = b; }
    bool get_mark() { return visited; }
};

int num_total_caves; // total number of caves
Cave cave[500];      // assume a maximum of 500 caves

int main() {
    load_all_data();
    reset_visited();
    
    int start, destination;
    cout << "Enter the number of the start cave: ";
    cin >> start;
    cout << "Enter the number of the destination cave: ";
    cin >> destination;
    cout << endl;
    
    bool path_exists = find_path(start, destination);
    cout << destination << endl; // DEBUG cout
    if (path_exists) {
        cout << "A path was found from " << start;
        cout << " to " << destination << "\n\n";
    } else {
        cout << "There is no path from " << start;
        cout << " to " << destination << "\n\n";
    }
}

bool find_path(int current, int destination) {
    if (current == destination) {

        return true;
    }
    
    bool visited = cave[current].get_mark();
    if (visited) {

        std::cout << "visited" << std::endl;
        return false; // do not visit a visited cave
    }
    
    cave[current].set_visited(true); // mark as visited
    std::cout << current << " -> ";     // DEBUG cout
    
    int num = cave[current].get_num_doors();
    for (int i = 0; i < num; i++) {
        int cave_num = cave[current].get_door(i);
        if (find_path(cave_num, destination)) {
            
            return true;
        }
    }

    std::cout << "backtrack" << std::endl;
    return false;
}
void load_all_data() {
    // load the data for all caves - change as needed
    // this data is for the example in the notes
    // -1 is used to indicate no door
    cave[0].load_data(3, 4, 3, 2, -1, -1);
    cave[1].load_data(0, -1, -1, -1, -1, -1);
    cave[2].load_data(1, 1, -1, -1, -1, -1);
    cave[3].load_data(2, 0, 2, -1, -1, -1);
    cave[4].load_data(1, 3, -1, -1, -1, -1);
    num_total_caves = 5;
}

void reset_visited() {
    // set all caves to be not visited
    for (int i = 0; i < num_total_caves; i++) {
        cave[i].set_visited(false);
    }
}

//--------------- methods for the Cave ------------
void Cave::load_data(int n, int a, int b, int c, int d, int e) {
    // WARNING - does not work for more than 5 doors
    num_doors = n;
    door[0] = a;
    door[1] = b;
    door[2] = c;
    door[3] = d;
    door[4] = e;
}