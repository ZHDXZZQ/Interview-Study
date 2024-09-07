/*
    解释器模式interpreter：给定一个语言，定义它的文法的一种表示，并定义一个解释器，用来解释该语言的句子。
    如果一个特定类型的问题发生的频率足够高，则将该问题的各个实例表示为一个简单语言中的句子。例如：正则表达式处理email和电话号码等
    优点：可以很容易的改变和扩展文法，使用类来表示文法规则，使用继承来改变或扩展。
    缺点：为文法中的每一条规则定义了至少一个类，如果包含许多规则文法可能难以管理和维护。
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// 上下文类，用于存储和管理变量
class Context {
private:
    std::unordered_map<std::string, int> variables; // 存储变量名和对应的值
public:
    // 设置变量的值
    void setVariable(const std::string& name, int value) {
        variables[name] = value;
    }

    // 获取变量的值
    int getVariable(const std::string& name) {
        return variables[name];
    }

    // 检查变量是否存在
    bool hasVariable(const std::string& name) {
        return variables.find(name) != variables.end();
    }
};

// 抽象表达式类
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret(Context& context) = 0; // 接受上下文并返回计算结果
};

// 数字表达式类，表示一个数字，终结符表达式
class NumberExpression : public Expression {
private:
    int number;
public:
    explicit NumberExpression(int number) : number(number) {}

    int interpret(Context& context) override {
        return number;
    }
};

// 变量表达式类，表示一个变量，终结符表达式
class VariableExpression : public Expression {
private:
    std::string name;
public:
    explicit VariableExpression(const std::string& name) : name(name) {}

    int interpret(Context& context) override {
        if (context.hasVariable(name)) {
            return context.getVariable(name);
        } else {
            std::cerr << "Error: Variable " << name << " is not defined." << std::endl;
            return 0; // 默认返回0，或根据需求进行错误处理
        }
    }
};

// 加法表达式类，非终结符表达式
class AddExpression : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    AddExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) 
        : left(left), right(right) {}

    int interpret(Context& context) override {
        return left->interpret(context) + right->interpret(context);
    }
};

// 减法表达式类，非终结符表达式
class SubtractExpression : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    SubtractExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right) 
        : left(left), right(right) {}

    int interpret(Context& context) override {
        return left->interpret(context) - right->interpret(context);
    }
};

// 测试代码
int main() {
    Context context;
    context.setVariable("x", 10); // 设置变量x的值为10
    context.setVariable("y", 5);  // 设置变量y的值为5

    // 表达式：x + 3 - y
    auto expression = std::make_shared<SubtractExpression>(
        std::make_shared<AddExpression>(
            std::make_shared<VariableExpression>("x"),
            std::make_shared<NumberExpression>(3)
        ),
        std::make_shared<VariableExpression>("y")
    );

    // 解释表达式并输出结果
    std::cout << "Result: " << expression->interpret(context) << std::endl; // 输出: Result: 8

    return 0;
}

// 以下同样是一种实现，但是没有用到context
// #include <iostream>
// #include <string>
// #include <map>
// #include <stack>
// #include <sstream>

// // 抽象表达式类
// class Expression {
// public:
//     virtual int interpret(std::map<std::string, int>& context) = 0;
//     virtual ~Expression() = default;
// };

// // 变量解释器类，终结符表达式
// class VariableExpression : public Expression {
// private:
//     std::string name;
// public:
//     VariableExpression(const std::string& name) : name(name) {}

//     int interpret(std::map<std::string, int>& context) override {
//         // 从上下文中获取变量的值
//         return context[name];
//     }
// };

// // 数字解释器类，终结符表达式
// class NumberExpression : public Expression {
// private:
//     int number;
// public:
//     NumberExpression(int number) : number(number) {}

//     int interpret(std::map<std::string, int>& context) override {
//         return number;
//     }
// };

// // 加法解释器类，非终结符表达式
// class AddExpression : public Expression {
// private:
//     Expression* left;
//     Expression* right;
// public:
//     AddExpression(Expression* left, Expression* right) : left(left), right(right) {}

//     int interpret(std::map<std::string, int>& context) override {
//         // 递归解释左右子表达式
//         return left->interpret(context) + right->interpret(context);
//     }

//     ~AddExpression() {
//         delete left;
//         delete right;
//     }
// };

// // 减法解释器类，非终结符表达式
// class SubtractExpression : public Expression {
// private:
//     Expression* left;
//     Expression* right;
// public:
//     SubtractExpression(Expression* left, Expression* right) : left(left), right(right) {}

//     int interpret(std::map<std::string, int>& context) override {
//         // 递归解释左右子表达式
//         return left->interpret(context) - right->interpret(context);
//     }

//     ~SubtractExpression() {
//         delete left;
//         delete right;
//     }
// };

// // 解释器客户端
// class InterpreterClient {
// public:
//     static Expression* parse(const std::string& expression) {
//         std::stack<Expression*> stack;
//         std::istringstream iss(expression);
//         std::string token;

//         // 简单的解析器，支持数字和加减运算
//         while (iss >> token) {
//             if (token == "+") {
//                 // 取出栈中的两个表达式作为左右操作数
//                 Expression* right = stack.top(); stack.pop();
//                 Expression* left = stack.top(); stack.pop();
//                 stack.push(new AddExpression(left, right));
//             } else if (token == "-") {
//                 Expression* right = stack.top(); stack.pop();
//                 Expression* left = stack.top(); stack.pop();
//                 stack.push(new SubtractExpression(left, right));
//             } else {
//                 // 数字转换为数字表达式并入栈
//                 stack.push(new NumberExpression(std::stoi(token)));
//             }
//         }

//         // 返回最终的表达式树
//         return stack.top();
//     }
// };

// int main() {
//     // 定义一个上下文，储存变量的值
//     std::map<std::string, int> context;

//     // 输入表达式并解析
//     std::string expression = "3 5 + 2 -";
//     Expression* exp = InterpreterClient::parse(expression);

//     // 解释并输出结果
//     int result = exp->interpret(context);
//     std::cout << "Result of expression '" << expression << "' is: " << result << std::endl;

//     delete exp;
//     return 0;
// }
