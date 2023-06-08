#pragma once
using namespace std;


template <typename TKey, typename TValue>

class HashNode {
public:
    TValue value;
    TKey key;

    HashNode(TKey key, TValue value)
    {
        this->value = value;
        this->key = key;
    }
};

template <typename TKey, typename TValue>


class OpenHash {


    HashNode<TKey, TValue>** table;
    int capacity;
    int size;
    HashNode<TKey, TValue>* fict;

public:
    OpenHash()
    {
        capacity = 20;
        size = 0;
        table = new HashNode<TKey, TValue>* [capacity];


        for (int i = 0; i < capacity; i++)
            table[i] = NULL;


        fict = new HashNode<TKey, TValue>(-1, -1);
    }

    int hashFunc(TKey key)
    {
        return key % capacity;
    }


    void insert(TKey key, TValue value)
    {
        HashNode<TKey, TValue>* temp = new HashNode<TKey, TValue>(key, value);


        int ind = hashFunc(key);

        while (table[ind] != NULL && table[ind]->key != key && table[ind]->key != -1) {
            ind++;
            ind %= capacity;
        }

        if (table[ind] == NULL || table[ind]->key == -1)
            size++;
        table[ind] = temp;
    }

    TValue del(int key)
    {
        int ind = hashFunc(key);

        while (table[ind] != NULL) {

            if (table[ind]->key == key) {
                HashNode<TKey, TValue>* temp = table[ind];


                table[ind] = fict;

                size--;
                return temp->value;
            }
            ind++;
            ind %= capacity;
        }

        return NULL;
    }


    TValue get(int key)
    {

        int ind = hashFunc(key);
        int counter = 0;

        while (table[ind] != NULL) { 

            if (counter++ > capacity)
                return NULL;


            if (table[ind]->key == key)
                return table[ind]->value;
            ind++;
            ind %= capacity;
        }


        return NULL;
    }


    int getSize()
    {
        return size;
    }


    bool isEmpty()
    {
        return size == 0;
    }

    void display()
    {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != NULL && table[i]->key != -1)
                cout << "key = " << table[i]->key
                << "  value = "
                << table[i]->value << endl;
        }
    }
};