Hare-IDL
========

Hare-IDL is an attempt to create an IDL compiler along the lines briefly described on [ITHare.com](http://ithare.com/): http://ithare.com/idl-encodings-mappings-and-backward-compatibility/ .

Why another IDL?
----------------

One common line of argument goes along the lines of "we've already got Google Protocol Buffers, we won't ever need anything else". 

However, even for usual business-level distributed programming (where Google Protocol Buffers *protocol* is indeed usually a pretty good choice) there are quite a few features which are not supported by Google Protocol Buffers. Probably the most glaring and most-requested one is ability to use existing classes in your programming language for marshalling, but there are quite a few others (see "Features" section below for details).

And when we're moving into realm of games (including stock exchanges) and simulations, Google Protocol Buffers quickly become too inefficient (or, if you're implementing your own compression on top of them, too inconventient). Features necessary for game-oriented IDL include such things as differential compression (including delta and dead reckoning), fine-tuning on per-field basis, and statistical analysis. All these things are missing from existing IDLs, and we know how to implement them (though it is going to take some time).

Target Audience
---------------

Hare-IDL is aimed to provide easy-to-use and efficient marshalling to a gerenal programming audience. In addition, it is aimed to provide highly efficient encodings specifically optimized for games.

Platforms
---------

Hare-IDL will provide a compiler (idlc). It is written in C++ and we should be able idlc to run on Win/Linux/Mac

idlc generates marshalling code. In the really long run, we hope to provide support for (i.e. to generate marshalling code in) the following languages:

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
    * Google Protocol Buffers is one of the the best all-around byte-oriented protocols
- OUR-OWN: bitstream; optimized for games and simulations (with deltas of all kinds, dead reckoning etc., see http://ithare.com/mmog-world-states-and-reducing-traffic/ for further discussion)
- STANDARD: JSON
- STANDARD: ASN.1 DER
    * parsing X.509 makes an interesting task :)

Features
--------

Eventually, we hope to provide the following features (those features **not found** in Google Protocol Buffers, are shown in **bold**),

### Features of common interest

-  **Different encodings for the same IDL (switched without any changes to the app-level code)**
-  **Ability to use existing class/structure in target language for mapping**
-  **Ability to use existing class/structure in target language as an IDL**
-  **Different mappings from the same IDL**
-  Extensibility
-  **Formal backward compatibility checks**
-  **IDL Versioning**
-  MAYBE IN THE LONG-RUN: **support for RPCs with futures** (see here: http://ithare.com/asynchronous-processing-for-finite-state-machines-actors-from-plain-events-to-futures-with-oo-and-lambda-call-pyramids-in-between/)

### Features which are of the most interest for games (including stock exchanges) and simulations

-  **Ability to adjust encoding on per-field basis (for applicable encoding(s))**
-  **Support for the differential handling for relevant encoding(s)**
-  **Support for lossy encoding(s)**
-  **bit-oriented encoding(s) with associated goodies (including per-field Huffman)**
-  **statistics gathering during test run and encoding optimization recommendations**
 
