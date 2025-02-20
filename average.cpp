#include <iostream>

using namespace std;

int main(int n, char *s[]){

    double sum = 0.0;
    double avg;

    if(n == 1){
        cout << "Please input numbers to find average.";
    }
    else{
        cout << "---------------------------------" << endl;
        for(int i = 0; i < n; i++){
            sum += atof(s[i]);
        }

        avg = sum / (n - 1);
        cout << "Average of "<< n-1 << " numbers = " << avg << endl;
        cout << "---------------------------------" << endl;
    }
    return 0;
}
