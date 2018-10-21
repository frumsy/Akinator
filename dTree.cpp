#include <string>
#include <iostream>

using namespace std;

struct Node {
    string data;
    string answer; //the answer for the current game at play. Should be set back to null on insert method
    Node* left;//yes
    Node* right;//no
};

//helper functions:
string GetResponse(string s){
    cout << s << endl;
    string line;
    getline(cin, line);
    return line;
}

bool isLeaf(Node* root)
{
    if(root == NULL){cout<<"ERROR"<<endl;return false;}
    if(root->left == NULL && root->right == NULL)
    {
        return true;
    }
    return false;
}

bool YesNoInput(){
    string input;
    cin >> input;    
    if(input == "Yes")
    {
        return true;
    }
    else if(input == "No")
    {
        return false;
    }
    else
    {
        cout<<"sorry input must be (Yes/No)." <<endl;
        return YesNoInput();
    }   
}

bool PlayAgain(Node*& root, Node*& first)
{
    cout << "Would you like to play again(Yes/No)" <<endl;
    if(YesNoInput())
    {
        root = first;
        return true;
    }
    else
    {
        return false;
    }
}

Node* GetNewNode(string data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->answer = "";
    newNode->left = newNode->right = NULL;
    return newNode; 
}

Node* Insert(Node* root, string newAnimalData, string questionData)
{
    if(root==NULL)
    {
       root = GetNewNode(newAnimalData);
    }
    else if (isLeaf(root))//root not NULL but it's a leaf
    {
        //create newQuestion node
        //create newLeafNode
        //add both root(leafnode) and newLeafNode to branches of tree
        Node* newAnimalNode = GetNewNode(newAnimalData);
        Node* oldAnimalNode = GetNewNode(root->data);
        root->data = questionData;
        root->left = newAnimalNode;
        root->right = oldAnimalNode;
        //root = Insert(root,"","");
    }
    else
    {
       cout <<"internal"<<endl; 
    }
    return root;
}

int main(){
    cout << "Welcome to the Guessing Game." <<endl;
    cout << "Think of an animal, and I will guess what it is." <<endl;
    Node* first;
    Node* root = NULL; 
    first = root = Insert(root, "snake", "");
    
    bool playing = true;
    while(playing){
        //cout << endl <<"ping\n"<< (root==first) <<endl;
        if(isLeaf(root))
        {
            cout << "Did you think of " + root->data <<endl;
            if(YesNoInput())//guessed right
            {
                cout << "Wow! I am great!" <<endl;
                playing = PlayAgain(root, first);
            }
            else//guessed wrong
            {
                //read in animal
                cout<<("I give up what is it?")<<endl;
                cin.clear();cin.sync();
                string animal;
                cin >> animal;//Not that this has to be one word long no white spaces allowed
                cin.clear();cin.sync();cin.ignore();
                //get new question
                string newQuestion = GetResponse("Please type a question whose answer is yes for " + animal +" and no for " + root->data); 

                cout<<"Thank you."<<endl;
                //insert new question
                root = Insert(root, animal, newQuestion);
                playing = PlayAgain(root, first);
            }
        }
        else//internal node
        {//ask question
            cout << root->data << endl;
            if(YesNoInput())//yes
            {
                root->answer = "Yes";
                root = root->left;
            }
            else
            {
                root->answer = "No";
                root = root->right;
            } 
        }
    }//end while loop
      
    cout <<"It was nice playing with you. Good Bye!" << endl;
    return 0;
}
