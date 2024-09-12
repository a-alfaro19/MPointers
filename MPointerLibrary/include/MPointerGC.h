#pragma once

#include <MPointerList.h>
#include <pthread.h>

namespace MPOINTER {

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
 void unregisterPointer(int id) const;

 /**
  * @brief Increase the reference count of a pointer
  * @param id MPointer id
  */
 void incrementReference(int id) const;

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

 /**
  * @brief Clear all pointers
  */
 void clearAllPointers();

 /**
  * @brief Print the list of pointers
  */
 void debug() const;

private:
 /**
  * @brief Constructor
  */
 MPointerGC();

 /**
  * @brief Run the garbage collection logic
  */
 static void* collectGarbage(void* arg);

 MPointerList mPointers; // List of pointers
 int nextId; // Next id to assign
 bool running; // Flag to stop the GC
 pthread_t gcThread{}; // Thread to run the GC
 static pthread_mutex_t lock; // Mutex for the list
 static pthread_cond_t cond; // Condition variable for the GC
 static MPointerGC* instance; // Instance of the MPointerGC
};

}