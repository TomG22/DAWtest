/**
 * This class is used to store and operate on a particular sound sample
 * which is intended to be divided into chunks for streaming purposes.
 * @author Tom G
 */

#pragma once

class Sound {
private:
    int chunkSize = 1024;
    void* dataSource = 0;
    void* currChunk = 0;
public:
    /**
     * Constructor for sound class
     */
    Sound();

    /**
     * Overrides the given amount of data at the given chunk index
     */
    void setData(void* dataSource, int chunks);
    void setData(void* dataSource, int chunkIdx, int chunks);

    /**
     * Returns a pointer to data at the given chunk index
     */
    void* getData(void* dataSource, int chunks);
    
    /**
     * Queues the next chunk to be read into the streaming system
     */
    bool processNextChunk();
}