/*
    访问者模式visitor：表示一个作用于某对象结构中的各元素的操作。它可以使得在不改变各元素的类的前提下定义作用于这些元素的新操作。
    把数据结构和作用于结构上的操作之间的耦合解开，使得操作集合可以相对自由地演化。
*/
#include <iostream>
#include <cmath>

using namespace std;

// 前置声明 Visitor 类
class Circle;
class Rectangle;

// 访问者基类，为每一个具体元素类声明一个visit操作
class Visitor {
public:
    virtual void visit(Circle* c) = 0;
    virtual void visit(Rectangle* r) = 0;
};

// 元素基类，以一个访问者为参数
class Shape {
public:
    virtual void accept(Visitor* visitor) = 0; // 接收访问者
};

// 圆形类，具体元素，实现accept
class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}
    
    double getRadius() const { return radius; }
    
    // 实现 accept 方法
    void accept(Visitor* visitor) override {
        visitor->visit(this); // 传递自身给访问者
    }

private:
    double radius;
};

// 矩形类
class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    // 实现 accept 方法
    void accept(Visitor* visitor) override {
        visitor->visit(this); // 传递自身给访问者
    }

private:
    double width;
    double height;
};

// 具体访问者类：计算面积，实现每个由visitor声明的操作，每个操作实现算法的一部分
class AreaVisitor : public Visitor {
public:
    void visit(Circle* c) override {
        double area = 3.14159 * c->getRadius() * c->getRadius();
        cout << "Circle area: " << area << endl;
    }

    void visit(Rectangle* r) override {
        double area = r->getWidth() * r->getHeight();
        cout << "Rectangle area: " << area << endl;
    }
};

// 具体访问者类：打印形状信息
class PrintVisitor : public Visitor {
public:
    void visit(Circle* c) override {
        cout << "Circle with radius: " << c->getRadius() << endl;
    }

    void visit(Rectangle* r) override {
        cout << "Rectangle with width: " << r->getWidth() 
             << " and height: " << r->getHeight() << endl;
    }
};

// 测试访问者模式
int main() {
    // 创建形状对象
    Circle circle(5.0);
    Rectangle rectangle(3.0, 4.0);

    // 创建访问者对象
    AreaVisitor areaVisitor;
    PrintVisitor printVisitor;

    // 对圆形应用访问者
    cout << "Visiting Circle:" << endl;
    circle.accept(&areaVisitor);   // 计算圆的面积
    circle.accept(&printVisitor);  // 打印圆的信息

    // 对矩形应用访问者
    cout << "\nVisiting Rectangle:" << endl;
    rectangle.accept(&areaVisitor);   // 计算矩形的面积
    rectangle.accept(&printVisitor);  // 打印矩形的信息

    return 0;
}
