#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h> 
using namespace std;

struct Node{

  bool isword = false;
  Node* children[256] = {nullptr};
  vector<pair<int, int>> direcciones;
  Node(){}

};

Node* nuevo(){
    Node * nodo = new Node;
    for(int i=0; i<256; ++i){
        nodo->children[i] = NULL;
    }
    return nodo;
}

struct Trie{
  Node* root;
  int size = 0;
  string filename;
  Trie(string file){
      filename = file;
      root = nuevo();
      loadDirections();
  };

    void countRam(){

        char word[256];
        string aux;
        int count = 0;
        printAllWords(root, word, aux, count);
        cout << count << endl;
    }

    void printAllWords(Node* root, char* wordArray, string aux, int &count, int pos = 0)
    {

        if(root == nullptr)
            return;
        if(root->isword)
        {
            printWord(wordArray, pos, aux, count);
        }
        for(int i=0; i<256; i++)
        {
            if(root->children[i] != nullptr)
            {
                wordArray[pos] = i;
                printAllWords(root->children[i], wordArray, aux,count, pos+1);
            }
        }
        count +=  sizeof(root) + sizeof(*root);
    }

   void loadDirections(){
       ifstream file(filename);
       string str;
       string aux;
       string word;
       while (getline(file, str))
       {
           aux = str;

           for(int i = aux.size()-1; i>=0; i--){
               if((int)aux[i] == 47){
                   break;
               }
               else{
                   word.push_back(aux[i]);
               }
           }


           int n = word.length();
           for (int i = 0; i < n / 2; i++)
               swap(word[i], word[n - i - 1]);

          // cout << word << endl;
          // cout << str << endl;

           add(word, const_cast<char*>(str.c_str()));
           word.clear();
       }

   }

  void printPrefix(string aux){
      Node* sen = root;
      for(auto it:aux){
          auto i = (int)it;
          if(!sen->children[i]){
              cout << "No encontrado" << endl;
              return;
          }else{
              sen = sen->children[i];
          }
      }
      if(sen != nullptr){
          char wordArray[256];
          int x=0;
          printAllWords(sen, wordArray, aux,x);
          /*
          fstream file;
          file.open("index.txt", ios::in | ios::out | ios::binary);
          char dir[200];
          for(auto it:sen->direcciones){
              auto pos1 = it.first;
              auto pos2 = it.second;
              file.seekg(pos1, ios::beg);
              file.read((char*)&dir, sizeof(dir));
              cout << dir << endl;
          }

          file.close();
           */
      }

  }
    void add(string aux){

        Node* sen = root;

        for(auto it:aux){
            auto i = (int)it;
            if(!sen->children[i]){
                sen->children[i] = nuevo();
                sen = sen->children[i];
            }else{
                sen = sen->children[i];
            }
        }
        sen->isword = true;

    }

    void printWord(char *str, int n, string aux, int i)
    {
        cout<<endl<<aux;
        for(int i=0; i<n; i++)
        {
            cout<<str[i];
        }
        cout << endl;
    }






  void add(string aux, char* path){

    Node* sen = root;

    for(auto it:aux){
        auto i = (int)it;
        if(!sen->children[i]){
            sen->children[i] = nuevo();
            sen = sen->children[i];
        }else{
            sen = sen->children[i];
        }
    }
      sen->isword = true;

    fstream file;
    file.open("index.txt", ios::in | ios::out | ios::binary);
    file.seekp(0, ios::end);
    auto pos1 = file.tellg();
    char dir[200];
    strncpy(dir, path, 200);
    file.write((char*)&dir, sizeof(dir));
    auto pos2 = file.tellg();
    file.close();

    sen->direcciones.push_back({pos1,pos2});


  }


  bool find(string aux){
      Node* sen = root;

      for(auto it:aux){
          auto i = (int)it;
          if(!sen->children[i]){
              return 0;
          }else{
              sen = sen->children[i];
          }
      }
      if(sen != nullptr && sen->isword){
          fstream file;
          file.open("index.txt", ios::in | ios::out | ios::binary);
          char dir[200];
          for(auto it:sen->direcciones){
              auto pos1 = it.first;
              auto pos2 = it.second;
              file.seekg(pos1, ios::beg);
              file.read((char*)&dir, sizeof(dir));
              cout << dir << endl;
          }

          file.close();
          return true;
      }
      return false;
  }

  void count(string aux){
      Node* sen = root;

      for(auto it:aux){
          auto i = (int)it;
          if(!sen->children[i]){
              return;
          }else{
              sen = sen->children[i];
          }
      } cout << endl;
      if(sen != nullptr && sen->isword){
          fstream file;
          file.open("index.txt", ios::in | ios::out | ios::binary);
          char dir[200];
          int cont = 0;
          for(auto it:sen->direcciones){
              auto pos1 = it.first;
              auto pos2 = it.second;
              file.seekg(pos1, ios::beg);
              file.read((char*)&dir, sizeof(dir));
              cout << dir << endl;
              cont++;
          }

          file.close();
          cout << endl << "Numero de instancias de " << aux << ": " << cont << endl;
          return;
      }

    }


};
