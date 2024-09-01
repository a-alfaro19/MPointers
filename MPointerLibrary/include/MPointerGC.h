#pragma once

#include <condition_variable>
#include <mutex>

#include "DoublyLinkedList.h"

class MPointerGC {
public:
    /**
     * @brief Disable cloning
     */
    MPointerGC(const MPointerGC &) = delete;

    /**
     * @brief Disable assignment
     */
    MPointerGC &operator=(const MPointerGC &) = delete;

    /**
     * @brief Destructor
     */
    ~MPointerGC();

    /**
     * @brief Get the instance of the MPointerGC
     * @return Instance of the MPointerGC
     */
    static MPointerGC* getInstance();

    /**
     * @brief Register a pointer
     * @param pointer Pointer address
     * @return MPointer id
     */
    int registerPointer(void* pointer);

    /**
     * @brief Unregister a pointer
     * @param id MPointer id
     */
    void unregisterPointer(int id);

    /**
     * @brief Increase the reference count of a pointer
     * @param id MPointer id
     */
    void incrementReference(int id);

    /**
     * @brief Stop the MPointerGC
     */
    void stop() noexcept;

    /**
    * @brief Check if the MPointerGC is running
    * @return True if the MPointerGC is running, false otherwise
    */
    [[nodiscard]] bool isRunning() const noexcept;

    /**
     * @brief Get the number of pointers
     * @return Number of pointers
     */
    [[nodiscard]] int getMPointersCount() const noexcept;

private:
   /**
    * MPointer Info
    */
    struct PointerInfo {
        void* pointer;
        int refCount;
        int id;
        bool marked;
    };

    /**
     * @brief Constructor
     */
    MPointerGC();

    /**
     * @brief Run the garbage collection logic
     */
    void collectGarbage();

    /**
     * @brief Mark the used pointers
     */
    void mark();

    /**
     * @brief Sweep the unused pointers
     */
    void sweep();

    /**
     * @brief Search a pointer by id
     * @param id MPointer id
     * @return PointerInfo pointer
     */
    [[nodiscard]] PointerInfo* findByID(int id) ;

    DoublyLinkedList<PointerInfo*> mPointers; // List of pointers
    static std::mutex mutex; // Mutex for the list
    int nextId; // Next id to assign
    bool running; // Flag to stop the GC
    std::condition_variable cv; // Condition variable to stop the GC
    std::thread gcThread; // Thread to run the GC
    static MPointerGC* instance; // Instance of the MPointerGC
};
