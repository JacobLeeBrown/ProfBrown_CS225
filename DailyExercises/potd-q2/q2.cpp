/* Problem of the Day -- Question 2 -- Students Code */
#include <ctime>
#include <iostream>

using namespace std;
 
int main()
{
    time_t seconds = time(nullptr);
	asctime(localtime(&seconds));
	time_t hours = seconds / 3600;
	time_t years = hours / (24*365);

    cout << "Seconds: " << seconds << "\n"
	<< "Hours: " << hours << "\n"
	<< "Years: " << years << "\n";
	
	return 0;
}
