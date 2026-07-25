#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>

using namespace std;

class Admin
{
public:
    string username;
    string password;
};

class Subscriber
{
public:
    int id;
    string name;
    string phone;
    string network;
    string simType;
    double balance;

    Subscriber *next;
};

class Call
{
public:
    int subscriberID;
    string callerName;
    string receiverNumber;
    int duration;

    Call *next;
};

class Activity
{
public:
    string action;

    Activity *next;
};

class TelecomSystem
{
private:

    Subscriber *head;

    Call *front;
    Call *rear;

    Activity *top;

    double rate;

public:

    TelecomSystem()
    {
        head=NULL;
        front=NULL;
        rear=NULL;
        top=NULL;

        rate=2.0;
    }

    void addActivity(string text)
    {
        Activity *newActivity=new Activity;

        newActivity->action=text;

        newActivity->next=top;

        top=newActivity;
    }

    void menu();

    void addSubscriber();
    void viewSubscribers();
    void searchSubscriber();
    void deleteSubscriber();

    void rechargeBalance();

    void makeCall();
    void processCall();

    void saveSubscribers();
    void loadSubscribers();

    void saveCalls();
    void loadCalls();

    void reports();

    void login()
    {
        Admin admin;

        admin.username="Abdul";
        admin.password="abdulsk9";

        string user;
        string pass;

        int attempts=0;

        while(attempts<3)
        {
            cout<<endl<<endl;
          
            cout<<"\t MILESTONE TELECOM NETWORK MANAGEMENT SYSTEM"<<endl;
            cout<<endl;

            cout<<"Username : ";
            cin>>user;

            cout<<"Password : ";
            cin>>pass;

            if(user==admin.username && pass==admin.password)
            {
                cout<<endl;
                cout<<"Login Successful"<<endl;
                
                loadSubscribers();
                loadCalls();

                menu();

                return;
            }
            else
            {
                attempts++;

                cout<<"Wrong Username or Password"<<endl;
            }
        }

        cout<<"Too many attempts"<<endl;
    }

};

void TelecomSystem::addSubscriber()
{
    Subscriber *newSubscriber = new Subscriber;

    cout<<"Enter Subscriber ID: ";
    cin>>newSubscriber->id;

    cin.ignore();

    cout<<"Enter Name: ";
    getline(cin,newSubscriber->name);

    cout<<"Enter Phone Number: ";
    getline(cin,newSubscriber->phone);

    cout<<"Enter Network: ";
    getline(cin,newSubscriber->network);

    cout<<"Enter SIM Type: ";
    getline(cin,newSubscriber->simType);

    newSubscriber->balance=0;

    newSubscriber->next=NULL;

    if(head==NULL)
    {
        head=newSubscriber;
    }
    else
    {
        Subscriber *temp=head;

        while(temp->next!=NULL)
        {
            temp=temp->next;
        }

        temp->next=newSubscriber;
    }

    cout<<"Subscriber Added Successfully"<<endl;

    addActivity("Subscriber Added");
}

void TelecomSystem::viewSubscribers()
{
    if(head==NULL)
    {
        cout<<"No Subscribers Found"<<endl;
        return;
    }

    Subscriber *temp=head;

    while(temp!=NULL)
    {
        cout<<endl;
        cout<<"Subscriber ID : "<<temp->id<<endl;
        cout<<"Name          : "<<temp->name<<endl;
        cout<<"Phone Number  : "<<temp->phone<<endl;
        cout<<"Network       : "<<temp->network<<endl;
        cout<<"SIM Type      : "<<temp->simType<<endl;
        cout<<"Balance       : "<<temp->balance<<endl;

        temp=temp->next;
    }
}

void TelecomSystem::searchSubscriber()
{
    if(head==NULL)
    {
        cout<<"No Subscribers"<<endl;
        return;
    }

    int id;

    cout<<"Enter Subscriber ID: ";
    cin>>id;

    Subscriber *temp=head;

    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            cout<<endl;
            cout<<"Subscriber Found"<<endl;
            cout<<"Name : "<<temp->name<<endl;
            cout<<"Phone : "<<temp->phone<<endl;
            cout<<"Network : "<<temp->network<<endl;
            cout<<"SIM Type : "<<temp->simType<<endl;
            cout<<"Balance : "<<temp->balance<<endl;

            return;
        }

        temp=temp->next;
    }

    cout<<"Subscriber Not Found"<<endl;
}

