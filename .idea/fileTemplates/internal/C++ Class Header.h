#parse("SimpleCopyrightFileHeader.h")
#[[#ifndef]]# ${INCLUDE_GUARD}
#[[#define]]# ${INCLUDE_GUARD}

namespace ${PROJECT_NAME} {
    class ${NAME} {
        public:
            ${NAME}();
            virtual ~${NAME}();
    };
} // namespace ${PROJECT_NAME}

#[[#endif]]# //${INCLUDE_GUARD}
