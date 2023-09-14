#include <iostream>
#include <iomanip>
using namespace std;

class GrowingArray {
public:
    /*
    * @param array - Исходный массив
    * @param length - Длина исходного массива
    * @param reserve - Число резервируемых ячеек
    */
    GrowingArray(double* array, int length, int reserve = 10)
    {
        this->length = length;
        this->reserve = reserve;
        this->capacity = length + reserve;
        this->array = this->recreateArray(array, length, this->capacity);
    }

    GrowingArray(const GrowingArray& growingArray) {
        this->length = growingArray.length;
        this->reserve = growingArray.reserve;
        this->capacity = growingArray.capacity;
        this->array = this->recreateArray(growingArray.array, this->length, this->capacity);
    }

    ~GrowingArray()
    {
        delete[] this->array;
    }

    /*
    * @return - Фактическая длина массива
    */
    int getCapacity() { return capacity; }

    /*
    * @return - Число элементов в массива
    */
    int getLength() { return length; }

    /*
    * Добавляет элемент в конец массива.
    * @param value - Новый элемент массива
    */
    void push(double value)
    {
        // Добавляем пустые ячейки.
        if (this->length == this->capacity) {
            this->capacity += this->reserve;
            this->array = this->recreateArray(this->array, this->length, this->capacity, true);
        }
        this->array[length] = value;
        this->length += 1;
    }

    /*
    * Удаляет последний элемент массива.
    * @return Удаленный элемент
    */
    double pop()
    {
        if (this->length == 0)
            throw out_of_range("Массив уже пуст");
        double deletedValue = this->array[this->length];
        this->length -= 1;
        // Удаляем пустые ячейки, если их слишком много.
        if (this->capacity - this->length > this->reserve) {
            this->capacity = this->length + this->reserve;
            this->array = this->recreateArray(this->array, this->length, this->capacity, true);
        }
        return deletedValue;
    }

    /*
    * @return Сумма всех элементов
    */
    double getSum() {
        double sum = 0;
        for (int i = 0; i < this->length; i++) {
            sum += this->array[i];
        }
        return sum;
    }

    /*
    * @return Сумма отрицательных элементов
    */
    double getNegativeSum() {
        double negativeSum = 0;
        for (int i = 0; i < this->length; i++) {
            if (this->array[i] < 0)
                negativeSum += this->array[i];
        }
        return negativeSum;
    }

    /*
    * @return Среднее арифметическое
    */
    double getAvg() {
        double sum = this->getSum();
        return (sum / this->length);
    }

    /*
    * Добавляет к каждому элементу массива число.
    * @param value - Число которое прибавится к каждому элементу
    */
    void appendToAll(double value) {
        for (int i = 0; i < this->length; i++) {
            this->array[i] += value;
        }
    }

    double& operator[] (const int index)
    {
        if (index < 0 || index >= this->length)
            throw out_of_range("Индекс за пределами массива");
        return this->array[index];
    }

    friend ostream& operator<< (ostream& os, const GrowingArray& arr) {
        for (int i = 0; i < arr.length; i++) {
            os << setprecision(3) << fixed;
            os << arr.array[i] << " ";
        }
        return os;
    }

private:
    double* recreateArray(double* array, int length, int capacity, bool clear = false)
    {
        double* newArray = new double[capacity];
        for (int i = 0; i < length; i++)
            newArray[i] = array[i];
        if (clear)
            delete[] array;
        return newArray;
    }

    // Число элементов в массиве.
    int length;

    // Фактическая длина массива.
    int capacity;

    // Число резервируемых ячеек при обновлении массива.
    int reserve;

    // Массив.
    double* array;
};


/*
* Трижды выводит строки в консоль с некоторыми манипуляциям.
*/
void showGrowingArray(GrowingArray& arr) {
    cout << arr.getLength() << endl;
    cout << arr << endl;
    double sum = arr.getSum();
    double avg = arr.getAvg();
    arr.push(sum);
    arr.push(avg);
    cout << arr << endl;
    arr.appendToAll(arr.getNegativeSum()/2);
    cout << arr << endl;
}

int main()
{
    // Инициализация
    int initLength = 0;
    cin >> initLength;
    double* initArray = new double[initLength];
    for (int i = 0; i < initLength; i++)
        cin >> initArray[i];
    GrowingArray arr = GrowingArray(initArray, initLength);
    delete[] initArray;

    // Задание
    cout << arr.getLength() << endl;
    showGrowingArray(arr);

    // Команды
    int action;
    cin >> action;
    while (action != 0) {
        if (action == 1) {
            double value;
            cin >> value;
            arr.push(value);
            cout << "+: ";
        }
        if (action == 2) {
            arr.pop();
            cout << "-: ";
        }
        showGrowingArray(arr);
        cin >> action;
    }

    return 0;
}