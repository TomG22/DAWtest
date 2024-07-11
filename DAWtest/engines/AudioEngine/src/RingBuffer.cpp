#include "RingBuffer.h"
#include <stdexcept>

RingBuffer::RingBuffer() {
    RingBuffer(1048);
}

RingBuffer::RingBuffer(int chunkSize) {
    this->chunkSize = chunkSize;
    data = new float[capacity];
}

RingBuffer::RingBuffer(float* dataSource, int chunkSize, int chunks) {
    this->chunkSize = chunkSize;
    size = chunkSize * chunks;
    capacity = size;
    data = new float[capacity];

    for (int i = 0; i < size; i++) {
        data[i] = dataSource[i];
    }
}

void RingBuffer::checkSize() {
    if (!isValidSize(size)) {
        throw std::runtime_error("Buffer ERROR: Invalid resize");
    }
}

bool RingBuffer::isValidSize(int newSize) {
    return newSize >= 0 && newSize <= capacity;
}

bool RingBuffer::isValidIdx(int idx) {
    return idx >= 0 && idx < size && size != 0;
}

void RingBuffer::growCapacity() {
    if (isFull()) {
        if (capacity * 2 >= maxCapacity) {
            setCapacity(maxCapacity);
        } else if (capacity * 2 < maxCapacity) {
            setCapacity(capacity * 2);
        }
        checkSize();
    }
}

void RingBuffer::shrinkCapacity() {
    if (size < capacity/4) {
        if (capacity / 2 <= minCapacity) {
            setCapacity(minCapacity);
        } else if (capacity / 2 > minCapacity) {
            setCapacity(capacity / 2);
        }
    }
    checkSize();
}

bool RingBuffer::isEmpty() {
    return size == 0;
}

bool RingBuffer::isFull() {
    return size >= capacity;
}

int RingBuffer::getCapacity() {
    return capacity;
}

int RingBuffer::getMinCapacity() {
    return minCapacity;
}

int RingBuffer::getMaxCapacity() {
    return maxCapacity;
}

int RingBuffer::getSize() {
    return size;
}

int RingBuffer::getChunkSize() {
    return chunkSize;
}

float RingBuffer::getFloat(int idx) {
    if (isValidIdx(idx)) {
        return data[front + idx % capacity];
    } else {
        throw std::runtime_error("Buffer ERROR: Tried to get data at an invalid index");
        return 0;
    }
}

float* RingBuffer::get() {
    return get(0);
}

float* RingBuffer::get(int chunkIdx) {
    if (isValidIdx(chunkIdx * chunkSize)) {
        return &data[front + (chunkIdx * chunkSize) % capacity];
    } else {
        throw std::runtime_error("Buffer ERROR: Tried to get data at an invalid index");
        return 0;
    }
}

float* RingBuffer::clone(int chunks) {
    return clone(chunks, 0);
}

float* RingBuffer::clone(int chunks, int chunkIdx) {
    float* cloneData = new float[chunkSize * chunks];

    if (isValidIdx(chunkIdx * chunkSize)) {
        for (int i = 0; i < chunkSize * chunks && i < capacity; i++) {
            cloneData[i] = data[front + (chunkIdx * chunkSize) + i % capacity];
        }
        return cloneData;
    } else {
        throw std::runtime_error("Buffer ERROR: Tried to clone data at an invalid index");
        return 0;
    }
}

float* RingBuffer::setCapacity(int newCapacity) {
    if (newCapacity == capacity) {
        return 0;
    } else if (newCapacity < minCapacity) {
        throw std::runtime_error("Buffer ERROR: Tried to set capacity below the minimum bound");
        return 0;
    } else if (newCapacity > maxCapacity) {
        throw std::runtime_error("Buffer ERROR: Tried to set capacity above the maximum bound");
        return 0;
    }

    float* newData = new float[newCapacity];

    for (int i = 0; i < size; i++) {
        newData[i] = data[front + i % capacity];
    }
    
    float* truncatedData = 0;

    // Copy any extra data into a truncatedData array
    if (newCapacity < size) {
        truncatedData = new float[size - newCapacity];
        for (int i = 0; i < size - newCapacity; i++) {
            truncatedData[i] = data[front + newCapacity + i % capacity];
        }

        size = newCapacity;
    }

    delete[] data;  // Deallocate the old array's memory
    data = newData;
    front = 0;
    capacity = newCapacity;

    return truncatedData;
}

