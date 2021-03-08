# FM-Index

This is implemented based on the description from [this blog post](http://olivernash.org/2014/01/03/dna-of-a-password-disaster/index.html).

A detailed description of the components and the overall operation can be found under `//doc` or [here](https://bcsgh.github.io/publication/fm-index/fm-index.pdf).

## Capabilities

An FM index  object can be constructed from a `std::string` in `O(n)` space and `O(n log n)` time.
Once constructed the index can be queried for the number of occurrences of a query string `q` in `O(len(q))` time.

## TODO

Add the ability to locate strings in the original string.
