#pragma once

#ifdef _DEBUG
#define DISABLE_COPY_AND_MOVE(ClassName) \
    ClassName(const ClassName&) = delete; \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(const ClassName&) = delete; \
    ClassName& operator=(ClassName&&) = delete; 
#else
#define DISABLE_COPY_AND_MOVE(ClassName)
#endif

#ifdef _DEBUG
#define DISABLE_ASSIGN_AND_MOVE(ClassName) \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(const ClassName&) = delete; \
    ClassName& operator=(ClassName&&) = delete; 
#else
#define DISABLE_ASSIGN_AND_MOVE(ClassName)
#endif

#ifdef _DEBUG
#define DISABLE_MOVE(ClassName) \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete; 
#else
#define DISABLE_ASSIGN_AND_MOVE(ClassName)
#endif

#ifdef _DEBUG
#define DISABLE_ALL_CONSTRUCTORS(ClassName)  \
    ClassName() = delete; \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete; \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete;
#else
#define DISABLE_ALL_CONSTRUCTORS(ClassName)
#endif
