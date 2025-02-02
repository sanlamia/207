#include<stdio.h>
#include<iostream>
#include<string>
#define left(n)(2*n)
#define right(n)(2*n)+1
using namespace std;

struct passenger
{
    string name;
    int milage;
    int years;
    int sequence;

    passenger()
    {
        name="";
        milage=0;
        years=0;
        sequence=0;
    }

    int calculatePriority()
    {
        int PriorityNumber = (((milage/1000)+years)-sequence);
        return PriorityNumber;
    }

    void printDetails()
    {
        cout<<"Passenger Details"<<endl;
        cout<<"Name: "<<name<<" Mileage:"<<milage<<" Years:"<<years<<" Sequence:"<<sequence<<endl;
        cout<<"Priority:"<<calculatePriority()<<endl;
    }

};

bool compare(passenger &a, passenger &b)
{
    return a.calculatePriority()<b.calculatePriority();
}

template<typename T,bool(*comparetor)(T &a, T &b)>

struct Heap
{
    T arr[10000];
    int idx;

    Heap()
    {
        idx=0;
    }

    bool isEmpty()
    {
        return idx==0;
    }

    void Insert(T val)
    {
        idx++;
        arr[idx]=val;
        int temp=idx;
        while(temp>1 && comparetor(arr[temp],arr[temp/2]))
        {
            Swap(arr[temp],arr[temp/2]);
            temp=temp/2;

        }

    }

    void heapify(int node)
    {
        int changed=node;
        if(left(node)<=idx && comparetor(arr[left(node)],arr[changed]))
        {
            changed=left(node);
        }
        if(right(node)<=idx && comparetor(arr[right(node)],arr[changed]))
        {
            changed=right(node);
        }
        if(changed!=node)
        {
            Swap(arr[node],arr[changed]);
            heapify(changed);
        }
    }

    void Swap(T &a,T &b)
    {
        T temp;
        temp=a;
        a=b;
        b=temp;
    }

    void Delete()
    {
        if(isEmpty()==false)
        {
            Swap(arr[1],arr[idx]);
            idx--;
            heapify(1);
        }
    }

    T getTop()
    {
        return arr[1];
    }

};
template<typename T>
struct Stack
{
    T arr[10000];
    int TOP;

    Stack()
    {
        TOP = -1;
    }

    void push(T val)
    {
        TOP++;
        arr[TOP]=val;

    }

    void pop()
    {
        if(!isEmpty())
        {
            TOP--;
        }
        else
        {
            printf("stack is empty\n");
        }
    }

    T top()
    {
        return arr[TOP];
    }

    bool isEmpty()
    {
        if (TOP == -1)
        {
            return true;
        }
        else
        {

            return false;
        }

    }

    void printAll()
    {
        for(int i=0; i<=TOP; i++)
        {
            arr[i].printDetails();
        }
    }
};

void parseInput(string str, string &name,int &milage, int &year, int &sequence)
{
    int spaceCount=0;
    for(int i=0 ; i<str.size() ; i++)
    {
        if(str[i]==' ')
        {
            spaceCount++;
        }
        if(spaceCount<2)
        {
            name+=str[i];
        }
        else if(spaceCount<3)
        {
            if(str[i]>='0' && str[i]<='9')
            {
                milage=(milage*10)+str[i]-'0'; //'0-9'
            }
        }
        else if(spaceCount<4)
        {
            if(str[i]>='0' && str[i]<='9')
            {
                year=(year*10)+str[i]-'0';
            }
        }
        else
        {
            if(str[i]>='0' && str[i]<='9' )
            {
                sequence=(sequence*10)+str[i]-'0';
            }
        }

    }
}

int main()
{
    Stack<passenger> stk = Stack<passenger>();
    Heap<passenger,compare> minHeap;
    passenger temp;
    int ticketCount;
    cout<<"\t\t\t" << "Welcome To Our Project Of Resolving Overbooked Flight\n\n"<< endl;
    cout<< "Please Enter Name Mileage Years and Sequence of passenger:\n\n"<<endl;
    string str;
    char arr[200];

    while(gets(arr))
    {
        temp = passenger();
        parseInput(string(arr),temp.name,temp.milage,temp.years,temp.sequence);
        minHeap.Insert(temp);
        fflush(stdin);
    }

    while(minHeap.isEmpty()==false)
    {
        stk.push(minHeap.getTop());
        minHeap.Delete();
    }

    stk.printAll();
    cout<<endl<<endl;
    cout<<"How Many Tickets Are Available ?" <<endl;
    cin>>ticketCount;
    cout<<"Passenger who will Get Tickets:\n"<<endl;

    for(int i=0; i<ticketCount; i++)
    {
        if(stk.isEmpty())
        {
            break;
        }
        stk.top().printDetails();
        stk.pop();
    }

    cout<<endl<<endl;

    if(stk.isEmpty())
    {
        cout<<"Everyone Got There Tickets!\n"<<endl;
    }
    else
    {
        cout<<"Rest of the Passenger will catch the next flight\n"<<endl;
        while(stk.isEmpty()==false)
        {
            stk.top().printDetails();
            stk.pop();
        }
    }

    return 0;
}

