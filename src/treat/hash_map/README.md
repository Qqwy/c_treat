# HashMap

This mini-library implements a very simple HashMap.

No guarantees are given as to the efficiency of the code.
It should be correct; in the small examples I have tested it with it does not leak memory.

The HashMap is super-simple: Removing elements is impossible, and therefore it also does not have functionality to make itself smaller again.

Virtually anything can be stored inside, as void-pointers are used as both key- and value-types. Of course, care needs to be taken when reading out a previously-stored value to cast it to the desired value type properly. Do note that because stored types are interpreted as pointers, storing an integer `0` as key is a bad idea: it will look as if the key is still empty.

## Usage

1. The library is included by including the `hash_map/hash_map.h` header.
2. Allocate a HashMap with the desired capacity (expected size) using `HashMap hash_map = HashMap_new(capacity)`.
3. Add elements using `HashMap_insert(&hash_map, key, value)`. This call might resize the HashMap to a larger one.
4. Search for an element using `HashMap_lookup(hash_map, key)`. `NULL` will be returned if the key is not inside the table.
5. After finishing using the HashMap, use `HashMap_destroy(hash_map)` to clean it up and free its memory.
