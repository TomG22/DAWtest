#pragma once

/**
 * This class is used to store and edit audio data in a queue like fashion
 * Chunks are groups of float values
 * Chunk indices are always relative to the front of the queue
 * @author Tom G
 */

class RingBuffer {
public:
    /**
     * Constructor for the RingBuffer class
     * If no arguments are provided, an empty buffer with a default chunk size of 1048 is created 
     * If a chunk size is provided, an empty buffer with the given chunk size is created
     * If a dataSource and amount of chunks are provided, a new buffer is filled with the given data
     */
    RingBuffer();
    RingBuffer(int chunkSize);
    RingBuffer(float* dataSource, int chunkSize, int chunks);

    /**
     * Returns true if the buffer is empty and false if otherwise
     */
    bool isEmpty();

    /**
     * Returns true if the buffer is full and false if otherwise
     */
    bool isFull();
    
    /**
     * Returns the capacity of the buffer
     */
    int getCapacity();

    /**
     * Returns the minimum capacity of the buffer
     */
    int getMinCapacity();

    /**
     * Returns the maximum capacity of the buffer
     */
    int getMaxCapacity();

    /**
     * Returns the current size of the buffer
     */
    int getSize();

    /**
     * Returns the chunk size of the buffer
     */
    int getChunkSize();

    /**
     * Returns the float located at the given index allocated or not
     */
    float getFloat(int idx);

    /**
     * Returns a pointer to where the data is at the specified chunk index
     * If no arguments are provided, the front is assumed as the chunk index
     * Throws an error if an attempt to set data starting at an undeclared chunk is made
     */
    float* get();
    float* get(int chunkIdx);

    /**
     * Returns a pointer to a duplicate of the specified amount of given data
     * If no arguments are provided, the front is assumed as the chunk index
     * Throws an error if an attempt to set data starting at an undeclared chunk is made
     */
    float* clone(int chunks);
    float* clone(int chunks, int chunkIdx);

    /**
     * Sets the capacity of the buffer
     */
    float* setCapacity(int newCapacity);

    /**
     * Validates the given size argument
     * Returns true if it's valid and false if otherwise
     */
    bool isValidSize(int newSize);

    /**
     * Checks of the current size is valid
     * Throws an exception if it's invalid
     */    
    void checkSize();

    /**
     * Validates the given index argument
     * Returns true if it's valid and false if otherwise
     */
    bool isValidIdx(int idx);

    /**
     * Replaces the amount of chunks given in the buffer with the given data starting from the given index
     * New space will be allocated for in the buffer automatically if needed
     * Makes a new reference to the overriden data and returns a pointer to it
     * If no chunkIdx argument is provided, the front is assumed as the starting chunk index
     * Throws an error if an attempt to set data starting at an undeclared chunk is made
     */
    float* set(float* dataSource, int chunks);
    float* set(float* dataSource, int chunks, int chunkIdx);

    /**
     * Replaces the amount of chunks given in the buffer with the sum of itself and
     * the given starting from the given index
     * New space will be allocated for in the buffer automatically if needed
     * Makes a new reference to the overriden data and returns a pointer to it
     * If no chunkIdx argument is provided, the front is assumed as the starting chunk index
     * Throws an error if an attempt to set data starting at an undeclared chunk is made
     */
    float* add(float* dataSource, int chunks);
    float* add(float* dataSource, int chunks, int chunkIdx);

    /**
     * Replaces the amount of chunks given in the buffer with the average sum of itself and
     * the given data starting from the given index
     * New space will be allocated for in the buffer automatically if needed
     * Makes a new reference to the overriden data and returns a pointer to it
     * If no chunkIdx argument is provided, the front is assumed as the starting chunk index
     * Throws an error if an attempt to set data starting at an undeclared chunk is made
     */
    float* average(float* dataSource, int chunks);
    float* average(float* dataSource, int chunks, int chunkIdx);

    /**
     * Replaces the amount of chunks given in the buffer with the average sum of itself with
     * the given starting from the given index
     * New space will be allocated for in the buffer automatically if needed
     * Makes a new reference to the overriden data and returns a pointer to it
     * If no chunkIdx argument is provided, the front is assumed as the starting chunk index
     * Throws an error if an attempt to set data starting at an undeclared chunk is made
     */
    float* multiply(float* dataSource, int chunks);
    float* multiply(float* dataSource, int chunks, int chunkIdx);

    /**
     * Appends the amount of chunks given to the back of the queue
     */
    void enqueue(float* dataSource, int chunks);

    /**
     * Dequeues the amount of chunks given
     * Makes a new reference to the removed data and returns a pointer to it
     */
    float* dequeue(int chunks);

private:
    int capacity = 4;
    int size = 0;
    int chunkSize = 1048;  // Chunk size is based off 32 bit units

    int front = 0;

    float* data;

    const int minCapacity = 4;
    const int maxCapacity = 65536;

    /**
     * Doubles the buffer's capacity if the buffer is full
     */
    void growCapacity();

    /**
     * Halves the buffer's capacity if the buffer is below 1/4 full
     */
    void shrinkCapacity();
};