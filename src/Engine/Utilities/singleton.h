///////////////////////////////////////////////////////////////////////
//
// Singleton
//
//  Copyright (c) 2013-2015 Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#ifndef THREEENGINE_SINGLETON_H
#define THREEENGINE_SINGLETON_H

#define SINGLETON_HEADER(CLASSNAME)\
    private: static CLASSNAME* _instance; CLASSNAME();\
    public: static CLASSNAME* instance(); virtual ~CLASSNAME(); void cleanup();

#define SINGLETON_IMPLEMENTATION(CLASSNAME)\
    CLASSNAME* CLASSNAME::_instance = nullptr;\
    CLASSNAME* CLASSNAME::instance() {\
        if (_instance == nullptr) { _instance = new CLASSNAME(); }\
        return _instance; }\
    CLASSNAME::CLASSNAME() = default;\
    CLASSNAME::~CLASSNAME() = default;\
    void CLASSNAME::cleanup() { if (_instance != nullptr) { delete _instance; _instance = nullptr; } }

#define SINGLETON_HEADER_ONLY(CLASSNAME)\
    private: static CLASSNAME* _instance; CLASSNAME() = default;\
    public: static CLASSNAME* instance() {\
        if (_instance == nullptr) { _instance = new CLASSNAME(); }\
        return _instance; }\
    virtual ~CLASSNAME() = default;\
    void cleanup() { if (_instance != nullptr) { delete _instance; _instance = nullptr; } }

#define SINGLETON_HEADER_ONLY_AFTERCLASS(CLASSNAME)\
    CLASSNAME* CLASSNAME::_instance = nullptr;
    

#endif // THREEENGINE_SINGLETON_H