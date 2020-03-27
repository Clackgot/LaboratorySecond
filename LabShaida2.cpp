
#include <iostream>
#include <vector>
#include <ctime>
#include "windows.h"

using namespace std;

void set_cur(int x, int y);
void custom_clear();

//Скрыть курсор
void remove_cur()
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
//Перечисление цветов Black, Blue, Green и т.д.
enum Colors 
{ 
    Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
    DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
}; 

template<Colors txt = LightGray, Colors bg = Black> ostream& color(ostream& text);
void rand_init_vec(vector<int>& vector, int count);
void print_vec(vector <int> vector);
void print_vec(vector <int> vector, int flag);
void print_vec(vector <int> vector, int flag1, int flag2);
void print_vec(vector <int> vector, int flag1, int flag2, int flag3);
void sort(vector<int>& vec, bool mode, bool log, bool animate);
void bin_search(vector<int> arr, int key, bool log, bool animatet);
template<typename type >type getValue(string s);

int main()
{
    setlocale(LC_ALL, "");//Кириллица в консоле
    remove_cur();//Не показывать курсор
    int key;//Искомый ключ
    bool sort_direct = false;//Направление сортировки false - возрастание, true - убывание 
    bool animate = false;//Режим вывода 0 - Списком| 1 - В одну строку
    bool log = false;//Вывод хода выполнения операции
    vector<int> vec;//Вектор
    int vec_size = 0;//Размер вектора
    vec_size = getValue<int>("Введите размер массива");//Ввод размера вектора с клавиатуры
    rand_init_vec(vec, vec_size);//Инициазиация массива случайными значениями с зерном time(0)
        sort_direct = getValue<bool>("Введите порядок сортировка(0 - возрастание| 1 - убывание)");//Ввод направления сортировки вектора с клавиатуры
        log = getValue<bool>("Выводить ход сортировки(0 - Нет| 1 - Да");//Ввод режима вывода хода сортировки(да/нет)
        if (log)
        {
            animate = getValue<bool>("Режим вывода хода сортировки(0 - Списком| 1 - В одну строку)");//Ввод режима вывода хода сортировки
        }
    sort(vec, sort_direct, log, animate);
    key = getValue<int>("Введите элемент поиска");//Ввод искомого ключа поиска
    log = getValue<bool>("Выводить ход поиска(0 - Нет| 1 - Да)");//Ввод режима вывода хода поиска(да/нет)
    if (log)
    {
        animate = getValue<bool>("Режим вывода хода поиска(0 - Списком| 1 - В одну строку)");//Ввод режима вывода хода поиска
    }
    bin_search(vec,key, log, animate);
}

//Шаблон безопасного считывания данных со стандартного потока istream и вывод
template<typename type > type getValue(string s)
{
    while (true) // Цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        cout << s << ": ";
        type a;
        cin >> a;
        if (cin.fail()) // Если предыдущее извлечение оказалось неудачным,
        {
            system("cls");
            cin.clear(); // То возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // Удаляем значения предыдущего ввода из входного буфера
        }
        else // Eсли всё хорошо, то возвращаем a
            return a;
    }
}

//Установка позиции курсора
void set_cur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Установка позиции курсора в координаты [0,0]
void custom_clear()
{
    set_cur(0, 0);
}

//Шаблон функции задания цвета вывода выходного потока ostream
template<Colors txt = LightGray, Colors bg = Black> ostream& color(ostream& text) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
    return text;
}

//Инициазиация массива случайными значениями с зерном time(0)
void rand_init_vec(vector<int>& vector, int count)
{
    srand(time(0));//Задание зерна ПСГЧ


    for (int i = 0; i < count; i++)
    {
        vector.push_back(rand() % 10);//Добавление сгенерированных элементов в конец вектора
    }
}

//Перегруженная сигнатура функции вывода вектора на экран
void print_vec(vector <int> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        cout << "[" << vector.at(i) << "]";
    }
    cout << endl;
}

//Перегруженная сигнатура функции вывода вектора на экран с выделением одного элемента цветом заданного индекса flag
void print_vec(vector <int> vector, int flag)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == flag)cout << color<Red, Black> << "[" << vector.at(i) << "]" << color<LightGray, Black> << color;
        //cout << color<LightGray, Black> << "test " << color<Red, Black> << "test2\n" << color;
        else cout << "[" << vector.at(i) << "]";
    }
    cout << endl;
}

//Перегруженная сигнатура функции вывода вектора на экран с выделением двух элементов цветом заданных индексов flag
void print_vec(vector <int> vector, int flag1, int flag2)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == flag1)cout << color<Green, Black> << "[" << vector.at(i) << "]" << color<LightGray, Black> << color;
        else if (i == flag2)cout << color<Red, Black> << "[" << vector.at(i) << "]" << color<LightGray, Black> << color;
        //cout << color<LightGray, Black> << "test " << color<Red, Black> << "test2\n" << color;
        else cout << "[" << vector.at(i) << "]";
    }
    cout << endl;
}

//Перегруженная сигнатура функции вывода вектора на экран с выделением трёх элементов цветом заданных индексов flag
void print_vec(vector <int> vector, int flag1, int flag2, int flag3)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == flag1)cout << color<Green, Black> << "[" << vector.at(i) << "]" << color<LightGray, Black> << color;
        else if (i == flag2)cout << color<Red, Black> << "[" << vector.at(i) << "]" << color<LightGray, Black> << color;
        else if (i == flag3)cout << color<Blue, Black> << "[" << vector.at(i) << "]" << color<LightGray, Black> << color;
        //cout << color<LightGray, Black> << "test " << color<Red, Black> << "test2\n" << color;
        else cout << "[" << vector.at(i) << "]";
    }
    cout << endl;
}

