#include "../include/RingBuffer.h"
#include <stdio.h>
#include <string>
#include <stdexcept>

static bool assertEquals(float* array, RingBuffer* ringBuffer) {
    int size = ringBuffer->getSize();
    float* bufferData = ringBuffer->get();
    int bufferCapacity = ringBuffer->getCapacity();
    for (int i = 0; i < size; i++) {
        if (array[i] != ringBuffer->getFloat(i)) {
            return false;
        }
    }
    return true;
}

static bool assertEquals(float* array, float* array2, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

static std::string toString(RingBuffer* ringBuffer) {
    int chunkSize = ringBuffer->getChunkSize();
    int size = ringBuffer->getSize();

    std::string strResult = "[";

    // Loop through all of the chunks except the last and print their data separated by a comma
    int i = 0;
    for (i = 0; i < size; i++) {
        if (i != 0) {
            if (i % chunkSize == 0) {
                strResult += "|";
            } else {
                strResult += ", ";
            }
        }

        strResult += std::to_string(ringBuffer->getFloat(i));
    }

    return strResult + ']';
}

static std::string toString(float* data, int chunkSize, int chunks) {
    std::string strResult = "[";

    // Loop through all of the chunks except the last and print their data separated by a comma
    int i = 0;
    for (i = 0; i < chunkSize * chunks; i++) {
        if (i != 0) {
            if (i % chunkSize == 0) {
                strResult += "|";
            } else {
                strResult += ", ";
            }
        }

        strResult += std::to_string(data[i]);
    }

    return strResult + ']';
}

static void testWrapper(std::string testName, float* expectedData, float* actualData, int chunkSize, int chunks) {
    if (assertEquals(expectedData, actualData, chunkSize * chunks)) {
        printf("%s passed\n", testName.c_str());
    } else {
        printf("%s failed\n", testName.c_str());
        printf("expected: %s\nactual: %s\n", toString(expectedData, chunkSize, chunks).c_str(), toString(actualData, chunkSize, chunks).c_str());
    }
}

static void testWrapper(std::string testName, float* expectedData, RingBuffer* ringBuffer, int chunks) {
    if (assertEquals(expectedData, ringBuffer)) {
        printf("%s passed\n", testName.c_str());
    } else {
        printf("%s failed\n", testName.c_str());
        printf("expected: %s\nactual: %s\n", toString(expectedData, ringBuffer->getChunkSize(), chunks).c_str(), toString(ringBuffer).c_str());
    }
}
 
// Chunk size: 1
// Chunks: 4
static void testConstructor1() {
    float testData[] = {0.0000011f, 3.1459f, 0.25252312f, 1.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 1,  4);

    testWrapper(std::string("testConstructor1"), testData, &ringBuffer, 4);
}

// Chunk size: 1
// Chunks: 2
static void testConstructor2() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 2, 2);

    testWrapper(std::string("testConstructor2"), testData, &ringBuffer, 2);
}

// Chunk size: 10
// Chunks: 1
static void testConstructor3() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};

    RingBuffer ringBuffer = RingBuffer(testData, 10, 1);

    testWrapper(std::string("testConstructor3"), testData, &ringBuffer, 1);
}

// Chunk size: 1
// Chunks: 1
static void testConstructor4() {
    float testData[] = {340282346638528859811704183484516925440.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 1, 1);

    testWrapper(std::string("testConstructor4"), testData, &ringBuffer, 1);
}

// Chunk size: 5
// Chunks: 2
static void testGet1() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* getResult = ringBuffer.get();
    
    testWrapper(std::string("testGet1"), testData, getResult, 5, 2);
}

// Chunk size: 5
// Chunks: 2
static void testGet2() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedData[] = {2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* getResult = ringBuffer.get(1);

    testWrapper(std::string("testGet2"), expectedData, getResult, 5, 1);
}

// Chunk size: 5
// Chunks: 2
static void testClone1() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* cloneResult = ringBuffer.clone(2);
    
    testWrapper(std::string("testClone1"), testData, cloneResult, 5, 2);
}

// Chunk size: 5
// Chunks: 2
static void testClone2() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedData[] = {2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* cloneResult = ringBuffer.clone(1, 1);

    testWrapper(std::string("testClone2"), expectedData, cloneResult, 5, 1);
}

