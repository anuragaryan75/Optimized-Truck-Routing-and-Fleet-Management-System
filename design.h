#include <windows.h>

vector <string> logo = {
"   _____                      _   _             _             _             ",
"  / ____|                    | \\ | |           (_)           | |           " ,
" | |     __ _ _ __ __ _  ___ |  \\| | __ ___   ___  __ _  __ _| |_ ___  _ __ ",
" | |    / _` | '__/ _` |/ _ \\| . ` |/ _` \\ \\ / / |/ _` |/ _` | __/ _ \\| '__|",
" | |___| (_| | | | (_| | (_) | |\\  | (_| |\\ V /| | (_| | (_| | || (_) | |   ",
"  \\_____\\__,_|_|  \\__, |\\___/|_| \\_|\\__,_| \\_/ |_|\\__, |\\__,_|\\__\\___/|_|   ",
"                   __/ |                           __/ |                    ",
"                  |___/                           |___/                     ",
"-----------------------------------------------------------------------------\n\t\tJaypee Institute of Information Technology"
};

class MenuItem{
    public:
    
    vector <string> menuSelect;
    int selected;
    char lastPressed;

    void lgDip(){
        for(auto it : logo){
            cout << it << "\n";
        }
        cout << "\n\n\n\n";
    }

    MenuItem(vector<string> options) {
        for (auto &it : options) {
            this->menuSelect.push_back(it);
        }
        this -> selected = 0;
        lastPressed = 'h';
    }

    void moveUp() {
        this -> selected--;
        if (this -> selected < 0) {
            this -> selected += this->menuSelect.size();
        }
    }

    void moveDown() {
        this->selected++;
        this->selected %= this -> menuSelect.size();
    }

    void move(char ch) {
        lastPressed = ch;
        if (tolower(ch) == 'w') {

            moveUp();
        }
        else if (tolower(ch) == 's') {
            moveDown();
        }
    }

    void display() {
        system("cls");
        lgDip();

        for (int i = 0; i < menuSelect.size(); ++i) {
            cout << "\t\t\t" << (selected == i ? ">>  " : "    ") << menuSelect[i] << "\n";
        }
        cout << "\n";
    }
};