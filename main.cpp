#include <iostream>
using namespace std;


class List
{

public:
    
    int GetSize() { return Size; } //геттер для size
    
    void clear(); //обнуляем список
    void push_front(int data); // вставка в начало
    void push_back(int data); // вставка в конец
    void pop_front(); // удаление из начала
    void pop_back(); // удаление из конца
    
    void insert(int data, int index); // вставка по индексу
    void removeAt(int index); // удаление по индексу
    
    int operator[](const int index); // итератор
    
    void PrintFromHead(); // печать с головы
    void PrintFromTail(); // печать с хвоста
    
    void reverse();
    
    List(); // конструктор
    ~List(); // деструктор
    
private:
    
    class Node // узел в нашем списке
    {
    public:
        Node (int data, Node *pNext = nullptr, Node *pPrev = nullptr) // конструктор
        {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
        
        int data;
        Node *pNext;
        Node *pPrev;
    };
    
    Node *head; // создаем голову
    Node *tail; // создаем хвост
    int Size; //размер
    friend void united(List &a, List &b);
};

List::List() // инициализируем первый объект
{
    head = nullptr;
    tail = nullptr;
    Size = 0;
}

List::~List() // деконструктор
{
    clear();
}


void List::clear()
{
    while (Size)
    {
        pop_front();
    }
}


void List::push_front(int data)
{
    if (Size > 1)
    {
        Node *temp = head; //наша вторая переменная
        head = new Node(data, head); // создаем новый head и передаем туда данные и ссылку на старый
        temp->pPrev = head; // делаем у второго элемента указатель на новый head
    }
    else if (Size == 1)
    {
        head = new Node(data, head); //создаем новый head-элемент
        tail->pPrev = this->head; //у хвоста предыдущий указатель ставим на новый элемент
    }
    else
    {
        head = tail = new Node(data, head, tail);
    }
    Size++;
}


void List::push_back(int data)
{
    if (Size > 1)
    {
        Node *temp = tail; //наша вторая переменная
        tail = new Node(data, nullptr, tail); // создаем новый tail и передаем туда данные и ссылку на старый
        temp->pNext = tail; //делаем у предпоследнего элемента указатель на старый
    }
    else if (Size == 1)
    {
        tail = new Node(data, nullptr, tail); //создаем новый хвост
        head->pNext = this->tail; // у старого хвоста делаем указатель на новый
    }
    else
    {
        head = tail = new Node(data, head, tail);
    }
    Size++;
    

}


void List::pop_front()
{
    if (Size > 1)
    {
        Node *temp = head; // делаем дополнительную переменную с сылкой на голову
        head = head->pNext; // меняем голову
        delete temp; // удаляем предыдущую голову
    }
    else if (Size == 1)
    {
        Node *temp = head;
        tail = head = head->pNext;
        delete temp;
    }
    
    Size--;
}


void List::pop_back()
{
    if (Size > 1)
    {
        Node *temp = tail; // делаем дополнительную переменную с сылкой на хвост
        tail = tail->pPrev; //изменяем хвост
        delete temp; // удалем старый хвост
    }
    else if (Size == 1)
    {
        Node *temp = tail;
        tail = head = tail->pPrev;
        delete temp;
    }
    
    Size--;
}


void List::insert(int data, int index)
{
    if (index == 0) push_front(data);
    
    else if (index == Size || index > Size) push_back(data);

    
    else if (index <= Size / 2) //если ближе голова
    {
        Node *previous = this->head; //создаем узел с адресом головы
        for (int i = 0; i < index - 1; i++) //проходимся от головы до узла, который указывает на нужный нам
        {
            previous = previous->pNext;
        }
        
        Node *newNode = new Node(data, previous->pNext, previous); // создаем новый узел
        
        previous->pNext = newNode; //у предыдущего меняем следующий на наш новый
        Node *next = newNode->pNext; // у нашего + 1 меняем указатель на предыдущий:
        next->pPrev = newNode;
        
        Size++;
    }
    
    else if (index > Size / 2) // если ближе хвост
    {
        Node *next = this->tail;
        for (int i = Size - 1; index < i; i--)
        {
            next = next->pPrev;
        }
        
        Node *newNode = new Node(data, next, next->pPrev);
        
        next->pPrev = newNode;
        Node *previous = newNode->pPrev;
        previous->pNext = newNode;
        
        Size++;
    }
}


void List::removeAt(int index)
{
    if (index == 0) pop_front(); //если голова
    
    else if (index == Size || index > Size) pop_back(); //если хвост

    
    else if (index <= Size / 2) //если ближе голова
    {
        Node *previous = this->head;
        for (int i = 0; i < index - 1; i++) //ихем предыдущий удаляемому
        {
            previous = previous->pNext;
        }
        
        Node *toDelete = previous->pNext; // удаляемый
        previous->pNext = toDelete->pNext; // указываем от предыдущего к следущему
        Node *next = toDelete->pNext;
        delete toDelete;
        next->pPrev = previous;
        
        Size--;
    }
    
    else if (index > Size / 2) // если конец ближе
    {
        Node *next = this->tail;
        for (int i = Size - 1; index < i; i--)
        {
            next = next->pPrev;
        }
        
        Node *toDelete = next->pPrev;
        next->pPrev = toDelete->pPrev;
        Node *previous = toDelete->pPrev;
        delete toDelete;
        previous->pNext = next;
        
        Size--;
    }
}


int List::operator[](const int index)
{
    if (index <= Size / 2) //если конец ближе
    {
        int counter = 0;
        Node *current = this->head;
        
        while (current != nullptr) // проходимся по всем
        {
            if (counter == index) return current->data; // если наш, то возвращаем значение
            current = current->pNext; // если нет, то идем дальше
            counter++;
        }
    }
    else
    {
        int counter = Size - 1;
        Node *current = this->tail;
        
        while (current != nullptr)
        {
            if (counter == index) return current->data;
            current = current-> pPrev;
            counter--;
        }
    }
    return 0;
}


void List::PrintFromHead()
{
    cout << "Come the method PrintFromHead:" << endl;
    Node *print = head; //проходимся по всему
    while (print)
    {
        cout << print->data << endl;
        print = print->pNext;
    }
    cout << endl;
}


void List::PrintFromTail()
{
    cout << "Come the method PrintFromTail:" << endl;
    Node *print = tail;
    while (print)
    {
        cout << print->data << endl;
        print = print->pPrev;
    }
    cout << endl;
}

void List::reverse()
{
    Node* ptr = head;
    while (ptr != 0) {
        Node* tmp = ptr->pNext; // запоминаем указатель на следующий
        ptr->pNext = ptr->pPrev; // указатель на следующий меняем на предыдущий
        ptr->pPrev = tmp; // указатель на предыдущий меняем на следующий
        if (tmp == NULL) { //если дошли до конца, то меняем местами хвост и голову
            tail = head;
            head = ptr;
        }
        ptr = tmp; //делаем то же самое со следующим элементом
        
    }
}

void united(List &a, List &b){ //объединяем голову первого и хвост второго
    b.head->pPrev = a.tail;
    a.tail->pNext = b.head;
    
}


int main()
{
    List lst1;
    
    List lst2;
    
    lst1.push_back(1);
    lst1.push_back(2);
    lst2.push_back(3);
    lst2.push_back(4);
    lst2.push_back(1000);
    united(lst1, lst2);
    lst1.PrintFromHead();
    return 0;
}

