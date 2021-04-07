# FM-Index

This is implemented based on the description from [this blog post](http://olivernash.org/2014/01/03/dna-of-a-password-disaster/index.html).

A detailed description of the components and the overall operation can be found under `//doc` or [here](https://bcsgh.github.io/publication/fm-index/fm-index.pdf).

## Capabilities

An `FMIndex` object can be constructed from a `std::string` in `O(n)` space and `O(n log n)` time.
Once constructed the index can be queried for the number of occurrences of a query string `q` in `O(len(q))` time.

An `FMIndexLookup` object be constructed from a `std::vector<std::string>` in
 (where `n=sum(len)`) `O(n)` space and `O(n log n)` time.
The set of strings given must be unique and must have no embedded `\0`.
Once constructed an `FMIndexLookup` can be queried like an `FMIndex` and also yeild the
 "indexes" of the matching records which can be converted back to the origianl strings.
This API is intended to support more complex queries like those needed for an autocomplete.
