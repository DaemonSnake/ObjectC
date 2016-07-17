#define CLASS(name) String ## __ ## name
#define ADD_THIS_P(args...) (CLASS(private) *this, ##args)
#define ADD_THIS(args...) (void *this, ##args)
#define method(name) (*name)ADD_THIS

//SwitchNamespace(String);

struct String
{
 void method(toString)();
};
//SwitchNamespace(String);
#define NAMESPACE(name) String ## __ ## name

#define GLUE2(x, y) x ## y
#define GLUE(x, y) GLUE2(x, y)
#define new_method(class, name...) GLUE(NAMESPACE(class), name) ADD_THIS_P

void new_method(toString)()
{
}

//SwitchNamespace();
#undef NAMESPACE
#define NAMESPACE(name) name ## __
void new_method(String, toString)()
{
}
