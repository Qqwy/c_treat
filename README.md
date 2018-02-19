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

**TODO** In the future, you'll be able to add a list of your own traits as arguments to this function and add them at that time as well.

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

The library itself is split into


# The `T_with` macro
