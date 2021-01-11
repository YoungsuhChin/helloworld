#include <iostream>
#include <string.h>

/*
문자 c 혹은 C 형식 문자열 str 에서 생성할 수 있는 생성자와 복사 생성자

문자열의 길이를 리턴하는 함수(length)

문자열 대입 함수(assign)

문자열 메모리 할당 함수(reserve) 및 현재 할당된 크기를 알아오는 함수(capacity)

특정 위치의 문자를 리턴하는 함수(at)

특정 위치에 특정 문자열을 삽입하는 함수(insert)

특정 위치의 특정 개수의 문자를 지우는 함수(erase)

특정 위치를 시작으로 특정 문자열을 검색하는 함수(find)

두 문자열을 사전식 비교하는 함수(compare)


*/
class MyString{
    char* string_content;
    int string_length;
    int memory_capacity;

    public:
    MyString(int capacity); //capacity만큼 미리 할당

    MyString(char c); //문자 하나로 생성
    MyString(const char* str); //문자열부터 생성
    MyString(const MyString& str); //복사생성자
    ~MyString();

    int length() const;
    int capacity() const;
    void reserve(int size);

    void print() const;
    void println() const;

    MyString& assign(const MyString& str);
    MyString& assign(const char* str);

    char at(int i) const;

    MyString& insert(int loc, const MyString& str);
    MyString& insert(int loc, const char* str);
    MyString& insert(int loc, char c);

    MyString& erase(int loc, int num);


    int find(int find_from, MyString& str)const;
    int find(int find_from, const char* str)const;
    int find(int find_from, char c) const;

    int compare(const MyString& str) const;
    
    bool operator==(MyString& str);

    char& operator[](const int index);
};

MyString::MyString(int capacity){
    string_content=new char[capacity];
    string_length=0;
    memory_capacity=capacity;
}

MyString::MyString(char c){
    string_content = new char[1];
    string_content[0]=c;
    string_length=1;
}

MyString::MyString(const char* str){
    string_length=strlen(str);
    string_content=new char[string_length];
    for(int i=0;i!=string_length;i++){ string_content[i]=str[i];}
}
MyString::MyString(const MyString& str){
    string_length=str.string_length;
    string_content=new char[string_length];
    for(int i=0;i!=string_length;i++) string_content[i]=str.string_content[i];

}
MyString::~MyString(){
    delete[] string_content;
}

int MyString::length() const{
    return string_length;
}

void MyString::print() const{
    for(int i=0;i!=string_length;i++){
        std::cout<<string_content[i];
    }
}
void MyString::println() const{
    for(int i=0;i!=string_length;i++){
        std::cout<<string_content[i];
    }
    std::cout<<std::endl;
}
MyString& MyString::assign(const MyString& str){
    if(str.string_length>memory_capacity){
        delete[] string_content;
    
    string_content=new char[str.string_length];
    memory_capacity=str.string_length;
    }
    for(int i=0 ;i!=str.string_length;i++){
        string_content[i]=str.string_content[i];
    }

    string_length=str.string_length;

    return *this;
}

MyString& MyString::assign(const char*  str){
    int str_length=strlen(str);
    if(str_length>memory_capacity){
        delete[] string_content;

        string_content = new char[str_length];
        memory_capacity=str_length;
    }
    for(int i=0;i!=str_length;i++){
        string_content[i]=str[i];
    }
    string_length=str_length;

    return *this;
}
int MyString::capacity() const{
    return memory_capacity;
}

void MyString::reserve(int size){
    if(size>memory_capacity){
        char* prev_string_content=string_content;

        string_content=new char[size];
        memory_capacity=size;

        for(int i=0;i!=string_length;i++){
            string_content[i]=prev_string_content[i];
        }
        delete[] prev_string_content;
    }
}

