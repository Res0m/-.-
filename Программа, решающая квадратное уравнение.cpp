#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

class Menutxt {
private:
    vector<string> menutxt;
    string instructions;

public:
    Menutxt(vector<string> menu, string instr) : menutxt(menu), instructions(instr) {}

    void show() {
        cout << "-------------------------" << endl;
        cout << "      РУКОВОДСТВО ПОЛЬЗОВАТЕЛЯ" << endl;
        cout << "-------------------------" << endl;
        cout << instructions << endl;
        cout << "-------------------------" << endl;
        cout << "      ГЛАВНОЕ МЕНЮ" << endl;
        cout << "-------------------------" << endl;
        for (const auto& item : menutxt) {
            cout << item << endl;
        }
        cout << "-------------------------" << endl;
    }
};

class Input {
private:
    string com;

public:
    void getInput() {
        cout << "Введите команду: ";
        cin >> com;
    }

    string getCommand() const {
        return com;
    }
};

class Equation {
private:
    double a, b, c;

public:
    Equation(double aVal, double bVal, double cVal) : a(aVal), b(bVal), c(cVal) {}

    void solve() {
        double D = b * b - 4 * a * c;
        if (D > 0) {
            double x1 = (-b + sqrt(D)) / (2 * a);
            double x2 = (-b - sqrt(D)) / (2 * a);
            cout << "Два решения: x1 = " << (x1 == 0 ? 0 : abs(x1)) << ", x2 = " << (x2 == 0 ? 0 : abs(x2)) << endl;
        }
        else if (D == 0) {
            double x = -b / (2 * a);
            cout << "Одно решение: x = " << (x == 0 ? 0 : abs(x)) << endl;
        }
        else {
            cout << "Нет решений" << endl;
        }
    }

    static void printHelp() {
        cout << "-------------------------" << endl;
        cout << "  Справка по решению квадратного уравнения" << endl;
        cout << "-------------------------" << endl;
        cout << "Для решения квадратного уравнения вида ax^2 + bx + c = 0, выполните следующие шаги:" << endl;
        cout << "1. Определите значения коэффициентов a, b и c." << endl;
        cout << "2. Вычислите дискриминант D = b^2 - 4ac." << endl;
        cout << "3. Если D > 0, у уравнения два действительных корня." << endl;
        cout << "   - x1 = (-b + sqrt(D)) / (2a)" << endl;
        cout << "   - x2 = (-b - sqrt(D)) / (2a)" << endl;
        cout << "4. Если D = 0, у уравнения один действительный корень." << endl;
        cout << "   - x = -b / (2a)" << endl;
        cout << "5. Если D < 0, у уравнения нет действительных корней (комплексные корни)." << endl;
        cout << "-------------------------" << endl;
    }
};

class Mainmenu {
private:
    Menutxt& menu;
    Input& input;

public:
    Mainmenu(Menutxt& menuRef, Input& inputRef) : menu(menuRef), input(inputRef) {}

    void quit() {
        cout << "Завершение программы..." << endl;
        exit(0);
    }

    void back() {
        cout << "Возврат в главное меню..." << endl;
        menu.show();
    }

    void Qequation() {
        double a, b, c;

        cout << "Введите коэффициенты (a, b, c) для квадратного уравнения ax^2 + bx + c = 0:" << endl;


        cout << "a (не должно быть нулем): ";
        while (!(cin >> a) || a == 0) {
            cout << "Неверный ввод. Пожалуйста, введите ненулевое число для коэффициента 'a': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "b: ";
        while (!(cin >> b)) {
            cout << "Неверный ввод. Пожалуйста, введите корректное число для коэффициента 'b': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "c: ";
        while (!(cin >> c)) {
            cout << "Неверный ввод. Пожалуйста, введите корректное число для коэффициента 'c': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (a == 1 && b == 0 && c == 0) {
            cout << "У уравнения только одно решение: x = 0" << endl;
            return;
        }

        Equation eq(a, b, c);
        try {
            eq.solve();
        }
        catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    void help() {
        Equation::printHelp();
    }

    void executeCommand() {
        input.getInput();
        string command = input.getCommand();
        if (command == "1") {
            Qequation();
            backOrQuit();
        }
        else if (command == "2") {
            help();
            backOrQuit();
        }
        else if (command == "3") {
            quit();
        }

        else {
            cout << "Неверная команда! Пожалуйста, попробуйте снова." << endl;
        }
    }

    void backOrQuit() {
        cout << "1. Назад" << endl;
        cout << "2. Выход" << endl;
        cout << "Выберите опцию: ";
        int option;
        cin >> option;
        switch (option) {
        case 1:
            back();
            break;
        case 2:
            quit();
            break;
        default:
            cout << "Неверная опция! Пожалуйста, выберите снова." << endl;
            backOrQuit();
            break;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    string instructions = "Добро пожаловать в программу по решению квадратных уравнений!\n\n"
        "Эта программа помогает вам решать квадратные уравнения вида ax^2 + bx + c = 0.\n"
        "Пожалуйста, следуйте инструкциям на экране, чтобы продолжить.\n";

    vector<string> menuItems = { "1. Решить квадратное уравнение", "2. Справка", "3. Выход" };
    Menutxt menu(menuItems, instructions);
    Input input;
    Mainmenu mainMenu(menu, input);

    menu.show();
    bool running = true;
    while (running) {
        mainMenu.executeCommand();
    }

    return 0;
}