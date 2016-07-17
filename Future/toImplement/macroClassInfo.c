#define GET_CLASS_INFO_EXTENDS(extends, ...)    \
    extends

#define GET_CLASS_INFO_IMPLEMENTS(x, y, implements...)   \
    implements

#define GET_CLASS_INFO_NB_IMPLEMENTS(x, nb, ...)        \
    nb

#define GET_CLASS_INFO(what, extends, nbInter, interfaces...)       \
    GET_CLASS_INFO_ ## what(extends, nbInter, ##interfaces)

#define CLASS_INFO_String(what)                 \
    GET_CLASS_INFO(what, Object, 1, toString)

#define CLASS_INFO(name, what)                  \
    CLASS_INFO_ ## name(what)

CLASS_INFO(String, EXTENDS)
CLASS_INFO(String, IMPLEMENTS)
CLASS_INFO(String, NB_IMPLEMENTS)
