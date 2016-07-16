# ObjectC
This project is a library to use as a superset of the C language.</br>
<h3>It offers the following :</h3>
</br>
  -Exceptions handling (try catch finally)</br>
  ```
  try {
   ...
  } catch(TypeName, VarName) {
   ...
  } finally {
   ...
  }
  ```
  -Classes, interfaces with Java like inheritance</br>
  ```
  class(Name, BaseClass, Interfaces...)
  {
  };
  
  virtual(Name)
  {
  };
  
  end_class(Name, OtherNames...);
  ```
  -Introspection
  ```
  Object *tmp = new(String, ctorS, "Hello") as(Object); // as only needed when casting from object to interface pointer
  isInstanceOf(String, tmp) // => true
  dynamic_cast(String, tmp)
  const char *(*method_toString)(String *) = getMethod(tmp, "toString");
  invoke(void, tmp, "toString");
  ```
  -Python Yield (co-routine, generators)</br>
  ```
  yields(int) range(int begin, int end)
  {
      for (int i = begin; i < end; i++)
         yields(i);
      yield_break(int);
  }
  
  int main()
  {
     for_yield(i, range(0, 5)) {
       printf("%d\n", i);
     }
     return 0;
  }
  ```
  -C++ life-cycle (RAII)</br>
  -C++ rvalue reference</br>
  -C#-like syntax for { get; set } (axors)</br>
  -private member and public methods</br>
  -override of methods</br>
  -etc...</br>
</br>
<h3>Features to come (See Future/ ): </h3>
  -Chained method call</br>
  -Python's format for strings</br>
  -A wrapper for gcc to add extra features and simplify syntax and improve error debuging</br>
  -A true ref counting system without loosing RAII</br>
  -scope(...) principle from Dlang</br>
  -A custom ABI for methods described as follow : type name_'number_of_arguments'(...)</br>
  -foreach() keyword using coroutines (yield)</br>
  
Disclamer: this project relies heavily gcc's extensions to the C language.
Most of thoses exist in clang under a different name but not all.
Therefore, for now, clang support is not a priority.
Once we feel confident in tagging the project in 1.0 then things may change.
The main prority is to improve the language and implement the above features.


Thanks.
