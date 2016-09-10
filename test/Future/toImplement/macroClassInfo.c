#define GET_CLASS_INFO_EXTENDS(extends, ...)    \
    extends

#define GET_CLASS_INFO_IMPLEMENTS(x, y, implements...)   \
    implements

#define GET_CLASS_INFO_NB_IMPLEMENTS(x, nb, ...)        \
    nb

#define CLASS_INFO_String(what)                 \
    GET_CLASS_INFO_ ## what(Object, 2, toString, Serializable)

#define CLASS_INFO(name, what)                  \
    CLASS_INFO_ ## name(what)

CLASS_INFO(String, EXTENDS)
CLASS_INFO(String, NB_IMPLEMENTS)
CLASS_INFO(String, IMPLEMENTS)
