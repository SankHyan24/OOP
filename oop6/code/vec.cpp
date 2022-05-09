#include <vec.hpp>

// Public Functions

/**
 * Function Vector()
 * @brief Construct a new Vec::Vec object without any elements.
 * It is empty.
 * @return Vector<T>
 */
template <class T>
Vector<T>::Vector() : m_pElements(new T[1]), m_nSize(0), m_nCapacity(1)
{
}

/**
 * Function Vector(int size)
 * @brief Construct a new Vec::Vec object with the specified number of elements.
 * It will allocate the required amount of memory. If the class T dont have a
 * default constructor, it will throw error in compile time.
 * @param size The number of elements to be allocated.
 * @return Vector<T>
 */
template <class T>
Vector<T>::Vector(int size) : m_pElements(new T[size]), m_nSize(size), m_nCapacity(size)
{
}

/**
 * Function Vector(const Vector &r)
 * @brief Construct a new Vec::Vec object with the specified number of elements.
 * It will allocate the required amount of memory, with the same value as the
 * specified vector.
 * @param r The vector to copy from.
 * @return Vector<T>
 */
template <class T>
Vector<T>::Vector(const Vector &r) : m_pElements(new T[r.m_nSize]), m_nSize(r.m_nSize), m_nCapacity(r.m_nSize)
{
    for (int i = 0; i < m_nSize; i++)
        m_pElements[i] = r.m_pElements[i];
}

/**
 * Function
 * @brief Destroy the Vec::Vec object.
 * It will deallocate the memory.
 * @return void
 */
template <class T>
Vector<T>::~Vector()
{
    delete[] m_pElements;
}

/**
 * Function operator[]
 * @brief Accesses the specified element without bounds checking.
 * @param index The index of the element to access.
 * @return T& The element at the specified index.
 */
template <class T>
T &Vector<T>::operator[](int index)
{
    return m_pElements[index];
}

/**
 * Function at
 * @brief Accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize.
 * @param index The index of the element to access.
 * @return T& The element at the specified index.
 * @throw std::out_of_rang
 */
template <class T>
T &Vector<T>::at(int index)
{
    if (index < 0 || index >= m_nSize)
        throw std::out_of_range("Index out of range");
    return m_pElements[index];
}

/**
 * Function size
 * @brief Returns the size of the container.
 * @return int The size of the container.
 */
template <class T>
int Vector<T>::size() const
{
    return m_nSize;
}

/**
 * Function push_back
 * @brief Adds an element to the end of the container.
 * @param x The element to add.
 * @return void
 */
template <class T>
void Vector<T>::push_back(const T &x)
{
    if (m_nSize == m_nCapacity)
        inflate();
    m_pElements[m_nSize++] = x;
}

/**
 * Function clear
 * @brief Clears the contents of the container.
 * @return void
 */
template <class T>
void Vector<T>::clear()
{
    m_nSize = 0;
    delete[] m_pElements;
}

/**
 * Function empty
 * @brief Checks whether the container is empty.
 * @return bool True if the container is empty, false otherwise.
 */
template <class T>
bool Vector<T>::empty() const
{
    return m_nSize == 0;
}

// Private functions

/**
 * Function inflate
 * @breif Expands the storage of the container to a new capacity, e.g. 2*m_nCapacity.
 * @return void
 * @throw std::bad_alloc
 */
template <class T>
void Vector<T>::inflate()
{
    T *pNewElements = new T[m_nCapacity * 2];
    if (pNewElements == nullptr)
        throw std::bad_alloc();
    for (int i = 0; i < m_nSize; i++)
        pNewElements[i] = m_pElements[i];
    delete[] m_pElements; // destroy the old storage
    m_pElements = pNewElements;
    m_nCapacity *= 2;
}

// Add your class you want to use in the template here:
template class Vector<int>;
template class Vector<std::string>;
// template class Vector<double>;
// template class Vector<char>;
// template class Vector<bool>;
// template class Vector<float>;
// template class Vector<long long>;