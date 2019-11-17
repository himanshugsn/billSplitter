#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class person{
    public:
    string name;
 float  totalExpense;
 float totalSpent;
 float balanceAmt;
 person(){
     totalExpense = 0;
     totalSpent = 0;
     balanceAmt = 0;
 }

};

unordered_map<string, person> myMap;

bool boolSort(person &a,person &b){
    return a.balanceAmt < b.balanceAmt;
}

void newExpense(){
    int numPeople; 
    cout << "Please Enter number of people\n";
    cin >> numPeople;
    vector<string> peopleNames;
    for(int i = 0; i < numPeople; i++){
        cout << "Enter name of " << i+1 << "th person\n";
        string tempName;
        cin >> tempName;
        peopleNames.push_back(tempName);
    }
   
   /* cout << "\nprinting vector\n";
       for(int i = 0; i < numPeople; i++){
        cout << peopleNames[i] << endl;
    }
    */
    

    cout << "\nEnter the Expense Amount\n";
    int amount;
    cin >> amount;

     //entering names in hashmap
    //person p[numPeople];
   for(int i = 0 ; i < numPeople;i++){
        //p[i].name = peopleNames[i];
        // check whether person is present or not;

        //myMap[peopleNames[i]] = p[i];
        unordered_map<string,person> :: iterator it = myMap.find(peopleNames[i]);
        if(it != myMap.end()){
            continue;
        } 
        // if not present then create and add
        else{
            person p;
            p.name = peopleNames[i];
            myMap[peopleNames[i]] = p;
        }


    }


    cout << "Enter who paid the Bill\n";
    string payee;
    cin >> payee;
    unordered_map<string,person> :: iterator it = myMap.find(payee);
    if(it != myMap.end()){
        it->second.totalSpent += amount;
    }
    else{
       cout <<  "Wrong name entered .... Try again with correct name \n";
       return;
    }


    float mean = amount/numPeople;
    //cout << mean;

    // entering expenses
    for(int i = 0; i < numPeople; i++){
        unordered_map<string,person> :: iterator it = myMap.find(peopleNames[i]);
        //cout << " name : " <<  it->second.name << endl;
        float temp;
        temp = it->second.totalExpense;
        
        //cout  << "temp" << temp <<endl;
        
        it->second.totalExpense = mean + temp;
        
        //cout <<"new temp" << temp << endl;
    }

   cout << " printing data \n";
   unordered_map<string,person> :: iterator itr = myMap.begin();
    while (itr != myMap.end())
    {
        cout << itr->second.name << " " << itr->second.totalExpense <<" " <<  itr->second.totalSpent << endl;
        itr++;
    }


   
}


void settlePayments(unordered_map<string,person> myMap){
    list<person> getters;
    list<person> givers;

    unordered_map<string,person> :: iterator i = myMap.begin();
    for(i= myMap.begin(); i != myMap.end(); i++ ){
        i->second.balanceAmt = i->second.totalSpent - i->second.totalExpense;
        if(i->second.balanceAmt < 0){
            givers.push_back(i->second);
        }
        if(i->second.balanceAmt > 0){
            getters.push_back(i->second);
        }
    }
   //  printing of getters and givers
    list <person> :: iterator it; 
    cout << "getters list";
    for(it = getters.begin(); it != getters.end(); ++it) 
        cout << '\t' << (*it).name << " " << (*it).balanceAmt; 
    cout << '\n'; 

    cout << "givers list"; 
    for(it = givers.begin(); it != givers.end(); ++it) 
        cout << '\t' << (*it).name << " " << (*it).balanceAmt; 
    cout << '\n';

    

    // list <person> :: iterator it; 
    for(it = getters.begin(); it != getters.end(); ++it) 
        (*it).balanceAmt = abs((*it).balanceAmt);
    
    for(it = givers.begin(); it != givers.end(); ++it) 
        (*it).balanceAmt = abs((*it).balanceAmt);


    getters.sort(boolSort);
    givers.sort(boolSort);

       //  printing of getters and givers
    //list <person> :: iterator it; 
    cout << "getters list";
    for(it = getters.begin(); it != getters.end(); ++it) 
        cout << '\t' << (*it).name << " " << (*it).balanceAmt; 
    cout << '\n'; 

    cout << "givers list"; 
    for(it = givers.begin(); it != givers.end(); ++it) 
        cout << '\t' << (*it).name << " " << (*it).balanceAmt; 
    cout << '\n';


    
    list<person> :: iterator givIt;
    list<person> :: iterator getIt;
    for(givIt = givers.begin(); givIt != givers.end(); givIt++){
        for(getIt = getters.begin(); getIt != getters.end(); getIt++){

            if((*getIt).balanceAmt == 0)
                break;

            if((*givIt).balanceAmt == (*getIt).balanceAmt){
                cout << (*givIt).name << " has to give " << (*givIt).balanceAmt << " to " << (*getIt).name <<endl;
                (*getIt).balanceAmt = 0;
                (*givIt).balanceAmt = 0;
            }

            else if((*givIt).balanceAmt > (*getIt).balanceAmt){
                cout << (*givIt).name << " has to give " << (*getIt).balanceAmt << " to " << (*getIt).name <<endl;
                (*givIt).balanceAmt -= (*getIt).balanceAmt;
                (*getIt).balanceAmt = 0;
            }

            else if((*givIt).balanceAmt < (*getIt).balanceAmt){
                 cout << (*givIt).name << " has to give " << (*givIt).balanceAmt << " to " << (*getIt).name <<endl;
                (*getIt).balanceAmt -= (*givIt).balanceAmt;
                (*givIt).balanceAmt = 0;
            }

        }
    }
    
    

  
    
    
    
   


   /* unordered_map<string,person> :: iterator itr = myMap.begin();
    while (itr != myMap.end())
    {
        cout << itr->second.name << " " << itr->second.balanceAmt << endl;
        itr++;
    }
    */
    

}


int main(){
    int exit  = 0;
    while(exit != 1){
        cout << "Select one \n";
        cout << "1. New Expense\n";
        cout << "2. Settle payments\n";
        int n;
        cin >> n;

        switch (n)
        {
         case 1:
            newExpense();    
            break;
        case 2:
            settlePayments(myMap);
            return 0;
        default:
            break;
        }
    }
   
    
  

   return 0;
    
}



/*



  unordered_map<string,person> :: iterator it = myMap.begin();
    while (it != myMap.end())
    {
        cout << it->second.name << " " << it->second.totalExpense <<" " it->second.totalSpent << endl;
        it++;
    }
    

    */