// Chunk size: 5
// Chunks: 2
static void testSet1() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float setData[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float expectedData[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* setResult = ringBuffer.set(setData, 1);
    
    testWrapper(std::string("testSet1"), expectedData, &ringBuffer, 2);
    testWrapper(std::string("testSet1Return"), testData, setResult, 5, 1);
}

// Chunk size: 2
// Chunks: 5
static void testSet2() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float setData[] = {4.4f, 5.5f};
    float expectedSetData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 4.4f, 5.5f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedReturnData[] = {0.0f, 2.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 2, 5);
    float* setResult = ringBuffer.set(setData, 1, 2);

    testWrapper(std::string("testSet2"), expectedSetData, &ringBuffer, 5);
    testWrapper(std::string("testSetReturn2"), expectedReturnData, setResult, 2, 1);
}

// Chunk size: 5
// Chunks: 2
static void testAdd1() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float addData[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* addResult = ringBuffer.add(addData, 1);
    
    testWrapper(std::string("testAdd1"), testData, &ringBuffer, 2);
    testWrapper(std::string("testAdd1Return"), testData, addResult, 5, 1);
}

// Chunk size: 2
// Chunks: 5
static void testAdd2() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float addData[] = {4.4f, 5.5f};
    float expectedAddData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 4.4f, 7.5f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedReturnData[] = {0.0f, 2.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 2, 5);
    float* addResult = ringBuffer.add(addData, 1, 2);

    testWrapper(std::string("testAdd2"), expectedAddData, &ringBuffer, 5);
    testWrapper(std::string("testAddReturn2"), expectedReturnData, addResult, 2, 1);
}

// Chunk size: 5
// Chunks: 2
static void testAverage1() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float averageData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* averageResult = ringBuffer.average(averageData, 1);
    
    testWrapper(std::string("testAverage1"), testData, &ringBuffer, 2);
    testWrapper(std::string("testAverage1Return"), testData, averageResult, 5, 1);
}

// Chunk size: 2
// Chunks: 5
static void testAverage2() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float averageData[] = {4.4f, 5.5f};
    float expectedAverageData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 2.2f, 3.75f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedReturnData[] = {0.0f, 2.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 2, 5);
    float* averageResult = ringBuffer.average(averageData, 1, 2);

    testWrapper(std::string("testAverage2"), expectedAverageData, &ringBuffer, 5);
    testWrapper(std::string("testAverageReturn2"), expectedReturnData, averageResult, 2, 1);
}

// Chunk size: 5
// Chunks: 2
static void testMultiply1() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float multiplyData[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 5, 2);
    float* multiplyResult = ringBuffer.multiply(multiplyData, 1);
    
    testWrapper(std::string("testMultiply1"), testData, &ringBuffer, 2);
    testWrapper(std::string("testMultiply1Return"), testData, multiplyResult, 5, 1);
}

// Chunk size: 2
// Chunks: 5
static void testMultiply2() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float multiplyData[] = {4.4f, 5.5f};
    float expectedMultiplyData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 11.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedReturnData[] = {0.0f, 2.0f};

    RingBuffer ringBuffer = RingBuffer(testData, 2, 5);
    float* multiplyResult = ringBuffer.multiply(multiplyData, 1, 2);

    testWrapper(std::string("testMultiply2"), expectedMultiplyData, &ringBuffer, 5);
    testWrapper(std::string("testMultiplyReturn2"), expectedReturnData, multiplyResult, 2, 1);
}

// Chunk size: 2
// Chunks: 5
static void testEnqueue() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float enqueueData[] = {4.4f, 5.5f};
    float expectedEnqueueData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f, 4.4f, 5.5f};

    RingBuffer ringBuffer = RingBuffer(testData, 2, 5);
    ringBuffer.enqueue(enqueueData, 1);
    testWrapper(std::string("testEnqueue"), expectedEnqueueData, &ringBuffer, 6);
}

