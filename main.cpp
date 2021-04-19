#include <iostream>
#include<string>
#include<vector>
#include <queue>
#include<chrono>

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
    cout<<"Asian"<<endl<<"Mexican"<<endl;

    string userFoodType;
    cin>>userFoodType;

    cout<<"Enter your maximum price limit: ";
    float userPrice;
    cin>>userPrice;

    cout<<"Enter your minimum rating requirement(0-5): ";
    float userRating;
    cin>>userRating;

    // This is where we need to randomize data and add it to the vec<Node>
    Node node1("McDonalds",1,15.35,"American",2.5);
    Node node2("CheeseCake Factory",5,62.59,"American",5.0);
    Node node3("Piesanos",2,55.99,"Italian",4.9);
    Node node4("Flacos",8,25.22,"Mexican",4.2);
    Node node5("ChikFila",2,15.95,"American",4.3);
    Node node6("Sushi-2-go",2,15.20,"Asian",1.1);
    Node node7("DragonFly",6,50.49,"Asian",4.8);
    Node node8("TacoBell",3,14.31,"Mexican",2.2);
    Node node9("TheDiner",10,31.22,"American",4.1);
    Node node10("ReggaeShack",3,16.76,"Mexican",3.0);
    Node node11("SweetBerries",5,21.99,"American",4.5);
    Node node12("ChinaStar",11,23.42,"Asian",3.4);
    Node node13("FiveStar",5,13.28,"Italian",3.3);
    Node node14("Embers",15,44.20,"Italian",4.9);
    Node node15("FreshKitchen",20,22.21,"American",5.0);
    Node node16("BagelsNoodles",7,19.90,"Asian",3.1);
    Node node17("Chuys",8,33.60,"Mexican",3.7);
    Node node18("Mamas Southern Kitchen",15,36.78,"American",4.2);
    Node node19("SaboraMexico",11,27.80,"Mexican",2.1);
    Node node20("ElIndio",2,15.75,"Mexican",4.3);

    // This is where we need to randomize data and add it to the vec<Node>
    vector<Node> vec;
    vec.push_back(node1);
    vec.push_back(node2);
    vec.push_back(node3);
    vec.push_back(node4);
    vec.push_back(node5);
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
    vec.push_back(node20);

    // This is where we need to randomize data and add it to the vec<Node>
    for(int i = 0; i < vec.size(); i++){
        Node& node = vec.at(i);

        if(node.typeOfFood != userFoodType){
            node.differenceScore = node.differenceScore + 50;
        }

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
            cout << "You chose Heap Sort!" << endl;
            HeapSort(vec);
            /*for(int i = 0; i < vec.size(); i++){
                cout<<vec.at(i).name<<" "<<vec.at(i).differenceScore<<endl;
            }*/
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
    for(int i = 0; i < 10; i++){
        cout<<i + 1<<". "<<vec.at(i).name<<" SCORE: "<<vec.at(i).differenceScore<<endl;
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
        BubbleSort(vec, vec.size());
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
