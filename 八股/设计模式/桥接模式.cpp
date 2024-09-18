/*
    对象的继承关系在编译时就定义好了，所以无法在运行时改变从父类继承的实现。
    子类的实现与它的父类有非常紧密的依赖关系，以至于父类实现中的任何变化必然会导致子类的变化。
    但需要复用子类时，如果继承下来的实现不适合解决新的问题，则父类必须重写或被其他更合适的类替换。
    这种依赖关系限制了灵活性并最终限制了复用性。

    合成/聚合复用原则CARP：尽量使用合成/聚合，尽量不要使用类继承。

    桥接模式Bridge：将抽象部分与它的实现部分分离，使它们都可以独立地变化。
    这个模式通过引入一个桥接接口，将抽象与实现解耦，从而支持各自的独立变化。

    抽象类（Abstraction）： 这是一个接口，定义了高层操作，但不实现它们。它通常持有一个指向实现类的引用。
    实现类（Implementor）： 这是一个接口，定义了具体的实现操作。它通常不会提供实现细节，而是将这些细节留给具体实现类。
    具体实现类（ConcreteImplementor）： 实现 Implementor 接口，并提供具体的实现。
    修正抽象类（RefinedAbstraction）： 继承自 Abstraction，并实现具体的操作。

    不太好理解，就是多层API调用
*/
#include <iostream>
#include <memory>

// Implementor: 绘制API
class DrawingAPI {
public:
    virtual void drawCircle(float x, float y, float radius) const = 0;
    virtual void drawRectangle(float x, float y, float width, float height) const = 0;
    virtual ~DrawingAPI() = default;
};

// ConcreteImplementor: 具体实现类
class DrawingAPI1 : public DrawingAPI {
public:
    void drawCircle(float x, float y, float radius) const override {
        std::cout << "DrawingAPI1: Circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
    
    void drawRectangle(float x, float y, float width, float height) const override {
        std::cout << "DrawingAPI1: Rectangle at (" << x << ", " << y << ") with width " << width << " and height " << height << std::endl;
    }
};

class DrawingAPI2 : public DrawingAPI {
public:
    void drawCircle(float x, float y, float radius) const override {
        std::cout << "DrawingAPI2: Circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
    
    void drawRectangle(float x, float y, float width, float height) const override {
        std::cout << "DrawingAPI2: Rectangle at (" << x << ", " << y << ") with width " << width << " and height " << height << std::endl;
    }
};

// Abstraction: 图形
class Shape {
public:
    virtual void draw() const = 0;
    virtual void resize(float factor) = 0;
    virtual ~Shape() = default;
protected:
    Shape(std::shared_ptr<DrawingAPI> drawingAPI) : drawingAPI(drawingAPI) {}
    std::shared_ptr<DrawingAPI> drawingAPI;
};

// RefinedAbstraction: 圆形
class Circle : public Shape {
public:
    Circle(float x, float y, float radius, std::shared_ptr<DrawingAPI> drawingAPI)
        : Shape(drawingAPI), x(x), y(y), radius(radius) {}
    
    void draw() const override {
        drawingAPI->drawCircle(x, y, radius);
    }
    
    void resize(float factor) override {
        radius *= factor;
    }

private:
    float x, y, radius;
};

// RefinedAbstraction: 矩形
class Rectangle : public Shape {
public:
    Rectangle(float x, float y, float width, float height, std::shared_ptr<DrawingAPI> drawingAPI)
        : Shape(drawingAPI), x(x), y(y), width(width), height(height) {}
    
    void draw() const override {
        drawingAPI->drawRectangle(x, y, width, height);
    }
    
    void resize(float factor) override {
        width *= factor;
        height *= factor;
    }

private:
    float x, y, width, height;
};

int main() {
    std::shared_ptr<DrawingAPI> api1 = std::make_shared<DrawingAPI1>();
    std::shared_ptr<DrawingAPI> api2 = std::make_shared<DrawingAPI2>();

    Shape* shapes[] = {
        new Circle(5, 10, 7, api1),
        new Rectangle(3, 6, 8, 4, api2),
        new Circle(10, 20, 5, api2)
    };

    for (Shape* shape : shapes) {
        shape->draw();
        shape->resize(2);
        shape->draw();
        delete shape;
    }

    return 0;
}