// Chunk size: 2
// Chunks: 5
static void testDequeue() {
    float testData[] = {0.000001f, 3.1459f, 0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedDequeueData[] = {0.25252312f, 1.0f, 0.0f, 2.0f, 33232.2f, 10.0f, 232.2f, 9999.9999f};
    float expectedReturnData[] = {0.000001f, 3.1459f};

    RingBuffer ringBuffer = RingBuffer(testData, 2, 5);
    float* dequeueResult = ringBuffer.dequeue(1);

    testWrapper(std::string("testDequeue"), expectedDequeueData, &ringBuffer, 4);
    testWrapper(std::string("testDequeueReturn"), expectedReturnData, dequeueResult, 2, 1);
}

static void testGrowCapacity() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer ringBuffer = RingBuffer(sampleData, 1, 4);
    ringBuffer.setCapacity(10);

    if (ringBuffer.getCapacity() == 10) {
        printf("testGrowCapacity passed\n");
    } else {
        printf("testGrowCapacity failed\n");
    }
}

static void testGrowMaxCapacity() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer ringBuffer = RingBuffer(sampleData, 1, 4);
    
    try {
        ringBuffer.setCapacity(ringBuffer.getMaxCapacity() + 1);
    } catch (const std::runtime_error& e) {
        if (ringBuffer.getCapacity() == 4) {
            printf("testGrowMaxCapacity passed and caught the runtime exception: %s\n", e.what());
        } else {
            printf("testGrowMaxCapacity failed\n");
        }
    }

}

static void testShrinkCapacity() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float expectedReturnData[] = {0.0f, 0.0f};

    RingBuffer ringBuffer = RingBuffer(sampleData, 1, 6);
    float* shrinkCapacityResult = ringBuffer.setCapacity(4);

    ringBuffer.setCapacity(4);

    testWrapper(std::string("testShrinkCapacity"), expectedReturnData, shrinkCapacityResult, 1, 2);
}

static void testShrinkMinCapacity() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer ringBuffer = RingBuffer(sampleData, 1, 4);

    try {
        ringBuffer.setCapacity(ringBuffer.getMinCapacity() - 1);
    } catch (const std::runtime_error& e) {
        if (ringBuffer.getCapacity() == 4) {
            printf("testShrinkMinCapacity passed and caught the runtime exception: %s\n", e.what());
        } else {
            printf("testShrinkMinCapacity failed\n");
        }
    }
}

static void testEnqueueWhenFull() {
    float enqueueChunk[] = {1.0f};

    RingBuffer ringBuffer = RingBuffer(1);

    int i = 0;
    while (i <= ringBuffer.getMaxCapacity()) {
        try {
            ringBuffer.enqueue(enqueueChunk, 1);
        } catch (const std::runtime_error& e) {
             if (ringBuffer.getSize() == ringBuffer.getMaxCapacity() && ringBuffer.getCapacity() == ringBuffer.getMaxCapacity()) {
                printf("testEnqueueWhenFull passed and caught the runtime exception: %s\n", e.what());
            } else {
                printf("testEnqueueWhenFull failed\n");
            }
        }
        i++;
    }
}

static void testDequeueWhenEmpty() {
    RingBuffer ringBuffer = RingBuffer(1);

    try {
        ringBuffer.dequeue(1);
    } catch (const std::runtime_error& e) {
         if (ringBuffer.getSize() == 0 && ringBuffer.getCapacity() == 4) {
            printf("testDequeueWhenEmpty passed and caught the runtime exception: %s\n", e.what());
        } else {
            printf("testDequeueWhenEmpty failed\n");
        }
    }
}

