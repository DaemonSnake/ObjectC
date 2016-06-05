// Copyright (C) 2016  Bastien Penavayre

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

@CLASS()
{
    @CLASS_DEFINITION()
        {
            @class(class_name, parent, interfaces...)
                {
                    type name;
                    ...;
                };

            @virtual(class_name) [@class]
            {
                type @method(name, args...);
                @axors(type, name, @(@(set || get) || @(set && get)));
                ...;
            };

            @end_decl(class_name, other_classes_names...); [@class, @virtual]
        }

    @CLASS_IMPLEMENTATION()
        {
            type @new_method(class_name, name, args...) [@end_decl]
            {
                @CODE();
                $.name; /* => this->name; */
                $$(method_name, args...); /* => M(this, method_name, args...); */
            }

            @new_def_axors(class_name, var_name, @(@(set || get) || @(set && get)));

            @new_axor(class_name, var_name, get)
            {
            }

            @new_axor(class_name, var_name, set, type new_val)
            {
            }

            @new_tor(class_name, name, args...) [@end_decl]
            {
                /* if in a ctor */
                @superCtor(parent, ctor_name, args...);
                /* if in dtor */
                @superDtor();
                @CODE();
            }

            implement(class_name, parent, interfaces...) [@end_decl]
            {
                @CODE();
            }
        }
}

@INTERFACE()
{
    @interface(name)
        {
            type @method(name, args...);
            ...;
        }
}

@GLOBAL_VAR()
{
    type var_name;

    @Ginit(type, ctor, var_name, args...)
    {
        @CODE();
    }
}

@CODE()
{
    type @_var(true_type, var_name, ctor, args...), ...;
    type @_def(true_type, var_name, args...), ...;
    type *var_name = @new(type, ctor_name, args...);
    type *var_name = @newDef(type, args...);
    
    @delete(var_name);
    @M(var_name, method_name, args...);
    @axM(var_name, sub_var_name, new_val); /* set */
    @axM(var_name, sub_var_name); /* get */
    @static_cast(type, var_name);
    @dynamic_cast(type, var_name);
    var_name @as(type);
    @isInstance(type, var_name);
    type @method(method_p, args...) = @getMethod(var_name, method_name);
    @invoke(return_type, var_name, method_name, args...);
    @invokeM(method_p, var_name, args...);
    @ifIs(true_type, var_name) {
        @CODE();
    }
    else @ifIs(other_type, var_name) {
            @CODE();
    }
    @try {
        @CODE();
    }
    @catch(type, name) {
        @CODE();
    }
    @finally {
        @CODE();
    }

    @for_yield(saving_result, function_name, args...)
    {
        @CODE();
    }

    function_taking_object_pointer(..., @rvalue(type, ctor_name, args...), ...);
    type *var_name = @function_rvalue(type, ctor_name, args...);
    type *var_name = @retvalue(func_returning_object_copy());
    return @stdmove(var_name); /* move the destruction of var_name from one function back */
}

YIELD()
{
    type function_name(Generator *this, args...)
    {
        @initYield();
        ...;
        @yield(value);
        @yield_break; /* breaks the for_yield() loop */
        ...;
        return last_value;
    }
}
