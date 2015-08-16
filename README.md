# m_smallintset
Integer set implementation with the upper bound of 65536.

## Features
### Addition and removal
In order to add (or remove) integers, use the `m_smallintset_add` (or
`m_smallintset_remove`) functions. Both manipulation functions have an `_all`
version that adds (or removes) all integers within the range `0..65535`.

### Presence test
To check if a certain integer is a member of the set, use the
`m_smallintset_contains` function. In case of a successful hit, the
`M_SMALLINTSET_TRUE` is returned, `M_SMALLINTSET_FALSE` otherwise.

### Set operations
#### Union & intersection
To perform the binary union (or intersect) operation, use the
`m_smallintset_union` (or `m_smallintset_intersect`) function. Both functions 
take two arguments - a `m_smallintset` instances - and store the result of the
operation into the first argument.

#### Complement
Using the `m_smallintset_complement` function, all every membership becomes
negated and therefore a set complement is created. This function modifies the
`m_smallintset` in question.

## Design
Internally, `m_smallintset` stores the presence of an integer as a single bit
inside an array. Since the library poses a limit on the upper bound of the
integers, we can compute the number of bytes needed: `65536 / 8 = 8192`.

## Performance
The library is written with performance in mind. All necessary memory is
pre-allocated in the `m_smallintset_init` function. The following benchmark
runs the `m_smallintset_contains` function `100000000` times and computes the
time necessary to perform the lookups in microseconds.

```C
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <m_smallintset.h>

#define LOOPS 100000000

int
main(void)
{
	uint32_t i;
	struct m_smallintset sis;
	uint64_t cnt;
	struct timeval start;
	struct timeval end;
	uint64_t diff;

	m_smallintset_init(&sis);

	for (i = 0; i < 0xfff; i++)
		m_smallintset_add(&sis, (uint16_t)(rand() % 0xffff));

	gettimeofday(&start, NULL);
	for (i = 0; i < LOOPS; i++)
		if (m_smallintset_contains(&sis, (uint16_t)(i % 0xffff)) == M_SMALLINTSET_TRUE)
			cnt++;
	gettimeofday(&end, NULL);

	diff = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
	printf("cnt = %llu\n", cnt);
	printf("diff = %llu\n", diff);
}
```
TODO what are the times, -O3, does LLVM Polly help? does it actually perform
the lookups? Does it use SIMD instructions on x86 or ARM?

## Memory consumption
After a call to the `m_smallintset_init` function, a `m_smallintset` takes
exactly 8192 bytes of memory plus `O(1)` of additional space, making the data
structure _implicit_. This space is always constant and does not depend on the
number of integers stored in the set.

## Build
```
$ ninja
```

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3
 * OS X 10.9 with Clang 3.5
 * Linux Gentoo 2.2 with Clang 3.6

If a platform does not appear to be in the previous list, it does not mean that
`m_smallintset` will not work in such environment. It only means that nobody
tested it - you are encouraged to do so and report either success or failure.

## License
2-clause BSD license. For more information please consult the
[LICENSE](LICENSE.md) file. In the case that you need a different license, feel
free to contact me.

## Author
Daniel Lovasko daniel.lovasko@gmail.com

