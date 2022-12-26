#ifndef LinkedList_H
#define LinkedList_H

// Класс, представляющий собой двусвязный список
template <class T>
class List
{
    // Структура, описывающая узел списка
    struct Node
    {
        // Указатель на следующий элемент
        Node *prev = nullptr;
        // Указатель на предыдущий элемент
        Node *next = nullptr;
        // Содержимое узла
        T data;
    };

    // Переменная, хранящая размер списка
    int m_size;
    // Указатель на первый фиктивный узел списка
    Node *first_node;
    // Указатель на последний фиктивный узел списка
    Node *last_node;

public:
    // Базовый конструктор, создающий список нулевой длины
    List()
    {
        // Задаем размер равный нулю
        m_size = 0;
        // Создаем первый фиктивный узел
        first_node = new Node();
        // Создаем последний фиктивный узел
        last_node = new Node();
        // Связываем их между собой
        first_node->next = last_node;
        last_node->prev = first_node;
    }

    // Подпрограмма, возвращающая размер списка
    int size()
    {
        return m_size;
    }

    // Подпрограмма, добавляющая узел с заданным содержимым в конец списка
    void push_back(T value)
    {
        // Увеличиваем размер списка на один
        m_size++;
        // Создаем новый узел
        Node *temp = new Node();
        // Устанавливаем его содержимое на заданное
        temp->data = value;
        // Связываем узел с последним фиктивным узлом списка
        temp->next = last_node;
        temp->prev = last_node->prev;
        // Связываем узел с предпоследним узлом списка
        last_node->prev->next = temp;
        last_node->prev = temp;
        // При этом разрывается связь между последним и предпоследним узлами
    }

    // Подпрограмма, добавляющая узел с заданным содержимым в начало списка
    void push_front(T value)
    {
        // Увеличиваем размер списка на один
        m_size++;
        // Создаем новый узел
        Node *temp = new Node();
        // Устанавливаем его содержимое на заданное
        temp->data = value;
        // Связываем узел с первым фиктивным узлом списка
        temp->prev = first_node;
        temp->next = first_node->next;
        // Связываем узел со вторым узлом списка
        first_node->next->prev = temp;
        first_node->next = temp;
        // При этом разрывается связь между первым и вторым узлами
    }

    // Подпрограмма, выдающая содержимое первого действительного узла (второго)
    T front()
    {
        // Если размер списка равен нулю, выдаем значение по умолчанию
        if (m_size == 0)
            return T();
        return first_node->next->data;
    }

    // Подпрограмма, выдающая содержимое последнего действительного узла (предпоследнего)
    T back()
    {
        // Если размер списка равен нулю, выдаем значение по умолчанию
        if (m_size == 0)
            return T();
        return last_node->prev->data;
    }

    // Подпрограмма, работающая аналогично front
    // Дополнительно удаляет узел, с выданным содержимым
    T pop_front()
    {
        // Если размер списка равен нулю, выдаем значение по умолчанию
        if (m_size == 0)
            return T();
        // Уменьшаем размер списка на один
        m_size--;
        // Получаем узел и его содержимое
        Node *curr = first_node->next;
        T value = curr->data;
        // Производим удаление узла из списка
        first_node->next = curr->next;
        curr->next->prev = first_node;
        delete curr;

        return value;
    }

    // Подпрограмма, работающая аналогично back
    // Дополнительно удаляет узел, с выданным содержимым
    T pop_back()
    {
        // Если размер списка равен нулю, выдаем значение по умолчанию
        if (m_size == 0)
            return T();
        // Уменьшаем размер списка на один
        m_size--;
        // Получаем узел и его содержимое
        Node *curr = last_node->prev;
        T value = curr->data;
        // Производим удаление узла из списка
        last_node->prev = curr->prev;
        curr->prev->next = last_node;
        delete curr;

        return value;
    }

    // Подпрограмма, которая выдает узел, расположенный на заданной позиции
    Node *get_node(int pos)
    {
        // Выбирается с какой стороны (начало или конец) ближе до целевого узла
        // И осуществляется проход по узлам до заданного
        Node *temp;
        if (pos > (m_size - 1) / 2)
        {
            temp = last_node->prev;
            for (int i = m_size - 1; i != pos; i--)
                temp = temp->prev;
        }
        else
        {
            temp = first_node->next;
            for (int i = 0; i != pos; i++)
                temp = temp->next;
        }
        return temp;
    }

    // Подпрограмма, меняющая местами два узла, вызывается из пользовательского кода
    void Swap(int first, int second)
    {
        // Получаем первый узел
        Node *f_node = get_node(first);
        // Получаем второй узел
        Node *s_node = get_node(second);
        // Осуществляем перестановку
        Swap(f_node, s_node);
    }
    // Подпрограмма, выполняющая сортировку списка
    void Sort()
    {
        // Если размер списка меньше, либо равен одному,
        // то сортировка не требуется
        if (m_size <= 1)
            return;
        // Показывает выполнялись ли перестановки
        bool isSwapped = false;

        // Цикл выполняется до тех пор, пока выполнилась хотя бы одна перестановка,
        // т.е. список еще не отсортирован
        do
        {
            // В цикле последовательно сравниваются два соседних элемента
            for (Node temp1 = first_node->next; temp1->next != last_node;)
            {
                // Если первый больше второго, то они меняются местами
                if (temp1->data > temp1->next->data)
                {
                    isSwapped = true;
                    Swap(temp1, temp1->next);
                    temp1 = temp1->prev;
                }
            }
        } while (isSwapped)
    }

private:
    // Подпрограмма, меняющая местами два узла, вызывается самим классом
    void Swap(Node *f_node, Node *s_node)
    {
        // Если узлы равны друг другу, замена не требуется
        if (f_node == s_node)
            return;
        // Временный указатель на узел
        Node *temp;
        // Переустанавливаем связи с предыдущими элементами
        temp = f_node->prev;
        f_node->prev = s_node->prev;
        f_node->prev->next = f_node;
        s_node->prev = temp;
        s_node->prev->next = s_node;
        // Переустанавливаем связи с последующими элементами
        temp = f_node->next;
        f_node->next = s_node->next;
        f_node->next->prev = f_node;
        s_node->next = temp;
        s_node->next->prev = s_node;
    }
};

#endif