void TelecomSystem::deleteSubscriber()
{
    if(head==NULL)
    {
        cout<<"No Subscribers"<<endl;
        return;
    }

    int id;

    cout<<"Enter Subscriber ID: ";
    cin>>id;

    Subscriber *temp=head;
    Subscriber *prev=NULL;

    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            if(prev==NULL)
            {
                head=temp->next;
            }
            else
            {
                prev->next=temp->next;
            }

            delete temp;

            cout<<"Subscriber Deleted"<<endl;

            addActivity("Subscriber Deleted");

            return;
        }

        prev=temp;
        temp=temp->next;
    }

    cout<<"Subscriber Not Found"<<endl;
}

void TelecomSystem::rechargeBalance()
{
    if(head==NULL)
    {
        cout<<"No Subscribers"<<endl;
        return;
    }

    int id;
    double amount;

    cout<<"Enter Subscriber ID: ";
    cin>>id;

    Subscriber *temp=head;

    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            cout<<"Enter Amount: ";
            cin>>amount;

            temp->balance=temp->balance+amount;

            cout<<"Recharge Successful"<<endl;
            cout<<"Current Balance: "<<temp->balance<<endl;

            addActivity("Balance Recharged");

            return;
        }

        temp=temp->next;
    }

    cout<<"Subscriber Not Found"<<endl;
}

void TelecomSystem::makeCall()
{
    if(head==NULL)
    {
        cout<<"No Subscribers Available"<<endl;
        return;
    }

    int id;

    cout<<"Enter Subscriber ID: ";
    cin>>id;

    Subscriber *temp=head;

    while(temp!=NULL)
    {
        if(temp->id==id)
        {
            break;
        }

        temp=temp->next;
    }

    if(temp==NULL)
    {
        cout<<"Subscriber Not Found"<<endl;
        return;
    }

    Call *newCall=new Call;

    newCall->subscriberID=id;
    newCall->callerName=temp->name;

    cin.ignore();

    cout<<"Enter Receiver Number: ";
    getline(cin,newCall->receiverNumber);

    cout<<"Enter Duration (Minutes): ";
    cin>>newCall->duration;

    newCall->next=NULL;

    if(front==NULL)
    {
        front=newCall;
        rear=newCall;
    }
    else
    {
        rear->next=newCall;
        rear=newCall;
    }

    cout<<"Call Added To Queue"<<endl;

    addActivity("Call Added");
}

void TelecomSystem::processCall()
{
    if(front==NULL)
    {
        cout<<"No Calls In Queue"<<endl;
        return;
    }

    Call *tempCall=front;

    Subscriber *temp=head;

    while(temp!=NULL)
    {
        if(temp->id==tempCall->subscriberID)
        {
            break;
        }

        temp=temp->next;
    }

    double cost;

    cost=tempCall->duration*rate;

    cout<<endl;
    cout<<"Processing Call"<<endl;
    cout<<"Caller : "<<tempCall->callerName<<endl;
    cout<<"Receiver : "<<tempCall->receiverNumber<<endl;
    cout<<"Duration : "<<tempCall->duration<<" Minutes"<<endl;
    cout<<"Cost : "<<cost<<endl;

    if(temp!=NULL)
    {
        if(temp->balance>=cost)
        {
            temp->balance=temp->balance-cost;

            cout<<"Call Successful"<<endl;
            cout<<"Remaining Balance : "<<temp->balance<<endl;
        }
        else
        {
            cout<<"Insufficient Balance"<<endl;
        }
    }

    front=front->next;

    if(front==NULL)
    {
        rear=NULL;
    }

    delete tempCall;

    addActivity("Call Processed");
}

void TelecomSystem::saveSubscribers()
{
    ofstream file("subscribers.csv");

    Subscriber *temp=head;

    while(temp!=NULL)
    {
        file<<temp->id<<",";
        file<<temp->name<<",";
        file<<temp->phone<<",";
        file<<temp->network<<",";
        file<<temp->simType<<",";
        file<<temp->balance<<endl;

        temp=temp->next;
    }

    file.close();

    cout<<"Subscribers Saved Successfully"<<endl;

    addActivity("Subscribers Saved");
}