static void testGetInvalidIdx() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer emptyRingBuffer = RingBuffer(1);
    RingBuffer oneChunkRingBuffer = RingBuffer(sampleData, 1, 1);

    try {
        oneChunkRingBuffer.get(-1);
    } catch (const std::runtime_error& e) {
        printf("testGetInvalidIdx passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        emptyRingBuffer.get(0);
    } catch (const std::runtime_error& e) {
        printf("testGetInvalidIdx2 passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        oneChunkRingBuffer.get(1);
    } catch (const std::runtime_error& e) {
        printf("testGetInvalidIdx3 passed and caught the runtime exception: %s\n", e.what());
    }
}

static void testCloneInvalidIdx() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer emptyRingBuffer = RingBuffer(1);
    RingBuffer oneChunkRingBuffer = RingBuffer(sampleData, 1, 1);

    try {
        oneChunkRingBuffer.clone(1, -1);
    } catch (const std::runtime_error& e) {
        printf("testCloneInvalidIdx passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        emptyRingBuffer.clone(1);
    } catch (const std::runtime_error& e) {
        printf("testCloneInvalidIdx2 passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        oneChunkRingBuffer.clone(1, 1);
    } catch (const std::runtime_error& e) {
        printf("testCloneInvalidIdx3 passed and caught the runtime exception: %s\n", e.what());
    }
}

static void testSetInvalidIdx() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer emptyRingBuffer = RingBuffer(1);
    RingBuffer oneChunkRingBuffer = RingBuffer(sampleData, 1, 1);

    try {
        oneChunkRingBuffer.set(sampleData, 1, -1);
    } catch (const std::runtime_error& e) {
        printf("testSetInvalidIdx passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        emptyRingBuffer.set(sampleData, 1);
    } catch (const std::runtime_error& e) {
        printf("testSetInvalidIdx2 passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        oneChunkRingBuffer.set(sampleData, 1, 1);
    } catch (const std::runtime_error& e) {
        printf("testSetInvalidIdx3 passed and caught the runtime exception: %s\n", e.what());
    }
}

static void testAddInvalidIdx() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer emptyRingBuffer = RingBuffer(1);
    RingBuffer oneChunkRingBuffer = RingBuffer(sampleData, 1, 1);

    try {
        oneChunkRingBuffer.add(sampleData, 1, -1);
    } catch (const std::runtime_error& e) {
        printf("testAddInvalidIdx passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        emptyRingBuffer.add(sampleData, 1);
    } catch (const std::runtime_error& e) {
        printf("testAddInvalidIdx2 passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        oneChunkRingBuffer.add(sampleData, 1, 1);
    } catch (const std::runtime_error& e) {
        printf("testAddInvalidIdx3 passed and caught the runtime exception: %s\n", e.what());
    }
}

static void testAverageInvalidIdx() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer emptyRingBuffer = RingBuffer(1);
    RingBuffer oneChunkRingBuffer = RingBuffer(sampleData, 1, 1);

    try {
        oneChunkRingBuffer.average(sampleData, 1, -1);
    } catch (const std::runtime_error& e) {
        printf("testAverageInvalidIdx passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        emptyRingBuffer.average(sampleData, 1);
    } catch (const std::runtime_error& e) {
        printf("testAverageInvalidIdx2 passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        oneChunkRingBuffer.average(sampleData, 1, 1);
    } catch (const std::runtime_error& e) {
        printf("testAverageInvalidIdx3 passed and caught the runtime exception: %s\n", e.what());
    }
}

static void testMultiplyInvalidIdx() {
    float sampleData[] = {0.0f, 0.0f, 0.0f, 0.0f};

    RingBuffer emptyRingBuffer = RingBuffer(1);
    RingBuffer oneChunkRingBuffer = RingBuffer(sampleData, 1, 1);

    try {
        oneChunkRingBuffer.multiply(sampleData, 1, -1);
    } catch (const std::runtime_error& e) {
        printf("testMultiplyInvalidIdx passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        emptyRingBuffer.multiply(sampleData, 1);
    } catch (const std::runtime_error& e) {
        printf("testMultiplyInvalidIdx2 passed and caught the runtime exception: %s\n", e.what());
    }

    try {
        oneChunkRingBuffer.multiply(sampleData, 1, 1);
    } catch (const std::runtime_error& e) {
        printf("testMultiplyInvalidIdx3 passed and caught the runtime exception: %s\n", e.what());
    }
}

int main() {
    testConstructor1();
    testConstructor2();
    testConstructor3();
    testConstructor4();

    testGet1();
    testGet2();

    testClone1();
    testClone2();

    testSet1();
    testSet2();

    testAdd1();
    testAdd2();

    testAverage1();
    testAverage2();

    testMultiply1();
    testMultiply2();

    testEnqueue();
    testDequeue();

    testGrowCapacity();
    testShrinkCapacity();

    testGrowMaxCapacity();
    testShrinkMinCapacity();

    testEnqueueWhenFull();
    testDequeueWhenEmpty();

    testGetInvalidIdx();
    testCloneInvalidIdx();
    testSetInvalidIdx();
    testAddInvalidIdx();
    testAverageInvalidIdx();
    testMultiplyInvalidIdx();

    return 0;
}
