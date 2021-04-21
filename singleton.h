#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdint>

//class implementation by Martin York
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class singleton
{
public:
    static singleton& getInstance()
    {
        static singleton instance;  // Guaranteed to be destroyed.
                                    // Instantiated on first use.
        return instance;
    }

    void setDirty(bool dirty);
    void setOp(uint8_t op);
    void setData(int pos, uint16_t data);


    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.

    singleton(singleton const&) = delete;
    void operator=(singleton const&)  = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status

private:
    singleton() {}                    // Constructor? (the {} brackets) are needed here.

    bool dirtyBit = false;
    uint8_t opcode;
    uint16_t data1;
    uint16_t data2;
    uint16_t data3;
    uint16_t data4;
};

#endif // SINGLETON_H
