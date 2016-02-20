Development Flow and Relese Versioning
======================================

Development Flow
----------------

We're using development flow as described here: http://nvie.com/posts/a-successful-git-branching-model/

For the time being, we're using *develop* as a default branch, creating *feature* branches as necessary for development. 

**One feature per feature branch** rule applies!

Merges to *master* are made ONLY at the points of "releases".

Releases and Versioning
-----------------------

Each release is a commit to *master*, each commit to *master* is a "release". 

Each commit to *master* MUST have a tag with "release version"

We're using Semantic Versioning as defined on http://semver.org/

For the time being, to comply with SemVer, we MUST have all the release versions as *0.x.y*. 
Note that x MAY go above 9, so 0.10.0 is a perfectly valid number)
