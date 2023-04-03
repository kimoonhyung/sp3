#include <iostream>
#include <stdio.h>
using namespace std;
int main() {
    char* buffer = new char[50];
    for (size_t i = 0; i < 50; i++)
        buffer[i] = 0;
    cout << "Input text: ";
    cin.getline(buffer, 50);
    int words_counterasm = 0;
    int words_counterc = 0;
    int word_length_counterc = 0;
    int word_length_counterasm = 0;
    cout << "asm result: ";
    const char* format_str_for_digit = "%d ";
    __asm {
        mov ecx, 50
        mov esi, buffer
        buffer_loop :
        mov eax, 50
            sub eax, ecx
            mov al, [esi + eax]
            cmp al, 32
            jne not_space
            its_space : //если пробел
            inc words_counterasm //инкрементируем
            push ecx //помещение операнда в стек
            push esi
            push eax
            push word_length_counterasm
            push format_str_for_digit
            call printf
            add esp, 8
            pop eax // убираем(извелекаем) операнд из стека
            pop esi
            pop ecx
            mov word_length_counterasm, 0 //зануляем
            jmp next_char 
            not_space : // смотрит есть ли пробел
            cmp al, 0
            jne not_zero
            its_zero : //вау след идет ноль
            inc words_counterasm //значит инкрементируем кол-во слов
            push ecx
            push esi
            push eax
            push word_length_counterasm
            push format_str_for_digit
            call printf
            add esp, 8
            pop eax
            pop esi
            pop ecx
            jmp end_loop
            not_zero : //что-то кроме 0
    smth_else:
        inc word_length_counterasm //+1 буковка в длину слова
            next_char : //идем в след букву
        loop buffer_loop
            end_loop :
    };
    cout << endl << "---------------------------------" << endl;
    cout << "C++ result:" << " ";
    for (size_t i = 0; i < 50; i++) {
        char ch = buffer[i];
        if (ch == ' ') {
            words_counterc += 1;
            cout << word_length_counterc << ' ';
            word_length_counterc = 0;
        }
       
        else if (ch == '\0') {
            words_counterc += 1;
            cout << word_length_counterc << ' ';
            break;
        }
        else
            word_length_counterc += 1;
    }

    cout << endl << "Words count: " << words_counterc << endl;
}