float* RingBuffer::set(float* dataSource, int chunks) {
    return set(dataSource, chunks, 0);
}

float* RingBuffer::set(float* dataSource, int chunks, int chunkIdx) {
    if (isValidIdx(chunkIdx * chunkSize)) {
        float* oldData = new float[chunkSize * chunks];

        for (int i = 0; i < chunkSize * chunks && i < capacity; i++) {
            oldData[i] = data[front + (chunkIdx * chunkSize) + i % capacity];
            data[front + (chunkIdx * chunkSize) + i % capacity] = dataSource[i];
        }
        return oldData;
    } else {
        throw std::runtime_error("Buffer ERROR: Tried to set data at an invalid index");
        return 0;
    }
}

float* RingBuffer::add(float* dataSource, int chunks) {
    return add(dataSource, chunks, 0);
}

float* RingBuffer::add(float* dataSource, int chunks, int chunkIdx) {
    if (isValidIdx(chunkIdx * chunkSize)) {
        float* oldData = new float[chunkSize * chunks];

        for (int i = 0; i < chunkSize * chunks && i < capacity; i++) {
            oldData[i] = data[front + (chunkIdx * chunkSize) + i % capacity];
            data[front + (chunkIdx * chunkSize) + i % capacity] = data[front + (chunkIdx * chunkSize) + i % capacity] + dataSource[i];
        }
        return oldData;
    } else {
        throw std::runtime_error("Buffer ERROR: Tried to add to data at an invalid index");
        return 0;
    }
}

float* RingBuffer::average(float* dataSource, int chunks) {
    return average(dataSource, chunks, 0);
}

float* RingBuffer::average(float* dataSource, int chunks, int chunkIdx) {
    if (isValidIdx(chunkIdx * chunkSize)) {
        float* oldData = new float[chunkSize * chunks];

        for (int i = 0; i < chunkSize * chunks && i < capacity; i++) {
            oldData[i] = data[front + (chunkIdx * chunkSize) + i % capacity];
            data[front + (chunkIdx * chunkSize) + i % capacity] = (data[front + (chunkIdx * chunkSize) + i % capacity] + dataSource[i])/2;
        }
        return oldData;
    } else {
        throw std::runtime_error("Buffer ERROR: Tried to apply an average on data at an invalid index");
        return 0;
    }
}

float* RingBuffer::multiply(float* dataSource, int chunks) {
    return multiply(dataSource, chunks, 0);
}

float* RingBuffer::multiply(float* dataSource, int chunks, int chunkIdx) {
    if (isValidIdx(chunkIdx * chunkSize)) {
        float* oldData = new float[chunkSize * chunks];

        for (int i = 0; i < chunkSize * chunks && i < capacity; i++) {
            oldData[i] = data[front + (chunkIdx * chunkSize) + i % capacity];
            data[front + (chunkIdx * chunkSize) + i % capacity] = data[front + (chunkIdx * chunkSize) + i % capacity] * dataSource[i];
        }
        return oldData;
    } else {
        throw std::runtime_error("Buffer ERROR: Tried to multiply data at an invalid index");
        return 0;
    }
}

void RingBuffer::enqueue(float* dataSource, int chunks) {
    if (size + chunkSize * chunks > maxCapacity) {
        throw std::runtime_error("Buffer ERROR: Can't enqueue more chunks than the max capacity");
    }

    int oldSize = size;
    size += chunkSize * chunks;
    growCapacity();

    for (int i = 0; i < chunkSize * chunks; i++) {
        data[front + oldSize + i % capacity] = dataSource[i];
    }
}

float* RingBuffer::dequeue(int chunks) {
    if (size - chunkSize * chunks <= 0) {
        throw std::runtime_error("Buffer ERROR: Can't dequeue more chunks than what's available");
    }

    float* dequeuedData = new float[chunkSize * chunks];

    for (int i = 0; i < chunkSize * chunks; i++) {
        dequeuedData[i] = data[front + i % capacity];
    }
    
    front = front + chunkSize * chunks % capacity;
    size -= chunkSize * chunks;
    shrinkCapacity();

    return dequeuedData;
}
