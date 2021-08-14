#include <bits/stdc++.h>
using namespace std;
const int STACKS = 10;
int score = 500;
vector<stack<int>> grid;
vector<stack<int>> temp_grid;
int cards[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
int frequency[13] ={0};
int rand_cards[10] = {5,5,5,5,4,4,4,4,4,4};
int real_cards[10] = {1,1,1,1,1,1,1,1,1,1};
void generate_Game()
{
    int idx;
    while(!grid.empty())
    {
        grid.pop_back();
    }
    srand(time(0));
    for(int i = 0 ; i < STACKS ; i++)
    {
        stack<int> temp;
        stack<int> temp1;
        if(i < 4)
        {
            for(int j = 0 ; j < 6 ; j++)
            {
                do{
                    idx = rand() % 13;
                }
                while(frequency[idx] == 8);
                temp.push(cards[idx]);
                frequency[idx]++;

            }
        }
        else
        {
            for(int j = 0 ; j < 5 ;j++)
            {
                do{
                    idx = rand() % 13;
                }
                while(frequency[idx] == 8);
                temp.push(cards[idx]);
                frequency[idx]++;
            }
        }
        grid.push_back(temp);
        temp_grid.push_back(temp1);
    }
    stack<int> help;
    for(int i = 0; i < 50; i++){
        do{
            idx = rand() % 13;
          }
        while(frequency[idx] == 8);
        help.push(cards[idx]);
        frequency[idx]++;
    }
    grid.push_back(help);
}

void fill_temp_grid()
{
    for(int i = 0 ; i < STACKS ; i++)
    {
        while(!grid[i].empty())
        {
            temp_grid[i].push(grid[i].top());
            grid[i].pop();
        }
    }
}
void print_grid()
{
    fill_temp_grid();
    cout<<"Your Score: "<<score<<endl;
    cout<<" -00-  -01-  -02-  -03-  -04-  -05-  -06-  -07-  -08-  -09- "<<endl;
    cout<<" ----  ----  ----  ----  ----  ----  ----  ----  ----  ---- "<<endl;
    while(true)
    {
        int ten_Null = 0;
        for(int i = 0 ; i <  STACKS ; i++)
        {
            if(!temp_grid[i].empty())
            {
                if(real_cards[i]-rand_cards[i]>0)
                {
                    if(temp_grid[i].top()>9)
                    {
                        cout<<" |"<<temp_grid[i].top()<<"| ";
                    }
                    else
                    {
                        cout<<" | "<<temp_grid[i].top()<<"| ";
                    }
                }
                else
                {
                    cout<<" | *| ";
                }
                grid[i].push(temp_grid[i].top());
                temp_grid[i].pop();
                real_cards[i]+=1;
            }
            else
            {
                cout<<"      ";
                ten_Null+=1;
            }
        }
        if(ten_Null>=10)
        {
            break;
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i = 0 ; i < STACKS ; i++){
        real_cards[i]=1;
    }
}
bool check_subOrder(int from, int to, int index)
{
    stack<int> From = grid[from];
    stack<int> To = grid[to];
    if(From.empty() || index >= From.size())
        return false;
    int counter = From.top() + 1;
    From.pop();
    int fromSize = From.size();
    for(int i = fromSize; i > index; i--)
    {
        //cout << "index: " << i << " Element: " << From.top() << endl;
        if(From.top() == counter)
        {
            counter++;
            From.pop();
        }
        else
            return false;
    }
    if(To.top() == counter || To.empty())
        return true;
    else
        return false;
}

void help(){
        if (grid[10].empty())
            return;
        else {
            for (int i=0 ; i < 10 ; i++)
            {
                grid[i].push(grid[10].top());
                grid[10].pop();
            }
        }
}

void take_input(int& from, int& to, int& index)
{
    cout << "Enter index of first stack" << endl;
    cin >> from;
    cout << "Enter index of second stack" << endl;
    cin >> to;
    cout << "Enter index of cards needed to move from stack " << from << " to stack " << to << endl;
    cin >> index;
    if(from == 11 && to == 0 && index == 0){
        help();
        print_grid();
        take_input(from,to,index);
    }
    else{
        if(from > STACKS - 1 || from < 0 || to > STACKS - 1 || to < 0)
        {
            cout << "Invalid indices" << endl;
            take_input(from, to, index);
        }
        if(rand_cards[from] > index)
        {
            cout << "can't move from inverted cards" << endl;
            take_input(from,to,index);
        }
        if(!check_subOrder(from, to, index))
        {
            cout << "can't move cards from this index" << endl;
            take_input(from, to, index);
        }
    }
}

void balance(int from_idx, int to_idx, int index)
{
    int from_size = grid[from_idx].size();
    int cardsNumber = from_size - index;
    if(from_size-cardsNumber == rand_cards[from_idx])
    {
        rand_cards[from_idx]-=1;
        real_cards[from_idx]=1;
    }
    else if(from_size-cardsNumber > rand_cards[from_idx])
    {
        real_cards[from_idx]=(from_size-cardsNumber)-rand_cards[from_idx];
    }
    real_cards[to_idx] += cardsNumber;
    cout<<cardsNumber<<endl;
    for(int i = 0 ; i < 10 ; i++){
        cout<<rand_cards[i]<<" ";
    }
    cout<<endl;
    for(int i = 0 ; i < 10 ; i++){
        cout<<real_cards[i]<<" ";
    }
    cout<<endl;
}

void move_play(int from_idx, int to_idx, int index)
{
    int from_size = grid[from_idx].size();
    int cardsNumber = from_size - index;
    stack<int> temp;
    for (int i=0 ; i < cardsNumber ; i++)
    {
        temp.push(grid[from_idx].top());
        grid[from_idx].pop();
    }
    for (int i=0 ; i<cardsNumber ; i++)
    {
        grid[to_idx].push(temp.top());
        temp.pop();
    }
    score --;
    balance(from_idx,to_idx,index);
}


bool check_order(int i){
    stack<int> temp;
    temp = grid[i];
    int cards = grid[i].size() - rand_cards[i];
    if(cards < 13)
        return false;
    for(int i = 0; i < 13 ; i++){
        if(temp.top() == i + 1){
            temp.pop();
        }
        else{
            return false;
        }
    }
    return true;
}

void delete_win(int idx){
    for(int i = 0; i < 13; i++){
        grid[idx].pop();
    }
}



void play(){
    generate_Game();
    print_grid();
    int from,to,index;
    while(score != 0){
        take_input(from,to,index);
        move_play(from,to,index);
        print_grid();
        cout<<check_order(to)<<endl;
        if(check_order(to)){
            delete_win(to);
            print_grid();
        }
    }
}

int main()
{
    play();
}