void TelecomSystem::loadSubscribers()
{
    ifstream file("subscribers.csv");

    if(!file)
    {
        cout<<"File Not Found"<<endl;
        return;
    }

    while(head!=NULL)
    {
        Subscriber *temp=head;
        head=head->next;
        delete temp;
    }

    string line;

    while(getline(file,line))
    {
        Subscriber *newSubscriber=new Subscriber;

        stringstream ss(line);

        string data;

        getline(ss,data,',');
        newSubscriber->id=atoi(data.c_str());

        getline(ss,newSubscriber->name,',');

        getline(ss,newSubscriber->phone,',');

        getline(ss,newSubscriber->network,',');

        getline(ss,newSubscriber->simType,',');

        getline(ss,data,',');
        newSubscriber->balance=atof(data.c_str());

        newSubscriber->next=NULL;

        if(head==NULL)
        {
            head=newSubscriber;
        }
        else
        {
            Subscriber *temp=head;

            while(temp->next!=NULL)
            {
                temp=temp->next;
            }

            temp->next=newSubscriber;
        }
    }

    file.close();

    cout<<"Subscribers Loaded Successfully"<<endl;

    addActivity("Subscribers Loaded");
}

void TelecomSystem::saveCalls()
{
    ofstream file("calls.csv");

    Call *temp=front;

    while(temp!=NULL)
    {
        file<<temp->subscriberID<<",";
        file<<temp->callerName<<",";
        file<<temp->receiverNumber<<",";
        file<<temp->duration<<endl;

        temp=temp->next;
    }

    file.close();

    cout<<"Calls Saved Successfully"<<endl;

    addActivity("Calls Saved");
}

void TelecomSystem::loadCalls()
{
    ifstream file("calls.csv");

    if(!file)
    {
        cout<<"File Not Found"<<endl;
        return;
    }

    while(front!=NULL)
    {
        Call *temp=front;
        front=front->next;
        delete temp;
    }

    rear=NULL;

    string line;

    while(getline(file,line))
    {
        Call *newCall=new Call;

        stringstream ss(line);

        string data;

        getline(ss,data,',');
        newCall->subscriberID=atoi(data.c_str());

        getline(ss,newCall->callerName,',');

        getline(ss,newCall->receiverNumber,',');

        getline(ss,data,',');
        newCall->duration=atoi(data.c_str());

        newCall->next=NULL;

        if(front==NULL)
        {
            front=newCall;
            rear=newCall;
        }
        else
        {
            rear->next=newCall;
            rear=newCall;
        }
    }

    file.close();

    cout<<"Calls Loaded Successfully"<<endl;

    addActivity("Calls Loaded");
}

void TelecomSystem::reports()
{
    if(top==NULL)
    {
        cout<<"No Activities Recorded"<<endl;
        return;
    }

    Activity *temp=top;

    cout<<endl;
    cout<<"Activity Report"<<endl;
    cout<<"----------------------"<<endl;

    while(temp!=NULL)
    {
        cout<<temp->action<<endl;
        temp=temp->next;
    }
}

void TelecomSystem::menu()
{
    int choice;

    do
    {
        cout<<endl<<endl;
    
        cout<<"\t TELECOM MAIN MENU"<<endl;
        cout<<endl;

        cout<<"1. Add Subscriber"<<endl;
        cout<<"2. View Subscribers"<<endl;
        cout<<"3. Search Subscriber"<<endl;
        cout<<"4. Delete Subscriber"<<endl;
        cout<<"5. Recharge Balance"<<endl;
        cout<<"6. Make Call"<<endl;
        cout<<"7. Process Call"<<endl;
        cout<<"8. Save Subscribers"<<endl;
        cout<<"9. Load Subscribers"<<endl;
        cout<<"10. Save Calls"<<endl;
        cout<<"11. Load Calls"<<endl;
        cout<<"12. View Activity Report"<<endl;
        cout<<"13. Exit"<<endl;

        cout<<"Enter Choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                addSubscriber();
                break;

            case 2:
                viewSubscribers();
                break;

            case 3:
                searchSubscriber();
                break;

            case 4:
                deleteSubscriber();
                break;

            case 5:
                rechargeBalance();
                break;

            case 6:
                makeCall();
                break;

            case 7:
                processCall();
                break;

            case 8:
                saveSubscribers();
                break;

            case 9:
                loadSubscribers();
                break;

            case 10:
                saveCalls();
                break;

            case 11:
                loadCalls();
                break;

            case 12:
                reports();
                break;

            case 13:
            	saveSubscribers();
            	saveCalls();
            	cout<<"Data Saved successfully"<<endl;
                cout<<"Thank you"<<endl;
                break;

            default:
                cout<<"Invalid Choice"<<endl;
        }

    }
    while(choice!=13);
}

int main()
{
    TelecomSystem telecom;

    telecom.login();

    return 0;
}
