//============================================================================
// Name         : lab6_Queue.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 7-10-2021
// Date Modified: 2-03-2022
// Copyright    : All rights are reserved
// Description  : Queue implementation using internal Array
//============================================================================
#include<iostream>
#include<iomanip> //for setw() manipulator
#include<exception>
#include <unistd.h>
#include<sstream>
#include<string>
#include<time.h>
#ifdef _WIN32
    #define clear_screen "clrscr"
#else
    #define clear_screen "clear"
#endif
#define SIZE 5
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3
#define MAX_CARS 500
int current_signal;
int SPEED=1; //1=slowest
using namespace std;

string colors[]={ "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m", "\033[38m"};

//===================================================
class QueueEmpty: public exception
{
    public:
        virtual const char* what() const throw()
        {
            return "Queue is Empty";
        }
};
//=================================================
class QueueFull: public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Queue is Full";
    }
};
//=================================================

template <typename T>
class Queue
{
    private:
        T *array;
        int N;    //Array Size (Capacity)
        int r;    //index where a new element will be added
    public:
        Queue(int N);
        ~Queue();
        void enqueue(T);
        T dequeue();
        bool isEmpty();
        bool isFull();
        friend void display();
};
//===========================================
class Car
{
    private:
        time_t arrival_time;
        string color;
    public:
        Car()
        {
            this->arrival_time = time(NULL);
            this-> color = colors[random()%6];
        }
        time_t get_arrival_time()
        {
            return arrival_time;
        }
        string getColor()
        {
            return color;
        }
};
//===========================================
void display();
//===========================================
Queue<Car> left_queue(SIZE);
Queue<Car> right_queue(SIZE);
Queue<Car> top_queue(SIZE);
Queue<Car> bottom_queue(SIZE);
//==========================================
int main()
{
    srand(time(NULL));
    int cars=0;
    time_t signal_timer = time(NULL);
    time_t dequetime = time(NULL);
    int waiting_time=0;
    current_signal = rand()%4;
    while(cars<MAX_CARS)
    {
        //complete the main function
        //.......................
        //signal_timer = time(NULL);
        Car tempObj;
        switch (current_signal) {
            case LEFT:
                if (!left_queue.isEmpty()) {
                    tempObj = left_queue.dequeue();
                    waiting_time = difftime(dequetime, tempObj.get_arrival_time());
                    dequetime = time(NULL);
                }
                if (!right_queue.isFull()) {
                    Car* carObj1 = new Car;
                    right_queue.enqueue(*carObj1);
                    cars++;
                }
                if (!top_queue.isFull()) {
                    Car* carObj2 = new Car;
                    top_queue.enqueue(*carObj2);
                    cars++;
                }
                if (!bottom_queue.isFull()) {
                    Car* carObj3 = new Car;
                    bottom_queue.enqueue(*carObj3);
                    cars++;
                }
                break;
                
            case RIGHT:
                if (!right_queue.isEmpty()) {
                    tempObj = right_queue.dequeue();
                    waiting_time = difftime(dequetime, tempObj.get_arrival_time());
                    dequetime = time(NULL);
                }
                if (!left_queue.isFull()) {
                    Car* carObj1 = new Car;
                    left_queue.enqueue(*carObj1);
                    cars++;
                }
                if (!top_queue.isFull()) {
                    Car* carObj2 = new Car;
                    top_queue.enqueue(*carObj2);
                    cars++;
                }
                if (!bottom_queue.isFull()) {
                    Car* carObj3 = new Car;
                    bottom_queue.enqueue(*carObj3);
                    cars++;
                }
                break;

            case TOP:
                if (!top_queue.isEmpty()) {
                    tempObj = top_queue.dequeue();
                    waiting_time = difftime(dequetime, tempObj.get_arrival_time());
                    dequetime = time(NULL);
                }
                if (!right_queue.isFull()) {
                    Car* carObj1 = new Car;
                    right_queue.enqueue(*carObj1);
                    cars++;
                }
                if (!left_queue.isFull()) {
                    Car* carObj2 = new Car;
                    left_queue.enqueue(*carObj2);
                    cars++;
                }
                if (!bottom_queue.isFull()) {
                    Car* carObj3 = new Car;
                    bottom_queue.enqueue(*carObj3);
                    cars++;
                }
                break;
                
            case BOTTOM:
                if (!bottom_queue.isEmpty()) {
                    tempObj = bottom_queue.dequeue();
                    waiting_time = difftime(dequetime, tempObj.get_arrival_time());
                    dequetime = time(NULL);
                }
                if (!right_queue.isFull()) {
                    Car* carObj1 = new Car;
                    right_queue.enqueue(*carObj1);
                    cars++;
                }
                if (!left_queue.isFull()) {
                    Car* carObj2 = new Car;
                    left_queue.enqueue(*carObj2);
                    cars++;
                }
                if (!top_queue.isFull()) {
                    Car* carObj3 = new Car;
                    top_queue.enqueue(*carObj3);
                    cars++;
                }
                break;
                
            default:
                break;
        }
        
        if (time(NULL)>signal_timer+2) {
            current_signal = rand()%4;
            signal_timer = time(NULL);
            continue;
        }
        system(clear_screen);
        display();
        cout<<"Total cars passed through the junction:"<<cars<<endl;
        cout<<"Avg. waiting time for a car: "<<setprecision(3)<<(float(waiting_time)/cars)*SPEED<<" seconds"<<endl;
        usleep(200000/SPEED);
    }
    return EXIT_SUCCESS;
}
//===================================================
void display()
{
    string spaces;
    for(int j=0; j<=SIZE; j++)
        spaces+="     ";
    cout<<spaces<<"╔════╗"<<endl;
    for(int i=SIZE-1; i>=0; i--)
    {
          cout<<spaces<<"║";
          if(i<top_queue.r)
                  cout<<top_queue.array[i].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m";
                  //cout<<setw(4)<<" ▒▒ ";
          else
              cout<<"    ";
          cout<<"║"<<endl;
          cout<<spaces<<"╠════╣"<<endl;;
    }

    cout<<spaces<<"║";
    if(current_signal==TOP)
        cout<<"\033[1;32m"<<" ■■ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<" ■■ "<<"\033[0m";
    cout<<"║"<<endl;

    cout<<"╔════";
    for(int i=0; i<SIZE; i++)
        cout<<"╦════";
    cout<<"╝    ╚";
    for(int i=0; i<SIZE; i++)
        cout<<"════╦";

    cout<<"════╗"<<endl;


    for(int i=SIZE-1; i>=0; i--)
    {
        cout<<"║";
        if(i<left_queue.r)
                  cout<<left_queue.array[i].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m";
        else
            cout<<"    ";
    }
    cout<<"║";

    if(current_signal==LEFT)
        cout<<"\033[1;32m"<<" █ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<" █ "<<"\033[0m";
    cout<<"      ";

    if(current_signal==RIGHT)
        cout<<"\033[1;32m"<<"   █ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<"   █ "<<"\033[0m";
    //cout<<"      ";

    for(int i=0; i<SIZE; i++)
    {
        cout<<"║";
        if(i<right_queue.r)
                  cout<<right_queue.array[i].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m";
        else
            cout<<"    ";
    }
    cout<<"║"<<endl;

    cout<<"╚════";
    for(int i=0; i<SIZE; i++)
        cout<<"╩════";
    cout<<"╗    ╔";
    for(int i=0; i<SIZE; i++)
        cout<<"════╩";
    cout<<"════╝"<<endl;

     cout<<spaces<<"║";

     if(current_signal==BOTTOM)
        cout<<"\033[1;32m"<<" ▄▄ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<" ▄▄ "<<"\033[0m";
    cout<<"║"<<endl;

    for(int i=0; i<SIZE; i++)
    {
          cout<<spaces<<"╠════╣"<<endl;
          cout<<spaces;
                  cout<<"║";
        if(i<bottom_queue.r)
                  cout<<bottom_queue.array[i].getColor()<<setw(4)<<" ▒▒ "<<"\033[0m"<<"║"<<endl;
        else
            cout<<"    ║"<<endl;
    }
    cout<<spaces<<"╚════╝"<<endl;
    cout<<endl;
}
//===============================================
//complete the missing functions/methods

template <typename T>
Queue<T>::Queue(int N) {
    array = new T[N];
    this->r = 0;
    this->N = N;
}

template <typename T>
Queue<T>::~Queue() {
    delete [] array;
}

template <typename T>
void Queue<T>::enqueue(T carObj) {
    if (isFull()) throw QueueFull();
    array[r] = carObj;
    r++;
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) throw QueueEmpty();
    T carObj = array[0];
    for (int i=0; i<r-1; i++) {
        array[i] = array[i+1];
    }
    r--;
    return carObj;
}

template <typename T>
bool Queue<T>::isEmpty() {
    return (r == 0);
}

template <typename T>
bool Queue<T>::isFull() {
    return (r == N);
}
