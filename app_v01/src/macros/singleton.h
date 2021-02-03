#pragma once

#define SINGLETON(name)             \
    private:                        \
        name() { init(); }          \
    public:                         \
        name(const name&) = delete; \
        static name& getInstance()  \
        {                           \
            static name instance;   \
            return instance;        \
        }
