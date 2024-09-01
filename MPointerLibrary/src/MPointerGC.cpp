#include "MPointerGC.h"

MPointerGC::~MPointerGC() {
    stop();
    if (gcThread.joinable()) {
        gcThread.join();
    }
}

MPointerGC* MPointerGC::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new MPointerGC();
    }
    return instance;
}

int MPointerGC::registerPointer(void* pointer) {
    std::lock_guard<std::mutex> lock(mutex);
    const int id = nextId++;
    auto* info = new PointerInfo{pointer, 1, id, true};
    mPointers.insert(info);
    return id;
}

void MPointerGC::unregisterPointer(const int id) {
    std::lock_guard<std::mutex> lock(mutex);
    if (PointerInfo* pointerInfo = findByID(id); pointerInfo->id == id) {
        pointerInfo->refCount--;
    }
}

void MPointerGC::incrementReference(const int id) {
    std::lock_guard<std::mutex> lock(mutex);
    auto* pointerInfo = findByID(id);
    pointerInfo->refCount++;
}

void MPointerGC::stop() noexcept {
    std::lock_guard<std::mutex> lock(mutex);
    running = false;
    cv.notify_all();
}

MPointerGC::MPointerGC()
    : nextId(1), running(true), gcThread([this]() { this->collectGarbage(); }) {}

void MPointerGC::mark() const {
    for (const auto& it : mPointers) {
        if (it->refCount > 0) {
            it->marked = true;
        } else {
            it->marked = false;
        }
    }
}

void MPointerGC::sweep() {
    for(auto it = mPointers.begin(); it != mPointers.end();) {
        if (!(*it)->marked) {
            delete static_cast<char*>((*it)->pointer);
            it = mPointers.remove(*it);
        } else {
            ++it;
        }
    }
}

void MPointerGC::collectGarbage() {
    while (running) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait_for(lock, std::chrono::seconds(5), [this]() { return !running; });
        mark();
        sweep();
    }
}

MPointerGC::PointerInfo* MPointerGC::findByID(const int id) {
    for (const auto& it : mPointers) {
        if (it->id == id) {
            return it;
        }
    }
    return nullptr;
}

