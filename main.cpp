#include <iostream>
#include<string>
#include<vector>


using namespace std;

class Node{
public:
    string name;
    string typeOfFood; // American, Italian, Asian, Mexican, Seafood
    float distanceFromUser; // in miles
    float price; // average price for two people
    float rating; // 1-5 stars
    float differenceScore;

    Node(){
        name = "";
        typeOfFood = "";
        distanceFromUser = 0;
        price = 0.0;
        rating = 0.0;
        differenceScore = 0.0;
    }

    Node(string n,float dist,float p,string food,float rate){
        name = n;
        distanceFromUser = dist;
        price = p;
        typeOfFood = food;
        rating = rate;
        differenceScore = 0;
    }
};

void SelectionSort(vector<Node>& myVec,int size){
    for(int i = 0; i < size - 1; i++){
        int minIndex = i;

        for(int j = i + 1; j < size; j++){
            if(myVec.at(j).differenceScore <= myVec.at(minIndex).differenceScore){
                minIndex = j;
            }
        }
        Node temp = myVec.at(minIndex);
        myVec.at(minIndex) = myVec.at(i);
        myVec.at(i) = temp;
    }
}

void BubbleSort(vector<Node>& myVec, int size){
    for(int i = 0; i < size - 1; i++){
        int swapped = 0;
        for(int j = 0; j < size - i - 1; j++){
            if(myVec.at(j).differenceScore >= myVec.at(j + 1).differenceScore){
                Node temp = myVec.at(j);
                myVec.at(j) = myVec.at(j+1);
                myVec.at(j+1) = temp;
                swapped = 1;
            }
        }
        if(swapped == 0){
            break;
        }
    }
}


void merge(vector<Node>& myVec, int start, int middle, int end){
    cout<<"CALLING MERGE!";

    int sizeLeft = middle - start + 1;
    int sizeRight = end - middle;

    vector<Node> leftVec;
    vector<Node> rightVec;

    for(int i = 0; i < sizeLeft; i++){
        Node& node = myVec.at(start + i);
        leftVec.at(i) = node;

    }
    for(int j = 0; j < sizeRight; j++){
        Node& node = myVec.at(middle + 1 + j);
        rightVec.at(j) = node;
    }

    int i = 0;
    int j = 0;
    int k = start;

    while(i < sizeLeft && j < sizeRight){
        if(leftVec.at(i).differenceScore <= rightVec.at(j).differenceScore){
            myVec.at(k) = leftVec.at(i);
            i++;
        }
        else{
            myVec.at(k) = rightVec.at(j);
            j++;
        }
        k++;
    }

    while(i < sizeLeft){
        myVec.at(k) = leftVec.at(i);
        i++;
        k++;
    }

    while(j < sizeRight){
        myVec.at(k) = rightVec.at(j);
        j++;
        k++;
    }
}

void mergeSort(vector<Node>& myVec, int start, int end){
    cout<<"CALLING THE SORT!";

    if(start < end){
        int middle = start + (end - 1) / 2;

        mergeSort(myVec,start,middle);
        mergeSort(myVec,middle + 1,end);
        merge(myVec,start,middle,end);
    }
}


