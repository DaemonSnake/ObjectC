struct __virtual_Object
{
  void (*dtor)(void *);
  const char *(*toString)(const void *);
  const Type *(*getType)(const void *);
};

struct __data_Object
{
  const Type *__class_type;
};

struct Object
{
  Object *this;
  const struct __virtual_Object *_virtual;
  struct __data_Object;
};
/*---------------------------------------------*/
struct I 
{
 Object *this;
 const struct __virtual_I *_virtual;
};

struct __virtual_I
{
  void (*print)(void *);
};
/*---------------------------------------------*/
struct __supers_virtual_Debug 
{
 struct __virtual_Object;
 struct __virtual_I;
};

struct __supers_data_Debug 
{
  struct __data_Object; // replace char __private_Object[sizeof(...)]
  Object *this_Object;
  I *this_I;
  I *__true_this_I;
  struct __virtual_I *_virtual_I; // replace char __private_I[sizeof(...)]
};

struct __weak_data_Debug
{
};

struct __weak_virtual_Debug
{
};

struct __virtual_Debug 
{
 struct __supers_virtual_Debug;
 struct __weak_virtual_Debug;
};

struct __data_Debug 
{
 struct __supers_data_Debug;
 struct __weak_data_Debug;
};

struct Debug
{
 Debug *this;
 const struct __virtual_Debug *_virtual;
 struct __data_Debug; // replace char __private_Debug[sizeof(...)]
};

/*
  struct __private_Debug
{
Debug *this;
const struct __virtual_Debug *_virtual;
struct __data_Debug;
};
