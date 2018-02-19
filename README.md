# Treat: C Traits+Objects library

This library is an experiment to create a trait-based system in C.
Unfortunately, using built-in datatypes is impossible, since there is no way to check if a `(void *)`-cast is proper and which object we actually received, unless we provide our own 'base' mechanism for this.


This library builds up on ideas of the [Object-Oriented programming in ANSI C](https://www.cs.rit.edu/~ats/books/ooc.pdf) book, which is a great read. However, in two ways this library is very different:

1. We do not create a separate pre-processor layer. Everything should still be written as normal C. Macros are fine, when used sensibly (they should only be used to do things that are impossible by other means).
2. We do not build a subtyping system, but a supertyping system with ad-hoc polymorphism: At any time:
  - New datatypes can be introduced
  - New traits can be introduced
  - A trait can be implemented for a certain datatype.

This mechanism is similar to _traits_ in Rust, _typeclasses_ in Haskell, _interfaces_ in Java, _mixins_ in Ruby, etc.
These traits are resolved at runtime and do not 'disappear' at compile-time (other than Rust's or C++'s). This does mean that this code is probably not extremely performant, but it should be more extensible and happiness-inducing for the programmer than plain old C99.

## Using Treat

You should include the `treat/treat.h` header in your file(s).
At the start of the program (before using any of Treat's functions), run `Treat.init()** to set up all known traits and trait-implementations, so the trait-dispatching logic can find them.

Custom Trait-implementations can be added using `Trait.add_impl(Trait *trait, Type *type, void *trait_implementation_struct);`

Now, you can use any of Treat's functions.
All datatypes have a module of their name, and the functions of this module are nested under this name, as you might know of other languages.
_(Under the hood, a module is a singular instance of a struct, and its fields are function-pointers to the approrpiate functions)_

The type name that is used is the same as the module name, but prefixed with a `T`. So the `Char` module's type name is`TChar`. (This is done because in C, a type and a value cannot have the same name.)

All data structure creation functions return pointers to data structures; they are intended to be passed by reference. The constructing function is called `new`:

`TChar *mychar = *Char.new('a');`

After finishing using something, run its destructor by calling the appropriate `destroy`:
`Char.destroy(mychar);`

There are also a general `Treat.new(DataType, zero, or, more, arguments);` and `Treat.destroy(any_datatype);`, but these should only be used
when you are not sure what type you'll end up with: The compiler will not be able to check mistakes in arguments in this case.


When having a datatype, any function of a trait that they implement can be used. An example is the `Inspect` trait that has the `inspect` function, which is implemented for (nearly?) all datatypes,
and returns a sensible string representation of the object useful for debugging:

```C
TInteger *fourtytwo = Integer.new(42);
Inspect.inspect(fourtytwo);
Integer.destroy(fourtytwo);
```


## Library Filestructure

The library itself is fully contained under the `src/treat` folder. This is what you should add to your project.
In this folder, we have the following:

- hash_map: used under the hood for trait dispatch. A version of https://github.com/Qqwy/c_hash_map
- trait: Contains the core trait creation and dispatcing logic.
- traits: Contains a folder for each of the traits already provided by Treat out of the box.
- type: Contains the core datatype creation and dispatching logic.
- types: Contains a folder for each of the datatypes already provided by Treat out of the box.
- utils: Contains a couple of simple utilities to help with allocation, printing errors and performing some math-related tasks.

Each of the main subfolders contains a `*.h `-file, which is the **external** header. This is what you include in your project when you use the code.
They usually also include a `*.ih`-file. This is the **internal** header, which should only be included from within the implementation of the specific module's functionality.

This separation means that your user-code scope is not cluttered with things defined/used by Treat.

### Module system

Modules are implemented as a single global struct that contains pointers to other structs or functions. This means that you can have calls like `Foo.Bar.baz(a, b, c)`.
For each module, the external header contains the struct that is used and a declaration of the actual module name.
The internal header contains a list of all included files, and a file called `__interface.c` contains the definition of the module struct, which links all appropriate functions to the module struct's fields.

Consumer Documentation is added inside the external header.

## Traits

### Creating a Trait

A Trait header file contains:

1. A module, just like the module system above, but its first field should be named `trait` and have the `TraitType` type.
_(This is required because this is where the trait's implementations will be stored.)_
2. A TraitImplementation-struct, which contains the calls that implementers require to implement a sfunction-pointer fields.

Usually, the function pointers are 1:1 the same between the two.

### Implementing a Trait

To implement a trait for a datatype, create an instance of the respective `TraitNameTraitImplementation` struct (like `InspectTraitImplementation` or `CloneTraitImplementation`).
Fill this struct's function pointer fields with the appropriate functions you wrote.
Usually, traits are supposed to be simple, which is why per trait implementation this library uses a single file (in the `trait_impls` directory of each datatype).

## Data Types

### Creating a new type

1. The actual datatype is a struct whose name starts with a capital `T` by convention (`TChar`, `TInteger`).
2. The module struct that implements all of the type's functions, has an extra field, which should be the first, calle `Type type`.
_(This is required because it is used for dynamic type lookup to find datatype size, constructor, destructor.)_
3. When setting up the module struct (in `__interface.c`), enter the appropriate fields of this struct as well:
  - The constructor (`.ctor`)
  - The destructor (`.dtor`)
  - The type struct size `(sizeof TYourType)`

A constructor accepts a `void *` as initial argument, and after this a variadic-argument list.
Inside the constructor, you should cast it to your `TYourType *`, and then fill it with the data you want, finally returning the same pointer.

The destructor accepts the same `void *`, and should free all pre-allocated fields (but not the structure as a whole), before returning the same pointer.

# The `T_with` macro

Using some Black Magic under the hood,
the T_with macro implements Resource Aquisition Is Initialization (RAII), or if you prefer:
Destruction Is Resource Relinquishment (DIRR).

Basically, the declared structure only lives for the passed block, and its `destructor` is automatically called once the block finishes.
Caveats:
1. Do not return while inside a T_with block, because this will skip the destructor.
2. Do not point the declared `TYourType * to somewhere else (or swap its value with another structure), because then the destructor will not be called properly anymore.

GCC is able to optimize the macro quite nicely :-).

Example:
```C
  T_with(TInteger * my_int, Integer.new(1234)) {
    Inspect.inspect(my_int);
  }
  // Look ma, no leaking! `my_int` is gone!
```