int main() {

    cout<<endl;

    cout<< "Hello and Welcome to Food-Lovers Paradise!"<<endl<<endl;

    cout<< "Please enter your favorite type of food: "<<endl<<"American"<<endl<<"Italian"<<endl;
    cout<<"Asian"<<endl<<"Mexican"<<endl;

    string userFoodType;
    cin>>userFoodType;

    cout<<"Enter your maximum price limit: ";
    float userPrice;
    cin>>userPrice;

    cout<<"Enter your minimum rating requirement(0-5): ";
    float userRating;
    cin>>userRating;


    Node node1("McDonalds",1,15.35,"American",2.5);
    Node node2("CheeseCake Factory",5,62.59,"American",5.0);
    Node node3("Piesanos",2,55.99,"Italian",4.9);
    Node node4("Flacos",8,25.22,"Mexican",4.2);
    /*Node node5("ChikFila",2,15.95,"American",4.3);
    Node node6("Sushi-2-go",2,15.20,"Asian",1.1);
    Node node7("DragonFly",6,50.49,"Asian",4.8);
    Node node8("TacoBell",3,14.31,"Mexican",2.2);
    Node node9("TheDiner",10,31.22,"American",4.1);
    Node node10("ReggaeShack",3,16.76,"Mexican",3.0);
    Node node11("SweetBerries",5,21.99,"American",4.5);
    Node node12("ChinaStar",11,23.42,"Asian",3.4);
    Node node13("FiveStar",5,13.28,"Italian",3.3);
    Node node14("Embers",15,41.20,"Italian",4.9);
    Node node15("FreshKitchen",20,22.21,"American",5.0);
    Node node16("BagelsNoodles",7,19.90,"Asian",3.1);
    Node node17("Chuys",8,33.60,"Mexican",3.7);
    Node node18("Mamas Southern Kitchen",15,36.78,"American",4.2);
    Node node19("SaboraMexico",11,27.80,"Mexican",2.1);
    Node node20("ElIndio",2,15.75,"Mexican",4.3);*/


    vector<Node> vec;
    vec.push_back(node1);
    vec.push_back(node2);
    vec.push_back(node3);
    vec.push_back(node4);
    /*vec.push_back(node5);
    vec.push_back(node6);
    vec.push_back(node7);
    vec.push_back(node8);
    vec.push_back(node9);
    vec.push_back(node10);
    vec.push_back(node11);
    vec.push_back(node12);
    vec.push_back(node13);
    vec.push_back(node14);
    vec.push_back(node15);
    vec.push_back(node16);
    vec.push_back(node17);
    vec.push_back(node18);
    vec.push_back(node19);
    vec.push_back(node20);*/



    for(int i = 0; i < vec.size(); i++){
        Node& node = vec.at(i);

        if(node.typeOfFood != userFoodType){
            node.differenceScore = node.differenceScore + 50;
        }

        if(node.price > userPrice){
            node.differenceScore = node.differenceScore + (node.price - userPrice);
        }

        if(node.rating < userRating){
            if(userRating - node.rating >= 1){
                node.differenceScore = node.differenceScore + (userRating - node.rating)*(userRating - node.rating);
            }
            else{
               node.differenceScore = node.differenceScore + (userRating - node.rating);
            }
        }
    }

    cout<<endl;

    cout<<"Which Sorting function would you like to use to sort the data?"<< endl;
    cout<<"1) Merge"<<endl;
    cout<<"2) Selection"<<endl;
    cout<<"3) Bubble"<<endl;
    cout<<"Answer: ";

    int choice;
    cin>>choice;

    int size = vec.size();

    switch(choice) {
        case 1:
            cout << "You chose Merge Sort!" << endl;
            mergeSort(vec,0,size - 1);
            break;
        case 2:
            cout << "You chose Selection Sort!" << endl;
            SelectionSort(vec,vec.size());
            /*for(int i = 0; i < vec.size(); i++){
                cout<<vec.at(i).name<<" "<<vec.at(i).differenceScore<<endl;
            }*/
            break;
        case 3:
            cout<< "You chose Bubble Sort!" << endl;
            BubbleSort(vec,vec.size());
            /*for(int i = 0; i < vec.size(); i++){
                cout<<vec.at(i).name<<" "<<vec.at(i).differenceScore<<endl;
            }*/
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    cout<<"Here are the top 10 Restaurants suggested for you!"<<endl;
    cout<<"1. "<<vec.at(0).name<<endl;
    cout<<"2. "<<vec.at(1).name<<endl;
    cout<<"3. "<<vec.at(2).name<<endl;
    cout<<"4. "<<vec.at(3).name<<endl;
    /*cout<<"5. "<<vec.at(4).name<<endl;
    cout<<"6. "<<vec.at(5).name<<endl;
    cout<<"7. "<<vec.at(6).name<<endl;
    cout<<"8. "<<vec.at(7).name<<endl;
    cout<<"9. "<<vec.at(8).name<<endl;
    cout<<"10. "<<vec.at(9).name<<endl;*/



    return 0;
}
