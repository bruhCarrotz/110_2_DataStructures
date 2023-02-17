#include "function.h"
#include <iostream>
using namespace std;

//stack
template <class T>
BaseStack<T>::BaseStack(){
	_capacity = 100;
    _stack = new T[_capacity];
    _top = 0;
}

template <class T>
BaseStack<T>::~BaseStack(){
    delete[] _stack;
}

template <class T>
bool BaseStack<T>::empty(){
    return (size()==0);
}

template <class T>
int BaseStack<T>::size(){
    return _top;
}

template <class T>
T& BaseStack<T>::top(){
    return _stack[_top];
}

template <class T>
void BaseStack<T>::push(const T& item){
    if(size() == _capacity){
        int newsize = _capacity * 1.6;
        T* new_stack = new T[newsize];
        for(int i=0 ; i<size() ; i++){
            new_stack[i] = _stack[i];
        }
        _capacity = newsize;
        delete [] _stack;
        _stack = new_stack;
    }     
    _stack[++_top] = item;
}

template <class T>
void BaseStack<T>::pop(){
    if(_top == 0) return;
    _stack[_top].~T();
    _top--;
}

//queue
template <class T>
BaseQueue<T>::BaseQueue(){
    _queue = new T[100000];
    _front = -1;
    _rear = -1;
    _capacity = 0;
}

template <class T>
BaseQueue<T>::~BaseQueue(){
    delete[] _queue;
}

template <class T>
bool BaseQueue<T>::empty(){
    return (size() == 0);
}

template <class T>
int BaseQueue<T>::size(){
    return _capacity;
}

template <class T>
T& BaseQueue<T>::front(){
    return _queue[_front+1];
}

template <class T>
void BaseQueue<T>::push(const T& item){
    _rear++;
    _queue[_rear] = item;
    _capacity++;
}

template <class T>
void BaseQueue<T>::pop(){
    if(!empty()){
        _queue[_front+1] = 0;
        _front += 1;
        _capacity--;
    }
}

void* memory;
int global_width;

BaseStack<char> *arr;
BaseQueue<char> bullet;

int largest(int a, int b){
    int maximum = 0;
    int current_stack;
    for(int i=a ; i<=b ; i++){
        while(arr[i].top() == '_'){
            arr[i].pop();
        }
        current_stack = arr[i].size();
        if(current_stack > maximum) 
            maximum = current_stack;
    }
    return maximum;
}

void check_top(int W){
    for (int i = 0 ; i<W ; i++){
        cout << arr[i].top() << ' ';
    }
    cout << bullet.front() << endl;
}

void InitialzeStage(int W, int H){
    global_width = W;
    char num;
    // memory = operator new[] (sizeof(BaseStack<char>) * (W+1) );
    // arr = static_cast<BaseStack<char>*>(memory);

    // for(int i=0 ; i<W ; i++){
    //     new(&arr[i]) BaseStack<char>(W);
    // }
    arr = new BaseStack<char>[W];

    for(int i=0 ; i<H ; i++){
        for(int j=0 ; j<W ; j++){
            cin >> num;
            arr[j].push(num);
        }
    }
}

void enemy_five(int col, int W){
    int left = col-2;
    int right = col +2;
    if(left < 0 )
        left = 0;
    if(right >= W)
        right = W-1;

    while(arr[col].top()=='_'){
            arr[col].pop();
            if(arr[col].empty()) break;
        }

    int max =  largest(left,right);

    for(int i=left ; i<=right ; i++){
        while(arr[i].size() < max){
            arr[i].push('_');
        }
        for(int j=0 ; j<3 ; j++){
            arr[i].push('1');
        }
    }
}

void shots(char enemy, int W, int col){
    switch (enemy){
    case '1':
        return;
        break;
    case '2':
        bullet.push('2');
        break;
    case '3':
        bullet.push('3');
        break;
    case '4':
        bullet.push('4');
        break;
    case '5':
        enemy_five(col,W);
        break;
    default:
        break;
    }
}

void ShootNormal(int col, int W){
    if(col < 0 || col >= W) return;

    char enemy = arr[col].top();
    while(enemy == '_'){
        arr[col].pop();
        enemy = arr[col].top();
        if(arr[col].empty())
            break;
    }
    if(arr[col].empty()) return;
    arr[col].pop();
    shots(enemy, W, col);
}

void ShootSpecial(int col, int W){
    if(col < 0 || col >= W) return;
    if(bullet.empty())
        return;
    char bul = bullet.front();
    

    bullet.pop();
    int left = col-2;
    int right = col +2;
    char target;

    switch (bul){
    case '2':
        if(left < 0 )
            left = 0;
        if(right >= W)
            right = W-1;
        for(int i=left ; i<=right ; i++){
            ShootNormal(i,W);
        }
        break;
    case '3':
        for(int i=0 ; i<3 ; i++){
            ShootNormal(col,W);
        }
        break;
    case '4':
        while(arr[col].top()=='_'){
            arr[col].pop();
            if(arr[col].empty()) break;
        }
        if(arr[col].empty()) break;

        target = arr[col].top();
        while(target == arr[col].top()){
            ShootNormal(col, W);
            while(arr[col].top()=='_')
            {
                arr[col].pop();
                if(arr[col].empty()) break;
            }
            if(arr[col].empty()) break;
        }

        break;    
    default:
        break;
    }
}

void FrontRow(int W){
    int maxval = largest(0,W-1);
    cout << "FRONT_ROW, LEVEL:" << maxval << endl;
    if(maxval){
        for (int i=0 ; i<W ; i++){
            if(largest(0,W-1) != arr[i].size()){
                arr[i].push('_');
            }
            if (i != W-1){
                cout << arr[i].top() << ' ';
            }
            else{
                cout << arr[i].top();
            }
        }
        cout << endl;
    }
}

string* str;

void printing(int level, int index){
    str[index].reserve(level+1000);
    for(int i=level ; i>=0 ; i--){
        if(arr[index].size() != i){
            str[index].push_back('_');
            continue;
        }
        str[index].push_back(arr[index].top());
        arr[index].pop();
    }
    arr[index].~BaseStack<char>(); //destroy
}

void ShowResult(int W){
    bullet.~BaseQueue();
    cout << "END_RESULT:" << endl;

    str = new string[W+1000];
    int level = largest(0,W-1);

    for(int i=0 ; i<W ; i++) {
        printing(level,i);
    }

    for(int i=level-1 ; i>=0 ; i--){
        for(int j=0 ; j<W ; j++){
            if (j != W-1){
                cout << str[j][i] << ' ';
            }
            else{
                cout << str[j][i];
            }
        }
        cout << endl;
    }
}

void deleteStage(){
    operator delete[](memory);
}