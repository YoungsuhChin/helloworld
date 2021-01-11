#include <iostream>

// 두 개의 동등한 객체 사이에서의 이항 연산자는 멤버 함수가 아닌 외부 함수로 오버로딩 하는 것이 좋습니다. (예를 들어 Complex 의 operator+(const Complex&, const Complex&) const 와 같이 말입니다.)

// 두 개의 객체 사이의 이항 연산자 이지만 한 객체만 값이 바뀐다던지 등의 동등하지 않는 이항 연산자는 멤버 함수로 오버로딩 하는 것이 좋습니다. (예를 들어서 operator+= 는 이항 연산자 이지만 operator+=(const Complex&) 가 낫다)

// 단항 연산자는 멤버 함수로 오버로딩 하는 것이 좋습니다 (예를 들어 operator++ 의 경우 멤버 함수로 오버로딩 합니다)

// 일부 연산자들은 반드시 멤버 함수로만 오버로딩 해야 합니다 (강좌 앞 부분 참고)

class Test{
    int x;

    public:
    Test(int x): x(x){}
    Test(const Test& t): x(t.x) {}

    Test& operator++(){
        x++;
        std::cout<<"전위 증감 연산자"<<std::endl;
        return *this;
    }
//전위 증감과 후위 증감에 차이를 두기 위해 후위 증감의 경우 인자로 int를 받지만 실제로는 아무것도 전달되지 않음.
    Test operator++(int){
        Test temp(*this);
        x++;
        std::cout<<"후위 증감 연산자"<<std::endl;
        return temp;
    }

    int get_x() const{
        return x;
    }
};

void func(const Test& t){
    std::cout<<"x:"<<t.get_x()<<std::endl;
}

int main(){
    Test t(3);
    func(++t);
    func(t++);
    std::cout<<"x: "<<t.get_x()<<std::endl;
}