#pragma once

#include <MPointerGC.h>

template <typename T>
class MPointer {
public:
    /**
     * @brief Create a new MPointer
     * @return MPointer
     */
    MPointer New() {
        T* memory = new T();
        int newId = gc().registerPointer(memory);

        return MPointer(memory, newId);
    }

    /**
     * @brief Destructor
     */
    ~MPointer() {
        gc().unregisterPointer(id);
    }

    /**
     * @brief Overload the * operator
     * @return T& value
     */
    T& operator*() noexcept {
        return *pointer;
    }

    /**
     * @brief Overload the & operator
     * @return T value
     */
    T operator&() noexcept {
        return *pointer;
    }

    /**
     * @brief Overload the = operator
     * @param other MPointer
     * @return MPointer with the assigned value
     */
    MPointer& operator=(const MPointer& other) noexcept {
        if (this != &other) {
            *pointer = *other.pointer;
            id = other.id;
            gc().incrementReference(id);
        }

        return *this;
    }

    /**
     * @brief Overload the = operator
     * @param value Value to assign
     * @return MPointer with the assigned value
     */
    MPointer& operator=(const T& value) noexcept {
        if (typeid(value).name() == typeid(*pointer).name()) {
            *pointer = value;
        }

        return *this;
    }

    /**
     * @brief Overload the == operator
     * @param other MPointer
     * @return True if the MPointers are equal, false otherwise
     */
    bool operator==(const MPointer& other) const noexcept {
        return id == other.id;
    }

private:
    /**
     * @brief Create a new MPointer
     * @return MPointer
     */
    MPointer(T* pointer, const int id) noexcept: id(id), pointer(pointer) {}

    /**
     * @brief Get the MPointerGC instance
     * @return MPointerGC instance
     */
    static MPointerGC *gc() {
        return MPointerGC::getInstance();
    }

    int id; // MPointer id
    T* pointer; // Pointer to the memory
};
