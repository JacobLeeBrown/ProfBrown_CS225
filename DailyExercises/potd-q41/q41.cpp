#include <iostream>
using namespace std;


int checkInput(int x, int y, int *arr, int SIZE)
{
		if(x < 0 || x >= SIZE)
		{
			return 1;
		}
		else if(y < 0 || y >= SIZE)
		{
			return 2;
		}
		else if(arr[y*SIZE + x] != 0)
		{
			return 3;
		}
		else
		{
			return 0;
		}
}

void getInput(int playerid, int *arr, int SIZE){
    cout << "Please enter the x and y coordinates of where you would like to place (0-indexed):" << endl;
    int x_coord, y_coord;
    cin >> x_coord;
    cin >> y_coord;
    while(checkInput(x_coord, y_coord, arr, SIZE) != 0)
    {
    	switch(checkInput(x_coord, y_coord, arr, SIZE))
    	{
    		case(1):
    			cout << "Your x coordinate is invalid, please enter a new x coord:" << endl;
    			cin >> x_coord;
    			break;
			case(2):
    			cout << "Your y coordinate is invalid, please enter a new y coord:" << endl;
    			cin >> y_coord;
    			break;
			case(3):
    			cout << "That spot is already taken, please enter new coordinates:" << endl;
    			cin >> x_coord;
    			cin >> y_coord;
    			break;
			default:
				cout << "ERROR" << endl;
    	}
    }
    arr[y_coord * SIZE + x_coord] = playerid;
}

int main(){
    int size;
    int *arr;
    cout << "WElCOME TO TIC-TAC-TOE 5000\nHow large would you like the nxn board to be? n=";
    cin >> size;
    arr = new int[size*size];
    // initialize board
    for(int i = 0; i < size*size; i++){
        arr[i] = 0;
    }
    cout << "LET'S BEGIN!" << endl;
    int turn = 0;
    int player = 1;
    //int winner;
    while(turn < size*size){
    //    You'll do this one tomorrow!
    //    printBoard(arr, size); 
        cout << "PLAYER " << player << " it's your move.";
        getInput(player, arr, size);
        // You'll do this in two days!
    //    if(winner = check(arr, size)){
    //        printBoard(arr, size);
    //        cout << "PLAYER " << winner << " WINS!" << endl;
    //        delete [] arr;
    //        return 0;
    //    }
        player = (player == 1) ? 2 : 1;
        turn++;
    }
    // printBoard(arr, size);
    cout << "Cat's game." << endl;
    delete [] arr;
    return 0;
}
