#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool keep_playing = true;

char guessUserNumber(const int t_middle_point){
    cout << "Is the number smaller bigger or equal of : "
         << t_middle_point << " ? [-, +, =]" << "\n";
    cout << endl;

    char user_input = 'c';
    cin >> user_input;

    return user_input;
}

void processUserInput(char t_user_input,
                      const int &t_middle_point,
                      int &t_min,
                      int &t_max)
{
    vector<char> available_choices{
        '+', '-', '='
    };
    // find user input in the available choices
    auto pos = find(available_choices.begin(),
            available_choices.end(),
            t_user_input);
    // if its end it is not in the vector
    if(pos == available_choices.end()){
        cout << "Wrong input" << endl;

        t_user_input = guessUserNumber(t_middle_point);

        //Recall the same function(recursive)
        // processUserInput(t_user_input,
        //                 t_middle_point,
        //                 t_min,
        //                 t_max);
    }

    if(t_user_input == '+'){
        t_min = t_middle_point;
    }

    if(t_user_input == '-'){
        t_max = t_middle_point;
    }

    if(t_user_input == '='){
        cout << "\n" << "I won!" << endl;
        keep_playing = false;
    }
}

int main(){
    int min = 1;
    int max = 100;

    while(keep_playing){
        int middle_point = (max + min) / 2;

        auto user_input = guessUserNumber(middle_point);

        cout << "min : " << min << "\n" << "max : " << max << "\n";

        processUserInput(user_input,
                        middle_point,
                        min,
                        max);
        cout << endl;
    }
    return 0;

}