char MyString::at(int i) const{
    if(i>=string_length||i<0)
        return NULL;
    else
        return string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str){
    if(loc<0 ||loc>string_length) return *this;

    if(string_length +str.string_length > memory_capacity){

        if(memory_capacity*2>string_length+str.string_length)
            memory_capacity*=2;
        else
            memory_capacity=string_length+str.string_length;

        char * prev_string_content=string_content;
        string_content=new char[memory_capacity];

        int i;//insert되는 부분 직전까지 내용 복사
        for(i=0;i<loc;i++){
            string_content[i]=prev_string_content[i];
        }
        //새로이 insert 되는 문자열 찾기
        for(int j=0;j!=str.string_length;j++){
            string_content[i+j]=str.string_content[j];
        }
        //원래 문자열 나머지 뒷부분 복사
        for(;i<string_length;i++){
            string_content[str.string_length+i]=prev_string_content[i];
        }
        delete[] prev_string_content;
        string_length+=str.string_length;
        return *this;
    }

    //초과하지 않은 경우-동적할당할 필요 없음
    //효율적 insert를 위해 밀리는 부분을 먼저 뒤로 밀어버린다.

    for(int i=string_length-1;i>=loc;i--){
        string_content[i+str.string_length]=string_content[i];
    }

    for(int i=0;i>str.string_length;i++){
        string_content[i+loc]=str.string_content[i];
    }
    string_length+=str.string_length;
    return *this;
}
MyString& MyString::insert(int loc, const char* str){
    MyString temp(str);
    return insert(loc, temp);
}
MyString& MyString::insert(int loc, char c){
    MyString temp(c);
    return insert(loc, temp);
}
MyString& MyString::erase(int loc, int num){
    if(num<0||loc<0||loc>string_length)return *this;

    for(int i=loc+num;i<string_length;i++){
        string_content[i-num]=string_content[i];
    }
    string_length-=num;
    return *this;
}
int MyString::find(int find_from, MyString& str) const{
    int i, j;
    if(str.string_length==0) return -1;
    for(i=find_from;i<=string_length-str.string_length;i++){
        for(j=0;j<str.string_length;j++){
            if(string_content[i+j] != str.string_content[j])break;
        }
        if(j==str.string_length) return i;
    }
    return -1;
}
int MyString::find(int find_from, const char* str) const{
    MyString temp(str);
    return find(find_from, temp);
}
int MyString::find(int find_from, char c) const{
    MyString temp(c);
    return find(find_from, temp);
}
int MyString::compare(const MyString& str)const{
    for(int i=0;i<std::min(string_length,str.string_length);i++){
        if(string_content[i]>str.string_content[i]){
            return 1;
        }
        else if(string_content[i]<str.string_content[i]){
            return -1;
        }
    }
    if(string_length==str.string_length) return 0;
    
    //참고로 abc와 abcd의 크기 비교는 abcd가 더 뒤에 오게 된다.
    else if(string_length>str.string_length)
        return 1;
    
    return -1;
}
bool MyString::operator==(MyString& str){
    return !compare(str);
}
char& MyString::operator[](const int index){
    return string_content[index];
}

int main(){
    MyString str("abcdef");
    str[3]='c';
    str.println();
    
    MyString str1("a word");
    MyString str2("sentence");
    MyString str3("sentence");
    if(str1==str2){
        std::cout<<"st1=str2"<<std::endl;
    }
    else{
        std::cout<<"str1!=str2"<<std::endl;
    }

    if(str2==str3){
        std::cout<<"str2=str3"<<std::endl;
    }
    else{
        std::cout<<"str2!=str3"<<std::endl;
    }
    // MyString str3("this is a very very long string");
    // std::cout<<"Location of first <very> in the string: "<<str3.find(0,"very")<<std::endl;
    // std::cout<<"Location of second <very> in the string: "<<str3.find(str3.find(0,"very")+1,"very")<<std::endl;

    // MyString str1("very long string");
    // MyString str2("<some string inserted between>");
    // str1.reserve(30);

    
    // std::cout<<"capacity: "<<str1.capacity()<<std::endl;
    // std::cout<<"String length: "<<str1.length()<< std::endl;
    // str1.println();

    // str1.insert(5,str2);
    // str1.println();
   
    // std::cout << "Capacity : " << str1.capacity() << std::endl;
    // std::cout << "String length : " << str1.length() << std::endl;
    // str1.println();
}