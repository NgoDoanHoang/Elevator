#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void elev_up(int floor);
void elev_down(int floor);
void elev_move(int floor);

enum Direction
{
    up = 1,
    down = 0
};

struct elev
{
    int current_floor;
    Direction direction;
};

struct user
{
    int current_floor;
    int desired_floor;
};

int main() 
{   
    elev elevator1;
    cout << "Input: current_floor / currentDirection: ";
    cin >> elevator1.current_floor;
    int directionValue;
    cin >> directionValue;
    elevator1.direction = static_cast<Direction>(directionValue);
    
   // vector<user> users;
    vector<int> request;
    vector<int> user_current_floor;
    vector<int> pick_up_floor_in_oppo_direction;
    
    int num = 0;
    int temp = 0;
    cout << "number of pp: ";
    cin >> num;
    
    for (int i = 0; i < num; i++)
    {
        user newUser;
        cout << "User " << i << ": floorOfUser / desired_floor: ";
        cin >> newUser.current_floor;
        cin >> newUser.desired_floor;

        user_current_floor.push_back(newUser.current_floor);
    };
    
    /*****this is to find out which floor to pick up*****/
    if (elevator1.direction == Direction::up)
    {
        sort(user_current_floor.begin(), user_current_floor.end());
       // cout << endl << "sort asc user_current_floor did run1" << endl;
    }
    else
    {
        sort(user_current_floor.begin(), user_current_floor.end(), greater<>());
       // cout << "sort des user_current_floor did run 2" << endl;
    }

    //check remaining floor in what direction
    bool remaining_floor_below = true;
    //go to floor that has request
    for (auto x: user_current_floor)
    {   
        if(elevator1.direction == Direction::up && x >= elevator1.current_floor)
        {
            elev_up(x);
        }
        else if(elevator1.direction == Direction::up && x < elevator1.current_floor)
        {   
            //add to a vector for back-turn
            pick_up_floor_in_oppo_direction.push_back(x);
        }
        else if (elevator1.direction == Direction::down && x <= elevator1.current_floor)
        {
            elev_down(x);
        }
        else
        {
            pick_up_floor_in_oppo_direction.push_back(x);
            remaining_floor_below = false;
        }
    }
    
    //sort remaining pick up floor
    if (remaining_floor_below)
    {
        sort(pick_up_floor_in_oppo_direction.begin(), pick_up_floor_in_oppo_direction.end(), greater<>());      
        //cout << "did this work? poc" << endl;
    } 
    else
    {
        sort(pick_up_floor_in_oppo_direction.begin(), pick_up_floor_in_oppo_direction.end());
        //cout << "what about this?" << endl;
    }
    //pick up the rest
    for(auto x: pick_up_floor_in_oppo_direction)
    {
        if (remaining_floor_below)
        {
            elev_down(x);
            //cout << "run here?" << endl;
        }
        else
        {
            elev_up(x);
            //cout << "run here2??" << endl;
        }
    }
    
    /*********  **********/
    
    return 0;
}



void elev_move(int floor)
{
    cout << "To destination floor: " << floor << endl;
}

void elev_up(int floor)
{
    cout << "Going up to pick up at floor: " << floor << endl;
}

void elev_down(int floor)
{
    cout << "Going down to pick up at floor: " << floor << endl;
}


//request[i] > 0 && elevator1.direction == Direction::up