/**
 * This class is used to store and edit audio data in a queue like fashion.
 * @author Tom G
 */

#pragma once

class RingBuffer {
private:
    int size = 0;
    int capacity = 1048576;
    int chunkSize = 1024;
    
    int front = 0;
    int back = 0;

    /**
     * Doubles the size of the buffer's capacity if the buffer is full
     */
    void growCapacity();

    /**
     * Halves the size of the buffer's capacity if the buffer is below 1/4 full
     */
    void shrinkCapacity();
public:
    /**
     * Constructor for the ring buffer class
     * If no arguments are provided, an empty buffer is created
     * If a dataSource and amount of chunks are provided, a new buffer is filled with the given data
     */
    RingBuffer();
    RingBuffer(void* dataSource, int chunks);

    /**
     * Returns true if the buffer is empty and false if otherwise
     */
    bool isEmpty();

    /**
     * Returns true if the buffer is full and false if otherwise
     */
    bool isFull();
    
    /**
     * Returns a pointer to where the data is at the specified chunk index
     * If no arguments are provided, 0 is assumed as the chunk index
     */
    void* get();
    void* get(int chunkIdx);
    
    /**
     * Overrides the amount of chunks given in the buffer starting from the given index
     * Makes a new reference to the overriden data and returns a pointer to it
     * If no chunkIdx argument is provided, 0 is assumed as the starting chunk index
     */
    void* set(void* dataSource, int chunks);
    void* set(void* dataSource, int chunkIdx, int chunks);
    
    /**
     * Removes the amount of chunks given in the buffer starting from the given index
     * Makes a new reference to the removed data and returns a pointer to it
     * If no chunkIdx argument is provided, 0 is assumed as the starting chunk index
     */
    void* remove(int chunks);
    void* remove(int chunkIdx, int chunks);

    /**
     * Appends the amount of chunks given to the back of the queue
     */
    void enqueue(void* dataSource, int chunks);

    /**
     * Dequeues the amount of chunks given
     * Makes a new reference to the removed data and returns a pointer to it
     */
    void* dequeue(int chunks);
};