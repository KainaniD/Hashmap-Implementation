#ifndef MAP_INCLUDED
#define MAP_INCLUDED

// Later in the course, we'll see that templates provide a much nicer
// way of enabling us to have Maps of different types.  For now, we'll
// use type aliases.

#include <string>

using KeyType = std::string;
using ValueType = double;



class Map
{
public:
    Map();         // Create an empty map (i.e., one whose size() is 0).

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).

    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; in this case, return true.
    // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; in this case, return true.
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).

    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.

    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.

    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map which the key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.

    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of the key/value pair in the map whose key is strictly
    // greater than exactly i keys in the map and return true.  Otherwise,
    // leave the key and value parameters unchanged and return false.

    void swap(Map& other);
    // Exchange the contents of this map with the other one.

    //Destructor
    ~Map();

    //Copy constructor
    Map(const Map& src);


    //Assignment operator
    Map& operator=(const Map& src);


private:


    // Since this structure is used only by the implementation of the
    // Map class, we'll make it private to Map.

    struct Node
    {
        Node* previousNode;
        KeyType   m_key;
        ValueType m_value;
        Node* nextNode;
    };            
    Node* headPtr;
    Node* tailPtr;

    int  m_size;                     // number of pairs in the map


     // At any time, the elements of m_data indexed from 0 to m_size-1
     // are in use and are stored in ascending order of the keys.

    bool findItem(const KeyType& key) const;
    void addToFront(const KeyType& key, const ValueType& value);
    void addToRear(const KeyType& key, const ValueType& value);
    void insertInOrder(const KeyType& key, const ValueType& value);
    ValueType getValueFromKey(const KeyType& key) const;
    bool doInsertOrUpdate(const KeyType& key, const ValueType& value, bool mayInsert, bool mayUpdate);
    // If the key is not present in the map and if mayInsert is true, insert
    // the pair if there is room.  If the key is present and mayUpdate is
    // true, update the pair with the given key.    
};

// Inline implementations

bool merge(const Map& m1, const Map& m2, Map& result);

void reassign(const Map& m, Map& result);

inline
int Map::size() const
{
    return m_size;
}

inline
bool Map::empty() const
{
    return size() == 0;
}

inline
bool Map::contains(const KeyType& key) const
{
    return findItem(key);
}

inline
bool Map::insert(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, false /* no update */);
}

inline
bool Map::update(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, false /* no insert */, true /* update */);
}

inline
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, true /* update */);
}

#endif // MAP_INCLUDED
