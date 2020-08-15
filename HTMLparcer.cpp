#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;
const char *quote = "\"";
int userInput=1;

class MainTag{
    string tagName;
    bool tagClose=false;
    vector<MainTag> subTag;
    vector<string> attribute;
    vector<string> attributeValue;
    public:
    void insertAttribute(string a,string av){
        attribute.push_back(a);
        attributeValue.push_back(av);
    }
    void printAttributeValue(string att){
        for(int i=0;i<this->attribute.size();i++){
            if(att.compare(this->attribute[i])==0){
                cout<<this->attributeValue[i]<<endl;
                return;
            }
        }
        cout<<"Not Found!"<<endl;
        return;
    }
    void printSubTagOrGoToSubTag(string codeLine){
        int findDot=codeLine.find('.');
        if(findDot>0){
            for(int i=0;i<subTag.size();i++){
                if((subTag[i].getTagName()).compare(codeLine.substr(0,findDot))==0){
                    subTag[i].printSubTagOrGoToSubTag(codeLine.substr(findDot+1));
                    return;
                }
            }
        }
        else{
            findDot=codeLine.find('~');
            for(int i=0;i<subTag.size();i++){
                if((subTag[i].getTagName()).compare(codeLine.substr(0,findDot))==0){
                    subTag[i].printAttributeValue(codeLine.substr(findDot+1));
                    return;
                }
            }
        }
        cout<<"Not Found!"<<endl;
    }
    string getTagName(){
        return this->tagName;
    }
    MainTag(string codeLine){
        int firstSpace=codeLine.find(" ");
        if(firstSpace>0){
          this->tagName=codeLine.substr(1,firstSpace-1);
          codeLine=codeLine.substr(firstSpace+1,codeLine.length());
          while(codeLine.length()!=0){
              int equalOpPosition=codeLine.find("=");
              int valueEndPos;
              for(valueEndPos=equalOpPosition+3;codeLine[valueEndPos]!=*quote;valueEndPos++);
              this->insertAttribute(codeLine.substr(0,equalOpPosition-1),
              codeLine.substr(equalOpPosition+3,valueEndPos-equalOpPosition-3));
              codeLine=codeLine.substr(valueEndPos+2);
          }
        }
        else{
          this->tagName=codeLine.substr(1,codeLine.length()-2);
        }

        int findBracket;
        do{
            getline(cin, codeLine);userInput++;
            findBracket=codeLine.find(">");
            if(codeLine[1]!='/'){
                MainTag tempTag(codeLine);
                subTag.push_back(tempTag);
            }
        }while((this->tagName).compare(codeLine.substr(2,findBracket-2))!=0);
    }
};
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,q;
    cin>>n>>q;
    //Tree formation
    vector<MainTag> rootTag;
    string codeLine;
    cin.ignore();
    while(userInput<=n){
        getline(cin, codeLine);userInput++;
        if(codeLine[1]!='/'){
            MainTag tempTag(codeLine);
            rootTag.push_back(tempTag);
        }
    }
    //End of tree formation

    // Part below takes queries and prints attribute values
    for(int i=0;i<q;i++){
        getline(cin, codeLine);
        int findDot=codeLine.find('.');
        bool tagfound=false;
        if(findDot>0){
            for(int i=0;i<rootTag.size();i++){
                if((rootTag[i].getTagName()).compare(codeLine.substr(0,findDot))==0){
                    rootTag[i].printSubTagOrGoToSubTag(codeLine.substr(findDot+1));
                    tagfound=true;
                }
            }
        }
        if(findDot<0){
            findDot=codeLine.find('~');
            for(int i=0;i<rootTag.size();i++){
                if((rootTag[i].getTagName()).compare(codeLine.substr(0,findDot))==0){
                    rootTag[i].printAttributeValue(codeLine.substr(findDot+1));
                    tagfound=true;
                }
            }
        }
        if(!tagfound) cout<<"Not Found!"<<endl;
    }
    return 0;
}

/* Sample test cases (STDIN input)

6 4
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
<tag3>
</tag3>
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value
tag1.tag2.tag3~name

Output:
Name1
Not Found!
HelloWorld
Not Found!




*/
