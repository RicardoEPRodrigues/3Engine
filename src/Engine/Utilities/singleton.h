///////////////////////////////////////////////////////////////////////
//
// Singleton
//
//  Copyright (c) 2013-2015 Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#pragma once

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
