#include "number.h"

//допилить нули в начале

uint2022_t from_uint(uint32_t x) {
    uint2022_t value;
    for(int i = 0; i < 68; i++){
        value.array[i] = 0;
    }
//    x.number[63] = i;
//    for(int j = 0; j < 63; j++){
//        x.number[j] = 0;
//    }
    cout<<value.array[67] << endl;
    value.array[67] = (x % base);
    cout<<value.array[67] << endl;
    value.array[66] = (x / base);
//    cout << value.number[66] << value.number[67];
    return value;
}

//разобраться со строкой и баффом

uint2022_t from_string(const char* buff) {
    uint2022_t value;
    uint32_t c;
    uint32_t s = 0;
    string line = buff;
    uint8_t len = line.size();
    for(int i = 0; i < 68*9 - len; i++){
        line = '0' + line;
    }
    for(int i = 0; i < 68; i++){
        c = 100000000;
        for(int j = i*9; j < i*9 + 9; j++){
            uint8_t digit = int(line[j] - '0');
            s += digit * c;
            c = c / 10;
        }
        value.array[i] = s;
        s = 0;
    }
//    for(int i = 0; i < 68; i++){
//        if(value.number[i] != 0){
//            cout << value.number[i];
//        }
//    }
    return value;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t value;
    uint32_t numb;
    uint32_t overload = 0;
    for (int i = 67; i >= 0; i--){
        numb = lhs.array[i] + rhs.array[i] + overload;
        value.array[i] = numb % base;
        overload = numb / base;
    }
    return value;

}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t value;
    uint32_t numb;
    bool flag = false;
    for (int i = 67; i >= 0; i--){
        //объявляем i-е элементы массивов в х и у
        uint32_t x = lhs.array[i];
        uint32_t y = rhs.array[i];
        if(x > y){
            if(flag){
                numb = x - y - 1;
                value.array[i] = numb;
                flag = false;
            }
            else{
                numb = x - y;
                value.array[i] = numb;
            }
        }
        else if(x == y){
            value.array[i] = 0;
            flag = false;
        }
        else{
            numb = base + x - y;
            value.array[i] = numb;
            flag = true;
        }
//        cout << numb << endl;
//        cout << x << endl;
//        cout << y << endl;
    }
    return value;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t value;
    uint64_t overload = 0;
    int j, num;
    int k = 0;
    //заполняем нулями
    for(int i = 0; i < 68; i++) {
        value.array[i] = 0;
    }
    for(int i = 67; i >= 0; i--) {
        j = 67;
        //объявляем произведение из юинта
        uint2022_t composition = from_uint(0);
        num = j - k;
        while(num >= 0) {
            //вычисляем число по базе
            composition.array[num] = uint64_t(((uint64_t(lhs.array[i]) * (uint64_t(rhs.array[j])) + overload))) % base;
            //считаем перегрузку
            overload = uint64_t((uint64_t(lhs.array[i]) * (uint64_t(rhs.array[j])) + overload)) / base;
            j -= 1;
            num -= 1;
        }
        k += 1;
        //прибавляем к ответу произведение
        value = value + composition;
//        cout << value << endl;
//        cout << overload << endl;
    }
    return value;
}


bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for(int i = 67; i >= 0; i--) {
        //если элементы массива не равны, то выводим false
        if (lhs.array[i] != rhs.array[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs == rhs){
        return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream& stream, const uint2022_t& value) {
    int i = 0;
    int point = 0;
    //ставим i на ненулевую позицию
    while(value.array[i] == 0){
        i++;
    }
    point = i;
    while(i < 68){
        if(i == point){
            stream << value.array[i];
            i += 1;
        }
        else{
            stream.width(9);
            stream.fill('0');
            stream << value.array[i];
            i += 1;
        }
    }
    return stream;

}
