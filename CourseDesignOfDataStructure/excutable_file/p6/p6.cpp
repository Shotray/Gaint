#include<iostream>

using namespace std;

struct Tree{
    Tree* _left;
    Tree* _right;
    string _name;
    bool _is_first;
    Tree():_left(NULL),_right(NULL),_name(""),_is_first(false){}
};

Tree* find(Tree* node,string name){
    Tree* ans=nullptr;
    bool is_found=false;
    if(!node) return ans;
    if(node->_name==name)return node;
    if(node->_left){
        ans=find(node->_left,name);
        if(ans) is_found=true;
    }
    if(node->_right&&!is_found) ans=find(node->_right,name);
    return ans;
}

Tree* find_parent(Tree* node,string name){
    Tree* ans=nullptr;
    bool is_found=false;
    if(!node) return ans;
    if(node->_left){
        if(node->_left->_name==name) ans=node;
        else ans=find_parent(node->_left,name);
        if(ans) is_found=true;
    }
    if(node->_right&&!is_found) {
        if(node->_right->_name==name) ans=node;
        else ans=find_parent(node->_right,name);
    };
    return ans;
}

void print(Tree* node)
{
    if(!node->_left) {
        cout<<"He has no child."<<endl;
        return;
    }
    cout<<node->_name<<"'s children are:";
    node=node->_left;
    while(node!=NULL){
        cout<<node->_name<<' ';
        node=node->_right;
    }
    cout<<endl;
}

void del(Tree*node){
    if(node->_left)del(node->_left);
    if(node->_right)del(node->_right);
    if(!node->_left&&!node->_right)
        delete node;
    return;
}

void del_child_tree(Tree*node_parent,Tree* node){
    if(node->_is_first==true){
        node_parent->_left=node->_right;
        if(node->_left)
            del(node->_left);
        delete node;
    }
    else{
        node_parent->_right=node->_right;
        if(node->_left)
            del(node->_left);
        delete node;
    }
}

//插入孩子
void insert(Tree* node,string name){
    Tree* newnode=new Tree;
    newnode->_name=name;
    if(!node->_left){
        node->_left=newnode;
        newnode->_is_first=true;
        return;
    }
    node=node->_left;
    while(node->_right){
        node=node->_right;
    }
    
    node->_right=newnode;
    return;
}

void modify(Tree* root,string new_name){
    root->_name=new_name;
    return;
}



void solve(){
    cout<<"**             Genealogy management system             **"<<endl;
    cout<<"========================================================="<<endl;
    cout<<"**    Please select the action you want to perform     **"<<endl;
    cout<<"**         A.Perfect genealogyPerfect genealogy        **"<<endl;
    cout<<"**                 B.Add family members                **"<<endl;
    cout<<"**            C.Dissolution of child family            **"<<endl;
    cout<<"**             D.Change family member's name           **"<<endl;
    cout<<"**                       E.Exit                        **"<<endl;
    Tree* root=new Tree;
    cout<<"First,we build a family tree."<<endl;
    cout<<"Please input the name of ancestor:";
    string name;
    cin>>name;
    insert(root,name);
    cout<<"The name of ancestor is "<<root->_left->_name<<endl;
    while(true){
        cout<<"Please select an action:";
        char action;
        cin>>action;
        if(action=='A'){
            cout<<"Please enter the name which you want to perfect his family tree:";
            cin>>name;
            Tree* node=find(root,name);
            if(!node){
                insert(root,name);
                node=find(root,name);
            }
            int total;
            cout<<"Please input the number of his children:";
            cin>>total;
            if(cin.fail())
                throw invalid_argument("Wrong input!");
            cout<<"Please input children's name in turn:";
            for(int i=0;i<total;i++){
                cin>>name;
                insert(node,name);
            }
            print(node);
        }
        else if(action=='B'){
            cout<<"Please enter the name which you want to add child to:";
            cin>>name;
            Tree* node=find(root,name);
            if(!node){
                insert(root,name);
                node=find(root,name);
            }
            cout<<"Please enter the name of child:";
            cin>>name;
            insert(node,name);
            print(node);
        }
        else if(action=='C'){
            cout<<"Please enter the name which you want to destroy his family:";
            cin>>name;
            Tree* node_parent=find_parent(root,name);
            Tree* node=find(root,name);
            cout<<"The person whose family will be destroyed is:"<<node->_name<<endl;
            print(node);
            del_child_tree(node_parent,node);
        }
        else if(action=='D'){
            cout<<"Please enter the name which you want to change his name:";
            cin>>name;
            Tree* node=find(root,name);
            string n=node->_name;
            cout<<"Please enter changed name:";
            cin>>name;
            modify(node,name);
            cout<<n<<" has changed to "<<name<<endl;
        }
        else if(action=='E'){
            del(root);
            break;}
        else{
            cout<<"WRONG INPUT!Please input again!"<<endl;
        }
    }
    return;
}

int main(void){
    solve();
    system("pause");
    return 0;
}