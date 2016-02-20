Hare-IDL
========

Hare-IDL is an attempt to create an IDL compiler along the lines briefly described on [ITHare.com](http://ithare.com/): http://ithare.com/idl-encodings-mappings-and-backward-compatibility/ .

Target Audience
---------------

Hare-IDL is aimed to provide easy-to-use and efficient marshalling to a gerenal programming audience. In addition, it is aimed to provide highly efficient encodings specifically optimized for games.

Platforms
---------

Hare-IDL provides a compiler (idlc). We hope to have idlc run on Win/Linux/Mac

Hare-IDL generates marshalling code. In the really long run, we hope to provide support for (i.e. to generate marshalling code in) the following languages:

- C++
- JavaScript
- Java
- Python
- C#

We'll also provide a way to write a code generator for any-language-you-want relatively easily (at least without knowledge of C++ being necessary).

Encodings
---------

In theory, Hare-IDL can support pretty much any encoding. In the long run, we hope to support the following standard and our own encodings:

- STANDARD: Google Protocol Buffers
    * Google Protocol Buffers is probably the best all-around byte-oriented protocol
- OUR-OWN: bitstream; optimized for games and simulations (with deltas of all kinds, dead reckoning etc., see http://ithare.com/mmog-world-states-and-reducing-traffic/ for further discussion)
- STANDARD: JSON
- STANDARD: ASN.1 DER
    * parsing X.509 makes an interesting task :)

Features
--------

We hope to provide the following features:

### Features of common interest

-  Different encodings for the same IDL (switched without any changes to the app-level code)
-  Ability to use existing structure as an IDL
-  Different mappings from the same IDL
-  Extensibility
-  Formal backward compatibility checks
-  IDL Versioning
-  MAYBE IN THE LONG-RUN: support for RPCs with futures (see here: http://ithare.com/asynchronous-processing-for-finite-state-machines-actors-from-plain-events-to-futures-with-oo-and-lambda-call-pyramids-in-between/)

### Features which are of the most interest for games (including stock exchanges) and simulations

-  Ability to adjust encoding on per-field basis (for applicable encoding(s))
-  Support for the differential handling for relevant encoding(s)
-  Support for lossy encoding(s)
