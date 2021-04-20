#include <iostream>
#include<string>
#include<vector>
#include <queue>
#include<chrono>
#include<fstream>
#include <sstream>

// Citations:
// Learned about how to work with c++ Clock system from: https://en.cppreference.com/w/cpp/chrono/system_clock/now
// Heapify down function from stepik Quiz 6 Solution
// Comparator class citation: Project 2 Huffman Trees


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
        distanceFromUser = 0.0;
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

class Compare{ // Comparator class citation: Project 2 Huffman Trees
public:
    int operator() (Node node1, Node node2){
        return node1.differenceScore < node2.differenceScore;
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

void heapify_down(vector<Node>& arr, int size, int root) { // Citation: Quiz 6 Solution - Discussion slides
    int L = 2*root + 1;
    int R = 2*root + 2;

    int largestChild = root;

    if(L <= size && arr.at(L).differenceScore > arr.at(largestChild).differenceScore){
        largestChild = L;
    }

    if(R <= size && arr.at(R).differenceScore > arr.at(largestChild).differenceScore){
        largestChild = R;
    }

    if(largestChild != root){
        Node temp = arr.at(root);
        arr.at(root) = arr.at(largestChild);
        arr.at(largestChild) = temp;

        heapify_down(arr,size,largestChild);
    }

}

void HeapSort(vector<Node>& myVec){

    // Build a max heap from the vector in place
    priority_queue<Node, vector<Node>, Compare> pq;

    for(int i = 0; i < myVec.size(); i++){
        pq.push(myVec.at(i));
    }

    for(int i = 0; i < myVec.size(); i++){
        myVec.at(i) = pq.top();
        pq.pop();
    }

    int last = myVec.size() - 1;

    while(last >= 0){
        Node temp = myVec.at(last);
        myVec.at(last) = myVec.at(0);
        myVec.at(0) = temp;

        last = last - 1;
        heapify_down(myVec,last,0);
    }


}


int main() {

    cout<<endl;

    cout<< "Hello and Welcome to Food-Lovers Paradise!"<<endl<<endl;

    cout<< "Please enter your favorite type of food: "<<endl<<"American"<<endl<<"Italian"<<endl;
    cout<<"Asian"<<endl<<"Mexican"<<endl<<"Indian"<<endl<<"Seafood"<<endl;

    string userFoodType;
    cin>>userFoodType;

    cout<<"Enter your maximum price limit: ";
    float userPrice;
    cin>>userPrice;

    cout<<"Enter your minimum rating requirement(0-5): ";
    float userRating;
    cin>>userRating;

    ifstream inFS;
    inFS.open("restaurants.csv");
    if(!inFS.is_open()){
        cout<<"Could not open file..."<<endl;
    }

    vector<Node> vec;

    while(!inFS.eof()){
        string str;
        getline(inFS,str);

        istringstream inSS(str);

        vector<string> allTheStrings;
        for(int i = 0; i < 5; i++){
            string temp;
            getline(inSS,temp,',');
            allTheStrings.push_back(temp);
        }

        string restName = allTheStrings.at(0);
        float restDist = stof(allTheStrings.at(1));
        float restPrice = stof(allTheStrings.at(2));
        string restCuisine = allTheStrings.at(3);
        float restRate = stof(allTheStrings.at(4));

        Node node(restName,restDist,restPrice,restCuisine,restRate);

        if(node.typeOfFood != userFoodType){
            node.differenceScore = node.differenceScore + 50;
        }

        node.differenceScore = node.differenceScore + node.distanceFromUser;

        if(node.price > userPrice){
            node.differenceScore = node.differenceScore + 1.5 * (node.price - userPrice);
        }
        else{
            if(userPrice - node.price >=5.00) {
                node.differenceScore = node.differenceScore + 0.25 * (userPrice - node.price);
            }
            else{
                node.differenceScore = node.differenceScore + 0.1 * (userPrice - node.price);
            }

        }

        if(node.rating < userRating){
            if(userRating - node.rating >= 1){
                node.differenceScore = node.differenceScore + (userRating - node.rating)*(userRating - node.rating);
            }
            else{
                node.differenceScore = node.differenceScore + (userRating - node.rating);
            }
        }

        vec.push_back(node);
    }

    cout<<endl;

    cout<<"Which Sorting function would you like to use to sort the data?"<< endl;
    cout<<"1) Heap"<<endl;
    cout<<"2) Selection"<<endl;
    cout<<"3) Bubble"<<endl;
    cout<<"Answer: ";

    int choice;
    cin>>choice;


    switch(choice) {
        case 1:
            cout << endl << "You chose Heap Sort!" << endl;
            HeapSort(vec);
            /*for(int i = 0; i < vec.size(); i++){
                cout<<vec.at(i).name<<" "<<vec.at(i).differenceScore<<endl;
            }*/
            break;
        case 2:
            cout << endl << "You chose Selection Sort!" << endl;
            SelectionSort(vec,vec.size());
            /*for(int i = 0; i < vec.size(); i++){
                cout<<vec.at(i).name<<" "<<vec.at(i).differenceScore<<endl;
            }*/
            break;
        case 3:
            cout<< endl << "You chose Bubble Sort!" << endl;
            BubbleSort(vec,vec.size());
            /*for(int i = 0; i < vec.size(); i++){
                cout<<vec.at(i).name<<" "<<vec.at(i).differenceScore<<endl;
            }*/
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    cout<< endl;
    cout<<"Here are the top 10 Restaurants suggested for you!"<<endl<<endl;
    for(int i = 0; i < 10; i++){
        cout<<i + 1<<". "<<vec.at(i).name<<endl;
    }

    cout<<endl;

    if(choice == 1) {

        auto start1 = std::chrono::system_clock::now();
        HeapSort(vec);
        auto end1 = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end1 - start1;

        cout << "It took " << diff.count() << " seconds to sort data using Heap Sort!" << endl;
    }
    else if(choice == 2){
        auto start3 = std::chrono::system_clock::now();
        SelectionSort(vec, vec.size());
        auto end3 = std::chrono::system_clock::now();

        std::chrono::duration<double> diff3 = end3 - start3;

        cout << "It took " << diff3.count() << " seconds to sort data using Selection Sort!" << endl;

    }
    else if(choice == 3) {

        auto start2 = std::chrono::system_clock::now();
        BubbleSort(vec, vec.size());
        auto end2 = std::chrono::system_clock::now();

        std::chrono::duration<double> diff2 = end2 - start2;

        cout << "It took " << diff2.count() << " seconds to sort data using Bubble Sort!" << endl;
    }


    return 0;
}
