#pragma once

#include <MPointerGC.h>
#include <cstdlib>
#include <stdexcept>
#include <typeinfo>
#include <iostream>

namespace MPOINTER {

template <typename T>
class MPointer {
public:
    /**
     * @brief Create a new MPointer
     * @return MPointer
     */
    static MPointer New() {
        T* memory = static_cast<T*>(std::malloc(sizeof(T)));
        int newId = gc()->registerPointer(memory);

        return MPointer(memory, newId);
    }

    /**
     * @brief Default constructor
     */
    MPointer(std::nullptr_t) {
        pointer = nullptr;
        id = -1;
    }

    /**
     * @brief Destructor
     */
    ~MPointer() {
        if (id != -1) {
            gc()->unregisterPointer(id);
        }
    }

    /**
     * @brief Overload the * operator
     * @return T& value
     */
    T& operator*() noexcept {
        if (!pointer) {
            throw std::runtime_error("Accessing a nullptr MPointer");
        }
        return *pointer;
    }

    /**
     * @brief Overload the -> operator
     * @return T* pointer
     */
    T* operator->() {
        return pointer;
    }

    /**
     * @brief Overload the = operator for a full copy
     * @param other MPointer
     * @return MPointer with the assigned value
     */
    MPointer& operator=(const MPointer& other) noexcept {
        if (this != &other) {
            if (!other.isNull()) {
                if (pointer != nullptr) {
                    gc()->unregisterPointer(this->id);
                }

                pointer = other.pointer;
                id = other.id;

                gc()->incrementReference(other.id);
            } else {
                if (pointer != nullptr) {
                    gc()->unregisterPointer(id);
                    pointer = nullptr;
                    id = -1;
                }
            }
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
            if (pointer == nullptr) {
                allocate();
            }
            *pointer = value;
        }

        return *this;
    }

    /**
     * @brief Overload the = operator for a nullptr
     * @return Null MPointer
     */
    MPointer& operator=(std::nullptr_t) noexcept {
        if (pointer != nullptr) {
            gc()->unregisterPointer(id);
            pointer = nullptr;
            id = -1;
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

    /**
     * @brief Allocate memory for a null MPointer
     */
    void allocate() {
        if (pointer == nullptr) {
            pointer = static_cast<T*>(std::malloc(sizeof(T)));
            id = gc()->registerPointer(pointer);
        }
    }

    /**
     * @brief Check if the MPointer is null
     * @return True if the MPointer is null, false otherwise
     */
    [[nodiscard]] bool isNull() const noexcept {
        return pointer == nullptr;
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
    static MPointerGC* gc() {
        return MPointerGC::getInstance();
    }

    int id; // MPointer id
    T* pointer; // Pointer to the memory
};

}