//Сортировка Shell
//mode 0 - возрастание, mode 1 - убывание
//log - выводить ход работы
//аnimate - лог в одной строке
void sort(vector<int>& vec, bool mode, bool log, bool animate)
{
    system("cls");//Очистка консоли
    int step, i, j, tmp, delay;//Объявление переменных
    delay = 50;//Задержка вывода хода работы на экран в мс
    int step_count = 0; //Счётчик итераций сортировки
    // Выбор шага
    for (step = vec.size() / 2; step > 0; step /= 2)//Сортировка между собой значений, стоящих один от другого на расстоянии step deltaStep=step/2
        // Перечисление элементов, которые сортируются на определённом шаге
        for (i = step; i < vec.size(); i++)
            // Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
            if (!mode)
                for (j = i - step; j >= 0 && vec.at(j) > vec.at(j + step); j -= step)
                {
                    tmp = vec.at(j);//Сохранение переменной во временную переменную
                    vec.at(j) = vec.at(j + step);//Обмен между собой ячеек с расстоянием step между друг другом
                    vec.at(j + step) = tmp;//Обмен между собой ячеек с расстоянием step между друг другом
                    step_count++;//Увеличение счётчика итераций сортировки
                    if (log) {
                        if (animate)custom_clear();//Очистить первую строку
                        print_vec(vec, j, j + step);//Вывести массив, с маркерами на текущих элементах сортировки

                        if (animate)Sleep(delay);//Ожидание
                    }
                }
            else if (mode)
                for (j = i - step; j >= 0 && vec.at(j) < vec.at(j + step); j -= step)
                {
                    tmp = vec.at(j);
                    vec.at(j) = vec.at(j + step);
                    vec.at(j + step) = tmp;
                    step_count++;
                    if (log) {
                        if (animate)custom_clear();
                        print_vec(vec, j, j + step);
                        if (animate)Sleep(delay);
                    }
                }
            else
            {
                return;
            }
            if (log)cout << "Сортировка выполнена за " << step_count << " перестановок" << endl;
}

//Бинарный поиск
//arr - Вектор int
//key - искомый ключ
//log - вывод хода поиска
//animate - режим вывода хода поиска
int bin_search(vector<int> vec, int key)
{
    sort(vec, false, false, false);//Сортировка по возрастанию
    int m;// m — середина области поиска
    int l = -1;//Левая граница диапазона
    int r = vec.size();//Павая граница диапазона
    while (l < r - 1)//Пока левая граница не равна правой
    {
        m = (l + r) / 2;//Нахождение середины области поиска           
        if (vec.at(m) <= key)l = m;//Если средний элемент области поиска меньше или равен ключу сместить левую границу вправо до середины 
        else r = m;//Иначе сместить праву границу влево до середины 
        print_vec(vec, m, l, r);//Вывести массив
        Sleep(300);
    } 
    return r;
}

//Безопасное считывание из потока istream
int getValue()
{
    while (true) // Цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        int a;
        cin >> a;
        if (cin.fail()) // Если предыдущее извлечение оказалось неудачным,
        {
            cin.clear(); // То возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); // Удаляем значения предыдущего ввода из входного буфера
        }
        else // Eсли всё хорошо, то возвращаем a
            return a;
    }
}

//Бинарный поиск
//arr - Вектор int
//key - искомый ключ
//log - вывод хода поиска
//animate - режим вывода хода поиска
void bin_search(vector<int> arr, int key, bool log, bool animate)
{
    int delay = 1200;//Задержка вывода хода работы на экран
    int iter = 0;//Счётчик итераций поиска ключа
    bool flag = false;//Найден ли элемент
    int l = 0; //Левая граница диапазона
    int r = arr.size(); //Правая граница диапазона
    int mid;//Середина области поиска
    sort(arr, false, false, false);//Сортировка массива по возрастанию

    while (l < r) {//Пока левая граница меньше правой
        mid = (l + r) / 2; // Считываем срединный индекс отрезка [l,r]
        iter++;//Увеличение счётчика итераций поиска ключа

        if (log) {//Если режим вывода хода работы
            for (int i = 0; i < arr.size(); i++)//Перебор вектора
            {
                if (i >= l && i < mid)cout << color<Yellow, Black> << "[" << arr.at(i) << "]" << color<LightGray, Black> << color;//Выделить жёлтым левый диапазон
                else if (i < r && i > mid)cout << color<Blue, Black> << "[" << arr.at(i) << "]" << color<LightGray, Black> << color;//Выделить синим правый диапазон
                else if (i == mid && l!=mid && r!=mid)cout << color<Red, Black> << "[" << arr.at(i) << "]" << color<LightGray, Black> << color;//Выделить красным середины диапазон поиска
                else cout << color<LightGray, Black> << "[" << arr.at(i) << "]" << color<LightGray, Black> << color;//Иначе не закрашивать
            }
            if (!animate)//Если без анимации
            {
                cout << endl;
            }
            else {//Анимация
                Sleep(delay);//Задержка delay мс
                custom_clear();//Перевод курсора в [0,0]
            }
        }

        //Проверяем, какую часть нужно отбросить с поиска
        if (arr[mid] > key) r = mid;//Если средний элемент диапазона поиска больше ключа - сместить правую границу влево
        else l = mid + 1;//Иначе сместить левую границу вправо
    }

    if(r>0)r--; //Уменьшение правую границу области поиска
    system("cls");
    if (arr[r] == key)//Если 
    { 
        cout << "Элемент со значением " << key << " найден";
    }
    
    else cout << "Извините, но такого элемента в массиве нет";

}

