#include "MPointerGC.h"
#include <unistd.h>
#include <cstdlib>

using namespace MPOINTER;

pthread_mutex_t MPointerGC::lock;
pthread_cond_t MPointerGC::cond;
MPointerGC* MPointerGC::instance = nullptr;

MPointerGC::~MPointerGC() {
    stop();
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
}

MPointerGC* MPointerGC::getInstance() {
    pthread_mutex_lock(&lock);
    if (instance == nullptr) { // If the instance is null, create a new one
        instance = new MPointerGC();
    }
    pthread_mutex_unlock(&lock);
    return instance;
}

int MPointerGC::registerPointer(void* pointer) {
    pthread_mutex_lock(&lock);
    const int id = nextId++;
    const auto* info = new PointerInfo{pointer, 1, id};
    mPointers.insert(*info);
    pthread_mutex_unlock(&lock);
    return id;
}

void MPointerGC::unregisterPointer(const int id) const {
    pthread_mutex_lock(&lock);
    if (PointerInfo* pointerInfo = mPointers.find(id); pointerInfo->id == id) {
        pointerInfo->refCount--; // Decrement the reference count
        if (pointerInfo->refCount == 0) { // If the reference count is 0, free the memory
            std::free(pointerInfo->pointer);
            pointerInfo->pointer = nullptr;
        }
    }
    pthread_mutex_unlock(&lock);
}

void MPointerGC::incrementReference(const int id) const {
    pthread_mutex_lock(&lock);
    auto* pointerInfo = mPointers.find(id);
    pointerInfo->refCount++;
    pthread_mutex_unlock(&lock);
}

void MPointerGC::stop() noexcept {
    running = false;
    pthread_cond_signal(&cond);
    pthread_join(gcThread, nullptr);
}

bool MPointerGC::isRunning() const noexcept {
    return running;
}

int MPointerGC::getMPointersCount() const noexcept {
    pthread_mutex_unlock(&lock);
    const int count = mPointers.getSize();
    pthread_mutex_unlock(&lock);
    return count;
}

void MPointerGC::clearAllPointers() {
    pthread_mutex_lock(&lock);
    mPointers.clear();
    nextId = 1;
    pthread_mutex_unlock(&lock);
}

void MPointerGC::debug() const {
    pthread_mutex_lock(&lock);
    mPointers.printList();
    pthread_mutex_unlock(&lock);
}

MPointerGC::MPointerGC() : nextId(1), running(true) {
    pthread_mutex_init(&lock, nullptr);
    pthread_cond_init(&cond, nullptr);
    pthread_create(&gcThread, nullptr, &collectGarbage, this);
}

void* MPointerGC::collectGarbage(void* arg) {
    auto* gc = static_cast<MPointerGC*>(arg);
    while (gc->running) {
        pthread_mutex_lock(&MPointerGC::lock);
        gc->mPointers.removeUnusedPointers();
        pthread_mutex_unlock(&MPointerGC::lock);
    }
    return nullptr;
}
